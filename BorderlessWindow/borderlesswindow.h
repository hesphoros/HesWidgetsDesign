#ifndef BORDERLESSWINDOW_H
#define BORDERLESSWINDOW_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

class Border;
class MainArea;

/**
 * @class BorderlessWindow
 * @brief 无边框窗口控件
 *
 * 实现一个完全自定义的无边框窗口，提供完整的窗口管理功能，
 * 包括可拖动的边框调整、标题栏控制等。
 * 采用网格布局管理8个方向的边框和主内容区域。
 */
class BorderlessWindow : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针，默认为nullptr
     *
     * 初始化无边框窗口，创建8个方向的边框控件和主内容区域。
     */
    explicit BorderlessWindow(QWidget *parent = nullptr);

    /**
     * @brief 获取用于UI设置的QWidget
     * @return 可用于setupUi的QWidget指针
     *
     * 返回主内容区域的QWidget，方便在Qt Designer 中使用。
     */
    QWidget *qWidgetUseInSetupUi();

    /**
     * @brief 设置窗口标题
     * @param title 要设置的标题文本
     *
     * 将标题传递给内部的主内容区域标题栏。
     */
    void setWindowTitle(const QString& title);

    /**
     * @brief 设置窗口图标
     * @param icon 要设置的图标
     *
     * 将图标传递给内部的主内容区域标题栏。
     */
    void setWindowIcon(const QPixmap& icon);

protected:
    /**
     * @brief 状态改变事件处理
     * @param event 状态改变事件对象
     *
     * 处理窗口状态变化（如最大化/最小化/正常状态切换）。
     */
    virtual void changeEvent(QEvent *event) override;

private:
    QGridLayout *gridLayout = nullptr;       ///< 主网格布局管理器

    /* 八个方向的边框控件 */
    Border*           left_border          = nullptr;          ///< 左边框控件
    Border*           left_top_border      = nullptr;          ///< 左上角边框控件
    Border*           right_top_border     = nullptr;          ///< 右上角边框控件
    Border*           top_border           = nullptr;          ///< 上边框控件
    Border*           bottom_border        = nullptr;          ///< 下边框控件
    Border*           left_bottom_border   = nullptr;          ///< 左下角边框控件
    Border*           right_border         = nullptr;          ///< 右边框控件
    Border*           right_bottom_border  = nullptr;          ///< 右下角边框控件
	/* 主内容区域控件 */
    MainArea*         main_area      = nullptr;                ///< 主内容区域控件
};

#endif // BORDERLESSWINDOW_H
