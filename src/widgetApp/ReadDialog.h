#ifndef READDIALOG_H
#define READDIALOG_H

#include "NetSettingsDialog.h"

#include <QDialog>

namespace Ui {
class ReadDialog;
}

class ReadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReadDialog(NetSettingsDialog *netSettingDialog,
                        QWidget *parent = nullptr);
    ~ReadDialog();

private slots:
    void on_v4Button_clicked();

    void on_v6Button_clicked();

private:
    Ui::ReadDialog *ui;

    NetSettingsDialog *netSettingDialog;
};

#endif // READDIALOG_H
