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

void HostDialog::InjectData(std::shared_ptr<Host> host)
{
    this->host = host;
    SetData();
}

void HostDialog::SetData()
{

    ui->hostName->setText(host->Name());
    ui->hostId->setText(QString::fromStdString(host->Id().str()));

    QIcon icon;
    QPixmap pixmap(":/resources/img/host.png");
    icon.addPixmap(pixmap);
    ui->graphImage->setIconSize(QSize(120,120));
    ui->graphImage->setIcon(icon);
    ui->idLine->setText(QString::fromStdString(host->Id().str()));

    ui->hostAddressBinary->setText(host->Ip().asStringBin());
    ui->hostAddressDecimal->setText(host->Ip().asStringDec());
}


void HostDialog::on_hostName_textEdited(const QString &name)
{
    host->Name(name);
}
