/**
 * @file HesIcon.cpp
 * @brief HesIcon 类的实现文件
 * @details 提供基于 HesAwesome 字体的图标生成功能，支持多种自定义参数
 * @author HesWidgetsDesign 开发团队
 * @date 2025
 * @copyright Copyright (c) 2025 HesWidgetsDesign. All rights reserved.
 */

#include "HesIcon.h"

#include <QPainter>
#include <QPixmap>

// 单例模式的 CPP 实现宏
HES_SINGLETON_CREATE_CPP(HesIcon)

/**
 * @brief HesIcon 构造函数
 * @details 私有构造函数，用于单例模式
 * @note 此类使用单例模式，不能直接实例化，需要通过 getInstance() 获取实例
 */
HesIcon::HesIcon()
{
}

/**
 * @brief HesIcon 析构函数
 * @details 私有析构函数，用于单例模式的资源清理
 */
HesIcon::~HesIcon()
{
}

/**
 * @brief 生成默认样式的 HesAwesome 图标
 * @param awesome 图标名称，来自 HesIconType::IconName 枚举
 * @return QIcon 生成的图标对象
 * @details 生成一个 30x30 像素，25 像素字体大小的默认图标
 * @note 使用 HesAwesome 字体渲染图标
 * @see HesIconType::IconName
 * @code
 * QIcon icon = hesIcon->getHesIcon(HesIconType::Home);
 * @endcode
 */
QIcon HesIcon::getHesIcon(HesIconType::IconName awesome)
{
    QFont iconFont = QFont("HesAwesome");
    QPixmap pix(30, 30);
    pix.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    // painter.setPen(QColor("#1570A5"));
    // painter.setBrush(QColor("#1570A5"));
    iconFont.setPixelSize(25);
    painter.setFont(iconFont);
    painter.drawText(pix.rect(), Qt::AlignCenter, QChar((unsigned short)awesome));
    painter.end();
    return QIcon(pix);
}

/**
 * @brief 生成指定颜色的 HesAwesome 图标
 * @param awesome 图标名称，来自 HesIconType::IconName 枚举
 * @param iconColor 图标颜色
 * @return QIcon 生成的图标对象
 * @details 生成一个 30x30 像素，25 像素字体大小，指定颜色的图标
 * @note 使用 HesAwesome 字体渲染图标，可自定义颜色
 * @see HesIconType::IconName
 * @code
 * QIcon redIcon = hesIcon->getHesIcon(HesIconType::Home, QColor(255, 0, 0));
 * @endcode
 */
QIcon HesIcon::getHesIcon(HesIconType::IconName awesome, QColor iconColor)
{
    QFont iconFont = QFont("HesAwesome");
    QPixmap pix(30, 30);
    pix.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(iconColor);
    // painter.setBrush(QColor("#1570A5"));
    iconFont.setPixelSize(25);
    painter.setFont(iconFont);
    painter.drawText(pix.rect(), Qt::AlignCenter, QChar((unsigned short)awesome));
    painter.end();
    return QIcon(pix);
}

/**
 * @brief 生成指定大小的 HesAwesome 图标
 * @param awesome 图标名称，来自 HesIconType::IconName 枚举
 * @param pixelSize 图标像素大小（宽高相等的正方形）
 * @return QIcon 生成的图标对象
 * @details 生成一个指定大小的正方形图标，字体大小与像素大小相同
 * @note 图标尺寸和字体大小都使用 pixelSize 参数
 * @see HesIconType::IconName
 * @code
 * QIcon bigIcon = hesIcon->getHesIcon(HesIconType::Home, 48);
 * @endcode
 */
QIcon HesIcon::getHesIcon(HesIconType::IconName awesome, int pixelSize)
{
    QFont iconFont = QFont("HesAwesome");
    QPixmap pix(pixelSize, pixelSize);
    pix.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    iconFont.setPixelSize(pixelSize);
    painter.setFont(iconFont);
    // 画图形字体
    painter.drawText(pix.rect(), Qt::AlignCenter, QChar((unsigned short)awesome));
    painter.end();
    return QIcon(pix);
}

/**
 * @brief 生成指定大小和颜色的 HesAwesome 图标
 * @param awesome 图标名称，来自 HesIconType::IconName 枚举
 * @param pixelSize 图标像素大小（宽高相等的正方形）
 * @param iconColor 图标颜色
 * @return QIcon 生成的图标对象
 * @details 生成一个指定大小和颜色的正方形图标，字体大小与像素大小相同
 * @note 同时自定义图标尺寸、字体大小和颜色
 * @see HesIconType::IconName
 * @code
 * QIcon customIcon = hesIcon->getHesIcon(HesIconType::Home, 48, QColor(0, 128, 255));
 * @endcode
 */
QIcon HesIcon::getHesIcon(HesIconType::IconName awesome, int pixelSize, QColor iconColor)
{
    QFont iconFont = QFont("HesAwesome");
    QPixmap pix(pixelSize, pixelSize);
    pix.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(iconColor);
    iconFont.setPixelSize(pixelSize);
    painter.setFont(iconFont);
    // 画图形字体
    painter.drawText(pix.rect(), Qt::AlignCenter, QChar((unsigned short)awesome));
    painter.end();
    return QIcon(pix);
}

/**
 * @brief 生成指定字体大小和画布尺寸的 HesAwesome 图标
 * @param awesome 图标名称，来自 HesIconType::IconName 枚举
 * @param pixelSize 字体像素大小
 * @param fixedWidth 画布固定宽度
 * @param fixedHeight 画布固定高度
 * @return QIcon 生成的图标对象
 * @details 生成一个自定义画布尺寸的图标，可以创建非正方形的图标
 * @note 字体大小和画布尺寸分别控制，适用于需要特殊尺寸比例的场景
 * @warning fixedWidth 和 fixedHeight 应该大于 pixelSize，否则图标可能显示不完整
 * @see HesIconType::IconName
 * @code
 * QIcon wideIcon = hesIcon->getHesIcon(HesIconType::Home, 24, 60, 30);
 * @endcode
 */
QIcon HesIcon::getHesIcon(HesIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight)
{
    QFont iconFont = QFont("HesAwesome");
    QPixmap pix(fixedWidth, fixedHeight);
    pix.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    iconFont.setPixelSize(pixelSize);
    painter.setFont(iconFont);
    // 画图形字体
    painter.drawText(pix.rect(), Qt::AlignCenter, QChar((unsigned short)awesome));
    painter.end();
    return QIcon(pix);
}

/**
 * @brief 生成完全自定义的 HesAwesome 图标
 * @param awesome 图标名称，来自 HesIconType::IconName 枚举
 * @param pixelSize 字体像素大小
 * @param fixedWidth 画布固定宽度
 * @param fixedHeight 画布固定高度
 * @param iconColor 图标颜色
 * @return QIcon 生成的图标对象
 * @details 这是最灵活的图标生成方法，可以完全自定义所有参数
 * @note 提供最大的自定义灵活性，适用于需要精确控制图标外观的场景
 * @warning fixedWidth 和 fixedHeight 应该大于 pixelSize，否则图标可能显示不完整
 * @see HesIconType::IconName
 * @code
 * QIcon fullCustomIcon = hesIcon->getHesIcon(
 *     HesIconType::Home, 
 *     24,                      // 字体大小
 *     60, 30,                  // 画布尺寸
 *     QColor(255, 128, 0)      // 橙色
 * );
 * @endcode
 */
QIcon HesIcon::getHesIcon(HesIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight, QColor iconColor)
{
    QFont iconFont = QFont("HesAwesome");
    QPixmap pix(fixedWidth, fixedHeight);
    pix.fill(Qt::transparent);
    QPainter painter;
    painter.begin(&pix);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(iconColor);
    iconFont.setPixelSize(pixelSize);
    painter.setFont(iconFont);
    // 画图形字体
    painter.drawText(pix.rect(), Qt::AlignCenter, QChar((unsigned short)awesome));
    painter.end();
    return QIcon(pix);
}
