#ifndef GRAPHENTITYDIALOG_H
#define GRAPHENTITYDIALOG_H

#include <QDialog>
#include <QLineEdit>

class GraphEntityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GraphEntityDialog(QWidget *parent = nullptr);
    ~GraphEntityDialog();

protected:

    QLineEdit *name;
    QLineEdit *addresDecimal;
    QLineEdit *addressBinary;

    QFrame *addressFrame;

    void resizeEditLine(QLineEdit *editLine, int width, int adjust);

private:

};

#endif // GRAPHENTITYDIALOG_H
