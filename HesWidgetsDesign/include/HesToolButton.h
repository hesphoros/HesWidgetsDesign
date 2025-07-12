#ifndef HESTOOLBUTTON_H
#define HESTOOLBUTTON_H

#include <QToolButton>

class HesToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit HesToolButton(QWidget* parent = nullptr);
    ~HesToolButton() override;

signals:

public slots:
};

#endif // HESTOOLBUTTON_H