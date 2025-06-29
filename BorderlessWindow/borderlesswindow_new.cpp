#include "borderlesswindow.h"
#include "mainarea.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>
#ifdef Q_OS_WIN
#include <windows.h>
#include <dwmapi.h>
#include <windowsx.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "user32.lib")
#endif

BorderlessWindow::BorderlessWindow(QWidget *parent)
    : QWidget{parent},
      gridLayout{new QGridLayout(this)},
      main_area{new MainArea(this)},
      m_dragging{false}
{
    this->setWindowFlags(this->windowFlags() | Qt::WindowType::FramelessWindowHint);
    this->setAttribute(Qt::WidgetAttribute::WA_TranslucentBackground);
    this->resize(640, 480);
    
    // 启用鼠标追踪
    this->setMouseTracking(true);

    // 简化布局 - 只有主内容区域，留出边缘空间用于拖拽
    this->gridLayout->setSpacing(0);
    this->gridLayout->setContentsMargins(EDGE_WIDTH, EDGE_WIDTH, EDGE_WIDTH, EDGE_WIDTH);
    this->gridLayout->addWidget(this->main_area, 0, 0, 1, 1);
    
    qDebug() << "BorderlessWindow created with edge width:" << EDGE_WIDTH;
}

QWidget *BorderlessWindow::qWidgetUseInSetupUi()
{
    return this->main_area->customerAreaWidget();
}

void BorderlessWindow::setWindowTitle(const QString &title)
{
    this->main_area->titleBar()->setTitle(title);
}

void BorderlessWindow::setWindowIcon(const QPixmap &icon)
{
    this->main_area->titleBar()->setIcon(icon);
}

BorderlessWindow::EdgeType BorderlessWindow::getEdgeType(const QPoint &pos) const
{
    if (this->isMaximized()) {
        return None;
    }
    
    QRect rect = this->rect();
    EdgeType edge = None;
    
    // 检测左右边缘
    if (pos.x() <= EDGE_WIDTH) {
        edge = static_cast<EdgeType>(edge | Left);
    } else if (pos.x() >= rect.width() - EDGE_WIDTH) {
        edge = static_cast<EdgeType>(edge | Right);
    }
    
    // 检测上下边缘
    if (pos.y() <= EDGE_WIDTH) {
        edge = static_cast<EdgeType>(edge | Top);
    } else if (pos.y() >= rect.height() - EDGE_WIDTH) {
        edge = static_cast<EdgeType>(edge | Bottom);
    }
    
    return edge;
}

void BorderlessWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        EdgeType edge = getEdgeType(event->pos());
        qDebug() << "Mouse press at edge type:" << static_cast<int>(edge);
        
        if (edge != None) {
#ifdef Q_OS_WIN
            // 使用 Windows API 开始调整大小
            ReleaseCapture();
            HWND hwnd = reinterpret_cast<HWND>(this->winId());
            
            int wParam = 0;
            if (edge == Left) wParam = HTLEFT;
            else if (edge == Right) wParam = HTRIGHT;
            else if (edge == Top) wParam = HTTOP;
            else if (edge == Bottom) wParam = HTBOTTOM;
            else if (edge == TopLeft) wParam = HTTOPLEFT;
            else if (edge == TopRight) wParam = HTTOPRIGHT;
            else if (edge == BottomLeft) wParam = HTBOTTOMLEFT;
            else if (edge == BottomRight) wParam = HTBOTTOMRIGHT;
            
            if (wParam != 0) {
                qDebug() << "Sending WM_NCLBUTTONDOWN with wParam:" << wParam;
                SendMessage(hwnd, WM_NCLBUTTONDOWN, wParam, 0);
                return;
            }
#endif
        }
    }
    QWidget::mousePressEvent(event);
}

void BorderlessWindow::mouseMoveEvent(QMouseEvent *event)
{
    EdgeType edge = getEdgeType(event->pos());
    
    // 设置光标样式
    Qt::CursorShape cursor = Qt::ArrowCursor;
    switch (edge) {
        case Left:
        case Right:
            cursor = Qt::SizeHorCursor;
            break;
        case Top:
        case Bottom:
            cursor = Qt::SizeVerCursor;
            break;
        case TopLeft:
        case BottomRight:
            cursor = Qt::SizeFDiagCursor;
            break;
        case TopRight:
        case BottomLeft:
            cursor = Qt::SizeBDiagCursor;
            break;
        default:
            cursor = Qt::ArrowCursor;
            break;
    }
    
    this->setCursor(cursor);
    QWidget::mouseMoveEvent(event);
}

void BorderlessWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_dragging = false;
    QWidget::mouseReleaseEvent(event);
}

void BorderlessWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::Type::WindowStateChange)
    {
        QWindowStateChangeEvent *stateChangeEvent = static_cast<QWindowStateChangeEvent *>(event);
        // 最大化
        if (this->windowState() & Qt::WindowState::WindowMaximized)
        {
            emit this->main_area->titleBar()->maximizeButton()->stateChange(MaximizeButton::State::MAXIMIZE);
            // 最大化时移除边缘空间
            this->gridLayout->setContentsMargins(0, 0, 0, 0);
        }
        // 最大化后还原
        else if (stateChangeEvent->oldState() & Qt::WindowState::WindowMaximized && !(this->windowState() & Qt::WindowState::WindowMaximized))
        {
            emit this->main_area->titleBar()->maximizeButton()->stateChange(MaximizeButton::State::NORMAL);
            // 还原时恢复边缘空间
            this->gridLayout->setContentsMargins(EDGE_WIDTH, EDGE_WIDTH, EDGE_WIDTH, EDGE_WIDTH);
        }
    }
    this->update();
    QWidget::changeEvent(event);
}

void BorderlessWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
#ifdef Q_OS_WIN
    HWND hwnd = reinterpret_cast<HWND>(this->winId());
    
    // 设置圆角
    UINT preference = 2; // DWMWCP_ROUND
    DwmSetWindowAttribute(hwnd, 33 /*DWMWA_WINDOW_CORNER_PREFERENCE*/, &preference, sizeof(preference));
    
    // 启用 DWM 渲染但不设置阴影边距，避免双重边框
    BOOL shadowEnabled = TRUE;
    DwmSetWindowAttribute(hwnd, 2 /*DWMWA_NCRENDERING_ENABLED*/, &shadowEnabled, sizeof(shadowEnabled));
#endif
}

void BorderlessWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // 绘制调试边框（可选）
    if (!this->isMaximized()) {
        painter.setPen(QPen(QColor(255, 0, 0, 100), 1));
        painter.drawRect(0, 0, EDGE_WIDTH, this->height()); // 左
        painter.drawRect(this->width() - EDGE_WIDTH, 0, EDGE_WIDTH, this->height()); // 右
        painter.drawRect(0, 0, this->width(), EDGE_WIDTH); // 上
        painter.drawRect(0, this->height() - EDGE_WIDTH, this->width(), EDGE_WIDTH); // 下
    }
    
    QWidget::paintEvent(event);
}

#ifdef Q_OS_WIN
bool BorderlessWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    if (eventType == "windows_generic_MSG") {
        MSG *msg = static_cast<MSG *>(message);
        
        if (msg->message == WM_NCHITTEST) {
            // 让系统处理边缘检测
            *result = HTCLIENT;
            return true;
        }
    }
    
    return QWidget::nativeEvent(eventType, message, result);
}
#endif
