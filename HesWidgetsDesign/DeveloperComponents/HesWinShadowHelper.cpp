#include "HesWinShadowHelper.h"
#include <iostream>
#ifdef Q_OS_WIN

#include <QDebug>
#include <QWidget>

/**
 * @brief
 * @note ntdll.dll 是windows核心系统库 这个库包含了底层的系统调用和函数
 *
 * @param parent
 */
HesWinShadowHelper::HesWinShadowHelper(QObject* parent)
    : QObject(parent)
{

    HMODULE module = LoadLibraryW(L"ntdll.dll");
    if (module)
    {
        // 获取RtlGetVersion函数的地址
        auto pRtlGetVersion = reinterpret_cast<RtlGetVersionFunc>(::GetProcAddress(module, "RtlGetVersion"));
        Q_ASSERT(pRtlGetVersion);
        // 调用RtlGetVersion函数获取Windows版本信息

        _windowsVersion.dwOSVersionInfoSize = sizeof(_windowsVersion); // 设置结构体大小
        pRtlGetVersion(&_windowsVersion); // 获取版本信息
    }
}


HesWinShadowHelper::~HesWinShadowHelper(){
    
}

/**
 * @brief 初始化 DWM API
 * @details 此函数用于加载 DWM API 函数，确保在使用 DWM 功能之前正确初始化
 * @note 需要在 Windows 系统上运行，并且确保 DWM API 可用
 * @return true 初始化成功
 * @return false 初始化失败
 * 
 */
bool HesWinShadowHelper::initDWMAPI() {
    // 动态加载 DWM API 函数
    HMODULE dwmModule = LoadLibraryW(L"dwmapi.dll");

    if (dwmModule) {
        // 获取 DwmExtendFrameIntoClientArea 函数地址
        if ( !_dwmExtendFrameIntoClientArea ) {
            _dwmExtendFrameIntoClientArea = reinterpret_cast<DwmExtendFrameIntoClientAreaFunc>(
                GetProcAddress(dwmModule, "DwmExtendFrameIntoClientArea"));
        }

        // 获取 DwmSetWindowAttribute 函数地址
        if ( !_dwmSetWindowAttribute ) {
            _dwmSetWindowAttribute = reinterpret_cast<DwmSetWindowAttributeFunc>(
                GetProcAddress(dwmModule, "DwmSetWindowAttribute"));
        }

        // 获取 DwmIsCompositionEnabled 函数地址
        if ( !_dwmIsCompositionEnabled ) {
            _dwmIsCompositionEnabled = reinterpret_cast<DwmIsCompositionEnabledFunc>(
                GetProcAddress(dwmModule, "DwmIsCompositionEnabled"));
        }

        // 获取 DwmEnableBlurBehindWindow 函数地址
        if ( !_dwmEnableBlurBehindWindow ) {
            _dwmEnableBlurBehindWindow = reinterpret_cast<DwmEnableBlurBehindWindowFunc>(
                GetProcAddress(dwmModule, "DwmEnableBlurBehindWindow"));
        }

        if (!(_dwmExtendFrameIntoClientArea && _dwmSetWindowAttribute && _dwmIsCompositionEnabled && _dwmEnableBlurBehindWindow))
        {
            qCritical() << "Dwm Func Init Fail!";
            return false;
        }

    }
    else {
        qCritical() << "Failed to load dwmapi.dll.";
        return false;
    }

    // 动态加载 SetWindowCompositionAttribute 函数 
    // user32.dll 是 Windows 的核心用户界面库 
    // 这个函数用于设置窗口的组合属性，通常用于实现毛玻璃效果
    // 注意：这个函数在 Windows 10 1809 及更高版本中可用
    // 需要确保系统版本支持
    HMODULE user32Module = LoadLibraryW(L"user32.dll");

    if ( user32Module ) {
        // 获取 SetWindowCompositionAttribute 函数地址
        // 这个函数是一个未公开的 API，通常用于设置窗口的视觉效果
        // 需要确保系统版本支持
        // 注意：这个函数在 Windows 10 1809 及更高版本中可用
        if ( !_setWindowCompositionAttribute ) {
            _setWindowCompositionAttribute = reinterpret_cast<SetWindowCompositionAttributeFunc>(
                GetProcAddress(user32Module, "SetWindowCompositionAttribute"));
        }

        if ( !( _setWindowCompositionAttribute ) ) {
            qCritical() << "Failed to load SetWindowCompositionAttribute function.";
            return false;
        }
    }
    
    else {
        qCritical() << "Failed to load user32.dll.";
        return false;
    }

    return true;
}

/**
 * @brief 设置窗口阴影效果
 * @param hwnd 窗口句柄
 * @details 此函数用于为指定窗口应用阴影效果。
 */
void HesWinShadowHelper::setWindowShadow(quint64 hwnd) {

    static const MARGINS shadowMargins = { 1, 0, 0 , 0 }; // 设置阴影边距
    // 调用 DwmExtendFrameIntoClientArea 函数来扩展窗口边框到客户区
    // 这将使窗口具有阴影效果 
    _dwmExtendFrameIntoClientArea(reinterpret_cast<HWND>(hwnd), &shadowMargins);
}

void HesWinShadowHelper::setWindowThemeMode(quint64 hwnd, bool isLightMode) {

    // 检查当前 Windows 版本是否支持主题模式更改
    if ( !compareWindowsVersion(Win10_1903) ) {
        qWarning() << "Current Windows version does not support theme mode changes.";
        return;
    }

    // 设置窗口的主题模式
    BOOL bIsLightMode = !isLightMode;
    // 根据 Windows 版本选择合适的 DWM 属性 
    _DWMWINDOWATTRIBUTE dwmAttribute = compareWindowsVersion(Win10_20H1) ?
        _DWMWA_USE_IMMERSIVE_DARK_MODE : _DWMWA_USE_IMMERSIVE_DARK_MODE_BEFORE_20H1;

    _dwmSetWindowAttribute (
        reinterpret_cast<HWND>(hwnd),
        dwmAttribute, &bIsLightMode,
        sizeof(bIsLightMode)
    );
}

void HesWinShadowHelper::setWindowDisplayMode(QWidget* widget,
          HesApplicationType::WindowDisplayMode displayMode, 
          HesApplicationType::WindowDisplayMode lastDisplayMode) {
    
    // 通过 winId() 获取窗口句柄 
    // 注意：winId() 返回的是 QWidget 的窗口句柄
    // 在 Windows 上，QWidget 的 winId() 返回的是 HWND 类型
    HWND winHwnd = reinterpret_cast<HWND>(widget->winId());

    switch ( lastDisplayMode ) {
        case HesApplicationType::Mica: {

            // 检查当前操作系统版本是否为 Windows 11 原版
            if ( !compareWindowsVersion(Win11_Origin) ) {
                break; 
            }
            //  如果当前版本是 Windows 11 22H2 或更高版本
            if ( compareWindowsVersion(Win11_22H2) ) {

                const _DWM_SYSTEMBACKDROP_TYPE backdropType = _DWMSBT_AUTO;
                // 设置窗口的系统背景类型为自动选择
                _dwmSetWindowAttribute(
                    winHwnd, _DWMWA_SYSTEMBACKDROP_TYPE,
                    &backdropType, sizeof(backdropType)
                );
            }

            else {
                // 禁用 Mica 效果
                const BOOL isEnable = FALSE;
                _dwmSetWindowAttribute(
                    winHwnd, _DWMWA_MICA_EFFECT,
                    &isEnable, sizeof(isEnable)
                );
            }
            break;
        }

        case HesApplicationType::MicaAlt: {
            // 检查当前操作系统版本是否为 Windows 11 原版
            if ( !compareWindowsVersion(Win10_20H1) ) {
                break;
            }
            const _DWM_SYSTEMBACKDROP_TYPE backdropType = _DWMSBT_AUTO;
            _dwmSetWindowAttribute(
                winHwnd, _DWMWA_SYSTEMBACKDROP_TYPE,
                &backdropType, sizeof(backdropType)
            );
            break;
        }

        case HesApplicationType::Acrylic: {
           
            if ( !compareWindowsVersion(Win11_Origin) ) {
                qWarning() << "Current Windows version does not support Acrylic effect.";
                break;
            }

            const _DWM_SYSTEMBACKDROP_TYPE backdropType = _DWMSBT_AUTO;
            
            _dwmSetWindowAttribute (
                winHwnd,
                _DWMWA_SYSTEMBACKDROP_TYPE,
                &backdropType,
                sizeof(backdropType)
            );

            break;
        }

        case HesApplicationType::DWMBlur: {
            if ( compareWindowsVersion(Win8_Origin) ) {
                
                _ACCENT_POLICY policy{};
                // 禁用 DWM 模糊效果
                policy.dwAccentState = _ACCENT_DISABLED;
                // 没用任何特殊的效果
                policy.dwAccentFlags = _ACCENT_NONE;
                
                _WINDOWCOMPOSITIONATTRIBDATA wcad{};
            
                wcad.Attrib = _WCA_ACCENT_POLICY; // 强调色策略 ( 毛玻璃 效果 )
                wcad.pvData = &policy;
                wcad.cbData = sizeof(policy);
                _setWindowCompositionAttribute(winHwnd, &wcad);
            }

            else {
                DWM_BLURBEHIND blurBehind{};
                blurBehind.fEnable = FALSE; 
                blurBehind.dwFlags = DWM_BB_ENABLE;
                _dwmEnableBlurBehindWindow(reinterpret_cast<HWND>(winHwnd), &blurBehind);
            }
            break;
        }

        default: {
            break;
        }
    }

    switch ( displayMode ) {
        case HesApplicationType::Mica: {
            if ( !compareWindowsVersion(Win11_Origin) ) {
                qWarning() << "Current Windows version does not support Mica effect.";
                break;
            }
            _externWindowMargins(winHwnd);

            if (compareWindowsVersion(Win11_22H2)) {
                const _DWM_SYSTEMBACKDROP_TYPE backdropType = _DWMSBT_MAINWINDOW;
                _dwmSetWindowAttribute (
                    winHwnd,
                    _DWMWA_SYSTEMBACKDROP_TYPE,
                    &backdropType,
                    sizeof(backdropType)
                );
            }
            
            else {
                const BOOL enable = TRUE;
                _dwmSetWindowAttribute (
                    winHwnd,
                    _DWMWA_MICA_EFFECT,
                    &enable,
                    sizeof(enable)
                );
            }
            
            break;
        }

        case HesApplicationType::MicaAlt: {
                
            if ( !compareWindowsVersion(Win11_22H2) ) {
                break;
            }
            _externWindowMargins(winHwnd);
            const _DWM_SYSTEMBACKDROP_TYPE backdropType = _DWMSBT_TABBEDWINDOW;
            _dwmSetWindowAttribute (
                winHwnd,
                _DWMWA_SYSTEMBACKDROP_TYPE,
                &backdropType,
                sizeof(backdropType)
            );

            break;
        }

        case HesApplicationType::Acrylic: {

            if (!compareWindowsVersion(Win11_Origin)) {
                break;
            }
            _externWindowMargins(winHwnd);
            const _DWM_SYSTEMBACKDROP_TYPE backdropType = _DWMSBT_TRANSIENTWINDOW;
            
            _dwmSetWindowAttribute (
                winHwnd,
                _DWMWA_SYSTEMBACKDROP_TYPE,
                &backdropType,
                sizeof(backdropType)
            );

            break;
        }

        case HesApplicationType::DWMBlur: {
            MARGINS windowMargins = {0, 1, 0, 0};
            _dwmExtendFrameIntoClientArea(winHwnd, &windowMargins);
            if (compareWindowsVersion(Win8_Origin)) {
                _ACCENT_POLICY policy{};
                policy.dwAccentState = _ACCENT_ENABLE_BLURBEHIND;
                policy.dwAccentFlags = _ACCENT_NONE;
                _WINDOWCOMPOSITIONATTRIBDATA wcad{};
                wcad.Attrib = _WCA_ACCENT_POLICY;
                wcad.pvData = &policy;
                wcad.cbData = sizeof(policy);
                _setWindowCompositionAttribute(winHwnd, &wcad);
            }
            
            else {
                DWM_BLURBEHIND bb{};
                bb.fEnable = TRUE;
                bb.dwFlags = DWM_BB_ENABLE;
                _dwmEnableBlurBehindWindow(winHwnd, &bb);
            }

            break;
        }

        default: {
            // 如果没有匹配的显示模式，什么都不做
            break;
        }
    }

}

bool HesWinShadowHelper::isCompositionEnabled() const {
    BOOL isCompositionEnabled = false;
    _dwmIsCompositionEnabled(&isCompositionEnabled);
    return isCompositionEnabled;
}

bool HesWinShadowHelper::compareWindowsVersion(const QString& windowsVersion) const {
    QStringList versionList = windowsVersion.split(".");
    if (versionList.size() != 3) {
        qWarning() << "Invalid version format. Expected format: x.x.x";
        return false;
    }

    return (
        _windowsVersion.dwMajorVersion > versionList[0].toUInt()) || 
        (_windowsVersion.dwMajorVersion == versionList[0].toUInt() && 
        (_windowsVersion.dwMinorVersion > versionList[1].toUInt() ||
         _windowsVersion.dwBuildNumber >= versionList[2].toUInt())
    );
}

void HesWinShadowHelper::_externWindowMargins(HWND hwnd) {
    static const MARGINS margins = {65536, 0, 0, 0};
    _dwmExtendFrameIntoClientArea(hwnd, &margins);
}

#endif // Q_OS_WIN