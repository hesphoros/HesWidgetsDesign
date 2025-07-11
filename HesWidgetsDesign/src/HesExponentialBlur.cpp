#include "HesExponentialBlur.h"

#include <QPainter>
#include <QPixmap>

#include "../private/HesExponentialBlurPrivate.h"
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <cmath>
#endif

HES_SINGLETON_CREATE_CPP(HesExponentialBlur)

HesExponentialBlur::HesExponentialBlur(QObject* parent)
    : QObject{parent}, d_ptr(new HesExponentialBlurPrivate())
{
    Q_D(HesExponentialBlur);
    d->q_ptr = this;
}


HesExponentialBlur::~HesExponentialBlur()
{
}

QPixmap HesExponentialBlur::doExponentialBlur(QImage img, const quint16& blurRadius)
{
    QImage image = img.convertToFormat(QImage::Format_ARGB32);
    HesExponentialBlur::getInstance()->d_ptr->_drawExponentialBlur(image, blurRadius);
    return QPixmap::fromImage(image);
}