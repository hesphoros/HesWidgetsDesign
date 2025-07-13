#ifndef HESAPPBARPRIVATE_H
#define HESAPPBARPRIVATE_H

#include <QObject>

#include "common/common_defs.h"
#include "stdafx.h"

class QLabel;
class QScreen;
class QHBoxLayout;
class QVBoxLayout;
class HesText;
class HesIconButton;
class HesToolButton;

class HesAppBar;

class HesAppBarPrivate : public QObject
{
    Q_OBJECT
    Q_D_DECLARE_POINTER(HesAppBar)
    Q_PROPERTY_CREATE_PRIVATE(bool, IsStayTop)
    Q_PROPERTY_CREATE_PRIVATE(bool, IsFixedSize)
    Q_PROPERTY_CREATE_PRIVATE(bool, IsDefaultClosed)
    Q_PROPERTY_CREATE_PRIVATE(bool, IsOnlyAllowMinAndClose)
    Q_PROPERTY_CREATE_PRIVATE(int, AppBarHeight)
    Q_PROPERTY_CREATE_PRIVATE(int, CustomWidgetMaximumWidth)
    
    Q_PROPERTY_CREATE_PRIVATE(QWidget*, CustomWidget)
public:
    explicit HesAppBarPrivate(QObject* parent = nullptr);
    ~HesAppBarPrivate() override;
    
    Q_SLOT void onMinButtonClicked();
    Q_SLOT void onMaxButtonClicked();
    Q_SLOT void onCloseButtonClicked();
    Q_SLOT void onStayTopButtonClicked();
private:
    QHBoxLayout*                           _mainLayout{nullptr};  /*!< 主布局            */
    QVBoxLayout*                      _iconLabelLayout{nullptr};  /*!< 图标布局          */
    QVBoxLayout*                     _titleLabelLayout{nullptr};  /*!< 标题布局          */
    HesAppBarType::ButtonFlags                     _buttonFlags;  /*!< 按钮标志          */
    HesToolButton*                    _routeBackButton{nullptr};  /*!< 路由返回按钮      */
    HesToolButton*                   _navigationButton{nullptr};  /*!< 导航按钮          */
    HesToolButton*                  _themeChangeButton{nullptr};  /*!< 主题切换按钮      */
    HesToolButton*                      _stayTopButton{nullptr};  /*!< 置顶按钮          */
    HesToolButton*                          _minButton{nullptr};  /*!< 最小化按钮        */
    HesToolButton*                          _maxButton{nullptr};  /*!< 最大化按钮        */
    HesIconButton*                        _closeButton{nullptr};  /*!< 关闭按钮          */
    QScreen*                               _lastScreen{nullptr};  /*!< 上次屏幕 ?        */
    HesText*                               _titleLabel{nullptr};  /*!< 标题标签          */
    QLabel*                                 _iconLabel{nullptr};  /*!< 图标标签          */
    qint64                                     _currentWinID{0};  /*!< 当前窗口ID        */
    int                                   _lastMinTrackWidth{0};  
    quint64                                      _clickTimer{0};  /*!< 点击计时器        */
    int                                               _edges{0};  
    int                                             _margins{8};  /*!< 边距              */
    bool                               _isHoverMaxButton{false};  /*!< 是否悬停最大化按钮 */
private:
    void _changeMaxButtonAwesome(bool isMaximized);
    void _showSystemMenu(QPoint point);
    void _updateCursor(int edges);
    bool _containsCursorToItem(QWidget* item);
    void _onThemeModeChange(HesThemeType::ThemeMode themeMode);
    int  _calculateMinimumWidth();
    QVBoxLayout* _createVLayout(QWidget* widget);
};

#endif // HESAPPBARPRIVATE_H