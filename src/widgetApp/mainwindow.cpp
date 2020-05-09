#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IPv4parser.h"
#include "SubnetsCalculatorV4.h"
#include "IPstructs.h"
#include <QSpinBox>
#include <QLabel>
#include <QtCore>

using namespace core;

namespace widgetApp {

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        addressWidget = ui->Address4Widget;

        subnetScrollContent = ui->subnetScroll;
        subnetScrollContent->setLayout(subnetsPanelLayout);

        infoScrollContent = ui->infoScroll;
        infoScrollContent ->setLayout(infoPanelLayout);

        subnetGraphContent = ui->graphScroll;

        subnetCountBox = ui->hostNumberSpinBox;

        binaryAddressWidget = ui->BinaryAddress4Widget;

        maskWidget = ui->Mask4Widget;

        binaryMaskWidget = ui->BinaryMask4Widget;

        initializeData();
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }
}

void widgetApp::MainWindow::initializeData()
{
    mainNetwork = new Networkv4();
    calculator = new SubnetsCalculatorV4();

    subnetCount = 0;
    isHorizontal = false;
}

void widgetApp::MainWindow::on_drawButton_clicked()
{
    drawNetworkGraph(isHorizontal);
}

void widgetApp::MainWindow::on_radioButton_clicked(bool checked)
{
    isHorizontal = (checked) ? true : false;
    drawNetworkGraph(isHorizontal);
}

void widgetApp::MainWindow::on_CalculateButton_clicked()
{
     mainNetwork->Ip = parser.ipFromString(
                 takeStringFromInputFields(addressWidget));

     mainNetwork->NetMask = parser.ipMaskFromString(
                 takeStringFromInputFields(maskWidget));

     displayInputInBinary(mainNetwork->Ip.get()->asStringBin(),
                          binaryAddressWidget);

     displayInputInBinary(mainNetwork->NetMask.get()->asStringBin(),
                          binaryMaskWidget);

     setSubnetsHostCount();

     calculator->calcSubnets(*mainNetwork, subnets);

     displayNetworkInfo();
}

void widgetApp::MainWindow::setSubnetsHostCount()
{
    for (int i = 0; i < subnetCount; i++)
    {
       Subnetv4 temp;
       temp.HostNumber = spinBoxList->at(i)->value();
       subnets.push_back(std::make_shared<Subnetv4>(temp));
    }
}

void widgetApp::MainWindow::deleteLayoutContent(QWidget *content)
{
    QLayoutItem *child;
    while ((child = content->layout()->takeAt(0)) != NULL)
    {
        if(child->widget() != NULL)
        {
            delete child->widget();
        }
        delete child;
    }
}

QString widgetApp::MainWindow::takeStringFromInputFields(QWidget *inputWidget)
{
    QList<QLineEdit*> inputFields = inputWidget->findChildren<QLineEdit*>();

    QString input= "";

    for (int i = 0; i < inputFields.count(); i++)
    {
        if(inputFields[i] != NULL)
        {
            input += inputFields[i]->text();
            if(i < inputFields.count() - 1) input += ".";
        }
    }

    return input;
}

void widgetApp::MainWindow::displayInputInBinary(QString input, QWidget *displayWidget)
{
    QList<QLineEdit*> displayFields = displayWidget->findChildren<QLineEdit*>();

    std::string bitsetString = input.toUtf8().constData();

    for (int i = 0; i < displayFields.count(); i++)
    {
        if(displayFields[i] != NULL)
        {
            QString octText = QString::fromStdString(bitsetString.substr(i * 9, 8));
            displayFields[i]->setText(octText);
        }
    }
}

void widgetApp::MainWindow::on_hostNumberSpinBox_valueChanged(int subnetCount)
{
    this->subnetCount = subnetCount;

    spinBoxList = new QList<QSpinBox*>();

    subnets.clear();

    deleteLayoutContent(subnetScrollContent);

    for (int i = 0; i < subnetCount; i++)
    {
        QHBoxLayout *textLayout = new QHBoxLayout();

        QString labelText = QString::fromStdString("Subnet " + std::to_string(1 + i));
        QLabel *subnetLabel = new QLabel(labelText);
        subnetLabel->setLayout(textLayout);
        subnetLabel->font().bold();

        subnetsPanelLayout->addWidget(subnetLabel);

        QHBoxLayout *frameLayout = new QHBoxLayout();
        QFrame *frame = new QFrame();

        frame->setMinimumHeight(30);
        frame->setLayout(frameLayout);

        QLabel *label = new QLabel("Hosts number: ");
        label->setMinimumHeight(20);
        QSpinBox *spinBox = new QSpinBox();
        spinBox->setStyleSheet("background-color: rgb(180, 180, 180);\nncolobackground-color: rgb(180, 180, 180);"
                                "\ncolor: rgb(240, 221, 168);r: rgb(220, 221, 168)");
        spinBox->setMinimumHeight(20);

        frameLayout->addWidget(label);
        frameLayout->addWidget(spinBox);

        subnetsPanelLayout->addWidget(frame);

        spinBoxList->append(spinBox);
    }
}

void widgetApp::MainWindow::drawNetworkGraph(bool isVertical)
{
    subnetGraphContent->setLayout(graphPanelLayout);

    subnetsGraphFrame = new QFrame();

    QLayoutItem *child;
    while ((child = subnetGraphContent->layout()->takeAt(0)) != NULL)
    {
        if(child->widget() != NULL)
        {
            delete child->widget();
        }
        delete child;
    }

    QFrame *graphNetworkFrame = new QFrame();
    graphNetworkFrame->setStyleSheet("background-color: rgb(218, 86, 88)");
    subnetGraphContent->layout()->addWidget(graphNetworkFrame);
    graphNetworkFrame->setLayout(new QVBoxLayout());

    QString routerButtonText = QString::fromStdString("R" + std::to_string(1));
    QPushButton *routerButton = new QPushButton(routerButtonText);
    routerButton->setStyleSheet("background-color: rgb(218, 86, 88)");
    routerButton->setMinimumSize(QSize(50,50));
    routerButton->setMaximumSize(QSize(50,50));
    graphNetworkFrame->layout()->addWidget(routerButton);

    subnetsGraphFrame->setStyleSheet("background-color: rgb(227, 229, 115, 100)");

    if(isVertical)
        subnetsGraphFrame->setLayout(new QVBoxLayout());
    else  subnetsGraphFrame->setLayout(new QHBoxLayout());

    subnetsGraphFrame->layout()->setSpacing(50);
    graphNetworkFrame->layout()->addWidget(subnetsGraphFrame);

    for(int i = 0; i < subnetCount; i++)
    {
         QVBoxLayout *frameLayout = new QVBoxLayout();

         QFrame *subnetFrame = new QFrame();
         subnetFrame->setLayout(frameLayout);

         subnetsGraphFrame->layout()->addWidget(subnetFrame);

         QString subButtonText = QString::fromStdString("S" + std::to_string(1 + i));
         QPushButton *subnetButton = new QPushButton(subButtonText);

         subnetButton->setStyleSheet("background-color: rgb(227, 229, 115)");
         subnetButton->setMinimumSize(QSize(40,40));
         subnetButton->setMaximumSize(QSize(40,40));
         subnetFrame->layout()->addWidget(subnetButton);

         QHBoxLayout *hostsLayout;

         for(int j = 0; j < subnets[i]->HostNumber; j++)
         {
            if((j + 8) % 8 == 0)
            {
                hostsLayout = new QHBoxLayout();
                QFrame *hostFrame = new QFrame();
                frameLayout -> addWidget(hostFrame);

                hostFrame->setLayout(hostsLayout);
                hostFrame->setStyleSheet("background-color: rgb(15, 159, 116,100)");
                hostFrame->setMaximumWidth(300);
            }

            QString hostButtonText = QString::fromStdString("H" + std::to_string(1 + j));
            QPushButton *hostButton = new QPushButton(hostButtonText);
            hostButton->setStyleSheet("background-color: rgb(15, 159, 116)");
            hostButton->setMinimumSize(QSize(20,20));
            hostButton->setMaximumSize(QSize(20,20));
            hostsLayout->addWidget(hostButton);
         }
    }
}

void widgetApp::MainWindow::displayNetworkInfo()
{
    deleteLayoutContent(infoScrollContent);

    for(int i = 0; i < subnetCount; i++)
    {
        QVBoxLayout *frameLayout = new QVBoxLayout();
        QFrame *frame = new QFrame();
        //frame->setStyleSheet("background-color: rgb(15, 159, 116,100)");
        infoPanelLayout->addWidget(frame);
        frame->setMinimumHeight(150);
        frame->setLayout(frameLayout);

        QString labelText = QString::fromStdString("Subnet " + std::to_string(1 + i));
        QLabel *subnetLabel = new QLabel(labelText);
        subnetLabel->font().bold();
        frame->layout()->addWidget(subnetLabel);

        QLabel *hostLabel = new QLabel(QString::fromStdString(
                                      "Host number: " + std::to_string((int)subnets.at(i)->HostNumber)));
        hostLabel->setMinimumHeight(20);

        QLabel *addressLabel = new QLabel("IP address: " + (subnets.at(i)->Ip->asStringDec()));
        QLabel *addressBinaryLabel = new QLabel("Binary IP address: " + (subnets.at(i)->Ip->asStringBin()));

        QLabel *maskLabel = new QLabel("Mask: " + (subnets.at(i)->NetMask->asStringDec()));
        QLabel *maskBinaryLabel = new QLabel("Binary mask: " + (subnets.at(i)->Ip->asStringBin()));

        QVBoxLayout *detailsLayout = new QVBoxLayout();
        QFrame *detailsFrame = new QFrame();
        detailsFrame->setLayout(detailsLayout);

        detailsFrame->layout()->addWidget(hostLabel);
        detailsFrame->layout()->addWidget(addressLabel);
        detailsFrame->layout()->addWidget(addressBinaryLabel);
        detailsFrame->layout()->addWidget(maskLabel);
        detailsFrame->layout()->addWidget(maskBinaryLabel);

        frame->layout()->addWidget(detailsFrame);

        infoPanelLayout->addWidget(frame);
    }
}


