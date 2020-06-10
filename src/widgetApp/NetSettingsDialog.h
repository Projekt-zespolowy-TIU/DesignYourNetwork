#ifndef NETSETTINGSDIALOG_H
#define NETSETTINGSDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QtCore>
#include <QSpinBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

#include "NetworkButton.h"
#include "NetworkDialog.h"
#include "SubnetButton.h"
#include "SubnetDialog.h"
#include "HostButton.h"
#include "HostDialog.h"
#include "GraphDialog.h"
#include "RaportDialog.h"

#include "core/INetwork.h"
#include "core/SubnetsCalculatorV4.h"
#include "core/SubnetsCalculatorV6.h"


namespace Ui {
class NetSettingsDialog;
}

class NetSettingsDialog : public QDialog
{
    Q_OBJECT

public:

    explicit NetSettingsDialog(QWidget *parent = nullptr);
    ~NetSettingsDialog();

    void clearData();

    void readData();

private slots:

    void on_calculateButton_clicked();

    void on_drawButton_clicked();

    void on_hostNumberSpinBox_valueChanged(int subnetCount);

    void on_raportButton_clicked();

    void on_toolBox_currentChanged(int index);

    void on_hostNumberSpinBoxv6_valueChanged(int subnetCount);

private:

    Ui::NetSettingsDialog *ui;

    bool isIpv6 = false;
    bool isHorizontal = false;

    std::shared_ptr<INetwork> mainNetwork;
    SubnetsCalculatorV4 calculatorv4;
    SubnetsCalculatorV6 calculatorv6;

    QWidget *addressWidget;
    QWidget *maskWidget;
    QWidget *binaryAddressWidget;
    QWidget *binaryMaskWidget;

    QWidget *address6Widget;
    QWidget *mask6Widget;
    QWidget *binaryAddress6Widget;
    QWidget *binaryMask6Widget;

    QSpinBox *subnetCountBox;
    QWidget *subnetScrollContent;
    QWidget *subnetGraphContent;

    QSpinBox *subnetCountBoxv6;
    QWidget *subnetScrollContentv6;
    QWidget *subnetGraphContentv6;

    QFrame *subnetsGraphFrame;

    QList<QSpinBox*> spinBoxList = QList<QSpinBox*>{};
    QList<QLineEdit*> subnetNames = QList<QLineEdit*>{};

    QList<QSpinBox*> spinBoxListv6 = QList<QSpinBox*>{};
    QList<QLineEdit*> subnetNamesv6 = QList<QLineEdit*>{};

    RaportDialog raportDialog{this};

    GraphDialog graphDialog{this};

    void setSubnets(QList<QSpinBox*> countWidgets, QList<QLineEdit*> nameLines);

    void drawNetworkGraph();

    void deleteLayoutContent(QWidget *content);

    void displayInputInBinary(const QString &input, QWidget *displayWidget);

    QString takeStringFromInputFields(QWidget *inputWidget, char separator);

    void updateSubnetsPanel(QList<QSpinBox*> *countWidgets, QList<QLineEdit*> *nameLines,
                            QWidget *subnetScrollContent, int subnetCount);
};

#endif // NETSETTINGSDIALOG_H
