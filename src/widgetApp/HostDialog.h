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

    explicit HostDialog(QWidget *parent = nullptr);
    ~HostDialog();

    void InjectData(Host);

    void SetData();

private slots:

    void on_hostName_textEdited(const QString &arg1);

private:

    Ui::HostDialog *ui;

    Host host;
};

#endif // HOSTDIALOG_H
