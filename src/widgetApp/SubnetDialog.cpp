#include "SubnetDialog.h"
#include "ui_SubnetDialog.h"

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

    QIcon icon;
    QPixmap pixmap(":/resources/img/switch.png");
    icon.addPixmap(pixmap);
    ui->graphImage->setIconSize(QSize(120,120));
    ui->graphImage->setIcon(icon);

    ui->hostCount->setText(QString::number(subnet->HostNumber));
    ui->hostCapacity->setText(QString::number(subnet->hostsCapacity()));
    ui->progressBar->setRange(0, subnet->hostsCapacity());
    ui->progressBar->setValue(subnet->HostNumber);

    ui->subnetAddressBinary->setText(subnet->Ip->asStringBin());
    ui->subnetAddressDecimal->setText(subnet->Ip->asStringDec());
    ui->subnetMaskBinary->setText(subnet->NetMask->asStringBin());
    ui->subnetMaskDecimal->setText(subnet->NetMask->asStringDec());

    ui->firstAddressBinary->setText(subnet->getMinHost()->asStringBin());
    ui->firstAddressDecimal->setText(subnet->getMinHost()->asStringDec());
    ui->lastAddressBinary->setText(subnet->getMaxHost()->asStringBin());
    ui->lastAddressDecimal->setText(subnet->getMaxHost()->asStringDec());

    ui->broadcastAddressBinary->setText(subnet->getBroadcast()->asStringBin());
    ui->broadcastAddressDecimal->setText(subnet->getBroadcast()->asStringDec());

}

void SubnetDialog::on_subnetName_textEdited(const QString &arg1)
{
    subnet->SubName = arg1;
}
