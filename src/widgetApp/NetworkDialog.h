#ifndef NETWORKDIALOG_H
#define NETWORKDIALOG_H

#include <QDialog>
#include <QLineEdit>

#include "core/INetwork.h"
#include "GraphEntityDialog.h"

using namespace core;

namespace Ui {
class NetworkDialog;
}

class NetworkDialog : public GraphEntityDialog
{
    Q_OBJECT

public:

    NetworkDialog(QWidget *parent);
    ~NetworkDialog();

    void InjectData(const std::shared_ptr<INetwork>& network);

    void SetData();

private slots:


private:

    Ui::NetworkDialog *ui;

    std::shared_ptr<INetwork> network;

    cpp_int subnetCount;

    cpp_int hostCount;

    QLineEdit *maskDecimal;
    QLineEdit *maskBinary;

    void adjustDataDisplay();
};

#endif // NETWORK DIALOG_H
