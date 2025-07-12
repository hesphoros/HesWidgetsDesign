#include "HesThemePrivate.h"
#include "common/common_color_macros.h"

HesThemePrivate::HesThemePrivate(QObject* parent)
    : QObject(parent)
{
}

HesThemePrivate::~HesThemePrivate()
{
}

#define ALIGN_ASSIGN(map, key, value) \
    map[key] = value;

void HesThemePrivate::_initThemeColor()
{
    // ScrollBar 滚动条
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::ScrollBarHandle,         HES_SCROLLBAR_HANDLE_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::ScrollBarHandle,         HES_SCROLLBAR_HANDLE_DARK);

    // ToggleSwitch 切换开关
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::ToggleSwitchNoToggledCenter, HES_TOGGLE_SWITCH_CENTER_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::ToggleSwitchNoToggledCenter, HES_TOGGLE_SWITCH_CENTER_DARK);

    // 主题颜色
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::PrimaryNormal,           HES_PRIMARY_NORMAL_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::PrimaryNormal,           HES_PRIMARY_NORMAL_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::PrimaryHover,            HES_PRIMARY_HOVER_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::PrimaryHover,            HES_PRIMARY_HOVER_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::PrimaryPress,            HES_PRIMARY_PRESS_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::PrimaryPress,            HES_PRIMARY_PRESS_DARK);

    // 通用颜色 - 普通窗体
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::WindowBase,              HES_WINDOW_BASE_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::WindowBase,              HES_WINDOW_BASE_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::WindowCentralStackBase,  HES_WINDOW_CENTRAL_STACK_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::WindowCentralStackBase,  HES_WINDOW_CENTRAL_STACK_DARK);

    // 浮动窗体
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::PopupBorder,             HES_POPUP_BORDER_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::PopupBorder,             HES_POPUP_BORDER_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::PopupBorderHover,        HES_POPUP_BORDER_HOVER_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::PopupBorderHover,        HES_POPUP_BORDER_HOVER_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::PopupBase,               HES_POPUP_BASE_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::PopupBase,               HES_POPUP_BASE_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::PopupHover,              HES_POPUP_HOVER_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::PopupHover,              HES_POPUP_HOVER_DARK);

    // Dialog 对话框窗体
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::DialogBase,              HES_DIALOG_BASE_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::DialogBase,              HES_DIALOG_BASE_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::DialogLayoutArea,        HES_DIALOG_LAYOUT_AREA_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::DialogLayoutArea,        HES_DIALOG_LAYOUT_AREA_DARK);

    // 基础文本颜色
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicText,               HES_TEXT_BASIC_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicText,               HES_TEXT_BASIC_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicTextInvert,         HES_TEXT_BASIC_INVERT_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicTextInvert,         HES_TEXT_BASIC_INVERT_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicDetailsText,        HES_TEXT_DETAILS_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicDetailsText,        HES_TEXT_DETAILS_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicTextNoFocus,        HES_TEXT_NO_FOCUS_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicTextNoFocus,        HES_TEXT_NO_FOCUS_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicTextDisable,        HES_TEXT_DISABLE_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicTextDisable,        HES_TEXT_DISABLE_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicTextPress,          HES_TEXT_PRESS_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicTextPress,          HES_TEXT_PRESS_DARK);

    // 基础边框颜色
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicBorder,             HES_BORDER_BASIC_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicBorder,             HES_BORDER_BASIC_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicBorderDeep,         HES_BORDER_DEEP_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicBorderDeep,         HES_BORDER_DEEP_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicBorderHover,        HES_BORDER_HOVER_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicBorderHover,        HES_BORDER_HOVER_DARK);

    // 基础背景颜色
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicBase,               HES_BASE_BASIC_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicBase,               HES_BASE_BASIC_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicBaseDeep,           HES_BASE_DEEP_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicBaseDeep,           HES_BASE_DEEP_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicDisable,            HES_BASE_DISABLE_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicDisable,            HES_BASE_DISABLE_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicHover,              HES_BASE_HOVER_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicHover,              HES_BASE_HOVER_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicPress,              HES_BASE_PRESS_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicPress,              HES_BASE_PRESS_DARK);

    // 基础线条颜色
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicBaseLine,           HES_LINE_BASE_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicBaseLine,           HES_LINE_BASE_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicHemline,            HES_LINE_HEMLINE_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicHemline,            HES_LINE_HEMLINE_DARK);

    // 基础指示器颜色
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicIndicator,          HES_INDICATOR_BASIC_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicIndicator,          HES_INDICATOR_BASIC_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicChute,              HES_CHUTE_BASIC_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicChute,              HES_CHUTE_BASIC_DARK);

    // 基础透明颜色
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicAlternating,        HES_ALPHA_ALTERNATING_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicAlternating,        HES_ALPHA_ALTERNATING_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicBaseAlpha,          HES_ALPHA_BASE_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicBaseAlpha,          HES_ALPHA_BASE_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicBaseDeepAlpha,      HES_ALPHA_BASE_DEEP_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicBaseDeepAlpha,      HES_ALPHA_BASE_DEEP_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicHoverAlpha,         HES_ALPHA_HOVER_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicHoverAlpha,         HES_ALPHA_HOVER_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicPressAlpha,         HES_ALPHA_PRESS_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicPressAlpha,         HES_ALPHA_PRESS_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicSelectedAlpha,      HES_ALPHA_SELECTED_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicSelectedAlpha,      HES_ALPHA_SELECTED_DARK);
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::BasicSelectedHoverAlpha, HES_ALPHA_SELECTED_HOVER_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::BasicSelectedHoverAlpha, HES_ALPHA_SELECTED_HOVER_DARK);

    // 状态颜色
    ALIGN_ASSIGN(_lightThemeColorList, HesThemeType::StatusDanger,            HES_STATUS_DANGER_LIGHT);
    ALIGN_ASSIGN(_darkThemeColorList,  HesThemeType::StatusDanger,            HES_STATUS_DANGER_DARK);
}
