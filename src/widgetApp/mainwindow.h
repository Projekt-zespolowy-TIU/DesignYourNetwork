#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include "IPv4parser.h"
#include "SubnetsCalculatorV4.h"
#include <QSpinBox>
#include <QLabel>
#include <QLayout>

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

        void on_CalculateButton_clicked();

        void on_drawButton_clicked();

        void on_hostNumberSpinBox_valueChanged(int value);

        void on_radioButton_clicked(bool checked);


    private:

        Ui::MainWindow *ui;

        int subnetCount;
        bool isHorizontal;

        IPv4parser parser;
        Networkv4 *mainNetwork;
        SubnetsCalculatorV4 *calculator;
        std::vector<std::shared_ptr<Subnet>> subnets;

        QWidget *addressWidget;
        QWidget *maskWidget;
        QWidget *binaryAddressWidget;
        QWidget *binaryMaskWidget;

        QSpinBox *subnetCountBox;
        QWidget *subnetScrollContent;
        QWidget *subnetGraphContent;
        QWidget *infoScrollContent;

        QFrame *subnetsGraphFrame;

        QVBoxLayout *subnetsPanelLayout = new QVBoxLayout();
        QVBoxLayout *infoPanelLayout = new QVBoxLayout();
        QHBoxLayout *graphPanelLayout = new QHBoxLayout();

        QList<QSpinBox*> *spinBoxList;

        void initializeData();

        void displayNetworkInfo();

        void setSubnetsHostCount();

        void drawNetworkGraph(bool isHorizontal);

        void deleteLayoutContent(QWidget *content);

        void displayInputInBinary(QString input, QWidget *displayWidget);

        QString takeStringFromInputFields(QWidget *inputWidget);

    };
}

#endif // MAINWINDOW_H
