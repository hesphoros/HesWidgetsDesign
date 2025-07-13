#include "HesToolButton.h"

#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>

#include "DeveloperComponents/HesToolButtonStyle.h"
#include "HesIcon.h"
#include "HesMenu.h"
#include "HesToolButtonPrivate.h"

HesToolButton::HesToolButton(QWidget* parent)
    : QToolButton(parent), d_ptr(new HesToolButtonPrivate())
{
    Q_D(HesToolButton);
    d->q_ptr = this;
    setIconSize(QSize(22, 22));
    setPopupMode(QToolButton::InstantPopup);
    d->_toolButtonStyle = new HesToolButtonStyle(style());
    setStyle(d->_toolButtonStyle);
}

HesToolButton::~HesToolButton()
{
}

void HesToolButton::setBorderRadius(int borderRadius)
{
    Q_D(HesToolButton);
    d->_toolButtonStyle->setBorderRadius(borderRadius);
    Q_EMIT pBorderRadiusChanged();
}

int HesToolButton::getBorderRadius() const
{
    Q_D(const HesToolButton);
    return d->_toolButtonStyle->getBorderRadius();
}

void HesToolButton::setIsSelected(bool isSelected)
{
    Q_D(HesToolButton);
    d->_toolButtonStyle->setIsSelected(isSelected);
    Q_EMIT pIsSelectedChanged();
}

bool HesToolButton::getIsSelected() const
{
    Q_D(const HesToolButton);
    return d->_toolButtonStyle->getIsSelected();
}

void HesToolButton::setIsTransparent(bool isTransparent)
{
    Q_D(HesToolButton);
    d->_toolButtonStyle->setIsTransparent(isTransparent);
    update();
}

bool HesToolButton::getIsTransparent() const
{
    Q_D(const HesToolButton);
    return d->_toolButtonStyle->getIsTransparent();
}

void HesToolButton::setMenu(HesMenu* menu)
{
    if (!menu || menu == this->menu())
    {
        return;
    }
    menu->setMenuItemHeight(27);
    QToolButton::setMenu(menu);
    menu->installEventFilter(this);
}

void HesToolButton::setElaIcon(ElaIconType::IconName icon)
{
    setProperty("ElaIconType", QChar((unsigned short)icon));
    setIcon(ElaIcon::getInstance()->getElaIcon(ElaIconType::Broom, 1));
}

bool HesToolButton::eventFilter(QObject* watched, QEvent* event)
{
    Q_D(HesToolButton);
    if (watched == menu())
    {
        switch (event->type())
        {
        case QEvent::Show:
        {
            //指示器动画
            QPropertyAnimation* rotateAnimation = new QPropertyAnimation(d->_toolButtonStyle, "pExpandIconRotate");
            connect(rotateAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
                update();
            });
            rotateAnimation->setDuration(300);
            rotateAnimation->setEasingCurve(QEasingCurve::InOutSine);
            rotateAnimation->setStartValue(d->_toolButtonStyle->getExpandIconRotate());
            rotateAnimation->setEndValue(-180);
            rotateAnimation->start(QAbstractAnimation::DeleteWhenStopped);
            break;
        }
        case QEvent::Hide:
        {
            //指示器动画
            QPropertyAnimation* rotateAnimation = new QPropertyAnimation(d->_toolButtonStyle, "pExpandIconRotate");
            connect(rotateAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
                update();
            });
            rotateAnimation->setDuration(300);
            rotateAnimation->setEasingCurve(QEasingCurve::InOutSine);
            rotateAnimation->setStartValue(d->_toolButtonStyle->getExpandIconRotate());
            rotateAnimation->setEndValue(0);
            rotateAnimation->start(QAbstractAnimation::DeleteWhenStopped);
            QMouseEvent focusEvent(QEvent::MouseButtonPress, QPoint(-1, -1), QPoint(-1, -1), Qt::NoButton, Qt::NoButton, Qt::NoModifier);
            QApplication::sendEvent(parentWidget(), &focusEvent);
            break;
        }
        default:
        {
            break;
        }
        }
    }
    return QObject::eventFilter(watched, event);
}
