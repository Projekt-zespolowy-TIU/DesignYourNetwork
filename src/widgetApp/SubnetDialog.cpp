#include "SubnetDialog.h"
#include "ui_SubnetDialog.h"

using namespace core;

SubnetDialog::SubnetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubnetDialog)
{
    ui->setupUi(this);

    firstHostBinary = ui->firstAddressBinary;
    firstHostDecimal = ui->firstAddressDecimal;
    lastHostBinary = ui->firstAddressBinary;
    lastHostDecimal = ui->firstAddressDecimal;
    broadcastBinary = ui->broadcastAddressBinary;
    broadcastDecimal = ui->broadcastAddressDecimal;
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
    //ui->progressBar->setRange(0, subnet->hostsCapacity().convert_to<unsigned long long>());
    //ui->progressBar->setValue(subnet->HostNumber().convert_to<unsigned long long>());

    ui->subnetAddressBinary->setText(subnet->Ip().asStringBin());
    ui->subnetAddressDecimal->setText(subnet->Ip().asStringDec());
    ui->subnetMaskBinary->setText(subnet->Mask().asStringBin());
    ui->subnetMaskDecimal->setText(subnet->Mask().asStringDec());

    ui->firstAddressBinary->setText(subnet->getMinHost()->asStringBin());
    ui->firstAddressDecimal->setText(subnet->getMinHost()->asStringDec());
    ui->lastAddressBinary->setText(subnet->getMaxHost()->asStringBin());
    ui->lastAddressDecimal->setText(subnet->getMaxHost()->asStringDec());


    //ui->broadcastAddressBinary->setText(dynamic_cast<Subnetv4&>(*subnet).getBroadcast()->asStringBin());
    //ui->broadcastAddressDecimal->setText(dynamic_cast<Subnetv4&>(*subnet).getBroadcast()->asStringDec());

    adjustDataDisplay();
}

void SubnetDialog::adjustDataDisplay()
{
    int editLineAdjust = 15;

    QFontMetrics fm(ui->subnetAddressBinary->font());
    QString myText = ui->subnetAddressBinary->text();
    int calcWidth = fm.width(myText);

    ui->addressFrame->setMinimumWidth(calcWidth + editLineAdjust * 2);

    resizeEditLine(ui->subnetAddressBinary, calcWidth, editLineAdjust);
    resizeEditLine(ui->subnetMaskBinary, calcWidth, editLineAdjust);
    resizeEditLine(ui->firstAddressBinary, calcWidth, editLineAdjust);
    resizeEditLine(ui->lastAddressBinary, calcWidth, editLineAdjust);

    //ui->addressFrame->setGeometry(ui->scrollAreaWidgetContents->geometry());
}

void SubnetDialog::resizeEditLine(QLineEdit *lineEdit, int width, int adjust)
{
    lineEdit->setGeometry(lineEdit->geometry().x(),
                            lineEdit->geometry().y(),
                            width + adjust,
                            lineEdit->geometry().height());
}
void SubnetDialog::on_subnetName_textEdited(const QString& name)
{
    subnet->SubName(name);
}
