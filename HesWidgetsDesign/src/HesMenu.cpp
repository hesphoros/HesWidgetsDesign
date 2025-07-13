#include "HesMenu.h"

#include <QApplication>
#include <QCloseEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QVBoxLayout>

#include "DeveloperComponents/HesMenuStyle.h"
#include "private/HesMenuPrivate.h"
HesMenu::HesMenu(QWidget* parent)
    : QMenu(parent), d_ptr(new HesMenuPrivate())
{
    Q_D(HesMenu);
    d->q_ptr = this;
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setObjectName("HesMenu");
    d->_menuStyle = new HesMenuStyle(style());
    setStyle(d->_menuStyle);
    d->_pAnimationImagePosY = 0;
}

HesMenu::HesMenu(const QString& title, QWidget* parent)
    : HesMenu(parent)
{
    setTitle(title);
}

HesMenu::~HesMenu()
{
}

void HesMenu::setMenuItemHeight(int menuItemHeight)
{
    Q_D(HesMenu);
    d->_menuStyle->setMenuItemHeight(menuItemHeight);
}

int HesMenu::getMenuItemHeight() const
{
    Q_D(const HesMenu);
    return d->_menuStyle->getMenuItemHeight();
}

QAction* HesMenu::addMenu(QMenu* menu)
{
    return QMenu::addMenu(menu);
}

HesMenu* HesMenu::addMenu(const QString& title)
{
    HesMenu* menu = new HesMenu(title, this);
    QMenu::addAction(menu->menuAction());
    return menu;
}

HesMenu* HesMenu::addMenu(const QIcon& icon, const QString& title)
{
    HesMenu* menu = new HesMenu(title, this);
    menu->setIcon(icon);
    QMenu::addAction(menu->menuAction());
    return menu;
}

HesMenu* HesMenu::addMenu(HesIconType::IconName icon, const QString& title)
{
    HesMenu* menu = new HesMenu(title, this);
    QMenu::addAction(menu->menuAction());
    menu->menuAction()->setProperty("HesIconType", QChar((unsigned short)icon));
    return menu;
}

QAction* HesMenu::addHesIconAction(HesIconType::IconName icon, const QString& text)
{
    QAction* action = new QAction(text, this);
    action->setProperty("HesIconType", QChar((unsigned short)icon));
    QMenu::addAction(action);
    return action;
}

QAction* HesMenu::addHesIconAction(HesIconType::IconName icon, const QString& text, const QKeySequence& shortcut)
{
    QAction* action = new QAction(text, this);
    action->setShortcut(shortcut);
    action->setProperty("HesIconType", QChar((unsigned short)icon));
    QMenu::addAction(action);
    return action;
}

bool HesMenu::isHasChildMenu() const
{
    QList<QAction*> actionList = this->actions();
    for (auto action : actionList)
    {
        if (action->isSeparator())
        {
            continue;
        }
        if (action->menu())
        {
            return true;
        }
    }
    return false;
}

bool HesMenu::isHasIcon() const
{
    QList<QAction*> actionList = this->actions();
    for (auto action : actionList)
    {
        if (action->isSeparator())
        {
            continue;
        }
        QMenu* menu = action->menu();
        if (menu && (!menu->icon().isNull() || !menu->property("HesIconType").toString().isEmpty()))
        {
            return true;
        }
        if (!action->icon().isNull() || !action->property("HesIconType").toString().isEmpty())
        {
            return true;
        }
    }
    return false;
}

void HesMenu::showEvent(QShowEvent* event)
{
    Q_EMIT menuShow();
    Q_D(HesMenu);
    //消除阴影偏移
    move(this->pos().x() - 6, this->pos().y());
    if (!d->_animationPix.isNull())
    {
        d->_animationPix = QPixmap();
    }
    d->_animationPix = this->grab(this->rect());
    QPropertyAnimation* posAnimation = new QPropertyAnimation(d, "pAnimationImagePosY");
    connect(posAnimation, &QPropertyAnimation::finished, this, [=]() {
        d->_animationPix = QPixmap();
        update();
    });
    connect(posAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        update();
    });
    posAnimation->setEasingCurve(QEasingCurve::OutCubic);
    posAnimation->setDuration(400);
    int targetPosY = height();
    if (targetPosY > 160)
    {
        if (targetPosY < 320)
        {
            targetPosY = 160;
        }
        else
        {
            targetPosY /= 2;
        }
    }

    if (pos().y() + d->_menuStyle->getMenuItemHeight() + 9 >= QCursor::pos().y())
    {
        posAnimation->setStartValue(-targetPosY);
    }
    else
    {
        posAnimation->setStartValue(targetPosY);
    }

    posAnimation->setEndValue(0);
    posAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    QMenu::showEvent(event);
}

void HesMenu::paintEvent(QPaintEvent* event)
{
    Q_D(HesMenu);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    if (!d->_animationPix.isNull())
    {
        painter.drawPixmap(QRect(0, d->_pAnimationImagePosY, width(), height()), d->_animationPix);
    }
    else
    {
        QMenu::paintEvent(event);
    }
}
