# ============================================
# DashboardPage 模块 - CMake配置
# ============================================

cmake_minimum_required(VERSION 3.16)

set(PAGE_NAME dashboard)

set(PAGE_SOURCES
    src/FileManagerPage.cpp
)

set(PAGE_HEADERS
    include/FileManagerPage.h
)

set(PAGE_UIS
    ui/FileManagerPage.ui
)

# 启用Qt的AUTOUIC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 设置AUTOUIC搜索路径（关键！）
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

add_library(${PAGE_NAME}_objects OBJECT
    ${PAGE_SOURCES}
    ${PAGE_HEADERS}
    ${PAGE_UIS}
)

target_include_directories(${PAGE_NAME}_objects PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/${PAGE_NAME}_autogen/include
)

if(TARGET Qt6::Core)
    target_link_libraries(${PAGE_NAME}_objects PUBLIC Qt6::Core Qt6::Widgets)
elseif(TARGET Qt5::Core)
    target_link_libraries(${PAGE_NAME}_objects PUBLIC Qt5::Core Qt5::Widgets)
endif()

# 导出包含目录到父项目
set(dashboard_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

message(STATUS "  [${PAGE_NAME}] 页面模块配置完成")
