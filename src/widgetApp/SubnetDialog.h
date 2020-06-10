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

    void InjectData(const std::shared_ptr<ISubnet>& subnet);

    void SetData();

private slots:

    void on_subnetName_textEdited(const QString& name);

private:

    bool isIpv4 = false;

    Ui::SubnetDialog *ui;

    std::shared_ptr<ISubnet> subnet;
};

#endif // SUBNETDIALOG_H
