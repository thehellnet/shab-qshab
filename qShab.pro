#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T20:46:10
#
#-------------------------------------------------

QT       += core gui network serialport webengine webenginewidgets

TARGET = qShab
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
        mainwindow.cpp \
    configuration.cpp \
    configurationcontroller.cpp

HEADERS  += mainwindow.hpp \
    configuration.hpp \
    configurationcontroller.hpp

FORMS    += mainwindow.ui

RESOURCES += resources.qrc
