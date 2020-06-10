#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QFrame>
#include <QPainter>
#include <QPen>

#include "NetworkDialog.h"
#include "SubnetDialog.h"
#include "HostDialog.h"

#include "core/SubnetsCalculatorV4.h"

using namespace core;

namespace Ui {
class GraphDialog;
}

class GraphDialog : public QDialog
{
    Q_OBJECT

public:

    GraphDialog(QWidget *parent);
    ~GraphDialog();

    void injectData(const std::shared_ptr<INetwork>& net4);

private slots:

     void on_networkButton_clicked(const std::shared_ptr<INetwork>& network);

     void on_subnetButton_clicked(const std::shared_ptr<ISubnet>& subnet);

     void on_hostButton_clicked(const std::shared_ptr<Host>& host);

     void on_scaleSlider_sliderMoved(int position);

     void on_hostNames_toggled(bool checked);

     void on_subnetAddresses_toggled(bool checked);

     void on_networkAddress_toggled(bool checked);

     void on_gridCheckBox_toggled(bool checked);


     void on_gridScaleSlider_sliderMoved(int position);

     void on_hostsInRowSlider_valueChanged(int value);

     void on_subnetsNamesCheckBox_toggled(bool checked);

private:

    Ui::GraphDialog *ui;

    bool showsHostNames = false;
    bool showsSubnetsNames = true;
    bool showsSubnetsAddresses = true;
    bool showsNetworkAddress = true;
    bool showsGrid = true;

    int hostsInRow = 8;
    float scale = 1.0f;
    float gridSize = 1.0f;

    NetworkDialog networkDialog{this};

    SubnetDialog subnetDialog{this};

    HostDialog hostDialog{this};

    QWidget *subnetScrollContent;
    QWidget *subnetGraphContent;
    QFrame *subnetsGraphFrame; 

    std::shared_ptr<INetwork> mainNetwork;

    QHBoxLayout *graphPanelLayout = new QHBoxLayout;

    void drawNetworkGraph();
};

#endif // GRAPHDIALOG_H
