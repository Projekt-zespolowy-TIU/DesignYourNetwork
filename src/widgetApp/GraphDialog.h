#ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QFrame>

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

    void injectData(std::shared_ptr<Networkv4> net4);

private slots:

     void on_networkButton_clicked(std::shared_ptr<Networkv4> network);

     void on_subnetButton_clicked(Subnetv4 subnet);

     void on_hostButton_clicked(std::shared_ptr<Host> host);

     void on_coloredGraphcheckBox_clicked(bool checked);

     void on_verticalViewButton_clicked(bool checked);

     void on_horizontalViewButton_clicked(bool checked);

     void on_scaleSlider_sliderMoved(int position);

     void on_hostNames_toggled(bool checked);

     void on_subnetAddresses_toggled(bool checked);

     void on_networkAddress_toggled(bool checked);

private:

    Ui::GraphDialog *ui;

    bool isVertical = false;
    bool isColored = false;
    bool showsHostNames = false;
    bool showsSubnetAddresses = false;
    bool showsNetworkAddress = false;

    float scale = 1.0f;

    NetworkDialog networkDialog{this};

    SubnetDialog subnetDialog{this};

    HostDialog hostDialog{this};

    QWidget *subnetScrollContent;
    QWidget *subnetGraphContent;
    QFrame *subnetsGraphFrame; 

    std::shared_ptr<Networkv4> mainNetwork;

    QHBoxLayout *graphPanelLayout = new QHBoxLayout(this);

    void drawNetworkGraph();
};

#endif // GRAPHDIALOG_H
