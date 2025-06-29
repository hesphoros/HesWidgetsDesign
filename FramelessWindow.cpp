// FramelessWindow.cpp
#include "FramelessWindow.h"
#include <QEvent>
#include <dwmapi.h>
#include <windowsx.h>

#pragma comment(lib, "dwmapi.lib")

namespace {
    constexpr int RESIZE_WINDOW_WIDTH = 8;

    #ifndef _MSC_VER
    #ifndef DWMWA_WINDOW_CORNER_PREFERENCE
    enum DWM_WINDOW_CORNER_PREFERENCE {
        DWMWCP_DEFAULT    = 0,
        DWMWCP_DONOTROUND = 1,
        DWMWCP_ROUND      = 2,
        DWMWCP_ROUNDSMALL = 3
    };
    constexpr DWORD DWMWA_WINDOW_CORNER_PREFERENCE = 33;
    #endif
    #endif
} // anonymous namespace

class FramelessWindow::FramelessWindowPrivate {
public:
    FramelessWindowPrivate(FramelessWindow* q) : q_ptr(q) {}

    int adjustResizeWindow(const QPoint& pos);
    void initWindow();

    FramelessWindow* q_ptr;
    QWidget* titleBar = nullptr;
    bool isMaximized = false;
};

FramelessWindow::FramelessWindow(QWidget* parent)
    : QWidget(parent)
    , d_ptr(std::make_unique<FramelessWindowPrivate>(this))
{
    d_ptr->initWindow();
}

FramelessWindow::~FramelessWindow() = default;

void FramelessWindow::setTitleBar(QWidget* titleBar)
{
    d_ptr->titleBar = titleBar;
}

bool FramelessWindow::nativeEvent(const QByteArray& eventType, void* message, qint64* result)
{
    MSG* msg = reinterpret_cast<MSG*>(message);
    switch (msg->message) {
        case WM_NCCALCSIZE:
            *result = 0;
            return true;

        case WM_NCHITTEST: {
            const LONG gx = GET_X_LPARAM(msg->lParam);
            const LONG gy = GET_Y_LPARAM(msg->lParam);
            QPoint globalPos(gx, gy);

            int hit = d_ptr->adjustResizeWindow(globalPos);
            if (hit) {
                *result = hit;
                return true;
            }

            // 标题栏拖拽检测
            if (d_ptr->titleBar) {
                double dpr = devicePixelRatioF();
                QPoint local = d_ptr->titleBar->mapFromGlobal(QPoint(gx / dpr, gy / dpr));
                if (d_ptr->titleBar->rect().contains(local)) {
                    QWidget* child = d_ptr->titleBar->childAt(local);
                    if (!child) {
                        *result = HTCAPTION;
                        return true;
                    }
                }
            }
            return false;
        }
        default:
            return QWidget::nativeEvent(eventType, message, result);
    }
}

bool FramelessWindow::event(QEvent* event)
{
    if (event->type() == QEvent::WindowStateChange) {
        bool maximized = isMaximized();
        if (maximized != d_ptr->isMaximized) {
            d_ptr->isMaximized = maximized;
            if (maximized) {
                setContentsMargins(0, 0, 0, 0);
            } else {
                setContentsMargins(8, 8, 8, 8);
            }
        }
    }
    return QWidget::event(event);
}

void FramelessWindow::FramelessWindowPrivate::initWindow()
{
    q_ptr->setWindowFlags(q_ptr->windowFlags() | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    q_ptr->setAttribute(Qt::WA_TranslucentBackground);

    HWND hwnd = HWND(q_ptr->winId());
    LONG style = ::GetWindowLong(hwnd, GWL_STYLE);
    ::SetWindowLong(hwnd, GWL_STYLE,
                    style | WS_THICKFRAME | WS_CAPTION | WS_MAXIMIZEBOX);

    UINT preference = DWMWCP_ROUND;
    DwmSetWindowAttribute(hwnd,
                          DWMWA_WINDOW_CORNER_PREFERENCE,
                          &preference, sizeof(preference));
}

int FramelessWindow::FramelessWindowPrivate::adjustResizeWindow(const QPoint& pos)
{
    int result = 0;

    RECT winrect;
    GetWindowRect(HWND(q_ptr->winId()), &winrect);

    int mouse_x = pos.x();
    int mouse_y = pos.y();

    bool resizeWidth = q_ptr->minimumWidth() != q_ptr->maximumWidth();
    bool resizeHeight = q_ptr->minimumHeight() != q_ptr->maximumHeight();

    if (resizeWidth) {
        if (mouse_x > winrect.left && mouse_x < winrect.left + RESIZE_WINDOW_WIDTH)
            result = HTLEFT;
        if (mouse_x < winrect.right && mouse_x >= winrect.right - RESIZE_WINDOW_WIDTH)
            result = HTRIGHT;
    }
    if (resizeHeight) {
        if (mouse_y < winrect.top + RESIZE_WINDOW_WIDTH && mouse_y >= winrect.top)
            result = HTTOP;

        if (mouse_y <= winrect.bottom && mouse_y > winrect.bottom - RESIZE_WINDOW_WIDTH)
            result = HTBOTTOM;
    }
    if (resizeWidth && resizeHeight) {
        // topleft corner
        if (mouse_x >= winrect.left && mouse_x < winrect.left + RESIZE_WINDOW_WIDTH && 
            mouse_y >= winrect.top && mouse_y < winrect.top + RESIZE_WINDOW_WIDTH) {
            result = HTTOPLEFT;
        }
        // topRight corner
        if (mouse_x <= winrect.right && mouse_x > winrect.right - RESIZE_WINDOW_WIDTH && 
            mouse_y >= winrect.top && mouse_y < winrect.top + RESIZE_WINDOW_WIDTH)
            result = HTTOPRIGHT;
        // leftBottom corner
        if (mouse_x >= winrect.left && mouse_x < winrect.left + RESIZE_WINDOW_WIDTH && 
            mouse_y <= winrect.bottom && mouse_y > winrect.bottom - RESIZE_WINDOW_WIDTH)
            result = HTBOTTOMLEFT;
        // rightbottom corner
        if (mouse_x <= winrect.right && mouse_x > winrect.right - RESIZE_WINDOW_WIDTH && 
            mouse_y <= winrect.bottom && mouse_y > winrect.bottom - RESIZE_WINDOW_WIDTH)
            result = HTBOTTOMRIGHT;
    }
    return result;
}
