# ============================================
# Qt DLL 自动部署模块
# ============================================
# 在构建完成后自动调用 windeployqt 拷贝所需 DLL
#
# 使用方法：
#   include(cmake/DeployQt.cmake)
#   deploy_qt_dlls(target_name)
# ============================================

# 查找 windeployqt 工具
function(find_windeployqt WIN_DEPLOY_QT_PATH)
    # 从 Qt 路径推导 windeployqt 位置
    set(QT_BIN_DIR "${CMAKE_PREFIX_PATH}/bin")
    
    if(EXISTS "${QT_BIN_DIR}/windeployqt.exe")
        set(${WIN_DEPLOY_QT_PATH} "${QT_BIN_DIR}/windeployqt.exe" PARENT_SCOPE)
        message(STATUS "找到 windeployqt: ${QT_BIN_DIR}/windeployqt.exe")
        return()
    endif()
    
    # 尝试从 Qt6Core_DIR 推导
    if(DEFINED Qt6Core_DIR)
        get_filename_component(QT_ROOT "${Qt6Core_DIR}" DIRECTORY)
        get_filename_component(QT_ROOT "${QT_ROOT}" DIRECTORY)
        if(EXISTS "${QT_ROOT}/bin/windeployqt.exe")
            set(${WIN_DEPLOY_QT_PATH} "${QT_ROOT}/bin/windeployqt.exe" PARENT_SCOPE)
            message(STATUS "找到 windeployqt: ${QT_ROOT}/bin/windeployqt.exe")
            return()
        endif()
    endif()
    
    # 尝试从 Qt5Core_DIR 推导
    if(DEFINED Qt5Core_DIR)
        get_filename_component(QT_ROOT "${Qt5Core_DIR}" DIRECTORY)
        get_filename_component(QT_ROOT "${QT_ROOT}" DIRECTORY)
        if(EXISTS "${QT_ROOT}/bin/windeployqt.exe")
            set(${WIN_DEPLOY_QT_PATH} "${QT_ROOT}/bin/windeployqt.exe" PARENT_SCOPE)
            message(STATUS "找到 windeployqt: ${QT_ROOT}/bin/windeployqt.exe")
            return()
        endif()
    endif()
    
    set(${WIN_DEPLOY_QT_PATH} "" PARENT_SCOPE)
endfunction()

# 部署 Qt DLL 的函数
function(deploy_qt_dlls TARGET_NAME)
    if(NOT WIN32)
        message(STATUS "非 Windows 平台，跳过 DLL 部署")
        return()
    endif()
    
    find_windeployqt(WIN_DEPLOY_QT)
    
    if(NOT WIN_DEPLOY_QT)
        message(WARNING "未找到 windeployqt.exe，无法自动部署 Qt DLL")
        message(WARNING "请手动将 Qt DLL 拷贝到 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
        return()
    endif()
    
    # 获取目标文件的完整路径
    set(TARGET_EXE "$<TARGET_FILE:${TARGET_NAME}>")
    set(TARGET_DIR "$<TARGET_FILE_DIR:${TARGET_NAME}>")
    
    # 根据编译器类型选择不同的 windeployqt 参数
    if(MINGW)
        # MinGW 编译器
        set(WINDEPLOYQT_ARGS 
            "--dir" "${TARGET_DIR}"
            "--libdir" "${TARGET_DIR}"
            "--plugindir" "${TARGET_DIR}/plugins"
            "--no-translations"
            "--no-compiler-runtime"
            "--force"
        )
        message(STATUS "使用 MinGW 模式部署 Qt DLL")
    else()
        # MSVC 编译器
        set(WINDEPLOYQT_ARGS 
            "--dir" "${TARGET_DIR}"
            "--libdir" "${TARGET_DIR}"
            "--plugindir" "${TARGET_DIR}/plugins"
            "--no-translations"
            "--force"
        )
        message(STATUS "使用 MSVC 模式部署 Qt DLL")
    endif()
    
    # 添加构建后命令，自动拷贝 DLL
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND "${WIN_DEPLOY_QT}"
        ARGS ${WINDEPLOYQT_ARGS}
        "${TARGET_EXE}"
        COMMENT "正在部署 Qt DLL 到 ${TARGET_DIR}..."
        VERBATIM
    )
    
    message(STATUS "已配置自动部署 Qt DLL: ${TARGET_NAME}")
endfunction()
