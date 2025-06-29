#include "border.h"
#include <QDebug>
#ifdef Q_OS_WIN
#include <windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#endif

Border::Border(QWidget *parent, BorderType bordertype)
    : QWidget{parent},
      border_type{bordertype}
{
    // 边框控件现在只用于布局，不处理鼠标事件
    // 所有拖拽调整大小功能由 BorderlessWindow 的 nativeEvent 处理

    if (this->border_type == BorderType::top_border || this->border_type == BorderType::bottom_border)
        this->setFixedHeight(this->border_width);
    else if (this->border_type == BorderType::left_border || this->border_type == BorderType::right_border)
        this->setFixedWidth(this->border_width);
    else
        this->setFixedSize(this->border_width, this->border_width);
        
    // 添加调试信息
    qDebug() << "Border created with type:" << static_cast<int>(this->border_type) 
             << "size:" << this->size() << "width:" << this->border_width;
}

BorderType Border::borderType() const
{
    return this->border_type;
}

void Border::paintEvent(QPaintEvent *)
{
    // 边框控件现在完全透明，不绘制任何内容
    // 所有视觉效果由 DWM 处理
}

void Border::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    
    // 只让第一个显示的边框设置 DWM 属性
    static bool dwmAttributesSet = false;
    
#ifdef Q_OS_WIN
    if (!dwmAttributesSet) {
        QWidget *topWindow = this->window();
        if (topWindow) {
            HWND hwnd = reinterpret_cast<HWND>(topWindow->winId());
            
            // 设置圆角
            UINT preference = 2; // DWMWCP_ROUND
            DwmSetWindowAttribute(hwnd, 33 /*DWMWA_WINDOW_CORNER_PREFERENCE*/, &preference, sizeof(preference));
            
            // 启用 DWM 渲染
            BOOL shadowEnabled = TRUE;
            DwmSetWindowAttribute(hwnd, 2 /*DWMWA_NCRENDERING_ENABLED*/, &shadowEnabled, sizeof(shadowEnabled));
            
            dwmAttributesSet = true;
        }
    }
#endif
}
