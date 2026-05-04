# ESP32-C3 与 ST7735S 显示屏项目

此项目旨在使用ESP32-C3开发板和bodmer/TFT_eSPI库驱动ST7735S显示屏。

## 配置信息

- **开发板**: ESP32-C3 (合宙开发板)
- **显示屏**: ST7735S 0.96寸 80x160分辨率
- **库**: bodmer/TFT_eSPI

### 引脚连接

由于ST7735S屏幕上的标识可能与实际功能不同，请注意：

| 屏幕标识 | 实际功能 | ESP32-C3引脚 |
|----------|----------|---------------|
| VCC      | 电源正极 | 3.3V          |
| GND      | 电源负极 | GND           |
| SCL      | SPI时钟  | GPIO6         |
| SDA      | SPI数据  | GPIO7         |
| CS       | 片选     | GPIO10        |
| DC       | 数据/命令| GPIO2         |
| RST      | 复位     | GPIO3         |

## 构建环境

### 主环境
- `esp32-c3-devkitm-1` - 使用TFT_eSPI库的主要环境

### 辅助环境
- `simple-st7735-test` - 使用较低SPI频率的简化测试环境
- `esp32-c3-i2c-test` - I2C设备扫描测试

## 使用方法

要上传主程序到ESP32-C3：
```
pio run -e esp32-c3-devkitm-1 --target upload
```

## 故障排除

如果显示屏出现问题，请参阅以下文档：
- `troubleshooting_detailed.md` - 详细的故障排除指南
- `serial_monitor_guide.md` - 如何查看串口输出