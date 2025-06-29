#ifndef BORDER_H
#define BORDER_H

#include <QObject>
#include <QWidget>
#include <QWindow>
#include <QMouseEvent>
#include <QEnterEvent>
#include <QPainter>

/**
 * @enum BorderType
 * @brief 枚举窗口边框的类型
 *
 * 用于标识窗口的不同边框位置，包括单边和角落组合
 */
enum class BorderType
{
    top_border = 1,          ///< 上边框
    bottom_border = 2,       ///< 下边框
    left_border = 3,         ///< 左边框
    right_border = 4,        ///< 右边框
    left_top_border = 5,     ///< 左上角边框
    right_top_border = 6,    ///< 右上角边框
    left_bottom_border = 7,  ///< 左下角边框
    right_bottom_border = 8  ///< 右下角边框
};


/**
 * @class Border
 * @brief 自定义窗口边框控件
 *
 * 用于实现无边框窗口的可拖动调整大小的边框控件。
 * 支持8种不同位置的边框类型，可通过鼠标事件调整窗口大小。
 */
class Border : public QWidget
{
    Q_OBJECT
public:    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     * @param bordertype 边框类型
     */
    explicit Border(QWidget *parent, BorderType bordertype);
    
    /**
     * @brief 获取边框类型
     * @return 当前边框的类型
     */
    BorderType borderType() const { return border_type; }

private:
    BorderType border_type;  ///< 当前边框的类型
    int border_width = 12;   ///< 边框的宽度(像素) - 增加到12px便于拖拽操作

protected:
    /**
     * @brief 鼠标按下事件处理
     * @param event 鼠标事件对象
     *
     * 处理鼠标按下事件，开始窗口大小调整操作
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief 鼠标移动事件处理
     * @param event 鼠标事件对象
     *
     * 处理鼠标移动事件，实现窗口大小调整
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief 绘制事件处理
     * @param event 绘制事件对象
     *
     * 绘制边框的可视化效果(如需要)
     */
    void paintEvent(QPaintEvent* event) override;

    /**
     * @brief 显示事件处理
     * @param event 显示事件对象
     *
     * 处理窗口显示事件
     */
    void showEvent(QShowEvent *event) override;

    /**
     * @brief 鼠标进入事件处理
     * @param event 鼠标进入事件对象
     */
    void enterEvent(QEnterEvent *event) override;

    /**
     * @brief 鼠标离开事件处理
     * @param event 鼠标离开事件对象
     */
    void leaveEvent(QEvent *event) override;
};
#endif // BORDER_H
