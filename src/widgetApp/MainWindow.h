#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QSpinBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

#include "NetworkButton.h"
#include "NetworkDialog.h"
#include "SubnetButton.h"
#include "SubnetDialog.h"
#include "HostButton.h"
#include "HostDialog.h"
#include "GraphDialog.h"
#include "RaportDialog.h"
#include "NetSettingsDialog.h"
#include "ManualDialog.h"

#include "core/INetwork.h"
#include "core/SubnetsCalculatorV4.h"
#include "core/SubnetsCalculatorV6.h"

using namespace core;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace widgetApp{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:

        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:

        void on_actionNew_triggered();

        void on_actionRead_triggered();

        void on_actionSave_triggered();

        void on_actionManual_triggered();

        void on_actionAbout_triggered();

    protected:

          void showEvent(QShowEvent *event);

    private:

        Ui::MainWindow *ui;

        NetSettingsDialog netSettingsDialog{this};

        ManualDialog manualDialog{this};

        void openNetSettings();
    };
}

#endif // MAINWINDOW_H
