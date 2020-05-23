#include "graphDialog.h"
#include "ui_graphdialog.h"
#include "networkButton.h"
#include "subnetButton.h"

#include <QLayout>
#include <QPushButton>
#include <QLabel>

GraphDialog::GraphDialog(Networkv4 mainNetwork,
    std::vector<std::shared_ptr<Subnet>> subnets, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphDialog)
{
    this->mainNetwork = mainNetwork;
    this->subnets = subnets;

    ui->setupUi(this);

    subnetGraphContent = ui-> graphScroll;

    drawNetworkGraph(isVertical, isColored);
}

GraphDialog::~GraphDialog()
{
    delete ui;
}

void GraphDialog::drawNetworkGraph(bool isVertical, bool isColored)
{
     //subnetGraphContent->setStyleSheet("background-color: rgb(218, 86, 88)");

    subnetGraphContent->setLayout(graphPanelLayout);

    subnetsGraphFrame = new QFrame();


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
    if(isColored)graphNetworkFrame->setStyleSheet("background-color: rgb(218, 86, 88)");
    subnetGraphContent->layout()->addWidget(graphNetworkFrame);
    graphNetworkFrame->setLayout(new QVBoxLayout());

    QString routerButtonText = QString::fromStdString("R" + std::to_string(1));
    NetworkButton *networkButton = new NetworkButton(mainNetwork);
    if(isColored)networkButton->setStyleSheet("background-color: rgb(218, 86, 88)");


    QIcon networkIcon;
    QPixmap pixmap(":/resources/img/router.png");
    networkIcon.addPixmap(pixmap);
    networkButton->setIconSize(QSize(50,50) * scale);
    networkButton->setIcon(networkIcon);
    networkButton->setFlat(true);

    networkButton->setMinimumSize(QSize(50,50) * scale);
    networkButton->setMaximumSize(QSize(50,50) * scale);
    graphNetworkFrame->layout()->addWidget(networkButton);

    connect(networkButton, SIGNAL(clicked(Networkv4)), this, SLOT(on_networkButton_clicked(Networkv4)));

    if(isColored)subnetsGraphFrame->setStyleSheet("background-color: rgb(227, 229, 115, 100)");

    if(isVertical)
        subnetsGraphFrame->setLayout(new QVBoxLayout());
    else  subnetsGraphFrame->setLayout(new QHBoxLayout());

    subnetsGraphFrame->layout()->setSpacing(50 * scale);
    graphNetworkFrame->layout()->addWidget(subnetsGraphFrame);

    for(int i = 0; i < static_cast<int>(subnets.size()); i++)
    {
         QVBoxLayout *frameLayout = new QVBoxLayout();

         QFrame *subnetFrame = new QFrame();
         subnetFrame->setLayout(frameLayout);

         subnetsGraphFrame->layout()->addWidget(subnetFrame);

         QString subButtonText = QString::fromStdString("S" + std::to_string(1 + i));
         //MyButton *subnetButton = new MyButton();
         SubnetButton *subnetButton = new SubnetButton(subnets.at(i));
         //subnetButton->setText(subButtonText);

         //subnetButton->setStyleSheet("background-color: rgb(227, 229, 115)");
         //subnetButton->setStyleSheet("background-color: rgb(70, 70, 70)");
         subnetButton->setFlat(true);
         QIcon subnetIcon;
         QPixmap pixmap(":/resources/img/switch.png");
         subnetIcon.addPixmap(pixmap);
         subnetButton->setIconSize(QSize(40,40) * scale);
         subnetButton->setIcon(subnetIcon);

         subnetButton->setMinimumSize(QSize(40,40) * scale);
         subnetButton->setMaximumSize(QSize(40,40) * scale);
         subnetFrame->layout()->addWidget(subnetButton);

         connect(subnetButton, SIGNAL(clicked(std::shared_ptr<Subnet>)), this, SLOT(on_subnetButton_clicked(std::shared_ptr<Subnet>)));

         QHBoxLayout *hostsLayout;

         for(int j = 0; j < subnets[i]->HostNumber; j++)
         {
            if((j + 8) % 8 == 0)
            {
                hostsLayout = new QHBoxLayout();
                QFrame *hostsFrame = new QFrame();
                frameLayout -> addWidget(hostsFrame);

                hostsFrame->setLayout(hostsLayout);
                if(isColored)hostsFrame->setStyleSheet("background-color: rgb(15, 159, 116, 100)");
                hostsFrame->setMaximumWidth(300 * scale);
            }

            QVBoxLayout *hostLayout = new QVBoxLayout;

            QFrame *hostFrame = new QFrame();
            hostLayout->addWidget(hostFrame);
            //QLabel *hostName = new QLabel();


            QString hostButtonText = QString::fromStdString("H" + std::to_string(1 + j));
            QPushButton *hostButton = new QPushButton();
            if(isColored)hostButton->setStyleSheet("background-color: rgb(15, 159, 116)");

            hostButton->setFlat(true);
            QIcon hostIcon;
            QPixmap hostPixmap(":/resources/img/host.png");
            hostIcon.addPixmap(hostPixmap);
            hostButton->setIconSize(QSize(30,30) * scale);
            hostButton->setIcon(hostIcon);

            hostButton->setMinimumSize(QSize(30,30) * scale);
            hostButton->setMaximumSize(QSize(30,30) * scale);
            hostsLayout->addWidget(hostButton);
         }
    }

}
void GraphDialog::on_subnetButton_clicked(std::shared_ptr<Subnet> subnet)
{
    subnetDialog.setModal(true);
    subnetDialog.InjectData(subnet);
    subnetDialog.exec();
}

void GraphDialog::on_networkButton_clicked(Networkv4 network)
{
    networkDialog.setModal(true);
    networkDialog.InjectData(network, subnets.size());
    networkDialog.exec();
}

void GraphDialog::on_coloredGraphcheckBox_clicked(bool checked)
{
    isColored = (checked) ? true : false;
    drawNetworkGraph(isVertical, isColored);
}

void GraphDialog::on_verticalViewButton_clicked(bool checked)
{
    isVertical = checked;
    drawNetworkGraph(isVertical, isColored);
}

void GraphDialog::on_horizontalViewButton_clicked(bool checked)
{
    isVertical = !checked;
    drawNetworkGraph(isVertical, isColored);
}

void GraphDialog::on_scaleSlider_sliderMoved(int position)
{
    scale = static_cast<float>(position) / 10.0f;
    drawNetworkGraph(isVertical, isColored);
}
