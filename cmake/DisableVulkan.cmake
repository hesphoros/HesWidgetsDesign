# 自定义Qt查找脚本 - 禁用Vulkan支持
# 这个脚本在查找Qt之前设置必要的变量来避免Vulkan依赖

# 禁用 Vulkan 相关的 CMake 包查找
set(CMAKE_DISABLE_FIND_PACKAGE_Vulkan TRUE CACHE BOOL "Disable Vulkan package finding" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_WrapVulkanHeaders TRUE CACHE BOOL "Disable Vulkan headers finding" FORCE)

# 设置 Qt 特性变量来禁用 Vulkan (在 find_package 之前设置)
set(QT_FEATURE_vulkan "OFF" CACHE BOOL "Disable Vulkan support in Qt" FORCE)
set(QT6_FEATURE_vulkan "OFF" CACHE BOOL "Disable Qt6 Vulkan support" FORCE)

# 设置环境变量
set(ENV{QT_FEATURE_vulkan} "OFF")

# 如果 Qt 版本已知，设置特定版本的特性
if(QT_VERSION_MAJOR EQUAL 6 OR NOT DEFINED QT_VERSION_MAJOR)
    # 为 Qt6 设置特性缓存变量
    set(Qt6Gui_FEATURE_vulkan "OFF" CACHE BOOL "Disable Qt6 Gui Vulkan feature" FORCE)
    set(Qt6_FEATURE_vulkan "OFF" CACHE BOOL "Disable Qt6 Vulkan feature" FORCE)
endif()

# 输出调试信息
message(STATUS "Vulkan support disabled for Qt")
message(STATUS "QT_FEATURE_vulkan: ${QT_FEATURE_vulkan}")
if(DEFINED QT6_FEATURE_vulkan)
    message(STATUS "QT6_FEATURE_vulkan: ${QT6_FEATURE_vulkan}")
endif()
