# Settings 模块
set(SETTINGS_SOURCES
    src/PreferencesPage.cpp
)

set(SETTINGS_HEADERS
    include/PreferencesPage.h
)

set(SETTINGS_UIS
    ui/PreferencesPage.ui
)

# 设置AUTOUIC搜索路径
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

add_library(settings_objects OBJECT
    ${SETTINGS_SOURCES}
    ${SETTINGS_HEADERS}
    ${SETTINGS_UIS}
)

target_include_directories(settings_objects PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/settings_objects_autogen/include
)

target_link_libraries(settings_objects PUBLIC
    ${QT_TARGET_PREFIX}::Core
    ${QT_TARGET_PREFIX}::Widgets
)

set(settings_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
