cmake_minimum_required(VERSION 3.16)
project(LiquidCam VERSION 1.0.0 LANGUAGES CXX)

# ============================================
# 编译选项配置
# ============================================

# 静态库选项：默认开启（用于静态链接Qt）
# 关闭此选项时将直接编译源文件到可执行文件（避免Qt5 LGPL版权问题）
option(BUILD_STATIC_LIBS "Build as static libraries (default: ON). Set to OFF to avoid Qt5 LGPL license issues." OFF)

# ============================================
# CMake全局配置
# ============================================

# 设置C++标准（兼容Qt5，使用C++11）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 自动处理Qt的MOC、UIC和RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 设置构建输出目录（所有编译产物都放在build文件夹下）
# CMAKE_BINARY_DIR 指向构建目录（通常是 ./build）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)    # 可执行文件 -> build/bin/
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)    # 动态库 -> build/lib/
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   # 静态库 -> build/lib/

# 多核编译加速
if(NOT DEFINED CMAKE_JOB_POOLS)
    set(CMAKE_JOB_POOLS link=1)
    set(CMAKE_JOB_POOL_LINK link)
endif()

# ============================================
# Qt版本配置 - 兼容Qt5和Qt6
# ============================================

# 定义要使用的Qt版本（修改此处可切换Qt版本）
# 默认使用Qt6，改为 "5" 可切换到Qt5
set(QT_VERSION_MAJOR "6")

# 查找Qt包（自动适配Qt5或Qt6）
if(${QT_VERSION_MAJOR} EQUAL 6)
    # 使用Qt6
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
    set(QT_TARGET_PREFIX "Qt6")
else()
    # 使用Qt5
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)
    set(QT_TARGET_PREFIX "Qt5")
endif()

# 打印使用的Qt版本信息
message(STATUS "使用Qt${QT_VERSION_MAJOR}进行编译")

# ============================================
# 全局包含目录
# ============================================

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/3rd/include
    ${CMAKE_SOURCE_DIR}/src/mainui/include
    ${CMAKE_SOURCE_DIR}/src/secondui/include
)

# ============================================
# 添加子模块
# ============================================

# 始终创建INTERFACE库来处理MOC/UIC和源文件组织
add_subdirectory(src/mainui)
add_subdirectory(src/secondui)

if(BUILD_STATIC_LIBS)
    message(STATUS "编译模式: 静态库模式")
else()
    message(STATUS "编译模式: 直接编译模式 (避免Qt5版权问题)")
endif()

# ============================================
# 构建可执行文件
# ============================================

# 主程序源文件
set(MAIN_SOURCES
    main.cpp
)

if(BUILD_STATIC_LIBS)
    # 静态库模式：链接静态库
    add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            mainui
            secondui
            ${QT_TARGET_PREFIX}::Core
            ${QT_TARGET_PREFIX}::Widgets
            ${QT_TARGET_PREFIX}::Gui
    )
else()
    # 直接编译模式：创建包含所有源文件的可执行文件
    # 使用INTERFACE库获取源文件，确保MOC/UIC正确处理
    add_executable(${PROJECT_NAME}
        ${MAIN_SOURCES}
        $<TARGET_OBJECTS:mainui_objects>
        $<TARGET_OBJECTS:secondui_objects>
    )

    # 直接链接Qt库
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            ${QT_TARGET_PREFIX}::Core
            ${QT_TARGET_PREFIX}::Widgets
            ${QT_TARGET_PREFIX}::Gui
    )

    # 链接INTERFACE库以获取头文件路径和编译选项
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            ${MAINUI_INTERFACE}
            ${SECONDCONTROLLER_INTERFACE}
    )
endif()

# 为主程序设置包含目录（用于main.cpp）
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src/mainui/include
        ${CMAKE_SOURCE_DIR}/src/mainui/src
        ${CMAKE_SOURCE_DIR}/src/mainui/biz
        ${CMAKE_SOURCE_DIR}/src/secondui/include
        ${CMAKE_SOURCE_DIR}/src/secondui/src
        ${CMAKE_SOURCE_DIR}/src/secondui/biz
)

# 设置可执行文件属性
set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

# Windows平台：设置为Windows子系统（不显示控制台）
if(WIN32)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME} PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
        )
    endif()
endif()

# ============================================
# 资源文件配置
# ============================================

# 添加全局资源目录（可选）
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resource)

# ============================================
# 安装配置（可选，用于部署）
# ============================================

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
