TEMPLATE = app
#CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console
CONFIG += c++17


SOURCES += \
    ipv4addTests.cpp \
    main.cpp

INCLUDEPATH += \
        ../external \
        ../src/core

CONFIG(release, debug|release) {
    MY_VAR = "release"
    message($$MY_VAR)
}
CONFIG(debug, debug|release) {
    MY_VAR = "debug"
    message($$MY_VAR)
}

LIBS += -L$$OUT_PWD/../src/core/$$MY_VAR -lcore
