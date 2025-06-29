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

void Border::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Border::mousePressEvent called for border type:" << static_cast<int>(this->border_type);
    
    if (this->window()->isMaximized()) {
        qDebug() << "Window is maximized, ignoring resize";
        return QWidget::mousePressEvent(event);
    }
    
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Left button pressed on border, attempting resize";
        
        // 方法1: 尝试使用 Qt 的原生方法
        QWindow *window = this->window()->windowHandle();
        if (window) {
            qDebug() << "Window handle found, calling startSystemResize";
            
            Qt::Edges edges = Qt::Edges();
            switch (this->border_type) {
            case BorderType::top_border:
                edges = Qt::TopEdge;
                break;
            case BorderType::bottom_border:
                edges = Qt::BottomEdge;
                break;
            case BorderType::left_border:
                edges = Qt::LeftEdge;
                break;
            case BorderType::right_border:
                edges = Qt::RightEdge;
                break;
            case BorderType::left_top_border:
                edges = Qt::LeftEdge | Qt::TopEdge;
                break;
            case BorderType::right_bottom_border:
                edges = Qt::RightEdge | Qt::BottomEdge;
                break;
            case BorderType::left_bottom_border:
                edges = Qt::LeftEdge | Qt::BottomEdge;
                break;
            case BorderType::right_top_border:
                edges = Qt::RightEdge | Qt::TopEdge;
                break;
            }
            
            bool result = window->startSystemResize(edges);
            qDebug() << "startSystemResize result:" << result;
            
            if (result) {
                event->accept();
                return;
            }
        }

#ifdef Q_OS_WIN
        // 方法2: 如果 Qt 方法失败，使用 Windows API
        qDebug() << "Falling back to Windows API";
        ReleaseCapture();
        HWND hwnd = reinterpret_cast<HWND>(this->window()->winId());
        
        int wParam = 0;
        switch (this->border_type) {
        case BorderType::top_border:
            wParam = HTTOP;
            break;
        case BorderType::bottom_border:
            wParam = HTBOTTOM;
            break;
        case BorderType::left_border:
            wParam = HTLEFT;
            break;
        case BorderType::right_border:
            wParam = HTRIGHT;
            break;
        case BorderType::left_top_border:
            wParam = HTTOPLEFT;
            break;
        case BorderType::right_bottom_border:
            wParam = HTBOTTOMRIGHT;
            break;
        case BorderType::left_bottom_border:
            wParam = HTBOTTOMLEFT;
            break;
        case BorderType::right_top_border:
            wParam = HTTOPRIGHT;
            break;
        }
        
        qDebug() << "Sending WM_NCLBUTTONDOWN with wParam:" << wParam;
        SendMessage(hwnd, WM_NCLBUTTONDOWN, wParam, 0);
#endif
        
        event->accept();
        return;
    }
    QWidget::mousePressEvent(event);
}

void Border::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "Mouse move over border type:" << static_cast<int>(this->border_type);
    
    if (this->window()->isMaximized()) {
        this->setCursor(Qt::CursorShape::ArrowCursor);
        return QWidget::mouseMoveEvent(event);
    }
    
    // 设置对应的调整大小光标
    switch (this->border_type) {
    case BorderType::top_border:
    case BorderType::bottom_border:
        this->setCursor(Qt::CursorShape::SizeVerCursor);
        break;
    case BorderType::left_border:
    case BorderType::right_border:
        this->setCursor(Qt::CursorShape::SizeHorCursor);
        break;
    case BorderType::left_top_border:
    case BorderType::right_bottom_border:
        this->setCursor(Qt::CursorShape::SizeFDiagCursor);
        break;
    case BorderType::left_bottom_border:
    case BorderType::right_top_border:
        this->setCursor(Qt::CursorShape::SizeBDiagCursor);
        break;
    }
    QWidget::mouseMoveEvent(event);
}

void Border::paintEvent(QPaintEvent *)
{
    // 完全透明的边框，不绘制任何内容
    // Border 控件只负责接收鼠标事件进行窗口大小调整
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
            
            // 不设置阴影边距，让系统自动处理
            // 这样可以避免双重边框问题
            
            // 启用 DWM 渲染
            BOOL shadowEnabled = TRUE;
            DwmSetWindowAttribute(hwnd, 2 /*DWMWA_NCRENDERING_ENABLED*/, &shadowEnabled, sizeof(shadowEnabled));
            
            dwmAttributesSet = true;
        }
    }
#endif
}

void Border::enterEvent(QEnterEvent *event)
{
    qDebug() << "Mouse entered border type:" << static_cast<int>(this->border_type);
    QWidget::enterEvent(event);
}

void Border::leaveEvent(QEvent *event)
{
    qDebug() << "Mouse left border type:" << static_cast<int>(this->border_type);
    QWidget::leaveEvent(event);
}

