#include <QList>
#include <QSerialPortInfo>

#include "configwindow.hpp"
#include "configurationcontroller.hpp"
#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    config = Configuration::getInstance();

    settings = new QSettings(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(handleOK()));
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked(bool)), this, SLOT(handleApply()));
    connect(ui->buttonBox->button(QDialogButtonBox::Close), SIGNAL(clicked(bool)), this, SLOT(handleClose()));
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked(bool)), this, SLOT(handleReset()));

    load();
}

ConfigWindow::~ConfigWindow()
{
    delete settings;

    delete ui;
}

void ConfigWindow::handleOK()
{

}

void ConfigWindow::handleApply()
{

}

void ConfigWindow::handleClose()
{
    close();
}

void ConfigWindow::handleReset()
{

}

void ConfigWindow::load()
{
    updateSerialPortsLists();

    ui->habSerialPortComboBox->setCurrentText(config->getHabSerialPort());
}

void ConfigWindow::save()
{
    ConfigurationController::saveConfig(config);
}

void ConfigWindow::updateSerialPortsLists()
{
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo>::iterator portIterator;

    ui->habSerialPortComboBox->clear();
    ui->localGpsSerialPortComboBox->clear();

    for(portIterator = portList.begin(); portIterator != portList.end(); portIterator++) {
        QSerialPortInfo serialPortInfo = *portIterator;
        ui->habSerialPortComboBox->addItem(serialPortInfo.portName());
        ui->localGpsSerialPortComboBox->addItem(serialPortInfo.portName());
    }
}
