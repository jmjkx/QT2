# ============================================
# SecondUI模块 - 计算器页面
# ============================================
# 结构参考：
#   include/    - 头文件
#   src/        - 源文件
#   ui/         - UI文件
#   resources/  - 资源文件

cmake_minimum_required(VERSION 3.16)

set(MODULE_NAME secondui)

# ============================================
# 头文件
# ============================================
set(MODULE_HEADERS
    include/CalculatorPage.h
)

# ============================================
# 源文件
# ============================================
set(MODULE_SOURCES
    src/CalculatorPage.cpp
)

# ============================================
# UI文件
# ============================================
set(MODULE_UIS
    ui/SecondWindow.ui
)

# ============================================
# 资源文件
# ============================================
set(MODULE_RESOURCES
    resources/secondui.qrc
)

# ============================================
# 启用Qt的自动处理
# ============================================
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# ============================================
# 包含目录
# ============================================
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ============================================
# 创建OBJECT库
# ============================================
add_library(${MODULE_NAME}_objects OBJECT
    ${MODULE_HEADERS}
    ${MODULE_SOURCES}
    ${MODULE_UIS}
    ${MODULE_RESOURCES}
)

if(BUILD_STATIC_LIBS)
    add_library(${MODULE_NAME} STATIC
        $<TARGET_OBJECTS:${MODULE_NAME}_objects>
    )
    message(STATUS "  [secondui] 构建为静态库")
else()
    message(STATUS "  [secondui] UI文件将被直接编译")
endif()

# ============================================
# 导出包含目录（供主项目使用）
# ============================================
set(secondui_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/secondui_autogen/include
    PARENT_SCOPE
)

# ============================================
# Qt依赖
# ============================================
if(TARGET Qt6::Core)
    target_link_libraries(${MODULE_NAME}_objects PUBLIC Qt6::Core Qt6::Widgets)
elseif(TARGET Qt5::Core)
    target_link_libraries(${MODULE_NAME}_objects PUBLIC Qt5::Core Qt5::Widgets)
endif()

if(BUILD_STATIC_LIBS)
    target_include_directories(${MODULE_NAME}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/secondui_autogen/include>
    )
    target_compile_features(${MODULE_NAME} PUBLIC cxx_std_11)
    if(WIN32)
        target_compile_definitions(${MODULE_NAME} PRIVATE UNICODE _UNICODE)
    endif()
else()
    target_include_directories(${MODULE_NAME}_objects PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/secondui_autogen/include
    )
    target_compile_features(${MODULE_NAME}_objects PUBLIC cxx_std_11)
    if(WIN32)
        target_compile_definitions(${MODULE_NAME}_objects PRIVATE UNICODE _UNICODE)
    endif()
endif()

add_custom_target(${MODULE_NAME}_ui_sources SOURCES ${MODULE_UIS})

message(STATUS "Module: ${MODULE_NAME} configured successfully")
