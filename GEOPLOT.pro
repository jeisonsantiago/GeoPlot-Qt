# Copyright (c) 2016 Jeison Santiago
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

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
