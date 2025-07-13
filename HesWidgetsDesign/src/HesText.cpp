#include "HesText.h"

#include <QContextMenuEvent>
#include <QPainter>

#include "HesTheme.h"
#include "HesTextPrivate.h"

HesText::HesText(QWidget* parent)
    : QLabel(parent), d_ptr(new HesTextPrivate())
{
    Q_D(HesText);
    d->q_ptr = this;
    d->_pTextStyle = HesTextType::NoStyle;
    d->_pHesIcon = HesIconType::None;
    setObjectName("HesText");
    setStyleSheet("#HesText{background-color:transparent;}");
    QFont textFont = font();
    textFont.setLetterSpacing(QFont::AbsoluteSpacing, d->_textSpacing);
    textFont.setPixelSize(28);
    setFont(textFont);
    setWordWrap(true);
    d->_themeMode = hesTheme->getThemeMode();
    d->onThemeChanged(hesTheme->getThemeMode());
    connect(hesTheme, &HesTheme::themeModeChanged, d, &HesTextPrivate::onThemeChanged);
}

HesText::HesText(QString text, QWidget* parent)
    : HesText(parent)
{
    setText(text);
}

HesText::HesText(QString text, int pixelSize, QWidget* parent)
    : HesText(text, parent)
{
    QFont font = this->font();
    font.setPixelSize(pixelSize);
    setFont(font);
}

HesText::~HesText()
{
}

void HesText::setIsWrapAnywhere(bool isWrapAnywhere)
{
    Q_D(HesText);
    setWordWrap(isWrapAnywhere);
    d->_isWrapAnywhere = isWrapAnywhere;
}

bool HesText::getIsWrapAnywhere() const
{
    Q_D(const HesText);
    return d->_isWrapAnywhere;
}

void HesText::setTextPixelSize(int size)
{
    QFont font = this->font();
    font.setPixelSize(size);
    setFont(font);
}

int HesText::getTextPixelSize() const
{
    return this->font().pixelSize();
}

void HesText::setTextPointSize(int size)
{
    QFont font = this->font();
    font.setPointSize(size);
    setFont(font);
}

int HesText::getTextPointSize() const
{
    return this->font().pointSize();
}

void HesText::setTextStyle(HesTextType::TextStyle textStyle)
{
    Q_D(HesText);
    QFont textFont = font();
    d->_pTextStyle = textStyle;
    switch (textStyle)
    {
    case HesTextType::NoStyle:
    {
        break;
    }
    case HesTextType::Caption:
    {
        textFont.setPixelSize(12);
        break;
    }
    case HesTextType::Body:
    {
        textFont.setPixelSize(13);
        break;
    }
    case HesTextType::BodyStrong:
    {
        textFont.setPixelSize(13);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case HesTextType::Subtitle:
    {
        textFont.setPixelSize(20);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case HesTextType::Title:
    {
        textFont.setPixelSize(28);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case HesTextType::TitleLarge:
    {
        textFont.setPixelSize(40);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    case HesTextType::Display:
    {
        textFont.setPixelSize(48);
        textFont.setWeight(QFont::DemiBold);
        break;
    }
    }
    setFont(textFont);
}

HesTextType::TextStyle HesText::getTextStyle() const
{
    Q_D(const HesText);
    return d->_pTextStyle;
}

void HesText::setHesIcon(HesIconType::IconName hesIcon)
{
    Q_D(HesText);
    d->_pHesIcon = hesIcon;
    update();
    Q_EMIT pHesIconChanged();
}

HesIconType::IconName HesText::getHesIcon() const
{
    Q_D(const HesText);
    return d->_pHesIcon;
}

void HesText::paintEvent(QPaintEvent* event)
{
    Q_D(HesText);
    if (d->_pHesIcon != HesIconType::None)
    {
        QPainter painter(this);
        painter.save();
        painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
        QFont iconFont = QFont("HesAwesome");
        iconFont.setPixelSize(this->font().pixelSize());
        painter.setFont(iconFont);
        painter.setPen(HesThemeColor(d->_themeMode, BasicText));
        painter.drawText(rect(), Qt::AlignCenter, QChar((unsigned short)d->_pHesIcon));
        painter.restore();
    }
    else
    {
        if (wordWrap() && d->_isWrapAnywhere)
        {
            QPainter painter(this);
            painter.save();
            painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
            painter.setPen(HesThemeColor(d->_themeMode, BasicText));
            painter.drawText(rect(), Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap | Qt::TextWrapAnywhere, text());
            painter.restore();
        }
        else
        {
            QLabel::paintEvent(event);
        }
    }
}
