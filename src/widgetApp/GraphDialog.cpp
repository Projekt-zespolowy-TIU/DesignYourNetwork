#include "GraphDialog.h"
#include "ui_GraphDialog.h"
#include "NetworkButton.h"
#include "SubnetButton.h"
#include "HostButton.h"

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

void GraphDialog::injectData(std::shared_ptr<Networkv4> net4)
{
    mainNetwork = net4;
    drawNetworkGraph();
}

void GraphDialog::drawNetworkGraph()
{

    subnetsGraphFrame = new QFrame(this);
    subnetsGraphFrame->setStyleSheet("border-width : 0px;");

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
    if(isColored) graphNetworkFrame->
            setStyleSheet("border-color: rgb(220,220,220);\nborder-width :"
                          " 4px;\nborder-style:solid;");

    subnetGraphContent->layout()->addWidget(graphNetworkFrame);
    graphNetworkFrame->setLayout(new QVBoxLayout(this));

    QString routerButtonText = QString{'R'} + '1';
    NetworkButton *networkButton = new NetworkButton(mainNetwork, this);
    QIcon networkIcon;
    QPixmap pixmap(":/resources/img/router.png");
    networkIcon.addPixmap(pixmap);
    networkButton->setIconSize(QSize(50,50) * scale);
    networkButton->setIcon(networkIcon);
    networkButton->setFlat(true);
    networkButton->setMinimumSize(QSize(50,50) * scale);
    networkButton->setMaximumSize(QSize(50,50) * scale);
    graphNetworkFrame->layout()->addWidget(networkButton);

    connect(networkButton, SIGNAL(clicked(std::shared_ptr<Networkv4>)), this,
            SLOT(on_networkButton_clicked(std::shared_ptr<Networkv4>)));

    if(showsNetworkAddress)
    {
        QLabel *networkAddress = new QLabel(mainNetwork->Ip().asStringDec() +
                                            " / " + mainNetwork->Mask().asStringDec(), this);
        networkAddress->setAlignment(Qt::AlignTop);
        graphNetworkFrame->layout()->addWidget(networkAddress);
    }

    subnetsGraphFrame->setStyleSheet("border-width : 0px;");
    if(isVertical)
        subnetsGraphFrame->setLayout(new QVBoxLayout(this));
    else  subnetsGraphFrame->setLayout(new QHBoxLayout(this));

    subnetsGraphFrame->layout()->setSpacing(50 * scale);
    graphNetworkFrame->layout()->addWidget(subnetsGraphFrame);

    for(size_t i = 0; i < mainNetwork->Subnets().size(); i++)
    {
         QVBoxLayout *frameLayout = new QVBoxLayout(this);

         QFrame *subnetFrame = new QFrame(this);
         subnetFrame->setLayout(frameLayout);
         subnetsGraphFrame->layout()->addWidget(subnetFrame);

         if(isColored) subnetFrame->
                 setStyleSheet("border-color: rgb(38,94,84);\nborder-width :"
                               " 4px;\nborder-style:solid;");

         SubnetButton *subnetButton = new SubnetButton(mainNetwork->Subnets().at(i));
         QString subButtonText = 'S' + QString::number(1 + i);
         QIcon subnetIcon;
         QPixmap pixmap(":/resources/img/switch.png");
         subnetIcon.addPixmap(pixmap);
         subnetButton->setIconSize(QSize(40,40) * scale);
         subnetButton->setIcon(subnetIcon);
         subnetButton->setMinimumSize(QSize(40,40) * scale);
         subnetButton->setMaximumSize(QSize(40,40) * scale);
         subnetFrame->layout()->addWidget(subnetButton);

         connect(subnetButton, SIGNAL(clicked(std::shared_ptr<ISubnet>)), this,
                 SLOT(on_subnetButton_clicked(std::shared_ptr<ISubnet>)));

         if(showsSubnetAddresses)
         {
             QLabel *subnetAddress = new QLabel(mainNetwork->Subnets().at(i)->Ip().asStringDec() +
                                                " / " + mainNetwork->Subnets().at(i)->Mask().asStringDec(), this);
             subnetAddress->setAlignment(Qt::AlignTop);
             subnetFrame->layout()->addWidget(subnetAddress);
         }

         QHBoxLayout *hostsLayout;

         for(int j = 0; j < mainNetwork->Subnets().at(i)->HostNumber(); j++)
         {
            if((j + 8) % 8 == 0)
            {
                hostsLayout = new QHBoxLayout(this);
                QFrame *hostsFrame = new QFrame(this);
                frameLayout -> addWidget(hostsFrame);
                hostsFrame->setLayout(hostsLayout);
                hostsFrame->setMaximumWidth(450 * scale);
                hostsFrame->setMinimumHeight(100 * scale);
                hostsFrame->setStyleSheet("border-width : 0px;");
            }

            QVBoxLayout *hostLayout = new QVBoxLayout(this);
            QFrame *hostFrame = new QFrame(this);
            hostFrame->setLayout(hostLayout);
            hostFrame->setMaximumHeight(100 * scale);
            hostFrame->setStyleSheet("border-width : 0px;");

            QString hostButtonText = 'H' + QString::number(1 + j);

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
}
void GraphDialog::on_hostButton_clicked(std::shared_ptr<Host> host)
{
    hostDialog.setModal(true);
    hostDialog.InjectData(host);
    hostDialog.exec();
}

void GraphDialog::on_subnetButton_clicked(std::shared_ptr<ISubnet> subnet)
{
    subnetDialog.setModal(true);
    subnetDialog.InjectData(subnet);
    subnetDialog.exec();
}

void GraphDialog::on_networkButton_clicked(std::shared_ptr<Networkv4> network)
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
