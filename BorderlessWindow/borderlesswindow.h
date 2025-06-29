#ifndef BORDERLESSWINDOW_H
#define BORDERLESSWINDOW_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#ifdef Q_OS_WIN
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#endif

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
     * 处理窗口状态变化（如最大化/最小化/正常状态切换）。     */    virtual void changeEvent(QEvent *event) override;

    virtual void showEvent(QShowEvent *event);
    virtual void paintEvent(QPaintEvent *event) override; // 支持背景亚克力效果
    
    // 鼠标事件处理 - 用于窗口边缘拖拽
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    
#ifdef Q_OS_WIN
    virtual bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
#endif

private:
    QGridLayout *gridLayout = nullptr;       ///< 主网格布局管理器
    MainArea*         main_area      = nullptr;                ///< 主内容区域控件
    
    // 边缘拖拽相关
    static const int EDGE_WIDTH = 8;         ///< 边缘拖拽区域宽度
    bool m_dragging = false;                 ///< 是否正在拖拽
    QPoint m_dragStartPos;                   ///< 拖拽开始位置
    
    // 鼠标位置检测
    enum EdgeType {
        None = 0,
        Left = 1,
        Right = 2, 
        Top = 4,
        Bottom = 8,
        TopLeft = Top | Left,
        TopRight = Top | Right,
        BottomLeft = Bottom | Left,
        BottomRight = Bottom | Right
    };
    
    EdgeType getEdgeType(const QPoint &pos) const;
};

#endif // BORDERLESSWINDOW_H
