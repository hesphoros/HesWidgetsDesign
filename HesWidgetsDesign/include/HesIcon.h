/**
 * @file HesIcon.h
 * @brief HesIcon 类的头文件
 * @details 提供基于 HesAwesome 字体的图标生成功能，支持多种自定义参数
 * @author HesWidgetsDesign 开发团队
 * @date 2025
 * @copyright Copyright (c) 2025 HesWidgetsDesign. All rights reserved.
 */

#ifndef HESICON_H
#define HESICON_H

#include <QIcon>

#include "common/common_defs.h"
#include "Singleton.h"
#include "stdafx.h"

/**
 * @class HesIcon
 * @brief HesAwesome 字体图标生成器
 * @details 这是一个单例类，用于生成基于 HesAwesome 字体的矢量图标。
 *          支持多种自定义参数，包括大小、颜色、画布尺寸等。
 * 
 * @note 此类使用单例模式，通过 getInstance() 方法获取实例
 * @note 依赖于 HesAwesome 字体文件，确保字体已正确加载
 * 
 * 主要特性：
 * - 基于字体的矢量图标，支持任意缩放
 * - 支持自定义颜色
 * - 支持自定义尺寸
 * - 支持非正方形画布
 * - 高质量抗锯齿渲染
 * 
 * 使用示例：
 * @code
 * // 获取单例实例
 * HesIcon* iconGenerator = HesIcon::getInstance();
 * 
 * // 生成默认图标
 * QIcon defaultIcon = iconGenerator->getHesIcon(HesIconType::Home);
 * 
 * // 生成自定义颜色图标
 * QIcon colorIcon = iconGenerator->getHesIcon(HesIconType::Settings, QColor(255, 0, 0));
 * 
 * // 生成自定义大小图标
 * QIcon bigIcon = iconGenerator->getHesIcon(HesIconType::User, 48);
 * 
 * // 生成完全自定义图标
 * QIcon customIcon = iconGenerator->getHesIcon(
 *     HesIconType::Mail, 24, 60, 30, QColor(0, 128, 255)
 * );
 * @endcode
 * 
 * @see HesIconType::IconName
 * @see Singleton
 */
class HES_EXPORT HesIcon
{
    // 单例模式声明
    HES_SINGLETON_CREATE_H(HesIcon)
private:
    /**
     * @brief 私有构造函数
     * @details 单例模式，禁止直接实例化
     */
    explicit HesIcon();
    
    /**
     * @brief 私有析构函数
     * @details 单例模式，由框架管理生命周期
     */
    ~HesIcon();

public:
    /**
     * @brief 生成默认样式的 HesAwesome 图标
     * @param awesome 图标名称，来自 HesIconType::IconName 枚举
     * @return QIcon 生成的图标对象
     * @details 生成一个 30x30 像素，25 像素字体大小的默认图标
     * @note 使用 HesAwesome 字体渲染图标，透明背景
     */
    QIcon getHesIcon(HesIconType::IconName awesome);
    
    /**
     * @brief 生成指定颜色的 HesAwesome 图标
     * @param awesome 图标名称，来自 HesIconType::IconName 枚举
     * @param iconColor 图标颜色
     * @return QIcon 生成的图标对象
     * @details 生成一个 30x30 像素，25 像素字体大小，指定颜色的图标
     */
    QIcon getHesIcon(HesIconType::IconName awesome, QColor iconColor);
    
    /**
     * @brief 生成指定大小的 HesAwesome 图标
     * @param awesome 图标名称，来自 HesIconType::IconName 枚举
     * @param pixelSize 图标像素大小（宽高相等的正方形）
     * @return QIcon 生成的图标对象
     * @details 生成一个指定大小的正方形图标，字体大小与像素大小相同
     */
    QIcon getHesIcon(HesIconType::IconName awesome, int pixelSize);
    
    /**
     * @brief 生成指定大小和颜色的 HesAwesome 图标
     * @param awesome 图标名称，来自 HesIconType::IconName 枚举
     * @param pixelSize 图标像素大小（宽高相等的正方形）
     * @param iconColor 图标颜色
     * @return QIcon 生成的图标对象
     * @details 生成一个指定大小和颜色的正方形图标，字体大小与像素大小相同
     */
    QIcon getHesIcon(HesIconType::IconName awesome, int pixelSize, QColor iconColor);
    
    /**
     * @brief 生成指定字体大小和画布尺寸的 HesAwesome 图标
     * @param awesome 图标名称，来自 HesIconType::IconName 枚举
     * @param pixelSize 字体像素大小
     * @param fixedWidth 画布固定宽度
     * @param fixedHeight 画布固定高度
     * @return QIcon 生成的图标对象
     * @details 生成一个自定义画布尺寸的图标，可以创建非正方形的图标
     * @warning fixedWidth 和 fixedHeight 应该大于 pixelSize，否则图标可能显示不完整
     */
    QIcon getHesIcon(HesIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight);
    
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
     */
    QIcon getHesIcon(HesIconType::IconName awesome, int pixelSize, int fixedWidth, int fixedHeight, QColor iconColor);
};

#endif // HESICON_H