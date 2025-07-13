#include "HesIconButton.h"

#include <QEvent>
#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include "HesTheme.h"
#include "HesIconButtonPrivate.h"

Q_PROPERTY_DEFINE_MEMBER_CPP(HesIconButton, int, BorderRadius)
Q_PROPERTY_DEFINE_MEMBER_CPP(HesIconButton, qreal, Opacity);
Q_PROPERTY_DEFINE_MEMBER_CPP(HesIconButton, QColor, LightHoverColor);
Q_PROPERTY_DEFINE_MEMBER_CPP(HesIconButton, QColor, DarkHoverColor);
Q_PROPERTY_DEFINE_MEMBER_CPP(HesIconButton, QColor, LightIconColor);
Q_PROPERTY_DEFINE_MEMBER_CPP(HesIconButton, QColor, DarkIconColor);
Q_PROPERTY_DEFINE_MEMBER_CPP(HesIconButton, QColor, LightHoverIconColor);
Q_PROPERTY_DEFINE_MEMBER_CPP(HesIconButton, QColor, DarkHoverIconColor);
Q_PROPERTY_DEFINE_MEMBER_CPP(HesIconButton, bool, IsSelected);

HesIconButton::HesIconButton(QPixmap pix, QWidget* parent)
    : QPushButton(parent), d_ptr(new HesIconButtonPrivate())
{
    Q_D(HesIconButton);
    d->q_ptr = this;
    d->_iconPix = pix.copy();
    d->_pHoverAlpha = 0;
    d->_pOpacity = 1;
    d->_pLightHoverColor = HesThemeColor(HesThemeType::Light, BasicHoverAlpha);
    d->_pDarkHoverColor = HesThemeColor(HesThemeType::Dark, BasicHoverAlpha);
    d->_pLightIconColor = HesThemeColor(HesThemeType::Light, BasicText);
    d->_pDarkIconColor = HesThemeColor(HesThemeType::Dark, BasicText);
    d->_pLightHoverIconColor = HesThemeColor(HesThemeType::Light, BasicText);
    d->_pDarkHoverIconColor = HesThemeColor(HesThemeType::Dark, BasicText);
    d->_pIsSelected = false;
    d->_pBorderRadius = 0;
    d->_themeMode = hesTheme->getThemeMode();
    connect(this, &HesIconButton::pIsSelectedChanged, this, [=]() { update(); });
    connect(hesTheme, &HesTheme::themeModeChanged, this, [=](HesThemeType::ThemeMode themeMode) { d->_themeMode = themeMode; });
}

HesIconButton::HesIconButton(HesIconType::IconName awesome, QWidget* parent)
    : QPushButton(parent), d_ptr(new HesIconButtonPrivate())
{
    Q_D(HesIconButton);
    d->q_ptr = this;
    d->_pHoverAlpha = 0;
    d->_pOpacity = 1;
    d->_pLightHoverColor = HesThemeColor(HesThemeType::Light, BasicHoverAlpha);
    d->_pDarkHoverColor = HesThemeColor(HesThemeType::Dark, BasicHoverAlpha);
    d->_pLightIconColor = HesThemeColor(HesThemeType::Light, BasicText);
    d->_pDarkIconColor = HesThemeColor(HesThemeType::Dark, BasicText);
    d->_pLightHoverIconColor = HesThemeColor(HesThemeType::Light, BasicText);
    d->_pDarkHoverIconColor = HesThemeColor(HesThemeType::Dark, BasicText);
    d->_pIsSelected = false;
    d->_pBorderRadius = 0;
    d->_themeMode = hesTheme->getThemeMode();
    QFont iconFont = QFont("HesAwesome");
    iconFont.setPixelSize(15);
    this->setFont(iconFont);
    d->_pAwesome = awesome;
    this->setText(QChar((unsigned short)awesome));
    connect(this, &HesIconButton::pIsSelectedChanged, this, [=]() { update(); });
    connect(hesTheme, &HesTheme::themeModeChanged, this, [=](HesThemeType::ThemeMode themeMode) { d->_themeMode = themeMode; });
}

HesIconButton::HesIconButton(HesIconType::IconName awesome, int pixelSize, QWidget* parent)
    : QPushButton(parent), d_ptr(new HesIconButtonPrivate())
{
    Q_D(HesIconButton);
    d->q_ptr = this;
    d->_pHoverAlpha = 0;
    d->_pOpacity = 1;
    d->_pLightHoverColor = HesThemeColor(HesThemeType::Light, BasicHoverAlpha);
    d->_pDarkHoverColor = HesThemeColor(HesThemeType::Dark, BasicHoverAlpha);
    d->_pLightIconColor = HesThemeColor(HesThemeType::Light, BasicText);
    d->_pDarkIconColor = HesThemeColor(HesThemeType::Dark, BasicText);
    d->_pLightHoverIconColor = HesThemeColor(HesThemeType::Light, BasicText);
    d->_pDarkHoverIconColor = HesThemeColor(HesThemeType::Dark, BasicText);
    d->_pIsSelected = false;
    d->_pBorderRadius = 0;
    d->_themeMode = hesTheme->getThemeMode();
    QFont iconFont = QFont("HesAwesome");
    iconFont.setPixelSize(pixelSize);
    this->setFont(iconFont);
    d->_pAwesome = awesome;
    this->setText(QChar((unsigned short)awesome));
    connect(this, &HesIconButton::pIsSelectedChanged, this, [=]() { update(); });
    connect(hesTheme, &HesTheme::themeModeChanged, this, [=](HesThemeType::ThemeMode themeMode) { d->_themeMode = themeMode; });
}

HesIconButton::HesIconButton(HesIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight, QWidget* parent)
    : QPushButton(parent), d_ptr(new HesIconButtonPrivate())
{
    Q_D(HesIconButton);
    d->q_ptr = this;
    d->_pHoverAlpha = 0;
    d->_pOpacity = 1;
    d->_pLightHoverColor = HesThemeColor(HesThemeType::Light, BasicHoverAlpha);
    d->_pDarkHoverColor = HesThemeColor(HesThemeType::Dark, BasicHoverAlpha);
    d->_pLightIconColor = HesThemeColor(HesThemeType::Light, BasicText);
    d->_pDarkIconColor = HesThemeColor(HesThemeType::Dark, BasicText);
    d->_pLightHoverIconColor = HesThemeColor(HesThemeType::Light, BasicText);
    d->_pDarkHoverIconColor = HesThemeColor(HesThemeType::Dark, BasicText);
    d->_pIsSelected = false;
    d->_pBorderRadius = 0;
    d->_themeMode = hesTheme->getThemeMode();
    QFont iconFont = QFont("HesAwesome");
    iconFont.setPixelSize(pixelSize);
    this->setFont(iconFont);
    d->_pAwesome = awesome;
    this->setText(QChar((unsigned short)awesome));
    this->setFixedSize(fixedWidth, fixedHeight);
    connect(this, &HesIconButton::pIsSelectedChanged, this, [=]() { update(); });
    connect(hesTheme, &HesTheme::themeModeChanged, this, [=](HesThemeType::ThemeMode themeMode) { d->_themeMode = themeMode; });
}

HesIconButton::~HesIconButton()
{
}

void HesIconButton::setAwesome(HesIconType::IconName awesome)
{
    Q_D(HesIconButton);
    d->_pAwesome = awesome;
    this->setText(QChar((unsigned short)awesome));
}

HesIconType::IconName HesIconButton::getAwesome() const
{
    return this->d_ptr->_pAwesome;
}

void HesIconButton::setPixmap(QPixmap pix)
{
    Q_D(HesIconButton);
    d->_iconPix = pix.copy();
}

bool HesIconButton::event(QEvent* event)
{
    Q_D(HesIconButton);
    switch (event->type())
    {
    case QEvent::Enter:
    {
        if (isEnabled() && !d->_pIsSelected)
        {
            d->_isAlphaAnimationFinished = false;
            QPropertyAnimation* alphaAnimation = new QPropertyAnimation(d, "pHoverAlpha");
            connect(alphaAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
                update();
            });
            connect(alphaAnimation, &QPropertyAnimation::finished, this, [=]() {
                d->_isAlphaAnimationFinished = true;
            });
            alphaAnimation->setDuration(175);
            alphaAnimation->setStartValue(d->_pHoverAlpha);
            alphaAnimation->setEndValue(d->_themeMode == HesThemeType::Light ? d->_pLightHoverColor.alpha() : d->_pDarkHoverColor.alpha());
            alphaAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        break;
    }
    case QEvent::Leave:
    {
        if (isEnabled() && !d->_pIsSelected)
        {
            d->_isAlphaAnimationFinished = false;
            QPropertyAnimation* alphaAnimation = new QPropertyAnimation(d, "pHoverAlpha");
            connect(alphaAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
                update();
            });
            connect(alphaAnimation, &QPropertyAnimation::finished, this, [=]() {
                d->_isAlphaAnimationFinished = true;
            });
            alphaAnimation->setDuration(175);
            alphaAnimation->setStartValue(d->_pHoverAlpha);
            alphaAnimation->setEndValue(0);
            alphaAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        }
        break;
    }
    default:
    {
        break;
    }
    }
    return QPushButton::event(event);
}

void HesIconButton::paintEvent(QPaintEvent* event)
{
    Q_D(HesIconButton);
    QPainter painter(this);
    painter.save();
    painter.setOpacity(d->_pOpacity);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::NoPen);
    if (d->_isAlphaAnimationFinished || d->_pIsSelected)
    {
        painter.setBrush(d->_pIsSelected ? d->_themeMode == HesThemeType::Light ? d->_pLightHoverColor : d->_pDarkHoverColor
                         : isEnabled()   ? underMouse() ? d->_themeMode == HesThemeType::Light ? d->_pLightHoverColor : d->_pDarkHoverColor : Qt::transparent
                                         : Qt::transparent);
    }
    else
    {
        QColor hoverColor = d->_themeMode == HesThemeType::Light ? d->_pLightHoverColor : d->_pDarkHoverColor;
        hoverColor.setAlpha(d->_pHoverAlpha);
        painter.setBrush(hoverColor);
    }
    painter.drawRoundedRect(rect(), d->_pBorderRadius, d->_pBorderRadius);
    // 图标绘制
    if (!d->_iconPix.isNull())
    {
        QPainterPath path;
        path.addEllipse(rect());
        painter.setClipPath(path);
        painter.drawPixmap(rect(), d->_iconPix);
    }
    else
    {
        painter.setPen(isEnabled() ? d->_themeMode == HesThemeType::Light ? underMouse() ? d->_pLightHoverIconColor : d->_pLightIconColor : underMouse() ? d->_pDarkHoverIconColor
                                                                                                                                                         : d->_pDarkIconColor
                                   : HesThemeColor(d->_themeMode, BasicTextDisable));
        painter.drawText(rect(), Qt::AlignCenter, QChar((unsigned short)d->_pAwesome));
    }
    painter.restore();
}
