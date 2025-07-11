#ifndef HESEXPOENTIALBLURPRIVATE_H
#define HESEXPOENTIALBLURPRIVATE_H

#include <QObject>
#include "stdafx.h"

class HesExponentialBlur;

class HesExponentialBlurPrivate : public QObject
{
    Q_OBJECT
    Q_D_DECLARE_POINTER(HesExponentialBlur)
public:
    explicit HesExponentialBlurPrivate(QObject* parent = nullptr);
    ~HesExponentialBlurPrivate();
private:

    static int _aprec;  
    static int _zprec; 
    
    /**
     * @brief Draws an exponential blur effect on the given image.
     *
     * @param image The image to be processed.
     * @param qRadius The radius of the blur effect.
     */
    static void _drawExponentialBlur(QImage& image, const quint16& qRadius);
    
    /**
     * @brief Draws a blur effect on the specified row of the image.
     *
     * @param image The image to be processed.
     * @param row The row to apply the blur effect to.
     * @param alpha The alpha value for the blur effect.
     */
    static void _drawRowBlur(QImage& image, const int& row, const int& alpha);
    
    /**
     * @brief Draws a blur effect on the specified column of the image.
     *
     * @param image The image to be processed.
     * @param column The column to apply the blur effect to.
     * @param alpha The alpha value for the blur effect.
     */
    static void _drawColumnBlur(QImage& image, const int& column, const int& alpha);

    /**
     * @brief Draws a blur effect on the inner pixels of the image.
     *
     * @param bptr The pointer to the image data.
     * @param zR The red channel value.
     * @param zG The green channel value.
     * @param zB The blue channel value.
     * @param zA The alpha channel value.
     * @param alpha The alpha value for the blur effect.
     */
    static void _drawInnerBlur(unsigned char* bptr, int& zR, int& zG, int& zB, int& zA, int alpha);
};

#endif // HESEXPOENTIALBLURPRIVATE_H