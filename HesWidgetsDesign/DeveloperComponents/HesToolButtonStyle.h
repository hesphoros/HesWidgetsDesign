#ifndef HESTOOLBUTTONSTYLE_H
#define HESTOOLBUTTONSTYLE_H

#include <QProxyStyle>
#include "common/common_defs.h"

class QStyleOptionToolButton;
class HesToolButtonStyle : public QProxyStyle
{
    Q_OBJECT
    Q_DEFINE_ACCESSORS(bool, IsTransparent)
    Q_DEFINE_ACCESSORS(int, BorderRadius)
    Q_DEFINE_ACCESSORS(qreal, ExpandIconRotate)
    Q_DEFINE_ACCESSORS(bool, IsSelected);

public:
    explicit HesToolButtonStyle(QStyle* style = nullptr);
    ~HesToolButtonStyle();
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex* option, QPainter* painter, const QWidget* widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption* option, const QSize& size, const QWidget* widget) const override;

private:
    HesThemeType::ThemeMode _themeMode;
    int _contentMargin{6};
    int _hasMenuIndicatorWidth{30};
    void _drawIndicator(QPainter* painter, const QStyleOptionToolButton* bopt, const QWidget* widget) const;
    void _drawIcon(QPainter* painter, QRectF iconRect, const QStyleOptionToolButton* bopt, const QWidget* widget) const;
    void _drawText(QPainter* painter, QRect contentRect, const QStyleOptionToolButton* bopt) const;
    qreal _calculateExpandIndicatorWidth(const QStyleOptionToolButton* bopt, QPainter* painter) const;
};

#endif // HESTOOLBUTTONSTYLE_H