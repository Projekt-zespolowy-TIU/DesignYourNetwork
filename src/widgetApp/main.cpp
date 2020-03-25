#include "mainwindow.h"

#include <QApplication>

using namespace widgetApp;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
