#include "HesAppBarPrivate.h"

#include "HesToolButton.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

#include <QGuiApplication>
#include <QLabel>
#include <QPropertyAnimation>
#include <QScreen>
#include <QVBoxLayout>
#include <QWidget>

#include "HesAppBar.h"
#include "HesIconButton.h"
#include "HesNavigitionBar.h"
#include "HesText.h"

HesAppBarPrivate::HesAppBarPrivate(QObject* parent) : QObject(parent) {
    // Constructor implementation
}
HesAppBarPrivate::~HesAppBarPrivate() {
    // Destructor implementation
}

void HesAppBarPrivate::onMinButtonClicked() {
    Q_Q(HesAppBar);
    q->window()->showMinimized();
}

void HesAppBarPrivate::onMaxButtonClicked() {
    Q_Q(HesAppBar);
    if (q->window()->isMaximized()) {
        q->window()->showNormal();
    } else {
        q->window()->showMaximized();
    }
}

void HesAppBarPrivate::onCloseButtonClicked()
{
    Q_Q(HesAppBar);
    if (_pIsDefaultClosed)
    {
        q->window()->close();
    }
    else
    {
        Q_EMIT q_ptr->closeButtonClicked();
    }
}


void HesAppBarPrivate::onStayTopButtonClicked() {
#ifdef Q_OS_WIN
    HWND hwnd = reinterpret_cast<HWND>(_currentWinID);
    // HWND_TOPMOST 是一个特殊的窗口位置标志，用于将窗口置于所有非顶层窗口之上
    // HWND_NOTOPMOST 则将窗口从顶层窗口列表中移除
    ::SetWindowPos(hwnd, _pIsStayTop ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#else
    Q_Q(const HesAppBar);
    bool isVisible = q->window()->isVisible();
    q->window()->setWindowFlag(Qt::WindowStaysOnTopHint, !_pIsStayTop);
    if (isVisible) {
        q->window()->show();
    }
#endif
    _stayTopButton->setIsSelected(_pIsStayTop);
    _stayTopButton->update();
}

void HesAppBarPrivate::_changeMaxButtonAwesome(bool isMaximized) {
    if (isMaximized) {
        _maxButton->setHesIcon(HesIconType::WindowRestore);
    } else {
        _maxButton->setHesIcon(HesIconType::Square);
    }
}

/**
 * @brief 显示系统菜单
 * @details 该函数用于在指定位置显示系统菜单
 * 
 * @param point 
 */
/**
 * @brief Displays the native Windows system menu at the specified screen position.
 *
 * This function shows the system menu (restore, move, size, minimize, maximize, close) for the window
 * at the given point. It adjusts menu item states based on the window's current state (maximized, fullscreen, fixed size).
 * The menu is displayed using native Win32 APIs and handles high-DPI scaling.
 *
 * @param point The screen position (in device-independent pixels) where the system menu should appear.
 */
void HesAppBarPrivate::_showSystemMenu(QPoint point) {
    Q_Q(HesAppBar);
#ifdef Q_OS_WIN
    QScreen* screen = qApp->screenAt(QCursor::pos());
    if (!screen) {
        screen = QGuiApplication::primaryScreen();
    }
    if (!screen) {
        return;
    }
    const QPoint origin = screen->geometry().topLeft();
    auto nativePos = QPointF(QPointF(point - origin) * screen->devicePixelRatio()).toPoint() + origin;
    HWND hwnd = reinterpret_cast<HWND>(q->window()->winId());
    const HMENU hMenu = ::GetSystemMenu(hwnd, FALSE);
    if (q->window()->isMaximized() || q->window()->isFullScreen())
    {
        ::EnableMenuItem(hMenu, SC_MOVE, MFS_DISABLED);
        ::EnableMenuItem(hMenu, SC_RESTORE, MFS_ENABLED);
    }
    else
    {
        ::EnableMenuItem(hMenu, SC_MOVE, MFS_ENABLED);
        ::EnableMenuItem(hMenu, SC_RESTORE, MFS_DISABLED);
    }
    if (!_pIsFixedSize && !q->window()->isMaximized() && !q->window()->isFullScreen())
    {
        ::EnableMenuItem(hMenu, SC_SIZE, MFS_ENABLED);
        ::EnableMenuItem(hMenu, SC_MAXIMIZE, MFS_ENABLED);
    }
    else
    {
        ::EnableMenuItem(hMenu, SC_SIZE, MFS_DISABLED);
        ::EnableMenuItem(hMenu, SC_MAXIMIZE, MFS_DISABLED);
    }
    const int result = ::TrackPopupMenu(hMenu, (TPM_RETURNCMD | (QGuiApplication::isRightToLeft() ? TPM_RIGHTALIGN : TPM_LEFTALIGN)), nativePos.x(),
                                        nativePos.y(), 0, hwnd, nullptr);
    if (result != FALSE)
    {
        ::PostMessageW(hwnd, WM_SYSCOMMAND, result, 0);
    }

#endif
}


/**
 * @brief 根据指定的窗口边缘更新鼠标光标。
 *
 * 此函数根据参数 `edges` 指示的窗口边缘设置窗口的光标形状。
 * 当鼠标悬停在窗口边框上时，光标会变化以反映可能的调整大小操作：
 * - 无边缘时为箭头光标。
 * - 左边或右边为水平调整大小光标。
 * - 上边或下边为垂直调整大小光标。
 * - 左上或右下为正斜向调整大小光标。
 * - 右上或左下为反斜向调整大小光标。
 *
 * @param edges Qt::Edge 标志的按位组合，指示窗口的边缘。
 */
void HesAppBarPrivate::_updateCursor(int edges)
{
    Q_Q(const HesAppBar);
    switch (edges)
    {
        case 0:
        {
            q->window()->setCursor(Qt::ArrowCursor);
            break;
        }
        case Qt::LeftEdge:
        case Qt::RightEdge:
        {
            q->window()->setCursor(Qt::SizeHorCursor);
            break;
        }
        case Qt::TopEdge:
        case Qt::BottomEdge:
        {
            q->window()->setCursor(Qt::SizeVerCursor);
            break;
        }
        case Qt::LeftEdge | Qt::TopEdge:
        case Qt::RightEdge | Qt::BottomEdge:
        {
            q->window()->setCursor(Qt::SizeFDiagCursor);
            break;
        }
        case Qt::RightEdge | Qt::TopEdge:
        case Qt::LeftEdge | Qt::BottomEdge:
        {
            q->window()->setCursor(Qt::SizeBDiagCursor);
            break;
        }
        default:
        {
            break;
        }
    }
}



/**
 * @brief 判断鼠标光标是否位于指定的QWidget控件上。
 *
 * 此函数用于检测鼠标是否在传入的item控件区域内，或者在导航栏相关按钮（如返回按钮、导航按钮、自定义控件、置顶按钮、主题切换按钮、最小化按钮、最大化按钮、关闭按钮）上。
 * 如果item为空或不可见，则返回false。
 * 首先判断鼠标是否在上述相关按钮上，若是则直接返回true。
 * 否则，判断鼠标是否在item控件的矩形区域内，若是则返回true，否则返回false。
 *
 * @param item 需要检测的QWidget控件指针。
 * @return 如果鼠标在控件或相关按钮上则返回true，否则返回false。
 */
bool HesAppBarPrivate::_containsCursorToItem(QWidget* item) {
    Q_Q(const HesAppBar);
    if (!item || !item->isVisible()) {
        return false;
    }

    auto point = item->window()->mapFromGlobal(QCursor::pos());
    QRectF rect = QRectF(item->mapTo(item->window(), QPoint(0, 0)), item->size());

    if ( _containsCursorToItem(_routeBackButton)   ||
         _containsCursorToItem(_navigationButton)  ||
         _containsCursorToItem(_pCustomWidget)     ||
         _containsCursorToItem(_stayTopButton)     ||
         _containsCursorToItem(_themeChangeButton) ||
         _containsCursorToItem(_minButton)         ||
         _containsCursorToItem(_maxButton)         ||
         _containsCursorToItem(_closeButton)) 
    {
        return true;
    }
    
    if (rect.contains(point)) {
        return true;
    }
    return false;
}

void HesAppBarPrivate::_onThemeModeChange(HesThemeType::ThemeMode themeMode) {
    if ( themeMode == HesThemeType::Light ) {
        _themeChangeButton->setHesIcon(HesIconType::MoonStars);
    } else if ( themeMode == HesThemeType::Dark ) {
        _themeChangeButton->setHesIcon(HesIconType::SunBright);
    }
}


int HesAppBarPrivate::_calculateMinimumWidth() {
    Q_Q(HesAppBar);
    int width = 0;
    if (_titleLabel->isVisible())
    {
        width += _titleLabel->width();
        width += 10;
    }
    if (_iconLabel->isVisible())
    {
        width += _iconLabel->width();
        width += 10;
    }
    bool isHasNavigationBar = false;
    if (q->parentWidget()->findChild<HesNavigationBar*>())
    {
        isHasNavigationBar = true;
        width += 305;
    }
    else
    {
        width += 5;
    }
    if (_pCustomWidget)
    {
        int customWidgetWidth = _pCustomWidget->width();
        if (isHasNavigationBar)
        {
            if (customWidgetWidth > 300)
            {
                width += customWidgetWidth - 300;
            }
        }
        else
        {
            width += customWidgetWidth;
        }
    }
    QList<QAbstractButton*> buttonList = q->findChildren<QAbstractButton*>();
    for (auto button : buttonList)
    {
        if (button->isVisible() && button->objectName() != "NavigationButton")
        {
            width += button->width();
        }
    }
    return width;
}

QVBoxLayout* HesAppBarPrivate::_createVLayout(QWidget* widget)
{
    if (!widget)
    {
        return nullptr;
    }
    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    if (widget == _iconLabel || widget == _titleLabel)
    {
        vLayout->addSpacing(6);
    }
    vLayout->addWidget(widget);
    vLayout->addStretch();
    return vLayout;
}