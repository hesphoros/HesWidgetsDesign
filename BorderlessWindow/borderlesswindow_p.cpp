#include "borderlesswindow_p.h"
#include "borderlesswindow.h"
#include "mainarea.h"
#include <QApplication>
#include <QDebug>

BorderlessWindowPrivate::BorderlessWindowPrivate(BorderlessWindow *parent)
    : QObject(parent)
    , q_ptr(parent)
    , gridLayout(nullptr)
    , mainArea(nullptr)
    , dragging(false)
{
}

BorderlessWindowPrivate::~BorderlessWindowPrivate()
{
}

void BorderlessWindowPrivate::initializeWindow()
{
    Q_Q(BorderlessWindow);
    
    // 设置无边框窗口
    q->setWindowFlags(q->windowFlags() | Qt::FramelessWindowHint);
    q->setAttribute(Qt::WA_TranslucentBackground);
    q->resize(640, 480);
    
    // 启用鼠标追踪
    q->setMouseTracking(true);
    
    // 创建布局和主区域
    gridLayout = new QGridLayout(q);
    mainArea = new MainArea(q);
    
    // 设置布局 - 主内容区域填满整个窗口
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(mainArea, 0, 0, 1, 1);
}

#ifdef Q_OS_WIN
void BorderlessWindowPrivate::setupWindowAttributes()
{
    Q_Q(BorderlessWindow);
    HWND hwnd = reinterpret_cast<HWND>(q->winId());
    
    // 设置圆角
    UINT preference = 2; // DWMWCP_ROUND
    DwmSetWindowAttribute(hwnd, 33 /*DWMWA_WINDOW_CORNER_PREFERENCE*/, &preference, sizeof(preference));
    
    // 启用 DWM 渲染
    BOOL shadowEnabled = TRUE;
    DwmSetWindowAttribute(hwnd, 2 /*DWMWA_NCRENDERING_ENABLED*/, &shadowEnabled, sizeof(shadowEnabled));
}

bool BorderlessWindowPrivate::handleNativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    Q_Q(BorderlessWindow);
    
    if (eventType == "windows_generic_MSG") {
        MSG *msg = static_cast<MSG *>(message);
        
        if (msg->message == WM_NCHITTEST) {
            QPoint localPos = q->mapFromGlobal(QPoint(GET_X_LPARAM(msg->lParam), GET_Y_LPARAM(msg->lParam)));
            *result = hitTest(localPos);
            
            // 如果不是客户区，说明我们处理了，返回true
            if (*result != HTCLIENT) {
                return true;
            }
        }
    }
    
    // 对于其他消息，让Qt的默认处理方式接管
    return QObject::nativeEvent(eventType, message, result);
}

LRESULT BorderlessWindowPrivate::hitTest(const QPoint &pos) const
{
    Q_Q(const BorderlessWindow);

    if (q->isMaximized()) {
        return HTCLIENT; // 最大化时不应允许拖拽调整
    }

    const int w = q->width();
    const int h = q->height();
    const int titleBarHeight = mainArea->titleBar()->height();

    // 1. 检测标题栏按钮区域 (最高优先级，避免被其他区域覆盖)
    if (pos.y() < titleBarHeight && pos.x() >= w - TITLE_BAR_BUTTON_WIDTH) {
        return HTCLIENT; // 返回客户区，让按钮可以接收鼠标事件
    }

    // 2. 检测四个角落
    if (pos.x() < EDGE_WIDTH && pos.y() < EDGE_WIDTH) return HTTOPLEFT;
    if (pos.x() >= w - EDGE_WIDTH && pos.y() < EDGE_WIDTH) return HTTOPRIGHT;
    if (pos.x() < EDGE_WIDTH && pos.y() >= h - EDGE_WIDTH) return HTBOTTOMLEFT;
    if (pos.x() >= w - EDGE_WIDTH && pos.y() >= h - EDGE_WIDTH) return HTBOTTOMRIGHT;

    // 3. 检测四个边缘
    if (pos.x() < EDGE_WIDTH) return HTLEFT;
    if (pos.x() >= w - EDGE_WIDTH) return HTRIGHT;
    if (pos.y() < EDGE_WIDTH) return HTTOP;
    if (pos.y() >= h - EDGE_WIDTH) return HTBOTTOM;

    // 4. 检测标题栏拖拽区域 (避开按钮)
    if (pos.y() < titleBarHeight) {
        return HTCAPTION;
    }

    // 5. 默认返回客户区
    return HTCLIENT;
}
#endif
