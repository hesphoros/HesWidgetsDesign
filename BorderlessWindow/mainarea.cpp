#include "mainarea.h"

MainArea::MainArea(QWidget *parent)
    : QWidget{parent},
      vertical_layout{new QVBoxLayout(this)},
      title_bar{new StandardTitleBar(this)},
      customer_area_widget{new QWidget(this)}
{
    // 简化布局间距
    this->vertical_layout->setContentsMargins(6, 6, 6, 6);
    this->vertical_layout->setSpacing(0);
    this->vertical_layout->addWidget(this->title_bar);
    this->vertical_layout->addWidget(this->customer_area_widget);
      // 简化客户区域样式，避免嵌套效果
    this->customer_area_widget->setStyleSheet(
        "QWidget {"
        "    background-color: rgba(255, 255, 255, 0.7);"
        "    border-bottom-left-radius: 10px;"
        "    border-bottom-right-radius: 10px;"
        "    border: none;"
        "}"
    );
}

QWidget *MainArea::customerAreaWidget()
{
    return this->customer_area_widget;
}

StandardTitleBar *MainArea::titleBar()
{
    return this->title_bar;
}

void MainArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (!this->window()->isMaximized())
    {
        // 绘制主内容区域背景，与亚克力背景协调
        QPainterPath mainPath;
        mainPath.addRoundedRect(rect().adjusted(1, 1, -1, -1), 11, 11);
        
        // 使用半透明背景，让亚克力效果透过
        QLinearGradient bgGradient(0, 0, 0, height());
        bgGradient.setColorAt(0, QColor(255, 255, 255, 180));
        bgGradient.setColorAt(1, QColor(248, 248, 248, 160));
        
        painter.fillPath(mainPath, bgGradient);
        
        // 轻微边框
        QPen borderPen(QColor(200, 200, 200, 100), 1);
        painter.setPen(borderPen);
        painter.drawPath(mainPath);
    }
    else
    {
        // 最大化时的简洁背景
        painter.fillRect(rect(), QColor(252, 252, 252, 200));
    }
    
    QWidget::paintEvent(event);
}
