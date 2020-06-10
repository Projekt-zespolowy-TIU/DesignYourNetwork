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

void SubnetDialog::InjectData(const std::shared_ptr<ISubnet>& subnet)
{
    this->subnet = subnet;
    SetData();
}

void SubnetDialog::SetData()
{
    ui->subnetName->setText(subnet->SubName());

    QIcon icon;
    QPixmap pixmap(":/resources/img/switch.png");
    icon.addPixmap(pixmap);
    ui->graphImage->setIconSize(QSize(120,120));
    ui->graphImage->setIcon(icon);

    ui->hostCount->setText(QString::fromStdString(subnet->HostNumber().str()));
    ui->hostCapacity->setText(QString::fromStdString(subnet->hostsCapacity().str()));

    ui->subnetAddressBinary->setText(subnet->Ip().asStringBin());
    ui->subnetAddressDecimal->setText(subnet->Ip().asStringDec());
    ui->subnetMaskBinary->setText(subnet->Mask().asStringBin());
    ui->subnetMaskDecimal->setText(subnet->Mask().asStringDec());

    ui->firstAddressBinary->setText(subnet->getMinHost()->asStringBin());
    ui->firstAddressDecimal->setText(subnet->getMinHost()->asStringDec());
    ui->lastAddressBinary->setText(subnet->getMaxHost()->asStringBin());
    ui->lastAddressDecimal->setText(subnet->getMaxHost()->asStringDec());

    auto subnetv4 = dynamic_cast<Subnetv4*>(subnet.get());

    if(subnetv4)
    {
        isIpv4 = true;

        ui->progressBar->setRange(0, subnet->hostsCapacity().convert_to<unsigned long long>());
        ui->progressBar->setValue(subnet->HostNumber().convert_to<unsigned long long>());
        ui->broadcastAddressBinary->setText(dynamic_cast<Subnetv4&>(*subnet).getBroadcast()->asStringBin());
        ui->broadcastAddressDecimal->setText(dynamic_cast<Subnetv4&>(*subnet).getBroadcast()->asStringDec());

    }
    else
    {
        isIpv4 = false;
    }

    ui->progressBar->setVisible(isIpv4);
    ui->broadcastAddressBinary->setVisible(isIpv4);
    ui->broadcastAddressDecimal->setVisible(isIpv4);
    ui->broadcastBinLabel->setVisible(isIpv4);
    ui->broadcastDecLabel->setVisible(isIpv4);
}

void SubnetDialog::on_subnetName_textEdited(const QString& name)
{
    subnet->SubName(name);
}
