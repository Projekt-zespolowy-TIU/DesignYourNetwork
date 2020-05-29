#ifndef RAPORTDIALOG_H
#define RAPORTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>

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

private slots:

    void on_saveButton_clicked();

private:
    Ui::RaportDialog *ui;

    Networkv4 network;
    std::vector<std::shared_ptr<Subnet>> subnets;

    QVBoxLayout *raportLayout = new QVBoxLayout();

    QTextEdit *raportText = new QTextEdit();

    void displayNetworkRaport();
};

#endif // RAPORTDIALOG_H
