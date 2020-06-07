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

#include "core/Networkv4.h"

using namespace core;

namespace widgetApp {
    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }
}



void widgetApp::MainWindow::on_actionNew_triggered()
{
    netSettingsDialog.clearData();
    netSettingsDialog.show();
}
