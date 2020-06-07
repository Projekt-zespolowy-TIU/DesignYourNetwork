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

    private:

        Ui::MainWindow *ui;

        int subnetCount = 0;

        bool isIpv6 = false;
        bool isHorizontal = false;

        std::shared_ptr<INetwork> mainNetwork;
        SubnetsCalculatorV4 calculatorv4;
        SubnetsCalculatorV6 calculatorv6;

        QWidget *addressWidget;
        QWidget *maskWidget;
        QWidget *binaryAddressWidget;
        QWidget *binaryMaskWidget;

        QWidget *address6Widget;
        QWidget *mask6Widget;
        QWidget *binaryAddress6Widget;
        QWidget *binaryMask6Widget;

        QSpinBox *subnetCountBox;
        QWidget *subnetScrollContent;
        QWidget *subnetGraphContent;

        QFrame *subnetsGraphFrame;

        QVBoxLayout *subnetsPanelLayout = new QVBoxLayout;

        QList<QSpinBox*> spinBoxList = QList<QSpinBox*>{};
        QList<QLineEdit*> subnetNames = QList<QLineEdit*>{};

        RaportDialog raportDialog{this};

        GraphDialog graphDialog{this};

        NetSettingsDialog netSettingsDialog{this};

        ManualDialog manualDialog{this};

        void setSubnetsHostCount();

        void drawNetworkGraph();

        void deleteLayoutContent(QWidget *content);

        void displayInputInBinary(const QString &input, QWidget *displayWidget);

        QString takeStringFromInputFields(QWidget *inputWidget, char separator);
    };
}

#endif // MAINWINDOW_H
