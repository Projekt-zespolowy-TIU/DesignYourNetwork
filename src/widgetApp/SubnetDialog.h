#ifndef SUBNETDIALOG_H
#define SUBNETDIALOG_H

#include <QDialog>
#include <QtCore>

#include "core/SubnetsCalculatorV4.h"

using namespace core;

namespace Ui {
class SubnetDialog;
}

class SubnetDialog : public QDialog
{
    Q_OBJECT

public:
    SubnetDialog(QWidget *parent);
    ~SubnetDialog();

    void InjectData(Subnetv4 subnet);

    void SetData();

private slots:

    void on_subnetName_textEdited(const QString &arg1);

private:
    Ui::SubnetDialog *ui;

    Subnetv4 subnet;
};

#endif // SUBNETDIALOG_H
