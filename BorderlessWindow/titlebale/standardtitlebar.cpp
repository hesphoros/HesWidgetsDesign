#include "standardtitlebar.h"

StandardTitleBar::StandardTitleBar(QWidget *parent)
    : SimpleTitleBar{parent},
    icon_label{new QLabel(this)},
    title_label{new TitleTextLabel(this)}

{
    // 优化标题栏布局和高度
    this->horizontal_layout->setContentsMargins(16, 8, 8, 8);
    this->setFixedHeight(48); // 现代化标题栏高度    // 修复标题栏样式，移除调试边框
    this->setStyleSheet(
        "StandardTitleBar {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 rgba(255, 255, 255, 0.95),"
        "        stop:0.3 rgba(252, 252, 255, 0.9),"
        "        stop:0.7 rgba(248, 248, 252, 0.85),"
        "        stop:1 rgba(245, 245, 250, 0.8));"
        "    border-top-left-radius: 11px;"
        "    border-top-right-radius: 11px;"
        "    border-bottom: 1px solid rgba(180, 180, 180, 0.4);"
        "    border-left: none;"
        "    border-right: none;"
        "    border-top: none;"
        "}"
    );    // 修复图标挤压问题 - 使用更合理的尺寸和设置
    this->icon_label->setFixedSize(24, 24); // 合适的图标容器尺寸
    this->icon_label->setScaledContents(false); // 关闭缩放，保持原始比例
    this->icon_label->setAlignment(Qt::AlignCenter);
    this->icon_label->setStyleSheet("QLabel { margin: 0px; padding: 0px; }"); // 清除多余边距
    
    // 现代化字体设置
    QFont titleFont;
    titleFont.setFamily("Segoe UI");
    titleFont.setPointSize(14);
    titleFont.setWeight(QFont::Normal);
    this->title_label->setFont(titleFont);
    
    this->horizontal_layout->insertWidget(0, title_label);
    this->horizontal_layout->insertWidget(0, icon_label);

    // 设置文字颜色
    QPalette p(this->title_label->palette());
    p.setBrush(QPalette::ColorRole::WindowText, QColor(32, 32, 32));
    this->title_label->setPalette(p);    // 设置默认图标和标题 - 使用合适大小的图标
    icon_label->setPixmap(this->style()->standardIcon(QStyle::StandardPixmap::SP_ComputerIcon).pixmap(20, 20));
    title_label->setText(QApplication::applicationName());
}

void StandardTitleBar::setIcon(const QPixmap &icon)
{
    this->icon_label->setPixmap(icon);
}

void StandardTitleBar::setTitle(const QString &title)
{
    this->title_label->setText(title);
}

void StandardTitleBar::setTitleFont(const QFont &font)
{
    this->title_label->setFont(font);
}

void StandardTitleBar::setTitleColor(const QColor &titleColor)
{
    this->titlt_text_color = titleColor;
    this->title_label->update();
}

QWidget *StandardTitleBar::iconLabel() const
{
    return this->icon_label;
}

StandardTitleBar::TitleTextLabel *StandardTitleBar::titleLabel() const
{
    return this->title_label;
}

void StandardTitleBar::TitleTextLabel::setIsClearBeforeNewPaint(bool isClear)
{
    this->is_clear_before_new_paint = isClear;
}

void StandardTitleBar::TitleTextLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::RenderHint::Antialiasing | QPainter::RenderHint::TextAntialiasing);
    if (this->is_clear_before_new_paint)
    {
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        painter.eraseRect(this->rect());
    }
    QLabel::paintEvent(event);
}
