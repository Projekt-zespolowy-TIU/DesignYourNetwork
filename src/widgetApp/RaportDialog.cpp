#include "RaportDialog.h"
#include "ui_RaportDialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QFile>
#include <QDir>
#include <QTextStream>

#include "core/INetwork.h"

using namespace core;

RaportDialog::RaportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RaportDialog)
{
    ui->setupUi(this);
}

RaportDialog::~RaportDialog()
{
    delete ui;
}

void RaportDialog::displayNetworkRaport()
{
    ui->raportScrollContent->setLayout(raportLayout);
    raportText->setFrameStyle(0);
    raportText->clear();

    raportText->append("Network \n"
                      "\nAddress: " + network->Ip().asStringDec() +
                      "\n" + network->Ip().asStringBin() +
                      "\nMask " + network->Mask().asStringDec() +
                      "\n" + network->Mask().asStringBin() +
                      "\nHost capacity: " + QString::fromStdString(network->hostsCapacity().str()));

    raportLayout->addWidget(raportText);

    for(size_t i = 0; i < network->Subnets().size(); i++)
    {
        raportText->append("\nSubnet " + QString::number(1 + i) + "\n" +
                          "\nName: " + network->Subnets().at(i)->SubName() +
                          "\nAddress: " + network->Subnets().at(i)->Ip().asStringDec() +
                          "\n" + network->Subnets().at(i)->Ip().asStringBin() +
                          "\nMask " + network->Subnets().at(i)->Mask().asStringDec() +
                          "\n" + network->Subnets().at(i)->Mask().asStringBin() +
                          "\nHosts: " + QString::fromStdString(network->Subnets().at(i)->HostNumber().str()) +
                           "/" + QString::fromStdString(network->Subnets().at(i)->hostsCapacity().str()));

        if(isDetailed)
        {
            for(const auto& host : network->Subnets().at(i)->HostsList())
            {
                raportText->append("\n    Host: " + QString::fromStdString(host->Id().str()));
                                  ("\n    Name: " + host->Name());
                                  ("\n    Address: " + host->Ip().asStringDec());
                                  ("\n    " + host->Ip().asStringBin());
            }
        }
    }
}

void RaportDialog::injectData(const std::shared_ptr<INetwork>& net4)
{
    network = net4;
}

void RaportDialog::on_saveButton_clicked()
{
    QString dir = QCoreApplication::applicationDirPath();
    QString filename = dir.append("/raport.txt");
    QFile file(filename);

    if ( file.open(QIODevice::ReadWrite) )
    {
        QTextStream stream(&file);
        stream << raportText->toPlainText() << endl;
    }
}

void RaportDialog::on_checkBox_toggled(bool checked)
{
    isDetailed = checked;
    displayNetworkRaport();
}
