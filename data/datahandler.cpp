#include "datahandler.hpp"
#include "protocol/lineparser.hpp"
#include "protocol/protocolexception.hpp"

DataHandler::DataHandler(QObject *parent) : QObject(parent)
{
    config = Configuration::getInstance();

    serverSocket = new ServerSocket(this);
    connect(serverSocket, SIGNAL(newLine(QString)), this, SLOT(handleNewLine(QString)));
}

DataHandler::~DataHandler()
{
    delete serverSocket;
}

void DataHandler::startHab()
{

}

void DataHandler::stopHab()
{

}

void DataHandler::startLocalGps()
{

}

void DataHandler::stopLocalGps()
{

}

void DataHandler::startServerSync()
{
    serverSocket->start(config->getServerSyncAddress(), config->getServerSyncPort());
}

void DataHandler::stopServerSync()
{
    serverSocket->stop();
}

void DataHandler::handleNewLine(QString strLine)
{
    if(strLine == lastLine)
        return;

    lastLine = strLine;
    serverSocket->writeLine(lastLine);

    try {
        emit newLine(LineParser::parseLine(strLine));
    } catch(ProtocolException &e) {
        return;
    }
}
