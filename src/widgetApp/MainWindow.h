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

        void on_hostNumberSpinBox_valueChanged(int subnetCount);

        void on_raportButton_clicked();

    private:

        Ui::MainWindow *ui;

        int subnetCount = 0;
        bool isHorizontal = false;

        std::shared_ptr<Networkv4> mainNetwork;
        SubnetsCalculatorV4 calculator;

        QWidget *addressWidget;
        QWidget *maskWidget;
        QWidget *binaryAddressWidget;
        QWidget *binaryMaskWidget;

        QSpinBox *subnetCountBox;
        QWidget *subnetScrollContent;
        QWidget *subnetGraphContent;

        QFrame *subnetsGraphFrame;

        QVBoxLayout *subnetsPanelLayout = new QVBoxLayout(this);
        QHBoxLayout *graphPanelLayout = new QHBoxLayout(this);

        QList<QSpinBox*> spinBoxList = QList<QSpinBox*>{};
        QList<QLineEdit*> subnetNames = QList<QLineEdit*>{};

        RaportDialog raportDialog{this};

        GraphDialog graphDialog{this};

        void setSubnetsHostCount();

        void drawNetworkGraph();

        void deleteLayoutContent(QWidget *content);

        void displayInputInBinary(const QString &input, QWidget *displayWidget);

        QString takeStringFromInputFields(QWidget *inputWidget);
    };
}

#endif // MAINWINDOW_H
