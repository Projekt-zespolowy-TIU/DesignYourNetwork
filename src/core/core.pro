QT -= gui

TEMPLATE = lib
CONFIG += staticlib

include(../../common.pri)

SOURCES += \
    IPaddressBase.cpp \
    IPv4mask.cpp \
    SubnetsCalculatorV4.cpp \
    IPmaskBase.cpp

HEADERS += \
    IIPaddress.h \
    IIPparser.h \
    IPaddressBase.h \
    IPmaskBase.h \
    IPstructs.h \
    IPv4address.h \
    IPv4parser.h \
    IPv4mask.h \
    SubnetsCalculatorV4.h \
    coreUtils.h

TARGET = core
