#include "NetSettingsDialog.h"
#include "ui_NetSettingsDialog.h"

#include <QFileDialog>
#include <QMessageBox>

#include "core/ReportGeneratorV4.h"
#include "core/ReportGeneratorV6.h"
#include "core/FileIO.h"
#include "core/coreUtils.h"

NetSettingsDialog::NetSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetSettingsDialog)
{
    ui->setupUi(this);

    ui->toolBox->setCurrentIndex(0);

    addressWidget = ui->Address4Widget;
    binaryAddressWidget = ui->BinaryAddress4Widget;
    maskWidget = ui->Mask4Widget;
    binaryMaskWidget = ui->BinaryMask4Widget;

    subnetScrollContent = ui->subnetScroll;
    subnetScrollContent->setLayout(new QVBoxLayout());
    subnetCountBox = ui->hostNumberSpinBox;

    subnetScrollContentv6 = ui->subnetScrollv6;
    subnetScrollContentv6->setLayout(new QVBoxLayout());
    subnetCountBoxv6 = ui->hostNumberSpinBoxv6;
}

NetSettingsDialog::~NetSettingsDialog()
{
    delete ui;
}

void NetSettingsDialog::clearData()
{
    mainNetwork = std::shared_ptr<INetwork>();

    ui->hostNumberSpinBox->setValue(0);
    ui->hostNumberSpinBoxv6->setValue(0);

    deleteLayoutContent(subnetScrollContent);
    deleteLayoutContent(subnetScrollContentv6);

    spinBoxList.clear();
    subnetNames.clear();

    spinBoxListv6.clear();
    subnetNamesv6.clear();

    graphDialog.close();
    raportDialog.close();
}

void NetSettingsDialog::readData()
{
    FileIO fileIO;
    QString path = QFileDialog::getOpenFileName(this);

    if(path != nullptr)
    {
        clearData();
        fileIO.loadIPv4(mainNetwork, path);
        calculateNetwork();
        graphDialog.injectData(mainNetwork);
        graphDialog.show();
    }
}

void NetSettingsDialog::saveData()
{
    FileIO fileIO;
    QString path = QFileDialog::getSaveFileName(this);

    if(path != nullptr)
    {
        fileIO.saveIPv4(*mainNetwork, path);
    }
}

void NetSettingsDialog::on_calculateButton_clicked()
{
    try{
        takeDataFromInput();
    } catch (const IPFormatExcept& e) {
        QMessageBox error{QMessageBox::Information, "Wrong inputs", e.what(), QMessageBox::Ok, this};
        error.exec();
        return;
    }

    try {
        calculateNetwork();
    } catch (const SubnetInvalidExcept& e){
        QMessageBox error{QMessageBox::Information, "Wrong inputs", e.what(), QMessageBox::Ok, this};
        error.exec();
        return;
    } catch (const SubnetExcept& e) {
        QMessageBox error{QMessageBox::Information, "Wrong inputs", e.what(), QMessageBox::Ok, this};
        error.exec();
        return;
    }
}

void NetSettingsDialog::setSubnets(QList<QSpinBox*> countWidgets, QList<QLineEdit*> nameLines)
{
    for (int i = 0; i < countWidgets.count(); i++)
    {
        mainNetwork->addSubnet(countWidgets.at(i)->value(),
                              nameLines.at(i)->text());
    }
}

void NetSettingsDialog::calculateNetwork()
{
    auto networkv6 = dynamic_cast<Networkv6*>(mainNetwork.get());

    if(networkv6)
    {
            setSubnets(spinBoxListv6, subnetNamesv6);
            calculatorv6.calcSubnets(*mainNetwork);
    }
    else
    {
        displayInputInBinary(mainNetwork->Ip().asStringBin(),
                              binaryAddressWidget);

        displayInputInBinary(mainNetwork->Mask().asStringBin(),
                              binaryMaskWidget);

            setSubnets(spinBoxList, subnetNames);
           calculatorv4.calcSubnets(*mainNetwork);
    }

    graphDialog.injectData(mainNetwork);

    if(auto x = std::dynamic_pointer_cast<Networkv4>(mainNetwork); x)
    {
        raportDialog.injectData(mainNetwork, std::make_unique<ReportGeneratorV4>());
    }
    else if(auto x = std::dynamic_pointer_cast<Networkv6>(mainNetwork); x)
    {
        raportDialog.injectData(mainNetwork, std::make_unique<ReportGeneratorV6>());
    }
}

void NetSettingsDialog::takeDataFromInput()
{
    if(isIpv6)
    {
        mainNetwork = std::make_shared<Networkv6>(ui->addressv6->text(), ui->maskv6->text());
    }
    else
    {
        mainNetwork = std::make_shared<Networkv4>(takeStringFromInputFields(addressWidget, '.'),
                     takeStringFromInputFields(maskWidget, '.'));
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
     graphDialog.setGeometry(this->geometry().x() + 425, this->geometry().y(),
                                graphDialog.geometry().width(), graphDialog.geometry().height());
     graphDialog.show();
}

void NetSettingsDialog::on_raportButton_clicked()
{
    if(raportDialog.isHidden())
    {
        raportDialog.setGeometry(this->geometry().x() + 700, this->geometry().y() + 150,
                                 raportDialog.geometry().width(), raportDialog.geometry().height());

        raportDialog.displayNetworkRaport();
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
    updateSubnetsPanel(&spinBoxList, &subnetNames,
                       subnetScrollContent, subnetCount);
}

void NetSettingsDialog::on_hostNumberSpinBoxv6_valueChanged(int subnetCount)
{
    updateSubnetsPanel(&spinBoxListv6, &subnetNamesv6,
                       subnetScrollContentv6, subnetCount);
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

void NetSettingsDialog::updateSubnetsPanel(QList<QSpinBox*> *countWidgets, QList<QLineEdit*> *nameLines,
                                           QWidget *subnetScrollContent, int subnetCount)
{
    countWidgets->clear();

    nameLines->clear();

    deleteLayoutContent(subnetScrollContent);

    for (int i = 0; i < subnetCount; i++)
    {
        QHBoxLayout *textLayout = new QHBoxLayout;
        QString labelText = {"Subnet " + QString::number(1 + i)};
        QLabel *subnetLabel = new QLabel(labelText, this);
        subnetLabel->setFont(QFont("MS Shell dlg", 13, QFont::Normal));
        subnetLabel->setLayout(textLayout);
        subnetLabel->font().bold();
        subnetScrollContent->layout()->addWidget(subnetLabel);
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
        subnetNameLine->setText(labelText);
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

        subnetScrollContent->layout()->addWidget(subnetFrame);

        nameLines->append(subnetNameLine);

        countWidgets->append(spinBox);
    }
}
