/*
 * ESP32 MPD 远程显示客户端
 * 屏幕：0.96寸 ST7735S 80×160 IPS，SPI，横向使用
 *
 * 使用 TFT_eSPI 库（硬件 SPI，ESP32 优化），替代 Adafruit 库（软件 SPI）
 * TFT_eSPI 的 pushImage() 使用硬件 SPI 批量传输，速度比 Adafruit 快 10x+
 *
 * 【性能优化要点】
 *   1. MPD 响应用静态 char 数组接收，避免 String 堆碎片
 *   2. 标志位解析用 strstr + 直接比较字符，不产生临时 String
 *   3. UI 脏检查：内容未变时跳过 lv_label_set_text，减少 LVGL 重绘
 *   4. 时间标签和进度条只在整秒跳变时更新，不每帧都写
 *   5. disp_flush_cb 使用 TFT_eSPI::pushImage 批量 SPI 传输（硬件 SPI）
 *   6. MPD 保持长连接，避免每秒 TCP 重连
 *   7. LVGL 缓冲区全屏（160×80），减少 flush 次数
 *   8. 用 char 数组 + enum 替代 String 做状态比较
 *   9. MPD 通信使用非阻塞状态机，不阻塞 LVGL 渲染
 */

#include <Arduino.h>
#include <WiFi.h>
#include <TFT_eSPI.h>
#include <lvgl.h>
#include <driver/gpio.h>

// ============================================================
//  网络与 MPD 配置
// ============================================================
static const char*         WIFI_SSID        = "ChinaNet-VsFM";
static const char*         WIFI_PASSWORD    = "2pwv2z5n";
static const char*         MPD_HOST         = "192.168.1.33";
static const int           MPD_PORT         = 6600;
static const unsigned long WIFI_TIMEOUT_MS  = 15000;
static const unsigned long MPD_TIMEOUT_MS   = 300;
static const unsigned long MPD_INTERVAL_MS  = 1000;
static const unsigned long FLIP_INTERVAL_MS = 7000;

// ============================================================
//  按键配置（IO09，另一侧接 GND，内部上拉）
// ============================================================
static const uint8_t  BTN_PIN         = 9;
static const uint32_t BTN_DEBOUNCE_MS = 50;   // 消抖时间
static const uint32_t BTN_COOLDOWN_MS = 500;  // 防止连发的冷却时间

WiFiClient client;

// ============================================================
//  播放器状态（用 enum + char[] 替代 String，避免堆分配）
// ============================================================
enum PlayStatus : uint8_t { STATUS_STOPPED, STATUS_PLAYING, STATUS_PAUSED };

struct PlayerState {
    char   title[128]  = "No Title";
    char   artist[128] = "Unknown";
    char   album[128]  = "Unknown Album";
    char   vol[8]      = "100";
    PlayStatus status  = STATUS_STOPPED;
    bool   repeat    = false;
    bool   random    = false;
    bool   single    = false;
    bool   consume   = false;
    bool   crossfade = false;
    float  duration  = 0.0f;
    float  elapsed   = 0.0f;
};
static PlayerState state;

// ============================================================
//  TFT_eSPI 初始化
//  引脚在 include/User_Setup.h 中配置
// ============================================================
static TFT_eSPI tft = TFT_eSPI();

static void initDisplay() {
    tft.init(INITR_GREENTAB160x80);
    delay(200);
    tft.setSwapBytes(true);
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
}

// ============================================================
//  LVGL 显示驱动
// ============================================================
static const uint16_t SCREEN_W = 160;
static const uint16_t SCREEN_H =  80;

static lv_disp_draw_buf_t draw_buf;
// 缓冲区全屏（160×80），减少 flush 次数
static lv_color_t lv_buf[SCREEN_W * SCREEN_H];

static void disp_flush_cb(lv_disp_drv_t* drv, const lv_area_t* area, lv_color_t* color_p) {
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;
    // TFT_eSPI::pushImage 使用硬件 SPI 批量传输，极快
    tft.pushImage(area->x1, area->y1, w, h, (uint16_t*)&color_p->full);
    lv_disp_flush_ready(drv);
}

// ============================================================
//  UI 控件句柄
// ============================================================
static lv_obj_t* label_status;
static lv_obj_t* label_flags;
static lv_obj_t* label_vol;
static lv_obj_t* label_title;
static lv_obj_t* cont_subinfo;
static lv_obj_t* label_artist;
static lv_obj_t* label_album;
static lv_obj_t* label_time_el;
static lv_obj_t* label_time_to;
static lv_obj_t* bar_progress;

LV_FONT_DECLARE(fusion_pixel_12);
LV_FONT_DECLARE(fusion_pixel_10);

// ============================================================
//  UI 辅助函数
// ============================================================
static void create_separator_line(int y) {
    lv_obj_t* line = lv_obj_create(lv_scr_act());
    lv_obj_set_size(line, 148, 1);
    lv_obj_set_pos(line, 6, y);
    lv_obj_set_style_bg_color(line,     lv_color_hex(0x333333), 0);
    lv_obj_set_style_border_width(line, 0, 0);
    lv_obj_set_style_radius(line,       0, 0);
}

// 脏检查：内容相同时跳过，避免 LVGL 无效重绘
static void label_set_if_changed(lv_obj_t* label, const char* text) {
    if (strcmp(lv_label_get_text(label), text) != 0) {
        lv_label_set_text(label, text);
    }
}

// 自适应滚动速度：根据文本超出宽度动态调整，使每次来回周期固定
// target_period_ms：期望的单程滚动时长（毫秒），默认 3000ms
// min_speed：最低速度下限（防止极短溢出时速度为 0）
static void set_scroll_speed_adaptive(lv_obj_t* label, uint32_t target_period_ms = 3000,
                                      uint32_t min_speed = 8) {
    // lv_obj_get_scroll_x 不适用于 LONG_SCROLL 标签，改用文本宽度 - 控件宽度
    lv_coord_t obj_w    = lv_obj_get_width(label);
    lv_coord_t txt_w    = lv_obj_get_scroll_right(label) + obj_w;  // 文本实际渲染宽度近似
    lv_coord_t overflow = lv_obj_get_scroll_right(label);           // 右侧剩余可滚动量

    if (overflow <= 0) {
        // 文本放得下，不需要滚动，设一个很慢的速度（实际不会滚）
        lv_obj_set_style_anim_speed(label, min_speed, 0);
        return;
    }

    // speed (px/s) = overflow (px) / target_period (s)
    uint32_t speed = (uint32_t)((overflow * 1000UL) / target_period_ms);
    if (speed < min_speed) speed = min_speed;

    lv_obj_set_style_anim_speed(label, speed, 0);
}

// 文本更新后调用：先设置文字，再重算速度
// 注意：LVGL 在 lv_label_set_text 后，内部 layout（文本换行、宽度计算）是懒惰求值的，
// 需要经过多次 lv_timer_handler 才能得到正确的 scroll_right。
// 用帧倒计数（frames_until_update）替代简单布尔：文本变化后等 4 帧再读取 scroll_right。
static const uint8_t SCROLL_SETTLE_FRAMES = 4;

struct ScrollLabel {
    lv_obj_t*  obj;
    uint8_t    frames_until_update; // 0 = 不需要更新；>0 = 还需等待的帧数
    uint32_t   period_ms;
};

static ScrollLabel scroll_labels[3]; // title / artist / album
static uint8_t     scroll_label_count = 0;

static void scroll_label_register(lv_obj_t* label, uint32_t period_ms = 3000) {
    if (scroll_label_count < 3) {
        scroll_labels[scroll_label_count++] = {label, 0, period_ms};
    }
}

static void scroll_label_set_text(lv_obj_t* label, const char* text) {
    if (strcmp(lv_label_get_text(label), text) == 0) return;
    lv_label_set_text(label, text);
    // 文本变化后，重置倒计数，等待 layout 稳定后再更新速度
    for (uint8_t i = 0; i < scroll_label_count; i++) {
        if (scroll_labels[i].obj == label) {
            scroll_labels[i].frames_until_update = SCROLL_SETTLE_FRAMES;
            break;
        }
    }
}

// 在 loop() 的 lv_timer_handler() 之后调用，每帧递减计数，到 0 时执行更新
static void scroll_labels_update_speeds() {
    for (uint8_t i = 0; i < scroll_label_count; i++) {
        if (scroll_labels[i].frames_until_update == 0) continue;
        scroll_labels[i].frames_until_update--;
        if (scroll_labels[i].frames_until_update == 0) {
            set_scroll_speed_adaptive(scroll_labels[i].obj, scroll_labels[i].period_ms);
        }
    }
}

// ============================================================
//  UI 布局
//
//  Y= 0 ┌─────────────────────────────┐
//       │ [>] 状态       [rz--] V:80% │  ← 10px 高，fusion_pixel_10
//  Y=14 ├─────────────────────────────┤  ← 1px 分割线
//  Y=18 │ 歌曲名（跑马灯）             │  ← 12px 高，fusion_pixel_12
//  Y=34 │ by 艺术家 / from 专辑（翻页）│  ← 20px 高，每 7s 切换
//  Y=55 │ 00:00               00:00   │  ← fusion_pixel_10
//  Y=68 │ ████████░░░░░░░░░░░░░░░░░░  │  ← 6px 进度条
//  Y=80 └─────────────────────────────┘
// ============================================================
static void setup_ui() {
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), 0);

    // ------ 顶部栏：状态图标（左） ------
    label_status = lv_label_create(lv_scr_act());
    lv_obj_set_pos(label_status, 6, 2);
    lv_obj_set_style_text_color(label_status, lv_color_hex(0x4A90E2), 0); // ✈ 航太蓝（未联网）
    lv_obj_set_style_text_font(label_status, &fusion_pixel_10, 0);
    lv_label_set_text(label_status, "...");

    // ------ 顶部栏：模式标志（右） ------
    label_flags = lv_label_create(lv_scr_act());
    lv_obj_set_pos(label_flags, 38, 2);
    lv_obj_set_width(label_flags, 80);
    lv_obj_set_style_text_align(label_flags, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_style_text_color(label_flags, lv_color_hex(0x008F11), 0);
    lv_obj_set_style_text_font(label_flags, &fusion_pixel_10, 0);
    lv_label_set_text(label_flags, "[----]");

    // ------ 顶部栏：音量（右端，中金色） ------
    label_vol = lv_label_create(lv_scr_act());
    lv_obj_set_pos(label_vol, 120, 2);
    lv_obj_set_width(label_vol, 34);
    lv_obj_set_style_text_align(label_vol, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_style_text_color(label_vol, lv_color_hex(0x996600), 0);
    lv_obj_set_style_text_font(label_vol, &fusion_pixel_10, 0);
    lv_label_set_text(label_vol, "V:0%");

    create_separator_line(14);

    // ------ 歌曲名（跑马灯） ------
    label_title = lv_label_create(lv_scr_act());
    lv_obj_set_pos(label_title, 6, 18);
    lv_obj_set_width(label_title, 148);
    lv_label_set_long_mode(label_title, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_text_color(label_title, lv_color_hex(0xEBE7E0), 0);
    lv_obj_set_style_text_font(label_title, &fusion_pixel_12, 0);
    lv_label_set_text(label_title, "...");
    scroll_label_register(label_title, 3000); // 单程 3 秒

    // ------ 艺术家 / 专辑翻页容器 ------
    cont_subinfo = lv_obj_create(lv_scr_act());
    lv_obj_set_pos(cont_subinfo, 6, 34);
    lv_obj_set_size(cont_subinfo, 148, 20);
    lv_obj_set_style_bg_opa(cont_subinfo,     LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(cont_subinfo, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_all(cont_subinfo,    0, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(cont_subinfo,   LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(cont_subinfo, LV_OBJ_FLAG_SCROLL_ELASTIC);

    // 第一楼：艺术家 (内部 Y=0)
    lv_obj_t* prefix_by = lv_label_create(cont_subinfo);
    lv_obj_set_pos(prefix_by, 0, 0);
    lv_obj_set_style_text_color(prefix_by, lv_color_hex(0x666666), 0);
    lv_obj_set_style_text_font(prefix_by, &fusion_pixel_12, 0);
    lv_label_set_text(prefix_by, "by");

    label_artist = lv_label_create(cont_subinfo);
    lv_obj_set_pos(label_artist, 20, 0);
    lv_obj_set_width(label_artist, 128);
    lv_label_set_long_mode(label_artist, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_text_color(label_artist, lv_color_hex(0xAAAAAA), 0);
    lv_obj_set_style_text_font(label_artist, &fusion_pixel_12, 0);
    lv_label_set_text(label_artist, "...");
    scroll_label_register(label_artist, 3000);

    // 第二楼：专辑 (内部 Y=20)
    lv_obj_t* prefix_from = lv_label_create(cont_subinfo);
    lv_obj_set_pos(prefix_from, 0, 20);
    lv_obj_set_style_text_color(prefix_from, lv_color_hex(0x666666), 0);
    lv_obj_set_style_text_font(prefix_from, &fusion_pixel_12, 0);
    lv_label_set_text(prefix_from, "from");

    label_album = lv_label_create(cont_subinfo);
    lv_obj_set_pos(label_album, 32, 20);
    lv_obj_set_width(label_album, 116);
    lv_label_set_long_mode(label_album, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_text_color(label_album, lv_color_hex(0x888888), 0);
    lv_obj_set_style_text_font(label_album, &fusion_pixel_12, 0);
    lv_label_set_text(label_album, "...");
    scroll_label_register(label_album, 3000);

    // 透明撑高控件
    lv_obj_t* spacer = lv_obj_create(cont_subinfo);
    lv_obj_set_size(spacer, 1, 1);
    lv_obj_set_pos(spacer, 0, 39);
    lv_obj_set_style_bg_opa(spacer,      LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(spacer, 0, 0);

    // ------ 时间标签 ------
    label_time_el = lv_label_create(lv_scr_act());
    lv_obj_set_pos(label_time_el, 6, 55);
    lv_obj_set_style_text_color(label_time_el, lv_color_hex(0x816797), 0);
    lv_obj_set_style_text_font(label_time_el, &fusion_pixel_10, 0);
    lv_label_set_text(label_time_el, "00:00");

    label_time_to = lv_label_create(lv_scr_act());
    lv_obj_set_pos(label_time_to, 114, 55);
    lv_obj_set_width(label_time_to, 40);
    lv_obj_set_style_text_align(label_time_to, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_style_text_color(label_time_to, lv_color_hex(0x546E7A), 0);
    lv_obj_set_style_text_font(label_time_to, &fusion_pixel_10, 0);
    lv_label_set_text(label_time_to, "00:00");

    // ------ 进度条 ------
    bar_progress = lv_bar_create(lv_scr_act());
    lv_obj_set_size(bar_progress, 148, 6);
    lv_obj_set_pos(bar_progress, 6, 68);
    lv_bar_set_range(bar_progress, 0, 100);

    lv_obj_set_style_radius(bar_progress,       0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(bar_progress,     lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_border_width(bar_progress, 1, LV_PART_MAIN);
    lv_obj_set_style_border_color(bar_progress, lv_color_hex(0x555555), LV_PART_MAIN);
    lv_obj_set_style_pad_all(bar_progress,      1, LV_PART_MAIN);

    lv_obj_set_style_radius(bar_progress,   0, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(bar_progress, lv_color_hex(0xE69F00), LV_PART_INDICATOR);
}

// ============================================================
//  工具：秒数 → "mm:ss"（写入静态缓冲区，不返回 String）
// ============================================================
static char time_buf[8];
static const char* formatTime(int totalSec) {
    sprintf(time_buf, "%02d:%02d", totalSec / 60, totalSec % 60);
    return time_buf;
}

// ============================================================
//  MPD 响应解析辅助
// ============================================================
static bool extractField(const char* resp, const char* key, char* out, int outLen) {
    const char* p = strstr(resp, key);
    if (!p) { out[0] = '\0'; return false; }
    p += strlen(key);
    const char* end = strchr(p, '\n');
    int len = end ? (int)(end - p) : (int)strlen(p);
    if (len >= outLen) len = outLen - 1;
    memcpy(out, p, len);
    while (len > 0 && (out[len-1] == '\r' || out[len-1] == ' ')) len--;
    out[len] = '\0';
    return true;
}

static bool extractFlag(const char* resp, const char* key) {
    const char* p = strstr(resp, key);
    if (!p) return false;
    return *(p + strlen(key)) == '1';
}

// ============================================================
//  UI：将 state 写入控件（脏检查）— 前向声明，供状态机调用
// ============================================================
static void update_ui_values();

// ============================================================
//  MPD 非阻塞状态机
//
//  将原来的阻塞式 fetchMPDData() 拆分为状态机，每次 loop() 只做
//  一小步工作（发送命令或读取可用字节），不阻塞 LVGL 渲染。
//
//  状态流转：
//    IDLE → SEND_STATUS → READ_STATUS → SEND_CURRENTSONG
//         → READ_CURRENTSONG → PARSE → IDLE
//
//  每次进入 loop() 时，如果当前状态不是 IDLE，就继续推进状态机；
//  如果状态是 IDLE 且距上次同步超过 MPD_INTERVAL_MS，则启动新一轮。
// ============================================================
enum MpdState : uint8_t {
    MPD_IDLE,
    MPD_SEND_STATUS,
    MPD_READ_STATUS,
    MPD_SEND_CURRENTSONG,
    MPD_READ_CURRENTSONG,
    MPD_PARSE
};

static MpdState       mpdState       = MPD_IDLE;
static unsigned long  mpdStateStart  = 0;
static unsigned long  lastSyncTime   = 0;
static float          baseElapsed    = 0.0f;
static bool           mpdConnected   = false;

// 非阻塞读取缓冲区（累积本次命令的响应数据）
static char mpd_buf[1024];
static int  mpd_buf_len = 0;

static void ensureMPDConnected() {
    if (!mpdConnected || !client.connected()) {
        client.stop();
        if (client.connect(MPD_HOST, MPD_PORT)) {
            // 同步吃掉欢迎行（只在连接时做一次阻塞读取，可接受）
            unsigned long start = millis();
            int len = 0;
            while (millis() - start < MPD_TIMEOUT_MS) {
                while (client.available() && len < (int)sizeof(mpd_buf) - 1) {
                    mpd_buf[len++] = (char)client.read();
                    if (len >= 3 &&
                        mpd_buf[len-3] == 'O' &&
                        mpd_buf[len-2] == 'K' &&
                        mpd_buf[len-1] == '\n') {
                        mpd_buf[len] = '\0';
                        goto connected;
                    }
                }
            }
connected:
            mpdConnected = true;
        } else {
            mpdConnected = false;
        }
    }
}

// 非阻塞读取：从 TCP 读取可用字节到 mpd_buf，返回 true 表示收到 "OK\n"
static bool readAvailable() {
    while (client.available() && mpd_buf_len < (int)sizeof(mpd_buf) - 1) {
        mpd_buf[mpd_buf_len++] = (char)client.read();
        if (mpd_buf_len >= 3 &&
            mpd_buf[mpd_buf_len-3] == 'O' &&
            mpd_buf[mpd_buf_len-2] == 'K' &&
            mpd_buf[mpd_buf_len-1] == '\n') {
            mpd_buf[mpd_buf_len] = '\0';
            return true; // 收到完整响应
        }
    }
    return false; // 还没收完
}

// 解析 mpd_buf 中的 status 响应到 state
static void parseStatusResponse(const char* resp) {
    char tmp[64];

    if (extractField(resp, "state: ", tmp, sizeof(tmp))) {
        if      (strcmp(tmp, "play")  == 0) state.status = STATUS_PLAYING;
        else if (strcmp(tmp, "pause") == 0) state.status = STATUS_PAUSED;
        else                                state.status = STATUS_STOPPED;
    }

    bool gotElapsed = false;
    if (extractField(resp, "elapsed: ", tmp, sizeof(tmp))) {
        state.elapsed = atof(tmp);
        gotElapsed = true;
    }
    if (extractField(resp, "time: ", tmp, sizeof(tmp))) {
        char* col = strchr(tmp, ':');
        if (col) {
            *col = '\0';
            if (!gotElapsed) state.elapsed = atof(tmp);
            state.duration = atof(col + 1);
        }
    }

    if (extractField(resp, "volume: ", tmp, sizeof(tmp))) {
        strncpy(state.vol, tmp, sizeof(state.vol) - 1);
        state.vol[sizeof(state.vol) - 1] = '\0';
    }

    state.repeat    = extractFlag(resp, "repeat: ");
    state.random    = extractFlag(resp, "random: ");
    state.single    = extractFlag(resp, "single: ");
    state.consume   = extractFlag(resp, "consume: ");
    state.crossfade = false;
    if (extractField(resp, "xfade: ", tmp, sizeof(tmp))) {
        state.crossfade = (atoi(tmp) > 0);
    }
}

// 解析 mpd_buf 中的 currentsong 响应到 state
static void parseSongResponse(const char* resp) {
    char tmp[64];

    if (extractField(resp, "Title: ", tmp, sizeof(tmp))) {
        strncpy(state.title, tmp, sizeof(state.title) - 1);
        state.title[sizeof(state.title) - 1] = '\0';
    }
    if (extractField(resp, "Artist: ", tmp, sizeof(tmp))) {
        strncpy(state.artist, tmp, sizeof(state.artist) - 1);
        state.artist[sizeof(state.artist) - 1] = '\0';
    }
    if (extractField(resp, "Album: ",  tmp, sizeof(tmp))) {
        strncpy(state.album, tmp, sizeof(state.album) - 1);
        state.album[sizeof(state.album) - 1] = '\0';
    }
}

// 发送 MPD next 命令，立即跳下一首
static void sendMpdNext() {
    if (!mpdConnected) return;

    // 清空残留，发送命令
    while (client.available()) client.read();
    client.print("next\n");

    // 等待 OK\n，最多 300ms
    uint32_t t = millis();
    while (millis() - t < 300) {
        if (client.available()) {
            String line = client.readStringUntil('\n');
            if (line.startsWith("OK") || line.startsWith("ACK")) break;
        }
    }

    // 重置缓冲区，强制立刻触发一次完整轮询
    mpd_buf_len = 0;
    mpdState    = MPD_SEND_STATUS;
}

// 非阻塞 MPD 状态机：每次 loop() 调用一次，推进一小步
static void mpdStateMachine() {
    if (!mpdConnected) {
        ensureMPDConnected();
        return;
    }

    switch (mpdState) {
    case MPD_IDLE:
        break;

    case MPD_SEND_STATUS:
        // 清空 TCP 输入缓冲区，防止残留数据
        while (client.available()) client.read();
        client.print("status\n");
        mpdStateStart = millis();
        mpd_buf_len = 0;
        mpdState = MPD_READ_STATUS;
        break;

    case MPD_READ_STATUS:
        if (readAvailable()) {
            // 收到完整 status 响应，立即解析（mpd_buf 随后会被 currentsong 覆盖）
            parseStatusResponse(mpd_buf);
            mpdState = MPD_SEND_CURRENTSONG;
        } else if (millis() - mpdStateStart > MPD_TIMEOUT_MS) {
            mpdState = MPD_IDLE;
        }
        break;

    case MPD_SEND_CURRENTSONG:
        // 清空 TCP 输入缓冲区，防止 status 残留数据污染 currentsong
        while (client.available()) client.read();
        client.print("currentsong\n");
        mpdStateStart = millis();
        mpd_buf_len = 0;
        mpdState = MPD_READ_CURRENTSONG;
        break;

    case MPD_READ_CURRENTSONG:
        if (readAvailable()) {
            // 收到完整 currentsong 响应，立即解析
            parseSongResponse(mpd_buf);
            mpdState = MPD_PARSE;
        } else if (millis() - mpdStateStart > MPD_TIMEOUT_MS) {
            mpdState = MPD_IDLE;
        }
        break;

    case MPD_PARSE:
        // 所有数据已解析完毕，更新时间戳并刷新 UI
        lastSyncTime = millis();
        baseElapsed = state.elapsed;
        update_ui_values();
        mpdState = MPD_IDLE;
        break;
    }
}

// ============================================================
//  UI：将 state 写入控件（脏检查）
// ============================================================
static void update_ui_values() {
    const char* icon;
    lv_color_t icolor;
    if (state.status == STATUS_PLAYING) {
        icon = "";
        icolor = lv_color_hex(0x00CED1); // 播放用电子深青
    } else if (state.status == STATUS_PAUSED) {
        icon = "⏸";
        icolor = lv_color_hex(0x708090); // 暂停用铓锣灰
    } else {
        icon = "☹";
        icolor = lv_color_hex(0xA52A2A); // 停止用暗红
    }
    label_set_if_changed(label_status, icon);
    lv_obj_set_style_text_color(label_status, icolor, 0);

    char flags[16];
    int fi = 0;
    flags[fi++] = '[';
    if (state.repeat)    flags[fi++] = 'r';
    if (state.random)    flags[fi++] = 'z';
    if (state.single)    flags[fi++] = 's';
    if (state.consume)   flags[fi++] = 'c';
    if (state.crossfade) flags[fi++] = 'x';
    flags[fi++] = ']';
    flags[fi] = '\0';
    label_set_if_changed(label_flags, flags);

    char vol_buf[12];
    snprintf(vol_buf, sizeof(vol_buf), "V:%s%%", state.vol);
    label_set_if_changed(label_vol, vol_buf);

    scroll_label_set_text(label_title,   state.title);
    scroll_label_set_text(label_artist,  state.artist);
    scroll_label_set_text(label_album,   state.album);
    label_set_if_changed(label_time_to, formatTime((int)state.duration));
}

// ============================================================
//  setup
// ============================================================
void setup() {
    Serial.begin(115200);

    // 按键初始化（内部上拉，按下读 LOW）
    pinMode(BTN_PIN, INPUT_PULLUP);
 
    // LVGL 初始化
    initDisplay();
    lv_init();
    lv_disp_draw_buf_init(&draw_buf, lv_buf, nullptr, SCREEN_W * SCREEN_H);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res  = SCREEN_W;
    disp_drv.ver_res  = SCREEN_H;
    disp_drv.flush_cb = disp_flush_cb;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    setup_ui();

    lv_label_set_text(label_status, "✈"); // ✈ 未联网
    lv_timer_handler();

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    unsigned long wifiStart = millis();
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - wifiStart > WIFI_TIMEOUT_MS) {
            lv_obj_set_style_text_color(label_status, lv_color_hex(0xA52A2A), 0);
            lv_label_set_text(label_status, "✈"); // ✈ 联网失败
            lv_timer_handler();
            break;
        }
        lv_timer_handler();
        delay(100);
    }
    if (WiFi.status() == WL_CONNECTED) {
        lv_obj_set_style_text_color(label_status, lv_color_hex(0xFFB000), 0);
        lv_label_set_text(label_status, "OK"); // 已联网
        lv_timer_handler();
    }
}

// ============================================================
//  loop
// ============================================================
void loop() {
    static unsigned long last_mpd_check      = 0;
    static unsigned long last_subinfo_switch = 0;
    static bool          showing_artist      = true;
    static int           last_displayed_sec  = -1;

    // ---- 按键检测（软件消抖） ----
    {
        static bool     last_raw        = HIGH;
        static bool     confirmed_state = HIGH;
        static uint32_t debounce_start  = 0;
        static uint32_t last_trigger    = 0;
        static bool     startup_guard   = true; // 上电后屏蔽 1 秒，等电平稳定

        if (startup_guard) {
            if (millis() >= 1000) {
                startup_guard   = false;
                last_raw        = digitalRead(BTN_PIN);
                confirmed_state = last_raw;
            }
        } else {
            bool raw = digitalRead(BTN_PIN);

            if (raw != last_raw) {
                debounce_start = millis();
                last_raw = raw;
            }
            if ((millis() - debounce_start) >= BTN_DEBOUNCE_MS && raw != confirmed_state) {
                confirmed_state = raw;
                if (confirmed_state == LOW) {  // 下降沿 = 按下
                    if (millis() - last_trigger >= BTN_COOLDOWN_MS) {
                        last_trigger = millis();
                        sendMpdNext();
                    }
                }
            }
        }
    }

    // ---- 非阻塞 MPD 状态机 ----
    // 如果状态机正在运行（非 IDLE），持续推进它
    if (mpdState != MPD_IDLE) {
        mpdStateMachine();
    }
    // 如果状态机空闲且距上次同步超过间隔，启动新一轮
    if (mpdState == MPD_IDLE && millis() - last_mpd_check > MPD_INTERVAL_MS) {
        mpdState = MPD_SEND_STATUS;
        last_mpd_check = millis();
        mpdStateMachine(); // 立即执行第一步
    }

    // 每 7 秒翻页：艺术家 ↔ 专辑
    if (millis() - last_subinfo_switch > FLIP_INTERVAL_MS) {
        showing_artist = !showing_artist;
        lv_obj_scroll_to_y(cont_subinfo, showing_artist ? 0 : 20, LV_ANIM_ON);
        last_subinfo_switch = millis();
    }

    // 进度补帧（不依赖 MPD 轮询频率）
    float simElapsed = baseElapsed;
    if (state.status == STATUS_PLAYING) {
        simElapsed += (millis() - lastSyncTime) / 1000.0f;
    }
    if (state.duration > 0 && simElapsed > state.duration) {
        simElapsed = state.duration;
    }

    // 只在整秒跳变时更新时间标签和进度条，减少无效重绘
    int nowSec = (int)simElapsed;
    if (nowSec != last_displayed_sec) {
        last_displayed_sec = nowSec;
        label_set_if_changed(label_time_el, formatTime(nowSec));
        int pct = (state.duration > 0)
                  ? (int)((simElapsed / state.duration) * 100.0f)
                  : 0;
        lv_bar_set_value(bar_progress, pct, LV_ANIM_ON);
    }

    lv_timer_handler();
    scroll_labels_update_speeds(); // 文本变化后下一帧重算自适应速度
    delay(5);
}
