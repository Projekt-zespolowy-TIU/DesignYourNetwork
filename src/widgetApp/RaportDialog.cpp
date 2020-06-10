#include "RaportDialog.h"
#include "ui_RaportDialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QFileDialog>

#include "core/INetwork.h"

using namespace core;

RaportDialog::RaportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RaportDialog)
{
    ui->setupUi(this);
}

RaportDialog::~RaportDialog()
{
    delete ui;
}

void RaportDialog::displayNetworkRaport()
{
    ui->raportScrollContent->setLayout(raportLayout);
    raportText->setFrameStyle(0);
    raportText->clear();

    if(isDetailed)
    {
        reportGenerator->generate(*network, DetaiLevel::SuperDetailed);
    }
    else
    {
        reportGenerator->generate(*network);
    }

    raportText->append(reportGenerator->getReport());

    raportLayout->addWidget(raportText);
}

void RaportDialog::injectData(const std::shared_ptr<INetwork>& net4, std::unique_ptr<IReportGenerator> reportEngine)
{
    network = net4;
    reportGenerator = std::move(reportEngine);
}

void RaportDialog::on_saveButton_clicked()
{
    QString dir = QCoreApplication::applicationDirPath();
    QString filename = QFileDialog::getSaveFileName(this);

    reportGenerator->save(filename);
}

void RaportDialog::on_checkBox_toggled(bool checked)
{
    isDetailed = checked;
    displayNetworkRaport();
}
