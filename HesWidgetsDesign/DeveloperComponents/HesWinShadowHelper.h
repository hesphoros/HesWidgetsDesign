#ifndef DEVELOPER_COMPONENTS_HES_WIN_SHADOW_HELPER_H
#define DEVELOPER_COMPONENTS_HES_WIN_SHADOW_HELPER_H

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


#endif // DEVELOPER_COMPONENTS_HES_WIN_SHADOW_HELPER_H