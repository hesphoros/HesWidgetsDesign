cmake_minimum_required(VERSION 3.10)

project(HesWidgetsDesign)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
include_directories(include)

# 在这里配置QT路径 例如 D:/Qt/6.6.2/msvc2019_64
SET(QT_SDK_DIR D:/Qt/6.5.3/msvc2019_64 CACHE PATH "QT SDK DIR" FORCE)
SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/Install CACHE PATH "Installation path" FORCE)

# 设置 Qt 路径
set(CMAKE_PREFIX_PATH ${QT_SDK_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui Network Sql Xml Concurrent Multimedia Test)

add_subdirectory(HesWidgetsDesign)
add_subdirectory(HesWidgetsDesignExample)
