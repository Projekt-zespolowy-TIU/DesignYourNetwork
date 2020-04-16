QT -= gui

TEMPLATE = lib
CONFIG += staticlib

include(../../common.pri)

SOURCES += \
    IPaddressBase.cpp \
    IPv4mask.cpp \
    SubnetsCalculator.cpp \
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
    SubnetsCalculator.h \
    coreUtils.h

TARGET = core
