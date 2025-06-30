#ifndef BORDERLESSWINDOW_P_H_
#define BORDERLESSWINDOW_P_H_

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QPoint>
#include <QRect>

#ifdef Q_OS_WIN
#include <windows.h>
#include <dwmapi.h>
#include <windowsx.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "user32.lib")
#endif

class MainArea;
class BorderlessWindow;

/**
 * @brief BorderlessWindow的私有实现类 (PIMPL设计模式)
 * 
 * 将所有实现细节封装在私有类中，提供更好的二进制兼容性和编译速度
 */
class BorderlessWindowPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(BorderlessWindow)

public:
    explicit BorderlessWindowPrivate(BorderlessWindow *parent);
    ~BorderlessWindowPrivate();

    void initializeWindow();

#ifdef Q_OS_WIN
    void setupWindowAttributes();
    bool handleNativeEvent(const QByteArray &eventType, void *message, qintptr *result);
    LRESULT hitTest(const QPoint &pos) const;
#endif

private:
    BorderlessWindow *q_ptr;
    QGridLayout *gridLayout;
    MainArea *mainArea;

    // 拖拽相关常量
    static const int EDGE_WIDTH = 8; // 边缘拖拽区域宽度
    static const int TITLE_BAR_BUTTON_WIDTH = 150; // 标题栏按钮区域宽度，根据实际情况调整
};

#endif // BORDERLESSWINDOW_P_H_
