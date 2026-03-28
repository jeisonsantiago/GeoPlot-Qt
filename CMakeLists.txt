cmake_minimum_required(VERSION 3.16)

project(GeoPlot VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Svg OpenGL PrintSupport Xml OpenGLWidgets)

qt_add_executable(GeoPlot
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    GeoGraphicsView.cpp
    GeoGraphicsView.h
    GeoScene.cpp
    GeoScene.h
    ItemGroup.cpp
    ItemGroup.h
    resources.qrc
    NOTES.md
)

target_link_libraries(GeoPlot PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Svg
    Qt6::OpenGL
    Qt6::PrintSupport
    Qt6::Xml
    Qt6::OpenGLWidgets
)