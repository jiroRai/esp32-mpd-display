// User_Setup.h — TFT_eSPI 配置
// 0.96寸 ST7735S 80×160 IPS，横向使用
// ESP32-C3 硬件 SPI (FSPI) 自定义引脚

#define ST7735_DRIVER

// 屏幕尺寸（竖屏/原生方向）
// ST7735_Defines.h 注释: "defined in portrait mode"
// 0.96寸 80×160 IPS，原生竖屏 80×160
// setRotation(1) 后自动交换为 160×80 横屏
#define TFT_WIDTH  80
#define TFT_HEIGHT 160

// ST7735 初始化参数
// 0.96寸 80×160 IPS 屏幕使用 GREENTAB160x80
// colstart=26, rowstart=1，匹配 Adafruit 的 setColRowStart(26,1)
#define ST7735_GREENTAB160x80

// 自定义引脚（ESP32-C3 FSPI 硬件 SPI）
#define TFT_CS   7
#define TFT_DC   6
#define TFT_RST  10
#define TFT_MOSI 3
#define TFT_SCLK 2

// SPI 频率（10MHz，兼容性更好，部分 ST7735S 克隆屏在 27MHz 下黑屏）
#define SPI_FREQUENCY  10000000

// 不使用 USE_HSPI_PORT 或 USE_FSPI_PORT
// ESP32-C3 上 HSPI = FSPI = SPI2_HOST，只有一个 SPI 控制器
// 默认使用 SPIClass& spi = SPI（全局 SPI 引用），由 Arduino 核心初始化
// 这避免了创建新的 SPIClass 实例可能导致的初始化问题
//#define USE_HSPI_PORT
//#define USE_FSPI_PORT

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
