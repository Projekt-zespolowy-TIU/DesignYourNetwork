#ifndef SUBNETDIALOG_H
#define SUBNETDIALOG_H

#include <QDialog>
#include <QtCore>
#include <QLineEdit>

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
    Ui::SubnetDialog *ui;

    std::shared_ptr<ISubnet> subnet;

    QLineEdit *firstHostDecimal;
    QLineEdit *lastHostDecimal;
    QLineEdit *broadcastDecimal;

    QLineEdit *firstHostBinary;
    QLineEdit *lastHostBinary;
    QLineEdit *broadcastBinary;

    void adjustDataDisplay();

    void resizeEditLine(QLineEdit *editLine, int width, int adjust);
};

#endif // SUBNETDIALOG_H
