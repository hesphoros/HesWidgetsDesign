#include "minimizebutton.h"

MinimizeButton::MinimizeButton(QWidget *parent)
    : TitleBarButton{parent}
{
    // 设置现代化按钮尺寸
    this->setFixedSize(46, 32);
    this->setIcon(QPixmap(":/icon/minimize_black.svg"));
      // 更现代的 Fluent Design 按钮样式
    this->setStyleSheet(
        "MinimizeButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    border-radius: 8px;"
        "    margin: 1px;"
        "}"
        "MinimizeButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 rgba(0, 0, 0, 0.08),"
        "        stop:1 rgba(0, 0, 0, 0.12));"
        "    border: 1px solid rgba(255, 255, 255, 0.5);"
        "}"
        "MinimizeButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 rgba(0, 0, 0, 0.15),"
        "        stop:1 rgba(0, 0, 0, 0.20));"
        "    border: 1px solid rgba(255, 255, 255, 0.3);"
        "}"
    );
    
    connect(this, &MinimizeButton::clicked, this->window(), &QWidget::showMinimized);
}
