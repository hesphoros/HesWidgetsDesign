#include "HesTheme.h"
#include "HesThemePrivate.h"

#include <QPainter>
#include <QPainterPath>

#define COLOR_DARK_GRAY QColor(0x70, 0x70, 0x70)
#define COLOR_LIGHT_GRAY QColor(0x9C, 0x9B, 0x9E)


HES_SINGLETON_CREATE_CPP(HesTheme)

HesTheme::HesTheme(QObject* parent)
    : QObject{parent}, d_ptr(new HesThemePrivate())
{
    Q_D(HesTheme);
    d->q_ptr = this;
    d->_initThemeColor();
}

HesTheme::~HesTheme()
{
}

void HesTheme::setThemeMode(HesThemeType::ThemeMode themeMode)
{
    Q_D(HesTheme);
    if (d->_themeMode != themeMode) {
        d->_themeMode = themeMode;
        Q_EMIT themeModeChanged(d->_themeMode);
    }
}

HesThemeType::ThemeMode HesTheme::getThemeMode() const
{
    Q_D(const HesTheme);
    return d->_themeMode;
}

void HesTheme::drawEffectShadow(QPainter* painter, QRect widgetRect, int shadowBorderWidth, int borderRadius)
{
    Q_D(HesTheme);
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing);
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    QColor color = d->_themeMode == HesThemeType::Light ? COLOR_DARK_GRAY : COLOR_LIGHT_GRAY;
    for (int i = 0; i < shadowBorderWidth; i++)
    {
        path.addRoundedRect(widgetRect.x() + shadowBorderWidth - i, widgetRect.y() + shadowBorderWidth - i, widgetRect.width() - (shadowBorderWidth - i) * 2, widgetRect.height() - (shadowBorderWidth - i) * 2, borderRadius + i, borderRadius + i);
        int alpha = 1 * (shadowBorderWidth - i + 1);
        color.setAlpha(alpha > 255 ? 255 : alpha);
        painter->setPen(color);
        painter->drawPath(path);
    }
    painter->restore();
}

void HesTheme::setThemeColor(HesThemeType::ThemeMode themeMode,HesThemeType::ThemeColor themeColor, const QColor& newColor)
{
    Q_D(HesTheme);
    if (themeMode == HesThemeType::Light) {
        d->_lightThemeColorList[themeColor] = newColor;
    } else {
        d->_darkThemeColorList[themeColor] = newColor;
    }
}

const QColor& HesTheme::getThemeColor(HesThemeType::ThemeMode themeMode, HesThemeType::ThemeColor themeColor)
{
    Q_D(HesTheme);
    if (themeMode == HesThemeType::Light)
    {
        return d->_lightThemeColorList[themeColor];
    }
    else
    {
        return d->_darkThemeColorList[themeColor];
    }
}