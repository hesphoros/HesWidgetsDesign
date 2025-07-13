#ifndef HESICONBUTTON_H
#define HESICONBUTTON_H


#include <QPushButton>

#include "common/common_defs.h"
#include "stdafx.h"
class HesIconButtonPrivate;
class HES_EXPORT HesIconButton : public QPushButton
{
    Q_OBJECT
    Q_DECLARE_PIMPL(HesIconButton)
    Q_PROPERTY_DEFINE_MEMBER_H(int, BorderRadius)
    Q_PROPERTY_DEFINE_MEMBER_H(qreal, Opacity)
    Q_PROPERTY_DEFINE_MEMBER_H(QColor, LightHoverColor)
    Q_PROPERTY_DEFINE_MEMBER_H(QColor, DarkHoverColor)
    Q_PROPERTY_DEFINE_MEMBER_H(QColor, LightIconColor)
    Q_PROPERTY_DEFINE_MEMBER_H(QColor, DarkIconColor)
    Q_PROPERTY_DEFINE_MEMBER_H(QColor, LightHoverIconColor);
    Q_PROPERTY_DEFINE_MEMBER_H(QColor, DarkHoverIconColor);
    Q_PROPERTY_DEFINE_MEMBER_H(bool, IsSelected);

public:
    HesIconButton(QPixmap pix, QWidget* parent = nullptr);
    HesIconButton(HesIconType::IconName awesome, QWidget* parent = nullptr);
    HesIconButton(HesIconType::IconName awesome, int pixelSize, QWidget* parent = nullptr);
    HesIconButton(HesIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight, QWidget* parent = nullptr);
    ~HesIconButton();
    void setAwesome(HesIconType::IconName awesome);
    HesIconType::IconName getAwesome() const;

    void setPixmap(QPixmap pix);

protected:
    virtual bool event(QEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
};




#endif // HESICONBUTTON_H