#ifndef HESMENUPRIVATE_H
#define HESMENUPRIVATE_H

#include <QObject>
#include <QPixmap>
#include <QPoint>

#include "stdafx.h"
class HesMenu;
class HesMenuStyle;
class HesMenuPrivate : public QObject
{
    Q_OBJECT
    Q_D_DECLARE_POINTER(HesMenu)
    Q_DEFINE_NOTIFY_PROPERTY(int, AnimationImagePosY)
public:
    explicit HesMenuPrivate(QObject* parent = nullptr);
    ~HesMenuPrivate();

private:
    QPixmap         _animationPix;
    bool            _isCloseAnimation{false};
    QPoint          _mousePressPoint;
    HesMenuStyle*   _menuStyle{nullptr};
};



#endif // HESMENUPRIVATE_H