QT -= gui

TEMPLATE = lib
CONFIG += staticlib

include(../../common.pri)

SOURCES += \
    IPaddressBase.cpp \
    IPv4mask.cpp

HEADERS += \
    IIPaddress.h \
    IIPparser.h \
    IPaddressBase.h \
    IPstructs.h \
    IPv4address.h \
    IPv4parser.h \
    IPv4mask.h \
    coreUtils.h

TARGET = core
