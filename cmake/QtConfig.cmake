# ============================================
# Qt 路径配置辅助文件
# ============================================
# 此文件帮助 CMake 找到 Qt 安装路径
# 
# 使用方法：
# 1. 找到你的 Qt 安装路径
# 2. 取消注释下面对应的路径配置
# 3. 修改为你的实际路径

# ============================================
# Windows Qt6 常见路径
# ============================================
# MSVC 编译器
# set(CMAKE_PREFIX_PATH "C:/Qt/6.5.0/msvc2019_64")
# set(CMAKE_PREFIX_PATH "C:/Qt/6.6.0/msvc2019_64")
# set(CMAKE_PREFIX_PATH "C:/Qt/6.7.0/msvc2022_64")

# MinGW 编译器
# set(CMAKE_PREFIX_PATH "C:/Qt/6.5.0/mingw_64")
# set(CMAKE_PREFIX_PATH "C:/Qt/6.6.0/mingw_64")
# set(CMAKE_PREFIX_PATH "C:/Qt/6.7.0/mingw_64")

# ============================================
# Windows Qt5 常见路径
# ============================================
# set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019_64")
# set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64")

# ============================================
# Linux Qt 常见路径
# ============================================
# set(CMAKE_PREFIX_PATH "/opt/Qt/6.5.0/gcc_64")
# set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake")

# ============================================
# macOS Qt 常见路径
# ============================================
# set(CMAKE_PREFIX_PATH "/Users/$USER/Qt/6.5.0/macos")
# set(CMAKE_PREFIX_PATH "/usr/local/Qt/6.5.0/clang_64")

# ============================================
# 或者使用环境变量（推荐）
# ============================================
# 在系统环境变量中设置：
# Windows: setx CMAKE_PREFIX_PATH "C:/Qt/6.5.0/mingw_64"
# Linux/macOS: export CMAKE_PREFIX_PATH=/path/to/qt

# 如果设置了环境变量，CMake 会自动使用
if(DEFINED ENV{CMAKE_PREFIX_PATH})
    message(STATUS "使用环境变量中的 Qt 路径: $ENV{CMAKE_PREFIX_PATH}")
endif()
