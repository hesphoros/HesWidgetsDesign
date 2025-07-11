# HesWidgetsDesign 构建说明

## 📋 项目概述

HesWidgetsDesign 是一个现代化的 Qt Widgets 库，提供了丰富的自定义控件和 Windows 平台特有的视觉效果支持。

## 🛠️ 构建要求

### 必需组件
- **CMake**: 3.16 或更高版本
- **Qt**: 6.5.3 或兼容版本 (推荐)
- **C++**: 支持 C++17 标准的编译器

### 平台特定要求

#### Windows
- **Visual Studio 2019/2022** 或 **MSVC 编译器**
- **Qt SDK**: `D:/Qt/6.5.3/msvc2019_64` (默认路径)
- **系统库**: dwmapi.lib, user32.lib, kernel32.lib, ntdll.lib

#### Linux
- **GCC 8+** 或 **Clang 10+**
- **Qt SDK**: `/opt/Qt/6.5.3/gcc_64` (默认路径)

#### macOS
- **Xcode 12+** 或 **Clang 10+**
- **Qt SDK**: `/opt/Qt/6.5.3/macos` (默认路径)

## 🚀 快速开始

### 方法一：使用构建脚本（推荐）

#### Windows
```batch
# 构建 Release 版本
build.bat

# 构建 Debug 版本
build.bat --debug

# 清理并重新构建
build.bat --clean --debug

# 指定自定义 Qt 路径
build.bat --qt-dir "C:/Qt/6.5.3/msvc2019_64"
```

#### Linux/macOS
```bash
# 给脚本添加执行权限
chmod +x build.sh

# 构建 Release 版本
./build.sh

# 构建 Debug 版本
./build.sh --debug

# 清理并重新构建
./build.sh --clean --debug

# 指定自定义 Qt 路径
./build.sh --qt-dir "/opt/Qt/6.5.3/gcc_64"
```

### 方法二：手动构建

```bash
# 1. 创建构建目录
mkdir build && cd build

# 2. 配置项目
cmake .. -DCMAKE_BUILD_TYPE=Release -DQT_SDK_DIR="你的Qt路径"

# 3. 构建项目
cmake --build . --config Release --parallel

# 4. 安装项目
cmake --install . --config Release
```

## 📁 项目结构

```
HesWidgetsDesign/
├── CMakeLists.txt                 # 主 CMake 配置文件
├── build.bat                      # Windows 构建脚本
├── build.sh                       # Linux/macOS 构建脚本
├── HesWidgetsDesign/              # 核心库
│   ├── CMakeLIsts.txt             # 库 CMake 配置
│   ├── include/                   # 公共头文件
│   │   ├── common/                # 通用定义和宏
│   │   ├── HesApplication.h       # 应用程序管理
│   │   ├── HesTheme.h             # 主题管理
│   │   └── HesWinShadowHelper.h   # Windows 阴影助手
│   ├── src/                       # 源文件
│   ├── private/                   # 私有实现
│   └── DeveloperComponents/       # 开发者组件
└── HesWidgetsDesignExample/       # 示例应用程序
    └── CMakeLIsts.txt             # 示例 CMake 配置
```

## 🎨 特性支持

### Windows 平台特有功能
- **Mica 效果**: Windows 11 的现代化背景效果
- **Acrylic 效果**: Windows 10 的毛玻璃背景
- **暗色主题**: 原生 Windows 暗色主题支持
- **圆角窗口**: Windows 11 风格的圆角窗口
- **窗口阴影**: 自定义窗口阴影效果

### 跨平台功能
- **主题管理**: 统一的主题色彩系统
- **单例模式**: 线程安全的单例实现
- **颜色宏系统**: 便于管理的颜色定义

## 🔧 配置选项

### CMake 配置选项

```bash
# Qt SDK 目录
-DQT_SDK_DIR="路径/到/Qt/SDK"

# 构建类型
-DCMAKE_BUILD_TYPE=Release|Debug|RelWithDebInfo|MinSizeRel

# 安装目录
-DCMAKE_INSTALL_PREFIX="安装路径"
```

### 编译器选项
- **MSVC**: `/utf-8`, `/W4`, `/permissive-`
- **GCC/Clang**: `-Wall`, `-Wextra`, `-Wpedantic`

## 📦 作为依赖使用

### 方法一：CMake find_package
```cmake
find_package(HesWidgetsDesign REQUIRED)
target_link_libraries(your_target HesWidgetsDesign::HesWidgetsDesign)
```

### 方法二：add_subdirectory
```cmake
add_subdirectory(path/to/HesWidgetsDesign)
target_link_libraries(your_target HesWidgetsDesign)
```

## 🐛 故障排除

### 常见问题

1. **Qt 路径找不到**
   ```
   解决方案: 使用 -DQT_SDK_DIR 指定正确的 Qt 安装路径
   ```

2. **Windows 上缺少系统库**
   ```
   解决方案: 确保安装了完整的 Windows SDK
   ```

3. **编译器版本不支持**
   ```
   解决方案: 升级到支持 C++17 的编译器版本
   ```

### 调试构建
```bash
# 启用详细输出
cmake --build . --config Debug --verbose

# 检查库依赖 (Linux)
ldd path/to/library

# 检查库依赖 (Windows)
dumpbin /dependents path/to/library.dll
```

## 📄 许可证

本项目采用 Apache License 2.0 许可证，详见 [LICENSE](LICENSE) 文件。

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！

## 📞 支持

如有问题，请创建 [GitHub Issue](https://github.com/hesphoros/HesWidgetsDesign/issues)。
