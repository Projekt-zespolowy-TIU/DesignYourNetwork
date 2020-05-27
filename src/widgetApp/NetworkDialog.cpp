#include "NetworkDialog.h"
#include "ui_networkdialog.h"

NetworkDialog::NetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkDialog)
{
    ui->setupUi(this);
}

NetworkDialog::~NetworkDialog()
{
    delete ui;
}

void NetworkDialog::InjectData(Networkv4 network, int subnetCount)
{
    this->network = network;
    this->subnetCount = subnetCount;
    SetData();
}

void NetworkDialog::SetData()
{
    ui->networkName->setText("Main network");
    ui->imageLabel->setPixmap(QPixmap(":/resources/img/router.png").scaled(120,120));
    ui->hostCount->setText(QString::fromStdString(std::to_string(network.hostsCapacity())));
    ui->subnetCount->setText(QString::fromStdString(std::to_string(subnetCount)));
    ui->networkAddressBinary->setText(network.Ip->asStringBin());
    ui->networkAddressDecimal->setText(network.Ip->asStringDec());
    ui->networkMaskBinary->setText(network.Ip->asStringBin());
    ui->networkMaskDecimal->setText(network.Ip->asStringDec());
}
