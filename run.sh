#!/bin/bash

# 获取当前脚本所在目录
SCRIPT_DIR=$(dirname "$(realpath "$0")")
# 从当前目录开始，向上查找直到找到 CMakeLists.txt 文件，确定项目根目录
PROJECT_DIR=$SCRIPT_DIR
while [ ! -f "$PROJECT_DIR/CMakeLists.txt" ]; do
    PROJECT_DIR=$(dirname "$PROJECT_DIR")
done
# 获取项目根目录名
PROJECT_NAME=$(basename "$PROJECT_DIR")
echo "Project root directory name: $PROJECT_NAME"
# 创建并进入构建目录
BUILD_DIR="$PROJECT_DIR/build"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
# 运行 CMake 配置和编译项目
cmake ..
make -j 16
# 根据项目名称生成 ELF、BIN 和 HEX 文件路径
ELF_FILE="$BUILD_DIR/${PROJECT_NAME}.elf"
BIN_FILE="$BUILD_DIR/${PROJECT_NAME}.bin"
HEX_FILE="$BUILD_DIR/${PROJECT_NAME}.hex"
# 检查 ELF 文件是否生成成功
if [ -f "$ELF_FILE" ]; then
# 将ELF 文件接換力 BIN 文件和 HEX 文件
    arm-none-eabi-objcopy -O binary "$ELF_FILE" "$BIN_FILE" 
    arm-none-eabi-objcopy -O ihex "$ELF_FILE" "$HEX_FILE"
    echo "Conversion to BIN and HEX completed."
else
    echo "Error: ELF file not found. Compilation might have failed."
    exit 1
fi
# 执行 OpenOCD 进行烧录
openocd -f "$PROJECT_DIR/flash.cfg"
# uncomment this could support downloading code to flash