#include "borderlesswindow.h"
#include "borderlesswindow_p.h"
#include "mainarea.h"
#include <QMouseEvent>
#include <QApplication>

BorderlessWindow::BorderlessWindow(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new BorderlessWindowPrivate(this))
{
    Q_D(BorderlessWindow);
    d->initializeWindow();
}

BorderlessWindow::~BorderlessWindow()
{
}

QWidget *BorderlessWindow::qWidgetUseInSetupUi()
{
    Q_D(BorderlessWindow);
    return d->mainArea->customerAreaWidget();
}

void BorderlessWindow::setWindowTitle(const QString &title)
{
    Q_D(BorderlessWindow);
    d->mainArea->titleBar()->setTitle(title);
}

void BorderlessWindow::setWindowIcon(const QPixmap &icon)
{
    Q_D(BorderlessWindow);
    d->mainArea->titleBar()->setIcon(icon);
}

void BorderlessWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::Type::WindowStateChange)
    {
        Q_D(BorderlessWindow);
        QWindowStateChangeEvent *stateChangeEvent = static_cast<QWindowStateChangeEvent *>(event);
        // 最大化
        if (this->windowState() & Qt::WindowState::WindowMaximized)
        {
            emit d->mainArea->titleBar()->maximizeButton()->stateChange(MaximizeButton::State::MAXIMIZE);
        }
        // 最大化后还原
        else if (stateChangeEvent->oldState() & Qt::WindowState::WindowMaximized && !(this->windowState() & Qt::WindowState::WindowMaximized))
        {
            emit d->mainArea->titleBar()->maximizeButton()->stateChange(MaximizeButton::State::NORMAL);
        }
    }
    this->update();
    QWidget::changeEvent(event);
}

void BorderlessWindow::showEvent(QShowEvent *event) {
    Q_D(BorderlessWindow);
    QWidget::showEvent(event);
#ifdef Q_OS_WIN
    d->setupWindowAttributes();
#endif
}

void BorderlessWindow::paintEvent(QPaintEvent *event) {
    // 移除调试边框，保持窗口简洁
    QWidget::paintEvent(event);
}

#ifdef Q_OS_WIN
bool BorderlessWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    Q_D(BorderlessWindow);
    return d->handleNativeEvent(eventType, message, result) || 
           QWidget::nativeEvent(eventType, message, result);
}
#endif
