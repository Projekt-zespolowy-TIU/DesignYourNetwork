#include "HostDialog.h"
#include "ui_HostDialog.h"

HostDialog::HostDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HostDialog)
{
    ui->setupUi(this);
}

HostDialog::~HostDialog()
{
    delete ui;
}

void HostDialog::InjectData(Subnet::Host host)
{
    this->host = host;
    SetData();
}

void HostDialog::SetData()
{
    ui->hostName->setText(host.Name);
    ui->hostImageLabel->setPixmap(QPixmap(":/resources/img/host.png").scaled(120,120));
    ui->hostAddressBinary->setText(host.Ip->asStringBin());
    ui->hostAddressDecimal->setText(host.Ip->asStringDec());
    ui->hostMaskBinary->setText(host.Ip->asStringBin());
    ui->hostMaskDecimal->setText(host.Ip->asStringDec());
}

