QT -= gui

TEMPLATE = lib
CONFIG += staticlib

include(../../common.pri)

SOURCES += \
    Host.cpp \
    IPaddress.cpp \
    IPv4address.cpp \
    IPv4mask.cpp \
    IPv4parser.cpp \
    Networkv4.cpp \
    SubnetsCalculatorV4.cpp \
    Subnetv4.cpp \
    coreUtils.cpp

HEADERS += \
    Host.h \
    IIPaddrPrintable.h \
    IIPparser.h \
    INetwork.h \
    IPaddress.h \
    IPv4address.h \
    IPv4parser.h \
    IPv4mask.h \
    ISubnet.h \
    Networkv4.h \
    SubnetsCalculatorV4.h \
    Subnetv4.h \
    coreUtils.h

TARGET = core
