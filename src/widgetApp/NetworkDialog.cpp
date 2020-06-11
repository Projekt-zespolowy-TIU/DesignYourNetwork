#include "NetworkDialog.h"
#include "ui_NetworkDialog.h"

#include "core/SubnetsCalculatorV4.h"

NetworkDialog::NetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkDialog)
{
    ui->setupUi(this);

    hostCount = 0;
}

NetworkDialog::~NetworkDialog()
{
    delete ui;
}

void NetworkDialog::InjectData(const std::shared_ptr<INetwork>& network)
{
    this->network = network;
    this->subnetCount = static_cast<int>(network->Subnets().size());
    hostCount = 0;

    for(int i = 0; i < subnetCount; i++)
    {
        hostCount += network->Subnets()[i]->HostNumber();
    }

    SetData();
}

void NetworkDialog::SetData()
{
    ui->networkName->setText("Main network");
    ui->subnetCount->setText(QString::fromStdString(subnetCount.str()));

    QIcon icon;
    QPixmap pixmap(":/resources/img/router.png");
    icon.addPixmap(pixmap);
    ui->graphImage->setIconSize(QSize(120,120));
    ui->graphImage->setIcon(icon);

    ui->hostCapacity->setText(QString::fromStdString(network->hostsCapacity().str()));
    ui->hostCount->setText(QString::fromStdString(hostCount.str()));

    ui->networkAddressBinary->setText(network->Ip().asStringBin());
    ui->networkAddressDecimal->setText(network->Ip().asStringDec());
    ui->networkMaskBinary->setText(network->Mask().asStringBin());
    ui->networkMaskDecimal->setText(network->Mask().asStringDec());

    auto networkv4 = dynamic_cast<Networkv4*>(network.get());

    if(networkv4)
    {
        isIpv4 = true;

        ui->progressBar->setRange(0, network->hostsCapacity().convert_to<unsigned long long>());
        ui->progressBar->setValue(hostCount.convert_to<unsigned long long>());
    }
    else
    {
        isIpv4 = false;
    }

    ui->progressBar->setVisible(isIpv4);
}





