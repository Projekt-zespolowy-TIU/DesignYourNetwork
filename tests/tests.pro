TEMPLATE = app
#CONFIG -= qt
CONFIG -= app_bundle
CONFIG += console
CONFIG += c++17
CONFIG += testcase


SOURCES += \
    ipv4parserTests.cpp \
    main.cpp

INCLUDEPATH += \
        ../external \
        $$PWD/../src/core

win32-g++: LIBS += -L$$OUT_PWD/../src/core/ -lcore
else:win32:!win32-g++:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/core/release/ -lcore
else:win32:!win32-g++:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/core/debug/ -lcore
else:unix: LIBS += -L$$OUT_PWD/../src/core/ -lcore

