//
// Created by Ming on 2025/6/30.
//

#pragma once

#include "FramelessWindow.h"

class MainWindow : public FramelessWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event) override;
};


