# FramelessWindow 与 BorderlessWindow 组件对比分析

## 共同点
1. **无边框窗口实现**
   - 两者都通过设置 Qt 的 FramelessWindowHint，实现去除系统默认边框和标题栏。
   - 都支持自定义标题栏、窗口拖拽、缩放等现代桌面窗口特性。
2. **平台依赖**
   - 都主要针对 Windows 平台，利用 Win32 API 实现原生窗口行为（如拖拽、缩放、圆角等）。
3. **事件处理**
   - 都重载 nativeEvent，处理 Windows 消息（如 WM_NCHITTEST）以实现自定义命中检测和窗口行为。
4. **自定义内容区**
   - 都允许开发者自定义窗口内容和标题栏，适合高度自定义 UI 场景。

## 不同点
1. **项目结构与模块化**
   - FramelessWindow：实现较为简洁，核心功能集中在一个类中，适合简单自定义需求。
   - BorderlessWindow：结构更为模块化，分为 border、mainarea、titlebale（标题栏相关多个子模块），支持多种标题栏样式和更复杂的自定义。
2. **标题栏实现**
   - FramelessWindow：通过 setTitleBar 设置自定义 QWidget 作为标题栏，逻辑简单。
   - BorderlessWindow：有专门的 titlebale 目录，包含多种标题栏和按钮实现，支持主题、样式切换和更丰富的交互。
3. **边框与缩放**
   - FramelessWindow：边框和缩放逻辑直接在主类中实现，适合基础需求。
   - BorderlessWindow：边框检测和绘制单独封装为 border 模块，缩放和命中检测更灵活。
4. **资源与主题**
   - FramelessWindow：资源和样式较为简单，主要依赖代码实现。
   - BorderlessWindow：使用 qrc 资源文件和 colormanagement 支持多主题和丰富的图标样式。
5. **可扩展性**
   - FramelessWindow：适合轻量级、单一窗口自定义。
   - BorderlessWindow：适合需要多样化标题栏、主题切换、复杂窗口交互的场景。

## 总结
- **FramelessWindow** 更适合简单、快速实现无边框窗口的场景，代码结构清晰，易于集成。
- **BorderlessWindow** 更适合对窗口外观和交互有更高要求的项目，模块化设计便于扩展和维护，支持多种自定义和主题。

---

> 本文档基于源码结构和实现方式自动分析生成，具体细节建议结合实际代码进一步理解。
