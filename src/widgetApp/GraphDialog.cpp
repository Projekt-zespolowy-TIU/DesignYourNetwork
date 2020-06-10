#include "GraphDialog.h"
#include "ui_GraphDialog.h"
#include "NetworkButton.h"
#include "SubnetButton.h"
#include "HostButton.h"
#include "GraphFrame.h"

#include <QLayout>
#include <QPushButton>
#include <QLabel>

GraphDialog::GraphDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphDialog)
{
    ui->setupUi(this);

    subnetGraphContent = ui-> graphScroll;

    subnetGraphContent->setLayout(graphPanelLayout);    
}

GraphDialog::~GraphDialog()
{
    delete ui;
}

void GraphDialog::injectData(const std::shared_ptr<INetwork>& net4)
{
    mainNetwork = net4;
    drawNetworkGraph();
}

void GraphDialog::drawNetworkGraph()
{
    subnetsGraphFrame = new QFrame(this);

    QList<SubnetButton*> subnetButtons = QList<SubnetButton*>();

    QList<QWidget*> hostsFrames = QList<QWidget*>();

    QLayoutItem *child;
    while ((child = subnetGraphContent->layout()->takeAt(0)) != nullptr)
    {
        if(child->widget())
        {
            delete child->widget();
        }
        delete child;
    }

    QFrame *graphNetworkFrame = new QFrame(this);
    graphNetworkFrame->setStyleSheet("background-color: rgb(0,0,0,0)");
    if(isColored) graphNetworkFrame->
            setStyleSheet("border-color: rgb(220,220,220);\nborder-width :"
                          " 4px;\nborder-style:solid;");
    graphNetworkFrame->setLayout(new QVBoxLayout);
    NetworkButton *networkButton = new NetworkButton(mainNetwork, this);
    networkButton->setStyleSheet("background-color: rgb(70,70,70)");
    QIcon networkIcon;
    QPixmap pixmap(":/resources/img/router.png");
    networkIcon.addPixmap(pixmap);
    networkButton->setIconSize(QSize(50,50) * scale);
    networkButton->setIcon(networkIcon);
    networkButton->setFlat(true);
    networkButton->setMinimumSize(QSize(50,50) * scale);
    networkButton->setMaximumSize(QSize(50,50) * scale);
    graphNetworkFrame->layout()->addWidget(networkButton);

    connect(networkButton, SIGNAL(clicked(std::shared_ptr<INetwork>)), this,
            SLOT(on_networkButton_clicked(std::shared_ptr<INetwork>)));
     QLabel *networkAddress = new QLabel(mainNetwork->Ip().asStringDec() +
                                            " / " + mainNetwork->Mask().asStringDec(), this);

     graphNetworkFrame->layout()->addWidget(networkAddress);
     networkAddress->setStyleSheet("font-weight: bold");
     networkAddress->setAlignment(Qt::AlignTop);

    if(isVertical)
        subnetsGraphFrame->setLayout(new QVBoxLayout);
    else
    {
        subnetsGraphFrame->setLayout(new QHBoxLayout);
        graphNetworkFrame->layout()->setAlignment(Qt::AlignHCenter);
    }

    subnetsGraphFrame->layout()->setSpacing(50 * scale);
    graphNetworkFrame->layout()->addWidget(subnetsGraphFrame);

    for(size_t i = 0; i < mainNetwork->Subnets().size(); i++)
    {
         QFrame *subnetFrame = new QFrame(this);
         subnetFrame->setLayout(new QVBoxLayout());

         subnetsGraphFrame->layout()->addWidget(subnetFrame);

         if(isColored) subnetFrame->
                 setStyleSheet("border-color: rgb(38,14,84);\nborder-width :"
                               " 4px;\nborder-style:solid;");
         QFrame *subnetButtonFrame = new QFrame(this);
         subnetButtonFrame->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
         subnetFrame->layout()->addWidget(subnetButtonFrame);

         SubnetButton *subnetButton = new SubnetButton(mainNetwork->Subnets().at(i), this);
         subnetButton->setStyleSheet("background-color: rgb(70,70,70)");

         QIcon subnetIcon;
         QPixmap pixmap(":/resources/img/switch.png");
         subnetIcon.addPixmap(pixmap);
         subnetButton->setIconSize(QSize(40,40) * scale);
         subnetButton->setIcon(subnetIcon);
         subnetButton->setMinimumSize(QSize(40,40) * scale);
         subnetButton->setMaximumSize(QSize(40,40) * scale);
         subnetButtonFrame->layout()->addWidget(subnetButton);
         subnetButtonFrame->layout()->setAlignment(subnetButton, Qt::AlignVCenter);

         connect(subnetButton, SIGNAL(clicked(std::shared_ptr<ISubnet>)), this,
                 SLOT(on_subnetButton_clicked(std::shared_ptr<ISubnet>)));

         QLabel *subnetName = new QLabel(mainNetwork->Subnets().at(i)->SubName());
         QLabel *subnetAddress = new QLabel(mainNetwork->Subnets().at(i)->Ip().asStringDec() +
                                            " / " + mainNetwork->Subnets().at(i)->Mask().asStringDec(), this);

         subnetAddress->setStyleSheet("font-weight: bold");
         subnetAddress->setAlignment(Qt::AlignHCenter);
         subnetName->setStyleSheet("font-weight: bold");
         subnetName->setAlignment(Qt::AlignHCenter);
         subnetFrame->layout()->addWidget(subnetAddress);
         subnetFrame->layout()->addWidget(subnetName);
         subnetFrame->layout()->setAlignment(Qt::AlignVCenter);

         subnetButtons.append(subnetButton);

         QFrame *hostsFrame = new QFrame(this);
         hostsFrame->setLayout(new QVBoxLayout());
         subnetFrame->layout()->addWidget(hostsFrame);
         hostsFrames.append(subnetAddress);

         QHBoxLayout *hostsLayout;

         for(int j = 0; j < mainNetwork->Subnets().at(i)->HostNumber(); j++)
         {
            if((j + hostsInRow) % hostsInRow == 0)
            {
                hostsLayout = new QHBoxLayout;
                QFrame *hostsRow = new QFrame(this);
                subnetFrame->layout()->addWidget(hostsRow);
                hostsRow->setLayout(hostsLayout);
                hostsFrame->layout()->addWidget(hostsRow);
                hostsRow->layout()->setAlignment(Qt::AlignCenter);

                float scaleAdjust = hostsInRow / 4;
                hostsRow->setMaximumWidth((450 * scale) * scaleAdjust);
            }

            QVBoxLayout *hostLayout = new QVBoxLayout;
            QFrame *hostFrame = new QFrame(this);
            hostFrame->setLayout(hostLayout);
            hostFrame->setMaximumHeight(100 * scale);

            if(isColored) hostFrame->
                    setStyleSheet("border-color: rgb(38,94,84);\nborder-width :"
                                  " 4px;\nborder-style:solid;");

            HostButton *hostButton = new HostButton(mainNetwork->Subnets().at(i)->HostsList().at(j), this);
            connect(hostButton, SIGNAL(clicked(std::shared_ptr<Host>)),
                    this, SLOT(on_hostButton_clicked(std::shared_ptr<Host>)));

            hostButton->setFlat(true);
            QIcon hostIcon;
            QPixmap hostPixmap(":/resources/img/host.png");
            hostIcon.addPixmap(hostPixmap);
            hostButton->setIconSize(QSize(30,30) * scale);
            hostButton->setIcon(hostIcon);
            hostButton->setMinimumSize(QSize(30,30) * scale);
            hostButton->setMaximumSize(QSize(30,30) * scale);
            hostLayout->addWidget(hostButton);
            hostsLayout->addWidget(hostFrame);

            if(showsHostNames)
            {
                QLabel *hostName = new QLabel(mainNetwork->Subnets().at(i)->HostsList().at(j)->Name(), this);
                QFont font;
                font.setPointSize(7 * scale);
                hostName->setFont(font);
                hostName->setMinimumSize(QSize(40,10) * scale);
                hostName->setMaximumSize(QSize(50,20) * scale);
                hostName->setAlignment(Qt::AlignHCenter);
                hostLayout->addWidget(hostName);            
            }
         }      
    }

    GraphFrame *graphFrame = new GraphFrame(networkButton, subnetButtons, hostsFrames,
                                            graphNetworkFrame, showsGrid, gridSize, this);

    graphFrame->setLayout(new QVBoxLayout());

    subnetGraphContent->layout()->addWidget(graphFrame);

    graphFrame->layout()->addWidget(graphNetworkFrame);


}
void GraphDialog::on_hostButton_clicked(const std::shared_ptr<Host>& host)
{
    hostDialog.setModal(true);
    hostDialog.InjectData(host);
    hostDialog.exec();
}

void GraphDialog::on_subnetButton_clicked(const std::shared_ptr<ISubnet>& subnet)
{
    subnetDialog.setModal(true);
    subnetDialog.InjectData(subnet);
    subnetDialog.exec();
}

void GraphDialog::on_networkButton_clicked(const std::shared_ptr<INetwork>& network)
{
    networkDialog.setModal(true);
    networkDialog.InjectData(network);
    networkDialog.exec();
}

void GraphDialog::on_coloredGraphcheckBox_clicked(bool checked)
{
    isColored = checked;
    drawNetworkGraph();
}

void GraphDialog::on_verticalViewButton_clicked(bool checked)
{
    isVertical = checked;
    drawNetworkGraph();
}

void GraphDialog::on_horizontalViewButton_clicked(bool checked)
{
    isVertical = !checked;
    drawNetworkGraph();
}

void GraphDialog::on_scaleSlider_sliderMoved(int position)
{
    scale = static_cast<float>(position) / 10.0f;

}

void GraphDialog::on_hostNames_toggled(bool checked)
{
    showsHostNames = checked;
    drawNetworkGraph();
}

void GraphDialog::on_subnetAddresses_toggled(bool checked)
{
    showsSubnetAddresses = checked;
    drawNetworkGraph();
}

void GraphDialog::on_networkAddress_toggled(bool checked)
{
    showsNetworkAddress = checked;
    drawNetworkGraph();
}

void GraphDialog::on_gridCheckBox_toggled(bool checked)
{
    showsGrid = checked;
    drawNetworkGraph();
}


void GraphDialog::on_gridScaleSlider_sliderMoved(int position)
{
    gridSize = static_cast<float>(position) / 10.0f;
    drawNetworkGraph();
}

void GraphDialog::on_hostsInRowSlider_valueChanged(int value)
{
    hostsInRow = value;
    drawNetworkGraph();
}
