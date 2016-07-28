#include <QList>
#include <QSerialPort>
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

    populateSerialPortsParams();
    updateSerialPortsLists();

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
    int index;

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

    index = -1;
    for(int i=0; i<ui->habSerialSpeedComboBox->count(); i++)
        if(ui->habSerialSpeedComboBox->itemData(i).value<QSerialPort::BaudRate>() == config->getHabSerialSpeed()) {
            index = i;
            break;
        }
    if(index != -1) {
        ui->habSerialSpeedComboBox->setCurrentIndex(index);
    } else {
        ui->habSerialSpeedComboBox->setItemText(0, config->getHabSerialPort());
        ui->habSerialSpeedComboBox->setCurrentIndex(0);
    }
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
