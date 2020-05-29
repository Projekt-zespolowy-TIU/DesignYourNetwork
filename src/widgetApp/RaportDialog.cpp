#include "RaportDialog.h"
#include "ui_RaportDialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>


#include "IPstructs.h"

using namespace core;

RaportDialog::RaportDialog(Networkv4 network, std::vector<std::shared_ptr<Subnet>> subnets,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RaportDialog)
{
    ui->setupUi(this);

    this->network = network;
    this->subnets = subnets;

    displayNetworkRaport();
}

RaportDialog::~RaportDialog()
{
    delete ui;
}

void RaportDialog::displayNetworkRaport()
{
    ui->raportScrollContent->setLayout(raportLayout);

    QTextEdit *text = new QTextEdit();
    text->setFrameStyle(0);

    text->append("Network \n");
    text->append("Address: " + network.Ip->asStringDec());
    text->append(network.Ip->asStringBin());
    text->append("Mask " + network.NetMask->asStringDec());
    text->append(network.NetMask->asStringBin());
    text->append("Host capacity: " + QString::number(network.hostsCapacity()));

    raportLayout->addWidget(text);

    for(int i = 0; i < static_cast<int>(subnets.size()); i++)
    {
        text->append("\n Subnet " + QString::number(1 + i) + "\n");
        text->append("Address: " + subnets.at(i)->Ip->asStringDec());
        text->append(subnets.at(i)->Ip->asStringBin());
        text->append("Mask " + subnets.at(i)->NetMask->asStringDec());
        text->append(subnets.at(i)->NetMask->asStringBin());
        text->append("Hosts: " + QString::number(subnets.at(i)->HostNumber) + "/" + QString::number(subnets.at(i)->hostsCapacity()));
    }
}
