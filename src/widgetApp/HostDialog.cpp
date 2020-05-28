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
    ui->hostId->setText(QString::number(host.Number));

    QIcon icon;
    QPixmap pixmap(":/resources/img/host.png");
    icon.addPixmap(pixmap);
    ui->graphImage->setIconSize(QSize(120,120));
    ui->graphImage->setIcon(icon);
    ui->idLine->setText(QString::number(host.Number));

    ui->hostAddressBinary->setText(host.Ip->asStringBin());
    ui->hostAddressDecimal->setText(host.Ip->asStringDec());
    ui->hostMaskBinary->setText(host.Ip->asStringBin());
    ui->hostMaskDecimal->setText(host.Ip->asStringDec());
}

