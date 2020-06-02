#ifndef RAPORTDIALOG_H
#define RAPORTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>

#include "core/Networkv4.h"

using namespace core;

namespace Ui {
class RaportDialog;
}

class RaportDialog : public QDialog
{
    Q_OBJECT

public:

    explicit RaportDialog( QWidget *parent = nullptr);

    ~RaportDialog();

    void injectData(Networkv4 network);

    void displayNetworkRaport();

private slots:

    void on_saveButton_clicked();

    void on_checkBox_toggled(bool checked);

private:

    Ui::RaportDialog *ui;

    bool isDetailed = false;

    Networkv4 network;

    QVBoxLayout *raportLayout = new QVBoxLayout();

    QTextEdit *raportText = new QTextEdit();
};

#endif // RAPORTDIALOG_H
