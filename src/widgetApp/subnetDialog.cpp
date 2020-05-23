#include "subnetDialog.h"
#include "ui_subnetdialog.h"

using namespace core;

SubnetDialog::SubnetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubnetDialog)
{
    ui->setupUi(this);
}

SubnetDialog::~SubnetDialog()
{
    delete ui;
}


void SubnetDialog::InjectData(std::shared_ptr<Subnet> subnet)
{
    this->subnet = subnet;
    SetData();
}

void SubnetDialog::SetData()
{
    ui->subnetName->setText(subnet->SubName);
    ui->imageLabel->setPixmap(QPixmap(":/resources/img/switch.png").scaled(120,120));
    ui->hostCount->setText(QString::fromStdString(std::to_string(subnet->hostsCapacity())));
    ui->subnetAddressBinary->setText(subnet->Ip->asStringBin());
    ui->subnetAddressDecimal->setText(subnet->Ip->asStringDec());
    ui->subnetMaskBinary->setText(subnet->Ip->asStringBin());
    ui->subnetMaskDecimal->setText(subnet->Ip->asStringDec());
}
