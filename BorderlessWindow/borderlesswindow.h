#ifndef BORDERLESSWINDOW_H
#define BORDERLESSWINDOW_H

#include <QWidget>
#include <QScopedPointer>

class BorderlessWindowPrivate;
class QPixmap;

/**
 * @class BorderlessWindow
 * @brief 无边框窗口控件 (使用PIMPL设计模式)
 *
 * 实现一个完全自定义的无边框窗口，提供完整的窗口管理功能，
 * 包括可拖动的边框调整、标题栏控制等。
 * 使用PIMPL模式将实现细节隐藏在私有类中。
 */
class BorderlessWindow : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(BorderlessWindow)

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针，默认为nullptr
     */
    explicit BorderlessWindow(QWidget *parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~BorderlessWindow();

    /**
     * @brief 获取用于UI设置的QWidget
     * @return 可用于setupUi的QWidget指针
     */
    QWidget *qWidgetUseInSetupUi();

    /**
     * @brief 设置窗口标题
     * @param title 要设置的标题文本
     */
    void setWindowTitle(const QString& title);

    /**
     * @brief 设置窗口图标
     * @param icon 要设置的图标
     */
    void setWindowIcon(const QPixmap& icon);

protected:
    /**
     * @brief 事件处理函数
     */
    virtual void changeEvent(QEvent *event) override;
    virtual void showEvent(QShowEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    
#ifdef Q_OS_WIN
    virtual bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
#endif

private:
    QScopedPointer<BorderlessWindowPrivate> d_ptr;
};

#endif // BORDERLESSWINDOW_H
