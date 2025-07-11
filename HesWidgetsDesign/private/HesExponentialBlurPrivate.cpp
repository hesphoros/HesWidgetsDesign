#include "HesExponentialBlurPrivate.h"

#include <QPixmap>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <cmath>
#endif

/**
 * @brief _aprec 和 _zprec 的默认值
 * 这些值用于控制指数模糊的精度和效果。
 * _aprec 控制模糊的精度，_zprec 控制模糊的深度。
 */
int HesExponentialBlurPrivate::_aprec = 12;
int HesExponentialBlurPrivate::_zprec = 7;


HesExponentialBlurPrivate::HesExponentialBlurPrivate(QObject* parent)
    : QObject{parent}
{
}

HesExponentialBlurPrivate::~HesExponentialBlurPrivate()
{
}

/**
 * @brief 应用指数模糊效果
 * @note 指数计算公式 为 1.0f - std::exp(-2.3f / (qRadius + 1.f))
 * @param image 要处理的图像
 * @param qRadius 模糊半径
 */
void HesExponentialBlurPrivate::_drawExponentialBlur(QImage& image, const quint16& qRadius)
{
    // 指数模糊处理逻辑
    if ( qRadius < 1 ) return;
    // 确保图像格式为 ARGB32_Premultiplied
    image = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    // 计算模糊半径的 alpha 值
    // alpha 值用于控制模糊的强度
    int alpha = (int)((1 << _aprec) * (1.0f - std::exp(-2.3f / (qRadius + 1.f))));
    int height = image.height();
    int width  = image.width();
    // 遍历图像的每一行
    for (int row = 0; row < height; row++) {
        _drawRowBlur(image, row, alpha);
    }

    // 遍历图像的每一列
    for (int column = 0; column < width; column++) {
        _drawColumnBlur(image, column, alpha);
    }
}

void HesExponentialBlurPrivate::_drawRowBlur(QImage& image, const int& row, const int& alpha)
{
    int zR = 0, zG = 0, zB = 0, zA = 0;
    // 获取当前行的像素数据
    QRgb * bptr = reinterpret_cast<QRgb*>(image.scanLine(row));
    int width = image.width();

    // zR zG zB zA 分别表示红色、绿色、蓝色和透明度通道的值
    // 计算当前行的第一个像素的颜色值
    zR = *((unsigned char*)bptr) << _zprec;
    zG = *((unsigned char*)bptr + 1) << _zprec;
    zB = *((unsigned char*)bptr + 2) << _zprec;
    zA = *((unsigned char*)bptr + 3) << _zprec;

    for ( int index = 0; index < width; index++ ) {
        _drawInnerBlur(reinterpret_cast<unsigned char*>(&bptr[index]), zR, zG, zB, zA, alpha);
    }

    for ( int index = width - 2; index >= 0; index-- ) {
        // 处理当前行的每个像素
        _drawInnerBlur(reinterpret_cast<unsigned char*>(&bptr[index]), zR, zG, zB, zA, alpha);
    }
    
}


void HesExponentialBlurPrivate::_drawColumnBlur(QImage& image, const int& column, const int& alpha)
{
    int zR, zG, zB, zA;

    QRgb* ptr = (QRgb*)image.bits();
    ptr += column;
    int height = image.height();
    int width = image.width();

    zR = *((unsigned char*)ptr) << _zprec;
    zG = *((unsigned char*)ptr + 1) << _zprec;
    zB = *((unsigned char*)ptr + 2) << _zprec;
    zA = *((unsigned char*)ptr + 3) << _zprec;

    for (int index = width; index < (height - 1) * width; index += width) {
        _drawInnerBlur((unsigned char*)&ptr[index], zR, zG, zB, zA, alpha);
    }


    for (int index = (height - 2) * width; index >= 0; index -= width) {
        _drawInnerBlur((unsigned char*)&ptr[index], zR, zG, zB, zA, alpha);
    }
}

/**
 * @brief 处理每个像素的模糊效果
 * @param bptr 指向当前像素的指针
 * @param zR   红色通道的累积值
 * @param zG   绿色通道的累积值
 * @param zB   蓝色通道的累积值
 * @param zA   透明度通道的累积值
 * @param alpha 模糊强度
 */
void HesExponentialBlurPrivate::_drawInnerBlur(unsigned char* bptr, int& zR, int& zG, int& zB, int& zA, int alpha)
{
    int R, G, B, A;
    R = *bptr;
    G = *(bptr + 1);
    B = *(bptr + 2);
    A = *(bptr + 3);


    // 使用 alpha 值对颜色通道进行插值计算
    // 这里的 alpha 值用于控制模糊的强度
    
    zR += (alpha * ((R << _zprec) - zR)) >> _aprec;
    zG += (alpha * ((G << _zprec) - zG)) >> _aprec;
    zB += (alpha * ((B << _zprec) - zB)) >> _aprec;
    zA += (alpha * ((A << _zprec) - zA)) >> _aprec;

    *bptr = zR >> _zprec;
    *(bptr + 1) = zG >> _zprec;
    *(bptr + 2) = zB >> _zprec;
    *(bptr + 3) = zA >> _zprec;
}
