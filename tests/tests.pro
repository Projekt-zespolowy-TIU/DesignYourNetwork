TEMPLATE = app
#CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console
CONFIG += testcase

include(../common.pri)

SOURCES += \
    IPstructsTests.cpp \
    IPv4addressTests.cpp \
    IPv4maskTests.cpp \
    IPv4parserTests.cpp \
    IPv6addressTests.cpp \
    IPv6parserTests.cpp \
    SubnetsCalculatorV4Tests.cpp \
    main.cpp

INCLUDEPATH += \
        ../external

include(../src/core/core.pri)
