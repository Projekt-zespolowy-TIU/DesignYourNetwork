QT -= gui

TEMPLATE = lib
CONFIG += staticlib

include(../../common.pri)

SOURCES += \
    IPv4address.cpp \
    IPv4parser.cpp

HEADERS += \
    IPv4address.h \
    IPv4parser.h

TARGET = core
