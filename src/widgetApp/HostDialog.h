#ifndef HOSTDIALOG_H
#define HOSTDIALOG_H

#include <QDialog>

#include "core/Host.h"

using namespace core;

namespace Ui {
class HostDialog;
}

class HostDialog : public QDialog
{
    Q_OBJECT

public:

    HostDialog(QWidget *parent);
    ~HostDialog();

    void InjectData(std::shared_ptr<Host>);

    void SetData();

private slots:

    void on_hostName_textEdited(const QString &arg1);

private:

    Ui::HostDialog *ui;

    std::shared_ptr<Host> host;
};

#endif // HOSTDIALOG_H
