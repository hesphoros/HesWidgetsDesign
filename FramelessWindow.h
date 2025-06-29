#pragma once
#include <QWidget>
#include <memory>

class FramelessWindow : public QWidget {
    Q_OBJECT
public:
    explicit FramelessWindow(QWidget* parent = nullptr);
    ~FramelessWindow();
    
    // 禁用拷贝
    FramelessWindow(const FramelessWindow&) = delete;
    FramelessWindow& operator=(const FramelessWindow&) = delete;
    
    void setTitleBar(QWidget* titleBar);

protected:
    bool nativeEvent(const QByteArray& eventType, void* message, qint64* result) override;
    bool event(QEvent* event) override;

private:
    class FramelessWindowPrivate;
    std::unique_ptr<FramelessWindowPrivate> d_ptr;
};