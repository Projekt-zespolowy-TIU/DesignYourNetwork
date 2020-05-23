QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../../common.pri)

SOURCES += \
    graphDialog.cpp \
    main.cpp \
    mainwindow.cpp \
    networkDialog.cpp \
    subnetDialog.cpp

HEADERS += \
    graphDialog.h \
    hostButton.h \
    mainwindow.h \
    networkButton.h \
    networkDialog.h \
    subnetButton.h \
    subnetDialog.h

FORMS += \
    graphdialog.ui \
    mainwindow.ui \
    networkdialog.ui \
    subnetdialog.ui

include(../core/core.pri)

RESOURCES += \
    resources.qrc
