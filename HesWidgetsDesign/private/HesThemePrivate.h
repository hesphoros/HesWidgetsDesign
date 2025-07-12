#ifndef HESTHEMEPRIVATE_H
#define HESTHEMEPRIVATE_H

#include "HesTheme.h"
#include <QColor>
#include <QMap>
#include <QObject>

#include "common/common_defs.h"
#include "stdafx.h"

class HesTheme;
class HesThemePrivate : public QObject
{
    Q_OBJECT
    Q_D_DECLARE_POINTER(HesTheme)
public:
    explicit HesThemePrivate(QObject* parent = nullptr);
    ~HesThemePrivate();

private:
    HesThemeType::ThemeMode _themeMode{HesThemeType::Light};    /*!< 主题类型 */
    QColor                  _lightThemeColorList[40];           /*!< 主题颜色列表 */
    QColor                  _darkThemeColorList[40];            /*!< 主题颜色列表 */
    void _initThemeColor();
};

#endif // HESTHEMEPRIVATE_H