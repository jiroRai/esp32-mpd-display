"""
PlatformIO extra_scripts: 在库下载后自动应用必要的补丁。
在 platformio.ini 中通过 extra_scripts = patches/apply_patches.py 启用。

补丁列表：
  1. TFT_eSPI_ESP32_C3.h: SPI_PORT SPI2_HOST → 2
     (REG_SPI_BASE(i) 要求 i==2 才返回 DR_REG_SPI2_BASE，但 SPI2_HOST=1)
  2. TFT_eSPI.cpp: 删除 begin_tft_write() 之前的 writecommand(0x00)
     (SPI 事务尚未开始就调用 writecommand 会导致崩溃)
  3. User_Setup.h: 覆盖为 ST7735 自定义配置
     (PlatformIO 优先搜索 libdeps 目录下的头文件，默认是 ILI9341 配置)
"""

import os
import sys

Import("env")

def apply_patches(source, target, env):
    # 获取库目录
    libdeps_dir = env.subst("$PROJECT_LIBDEPS_DIR")
    # 获取当前环境名称
    env_name = env.subst("$PIOENV")
    
    print(f"[PATCH] Applying patches for env: {env_name}")
    print(f"[PATCH] Libdeps dir: {libdeps_dir}")
    
    # 补丁 1: TFT_eSPI_ESP32_C3.h - SPI_PORT
    c3_header = os.path.join(libdeps_dir, env_name, "TFT_eSPI", "Processors", "TFT_eSPI_ESP32_C3.h")
    if os.path.exists(c3_header):
        with open(c3_header, "r", encoding="utf-8") as f:
            content = f.read()
        
        old = "#define SPI_PORT SPI2_HOST"
        new = "#define SPI_PORT 2 // FIXED: SPI2_HOST=1 but REG_SPI_BASE(i) needs i==2"
        if old in content:
            content = content.replace(old, new)
            with open(c3_header, "w", encoding="utf-8") as f:
                f.write(content)
            print(f"[PATCH] ✓ Fixed SPI_PORT in {c3_header}")
        else:
            print(f"[PATCH] - SPI_PORT already fixed or not found in {c3_header}")
    else:
        print(f"[PATCH] ⚠ Warning: {c3_header} not found")
    
    # 补丁 2: TFT_eSPI.cpp - 删除 begin_tft_write() 之前的 writecommand(0x00)
    tft_cpp = os.path.join(libdeps_dir, env_name, "TFT_eSPI", "TFT_eSPI.cpp")
    if os.path.exists(tft_cpp):
        with open(tft_cpp, "r", encoding="utf-8") as f:
            content = f.read()
        
        old_line = "    writecommand(0x00); // Put SPI bus in known state for TFT with CS tied low\n"
        if old_line in content:
            content = content.replace(old_line, "")
            with open(tft_cpp, "w", encoding="utf-8") as f:
                f.write(content)
            print(f"[PATCH] ✓ Removed writecommand(0x00) before begin_tft_write() in {tft_cpp}")
        else:
            print(f"[PATCH] - writecommand(0x00) already removed or not found in {tft_cpp}")
    else:
        print(f"[PATCH] ⚠ Warning: {tft_cpp} not found")
    
    # 补丁 3: User_Setup.h - 覆盖为 ST7735 自定义配置
    user_setup = os.path.join(libdeps_dir, env_name, "TFT_eSPI", "User_Setup.h")
    if os.path.exists(user_setup):
        with open(user_setup, "r", encoding="utf-8") as f:
            content = f.read()
        
        # 检查是否已经是我们的自定义配置（通过检查 ST7735_DRIVER 是否已启用）
        if "#define ST7735_DRIVER" in content and "TFT_CS   7" in content:
            print(f"[PATCH] - User_Setup.h already has ST7735 config")
        else:
            # 写入自定义配置
            custom_config = """// User_Setup.h — TFT_eSPI 配置 (PATCHED by apply_patches.py)
// 0.96寸 ST7735S 80×160 IPS，横向使用
// ESP32-C3 硬件 SPI (FSPI) 自定义引脚

#define ST7735_DRIVER

// 屏幕尺寸（竖屏/原生方向）
#define TFT_WIDTH  80
#define TFT_HEIGHT 160

// ST7735 初始化参数
#define ST7735_GREENTAB160x80

// 自定义引脚（ESP32-C3 FSPI 硬件 SPI）
#define TFT_CS   7
#define TFT_DC   6
#define TFT_RST  10
#define TFT_MOSI 3
#define TFT_SCLK 2

// SPI 频率（10MHz）
#define SPI_FREQUENCY  10000000

// 字体
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT

// SPI 读取（不需要）
#define SPI_READ_FREQUENCY  0
#define SPI_TOUCH_FREQUENCY 0
"""
            with open(user_setup, "w", encoding="utf-8") as f:
                f.write(custom_config)
            print(f"[PATCH] ✓ Overwritten User_Setup.h with ST7735 config in {user_setup}")
    else:
        print(f"[PATCH] ⚠ Warning: {user_setup} not found")

# 使用多个钩子确保补丁被应用
# 1. 在构建之前应用补丁（此时库已下载）
env.AddPreAction("buildprog", apply_patches)
# 2. 也绑定到 compiling 动作，以防 buildprog 不触发
env.AddPreAction("$BUILD_DIR/src/main.cpp.o", apply_patches)
