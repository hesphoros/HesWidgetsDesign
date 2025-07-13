#ifndef HESTOOLBUTTONPRIVATE_H
#define HESTOOLBUTTONPRIVATE_H

#include <QObject>

#include "stdafx.h"
class HesToolButton;
class HesToolButtonStyle;
class HesToolButtonPrivate : public QObject
{
    Q_OBJECT
    Q_D_DECLARE_POINTER(HesToolButton)
public:
    explicit HesToolButtonPrivate(QObject* parent = nullptr);
    ~HesToolButtonPrivate();

private:
    HesToolButtonStyle* _toolButtonStyle{nullptr};
};

#endif // HESTOOLBUTTONPRIVATE_H
