#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SubnetDialog.h"
#include "SubnetButton.h"
#include "networkDialog.h"
#include "NetworkButton.h"

#include <QSpinBox>
#include <QLabel>
#include <QtCore>

#include "IPv4parser.h"
#include "SubnetsCalculatorV4.h"

using namespace core;

namespace widgetApp {

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        addressWidget = ui->Address4Widget;

        binaryAddressWidget = ui->BinaryAddress4Widget;

        maskWidget = ui->Mask4Widget;

        binaryMaskWidget = ui->BinaryMask4Widget;

        subnetScrollContent = ui->subnetScroll;
        subnetScrollContent->setLayout(subnetsPanelLayout);

        infoScrollContent = ui->infoScroll;
        infoScrollContent ->setLayout(infoPanelLayout);

        //subnetGraphContent = ui->graphScroll;

        subnetCountBox = ui->hostNumberSpinBox;

        QIcon icon;
        QPixmap pixmap(":/resources/img/web.png");
        icon.addPixmap(pixmap.scaled(100,100));
        ui->toolBox->setItemIcon(0, icon);

    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }
}

void widgetApp::MainWindow::resetData()
{
    mainNetwork = Networkv4();
    calculator = SubnetsCalculatorV4();

    subnetCount = 0;
    isHorizontal = false;
}

void widgetApp::MainWindow::on_drawButton_clicked()
{
    drawNetworkGraph();
}

void widgetApp::MainWindow::on_radioButton_clicked(bool checked)
{
    isHorizontal = (checked) ? true : false;
    drawNetworkGraph();
}

void widgetApp::MainWindow::on_CalculateButton_clicked()
{
     mainNetwork.Ip = parser.ipFromString(
                 takeStringFromInputFields(addressWidget));

     mainNetwork.NetMask = parser.ipMaskFromString(
                 takeStringFromInputFields(maskWidget));

     displayInputInBinary(mainNetwork.Ip.get()->asStringBin(),
                          binaryAddressWidget);

     displayInputInBinary(mainNetwork.NetMask.get()->asStringBin(),
                          binaryMaskWidget);

     setSubnetsHostCount();

     calculator.calcSubnets(mainNetwork, subnets);

     displayNetworkInfo();

     raportDialog = new RaportDialog(mainNetwork, subnets, this);
     raportDialog->setGeometry(this->geometry().x() + 1180, this->geometry().y() + 60, raportDialog->geometry().width(), raportDialog->geometry().height());
     //raportDialog->setModal(true);
     //raportDialog->exec();
     raportDialog->show();

}

void widgetApp::MainWindow::setSubnetsHostCount()
{ 
    for (int i = 0; i < subnetCount; i++)
    {
       Subnetv4 subnet;
       subnet.HostNumber = spinBoxList->at(i)->value();
       subnets.push_back(std::make_shared<Subnetv4>(subnet));

       for (int i = 0; i < subnet.HostNumber; i++)
       {
           Subnet::Host host;
           subnet.HostsList.push_back(host);
       }
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
        subnetLabel->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        subnetLabel->setLayout(textLayout);
        subnetLabel->font().bold();

        subnetsPanelLayout->addWidget(subnetLabel);

        QHBoxLayout *frameLayout = new QHBoxLayout();
        QFrame *frame = new QFrame();

        frame->setMinimumHeight(30);
        frame->setLayout(frameLayout);

        QLabel *label = new QLabel("Hosts number: ");
        label->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        label->setMinimumHeight(20);
        QSpinBox *spinBox = new QSpinBox();
        spinBox->setStyleSheet("background-color: rgb(60, 60, 60);\n color: rgb(220, 220, 220)");
        spinBox->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        spinBox->setMinimumHeight(20);

        frameLayout->addWidget(label);
        frameLayout->addWidget(spinBox);

        subnetsPanelLayout->addWidget(frame);

        spinBoxList->append(spinBox);
    }
}

void widgetApp::MainWindow::drawNetworkGraph()
{
     graphDialog = new GraphDialog(mainNetwork, subnets, this);
     graphDialog->setGeometry(this->geometry().x() + 390, this->geometry().y() + 60, graphDialog->geometry().width(), graphDialog->geometry().height());
     //graphDialog->setModal(true);
     //graphDialog->exec();
     graphDialog->show();
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
                                      "Host number: " + std::to_string(static_cast<int>(subnets.at(i)->HostNumber))));
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
void widgetApp::MainWindow::on_saveButton_clicked()
{

}




