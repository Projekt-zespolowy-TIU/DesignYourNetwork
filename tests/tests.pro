TEMPLATE = app
#CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console
CONFIG += testcase

include(../common.pri)

SOURCES += \
    IPaddressBaseTests.cpp \
    IPv4maskTests.cpp \
    IPv4parserTests.cpp \
    SubnetsCalculatorV4Tests.cpp \
    main.cpp

INCLUDEPATH += \
        ../external

include(../src/core/core.pri)
