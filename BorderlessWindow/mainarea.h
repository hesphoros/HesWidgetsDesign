#ifndef MAINAREA_H
#define MAINAREA_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include "./titlebale/standardtitlebar.h"


/**
 * @class MainArea
 * @brief 主内容区域控件
 *
 * 提供一个包含标题栏和客户区域的标准主界面布局控件。
 * 采用垂直布局管理，上方为标题栏，下方为客户自定义区域。
 */
class MainArea : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针
     *
     * 初始化主区域布局，创建标题栏和客户区域。
     */
    explicit MainArea(QWidget *parent);

    /**
     * @brief 获取客户区域控件
     * @return 指向客户区域QWidget的指针
     *
     * 返回客户区域控件，用户可在此区域添加自定义内容。
     */
    QWidget *customerAreaWidget();

    /**
     * @brief 获取标题栏控件
     * @return 指向StandardTitleBar的指针
     *
     * 返回标题栏控件，可用于自定义标题栏行为或样式。
     */
    StandardTitleBar *titleBar();

private:
    QVBoxLayout *vertical_layout = nullptr;      ///< 垂直布局管理器
    StandardTitleBar *title_bar = nullptr;       ///< 标题栏控件
    QWidget *customer_area_widget = nullptr;     ///< 客户区域容器控件

protected:
    /**
     * @brief 绘制事件处理
     * @param event 绘制事件对象
     *
     * 处理主区域的绘制操作，可在此实现自定义背景等绘制效果。
     */
    void paintEvent(QPaintEvent *event) override;
};

#endif // MAINAREA_H
