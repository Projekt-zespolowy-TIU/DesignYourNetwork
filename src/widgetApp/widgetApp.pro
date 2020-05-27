QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../common.pri)

SOURCES += \
    GraphDialog.cpp \
    Main.cpp \
    MainWindow.cpp \
    NetworkDialog.cpp \
    SubnetDialog.cpp

HEADERS += \
    GraphDialog.h \
    HostButton.h \
    MainWindow.h \
    NetworkButton.h \
    NetworkDialog.h \
    SubnetButton.h \
    SubnetDialog.h

FORMS += \
    GraphDialog.ui \
    MainWindow.ui \
    NetworkDialog.ui \
    SubnetDialog.ui

include(../core/core.pri)

RESOURCES += \
    resources.qrc
