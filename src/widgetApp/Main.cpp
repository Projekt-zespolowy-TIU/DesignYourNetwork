#include "MainWindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QPalette>

using namespace widgetApp;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create("fusion"));

    QPalette palette;
   palette.setColor(QPalette::Window, QColor(53,53,53));
   palette.setColor(QPalette::WindowText, Qt::white);
   palette.setColor(QPalette::Base, QColor(15,15,15));
   palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
   palette.setColor(QPalette::ToolTipBase, Qt::white);
   palette.setColor(QPalette::ToolTipText, Qt::white);
   palette.setColor(QPalette::Text, Qt::white);
   palette.setColor(QPalette::Button, QColor(53,53,53));
   palette.setColor(QPalette::ButtonText, Qt::white);
   palette.setColor(QPalette::BrightText, Qt::green);

   palette.setColor(QPalette::Highlight, QColor(38,64,84).lighter());
   palette.setColor(QPalette::Highlight, QColor(38,94,84).lighter());
   palette.setColor(QPalette::HighlightedText, Qt::black);
   qApp->setPalette(palette);

    MainWindow w;
    w.show();
    return a.exec();
}
