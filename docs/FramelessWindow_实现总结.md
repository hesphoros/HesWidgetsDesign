# FramelessWindow 类实现总结

## 设计目标
`FramelessWindow` 类旨在实现一个无边框、可自定义标题栏的窗口，支持窗口拖拽、缩放、圆角等现代化窗口特性，主要用于 Windows 平台下的 Qt 应用。

## 实现思路

### 1. 无边框窗口设置
- 通过 `setWindowFlags` 增加 `Qt::FramelessWindowHint` 和 `Qt::WindowSystemMenuHint`，去除系统默认边框和标题栏。
- 设置 `Qt::WA_TranslucentBackground` 属性，实现窗口背景透明。

### 2. Windows 原生接口增强
- 获取窗口句柄 `HWND`，通过 `GetWindowLong` 和 `SetWindowLong` 增加 `WS_THICKFRAME`、`WS_CAPTION`、`WS_MAXIMIZEBOX`，使窗口支持缩放、最大化等操作。
- 使用 `DwmSetWindowAttribute` 设置 `DWMWA_WINDOW_CORNER_PREFERENCE`，实现窗口圆角效果。

### 3. 标题栏自定义与拖拽
- 提供 `setTitleBar` 方法，允许外部设置自定义标题栏控件。
- 在 `nativeEvent` 事件中处理 `WM_NCHITTEST`，判断鼠标是否在自定义标题栏区域，实现拖拽移动。
- 若鼠标在标题栏且未命中子控件，则返回 `HTCAPTION`，实现拖动。

### 4. 边框缩放逻辑
- 在 `nativeEvent` 事件中处理 `WM_NCHITTEST`，调用 `adjustResizeWindow` 判断鼠标是否在窗口边缘或角落，实现窗口缩放。
- 通过判断鼠标位置与窗口边界的关系，返回不同的 hit test 结果（如 `HTLEFT`、`HTTOPLEFT` 等）。

### 5. 最大化与边距自适应
- 重载 `event` 方法，监听 `QEvent::WindowStateChange`。
- 最大化时去除内容边距，恢复时设置默认边距（如 8 像素），保证窗口阴影和缩放手柄效果。

## 关键点与注意事项
- 仅支持 Windows 平台，依赖 Win32 API 和 DWM（桌面窗口管理器）。
- 需确保自定义标题栏区域正确响应鼠标事件，避免子控件影响拖拽体验。
- 圆角、阴影等效果依赖于 Windows 10 及以上系统的 DWM 支持。

## 适用场景
适用于需要高度自定义窗口外观的 Qt 桌面应用，如自定义皮肤、现代风格 UI 等。

---

> 本文档总结自 `FramelessWindow.cpp` 源码实现。
