# LiquidCam - Qt5/Qt6 CMake 项目模板

基于Qt5/Qt6和CMake的多模块项目模板，支持多人协作开发。

## 主要特性

- ✅ **C++11标准**：兼容老版本编译器
- ✅ **Qt5/Qt6双版本支持**：一键切换Qt版本
- ✅ **模块化设计**：清晰的代码结构
- ✅ **多人协作**：CMake配置统一，易于协作
- ✅ **详细注释**：代码逻辑清晰，易于维护

## 项目结构

```
LiquidCam/
├── CMakeLists.txt              # 根CMake配置
├── CMakePresets.json           # CMake构建预设
├── .gitignore                  # Git忽略文件
├── main.cpp                    # 程序主入口
├── README.md                   # 项目说明文档
│
├── src/                        # 源代码目录
│   ├── mainui/                 # 主界面模块
│   │   ├── CMakeLists.txt
│   │   ├── ui/                 # UI文件（.ui）
│   │   ├── include/            # 头文件
│   │   ├── src/                # 源文件
│   │   ├── biz/                # 业务逻辑
│   │   └── resources/          # 资源文件
│   └── secondui/               # 次级界面模块（计算器）
│       ├── CMakeLists.txt
│       ├── ui/
│       ├── include/
│       ├── src/
│       ├── biz/
│       └── resources/
│
├── resource/                   # 全局资源目录
│   ├── images/                 # 图片资源
│   │   ├── mainui/
│   │   └── secondui/
│   └── styles/                 # 样式资源
│       ├── mainui/
│       └── secondui/
│
├── tests/                      # 测试代码目录
└── 3rd/                        # 第三方库目录
    ├── include/
    └── lib/
```

## 模块说明

### 1. MainUI模块（主界面）
- **功能**：显示欢迎信息、系统信息、操作日志
- **特点**：
  - 简洁的UI设计
  - 信号槽机制实现事件处理
  - 业务逻辑与UI分离（MVC模式）

### 2. SecondUI模块（计算器）
- **功能**：实现一个简单的计算器
- **特点**：
  - 支持四则运算
  - 百分比、正负号转换
  - 错误处理（除零检测）

## Qt版本切换

项目默认使用**Qt6**，如需切换到**Qt5**（兼容老机器），只需修改根目录CMakeLists.txt：

```cmake
# 根目录 CMakeLists.txt 第33行附近
# 修改为使用Qt5
set(QT_VERSION_MAJOR "5")

# 或保持默认使用Qt6
set(QT_VERSION_MAJOR "6")
```

**一键切换后重新编译即可，无需修改代码！**

## 编译说明

### 前置要求
- CMake 3.16 或更高版本
- Qt 5.5+ 或 Qt 6.x
- 支持 C++11 的编译器（MSVC 2013+, GCC 4.8+, Clang 3.3+）

### Windows平台编译

1. 设置Qt路径环境变量（可选，如果CMake找不到Qt）

**使用Qt5：**
```bash
set CMAKE_PREFIX_PATH=C:\Qt\5.15.2\msvc2019_64
```

**使用Qt6：**
```bash
set CMAKE_PREFIX_PATH=C:\Qt\6.5.0\msvc2019_64
```

2. 创建构建目录并生成项目
```bash
mkdir build
cd build
cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
```

3. 编译项目
```bash
cmake --build .
```

4. 运行程序
```bash
.\bin\LiquidCam.exe
```

### Linux/macOS平台编译

1. 设置Qt路径环境变量（可选，如果CMake找不到Qt）

**使用Qt5：**
```bash
export Qt5_DIR=/opt/Qt5.15.2/lib/cmake/Qt5
```

**使用Qt6：**
```bash
export Qt6_DIR=/opt/Qt6.5.0/lib/cmake/Qt6
```

2. 创建构建目录并生成项目
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

3. 编译项目
```bash
make -j$(nproc)
```

4. 运行程序
```bash
./bin/LiquidCam
```

### 使用编译脚本（推荐）

**Windows：**
```bash
# 编译Debug版本
build.bat

# 编译Release版本
build.bat Release

# 清理后重新编译
build.bat clean Debug
```

**Linux/macOS：**
```bash
chmod +x build.sh

# 编译Debug版本
./build.sh

# 编译Release版本
./build.sh Release

# 清理后重新编译
./build.sh clean Debug
```

## 代码规范

### 1. 命名规范
- **类名**：PascalCase（如 MainWindow）
- **变量名**：camelCase（如 m_controller）
- **成员变量**：m_ 前缀（如 m_textEdit）
- **常量**：UPPER_CASE（如 MAX_SIZE）
- **函数名**：camelCase（如 setupUi）
- **指针管理**：C++11使用原始指针，在析构函数中手动delete

### 2. 文件组织
- 头文件（.h）：声明类、函数、常量
- 源文件（.cpp）：实现具体逻辑
- UI文件（.ui）：Qt Designer设计的界面
- 业务逻辑（biz/）：与UI分离的业务代码

### 3. 注释规范
- 文件头部注释：说明文件用途
- 类注释：说明类的功能和职责
- 函数注释：说明函数参数、返回值和功能
- 关键代码：添加内联注释说明逻辑

### 4. 设计原则
- **分层架构**：UI层、业务逻辑层分离
- **单一职责**：每个类只负责一个功能
- **信号槽机制**：使用Qt信号槽进行模块通信
- **资源管理**：C++11使用原始指针，在析构函数中手动释放资源

## 多人协作指南

### 1. Qt版本统一管理
- 项目默认使用Qt6编译
- 老机器开发者可将CMakeLists.txt中的`QT_VERSION_MAJOR`改为"5"
- 代码完全兼容Qt5和Qt6，无需修改源代码
- 建议在团队文档中记录默认Qt版本

### 2. 分工建议
- **MainUI开发者**：负责主界面模块
- **SecondUI开发者**：负责计算器模块
- **公共模块**：共享的资源和工具类

### 3. 协作规范
- 使用Git进行版本控制
- 遵循Git分支策略（feature分支开发）
- 代码审查后再合并到主分支
- 定期同步主分支代码
- 不要提交build目录到Git

### 4. 编译配置
- 使用CMake统一构建配置
- 每个开发者本地生成自己的build目录
- 第三方库统一版本放置在3rd目录

## 常见问题

### 1. Qt5路径找不到
```bash
# Windows
set Qt5_DIR=C:\Qt\5.15.2\msvc2019_64\lib\cmake\Qt5

# Linux/macOS
export Qt5_DIR=/opt/Qt5.15.2/lib/cmake/Qt5
```

### 2. 编译错误
- 确认C++标准设置为C++17
- 检查Qt5版本是否支持
- 查看CMake输出日志定位问题

### 3. 运行时错误
- 确认Qt动态库在PATH中（Windows）
- 确认所有依赖资源文件已正确编译
- 查看控制台输出的调试信息

## 扩展开发

### 添加新模块
1. 在src目录下创建新模块文件夹
2. 按照现有模块结构创建子目录（ui/include/src/biz/resources）
3. 编写CMakeLists.txt配置文件
4. 在根目录CMakeLists.txt中添加子模块

### 添加新功能
1. 在对应的biz目录下添加业务逻辑
2. 在include目录下添加头文件
3. 在src目录下实现具体功能
4. 在UI文件中添加界面元素

## 技术栈

- **语言**：C++11
- **框架**：Qt 5.5+ / Qt 6.x（双版本支持）
- **构建工具**：CMake 3.16+
- **编译器**：MSVC 2013+ / GCC 4.8+ / Clang 3.3+
- **版本控制**：Git
- **跨平台**：Windows / Linux / macOS

## Qt版本兼容性说明

| 功能 | Qt5 (5.5+) | Qt6 (6.x) | 说明 |
|------|-----------|-----------|------|
| 基础UI | ✅ | ✅ | 完全兼容 |
| 信号槽 | ✅ | ✅ | 完全兼容 |
| 样式表 | ✅ | ✅ | 完全兼容 |
| 资源系统 | ✅ | ✅ | 完全兼容 |
| 计算器功能 | ✅ | ✅ | 完全兼容 |
| 性能 | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ | Qt6性能更优 |

**推荐配置：**
- 新项目/高性能需求：使用Qt6
- 兼容老机器/团队协作：使用Qt5
- 两者代码完全一致，只改CMakeLists.txt切换

## 许可证

本项目为演示项目，可自由使用和修改。

## 联系方式

如有问题或建议，请联系项目维护者。
