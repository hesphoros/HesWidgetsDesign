#include "borderlesswindow.h"
#include "border.h"
#include "mainarea.h"
#include <QPainter>
#include <QPainterPath>
#include <QLinearGradient>
#ifdef Q_OS_WIN
#include <windows.h>
#include <dwmapi.h>
#include <windowsx.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "user32.lib")

// Win11 亚克力背景相关结构体定义
struct ACCENTPOLICY {
    int nAccentState;
    int nFlags;
    int nColor;
    int nAnimationId;
};

struct WINCOMPATTRDATA {
    int nAttribute;
    PVOID pData;
    ULONG ulDataSize;
};
#endif

BorderlessWindow::BorderlessWindow(QWidget *parent)
    : QWidget{parent},
      /**  主网格管理布局 */
      gridLayout{new QGridLayout(this)},
      /** 8个位置的border */
      left_border{new Border(this, BorderType::left_border)},
      left_top_border{new Border(this, BorderType::left_top_border)},
      right_top_border{new Border(this, BorderType::right_top_border)},
      top_border{new Border(this, BorderType::top_border)},
      bottom_border{new Border(this, BorderType::bottom_border)},
      left_bottom_border{new Border(this, BorderType::left_bottom_border)},
      right_border{new Border(this, BorderType::right_border)},
      right_bottom_border{new Border(this, BorderType::right_bottom_border)},
      /*主内容区域控件*/
      main_area{new MainArea(this)}
{
    this->setWindowFlags(this->windowFlags() | Qt::WindowType::FramelessWindowHint);
    this->setAttribute(Qt::WidgetAttribute::WA_TranslucentBackground);
    this->resize(640, 480);

    // 确保网格布局正确设置
    this->gridLayout->setSpacing(0);
    this->gridLayout->setContentsMargins(0, 0, 0, 0);
      // 按正确顺序添加组件到网格布局
    this->gridLayout->addWidget(this->left_top_border, 0, 0, 1, 1);
    this->gridLayout->addWidget(this->top_border, 0, 1, 1, 1);
    this->gridLayout->addWidget(this->right_top_border, 0, 2, 1, 1);
    this->gridLayout->addWidget(this->left_border, 1, 0, 1, 1);
    this->gridLayout->addWidget(this->main_area, 1, 1, 1, 1);
    this->gridLayout->addWidget(this->right_border, 1, 2, 1, 1);
    this->gridLayout->addWidget(this->left_bottom_border, 2, 0, 1, 1);
    this->gridLayout->addWidget(this->bottom_border, 2, 1, 1, 1);
    this->gridLayout->addWidget(this->right_bottom_border, 2, 2, 1, 1);    // 确保主区域可以拉伸
    this->gridLayout->setRowStretch(1, 1);
    this->gridLayout->setColumnStretch(1, 1);
    
    // 确保所有边框控件在最上层并安装事件过滤器
    this->left_top_border->raise();
    this->left_top_border->installEventFilter(this);
    this->top_border->raise();
    this->top_border->installEventFilter(this);
    this->right_top_border->raise();
    this->right_top_border->installEventFilter(this);
    this->left_border->raise();
    this->left_border->installEventFilter(this);
    this->right_border->raise();
    this->right_border->installEventFilter(this);
    this->left_bottom_border->raise();
    this->left_bottom_border->installEventFilter(this);
    this->bottom_border->raise();
    this->bottom_border->installEventFilter(this);
    this->right_bottom_border->raise();
    this->right_bottom_border->installEventFilter(this);
    this->bottom_border->raise();
    this->right_bottom_border->raise();
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

void BorderlessWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::Type::WindowStateChange)
    {
        QWindowStateChangeEvent *stateChangeEvent = static_cast<QWindowStateChangeEvent *>(event);
        // 最大化后最小化
        if (stateChangeEvent->oldState() & Qt::WindowState::WindowMaximized && this->windowState() & Qt::WindowState::WindowMinimized)
            return QWidget::changeEvent(event);
        // 最大化
        if (this->windowState() & Qt::WindowState::WindowMaximized)
        {
            emit this->main_area->titleBar()->maximizeButton()->stateChange(MaximizeButton::State::MAXIMIZE);
            for (Border *border : this->findChildren<Border *>())
                if(!border->isHidden())border->hide();

        }
        // 最大化后还原
        if (stateChangeEvent->oldState() & Qt::WindowState::WindowMaximized && !(this->windowState() & Qt::WindowState::WindowMaximized))
        {
            emit this->main_area->titleBar()->maximizeButton()->stateChange(MaximizeButton::State::NORMAL);
            for (Border *border : this->findChildren<Border *>())
                if(border->isHidden())border->show();
        }
    }
    this->update();
    QWidget::changeEvent(event);
}

void BorderlessWindow::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
    // DWM 属性现在由 Border 组件负责设置，避免双重边框
}

void BorderlessWindow::paintEvent(QPaintEvent *event) {
    // 简化绘制，主要背景由亚克力效果提供
    QWidget::paintEvent(event);
}

#ifdef Q_OS_WIN
bool BorderlessWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    if (eventType == "windows_generic_MSG") {
        MSG* msg = static_cast<MSG*>(message);
        
        if (msg->message == WM_NCHITTEST) {
            if (this->isMaximized()) {
                return false;
            }
            
            // 获取鼠标的屏幕坐标
            POINT cursor;
            cursor.x = GET_X_LPARAM(msg->lParam);
            cursor.y = GET_Y_LPARAM(msg->lParam);
            
            // 转换为窗口客户区坐标
            ScreenToClient(msg->hwnd, &cursor);
            
            // 获取窗口客户区大小
            RECT clientRect;
            GetClientRect(msg->hwnd, &clientRect);
            
            int borderWidth = 12; // 边框宽度
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;
            
            qDebug() << "WM_NCHITTEST: cursor at" << cursor.x << cursor.y << "client size:" << width << height;
            
            // 检查边框区域
            bool inLeft = (cursor.x >= 0 && cursor.x <= borderWidth);
            bool inRight = (cursor.x >= width - borderWidth && cursor.x <= width);
            bool inTop = (cursor.y >= 0 && cursor.y <= borderWidth);
            bool inBottom = (cursor.y >= height - borderWidth && cursor.y <= height);
            
            // 角落区域
            if (inLeft && inTop) {
                qDebug() << "HTTOPLEFT";
                *result = HTTOPLEFT;
                return true;
            }
            else if (inRight && inTop) {
                qDebug() << "HTTOPRIGHT";
                *result = HTTOPRIGHT;
                return true;
            }
            else if (inLeft && inBottom) {
                qDebug() << "HTBOTTOMLEFT";
                *result = HTBOTTOMLEFT;
                return true;
            }
            else if (inRight && inBottom) {
                qDebug() << "HTBOTTOMRIGHT";
                *result = HTBOTTOMRIGHT;
                return true;
            }
            // 边缘区域
            else if (inLeft) {
                qDebug() << "HTLEFT";
                *result = HTLEFT;
                return true;
            }
            else if (inRight) {
                qDebug() << "HTRIGHT";
                *result = HTRIGHT;
                return true;
            }
            else if (inTop) {
                qDebug() << "HTTOP";
                *result = HTTOP;
                return true;
            }
            else if (inBottom) {
                qDebug() << "HTBOTTOM";
                *result = HTBOTTOM;
                return true;
            }
        }
    }
    
    return QWidget::nativeEvent(eventType, message, result);
}
#endif

