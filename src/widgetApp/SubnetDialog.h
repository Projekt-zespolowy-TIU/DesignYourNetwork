#ifndef SUBNETDIALOG_H
#define SUBNETDIALOG_H

#include <QDialog>
#include <QtCore>

#include "IPv4parser.h"
#include "SubnetsCalculatorV4.h"

using namespace core;

namespace Ui {
class SubnetDialog;
}

class SubnetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SubnetDialog(QWidget *parent = nullptr);
    ~SubnetDialog();

    void InjectData(std::shared_ptr<Subnet> subnet);

    void SetData();

private slots:

    void on_subnetName_textEdited(const QString &arg1);

private:
    Ui::SubnetDialog *ui;

    std::shared_ptr<Subnet> subnet;
};

#endif // SUBNETDIALOG_H
