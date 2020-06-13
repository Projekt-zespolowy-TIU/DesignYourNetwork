#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include "NetSettingsDialog.h"

#include <QDialog>

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(NetSettingsDialog *netSettingsDialog,
                        QWidget *parent = nullptr);
    ~SaveDialog();

private slots:
    void on_v4Button_clicked();

    void on_v6Button_clicked();

private:
    Ui::SaveDialog *ui;

    NetSettingsDialog *netSettingsDialog;
};

#endif // SAVEDIALOG_H
