cmake_minimum_required(VERSION 3.16)
project(LiquidCam VERSION 1.0.0 LANGUAGES CXX)

# ============================================
# 编译说明
# ============================================
# Windows:
#   cd build && cmake .. && cmake --build .
#
# MSVC (推荐):
#   cmake .. -G "Visual Studio 17 2022" -A x64
#   cmake --build . --config Release
#
# 或者手动指定 Qt 路径:
#   cmake .. -DCMAKE_PREFIX_PATH="C:/Qt/6.x.x/msvc2019_64"
# ============================================

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 自动处理 Qt 的 MOC、UIC 和 RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 设置构建输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ============================================
# MSVC 特定设置
# ============================================
if(MSVC)
    set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)
    set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/pdb)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    message(STATUS "使用 MSVC 编译器")
elseif(MINGW)
    message(STATUS "使用 MinGW 编译器")
else()
    message(STATUS "使用其他编译器")
endif()

# ============================================
# Qt 自动查找
# ============================================
if(NOT CMAKE_PREFIX_PATH)
    # 首先尝试从环境变量获取
    if(DEFINED ENV{Qt6_DIR})
        get_filename_component(QT_PARENT_DIR "$ENV{Qt6_DIR}" DIRECTORY)
        get_filename_component(QT_PARENT_DIR "${QT_PARENT_DIR}" DIRECTORY)
        list(APPEND CMAKE_PREFIX_PATH "${QT_PARENT_DIR}")
        message(STATUS "从 Qt6_DIR 获取 Qt 路径: ${QT_PARENT_DIR}")
    elseif(DEFINED ENV{QT_DIR})
        list(APPEND CMAKE_PREFIX_PATH $ENV{QT_DIR})
        message(STATUS "从 QT_DIR 获取 Qt 路径: $ENV{QT_DIR}")
    elseif(DEFINED ENV{Qt5_DIR})
        get_filename_component(QT_PARENT_DIR "$ENV{Qt5_DIR}" DIRECTORY)
        get_filename_component(QT_PARENT_DIR "${QT_PARENT_DIR}" DIRECTORY)
        list(APPEND CMAKE_PREFIX_PATH "${QT_PARENT_DIR}")
        message(STATUS "从 Qt5_DIR 获取 Qt 路径: ${QT_PARENT_DIR}")
    else()
        # 根据编译器自动查找 Qt 路径
        if(MSVC)
            set(QT_SEARCH_PATHS
                "C:/Qt/6.10.2/msvc2019_64"
                "C:/Qt/6.10.2/msvc2022_64"
                "C:/Qt/6.9.0/msvc2019_64"
                "C:/Qt/6.9.0/msvc2022_64"
                "C:/Qt/6.8.0/msvc2019_64"
                "C:/Qt/6.8.0/msvc2022_64"
                "C:/Qt/6.7.0/msvc2019_64"
                "C:/Qt/6.7.0/msvc2022_64"
                "D:/Qt/6.10.2/msvc2019_64"
                "D:/Qt/6.10.2/msvc2022_64"
                "D:/Qt/6.9.0/msvc2019_64"
                "D:/Qt/6.9.0/msvc2022_64"
                "D:/APP/STUDY/QT/6.10.2/msvc2019_64"
                "D:/APP/STUDY/QT/6.10.2/msvc2022_64"
            )
        else()
            # MinGW 路径
            set(QT_SEARCH_PATHS
                "C:/Qt/6.10.2/mingw_64"
                "C:/Qt/6.9.0/mingw_64"
                "C:/Qt/6.8.0/mingw_64"
                "D:/Qt/6.10.2/mingw_64"
                "D:/APP/STUDY/QT/6.10.2/mingw_64"
                "D:/APP/STUDY/QT/6.9.0/mingw_64"
            )
        endif()
        
        foreach(QT_PATH ${QT_SEARCH_PATHS})
            if(EXISTS "${QT_PATH}/lib/cmake/Qt6Core/Qt6CoreConfig.cmake")
                list(APPEND CMAKE_PREFIX_PATH ${QT_PATH})
                message(STATUS "自动找到 Qt6 路径: ${QT_PATH}")
                break()
            elseif(EXISTS "${QT_PATH}/lib/cmake/Qt5Core/Qt5CoreConfig.cmake")
                list(APPEND CMAKE_PREFIX_PATH ${QT_PATH})
                message(STATUS "自动找到 Qt5 路径: ${QT_PATH}")
                break()
            endif()
        endforeach()
    endif()
endif()

# 查找 Qt
find_package(Qt6 COMPONENTS Core Widgets Gui QUIET)
if(Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
    set(QT_TARGET_PREFIX Qt6)
    find_package(Qt6 COMPONENTS Core Widgets Gui REQUIRED)
else()
    find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
    set(QT_VERSION_MAJOR 5)
    set(QT_TARGET_PREFIX Qt5)
endif()

message(STATUS "========================================")
message(STATUS "LiquidCam 配置")
message(STATUS "========================================")
message(STATUS "Qt 版本: ${QT_VERSION_MAJOR}")
message(STATUS "Qt 路径: ${${QT_TARGET_PREFIX}Core_DIR}")

# ============================================
# 全局包含目录
# ============================================
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/mainui/include
    ${CMAKE_SOURCE_DIR}/src/secondui/include
    ${CMAKE_SOURCE_DIR}/src/dashboard/include
    ${CMAKE_SOURCE_DIR}/src/settings/include
)

# ============================================
# 添加子模块
# ============================================
add_subdirectory(src/mainui)
add_subdirectory(src/secondui)
add_subdirectory(src/dashboard)
add_subdirectory(src/settings)

# ============================================
# 构建可执行文件
# ============================================
set(MAIN_SOURCES main.cpp)

add_executable(${PROJECT_NAME}
    ${MAIN_SOURCES}
    $<TARGET_OBJECTS:mainui_objects>
    $<TARGET_OBJECTS:secondui_objects>
    $<TARGET_OBJECTS:settings_objects>
    $<TARGET_OBJECTS:dashboard_objects>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${QT_TARGET_PREFIX}::Core
        ${QT_TARGET_PREFIX}::Widgets
        ${QT_TARGET_PREFIX}::Gui
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_BINARY_DIR}/src/mainui/mainui_autogen/include
        ${CMAKE_BINARY_DIR}/src/secondui/secondui_autogen/include
        ${CMAKE_BINARY_DIR}/src/dashboard/dashboard_objects_autogen/include
        ${CMAKE_BINARY_DIR}/src/settings/settings_objects_autogen/include
        ${secondui_INCLUDE_DIR}
        ${settings_INCLUDE_DIR}
        ${dashboard_INCLUDE_DIR}
)

# ============================================
# Qt DLL 自动部署
# ============================================
include(cmake/DeployQt.cmake)
deploy_qt_dlls(${PROJECT_NAME})

# ============================================
# 完成信息
# ============================================
message(STATUS "")
message(STATUS "配置完成！使用以下命令编译：")
message(STATUS "  cmake --build build")
message(STATUS "")
