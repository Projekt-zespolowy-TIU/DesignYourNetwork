#include "SaveDialog.h"
#include "ui_SaveDialog.h"

SaveDialog::SaveDialog(NetSettingsDialog *netSettingsDialog,
                       QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveDialog)
{
    ui->setupUi(this);

    this->netSettingsDialog = netSettingsDialog;
}

SaveDialog::~SaveDialog()
{
    delete ui;
}

void SaveDialog::on_v4Button_clicked()
{
    netSettingsDialog->saveData(false);
    this->hide();
}

void SaveDialog::on_v6Button_clicked()
{
    netSettingsDialog->saveData(true);
    this->hide();
}
