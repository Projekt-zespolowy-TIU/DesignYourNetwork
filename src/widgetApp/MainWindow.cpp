#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SubnetDialog.h"
#include "SubnetButton.h"
#include "NetworkDialog.h"
#include "NetworkButton.h"
#include "NetSettingsDialog.h"

#include <QSpinBox>
#include <QLabel>
#include <QtCore>
#include <QDesktopServices>

#include "core/Networkv4.h"

using namespace core;

namespace widgetApp {
    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        ui->menuNewFile->actions().at(0)->setShortcut(Qt::Key_N | Qt::CTRL);
        ui->menuNewFile->actions().at(1)->setShortcut(Qt::Key_R | Qt::CTRL);
        ui->menuNewFile->actions().at(2)->setShortcut(Qt::Key_S | Qt::CTRL);
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }
}

void widgetApp::MainWindow::openNetSettings()
{
    netSettingsDialog.clearData();
    netSettingsDialog.setGeometry(this->window()->geometry().x() + 10, this->window()->geometry().y() + 60,
                              netSettingsDialog.geometry().width(),  netSettingsDialog.geometry().height());
    netSettingsDialog.show();
}

void widgetApp::MainWindow::on_actionNew_triggered()
{
    openNetSettings();
}

void widgetApp::MainWindow::on_actionRead_triggered()
{
    netSettingsDialog.readData();
}

void widgetApp::MainWindow::on_actionSave_triggered()
{

}

void widgetApp::MainWindow::on_actionManual_triggered()
{
    manualDialog.open();
}

void widgetApp::MainWindow::on_actionAbout_triggered()
{
    QString link = "https://github.com/Projekt-zespolowy-TIU/DesignYourNetwork";
    QDesktopServices::openUrl(QUrl(link));
}

void widgetApp::MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    openNetSettings();
}


