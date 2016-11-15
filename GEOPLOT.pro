#-------------------------------------------------
#
# Project created by QtCreator 2016-11-10T19:55:37
#
#-------------------------------------------------

QT       += core gui svg webenginewidgets opengl printsupport xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GEOPLOT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GeoGraphicsView.cpp \
    GeoScene.cpp \
    ItemGroup.cpp

HEADERS  += mainwindow.h \
    GeoGraphicsView.h \
    GeoScene.h \
    ItemGroup.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
