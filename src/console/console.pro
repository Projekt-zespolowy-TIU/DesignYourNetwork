QT -= gui

CONFIG += console
CONFIG -= app_bundle

TARGET = "DesignYourNetwork(console)"

include(../../common.pri)

SOURCES += \
        main.cpp

include(../core/core.pri)
