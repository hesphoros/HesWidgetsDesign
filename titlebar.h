// TitleBar.h
#pragma once

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>

class TitleBar : public QWidget
{
Q_OBJECT
public:
    explicit TitleBar(const QString& title = QString(), QWidget* parent = nullptr);

    void setTitle(const QString& title);

signals:
    void minimizeClicked();
    void maximizeClicked();
    void restoreClicked();
    void closeClicked();

private slots:
    void onMinimize();
    void onMaximizeRestore();
    void onClose();

private:
    QLabel*         m_titleLabel;
    QToolButton*    m_minBtn;
    QToolButton*    m_maxBtn;
    QToolButton*    m_closeBtn;
    bool            m_isMaximized;
};
