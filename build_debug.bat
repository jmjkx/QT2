@echo off
echo ============================================
echo  LiquidCam Build Script (Debug)
echo ============================================
echo.

set "PROJECT_ROOT=%~dp0"
set "BUILD_DIR=%PROJECT_ROOT%build"

if not exist "%BUILD_DIR%" (
    echo Creating build directory: %BUILD_DIR%
    mkdir "%BUILD_DIR%"
)

cd /d "%BUILD_DIR%"

echo.
echo [1/2] Configuring project...
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Debug
if errorlevel 1 (
    echo Configure failed!
    pause
    exit /b 1
)

echo.
echo [2/2] Building Debug...
cmake --build . --parallel
if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo ============================================
echo  Build Success!
echo  Output: %BUILD_DIR%\bin
echo ============================================
pause
