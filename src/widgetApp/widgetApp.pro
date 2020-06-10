QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = "DesignYourNetwork"

include(../../common.pri)

SOURCES += \
    GraphDialog.cpp \
    HostDialog.cpp \
    Main.cpp \
    MainWindow.cpp \
    ManualDialog.cpp \
    NetSettingsDialog.cpp \
    NetworkDialog.cpp \
    RaportDialog.cpp \
    SubnetDialog.cpp

HEADERS += \
    GraphDialog.h \
    GraphFrame.h \
    HostButton.h \
    HostDialog.h \
    MainWindow.h \
    ManualDialog.h \
    NetSettingsDialog.h \
    NetworkButton.h \
    NetworkDialog.h \
    RaportDialog.h \
    SubnetButton.h \
    SubnetDialog.h

FORMS += \
    GraphDialog.ui \
    HostDialog.ui \
    MainWindow.ui \
    ManualDialog.ui \
    NetSettingsDialog.ui \
    NetworkDialog.ui \
    RaportDialog.ui \
    SubnetDialog.ui

include(../core/core.pri)

RESOURCES += \
    resources.qrc
