# 编译模式说明

## 概述

本工程支持两种编译模式，通过CMake选项 `BUILD_STATIC_LIBS` 控制。
**注意：子目录的CMakeLists.txt始终执行，只是根据选项决定是否生成静态库。**

---

## 静态库模式（默认）

**特点：**
- 子模块编译为静态库（`libmainui.a` 和 `libsecondui.a`）
- 主程序链接这些静态库
- 编译产物位于 `build/lib/` 目录
- 模块化清晰，便于调试和维护

**构建流程：**
```
根CMakeLists
  ├─→ add_subdirectory(src/mainui)
  │       └─→ add_library(mainui STATIC ...)  ✅ 生成静态库
  └─→ add_subdirectory(src/secondui)
          └─→ add_library(secondui STATIC ...) ✅ 生成静态库
主程序 → target_link_libraries(mainui secondui)  ✅ 链接静态库
```

**用途：**
- Qt6 开发（无版权限制）
- Qt5 开发但已购买商业授权
- 需要静态链接Qt的场景

**编译命令：**
```bash
# 默认开启静态库模式
cmake -B build
cmake --build build
```

---

## 直接编译模式

**特点：**
- 子目录CMakeLists.txt正常执行（收集配置）
- **不生成静态库**
- 所有源文件直接编译到可执行文件
- 避免Qt5 LGPL协议的版权限制
- 更简单的构建流程

**构建流程：**
```
根CMakeLists
  ├─→ add_subdirectory(src/mainui)
  │       └─→ 跳过 add_library，仅配置变量
  └─→ add_subdirectory(src/secondui)
          └─→ 跳过 add_library，仅配置变量
主程序 → add_executable(... 所有源文件 ...)  ✅ 直接编译所有代码
```

**用途：**
- Qt5 LGPL 版本开发（避免静态链接Qt）
- 需要动态链接Qt的场景
- 商业发布但未购买Qt授权

**编译命令：**
```bash
# 关闭静态库模式
cmake -B build -DBUILD_STATIC_LIBS=OFF
cmake --build build
```

---

## Qt版本切换

结合编译模式和Qt版本选择：

### Qt6（推荐）
```cmake
# CMakeLists.txt 第44行
set(QT_VERSION_MAJOR "6")
```

### Qt5（需注意版权）
```cmake
# CMakeLists.txt 第44行
set(QT_VERSION_MAJOR "5")
```

#### Qt5 + 静态库模式
- ⚠️ **警告**：静态链接Qt5可能违反LGPL协议
- 仅适用于已购买Qt商业授权的情况

#### Qt5 + 直接编译模式（推荐）
- ✅ **合规**：动态链接Qt5，符合LGPL协议
- 避免版权问题

---

## 技术细节

### CMakeLists 结构

**根CMakeLists.txt：**
```cmake
option(BUILD_STATIC_LIBS "Build as static libraries" ON)

# 始终添加子模块
add_subdirectory(src/mainui)
add_subdirectory(src/secondui)

if(BUILD_STATIC_LIBS)
    # 静态库模式：链接静态库
    add_executable(LiquidCam main.cpp)
    target_link_libraries(LiquidCam PRIVATE mainui secondui Qt6::Core ...)
else()
    # 直接编译模式：包含所有源文件
    add_executable(LiquidCam main.cpp
        src/mainui/src/MainWindow.cpp
        src/mainui/biz/MainController.cpp
        src/secondui/src/SecondWindow.cpp
        src/secondui/biz/SecondController.cpp
    )
    target_link_libraries(LiquidCam PRIVATE Qt6::Core ...)
endif()
```

**mainui/CMakeLists.txt：**
```cmake
if(BUILD_STATIC_LIBS)
    add_library(mainui STATIC
        src/MainWindow.cpp
        biz/MainController.cpp
    )
    # 设置包含目录、链接Qt库等
else()
    # 跳过静态库生成，仅执行配置
    message(STATUS "  [mainui] 源文件将被直接编译到可执行文件")
endif()
```

**secondui/CMakeLists.txt：**
```cmake
if(BUILD_STATIC_LIBS)
    add_library(secondui STATIC
        src/SecondWindow.cpp
        biz/SecondController.cpp
    )
    # 设置包含目录、链接Qt库等
else()
    # 跳过静态库生成，仅执行配置
    message(STATUS "  [secondui] 源文件将被直接编译到可执行文件")
endif()
```

---

## 快速参考

| 场景 | BUILD_STATIC_LIBS | QT_VERSION_MAJOR | 状态 |
|------|-----------------|----------------|------|
| Qt6开发 | ON（默认） | 6 | ✅ 推荐 |
| Qt6 + 直接编译 | OFF | 6 | ✅ 可用 |
| Qt5 + 商业授权 | ON | 5 | ✅ 合规 |
| Qt5 + LGPL模式 | OFF（必须） | 5 | ✅ 合规 |
| Qt5 + 静态库（无授权） | ON | 5 | ❌ 违规 |

---

## Windows编译示例

### PowerShell
```powershell
# 静态库模式（默认）
cmake -B build -G "MinGW Makefiles"
cmake --build build

# 直接编译模式（避免Qt5版权）
cmake -B build -G "MinGW Makefiles" -DBUILD_STATIC_LIBS=OFF
cmake --build build
```

### Bash/MSYS2
```bash
# 静态库模式（默认）
./build.sh

# 直接编译模式
cmake -B build -DBUILD_STATIC_LIBS=OFF
cmake --build build
```

---

## 构建产物对比

### 静态库模式
```
build/
├── bin/
│   └── LiquidCam.exe          # 可执行文件（链接静态库）
└── lib/
    ├── libmainui.a            # 主界面静态库
    └── libsecondui.a         # 计算器静态库
```

### 直接编译模式
```
build/
└── bin/
    └── LiquidCam.exe          # 可执行文件（包含所有代码）
```

## 输出示例

### 静态库模式
```
-- 使用Qt6进行编译
-- 编译模式: 静态库模式
--   [mainui] 构建为静态库
--   [secondui] 构建为静态库
```

### 直接编译模式
```
-- 使用Qt6进行编译
-- 编译模式: 直接编译模式 (避免Qt5版权问题)
--   [mainui] 源文件将被直接编译到可执行文件
--   [secondui] 源文件将被直接编译到可执行文件
```
