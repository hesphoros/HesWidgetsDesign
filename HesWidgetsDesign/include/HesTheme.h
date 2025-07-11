#ifndef HESTHEME_H
#define HESTHEME_H

#include <QObject>
#include "common/common_defs.h"
#include "Singleton.h"

#define hesTheme HesTheme::getInstance()
class QPainter;
class HesThemePrivate;

class HES_EXPORT HesTheme : public QObject
{
    Q_OBJECT
    Q_DECLARE_PIMPL(HesTheme)
    HES_SINGLETON_CREATE_H(HesTheme)
private:
    explicit HesTheme(QObject* parent = nullptr);
    ~HesTheme();

public:
    /**
     * @brief 设置主题类型
     * @param themeMode 主题类型
     */
    void setThemeMode(HesThemeType::ThemeMode themeMode);

    /**
     * @brief 获取当前主题类型
     * @retval 当前主题类型
     * @return HesThemeType::ThemeMode
     */
    HesThemeType::ThemeMode getThemeMode() const;

    /**
     * @brief 在指定的区域绘制一块阴影
     * @param painter            画笔指针
     * @param widgetRect         绘制范围
     * @param shadowBorderWidth  阴影宽度
     * @param borderRadius       圆角半径
     */
    void drawEffectShadow(QPainter* painter, QRect widgetRect, int shadowBorderWidth, int borderRadius);

    /**
     * @brief 设置主题颜色
     * @param themeMode 主题类型
     * @param themeColor 详细的主题颜色
     * @param newColor 新的颜色
     */
    void setThemeColor(HesThemeType::ThemeMode themeMode, HesThemeType::ThemeColor themeColor, QColor newColor);

    /**
     * @brief 获取主题颜色
     * @param themeMode 主题类型
     * @param themeColor 详细的主题颜色
     * @return const QColor&
     * @retval 组件颜色
     */
    const QColor& getThemeColor(HesThemeType::ThemeMode themeMode, HesThemeType::ThemeColor themeColor);
Q_SIGNALS:
    Q_SIGNAL void themeModeChanged(HesThemeType::ThemeMode themeMode);
};

#endif // HESTHEME_H