#include "configwindow.hpp"
#include "configurationcontroller.hpp"
#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), this, SLOT(handleOK()));
    connect(ui->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked(bool)), this, SLOT(handleApply()));
    connect(ui->buttonBox->button(QDialogButtonBox::Close), SIGNAL(clicked(bool)), this, SLOT(handleClose()));
    connect(ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked(bool)), this, SLOT(handleReset()));

    load();
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

void ConfigWindow::setConfig(Configuration* value)
{
    config = value;
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
    ConfigurationController.loadConfig(config);
}

void ConfigWindow::save()
{
    ConfigurationController.saveConfig(config);
}
