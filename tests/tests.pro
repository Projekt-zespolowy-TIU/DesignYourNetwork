TEMPLATE = app
#CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console
CONFIG += testcase

include(../common.pri)

SOURCES += \
    IPv4parserTests.cpp \
    main.cpp

INCLUDEPATH += \
        ../external

include(../src/core/core.pri)
