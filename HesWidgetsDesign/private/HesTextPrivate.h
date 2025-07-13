#ifndef HESTEXTPRIVATE_H
#define HESTEXTPRIVATE_H

#include <QObject>
#include "HesText.h"
#include "common/common_defs.h"
#include "stdafx.h"

class HesText;

class HesTextPrivate : public QObject
{
    Q_OBJECT
    Q_D_DECLARE_POINTER(HesText)
    Q_PROPERTY_CREATE_PRIVATE(HesTextType::TextStyle, TextStyle)   /*!< 文本样式 */
    Q_PROPERTY_CREATE_PRIVATE(HesIconType::IconName, HesIcon)       /*!< HesIconType 图标名称 */
public:
    explicit HesTextPrivate(QObject *parent = nullptr);
    ~HesTextPrivate() override;
    Q_SLOT void onThemeChanged(HesThemeType::ThemeMode themeMode);
private:
    HesThemeType::ThemeMode _themeMode;
    bool                    _isWrapAnywhere{false};          /*!< 是否允许任意位置换行 */
    qreal                   _textSpacing{0.5};          /*!< 文本间距 */
    void                    _changeTheme();
};


#endif // HESTEXTPRIVATE_H