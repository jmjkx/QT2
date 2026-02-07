# ============================================
# SettingsPage 模块 - CMake配置
# ============================================
# 这是标准的新页面模板，复制此目录即可创建新页面

cmake_minimum_required(VERSION 3.16)

set(PAGE_NAME settings)

# 页面源文件
set(PAGE_SOURCES
    src/PreferencesPage.cpp
)

# 页面头文件
set(PAGE_HEADERS
    include/PreferencesPage.h
)

# 页面UI文件
set(PAGE_UIS
    ui/PreferencesPage.ui
)

# 启用Qt的AUTOUIC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 设置AUTOUIC搜索路径（关键！）
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# 创建OBJECT库（被主项目引用）
add_library(${PAGE_NAME}_objects OBJECT
    ${PAGE_SOURCES}
    ${PAGE_HEADERS}
    ${PAGE_UIS}
)

# 设置包含目录
target_include_directories(${PAGE_NAME}_objects PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    # 生成的ui_*.h文件目录
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/${PAGE_NAME}_autogen/include
)

# 链接Qt库
if(TARGET Qt6::Core)
    target_link_libraries(${PAGE_NAME}_objects PUBLIC Qt6::Core Qt6::Widgets)
elseif(TARGET Qt5::Core)
    target_link_libraries(${PAGE_NAME}_objects PUBLIC Qt5::Core Qt5::Widgets)
endif()

# 导出包含目录到父项目
set(settings_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

message(STATUS "  [${PAGE_NAME}] 页面模块配置完成")
