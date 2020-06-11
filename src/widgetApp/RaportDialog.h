#ifndef RAPORTDIALOG_H
#define RAPORTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>

#include "core/INetwork.h"
#include "core/IReportGenerator.h"

using namespace core;

namespace Ui {
class RaportDialog;
}

class RaportDialog : public QDialog
{
    Q_OBJECT

public:

    RaportDialog(QWidget *parent);

    ~RaportDialog();

    void displayNetworkRaport();

    void injectData(const std::shared_ptr<INetwork>& net4, std::unique_ptr<IReportGenerator> reportEngine);

private slots:

    void on_saveButton_clicked();

    void on_checkBox_toggled(bool checked);

private:

    Ui::RaportDialog *ui;

    bool isDetailed = false;

    std::shared_ptr<INetwork> network;

    std::unique_ptr<IReportGenerator> reportGenerator;

    QBoxLayout *raportLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    QTextEdit *raportText = new QTextEdit(this);
};

#endif // RAPORTDIALOG_H
