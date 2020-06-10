#ifndef MANUALDIALOG_H
#define MANUALDIALOG_H

#include <QDialog>

namespace Ui {
class ManualDialog;
}

class ManualDialog : public QDialog
{
    Q_OBJECT

public:
    ManualDialog(QWidget *parent);
    ~ManualDialog();

private:
    Ui::ManualDialog *ui;
};

#endif // MANUALDIALOG_H
