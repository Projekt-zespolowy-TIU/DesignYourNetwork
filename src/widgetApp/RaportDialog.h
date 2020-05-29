#ifndef RAPORTDIALOG_H
#define RAPORTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>

#include "IPstructs.h"

using namespace core;

namespace Ui {
class RaportDialog;
}

class RaportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RaportDialog(Networkv4 network, std::vector<std::shared_ptr<Subnet>> subnets,
                          QWidget *parent = nullptr);
    ~RaportDialog();

private:
    Ui::RaportDialog *ui;

    Networkv4 network;
    std::vector<std::shared_ptr<Subnet>> subnets;

    QVBoxLayout *raportLayout = new QVBoxLayout();

    void displayNetworkRaport();
};

#endif // RAPORTDIALOG_H
