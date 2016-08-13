#include <cmath>

#include "datahandler.hpp"
#include "utility.hpp"
#include "protocol/lineparser.hpp"
#include "protocol/clientconnectline.hpp"

DataHandler::DataHandler(QObject *parent) : QObject(parent)
{
    config = Configuration::getInstance();

    localClient = new Client();
    reloadLocalClient();

    remoteClients = new QList<Client*>;
    localUpdateTimer = new QTimer();

    localUpdateTimer->setInterval(5000);
    localUpdateTimer->setSingleShot(false);
    localUpdateTimer->setTimerType(Qt::VeryCoarseTimer);
    connect(localUpdateTimer, SIGNAL(timeout()), this, SLOT(sendLocalClientUpdates()));

    serverSocket = new ServerSocket(this);
    connect(serverSocket, SIGNAL(newLine(QString)), this, SLOT(handleNewLine(QString)));
    connect(serverSocket, SIGNAL(newSocketState(QAbstractSocket::SocketState)), this, SLOT(handleServerSyncSocketEvent(QAbstractSocket::SocketState)));

    gpsHandler = new GPSHandler(this);
    connect(gpsHandler, SIGNAL(newPosition(QGeoCoordinate)), this, SLOT(handleLocalGpsNewPosition(QGeoCoordinate)));
}

DataHandler::~DataHandler()
{
    delete localClient;
    delete remoteClients;
    delete gpsHandler;
    delete serverSocket;
}

QList<Client*>* DataHandler::getClients() const
{
    return remoteClients;
}

void DataHandler::startHab()
{

}

void DataHandler::stopHab()
{

}

void DataHandler::startLocalGps()
{
    gpsHandler->start();
    toogleLocalPositionUpdateTimer();
}

void DataHandler::stopLocalGps()
{
    gpsHandler->stop();
    toogleLocalPositionUpdateTimer();
}

void DataHandler::startServerSync()
{
    serverSocket->start(config->getServerSyncAddress(), config->getServerSyncPort());
    toogleLocalPositionUpdateTimer();
}

void DataHandler::stopServerSync()
{
    serverSocket->stop();
    toogleLocalPositionUpdateTimer();

    remoteClients->clear();
    emit removeAllRemoteClients();
}

void DataHandler::toogleLocalPositionUpdateTimer()
{
    if(gpsHandler->isRunning() && serverSocket->isRunning())
        localUpdateTimer->start();
    else
        localUpdateTimer->stop();
}

void DataHandler::handleNewLine(QString strLine)
{
    if(strLine == lastLine)
        return;

    lastLine = strLine;
    serverSocket->writeLine(lastLine);

    Line* line = LineParser::parseLine(strLine);
    if(line == nullptr)
        return;

    emit newLine(strLine);

    parseNewLine(line);

    delete line;
}

Client* DataHandler::findClientById(QString id)
{
    for(int i = 0; i < remoteClients->count(); i++) {
        Client* client = remoteClients->at(i);
        if(client->getId() == id)
            return client;
    }

    return nullptr;
}

void DataHandler::parseNewLine(Line* line)
{
    if(line->getCommand() == Command::ClientConnect) {
        ClientConnectLine* castedLine = static_cast<ClientConnectLine*>(line);

        Client* newClient = new Client();
        newClient->setId(castedLine->getId());
        newClient->setName(castedLine->getName());
        remoteClients->append(newClient);

        emit addRemoteClient(newClient);
        emit updateClientsList();
    } else if(line->getCommand() == Command::ClientUpdate) {
        ClientUpdateLine* castedLine = static_cast<ClientUpdateLine*>(line);

        Client* client = findClientById(castedLine->getId());
        if(client == nullptr)
            return;

        QGeoCoordinate position;
        position.setLatitude(castedLine->getLatitude());
        position.setLongitude(castedLine->getLongitude());
        position.setAltitude(castedLine->getAltitude());
        client->setPosition(position);

        emit updateRemoteClient(client);
    } else if(line->getCommand() == Command::ClientDisconnect) {
        ClientDisconnectLine* castedLine = static_cast<ClientDisconnectLine*>(line);

        for(int i = 0; i < remoteClients->count(); i++) {
            Client* client = remoteClients->at(i);
            if(client->getId() == castedLine->getId()) {
                remoteClients->removeAt(i);
                emit removeRemoteClient(client);
                emit updateClientsList();
            }
        }
    } else if(line->getCommand() == Command::HabPosition) {
        HabPositionLine* castedLine = static_cast<HabPositionLine*>(line);

    } else if(line->getCommand() == Command::HabImage) {
        HabImageLine* castedLine = static_cast<HabImageLine*>(line);

    } else if(line->getCommand() == Command::HabTelemetry) {
        HabTelemetryLine* castedLine = static_cast<HabTelemetryLine*>(line);

    }
}

void DataHandler::handleServerSyncSocketEvent(QAbstractSocket::SocketState socketState)
{
    if(socketState == QAbstractSocket::ConnectedState) {
        ClientConnectLine ccLine;
        ccLine.setId(localClient->getId());
        ccLine.setName(localClient->getName());
        QString socketLine = Utility::addChecksum(ccLine.serialize());
        serverSocket->writeLine(socketLine);
        emit newLine(socketLine);
    }

    emit newSocketState(socketState);
}

void DataHandler::reloadLocalClient()
{
    localClient->setId(Utility::getMachineId());
    localClient->setName(config->getServerSyncName());
    emit updateLocalClient(localClient);
}

void DataHandler::handleLocalGpsNewPosition(QGeoCoordinate newPosition)
{
    if(std::isnan(newPosition.altitude()))
        return;

    localClient->setPosition(newPosition);
    emit updateLocalClient(localClient);
}

void DataHandler::sendLocalClientUpdates()
{
    if(std::isnan(localClient->getPosition().latitude())
            || std::isnan(localClient->getPosition().longitude())
            || std::isnan(localClient->getPosition().altitude()))
        return;

    ClientUpdateLine cuLine;
    cuLine.setId(localClient->getId());
    cuLine.setLatitude(localClient->getPosition().latitude());
    cuLine.setLongitude(localClient->getPosition().longitude());
    cuLine.setAltitude(localClient->getPosition().altitude());

    QString socketLine = Utility::addChecksum(cuLine.serialize());
    serverSocket->writeLine(socketLine);
    emit newLine(socketLine);
}
