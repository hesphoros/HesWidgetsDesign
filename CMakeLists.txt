cmake_minimum_required(VERSION 3.16)

project(HesWidgetsDesign VERSION 1.0.0 LANGUAGES CXX)

# ============================================================================
# 编译器和标准设置
# ============================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置编译选项
if(MSVC)
    # MSVC 编译器设置
    add_compile_options(/utf-8)          # UTF-8 编码支持
    add_compile_options(/W4)             # 高警告级别
    add_compile_options(/permissive-)    # 严格的 C++ 标准
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)  # 禁用安全警告
    add_compile_definitions(NOMINMAX)    # 避免 Windows.h 中的 min/max 宏冲突
    add_compile_definitions(WIN32_LEAN_AND_MEAN)  # 减少 Windows.h 包含
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ============================================================================
# Qt 配置
# ============================================================================
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Qt SDK 路径配置 (可通过命令行参数覆盖)
if(NOT DEFINED QT_SDK_DIR)
    if(WIN32)
        set(QT_SDK_DIR "D:/Qt/6.5.3/msvc2019_64" CACHE PATH "Qt SDK Directory")
    elseif(UNIX AND NOT APPLE)
        set(QT_SDK_DIR "/opt/Qt/6.5.3/gcc_64" CACHE PATH "Qt SDK Directory")
    elseif(APPLE)
        set(QT_SDK_DIR "/opt/Qt/6.5.3/macos" CACHE PATH "Qt SDK Directory")
    endif()
endif()

# 设置 Qt 路径和安装目录
set(CMAKE_PREFIX_PATH ${QT_SDK_DIR})
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Install CACHE PATH "Installation path" FORCE)

# 查找 Qt 包
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS 
    Core 
    Widgets 
    Gui 
    Network 
    Sql 
    Xml 
    Concurrent 
    Multimedia 
    Test
)

# ============================================================================
# 平台特定配置
# ============================================================================
if(WIN32)
    # Windows 特定的库
    find_library(DWMAPI_LIB dwmapi REQUIRED)
    find_library(USER32_LIB user32 REQUIRED)
    find_library(KERNEL32_LIB kernel32 REQUIRED)
    find_library(NTDLL_LIB ntdll REQUIRED)
    
    # Windows 特定的编译定义
    add_compile_definitions(
        _WINDOWS
        _UNICODE
        UNICODE
    )
endif()

# ============================================================================
# 构建配置
# ============================================================================
# 设置构建类型的默认值
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# 输出目录配置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ============================================================================
# 项目信息输出
# ============================================================================
message(STATUS "=== HesWidgetsDesign Project Configuration ===")
message(STATUS "Project version: ${PROJECT_VERSION}")
message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Qt version: ${QT_VERSION}")
message(STATUS "Qt SDK directory: ${QT_SDK_DIR}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
if(WIN32)
    message(STATUS "Target platform: Windows")
    message(STATUS "DWMAPI library: ${DWMAPI_LIB}")
endif()
message(STATUS "===============================================")

# ============================================================================
# 添加子目录
# ============================================================================
add_subdirectory(HesWidgetsDesign)
add_subdirectory(HesWidgetsDesignExample)
