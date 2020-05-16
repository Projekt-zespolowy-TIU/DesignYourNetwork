#include "networkDialog.h"
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

void NetworkDialog::InjectData(Networkv4 network)
{
    this->network = network;
    SetData();
}

void NetworkDialog::SetData()
{
    //ui->networkName->setText();
    ui->imageLabel->setPixmap(QPixmap(":/resources/img/router.png").scaled(120,120));
    //ui->hostCount->setText();
    //ui->subnetCount->setText();
    ui->networkAddressBinary->setText(network.Ip->asStringBin());
    ui->networkAddressDecimal->setText(network.Ip->asStringDec());
    ui->networkMaskBinary->setText(network.Ip->asStringBin());
    ui->networkMaskDecimal->setText(network.Ip->asStringDec());
}
