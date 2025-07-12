# HesWidgetsDesign Example

这是一个用于测试 HesWidgetsDesign 库中 HesApplication 和 HesTheme 功能的示例程序。

## 功能特性

### 🏢 HesApplication 测试功能
- **初始化测试**: 测试 HesApplication 的初始化过程
- **窗口显示模式**: 支持多种窗口显示模式切换
  - 正常模式 (Normal)
  - Hes Mica 模式
  - Mica 模式
  - Mica Alt 模式
  - Acrylic 模式
  - DWM Blur 模式
- **窗口同步**: 测试窗口显示模式同步功能
- **光标检测**: 测试光标位置检测功能

### 🎨 HesTheme 测试功能
- **主题模式切换**: 支持浅色/深色主题切换
- **信号监听**: 监听主题变更信号

## 使用方法

### 构建和运行
```bash
# 在项目根目录执行
cmake -S . -B build
cmake --build build

# 运行示例程序
./build/bin/HesWidgetsDesignExample
```

### 操作指南

1. **初始化**: 点击"初始化 HesApplication"按钮来初始化 HesApplication 实例
2. **切换模式**: 使用下拉菜单切换窗口显示模式和主题模式
3. **同步窗口**: 点击"同步窗口显示模式"将当前窗口与选择的显示模式同步
4. **测试光标**: 将鼠标悬停在"测试光标检测"按钮上，然后点击按钮查看检测结果

### 界面说明

- **控制面板**: 包含所有的操作按钮和选择器
- **当前状态**: 实时显示 HesApplication 和 HesTheme 的当前状态
- **操作日志**: 记录所有操作的详细日志信息

## 注意事项

- 某些窗口效果（如 Mica、Acrylic）仅在 Windows 11 上可用
- DWM Blur 效果在较旧的 Windows 版本上可能表现不同
- 确保系统支持所选的窗口效果

## 故障排除

如果遇到问题：
1. 检查操作日志中的错误信息
2. 确认系统版本是否支持所选的窗口效果
3. 查看控制台输出的调试信息

## 开发说明

这个示例展示了如何：
- 正确初始化 HesApplication
- 使用单例模式访问 HesApplication 和 HesTheme
- 监听和响应框架事件
- 测试框架的各种功能特性
