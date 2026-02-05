@echo off
REM ============================================
REM LiquidCam 项目编译脚本 (Windows)
REM ============================================
REM 用途：快速编译项目
REM 使用：build.bat [Debug|Release] [clean]
REM
REM Qt版本切换：
REM   修改根目录 CMakeLists.txt 中的 QT_VERSION_MAJOR
REM   "6": 使用Qt6（默认）
REM   "5": 使用Qt5（兼容老机器）

setlocal

REM 设置默认构建类型
set BUILD_TYPE=Debug

REM 解析命令行参数
if "%1"=="clean" goto clean
if "%1"=="Debug" set BUILD_TYPE=Debug
if "%1"=="Release" set BUILD_TYPE=Release
if "%2"=="clean" set CLEAN_BUILD=true

echo ========================================
echo LiquidCam 项目编译脚本
echo ========================================
echo 构建类型: %BUILD_TYPE%
echo ========================================

REM 创建构建目录
if not exist build mkdir build
cd build

REM 清理构建（如果需要）
if "%CLEAN_BUILD%"=="true" (
    echo 清理旧的构建文件...
    del /Q /S * 2>nul
    cd ..
    rmdir /S /Q build
    mkdir build
    cd build
)

REM 生成CMake项目
echo 正在配置CMake...
cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=%BUILD_TYPE%

if errorlevel 1 (
    echo [错误] CMake配置失败！
    pause
    exit /b 1
)

REM 编译项目
echo 正在编译项目...
cmake --build . --config %BUILD_TYPE%

if errorlevel 1 (
    echo [错误] 编译失败！
    pause
    exit /b 1
)

echo ========================================
echo 编译成功！
echo 可执行文件位置: bin\LiquidCam.exe
echo ========================================
pause

:clean
echo 正在清理构建文件...
if exist build (
    cd build
    del /Q /S * 2>nul
    cd ..
    rmdir /S /Q build
)
echo 清理完成！
pause
