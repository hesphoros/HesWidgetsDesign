cmake_minimum_required(VERSION 3.14)
project(HesWidgetsDesign)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(HesWidgetsDesign WIN32
    FramelessWindow.cpp
    main.cpp
)

target_link_libraries(HesWidgetsDesign Qt6::Widgets dwmapi)
