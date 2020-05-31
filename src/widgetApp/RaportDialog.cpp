#include "RaportDialog.h"
#include "ui_RaportDialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QFile>
#include <QDir>
#include <QTextStream>

#include "IPstructs.h"

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

void RaportDialog::injectData(Networkv4 network, std::vector<std::shared_ptr<Subnet>> subnets)
{
    this->network = network;
    this->subnets = subnets;
}

void RaportDialog::displayNetworkRaport()
{
    ui->raportScrollContent->setLayout(raportLayout);
    raportText->setFrameStyle(0);
    raportText->clear();

    raportText->append("Network \n"
                      "\nAddress: " + network.Ip->asStringDec() +
                      "\n" + network.Ip->asStringBin() +
                      "\nMask " + network.NetMask->asStringDec() +
                      "\n" + network.NetMask->asStringBin() +
                      "\nHost capacity: " + QString::number(network.hostsCapacity()));

    raportLayout->addWidget(raportText);

    for(int i = 0; i < static_cast<int>(subnets.size()); i++)
    {
        raportText->append("\nSubnet " + QString::number(1 + i) + "\n" +
                          "\nName: " + subnets.at(i)->SubName +
                          "\nAddress: " + subnets.at(i)->Ip->asStringDec() +
                          "\n" + subnets.at(i)->Ip->asStringBin() +
                          "\nMask " + subnets.at(i)->NetMask->asStringDec() +
                          "\n" + subnets.at(i)->NetMask->asStringBin() +
                          "\nHosts: " + QString::number(subnets.at(i)->HostNumber) +
                           "/" + QString::number(subnets.at(i)->hostsCapacity()));

        if(isDetailed)
        {
            for(int j = 0; j < static_cast<int>(subnets.at(i)->HostsList.size()); j++)
            {
                raportText->append("\n    Host: " + QString::number(subnets.at(i)->HostsList.at(j).Number));
                                  ("\n    Name: " + subnets.at(i)->HostsList.at(j).Name);
                                  ("\n    Address: " + subnets.at(i)->HostsList.at(j).Ip->asStringDec());
                                  ("\n    " + subnets.at(i)->HostsList.at(j).Ip->asStringBin());
            }
        }
    }
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
