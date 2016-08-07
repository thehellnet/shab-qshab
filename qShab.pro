#-------------------------------------------------
#
# Project created by QtCreator 2016-07-05T20:46:10
#
#-------------------------------------------------

QT       += core gui network serialport positioning webengine webenginewidgets

TARGET = qShab
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
        mainwindow.cpp \
    configwindow.cpp \
    statusbarwidgets.cpp \
    utility.cpp \
    config/configuration.cpp \
    config/configurationcontroller.cpp \
    protocol/line.cpp \
    protocol/lineparser.cpp \
    protocol/habpositionline.cpp \
    protocol/habimageline.cpp \
    protocol/habtelemetryline.cpp \
    protocol/clientconnectline.cpp \
    protocol/clientupdateline.cpp \
    protocol/clientdisconnectline.cpp \
    data/datahandler.cpp \
    data/serversocket.cpp \
    datalogger.cpp \
    protocol/client.cpp

HEADERS  += mainwindow.hpp \
    configwindow.hpp \
    statusbarwidgets.hpp \
    utility.hpp \
    config/configuration.hpp \
    config/configurationcontroller.hpp \
    protocol/command.hpp \
    protocol/line.hpp \
    protocol/lineparser.hpp \
    protocol/habpositionline.hpp \
    protocol/habimageline.hpp \
    protocol/habtelemetryline.hpp \
    protocol/clientconnectline.hpp \
    protocol/clientupdateline.hpp \
    protocol/clientdisconnectline.hpp \
    data/datahandler.hpp \
    data/serversocket.hpp \
    datalogger.hpp \
    protocol/client.hpp

FORMS    += mainwindow.ui \
    configwindow.ui

RESOURCES += resources.qrc
