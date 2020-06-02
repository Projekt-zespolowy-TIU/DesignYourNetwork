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

#include "core/SubnetsCalculatorV4.h"

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

        void on_calculateButton_clicked();

        void on_drawButton_clicked();

        void on_hostNumberSpinBox_valueChanged(int value);

        void on_raportButton_clicked();

    private:

        Ui::MainWindow *ui;

        int subnetCount = 0;
        bool isHorizontal = false;

        SubnetsCalculatorV4 calculator;

        Networkv4 mainNetwork;

        QWidget *addressWidget;
        QWidget *maskWidget;
        QWidget *binaryAddressWidget;
        QWidget *binaryMaskWidget;

        QSpinBox *subnetCountBox;
        QWidget *subnetScrollContent;
        QWidget *subnetGraphContent;

        QFrame *subnetsGraphFrame;

        QVBoxLayout *subnetsPanelLayout = new QVBoxLayout();
        QHBoxLayout *graphPanelLayout = new QHBoxLayout();

        QList<QSpinBox*> *spinBoxList = new QList<QSpinBox*>();
        QList<QLineEdit*> *subnetNames = new QList<QLineEdit*>;

        NetworkDialog networkDialog;

        SubnetDialog subnetDialog;

        HostDialog hostDialog;

        RaportDialog *raportDialog = new RaportDialog(this);;

        GraphDialog *graphDialog;

        void setSubnetsHostCount();

        void drawNetworkGraph();

        void deleteLayoutContent(QWidget *content);

        void displayInputInBinary(QString input, QWidget *displayWidget);

        QString takeStringFromInputFields(QWidget *inputWidget);
    };
}

#endif // MAINWINDOW_H
