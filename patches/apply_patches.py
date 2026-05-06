"""
PlatformIO extra_scripts: 在库下载后自动应用必要的补丁。
在 platformio.ini 中通过 extra_scripts = patches/apply_patches.py 启用。

补丁列表：
  1. TFT_eSPI_ESP32_C3.h: SPI_PORT SPI2_HOST → 2
     (REG_SPI_BASE(i) 要求 i==2 才返回 DR_REG_SPI2_BASE，但 SPI2_HOST=1)
  2. TFT_eSPI.cpp: 删除 begin_tft_write() 之前的 writecommand(0x00)
     (SPI 事务尚未开始就调用 writecommand 会导致崩溃)
"""

import os
import sys

Import("env")

def apply_patches(source, target, env):
    # 获取库目录
    libdeps_dir = env.subst("$PROJECT_LIBDEPS_DIR")
    # 获取当前环境名称
    env_name = env.subst("$PIOENV")
    
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
            print(f"[PATCH] Fixed SPI_PORT in {c3_header}")
        else:
            print(f"[PATCH] SPI_PORT already fixed or not found in {c3_header}")
    else:
        print(f"[PATCH] Warning: {c3_header} not found")
    
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
            print(f"[PATCH] Removed writecommand(0x00) before begin_tft_write() in {tft_cpp}")
        else:
            print(f"[PATCH] writecommand(0x00) already removed or not found in {tft_cpp}")
    else:
        print(f"[PATCH] Warning: {tft_cpp} not found")

# 在构建之前应用补丁（此时库已下载）
env.AddPreAction("buildprog", apply_patches)
