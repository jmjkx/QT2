# ============================================
# Qt 自动查找模块
# ============================================
# 优先顺序：
# 1. 环境变量 QT_DIR
# 2. 命令行参数 -DQT_DIR=xxx
# 3. 自动查找常见安装路径
# 4. 使用硬编码路径作为后备

# 硬编码的 Qt 路径（作为后备）- 优先使用 MinGW
set(QT_FALLBACK_PATH "D:/APP/STUDY/QT/6.10.2/mingw_64")

# 常见 Qt 安装路径列表（包含 MinGW 和 MSVC）
set(QT_COMMON_PATHS
    "D:/APP/STUDY/QT/6.10.2/mingw_64"
    "C:/Qt/6.10.2/mingw_64"
    "C:/Qt/6.8.0/mingw_64"
    "C:/Qt/6.5.3/mingw_64"
    "C:/Qt/6.2.4/mingw_64"
    "D:/Qt/6.10.2/mingw_64"
    "C:/Qt/6.10.2/msvc2022_64"
    "C:/Qt/6.8.0/msvc2022_64"
    "D:/APP/STUDY/QT/6.10.2/msvc2022_64"
)

# 函数：检查路径是否包含有效的 Qt
function(check_qt_path qt_path result)
    if(EXISTS "${qt_path}/bin/qmake.exe" OR EXISTS "${qt_path}/bin/Qt6Core.dll" OR EXISTS "${qt_path}/lib/Qt6Core.lib")
        set(${result} TRUE PARENT_SCOPE)
    else()
        set(${result} FALSE PARENT_SCOPE)
    endif()
endfunction()

# 尝试从环境变量获取 Qt 路径
if(DEFINED ENV{QT_DIR} AND NOT DEFINED QT_DIR)
    set(QT_DIR $ENV{QT_DIR})
    message(STATUS "从环境变量 QT_DIR 获取 Qt 路径: ${QT_DIR}")
endif()

# 检查命令行参数或环境变量指定的 Qt 路径
if(DEFINED QT_DIR)
    check_qt_path(${QT_DIR} QT_VALID)
    if(QT_VALID)
        set(CMAKE_PREFIX_PATH ${QT_DIR})
        message(STATUS "使用指定的 Qt 路径: ${QT_DIR}")
    else()
        message(WARNING "指定的 Qt 路径无效: ${QT_DIR}")
    endif()
endif()

# 如果还没找到 Qt，尝试自动查找
if(NOT DEFINED CMAKE_PREFIX_PATH OR CMAKE_PREFIX_PATH STREQUAL "")
    message(STATUS "正在自动查找 Qt...")
    set(QT_FOUND FALSE)
    
    foreach(qt_path ${QT_COMMON_PATHS})
        check_qt_path(${qt_path} QT_VALID)
        if(QT_VALID)
            set(CMAKE_PREFIX_PATH ${qt_path})
            set(QT_FOUND TRUE)
            message(STATUS "自动找到 Qt: ${qt_path}")
            break()
        endif()
    endforeach()
    
    # 如果还没找到，使用硬编码路径
    if(NOT QT_FOUND)
        set(CMAKE_PREFIX_PATH ${QT_FALLBACK_PATH})
        message(STATUS "使用硬编码的 Qt 路径: ${QT_FALLBACK_PATH}")
    endif()
endif()

message(STATUS "最终 Qt 路径: ${CMAKE_PREFIX_PATH}")
