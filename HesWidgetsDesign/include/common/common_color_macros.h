#ifndef HES_COLOR_MACROS_H
#define HES_COLOR_MACROS_H

#include <QColor>

// ============================================================================
// HES 颜色宏定义 - 用于替代直接使用 QColor
// ============================================================================

// 滚动条颜色
#define HES_SCROLLBAR_HANDLE_LIGHT          QColor(0xA0, 0xA0, 0xA0)
#define HES_SCROLLBAR_HANDLE_DARK           QColor(0x9F, 0x9F, 0x9F)

// 切换开关颜色
#define HES_TOGGLE_SWITCH_CENTER_LIGHT      QColor(0x5A, 0x5A, 0x5A)
#define HES_TOGGLE_SWITCH_CENTER_DARK       QColor(0xD0, 0xD0, 0xD0)

// 主题颜色 - 主要色调
#define HES_PRIMARY_NORMAL_LIGHT            QColor(0x00, 0x67, 0xC0)
#define HES_PRIMARY_NORMAL_DARK             QColor(0x4C, 0xC2, 0xFF)
#define HES_PRIMARY_HOVER_LIGHT             QColor(0x19, 0x75, 0xC5)
#define HES_PRIMARY_HOVER_DARK              QColor(0x47, 0xB1, 0xE8)
#define HES_PRIMARY_PRESS_LIGHT             QColor(0x31, 0x83, 0xCA)
#define HES_PRIMARY_PRESS_DARK              QColor(0x42, 0xA1, 0xD2)

// 窗体颜色
#define HES_WINDOW_BASE_LIGHT               QColor(0xF3, 0xF3, 0xF3)
#define HES_WINDOW_BASE_DARK                QColor(0x20, 0x20, 0x20)
#define HES_WINDOW_CENTRAL_STACK_LIGHT      QColor(0xFF, 0xFF, 0xFF, 80)
#define HES_WINDOW_CENTRAL_STACK_DARK       QColor(0x3E, 0x3E, 0x3E, 60)

// 弹出框颜色
#define HES_POPUP_BORDER_LIGHT              QColor(0xD6, 0xD6, 0xD6)
#define HES_POPUP_BORDER_DARK               QColor(0x47, 0x47, 0x47)
#define HES_POPUP_BORDER_HOVER_LIGHT        QColor(0xCC, 0xCC, 0xCC)
#define HES_POPUP_BORDER_HOVER_DARK         QColor(0x54, 0x54, 0x54)
#define HES_POPUP_BASE_LIGHT                QColor(0xFA, 0xFA, 0xFA)
#define HES_POPUP_BASE_DARK                 QColor(0x2C, 0x2C, 0x2C)
#define HES_POPUP_HOVER_LIGHT               QColor(0xF0, 0xF0, 0xF0)
#define HES_POPUP_HOVER_DARK                QColor(0x38, 0x38, 0x38)

// 对话框颜色
#define HES_DIALOG_BASE_LIGHT               Qt::white
#define HES_DIALOG_BASE_DARK                QColor(0x1F, 0x1F, 0x1F)
#define HES_DIALOG_LAYOUT_AREA_LIGHT        QColor(0xF3, 0xF3, 0xF3)
#define HES_DIALOG_LAYOUT_AREA_DARK         QColor(0x20, 0x20, 0x20)

// 基础文本颜色
#define HES_TEXT_BASIC_LIGHT                Qt::black
#define HES_TEXT_BASIC_DARK                 Qt::white
#define HES_TEXT_BASIC_INVERT_LIGHT         Qt::white
#define HES_TEXT_BASIC_INVERT_DARK          Qt::black
#define HES_TEXT_DETAILS_LIGHT              QColor(0x87, 0x87, 0x87)
#define HES_TEXT_DETAILS_DARK               QColor(0xAD, 0xAD, 0xB0)
#define HES_TEXT_NO_FOCUS_LIGHT             QColor(0x86, 0x86, 0x8A)
#define HES_TEXT_NO_FOCUS_DARK              QColor(0x86, 0x86, 0x8A)
#define HES_TEXT_DISABLE_LIGHT              QColor(0xB6, 0xB6, 0xB6)
#define HES_TEXT_DISABLE_DARK               QColor(0xA7, 0xA7, 0xA7)
#define HES_TEXT_PRESS_LIGHT                QColor(0x5A, 0x5A, 0x5D)
#define HES_TEXT_PRESS_DARK                 QColor(0xBB, 0xBB, 0xBF)

// 基础边框颜色
#define HES_BORDER_BASIC_LIGHT              QColor(0xE5, 0xE5, 0xE5)
#define HES_BORDER_BASIC_DARK               QColor(0x4B, 0x4B, 0x4B)
#define HES_BORDER_DEEP_LIGHT               QColor(0xA8, 0xA8, 0xA8)
#define HES_BORDER_DEEP_DARK                QColor(0x5C, 0x5C, 0x5C)
#define HES_BORDER_HOVER_LIGHT              QColor(0xDA, 0xDA, 0xDA)
#define HES_BORDER_HOVER_DARK               QColor(0x57, 0x57, 0x57)

// 基础背景颜色
#define HES_BASE_BASIC_LIGHT                QColor(0xFD, 0xFD, 0xFD)
#define HES_BASE_BASIC_DARK                 QColor(0x34, 0x34, 0x34)
#define HES_BASE_DEEP_LIGHT                 QColor(0xE6, 0xE6, 0xE6)
#define HES_BASE_DEEP_DARK                  QColor(0x61, 0x61, 0x61)
#define HES_BASE_DISABLE_LIGHT              QColor(0xF5, 0xF5, 0xF5)
#define HES_BASE_DISABLE_DARK               QColor(0x2A, 0x2A, 0x2A)
#define HES_BASE_HOVER_LIGHT                QColor(0xF3, 0xF3, 0xF3)
#define HES_BASE_HOVER_DARK                 QColor(0x40, 0x40, 0x40)
#define HES_BASE_PRESS_LIGHT                QColor(0xF7, 0xF7, 0xF7)
#define HES_BASE_PRESS_DARK                 QColor(0x3A, 0x3A, 0x3A)

// 基础线条颜色
#define HES_LINE_BASE_LIGHT                 QColor(0xD1, 0xD1, 0xD1)
#define HES_LINE_BASE_DARK                  QColor(0x45, 0x45, 0x45)
#define HES_LINE_HEMLINE_LIGHT              QColor(0x86, 0x86, 0x86)
#define HES_LINE_HEMLINE_DARK               QColor(0x9A, 0x9A, 0x9A)

// 基础指示器颜色
#define HES_INDICATOR_BASIC_LIGHT           QColor(0x75, 0x7C, 0x87)
#define HES_INDICATOR_BASIC_DARK            QColor(0x75, 0x7C, 0x87)
#define HES_CHUTE_BASIC_LIGHT               QColor(0xB3, 0xB3, 0xB3)
#define HES_CHUTE_BASIC_DARK                QColor(0x63, 0x63, 0x63)

// 基础透明颜色
#define HES_ALPHA_ALTERNATING_LIGHT         QColor(0xEF, 0xEF, 0xEF, 160)
#define HES_ALPHA_ALTERNATING_DARK          QColor(0x45, 0x45, 0x45, 125)
#define HES_ALPHA_BASE_LIGHT                QColor(0xFF, 0xFF, 0xFF, 160)
#define HES_ALPHA_BASE_DARK                 QColor(0x2D, 0x2D, 0x2D, 95)
#define HES_ALPHA_BASE_DEEP_LIGHT           QColor(0xCC, 0xCC, 0xCC, 160)
#define HES_ALPHA_BASE_DEEP_DARK            QColor(0x72, 0x72, 0x72, 95)
#define HES_ALPHA_HOVER_LIGHT               QColor(0xCC, 0xCC, 0xCC, 70)
#define HES_ALPHA_HOVER_DARK                QColor(0x4B, 0x4B, 0x4B, 75)
#define HES_ALPHA_PRESS_LIGHT               QColor(0xCC, 0xCC, 0xCC, 40)
#define HES_ALPHA_PRESS_DARK                QColor(0x4B, 0x4B, 0x4B, 55)
#define HES_ALPHA_SELECTED_LIGHT            QColor(0xCC, 0xCC, 0xCC, 70)
#define HES_ALPHA_SELECTED_DARK             QColor(0x4B, 0x4B, 0x4B, 75)
#define HES_ALPHA_SELECTED_HOVER_LIGHT      QColor(0xCC, 0xCC, 0xCC, 40)
#define HES_ALPHA_SELECTED_HOVER_DARK       QColor(0x4B, 0x4B, 0x4B, 55)

// 状态颜色
#define HES_STATUS_DANGER_LIGHT             QColor(0xE8, 0x11, 0x23)
#define HES_STATUS_DANGER_DARK              QColor(0xE8, 0x11, 0x23)

// ============================================================================
// 便捷宏 - 根据主题模式自动选择颜色
// ============================================================================

// 使用示例：HES_COLOR(SCROLLBAR_HANDLE, isLight)
#define HES_COLOR(colorName, isLight) \
    ((isLight) ? HES_##colorName##_LIGHT : HES_##colorName##_DARK)

// 主题相关的便捷宏
#define HES_THEME_COLOR(colorName, themeMode) \
    HES_COLOR(colorName, (themeMode == HesThemeType::Light))

#endif // HES_COLOR_MACROS_H