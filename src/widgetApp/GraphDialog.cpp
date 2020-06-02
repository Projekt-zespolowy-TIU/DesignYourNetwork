#include "GraphDialog.h"
#include "ui_GraphDialog.h"
#include "NetworkButton.h"
#include "SubnetButton.h"
#include "HostButton.h"

#include <QLayout>
#include <QPushButton>
#include <QLabel>

GraphDialog::GraphDialog(Networkv4 mainNetwork, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphDialog),
    mainNetwork{IPv4address{}, IPv4mask{}}
{
    this->mainNetwork = mainNetwork;

    ui->setupUi(this);

    subnetGraphContent = ui-> graphScroll;

    subnetGraphContent->setLayout(graphPanelLayout);

    drawNetworkGraph();
}

GraphDialog::~GraphDialog()
{
    delete ui;
}

void GraphDialog::drawNetworkGraph()
{

    subnetsGraphFrame = new QFrame();
    subnetsGraphFrame->setStyleSheet("border-width : 0px;");

    QLayoutItem *child;
    while ((child = subnetGraphContent->layout()->takeAt(0)) != NULL)
    {
        if(child->widget() != NULL)
        {
            delete child->widget();
        }
        delete child;
    }


    QFrame *graphNetworkFrame = new QFrame();
    if(isColored) graphNetworkFrame->
            setStyleSheet("border-color: rgb(220,220,220);\nborder-width :"
                          " 4px;\nborder-style:solid;");

    subnetGraphContent->layout()->addWidget(graphNetworkFrame);
    graphNetworkFrame->setLayout(new QVBoxLayout());

    QString routerButtonText = QString{'R'} + '1';
    NetworkButton *networkButton = new NetworkButton(mainNetwork);
    QIcon networkIcon;
    QPixmap pixmap(":/resources/img/router.png");
    networkIcon.addPixmap(pixmap);
    networkButton->setIconSize(QSize(50,50) * scale);
    networkButton->setIcon(networkIcon);
    networkButton->setFlat(true);
    networkButton->setMinimumSize(QSize(50,50) * scale);
    networkButton->setMaximumSize(QSize(50,50) * scale);
    graphNetworkFrame->layout()->addWidget(networkButton);

    connect(networkButton, SIGNAL(clicked(Networkv4)), this,
            SLOT(on_networkButton_clicked(Networkv4)));

    if(showsNetworkAddress)
    {
        QLabel *networkAddress = new QLabel(mainNetwork.Ip().asStringDec() +
                                            " / " + mainNetwork.Mask().asStringDec());
        networkAddress->setAlignment(Qt::AlignTop);
        graphNetworkFrame->layout()->addWidget(networkAddress);
    }

    subnetsGraphFrame->setStyleSheet("border-width : 0px;");
    if(isVertical)
        subnetsGraphFrame->setLayout(new QVBoxLayout());
    else  subnetsGraphFrame->setLayout(new QHBoxLayout());

    subnetsGraphFrame->layout()->setSpacing(50 * scale);
    graphNetworkFrame->layout()->addWidget(subnetsGraphFrame);

    for(size_t i = 0; i < mainNetwork.Subnets().size(); i++)
    {
         QVBoxLayout *frameLayout = new QVBoxLayout();

         QFrame *subnetFrame = new QFrame();
         subnetFrame->setLayout(frameLayout);
         subnetsGraphFrame->layout()->addWidget(subnetFrame);

         if(isColored) subnetFrame->
                 setStyleSheet("border-color: rgb(38,94,84);\nborder-width :"
                               " 4px;\nborder-style:solid;");

         SubnetButton *subnetButton = new SubnetButton(mainNetwork.Subnets().at(i));
         QString subButtonText = 'S' + QString::number(1 + i);
         QIcon subnetIcon;
         QPixmap pixmap(":/resources/img/switch.png");
         subnetIcon.addPixmap(pixmap);
         subnetButton->setIconSize(QSize(40,40) * scale);
         subnetButton->setIcon(subnetIcon);
         subnetButton->setMinimumSize(QSize(40,40) * scale);
         subnetButton->setMaximumSize(QSize(40,40) * scale);
         subnetFrame->layout()->addWidget(subnetButton);

         connect(subnetButton, SIGNAL(clicked(Subnetv4)), this,
                 SLOT(on_subnetButton_clicked(Subnetv4)));

         if(showsSubnetAddresses)
         {
             QLabel *subnetAddress = new QLabel(mainNetwork.Subnets().at(i).Ip().asStringDec() +
                                                " / " + mainNetwork.Subnets().at(i).Mask().asStringDec());
             subnetAddress->setAlignment(Qt::AlignTop);
             subnetFrame->layout()->addWidget(subnetAddress);
         }

         QHBoxLayout *hostsLayout;

         for(int j = 0; j < mainNetwork.Subnets().at(i).HostNumber(); j++)
         {
            if((j + 8) % 8 == 0)
            {
                hostsLayout = new QHBoxLayout();
                QFrame *hostsFrame = new QFrame();
                frameLayout -> addWidget(hostsFrame);
                hostsFrame->setLayout(hostsLayout);
                hostsFrame->setMaximumWidth(450 * scale);
                hostsFrame->setMinimumHeight(100 * scale);
                hostsFrame->setStyleSheet("border-width : 0px;");
            }

            QVBoxLayout *hostLayout = new QVBoxLayout;
            QFrame *hostFrame = new QFrame();
            hostFrame->setLayout(hostLayout);
            hostFrame->setMaximumHeight(100 * scale);
            hostFrame->setStyleSheet("border-width : 0px;");

            QString hostButtonText = QString::fromStdString("H" + std::to_string(1 + j));

            HostButton *hostButton = new HostButton(mainNetwork.Subnets().at(i).HostsList().at(j));
            connect(hostButton, SIGNAL(clicked(Host)),
                    this, SLOT(on_hostButton_clicked(Host)));

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
                QLabel *hostName = new QLabel(mainNetwork.Subnets().at(i).HostsList().at(j).Name());
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
}
void GraphDialog::on_hostButton_clicked(Host host)
{
    hostDialog.setModal(true);
    hostDialog.InjectData(host);
    hostDialog.exec();
}

void GraphDialog::on_subnetButton_clicked(Subnetv4 subnet)
{
    subnetDialog.setModal(true);
    subnetDialog.InjectData(subnet);
    subnetDialog.exec();
}

void GraphDialog::on_networkButton_clicked(Networkv4 network)
{
    networkDialog.setModal(true);
    networkDialog.InjectData(network);
    networkDialog.exec();
}

void GraphDialog::on_coloredGraphcheckBox_clicked(bool checked)
{
    isColored = (checked) ? true : false;
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
    drawNetworkGraph();
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
