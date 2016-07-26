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
    configurationcontroller.cpp \
    configwindow.cpp

HEADERS  += mainwindow.hpp \
    configuration.hpp \
    configurationcontroller.hpp \
    configwindow.hpp

FORMS    += mainwindow.ui \
    configwindow.ui

RESOURCES += resources.qrc
