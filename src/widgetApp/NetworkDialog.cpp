#include "NetworkDialog.h"
#include "ui_NetworkDialog.h"

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

void NetworkDialog::InjectData(Networkv4 network,
    std::vector<std::shared_ptr<Subnet>> subnets)
{
    this->network = network;
    this->subnetCount = static_cast<int>(subnets.size());

    for(int i = 0; i < subnetCount; i++)
    {
        hostCount += subnets[i]->HostNumber;
    }

    SetData();
}

void NetworkDialog::SetData()
{
    ui->networkName->setText("Main network");
    ui->subnetCount->setText(QString::fromStdString(std::to_string(subnetCount)));

    QIcon icon;
    QPixmap pixmap(":/resources/img/router.png");
    icon.addPixmap(pixmap);
    ui->graphImage->setIconSize(QSize(120,120));
    ui->graphImage->setIcon(icon);

    ui->hostCapacity->setText(QString::number(network.hostsCapacity()));
    ui->hostCount->setText(QString::number(hostCount));
    ui->progressBar->setRange(0, network.hostsCapacity());
    ui->progressBar->setValue(hostCount);

    ui->networkAddressBinary->setText(network.Ip->asStringBin());
    ui->networkAddressDecimal->setText(network.Ip->asStringDec());
    ui->networkMaskBinary->setText(network.Ip->asStringBin());
    ui->networkMaskDecimal->setText(network.Ip->asStringDec());
}
