QT -= gui

TEMPLATE = lib
CONFIG += staticlib

include(../../common.pri)

SOURCES += \
    IPaddressBase.cpp \
    IPv4address.cpp \
    IPv4mask.cpp \
    IPv4parser.cpp \
    SubnetsCalculatorV4.cpp \
    IPmaskBase.cpp \
    coreUtils.cpp

HEADERS += \
    IIPaddress.h \
    IIPmask.h \
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
