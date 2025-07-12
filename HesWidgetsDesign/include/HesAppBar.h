#ifndef HESAPPBAR_H
#define HESAPPBAR_H

#include <QWidget>

#include "common/common_defs.h"


/**
 * @brief nativeEvent 是 Qt 中用于处理操作系统原生事件的虚函数。
 * 在 Qt 的事件系统中，事件通常是通过 QEvent 类进行处理的
 * 而 nativeEvent 允许你直接处理由操作系统
 * 如 Windows、macOS、Linux 等 发送的底层原生事件
 * 
 */
#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK( 6, 0, 0 )
#define Q_TAKEOVER_NATIVEEVENT_H virtual bool nativeEvent(const QByteArray& eventType, void* message, qintptr* result) override; 
#else
#define Q_TAKEOVER_NATIVEEVENT_H virtual bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;
#endif 
#else
#define Q_TAKEOVER_NATIVEEVENT_H
#endif  // Q_OS_WIN

#ifdef Q_OS_WIN

// 处理原生事件
#define HESAPPBAR_HANDLE(HesAppBar)                                                         \
    if ( HesAppBar )                                                                        \
    {                                                                                       \
        int ret = HesAppBar->takeOverNativeEvent(eventType, message, result);               \
        if ( ret == -1 )                                                                    \
        {                                                                                   \
            return QWidget::nativeEvent(eventType, message, result);                        \
        }                                                                                   \
         return (bool)ret;                                                                  \
    }                                                                                       \
   return QWidget::nativeEvent(eventType, message, result);
#endif  // Q_OS_WIN


#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#define Q_TAKEOVER_NATIVEEVENT_CPP(CLASS, HesAppBar)                                        \
    bool CLASS::nativeEvent(const QByteArray& eventType, void* message, qintptr* result)    \
    {                                                                                       \
        HESAPPBAR_HANDLE(HesAppBar)                                                         \
    }
#else
#define Q_TAKEOVER_NATIVEEVENT_CPP(CLASS, HesAppBar)                                        \
    bool CLASS::nativeEvent(const QByteArray& eventType, void* message, long* result)       \
    {                                                                                       \
        HESAPPBAR_HANDLE(HesAppBar)                                                         \
    }
#endif
#else
#define Q_TAKEOVER_NATIVEEVENT_CPP(CLASS, HesAppBar)
#endif  // Q_OS_WIN

class HesAppBarPrivate;

class HES_EXPORT HesAppBar : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PIMPL(HesAppBar)
    Q_PROPERTY_DEFINE_MEMBER_H(bool, IsStayTop)                 

    /**
     * @brief IsFixedSize
     * @details 该属性控制窗口是否可以在四边进行拉伸
     * * true 为允许拉伸，false 为禁止拉伸；
     */
    Q_PROPERTY_DEFINE_MEMBER_H(bool, IsFixedSize)               
    /**
     * @brief IsDefaultClosed
     * @details 该属性控制窗口是否以默认形式关闭
     * true 为以默认形式关闭，
     * 若设置为 false，点击关闭按钮或在任务栏关闭程序后，
     * 关闭事件会被拦截，同时发送 closeButtonClicked 信号，
     * 用户可连接此信号进行处理；
     */
    Q_PROPERTY_DEFINE_MEMBER_H(bool, IsDefaultClosed)           

    /**
     * @brief IsOnlyAllowMinAndClose
     * @details 该属性限定窗口的可用行为，设置为 true 时，
     * 窗口仅对最小化和关闭按钮响应，这个属性被用来实现主题切换等特殊功能；
     */
    Q_PROPERTY_DEFINE_MEMBER_H(bool, IsOnlyAllowMinAndClose)    

    /**
     * @brief AppBarHeight
     * @note default value is 45
     * @details 该属性设置无边框标题栏的固定高度
     * 此区域会被视作非客户区，响应 窗口拖动、双击放大、右键菜单等操作
     */
    Q_PROPERTY_DEFINE_MEMBER_H(int,  AppBarHeight)              /**!< 应用栏高度        */

    /**
     * @brief CustomWidgetMaximumWidth
     * @details 该属性限制 CustomWidget 自定义窗口的最大宽度
     * 当 CustomWidget 被设置后，该属性生效；
     */
    Q_PROPERTY_DEFINE_MEMBER_H(int,  CustomWidgetMaximumWidth)  /**!< 自定义控件最大宽度 */

public:
    explicit HesAppBar(QWidget* parent = nullptr);
    ~HesAppBar();

    void setCustomWidget(HesAppBarType::CustomArea customArea, QWidget* customWidget);
    QWidget* getCustomWidget() const;

    void setWindowButtonFlag(HesAppBarType::ButtonType   buttonFlag, bool isEnabled = true );
    void setWindowButtonFlags(HesAppBarType::ButtonFlags buttonFlags);

    void setRouteBackButtonEnable(bool isEnable);

    void closeWindow();
#ifdef Q_OS_WIN
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    int takeOverNativeEvent(const QByteArray& eventType, void* message, qintptr* result);
#else
    int takeOverNativeEvent(const QByteArray& eventType, void* message, long* result);
#endif
#endif // Q_OS_WIN

Q_SIGNALS:
    Q_SIGNAL void routeBackButtonClicked();     /*!< 路由返回按钮被点击   */
    Q_SIGNAL void navigationButtonClicked();    /*!< 导航按钮被点击       */
    Q_SIGNAL void themeChangeButtonClicked();   /*!< 主题切换按钮被点击   */
    Q_SIGNAL void closeButtonClicked();         /*!< 关闭按钮被点击       */
    Q_SIGNAL void customWidgetChanged();        /*!< 自定义控件发生变化   */

protected:
    virtual bool eventFilter(QObject* obj, QEvent* event) override;

};

#endif // HESAPPBAR_H