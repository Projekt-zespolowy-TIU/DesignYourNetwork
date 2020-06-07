#include "NetSettingsDialog.h"
#include "ui_NetSettingsDialog.h"

NetSettingsDialog::NetSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetSettingsDialog)
{
    ui->setupUi(this);

    addressWidget = ui->Address4Widget;
    binaryAddressWidget = ui->BinaryAddress4Widget;
    maskWidget = ui->Mask4Widget;
    binaryMaskWidget = ui->BinaryMask4Widget;

    address6Widget = ui->Address6Widget;
    mask6Widget = ui->Mask6Widget;

    subnetScrollContent = ui->subnetScroll;
    subnetScrollContent->setLayout(subnetsPanelLayout);
    subnetCountBox = ui->hostNumberSpinBox;
}

NetSettingsDialog::~NetSettingsDialog()
{
    delete ui;
}

void NetSettingsDialog::clearData()
{
    subnetCount = 0;
    ui->hostNumberSpinBox->setValue(0);
    deleteLayoutContent(subnetScrollContent);

    spinBoxList.clear();
    subnetNames.clear();

    graphDialog.close();
    raportDialog.close();
}


void NetSettingsDialog::on_calculateButton_clicked()
{

     mainNetwork = std::make_shared<Networkv4>(takeStringFromInputFields(addressWidget, '.'),
                  takeStringFromInputFields(maskWidget, '.'));

     //mainNetwork = std::make_shared<Networkv6>(takeStringFromInputFields(address6Widget,':'),
                  //takeStringFromInputFields(mask6Widget, ':'));

      //mainNetwork = std::make_shared<Networkv6>(QString("4ffe:2900:5545:3210:2000:f8ff:fe21:67cf"),
                                               //QString("ffff:ffff:0000:0000:0000:0000:0000:0000"));

     //mainNetwork->addSubnet(1, "test");


     displayInputInBinary(mainNetwork->Ip().asStringBin(),
                          binaryAddressWidget);

     displayInputInBinary(mainNetwork->Mask().asStringBin(),
                          binaryMaskWidget);

     setSubnetsHostCount();
     //calculatorv6.calcSubnets(*mainNetwork);


     isIpv6 = false;
     if(isIpv6)
     {
         calculatorv6.calcSubnets(*mainNetwork);
     }
     else calculatorv4.calcSubnets(*mainNetwork);



     graphDialog.injectData(mainNetwork);
     raportDialog.injectData(mainNetwork);
}

void NetSettingsDialog::setSubnetsHostCount()
{
    for (int i = 0; i < subnetCount; i++)
    {
        mainNetwork->addSubnet(spinBoxList.at(i)->value(),
                              subnetNames.at(i)->text());
    }
}

void NetSettingsDialog::deleteLayoutContent(QWidget *content)
{
    QLayoutItem *child;
    while ((child = content->layout()->takeAt(0)) != nullptr)
    {
        if(child->widget())
        {
            delete child->widget();
        }
        delete child;
    }
}

QString NetSettingsDialog::takeStringFromInputFields(QWidget *inputWidget, char separator)
{
    QList<QLineEdit*> inputFields = inputWidget->findChildren<QLineEdit*>();

    QString input= "";

    for (int i = 0; i < inputFields.count(); i++)
    {
        if(inputFields.at(i))
        {
            input += inputFields.at(i)->text();
            if(i < inputFields.count() - 1) input += separator;
        }
    }
    return input;
}

void NetSettingsDialog::displayInputInBinary(const QString &input, QWidget *displayWidget)
{
    QList<QLineEdit*> displayFields = displayWidget->findChildren<QLineEdit*>();

    std::string bitsetString = input.toStdString();

    for (int i = 0; i < displayFields.count(); i++)
    {
        if(displayFields[i])
        {
            QString octText = QString::fromStdString(bitsetString.substr(i * 9, 8));
            displayFields[i]->setText(octText);
        }
    }
}



void NetSettingsDialog::on_drawButton_clicked()
{
     graphDialog.setGeometry(this->geometry().x() + 390, this->geometry().y() + 60,
                              graphDialog.geometry().width(), graphDialog.geometry().height());
     graphDialog.show();
}

void NetSettingsDialog::on_raportButton_clicked()
{
    if(raportDialog.isHidden())
    {
        raportDialog.displayNetworkRaport();
        raportDialog.setGeometry(this->geometry().x() + 0, this->geometry().y() + 600,
                                  raportDialog.geometry().width(), raportDialog.geometry().height());
        raportDialog.show();
    }
    else
    {
        raportDialog.displayNetworkRaport();
    }
}

void NetSettingsDialog::on_toolBox_currentChanged(int index)
{
    isIpv6 = (index == 0) ? false : true;
}

void NetSettingsDialog::on_hostNumberSpinBox_valueChanged(int subnetCount)
{
    this->subnetCount = subnetCount;

    spinBoxList.clear();

    subnetNames.clear();

    deleteLayoutContent(subnetScrollContent);

    for (int i = 0; i < subnetCount; i++)
    {
        QHBoxLayout *textLayout = new QHBoxLayout;
        QString labelText = {"Subnet " + QString::number(1 + i)};
        QLabel *subnetLabel = new QLabel(labelText, this);
        subnetLabel->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        subnetLabel->setLayout(textLayout);
        subnetLabel->font().bold();
        subnetsPanelLayout->addWidget(subnetLabel);
        QVBoxLayout *subnetLayout = new QVBoxLayout;
        QFrame *subnetFrame = new QFrame(this);
        subnetFrame->setLayout(subnetLayout);

        QHBoxLayout *frameLayout = new QHBoxLayout;
        QLabel *nameLabel = new QLabel("Subnet name: ", this);
        nameLabel->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        nameLabel->setMinimumHeight(23);
        QFrame *nameFrame = new QFrame(this);
        nameFrame->setMinimumHeight(35);
        nameFrame->setLayout(frameLayout);
        QLineEdit *subnetNameLine = new QLineEdit(this);
        subnetNameLine->setMinimumHeight(23);
        subnetNameLine->setStyleSheet("background-color: rgb(60, 60, 60);\n color: rgb(220, 220, 220)");
        frameLayout->addWidget(nameLabel);
        frameLayout->addWidget(subnetNameLine);
        frameLayout = new QHBoxLayout;
        QFrame *hostCountFrame = new QFrame(this);
        hostCountFrame->setMinimumHeight(35);
        hostCountFrame->setLayout(frameLayout);

        QLabel *hostNumberLabel = new QLabel("Hosts number: ", this);
        hostNumberLabel->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        hostNumberLabel->setMinimumHeight(23);
        QSpinBox *spinBox = new QSpinBox(this);
        spinBox->setRange(0, 999);
        spinBox->setValue(1);
        spinBox->setStyleSheet("background-color: rgb(60, 60, 60);\n color: rgb(220, 220, 220)");
        spinBox->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        spinBox->setMinimumHeight(23);
        frameLayout->addWidget(hostNumberLabel);
        frameLayout->addWidget(spinBox);

        subnetFrame->layout()->addWidget(hostCountFrame);

        subnetFrame->layout()->addWidget(nameFrame);

        subnetsPanelLayout->addWidget(subnetFrame);

        subnetNames.append(subnetNameLine);

        spinBoxList.append(spinBox);
    }
}
