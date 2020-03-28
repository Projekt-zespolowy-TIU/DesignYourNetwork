QT -= gui

TEMPLATE = lib
CONFIG += staticlib

include(../../common.pri)

SOURCES += \
    ipv4add.cpp \
    ipv4parser.cpp

HEADERS += \
    ipv4add.h \
    ipv4parser.h

TARGET = core
