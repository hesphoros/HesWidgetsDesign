//
// Created by Ming on 2025/6/30.
//

#include "MainWindow.h"
#include "titlebar.h"
#include <QPainter>

MainWindow::MainWindow(QWidget* parent) : FramelessWindow(parent)
{
    auto titleBar = new TitleBar("我的应用", this);
    connect(titleBar, &TitleBar::minimizeClicked, this, &MainWindow::showMinimized);
    connect(titleBar, &TitleBar::maximizeClicked, this, &MainWindow::showMaximized);
    connect(titleBar, &TitleBar::restoreClicked, this, &MainWindow::showNormal);
    connect(titleBar, &TitleBar::closeClicked, this, &MainWindow::close);
    setTitleBar(titleBar);
    // 2) 给 MainWindow 设置一个垂直布局
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);     // 去掉边距
    mainLayout->setSpacing(0);

    // 3) 把 titleBar 加进布局
    mainLayout->addWidget(titleBar);

    // 4) 下面可以放一个 central widget，做你主要的内容
    auto central = new QWidget(this);
    // （这里你可以给 central 再设置子布局和子控件）
    mainLayout->addWidget(central);

    // 5) 应用布局到 MainWindow
    setLayout(mainLayout);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::gray);
    p.drawRect(rect());
}
