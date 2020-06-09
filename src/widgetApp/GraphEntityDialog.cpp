#include "GraphEntityDialog.h"


GraphEntityDialog::GraphEntityDialog(QWidget *parent) :
    QDialog(parent)

{

}

GraphEntityDialog::~GraphEntityDialog()
{

}

void GraphEntityDialog::resizeEditLine(QLineEdit *lineEdit, int width, int adjust)
{
    lineEdit->setGeometry(lineEdit->geometry().x(),
                            lineEdit->geometry().y(),
                            width + adjust,
                            lineEdit->geometry().height());
}
