#include "ReadDialog.h"
#include "ui_ReadDialog.h"

ReadDialog::ReadDialog(NetSettingsDialog *netSettingsDialog,
                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReadDialog)
{
    ui->setupUi(this);

    this->netSettingDialog = netSettingsDialog;
}

ReadDialog::~ReadDialog()
{
    delete ui;
}

void ReadDialog::on_v4Button_clicked()
{
    netSettingDialog->readData(false);
    this->hide();
}

void ReadDialog::on_v6Button_clicked()
{
    netSettingDialog->readData(true);
    this->hide();
}
