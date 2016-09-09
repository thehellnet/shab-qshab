#include <QtGlobal>
#include <QDateTime>

#include "datahandler.hpp"
#include "utility.hpp"
#include "protocol/lineparser.hpp"
#include "protocol/clientconnectline.hpp"

DataHandler::DataHandler(QObject *parent) : QObject(parent)
{
    config = Configuration::getInstance();

    hab = new Hab();

    localClient = new Client();
    reloadLocalClient();

    remoteClients = new QList<Client*>;
    localUpdateTimer = new QTimer();

    localUpdateTimer->setInterval(5000);
    localUpdateTimer->setSingleShot(false);
    localUpdateTimer->setTimerType(Qt::VeryCoarseTimer);
    connect(localUpdateTimer, SIGNAL(timeout()), this, SLOT(sendLocalClientUpdates()));

    serverSocket = new ServerSocket(this);
    connect(serverSocket, SIGNAL(newLine(QString)), this, SLOT(handleSocketNewLine(QString)));
    connect(serverSocket, SIGNAL(newSocketState(QAbstractSocket::SocketState)), this, SLOT(handleServerSyncSocketEvent(QAbstractSocket::SocketState)));

    gpsHandler = new GPSHandler(this);
    connect(gpsHandler, SIGNAL(newPosition(QGeoCoordinate)), this, SLOT(handleLocalGpsNewPosition(QGeoCoordinate)));

    habHandler = new HabHandler(this);
    connect(habHandler, SIGNAL(newLine(QString)), this, SLOT(handleSerialNewLine(QString)));

    heartBeatTimer = new QTimer(this);
    heartBeatTimer->setInterval(2500);
    heartBeatTimer->setSingleShot(false);
    connect(heartBeatTimer, SIGNAL(timeout()), this, SLOT(heartBeatCheck()));
}

DataHandler::~DataHandler()
{
    delete localClient;
    delete remoteClients;
    delete habHandler;
    delete gpsHandler;
    delete serverSocket;
}

QList<Client*>* DataHandler::getClients() const
{
    return remoteClients;
}

void DataHandler::startHab()
{
    habHandler->start();
}

void DataHandler::stopHab()
{
    habHandler->stop();
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
    heartBeatTimer->start();
    lastPingTime = QDateTime::currentDateTime();
}

void DataHandler::stopServerSync()
{
    serverSocket->stop();
    toogleLocalPositionUpdateTimer();
    heartBeatTimer->stop();

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

void DataHandler::checkRatio()
{
    while(ratioLines.size() > 20)
        ratioLines.removeAt(0);

    int radioLines = 0;
    int socketLines = 0;
    QList<int>::iterator i;
    for (i = ratioLines.begin(); i != ratioLines.end(); ++i) {
        switch(*i) {
            case 0:
                radioLines++;
                break;
            case 1:
                socketLines++;
                break;
        }
    }

    emit updateRatio(radioLines, socketLines);
}

void DataHandler::handleSerialNewLine(QString strLine)
{
    handleNewLine(strLine, 0);
}

void DataHandler::handleSocketNewLine(QString strLine)
{
    handleNewLine(strLine, 1);
}

void DataHandler::handleNewLine(QString strLine, int type)
{
    if(strLine == lastLine)
        return;

    Line* line = LineParser::parseLine(strLine);
    if(line == nullptr)
        return;

    lastLine = strLine;

    emit newLine(strLine);

    if(line->getCommand() == HabPosition
            || line->getCommand() == HabImage
            || line->getCommand() == HabTelemetry) {
        if(type == 0)
            serverSocket->writeLine(strLine);
        ratioLines.append(type);
        checkRatio();
    }

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
        hab->setFixStatus(castedLine->getFixStatus());
        hab->setLatitude(castedLine->getLatitude());
        hab->setLongitude(castedLine->getLongitude());
        hab->setAltitude(castedLine->getAltitude());
        emit habPositionUpdated(hab);
    } else if(line->getCommand() == Command::HabImage) {
        HabImageLine* castedLine = static_cast<HabImageLine*>(line);

        if(castedLine->getSliceNum() == 1)
            hab->clearImageData();

        hab->setSliceTot(castedLine->getSliceTot());
        hab->setSliceNum(castedLine->getSliceNum());
        hab->appendImageData(castedLine->getData());
        emit habImageSlice(hab);

        if(castedLine->getSliceNum() == castedLine->getSliceTot())
            emit newImage(hab->getImageData());
    } else if(line->getCommand() == Command::HabTelemetry) {
        HabTelemetryLine* castedLine = static_cast<HabTelemetryLine*>(line);
        hab->setIntTemp(castedLine->getIntTemp());
        hab->setExtTemp(castedLine->getExtTemp());
        hab->setExtAlt(castedLine->getExtAlt());
        emit habTelemetryUpdated(hab);
    } else if(line->getCommand() == Command::ServerPing) {
        //ServerPingLine* castedLine = static_cast<ServerPingLine*>(line);
        lastPingTime = QDateTime::currentDateTime();
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
    if(qIsNaN(newPosition.altitude()))
        return;

    localClient->setPosition(newPosition);
    emit updateLocalClient(localClient);
}

void DataHandler::sendLocalClientUpdates()
{
    if(qIsNaN(localClient->getPosition().latitude())
            || qIsNaN(localClient->getPosition().longitude())
            || qIsNaN(localClient->getPosition().altitude()))
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

void DataHandler::heartBeatCheck()
{
    QDateTime now = QDateTime::currentDateTime();

    qDebug() << "Last DateTime:" << lastPingTime;
    qDebug() << "Now:          " << now;

    if(lastPingTime.addSecs(5) <= now) {
        serverSocket->restartSocket();
        lastPingTime = QDateTime::currentDateTime();
        return;
    }

    if(serverSocket->isSocketConnected()) {
        ServerPingLine pingLine;
        pingLine.setTimestamp(QDateTime::currentDateTime().toMSecsSinceEpoch());
        QString socketLine = Utility::addChecksum(pingLine.serialize());
        serverSocket->writeLine(socketLine);
    }
}
