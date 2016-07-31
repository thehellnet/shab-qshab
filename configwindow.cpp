#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFileDialog>

#include "configwindow.hpp"
#include "config/configurationcontroller.hpp"
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

    connect(ui->logRawCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateLogRawStatus()));
    connect(ui->logImagesCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateLogImagesStatus()));

    connect(ui->logRawPathButton, SIGNAL(clicked(bool)), this, SLOT(chooseLogRawPath()));
    connect(ui->logImagesPathButton, SIGNAL(clicked(bool)), this, SLOT(chooseLogIamgesPath()));

    populateSerialPortsParams();
    updateSerialPortsLists();
    updateLogRawStatus();
    updateLogImagesStatus();

    load();
}

ConfigWindow::~ConfigWindow()
{
    delete settings;

    delete ui;
}

void ConfigWindow::handleOK()
{
    save();
}

void ConfigWindow::handleApply()
{
    save();
}

void ConfigWindow::handleClose()
{
    close();
}

void ConfigWindow::handleReset()
{
    load();
}

void ConfigWindow::updateLogRawStatus()
{
    bool status = ui->logRawCheckBox->isChecked();

    ui->logRawPathText->setEnabled(status);
    ui->logRawPathButton->setEnabled(status);
}

void ConfigWindow::updateLogImagesStatus()
{
    bool status = ui->logImagesCheckBox->isChecked();

    ui->logImagesPathText->setEnabled(status);
    ui->logImagesPathButton->setEnabled(status);
}

void ConfigWindow::chooseLogRawPath()
{
    QFileDialog dialog;
    dialog.setDefaultSuffix("*.log");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.exec();

    QString fileName = dialog.selectedFiles().at(0);
    ui->logRawPathText->setText(fileName);
}

void ConfigWindow::chooseLogIamgesPath()
{
    QFileDialog dialog;
    dialog.setDefaultSuffix("");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.exec();

    QString fileName = dialog.selectedFiles().at(0);
    ui->logImagesPathText->setText(fileName);
}

void ConfigWindow::load()
{
    int index;

    ConfigurationController::loadConfig(config);

    ui->habSerialPortBox->setEnabled(!config->getHabRunning());
    ui->localGpsSerialPortBox->setEnabled(!config->getLocalGpsRunning());
    ui->serverSyncBox->setEnabled(!config->getServerSyncRunning());

    index = -1;
    for(int i=0; i<ui->habSerialPortComboBox->count(); i++)
        if(ui->habSerialPortComboBox->currentText() == config->getHabSerialPort()) {
            index = i;
            break;
        }
    if(index != -1) {
        ui->habSerialPortComboBox->setCurrentIndex(index);
    } else {
        ui->habSerialPortComboBox->setItemText(0, config->getHabSerialPort());
        ui->habSerialPortComboBox->setCurrentIndex(0);
    }

    for(int i=0; i<ui->habSerialSpeedComboBox->count(); i++)
        if(ui->habSerialSpeedComboBox->itemData(i).value<QSerialPort::BaudRate>() == config->getHabSerialSpeed()) {
            ui->habSerialSpeedComboBox->setCurrentIndex(i);
            break;
        }

    ui->localGpsSerialPortBox->setChecked(config->getLocalGpsSerialEnable());

    index = -1;
    for(int i=0; i<ui->localGpsSerialPortComboBox->count(); i++)
        if(ui->localGpsSerialPortComboBox->itemText(i) == config->getLocalGpsSerialPort()) {
            index = i;
            break;
        }
    if(index != -1) {
        ui->localGpsSerialPortComboBox->setCurrentIndex(index);
    } else {
        ui->localGpsSerialPortComboBox->setItemText(0, config->getLocalGpsSerialPort());
        ui->localGpsSerialPortComboBox->setCurrentIndex(0);
    }

    for(int i=0; i<ui->localGpsSerialSpeedComboBox->count(); i++)
        if(ui->localGpsSerialSpeedComboBox->itemData(i).value<QSerialPort::BaudRate>() == config->getLocalGpsSerialSpeed()) {
            ui->localGpsSerialSpeedComboBox->setCurrentIndex(i);
            break;
        }

    for(int i=0; i<ui->localGpsSerialFlowControlComboBox->count(); i++)
        if(ui->localGpsSerialFlowControlComboBox->itemData(i).value<QSerialPort::FlowControl>() == config->getLocalGpsSerialFlowControl()) {
            ui->localGpsSerialFlowControlComboBox->setCurrentIndex(i);
            break;
        }

    for(int i=0; i<ui->localGpsSerialParityComboBox->count(); i++)
        if(ui->localGpsSerialParityComboBox->itemData(i).value<QSerialPort::Parity>() == config->getLocalGpsSerialParity()) {
            ui->localGpsSerialParityComboBox->setCurrentIndex(i);
            break;
        }

    for(int i=0; i<ui->localGpsSerialDataBitsComboBox->count(); i++)
        if(ui->localGpsSerialDataBitsComboBox->itemData(i).value<QSerialPort::DataBits>() == config->getLocalGpsSerialDataBits()) {
            ui->localGpsSerialDataBitsComboBox->setCurrentIndex(i);
            break;
        }

    for(int i=0; i<ui->localGpsSerialStopBitsComboBox->count(); i++)
        if(ui->localGpsSerialStopBitsComboBox->itemData(i).value<QSerialPort::StopBits>() == config->getLocalGpsSerialStopBits()) {
            ui->localGpsSerialStopBitsComboBox->setCurrentIndex(i);
            break;
        }

    ui->serverSyncBox->setChecked(config->getServerSyncEnable());
    ui->serverSyncAddressText->setText(config->getServerSyncAddress());
    ui->serverSyncPortText->setText(QString::number(config->getServerSyncPort()));

    ui->logRawCheckBox->setChecked(config->getLogRawEnable());
    ui->logRawPathText->setText(config->getLogRawPath());
    ui->logImagesCheckBox->setChecked(config->getLogImagesEnable());
    ui->logImagesPathText->setText(config->getLogImagesPath());
}

void ConfigWindow::save()
{
    config->setHabSerialPort(ui->habSerialPortComboBox->currentText());
    config->setHabSerialSpeed(ui->habSerialSpeedComboBox->currentData().value<QSerialPort::BaudRate>());

    config->setLocalGpsSerialEnable(ui->localGpsSerialPortBox->isChecked());
    config->setLocalGpsSerialPort(ui->localGpsSerialPortComboBox->currentText());
    config->setLocalGpsSerialSpeed(ui->localGpsSerialPortComboBox->currentData().value<QSerialPort::BaudRate>());
    config->setLocalGpsSerialFlowControl(ui->localGpsSerialFlowControlComboBox->currentData().value<QSerialPort::FlowControl>());
    config->setLocalGpsSerialParity(ui->localGpsSerialParityComboBox->currentData().value<QSerialPort::Parity>());
    config->setLocalGpsSerialDataBits(ui->localGpsSerialDataBitsComboBox->currentData().value<QSerialPort::DataBits>());
    config->setLocalGpsSerialStopBits(ui->localGpsSerialStopBitsComboBox->currentData().value<QSerialPort::StopBits>());

    config->setServerSyncEnable(ui->serverSyncBox->isChecked());
    config->setServerSyncAddress(ui->serverSyncAddressText->text());
    config->setServerSyncPort(ui->serverSyncPortText->text().toUInt());

    config->setLogRawEnable(ui->logRawCheckBox->isChecked());
    config->setLogRawPath(ui->logRawPathText->text());
    config->setLogImagesEnable(ui->logImagesCheckBox->isChecked());
    config->setLogImagesPath(ui->logImagesPathText->text());

    ConfigurationController::saveConfig(config);

    emit configurationChanged();
}

void ConfigWindow::updateSerialPortsLists()
{
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    QList<QSerialPortInfo>::iterator portIterator;

    ui->habSerialPortComboBox->clear();
    ui->localGpsSerialPortComboBox->clear();

    ui->habSerialPortComboBox->addItem("");
    ui->localGpsSerialPortComboBox->addItem("");

    for(portIterator = portList.begin(); portIterator != portList.end(); portIterator++) {
        QSerialPortInfo serialPortInfo = *portIterator;
        ui->habSerialPortComboBox->addItem(serialPortInfo.portName());
        ui->localGpsSerialPortComboBox->addItem(serialPortInfo.portName());
    }
}

void ConfigWindow::populateSerialPortsParams()
{
    ui->habSerialSpeedComboBox->clear();
    ui->habSerialSpeedComboBox->addItem("1200 baud", QSerialPort::Baud1200);
    ui->habSerialSpeedComboBox->addItem("2400 baud", QSerialPort::Baud2400);
    ui->habSerialSpeedComboBox->addItem("4800 baud", QSerialPort::Baud4800);
    ui->habSerialSpeedComboBox->addItem("9600 baud", QSerialPort::Baud9600);
    ui->habSerialSpeedComboBox->addItem("19200 baud", QSerialPort::Baud19200);
    ui->habSerialSpeedComboBox->addItem("38400 baud", QSerialPort::Baud38400);
    ui->habSerialSpeedComboBox->addItem("57600 baud", QSerialPort::Baud57600);
    ui->habSerialSpeedComboBox->addItem("115200 baud", QSerialPort::Baud115200);

    ui->localGpsSerialSpeedComboBox->clear();
    ui->localGpsSerialSpeedComboBox->addItem("1200 baud", QSerialPort::Baud1200);
    ui->localGpsSerialSpeedComboBox->addItem("2400 baud", QSerialPort::Baud2400);
    ui->localGpsSerialSpeedComboBox->addItem("4800 baud", QSerialPort::Baud4800);
    ui->localGpsSerialSpeedComboBox->addItem("9600 baud", QSerialPort::Baud9600);
    ui->localGpsSerialSpeedComboBox->addItem("19200 baud", QSerialPort::Baud19200);
    ui->localGpsSerialSpeedComboBox->addItem("38400 baud", QSerialPort::Baud38400);
    ui->localGpsSerialSpeedComboBox->addItem("57600 baud", QSerialPort::Baud57600);
    ui->localGpsSerialSpeedComboBox->addItem("115200 baud", QSerialPort::Baud115200);

    ui->localGpsSerialFlowControlComboBox->clear();
    ui->localGpsSerialFlowControlComboBox->addItem("Disabled", QSerialPort::NoFlowControl);
    ui->localGpsSerialFlowControlComboBox->addItem("Hardware (RTS/CTS)", QSerialPort::HardwareControl);
    ui->localGpsSerialFlowControlComboBox->addItem("Software (XON/XOFF)", QSerialPort::SoftwareControl);

    ui->localGpsSerialParityComboBox->clear();
    ui->localGpsSerialParityComboBox->addItem("Disabled", QSerialPort::NoParity);
    ui->localGpsSerialParityComboBox->addItem("Even", QSerialPort::EvenParity);
    ui->localGpsSerialParityComboBox->addItem("Odd", QSerialPort::OddParity);
    ui->localGpsSerialParityComboBox->addItem("Space", QSerialPort::SpaceParity);
    ui->localGpsSerialParityComboBox->addItem("Mark", QSerialPort::MarkParity);

    ui->localGpsSerialDataBitsComboBox->clear();
    ui->localGpsSerialDataBitsComboBox->addItem("5 bit", QSerialPort::Data5);
    ui->localGpsSerialDataBitsComboBox->addItem("6 bit", QSerialPort::Data6);
    ui->localGpsSerialDataBitsComboBox->addItem("7 bit", QSerialPort::Data7);
    ui->localGpsSerialDataBitsComboBox->addItem("8 bit", QSerialPort::Data8);

    ui->localGpsSerialStopBitsComboBox->clear();
    ui->localGpsSerialStopBitsComboBox->addItem("1 bit", QSerialPort::OneStop);
    ui->localGpsSerialStopBitsComboBox->addItem("1.5 bit", QSerialPort::OneAndHalfStop);
    ui->localGpsSerialStopBitsComboBox->addItem("2 bit", QSerialPort::TwoStop);
}
