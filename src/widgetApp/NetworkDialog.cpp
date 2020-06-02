#include "NetworkDialog.h"
#include "ui_NetworkDialog.h"

NetworkDialog::NetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkDialog),
    network{ {}, {} }
{
    ui->setupUi(this);

    hostCount = 0;
}

NetworkDialog::~NetworkDialog()
{
    delete ui;
}

void NetworkDialog::InjectData(Networkv4 network)
{
    this->network = network;
    this->subnetCount = static_cast<int>(network.Subnets().size());
    hostCount = 0;

    for(int i = 0; i < subnetCount; i++)
    {
        hostCount += network.Subnets()[i].HostNumber();
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

    ui->hostCapacity->setText(QString::fromStdString(network.hostsCapacity().str()));
    ui->hostCount->setText(QString::fromStdString(hostCount.str()));
    ui->progressBar->setRange(0, network.hostsCapacity().convert_to<unsigned long long>());
    ui->progressBar->setValue(hostCount.convert_to<unsigned long long>());

    ui->networkAddressBinary->setText(network.Ip().asStringBin());
    ui->networkAddressDecimal->setText(network.Ip().asStringDec());
    ui->networkMaskBinary->setText(network.Mask().asStringBin());
    ui->networkMaskDecimal->setText(network.Mask().asStringDec());
}
