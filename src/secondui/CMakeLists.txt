# ============================================
# SecondUI模块 - CMake配置文件
# ============================================
# 本模块负责次级界面的实现，包含UI、业务逻辑和资源管理

cmake_minimum_required(VERSION 3.16)

# 定义当前模块名称
set(MODULE_NAME secondui)

# ============================================
# 源文件定义
# ============================================

# 模块源文件（所有.cpp文件）
set(MODULE_SOURCES
    src/SecondWindow.cpp
    biz/SecondController.cpp
)

# 模块头文件（所有.h文件）
set(MODULE_HEADERS
    include/SecondWindow.h
    include/SecondController.h
)

# UI文件（所有.ui文件，如果有）
set(MODULE_UIS
    ui/SecondWindow.ui
)

# 资源文件（所有.qrc文件，如果有）
set(MODULE_RESOURCES
    resources/secondui.qrc
)

# ============================================
# 根据BUILD_STATIC_LIBS选项决定编译方式
# ============================================

# 始终创建OBJECT库来处理MOC/UIC
add_library(${MODULE_NAME}_objects OBJECT
    ${MODULE_SOURCES}
    ${MODULE_HEADERS}
    ${MODULE_UIS}
    ${MODULE_RESOURCES}
)

if(BUILD_STATIC_LIBS)
    # 静态库模式：创建静态库
    add_library(${MODULE_NAME} STATIC
        $<TARGET_OBJECTS:${MODULE_NAME}_objects>
    )
    message(STATUS "  [secondui] 构建为静态库")
else()
    # 直接编译模式：OBJECT库可被父项目使用
    message(STATUS "  [secondui] 源文件将被直接编译到可执行文件")
endif()

# 创建INTERFACE库用于导出编译选项和头文件路径（仅用于链接时的配置）
add_library(${MODULE_NAME}_if INTERFACE)
target_include_directories(${MODULE_NAME}_if INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/biz
)

# 向父项目导出INTERFACE库名称
set(SECONDCONTROLLER_INTERFACE ${MODULE_NAME}_if PARENT_SCOPE)

# ============================================
# 包含目录配置
# ============================================

# 导出模块源文件和头文件给父项目使用
set(SECONDCONTROLLER_SOURCES ${MODULE_SOURCES} PARENT_SCOPE)
set(SECONDCONTROLLER_HEADERS ${MODULE_HEADERS} PARENT_SCOPE)
set(SECONDCONTROLLER_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/biz
    PARENT_SCOPE
)

# ============================================
# Qt依赖（兼容Qt5和Qt6）
# ============================================

# 从父级项目继承Qt版本配置
if(TARGET Qt6::Core)
    target_link_libraries(${MODULE_NAME}_objects PUBLIC Qt6::Core Qt6::Widgets Qt6::Gui)
elseif(TARGET Qt5::Core)
    target_link_libraries(${MODULE_NAME}_objects PUBLIC Qt5::Core Qt5::Widgets Qt5::Gui)
endif()

if(BUILD_STATIC_LIBS)
    # 静态库模式：设置包含目录
    target_include_directories(${MODULE_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/biz>
    )

    # 设置C++标准
    target_compile_features(${MODULE_NAME} PUBLIC cxx_std_11)

    # Windows平台特定设置
    if(WIN32)
        target_compile_definitions(${MODULE_NAME} PRIVATE UNICODE _UNICODE)
    endif()
else()
    # 直接编译模式：设置OBJECT库属性
    target_include_directories(${MODULE_NAME}_objects PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/biz
    )
    target_compile_features(${MODULE_NAME}_objects PUBLIC cxx_std_11)
    if(WIN32)
        target_compile_definitions(${MODULE_NAME}_objects PRIVATE UNICODE _UNICODE)
    endif()
endif()

# 调试信息
message(STATUS "Module: ${MODULE_NAME} configured successfully")
