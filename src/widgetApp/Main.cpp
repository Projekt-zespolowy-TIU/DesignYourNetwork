#include "MainWindow.h"

#include <QApplication>
#include <QStyleFactory>

using namespace widgetApp;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create("fusion"));

    MainWindow w;
    w.show();
    return a.exec();
}
