void TitleBar::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 设置标题栏背景色
    painter.fillRect(rect(), QColor(240, 240, 240));

    // 绘制标题文字
    QFont font("Segoe UI", 16);
    painter.setFont(font);
    painter.setPen(QColor(0, 0, 0));
    painter.drawText(rect(), Qt::AlignCenter, this->windowTitle());

    QWidget::paintEvent(event);
}

void TitleBar::enterEvent(QEvent *event) {
    this->setStyleSheet("background-color: rgba(200, 200, 200, 0.8); border-radius: 8px;");
    QWidget::enterEvent(event);
}

void TitleBar::leaveEvent(QEvent *event) {
    this->setStyleSheet("background-color: transparent;");
    QWidget::leaveEvent(event);
}