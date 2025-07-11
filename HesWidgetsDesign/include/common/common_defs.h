#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

#include "stdafx.h"



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
Q_ENUM_REGISTER(HesApplicationType)
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