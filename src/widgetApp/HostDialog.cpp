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

void HostDialog::InjectData(const std::shared_ptr<Host>& host)
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

    adjustDataDisplay();
}

void HostDialog::adjustDataDisplay()
{
    int editLineAdjust = 15;

    QFontMetrics fm(ui->hostAddressBinary->font());
    QString myText = ui->hostAddressBinary->text();
    int calcWidth = fm.width(myText);

    ui->addressFrame->setMinimumWidth(calcWidth + editLineAdjust * 2);

    resizeEditLine(ui->hostAddressBinary, calcWidth, editLineAdjust);

    //ui->addressFrame->setGeometry(ui->scrollAreaWidgetContents->geometry());
}

void HostDialog::resizeEditLine(QLineEdit *lineEdit, int width, int adjust)
{
    lineEdit->setGeometry(lineEdit->geometry().x(),
                            lineEdit->geometry().y(),
                            width + adjust,
                            lineEdit->geometry().height());
}

void HostDialog::on_hostName_textEdited(const QString& name)
{
    host->Name(name);
}
