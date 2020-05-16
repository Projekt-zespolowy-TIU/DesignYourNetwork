QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../common.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    networkDialog.cpp \
    subnetDialog.cpp

HEADERS += \
    hostButton.h \
    mainwindow.h \
    networkButton.h \
    networkDialog.h \
    subnetButton.h \
    subnetDialog.h

FORMS += \
    mainwindow.ui \
    networkdialog.ui \
    subnetdialog.ui

include(../core/core.pri)

RESOURCES += \
    resources.qrc
