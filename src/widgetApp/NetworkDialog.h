#ifndef NETWORKDIALOG_H
#define NETWORKDIALOG_H

#include <QDialog>
#include "IPstructs.h"

using namespace core;

namespace Ui {
class NetworkDialog;
}

class NetworkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkDialog(QWidget *parent = nullptr);
    ~NetworkDialog();

    void InjectData(Networkv4 network,
        std::vector<std::shared_ptr<Subnet>> subnets);

    void SetData();

private slots:


private:
    Ui::NetworkDialog *ui;

    Networkv4 network;

    int subnetCount;

    int hostCount;
};

#endif // NETWORK DIALOG_H
