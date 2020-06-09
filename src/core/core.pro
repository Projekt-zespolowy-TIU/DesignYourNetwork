QT -= gui

TEMPLATE = lib
CONFIG += staticlib

include(../../common.pri)

SOURCES += \
    Host.cpp \
    IPaddress.cpp \
    IPprotocolAlgorithm.cpp \
    IPv4address.cpp \
    IPv4mask.cpp \
    IPv4parser.cpp \
    IPv6address.cpp \
    IPv6mask.cpp \
    IPv6parser.cpp \
    Networkv4.cpp \
    Networkv6.cpp \
    ReportGeneratorV4.cpp \
    ReportGeneratorV6.cpp \
    SubnetsCalculatorV4.cpp \
    SubnetsCalculatorV6.cpp \
    Subnetv4.cpp \
    Subnetv6.cpp \
    coreUtils.cpp

HEADERS += \
    Host.h \
    IIPaddrPrintable.h \
    IIPparser.h \
    INetwork.h \
    IPaddress.h \
    IPprotocolAlgorithm.h \
    IPv4address.h \
    IPv4parser.h \
    IPv4mask.h \
    IPv6address.h \
    IPv6mask.h \
    IPv6parser.h \
    IReportGenerator.h \
    ISubnet.h \
    Networkv4.h \
    Networkv6.h \
    ReportGeneratorV4.h \
    ReportGeneratorV6.h \
    SubnetsCalculatorV4.h \
    SubnetsCalculatorV6.h \
    Subnetv4.h \
    Subnetv6.h \
    coreUtils.h

TARGET = core
