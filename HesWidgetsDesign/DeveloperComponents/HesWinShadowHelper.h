#ifndef DEVELOPER_COMPONENTS_HES_WIN_SHADOW_HELPER_H
#define DEVELOPER_COMPONENTS_HES_WIN_SHADOW_HELPER_H

#include "common/common_defs.h"
#include "Singleton.h"
#include <QObject>
#include <qglobal.h>
#ifdef Q_OS_WIN
#include <windows.h>
#include <dwmapi.h>
#include <windowsx.h>

// Windows 内部类型定义
#ifndef NTSTATUS
typedef LONG NTSTATUS;
#endif



/*
 * ============================================================================
 * Windows 版本号定义与对应关系表
 * ============================================================================
 * 
 * +-------------------+---------------+--------------------------------+-------------------+
 * | 宏定义            | 版本号        | Windows 版本名称               | 发布时间          |
 * +-------------------+---------------+--------------------------------+-------------------+
 * | Win8_Origin       | 6.0.0         | Windows 8 原始版本             | 2012年10月        |
 * | Win8_10           | 6.3.0         | Windows 8.1                    | 2013年10月        |
 * | Win10_Origin      | 10.0.0        | Windows 10 原始版本 (1507)     | 2015年7月         |
 * | Win10_1809        | 10.0.17763    | Windows 10 October 2018 Update | 2018年10月        |
 * | Win10_1903        | 10.0.18362    | Windows 10 May 2019 Update     | 2019年5月         |
 * | Win10_20H1        | 10.0.19041    | Windows 10 May 2020 Update     | 2020年5月         |
 * | Win11_Origin      | 10.0.22000    | Windows 11 原始版本 (21H2)     | 2021年10月        |
 * | Win11_22H2        | 10.0.22621    | Windows 11 2022 Update         | 2022年9月         |
 * +-------------------+---------------+--------------------------------+-------------------+
 * 
 * 支持的特性对应关系：
 * +-------------------+--------------------------------+----------------------------+
 * | Windows 版本      | 支持的主要特性                 | 推荐用途                   |
 * +-------------------+--------------------------------+----------------------------+
 * | Win8_Origin       | 基础窗口阴影                   | 基本阴影效果               |
 * | Win8_10           | 改进的窗口管理                 | 基本阴影效果               |
 * | Win10_Origin      | 窗口动画、基础毛玻璃           | 基础现代化效果             |
 * | Win10_1809        | 改进的 Acrylic 效果            | 毛玻璃背景                 |
 * | Win10_1903        | 原生暗色主题支持               | 暗色主题切换               |
 * | Win10_20H1        | 增强的窗口效果                 | 现代化窗口样式             |
 * | Win11_Origin      | 圆角窗口、Mica 效果            | 现代化设计语言             |
 * | Win11_22H2        | 优化的 Mica 效果、新动画       | 最新设计效果               |
 * +-------------------+--------------------------------+----------------------------+
 * 
 * 特性支持矩阵：
 * 
 * 特性名称                    | Win8 | Win8.1 | Win10 | Win10_1809 | Win10_1903 | Win10_20H1 | Win11 | Win11_22H2
 * ---------------------------|------|--------|-------|------------|------------|------------|-------|------------
 * 基础窗口阴影                |  Y   |   Y    |   Y   |     Y      |     Y      |     Y      |   Y   |     Y
 * 窗口动画效果                |  N   |   N    |   Y   |     Y      |     Y      |     Y      |   Y   |     Y
 * Acrylic 毛玻璃效果          |  N   |   N    |   Y   |     Y      |     Y      |     Y      |   Y   |     Y
 * 原生暗色主题                |  N   |   N    |   N   |     N      |     Y      |     Y      |   Y   |     Y
 * 增强的窗口效果              |  N   |   N    |   N   |     N      |     N      |     Y      |   Y   |     Y
 * 圆角窗口                    |  N   |   N    |   N   |     N      |     N      |     N      |   Y   |     Y
 * Mica 效果                   |  N   |   N    |   N   |     N      |     N      |     N      |   Y   |     Y
 * 优化的 Mica 和新动画        |  N   |   N    |   N   |     N      |     N      |     N      |   N   |     Y
 * 
 * 图例：Y = 支持，N = 不支持
 * 
 * 注意事项：
 * - Windows 内部版本号与显示版本号可能不同
 * - 建议使用 >= 比较来检查版本兼容性
 * - 某些特性需要额外的系统配置才能启用
*/

// Windows 版本号定义
#define Win8_Origin     "6.0.0"         // Windows 8 原始版本
#define Win8_10         "6.3.0"         // Windows 8.1
#define Win10_Origin    "10.0.0"        // Windows 10 原始版本 (1507)
#define Win10_1809      "10.0.17763"    // Windows 10 October 2018 Update
#define Win10_1903      "10.0.18362"    // Windows 10 May 2019 Update (暗色主题支持)
#define Win10_20H1      "10.0.19041"    // Windows 10 May 2020 Update
#define Win11_Origin    "10.0.22000"    // Windows 11 原始版本 (21H2)
#define Win11_22H2      "10.0.22621"    // Windows 11 2022 Update


// 版本比较用的数值定义 (便于比较)
#define WIN8_ORIGIN_BUILD       0           // Windows 8
#define WIN8_10_BUILD           6300        // Windows 8.1
#define WIN10_ORIGIN_BUILD      10000       // Windows 10 原始版本
#define WIN10_1809_BUILD        17763       // Windows 10 1809
#define WIN10_1903_BUILD        18362       // Windows 10 1903
#define WIN10_20H1_BUILD        19041       // Windows 10 20H1
#define WIN11_ORIGIN_BUILD      22000       // Windows 11 原始版本
#define WIN11_22H2_BUILD        22621       // Windows 11 22H2

class HesWinShadowHelper : public QObject
{
    Q_OBJECT
    HES_SINGLETON_CREATE(HesWinShadowHelper)
private:
    explicit HesWinShadowHelper(QObject* parent = nullptr);
    ~HesWinShadowHelper() override;
public:
    /**
     * @brief 初始化 DWM API
     * @return true 
     * @return false 
     */
    bool initDWMAPI();

    void setWindowShadow(quint64 hwnd);
    void setWindowThemeMode(quint64 hwnd, bool isLightMode);
    void setWindowDisplayMode(QWidget* widget,
          HesApplicationType::WindowDisplayMode displayMode, 
          HesApplicationType::WindowDisplayMode lastDisplayMode);
    bool isCompositionEnabled() const;
    bool compareWindowsVersion(const QString& version) const;
private:

    /**
     * @enum _DWM_SYSTEMBACKDROP_TYPE
     * @brief 指定要应用于窗口的系统背景类型。
     *
     * 此枚举定义了窗口可用的背景类型，可用于控制窗口背景的外观和行为。
     *
     * - _DWMSBT_AUTO: 自动选择合适的背景类型。
     * - _DWMSBT_NONE: 不应用任何背景。
     * - _DWMSBT_MAINWINDOW: 应用适合主应用程序窗口的背景。
     * - _DWMSBT_TRANSIENTWINDOW: 应用适合临时或瞬态窗口的背景。
     * - _DWMSBT_TABBEDWINDOW: 应用适合标签页窗口的背景。
     */
    enum _DWM_SYSTEMBACKDROP_TYPE
    {
        _DWMSBT_AUTO,               // 自动选择背景类型
        _DWMSBT_NONE,               // 无背景
        _DWMSBT_MAINWINDOW,         // 主窗口背景
        _DWMSBT_TRANSIENTWINDOW,    // 临时窗口背景
        _DWMSBT_TABBEDWINDOW        // 标签页窗口背景
    };

    /**
     * @enum _DWMWINDOWATTRIBUTE
     * @brief 枚举自定义的 DWM (桌面窗口管理器) 窗口属性，用于高级窗口效果控制。
     *
     * 这些属性可用于控制窗口的各种视觉方面，如背景画刷、沉浸式暗色模式、
     * 窗口圆角偏好、边框厚度、系统背景类型和特殊效果等。
     *
     * @var _DWMWA_USE_HOSTBACKDROPBRUSH
     *   为窗口启用主机背景画刷 (值: 17)。
     * @var _DWMWA_USE_IMMERSIVE_DARK_MODE_BEFORE_20H1
     *   为 Windows 20H1 之前的版本启用沉浸式暗色模式 (值: 19)。
     * @var _DWMWA_USE_IMMERSIVE_DARK_MODE
     *   为 Windows 20H1 及更高版本启用沉浸式暗色模式 (值: 20)。
     * @var _DWMWA_WINDOW_CORNER_PREFERENCE
     *   设置窗口圆角偏好 (例如圆角或尖角) (值: 33)。
     * @var _DWMWA_VISIBLE_FRAME_BORDER_THICKNESS
     *   指定可见边框的厚度 (值: 37)。
     * @var _DWMWA_SYSTEMBACKDROP_TYPE
     *   为窗口设置系统背景类型 (值: 38)。
     * @var _DWMWA_MICA_EFFECT
     *   为窗口背景启用 Mica 材质效果 (值: 1029)。
     */
    enum _DWMWINDOWATTRIBUTE
    {
        _DWMWA_USE_HOSTBACKDROPBRUSH = 17,                  // 主机背景画刷
        _DWMWA_USE_IMMERSIVE_DARK_MODE_BEFORE_20H1 = 19,    // 20H1 之前的暗色模式
        _DWMWA_USE_IMMERSIVE_DARK_MODE = 20,                // 20H1+ 的暗色模式
        _DWMWA_WINDOW_CORNER_PREFERENCE = 33,               // 窗口圆角偏好
        _DWMWA_VISIBLE_FRAME_BORDER_THICKNESS = 37,         // 可见边框厚度
        _DWMWA_SYSTEMBACKDROP_TYPE = 38,                    // 系统背景类型
        _DWMWA_MICA_EFFECT = 1029                           // Mica 效果
    };

    /**
     * @enum _WINDOWCOMPOSITIONATTRIB
     * @brief 窗口组合属性枚举，用于控制窗口的视觉效果和行为。
     *
     * 此枚举定义了可用于 SetWindowCompositionAttribute API 的各种窗口属性，
     * 这些属性可以控制窗口的渲染、主题、特效和其他视觉方面。
     *
     * @var _WCA_UNDEFINED
     *   未定义的属性 (值: 0)
     * @var _WCA_NCRENDERING_ENABLED
     *   启用非客户区渲染 (值: 1)
     * @var _WCA_NCRENDERING_POLICY
     *   非客户区渲染策略 (值: 2)
     * @var _WCA_TRANSITIONS_FORCEDISABLED
     *   强制禁用窗口过渡动画 (值: 3)
     * @var _WCA_ALLOW_NCPAINT
     *   允许非客户区绘制 (值: 4)
     * @var _WCA_CAPTION_BUTTON_BOUNDS
     *   标题栏按钮边界 (值: 5)
     * @var _WCA_NONCLIENT_RTL_LAYOUT
     *   非客户区从右到左布局 (值: 6)
     * @var _WCA_FORCE_ICONIC_REPRESENTATION
     *   强制图标表示 (值: 7)
     * @var _WCA_EXTENDED_FRAME_BOUNDS
     *   扩展框架边界 (值: 8)
     * @var _WCA_HAS_ICONIC_BITMAP
     *   是否有图标位图 (值: 9)
     * @var _WCA_THEME_ATTRIBUTES
     *   主题属性 (值: 10)
     * @var _WCA_NCRENDERING_EXILED
     *   非客户区渲染流放 (值: 11)
     * @var _WCA_NCADORNMENTINFO
     *   非客户区装饰信息 (值: 12)
     * @var _WCA_EXCLUDED_FROM_LIVEPREVIEW
     *   从实时预览中排除 (值: 13)
     * @var _WCA_VIDEO_OVERLAY_ACTIVE
     *   视频覆盖激活 (值: 14)
     * @var _WCA_FORCE_ACTIVEWINDOW_APPEARANCE
     *   强制活动窗口外观 (值: 15)
     * @var _WCA_DISALLOW_PEEK
     *   禁用窗口预览 (值: 16)
     * @var _WCA_CLOAK
     *   隐藏窗口 (值: 17)
     * @var _WCA_CLOAKED
     *   窗口已隐藏状态 (值: 18)
     * @var _WCA_ACCENT_POLICY
     *   强调色策略，用于毛玻璃效果 (值: 19)
     * @var _WCA_FREEZE_REPRESENTATION
     *   冻结窗口表示 (值: 20)
     * @var _WCA_EVER_UNCLOAKED
     *   窗口是否曾经显示过 (值: 21)
     * @var _WCA_VISUAL_OWNER
     *   视觉所有者 (值: 22)
     * @var _WCA_HOLOGRAPHIC
     *   全息模式 (值: 23)
     * @var _WCA_EXCLUDED_FROM_DDA
     *   从桌面重复排除 (值: 24)
     * @var _WCA_PASSIVEUPDATEMODE
     *   被动更新模式 (值: 25)
     * @var _WCA_USEDARKMODECOLORS
     *   使用暗色模式颜色 (值: 26)
     * @var _WCA_CORNER_STYLE
     *   窗口圆角样式 (值: 27)
     * @var _WCA_PART_COLOR
     *   部分颜色设置 (值: 28)
     * @var _WCA_DISABLE_MOVESIZE_FEEDBACK
     *   禁用移动大小反馈 (值: 29)
     * @var _WCA_LAST
     *   最后一个有效属性标记 (值: 30)
     */
    enum _WINDOWCOMPOSITIONATTRIB
    {
        _WCA_UNDEFINED = 0,                         // 未定义
        _WCA_NCRENDERING_ENABLED = 1,               // 启用非客户区渲染
        _WCA_NCRENDERING_POLICY = 2,                // 非客户区渲染策略
        _WCA_TRANSITIONS_FORCEDISABLED = 3,         // 强制禁用过渡动画
        _WCA_ALLOW_NCPAINT = 4,                     // 允许非客户区绘制
        _WCA_CAPTION_BUTTON_BOUNDS = 5,             // 标题栏按钮边界
        _WCA_NONCLIENT_RTL_LAYOUT = 6,              // 非客户区 RTL 布局
        _WCA_FORCE_ICONIC_REPRESENTATION = 7,       // 强制图标表示
        _WCA_EXTENDED_FRAME_BOUNDS = 8,             // 扩展框架边界
        _WCA_HAS_ICONIC_BITMAP = 9,                 // 是否有图标位图
        _WCA_THEME_ATTRIBUTES = 10,                 // 主题属性
        _WCA_NCRENDERING_EXILED = 11,               // 非客户区渲染流放
        _WCA_NCADORNMENTINFO = 12,                  // 非客户区装饰信息
        _WCA_EXCLUDED_FROM_LIVEPREVIEW = 13,        // 从实时预览排除
        _WCA_VIDEO_OVERLAY_ACTIVE = 14,             // 视频覆盖激活
        _WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,    // 强制活动窗口外观
        _WCA_DISALLOW_PEEK = 16,                    // 禁用窗口预览
        _WCA_CLOAK = 17,                            // 隐藏窗口
        _WCA_CLOAKED = 18,                          // 窗口已隐藏状态
        _WCA_ACCENT_POLICY = 19,                    // 强调色策略 (毛玻璃)
        _WCA_FREEZE_REPRESENTATION = 20,            // 冻结窗口表示
        _WCA_EVER_UNCLOAKED = 21,                   // 窗口是否曾显示
        _WCA_VISUAL_OWNER = 22,                     // 视觉所有者
        _WCA_HOLOGRAPHIC = 23,                      // 全息模式
        _WCA_EXCLUDED_FROM_DDA = 24,                // 从桌面重复排除
        _WCA_PASSIVEUPDATEMODE = 25,                // 被动更新模式
        _WCA_USEDARKMODECOLORS = 26,                // 使用暗色模式颜色
        _WCA_CORNER_STYLE = 27,                     // 窗口圆角样式
        _WCA_PART_COLOR = 28,                       // 部分颜色设置
        _WCA_DISABLE_MOVESIZE_FEEDBACK = 29,        // 禁用移动大小反馈
        _WCA_LAST = 30                              // 最后一个有效属性
    };

    /**
     * @enum _ACCENT_STATE
     * @brief 窗口强调色状态枚举，用于控制窗口背景的模糊和透明效果。
     *
     * 此枚举定义了不同的窗口背景效果状态，包括禁用、渐变、透明渐变、
     * 背景模糊和 Acrylic 材质效果等。这些状态主要用于实现现代化的
     * 窗口视觉效果，如毛玻璃背景。
     *
     * @var _ACCENT_DISABLED
     *   禁用所有强调色效果 (值: 0)
     * @var _ACCENT_ENABLE_GRADIENT
     *   启用渐变效果 (值: 1)
     * @var _ACCENT_ENABLE_TRANSPARENTGRADIENT
     *   启用透明渐变效果 (值: 2)
     * @var _ACCENT_ENABLE_BLURBEHIND
     *   启用背景模糊效果 (值: 3)
     * @var _ACCENT_ENABLE_ACRYLICBLURBEHIND
     *   启用 Acrylic 材质模糊效果 (值: 4)
     * @var _ACCENT_ENABLE_HOST_BACKDROP
     *   启用主机背景效果 (值: 5)
     * @var _ACCENT_INVALID_STATE
     *   无效状态标记 (值: 6)
     */
    enum _ACCENT_STATE
    {
        _ACCENT_DISABLED = 0,                       // 禁用强调色效果
        _ACCENT_ENABLE_GRADIENT = 1,                // 启用渐变效果
        _ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,     // 启用透明渐变效果
        _ACCENT_ENABLE_BLURBEHIND = 3,              // 启用背景模糊效果
        _ACCENT_ENABLE_ACRYLICBLURBEHIND = 4,       // 启用 Acrylic 模糊效果
        _ACCENT_ENABLE_HOST_BACKDROP = 5,           // 启用主机背景效果
        _ACCENT_INVALID_STATE = 6                   // 无效状态
    };

    /**
     * @enum _ACCENT_FLAG
     * @brief 强调色标志枚举，用于控制 Acrylic 效果的具体行为。
     *
     * 此枚举定义了强调色效果的附加标志，可以用来启用或配置
     * Acrylic 材质效果的特定行为，如亮度控制等。
     *
     * @var _ACCENT_NONE
     *   无附加标志 (值: 0)
     * @var _ACCENT_ENABLE_ACRYLIC
     *   启用 Acrylic 效果 (值: 1)
     * @var _ACCENT_ENABLE_ACRYLIC_WITH_LUMINOSITY
     *   启用带亮度控制的 Acrylic 效果 (值: 482)
     */
    enum _ACCENT_FLAG
    {
        _ACCENT_NONE = 0,                             // 无附加标志
        _ACCENT_ENABLE_ACRYLIC = 1,                   // 启用 Acrylic 效果
        _ACCENT_ENABLE_ACRYLIC_WITH_LUMINOSITY = 482  // 启用带亮度的 Acrylic 效果
    };

    /**
     * @struct _ACCENT_POLICY
     * @brief 强调色策略结构体，定义窗口背景效果的具体参数。
     *
     * 此结构体包含了控制窗口背景效果所需的所有参数，包括状态、
     * 标志、渐变颜色和动画 ID。通过设置这些参数，可以实现
     * 各种现代化的窗口视觉效果。
     *
     * @var dwAccentState
     *   强调色状态，对应 _ACCENT_STATE 枚举值
     * @var dwAccentFlags
     *   强调色标志，对应 _ACCENT_FLAG 枚举值
     * @var dwGradientColor
     *   渐变颜色值，ARGB 格式 (Alpha, Red, Green, Blue)
     * @var dwAnimationId
     *   动画 ID，用于指定过渡动画效果
     */
    struct _ACCENT_POLICY 
    {
        DWORD dwAccentState;        // 强调色状态
        DWORD dwAccentFlags;        // 强调色标志
        DWORD dwGradientColor;      // 渐变颜色 (ARGB)
        DWORD dwAnimationId;        // 动画 ID
    };

    /**
     * @struct _WINDOWCOMPOSITIONATTRIBDATA
     * @brief 窗口组合属性数据结构体，用于传递窗口属性设置参数。
     *
     * 此结构体是 SetWindowCompositionAttribute API 的参数结构，
     * 用于指定要设置的窗口属性类型、数据指针和数据大小。
     * 通常与 _ACCENT_POLICY 结构体配合使用来设置窗口的视觉效果。
     *
     * @var Attrib
     *   窗口组合属性类型，对应 _WINDOWCOMPOSITIONATTRIB 枚举值
     * @var pvData
     *   指向属性数据的指针，通常指向 _ACCENT_POLICY 结构体
     * @var cbData
     *   属性数据的字节大小，通常为 sizeof(_ACCENT_POLICY)
     */
    struct _WINDOWCOMPOSITIONATTRIBDATA 
    {
        _WINDOWCOMPOSITIONATTRIB Attrib;    // 窗口组合属性类型
        PVOID pvData;                       // 属性数据指针
        SIZE_T cbData;                      // 数据大小 (字节)
    };
private:
    // ============================================================================
    // Windows API 函数指针定义
    // ============================================================================
    
    /**
     * @typedef DwmExtendFrameIntoClientAreaFunc
     * @brief DwmExtendFrameIntoClientArea API 函数指针类型定义
     * 
     * 用于将 DWM 框架扩展到客户区，实现无边框窗口效果。
     * 通过设置边距参数，可以控制哪些区域保留为非客户区。
     * 
     * @param hWnd 目标窗口句柄
     * @param pMarInset 指向 MARGINS 结构的指针，定义扩展边距
     * @return HRESULT 操作结果，S_OK 表示成功
     */
    using DwmExtendFrameIntoClientAreaFunc = HRESULT(WINAPI*)(HWND hWnd, const MARGINS* pMarInset);
    
    /**
     * @typedef DwmSetWindowAttributeFunc
     * @brief DwmSetWindowAttribute API 函数指针类型定义
     * 
     * 用于设置 DWM 窗口属性，如暗色主题、圆角窗口、Mica 效果等。
     * 这是实现现代化窗口视觉效果的核心 API。
     * 
     * @param hwnd 目标窗口句柄
     * @param dwAttribute 要设置的属性类型 (对应 _DWMWINDOWATTRIBUTE 枚举)
     * @param pvAttribute 指向属性值的指针
     * @param cbAttribute 属性值的字节大小
     * @return HRESULT 操作结果，S_OK 表示成功
     */
    using DwmSetWindowAttributeFunc = HRESULT(WINAPI*)(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
    
    /**
     * @typedef DwmIsCompositionEnabledFunc
     * @brief DwmIsCompositionEnabled API 函数指针类型定义
     * 
     * 用于检查桌面窗口管理器 (DWM) 组合是否已启用。
     * 只有在 DWM 组合启用时，才能使用高级窗口效果。
     * 
     * @param pfEnabled 指向布尔值的指针，接收组合状态
     * @return HRESULT 操作结果，S_OK 表示成功
     */
    using DwmIsCompositionEnabledFunc = HRESULT(WINAPI*)(BOOL* pfEnabled);
    
    /**
     * @typedef RtlGetVersionFunc
     * @brief RtlGetVersion API 函数指针类型定义
     * 
     * 用于获取真实的 Windows 版本信息，不受应用程序兼容性设置影响。
     * 比 GetVersionEx 更可靠，用于精确的版本检测。
     * 
     * @param lpVersionInformation 指向 RTL_OSVERSIONINFOW 结构的指针
     * @return NTSTATUS 操作结果，STATUS_SUCCESS 表示成功
     */
    using RtlGetVersionFunc = NTSTATUS(WINAPI*)(PRTL_OSVERSIONINFOW);
    
    /**
     * @typedef DwmEnableBlurBehindWindowFunc
     * @brief DwmEnableBlurBehindWindow API 函数指针类型定义
     * 
     * 用于为窗口启用背景模糊效果，主要用于 Windows Vista/7 时代的 Aero 效果。
     * 在现代 Windows 版本中，推荐使用 Acrylic 效果替代。
     * 
     * @param hWnd 目标窗口句柄
     * @param pBlurBehind 指向 DWM_BLURBEHIND 结构的指针，定义模糊参数
     * @return HRESULT 操作结果，S_OK 表示成功
     */
    using DwmEnableBlurBehindWindowFunc = HRESULT(WINAPI*)(HWND hWnd, const DWM_BLURBEHIND* pBlurBehind);
    
    /**
     * @typedef SetWindowCompositionAttributeFunc
     * @brief SetWindowCompositionAttribute API 函数指针类型定义
     * 
     * 用于设置窗口组合属性，主要用于实现 Acrylic 毛玻璃效果。
     * 这是一个未公开的 API，但广泛用于实现现代化窗口效果。
     * 
     * @param hwnd 目标窗口句柄
     * @param data 指向 _WINDOWCOMPOSITIONATTRIBDATA 结构的指针
     * @return BOOL 操作结果，TRUE 表示成功
     */
    using SetWindowCompositionAttributeFunc = BOOL(WINAPI*)(HWND hwnd, const _WINDOWCOMPOSITIONATTRIBDATA* data);
private:
    // ============================================================================
    // 成员变量定义
    // ============================================================================
    
    /**
     * @brief DwmExtendFrameIntoClientArea API 函数指针
     * 
     * 用于实现无边框窗口效果的函数指针。在 initDWMAPI() 中动态加载，
     * 如果加载失败则为 nullptr。使用前需要检查是否为空。
     */
    DwmExtendFrameIntoClientAreaFunc _dwmExtendFrameIntoClientArea{nullptr};
    
    /**
     * @brief DwmSetWindowAttribute API 函数指针
     * 
     * 用于设置 DWM 窗口属性的函数指针，如暗色主题、圆角等。
     * 这是实现现代化窗口效果的关键函数。
     */
    DwmSetWindowAttributeFunc _dwmSetWindowAttribute{nullptr};
    
    /**
     * @brief DwmIsCompositionEnabled API 函数指针
     * 
     * 用于检查 DWM 组合是否启用的函数指针。
     * 在应用窗口效果前需要先检查组合状态。
     */
    DwmIsCompositionEnabledFunc _dwmIsCompositionEnabled{nullptr};
    
    /**
     * @brief DwmEnableBlurBehindWindow API 函数指针
     * 
     * 用于启用背景模糊效果的函数指针，主要用于传统 Aero 效果。
     * 在现代系统中推荐使用 Acrylic 效果。
     */
    DwmEnableBlurBehindWindowFunc _dwmEnableBlurBehindWindow{nullptr};
    
    /**
     * @brief SetWindowCompositionAttribute API 函数指针
     * 
     * 用于设置窗口组合属性的函数指针，实现 Acrylic 毛玻璃效果的核心函数。
     * 这是一个未公开的 Windows API，需要动态加载。
     */
    SetWindowCompositionAttributeFunc _setWindowCompositionAttribute{nullptr};
    
    /**
     * @brief Windows 版本信息结构体
     * 
     * 存储当前系统的 Windows 版本信息，用于版本检测和特性兼容性判断。
     * 通过 RtlGetVersion API 获取，包含主版本号、次版本号和构建号等信息。
     */
    RTL_OSVERSIONINFOW _windowsVersion{};

    // ============================================================================
    // 私有成员函数
    // ============================================================================
    
    /**
     * @brief 扩展窗口边距到客户区
     * 
     * 内部函数，用于将窗口的非客户区边距扩展到客户区，
     * 实现无边框窗口效果。通常在设置窗口阴影时调用。
     * 
     * @param hwnd 目标窗口句柄
     */
    void _externWindowMargins(HWND hwnd);
};
#endif

#endif // DEVELOPER_COMPONENTS_HES_WIN_SHADOW_HELPER_H