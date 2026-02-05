#!/bin/bash
# ============================================
# LiquidCam 项目编译脚本 (Linux/macOS)
# ============================================
# 用途：快速编译项目
# 使用: ./build.sh [Debug|Release] [clean]
#
# Qt版本切换：
#   修改根目录 CMakeLists.txt 中的 QT_VERSION_MAJOR
#   "6": 使用Qt6（默认）
#   "5": 使用Qt5（兼容老机器）

# 设置默认构建类型
BUILD_TYPE="Debug"
CLEAN_BUILD=false

# 解析命令行参数
while [[ $# -gt 0 ]]; do
    case "$1" in
        clean)
            CLEAN_BUILD=true
            shift
            ;;
        Debug|Release)
            BUILD_TYPE="$1"
            shift
            ;;
        *)
            shift
            ;;
    esac
done

echo "========================================"
echo "LiquidCam 项目编译脚本"
echo "========================================"
echo "构建类型: $BUILD_TYPE"
echo "========================================"

# 创建构建目录
mkdir -p build
cd build

# 清理构建（如果需要）
if [ "$CLEAN_BUILD" = true ]; then
    echo "清理旧的构建文件..."
    rm -rf *
    cd ..
    mkdir -p build
    cd build
fi

# 生成CMake项目
echo "正在配置CMake..."
cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE

if [ $? -ne 0 ]; then
    echo "[错误] CMake配置失败！"
    exit 1
fi

# 编译项目
echo "正在编译项目..."
make -j$(nproc)

if [ $? -ne 0 ]; then
    echo "[错误] 编译失败！"
    exit 1
fi

echo "========================================"
echo "编译成功！"
echo "可执行文件位置: bin/LiquidCam"
echo "========================================"

# 运行程序（可选）
# echo "正在运行程序..."
# ./bin/LiquidCam
