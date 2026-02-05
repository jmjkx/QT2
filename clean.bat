@echo off
echo ========================================
echo 清理LiquidCam项目
echo ========================================

if exist build (
    echo 正在删除build目录...
    rmdir /S /Q build
    echo 清理完成！
) else (
    echo build目录不存在，无需清理
)

pause
