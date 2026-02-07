# Dashboard 模块
set(DASHBOARD_SOURCES
    src/FileManagerPage.cpp
)

set(DASHBOARD_HEADERS
    include/FileManagerPage.h
)

set(DASHBOARD_UIS
    ui/FileManagerPage.ui
)

# 设置AUTOUIC搜索路径
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

add_library(dashboard_objects OBJECT
    ${DASHBOARD_SOURCES}
    ${DASHBOARD_HEADERS}
    ${DASHBOARD_UIS}
)

target_include_directories(dashboard_objects PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/dashboard_objects_autogen/include
)

target_link_libraries(dashboard_objects PUBLIC
    ${QT_TARGET_PREFIX}::Core
    ${QT_TARGET_PREFIX}::Widgets
)

set(dashboard_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
