#ifndef HESEXPOENTIALBLUR_H
#define HESEXPOENTIALBLUR_H

#include <QObject>

#include "Singleton.h"
#include "stdafx.h"

class HesExponentialBlurPrivate;

class HES_EXPORT HesExponentialBlur : public QObject
{
    Q_OBJECT
    HES_SINGLETON_CREATE_H(HesExponentialBlur)
    Q_DECLARE_PIMPL(HesExponentialBlur)
public:
    explicit HesExponentialBlur(QObject* parent = nullptr);
    ~HesExponentialBlur();
public:
    /**
     * @brief 对图像应用指数模糊
     * @param img 输入图像
     * @param blurRadius 模糊半径
     * @return 处理后的图像
     */
    static QPixmap doExponentialBlur(QImage img, const quint16& blurRadius);
};

#endif // HESEXPOENTIALBLUR_H