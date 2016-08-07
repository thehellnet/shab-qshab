#include "datahandler.hpp"
#include "utility.hpp"
#include "protocol/lineparser.hpp"
#include "protocol/clientconnectline.hpp"

DataHandler::DataHandler(QObject *parent) : QObject(parent)
{
    config = Configuration::getInstance();

    clients = new QList<Client*>;

    serverSocket = new ServerSocket(this);
    connect(serverSocket, SIGNAL(newLine(QString)), this, SLOT(handleNewLine(QString)));
    connect(serverSocket, SIGNAL(newSocketState(QAbstractSocket::SocketState)), this, SLOT(handleServerSyncSocketEvent(QAbstractSocket::SocketState)));
}

DataHandler::~DataHandler()
{
    delete clients;
    delete serverSocket;
}

QList<Client*>* DataHandler::getClients() const
{
    return clients;
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
    initLocalClient();
    emit updateClientsList();

    serverSocket->start(config->getServerSyncAddress(), config->getServerSyncPort());
}

void DataHandler::stopServerSync()
{
    serverSocket->stop();
    clients->clear();
    emit updateClientsList();
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

    parseNewLine(line);
    emit newLine(line);
    delete line;
}

Client* DataHandler::findClientById(QString id)
{
    for(int i=1; i<clients->count(); i++) {
        Client* client = clients->at(i);
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
        clients->append(newClient);

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

        emit updateClientsList();
    } else if(line->getCommand() == Command::ClientDisconnect) {
        ClientDisconnectLine* castedLine = static_cast<ClientDisconnectLine*>(line);

        for(int i = 1; i < clients->count(); i++) {
            Client* client = clients->at(i);
            if(client->getId() == castedLine->getId())
                clients->removeAt(i);
        }

        emit updateClientsList();
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
        Client* localClient = clients->at(0);

        ClientConnectLine* ccLine = new ClientConnectLine();
        ccLine->setId(localClient->getId());
        ccLine->setName(localClient->getName());
        QString socketLine = Utility::addChecksum(ccLine->serialize());
        serverSocket->writeLine(socketLine);

        emit newLine(socketLine);
        emit newLine(ccLine);

        delete ccLine;
    }

    emit newSocketState(socketState);
}

void DataHandler::initLocalClient()
{
    Client* localClient = new Client();
    localClient->setId(Utility::getMachineId());
    localClient->setName(config->getServerSyncName());
    clients->append(localClient);
}

void DataHandler::updateLocalClient()
{
    Client* localClient = clients->at(0);
    localClient->setName(config->getServerSyncName());
}
