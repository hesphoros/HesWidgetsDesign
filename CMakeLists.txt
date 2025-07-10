cmake_minimum_required(VERSION 3.16)

project(HesWidgetsDesign VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 Qt 自动化工具
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 设置编译选项
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 配置 Qt 路径
set(QT_SDK_DIR "D:/Qt/6.5.3/msvc2019_64" CACHE PATH "QT SDK DIR" FORCE)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Install CACHE PATH "Installation path" FORCE)

# 设置 Qt 路径
set(CMAKE_PREFIX_PATH ${QT_SDK_DIR})

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

# 输出 Qt 信息
message(STATUS "Qt version: ${QT_VERSION}")
message(STATUS "Qt SDK directory: ${QT_SDK_DIR}")

# 添加子目录
add_subdirectory(HesWidgetsDesign)
add_subdirectory(HesWidgetsDesignExample)
