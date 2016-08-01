#include "datahandler.hpp"
#include "protocol/lineparser.hpp"
#include "protocol/protocolexception.hpp"

DataHandler::DataHandler(QObject *parent) : QObject(parent)
{
    config = Configuration::getInstance();

    serverSocket = new ServerSocket(this);
    connect(serverSocket, SIGNAL(newLine(QString)), this, SLOT(handleNewLine(QString)));
    connect(serverSocket, SIGNAL(newSocketState(QAbstractSocket::SocketState)), this, SLOT(handleServerSyncSocketEvent(QAbstractSocket::SocketState)));
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
        Line line = LineParser::parseLine(strLine);
        emit newLine(line);
    } catch(ProtocolException &e) {
        return;
    }
}

void DataHandler::handleServerSyncSocketEvent(QAbstractSocket::SocketState socketState)
{
    if(socketState == QAbstractSocket::ConnectedState) {

    }

    emit newSocketState(socketState);
}
