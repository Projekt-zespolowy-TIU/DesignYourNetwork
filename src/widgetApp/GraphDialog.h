 #ifndef GRAPHDIALOG_H
#define GRAPHDIALOG_H

#include <QDialog>
#include <QLayout>
#include <QFrame>

#include "NetworkDialog.h"
#include "SubnetDialog.h"
#include "HostDialog.h"
#include "SubnetsCalculatorV4.h"

using namespace core;

namespace Ui {
class GraphDialog;
}

class GraphDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GraphDialog(Networkv4 mainNetwork,
        std::vector<std::shared_ptr<Subnet>> subnets, QWidget *parent = nullptr);
    ~GraphDialog();


private slots:

     void on_networkButton_clicked(Networkv4 network);

     void on_subnetButton_clicked(std::shared_ptr<Subnet> subnet);

     void on_hostButton_clicked(Subnet::Host host);

     void on_coloredGraphcheckBox_clicked(bool checked);

     void on_verticalViewButton_clicked(bool checked);

     void on_horizontalViewButton_clicked(bool checked);

     void on_scaleSlider_sliderMoved(int position);

private:
    Ui::GraphDialog *ui;

    bool isVertical = false;
    bool isColored = false;

    float scale = 1.0f;

    NetworkDialog networkDialog;

    SubnetDialog subnetDialog;

    HostDialog hostDialog;

    QWidget *subnetScrollContent;
    QWidget *subnetGraphContent;
    QFrame *subnetsGraphFrame;
    QHBoxLayout *graphPanelLayout = new QHBoxLayout();

    Networkv4 mainNetwork;

    std::vector<std::shared_ptr<Subnet>> subnets;

   void drawNetworkGraph(bool isVertical, bool isColored);
;
};

#endif // GRAPHDIALOG_H
