void TitleBarButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置按钮背景色
    if (this->isHovered) {
        painter.fillRect(rect(), QColor(220, 220, 220));
    } else {
        painter.fillRect(rect(), QColor(240, 240, 240));
    }

    // 绘制 Fluent SVG 图标
    QPixmap icon = this->isHovered ? this->hoveredIcon : this->defaultIcon;
    painter.drawPixmap((width() - icon.width()) / 2, (height() - icon.height()) / 2, icon);

    QWidget::paintEvent(event);
}

void TitleBarButton::enterEvent(QEvent *event) {
    this->isHovered = true;
    this->update();
    QWidget::enterEvent(event);
}

void TitleBarButton::leaveEvent(QEvent *event) {
    this->isHovered = false;
    this->update();
    QWidget::leaveEvent(event);
}

void TitleBarButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->setStyleSheet("transform: scale(0.95);");
    }
    QWidget::mousePressEvent(event);
}

void TitleBarButton::mouseReleaseEvent(QMouseEvent *event) {
    this->setStyleSheet("transform: scale(1);");
    QWidget::mouseReleaseEvent(event);
}