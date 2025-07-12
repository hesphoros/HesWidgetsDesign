#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

#include <QObject>
#include "stdafx.h"

// 枚举类导出 兼容 QT5 低版本
/**
 * @brief 如果Qt版本大于等于5.14.0，
 */
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
#define Q_ENUM_BEGIN(CLASS) \
    namespace CLASS     \
    { \
    Q_NAMESPACE_EXPORT(HES_EXPORT)

#define Q_ENUM_END(CLASS) }

#define Q_ENUM_REGISTER(CLASS) Q_ENUM_NS(CLASS)
#else
#define Q_ENUM_BEGIN(CLASS) \
    class HES_EXPORT CLASS : public QObject \
    { \
        Q_OBJECT \
    public:

#define Q_ENUM_END(CLASS) \
    private: \
        Q_DISABLE_COPY(CLASS) \
    }; 

#define Q_ENUM_REGISTER(CLASS) Q_ENUM(CLASS)
#endif



//---------------------------------------------------------------------------
// HesApplicationType
//---------------------------------------------------------------------------
Q_ENUM_BEGIN(HesApplicationType)
    enum WindowDisplayMode
    {
        Normal  = 0x0000,  /*!< Normal  */
        HesMica = 0x0001,  /*!< HesMica */
    #if defined(Q_OS_WIN)
        Mica    = 0x0002,  /*!< Mica    */
        MicaAlt = 0x0003,  /*!< MicaAlt */
        Acrylic = 0x0004,  /*!< Acrylic */
        DWMBlur = 0x0005,  /*!< DWMBlur */
    #endif
    };
Q_ENUM_REGISTER(WindowDisplayMode)
Q_ENUM_END(HesApplicationType)
//---------------------------------------------------------------------------
// End HesApplicationType
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// HesThemeType
//---------------------------------------------------------------------------
Q_ENUM_BEGIN(HesThemeType)
    
    /**
     * @brief 主题类型
     * @enum HesThemeType::ThemeMode
     * @details 主题模式枚举
     */
    enum ThemeMode
    {
        Light = 0x0000,  /*!< Light */
        Dark  = 0x0001,  /*!< Dark  */
    };
Q_ENUM_REGISTER(ThemeMode)
    enum ThemeColor
    {
        ScrollBarHandle,
        ToggleSwitchNoToggledCenter,
        WindowBase,
        WindowCentralStackBase,
        PrimaryNormal,
        PrimaryHover,
        PrimaryPress,
        PopupBorder,
        PopupBorderHover,
        PopupBase,
        PopupHover,
        DialogBase,
        DialogLayoutArea,
        BasicText,
        BasicTextInvert,
        BasicDetailsText,
        BasicTextNoFocus,
        BasicTextDisable,
        BasicTextPress,
        BasicBorder,
        BasicBorderDeep,
        BasicBorderHover,
        BasicBase,
        BasicBaseDeep,
        BasicDisable,
        BasicHover,
        BasicPress,
        BasicSelectedHover,
        BasicBaseLine,
        BasicHemline,
        BasicIndicator,
        BasicChute,
        BasicAlternating,
        BasicBaseAlpha,
        BasicBaseDeepAlpha,
        BasicHoverAlpha,
        BasicPressAlpha,
        BasicSelectedAlpha,
        BasicSelectedHoverAlpha,
        StatusDanger,
    };
Q_ENUM_REGISTER(ThemeColor)
Q_ENUM_END(HesThemeType)
//---------------------------------------------------------------------------
// End HesThemeType
//---------------------------------------------------------------------------

#endif // COMMON_DEFS_H