#ifndef HESICONBUTTONPRIVATE_H
#define HESICONBUTTONPRIVATE_H

#include <QColor>
#include <QObject>
#include <QPixmap>

#include "common/common_defs.h"
#include "stdafx.h"
class HesIconButton;
class HesIconButtonPrivate : public QObject
{
    Q_OBJECT
    Q_D_DECLARE_POINTER(HesIconButton)
    Q_PRIVATE_CREATE(int, BorderRadius)
    Q_PRIVATE_CREATE(qreal, Opacity);
    Q_PRIVATE_CREATE(HesIconType::IconName, Awesome)
    Q_PRIVATE_CREATE(QColor, LightHoverColor);
    Q_PRIVATE_CREATE(QColor, DarkHoverColor);
    Q_PRIVATE_CREATE(QColor, LightIconColor);
    Q_PRIVATE_CREATE(QColor, DarkIconColor);
    Q_PRIVATE_CREATE(QColor, LightHoverIconColor);
    Q_PRIVATE_CREATE(QColor, DarkHoverIconColor);
    Q_PRIVATE_CREATE(bool, IsSelected);
    Q_DEFINE_NOTIFY_PROPERTY(int, HoverAlpha)
public:
    explicit HesIconButtonPrivate(QObject* parent = nullptr);
    ~HesIconButtonPrivate();

private:
    QPixmap _iconPix;
    bool _isAlphaAnimationFinished{true};
    HesThemeType::ThemeMode _themeMode;
};

#endif // HESICONBUTTONPRIVATE_H
