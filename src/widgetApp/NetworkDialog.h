#ifndef NETWORKDIALOG_H
#define NETWORKDIALOG_H

#include <QDialog>

#include "core/Networkv4.h"

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

    void InjectData(Networkv4 network);

    void SetData();

private slots:


private:

    Ui::NetworkDialog *ui;

    Networkv4 network;

    cpp_int subnetCount;

    cpp_int hostCount;
};

#endif // NETWORK DIALOG_H
