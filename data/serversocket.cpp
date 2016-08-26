#include <QString>
#include <QByteArray>
#include <QTimer>

#include "serversocket.hpp"

ServerSocket::ServerSocket(QObject *parent) : QObject(parent)
{
    socket = nullptr;
    running = false;
    reconnecting = false;
}

bool ServerSocket::isRunning() const
{
    return running;
}

bool ServerSocket::isSocketConnected()
{
    return socket != nullptr && socket->isOpen();
}

void ServerSocket::start(QString address, quint16 port)
{
    if(socket != nullptr)
        return;

    lastLine = "";

    this->address = address;
    this->port = port;
    connectSocket();

    running = true;
}

void ServerSocket::stop()
{
    if(socket == nullptr)
        return;

    running = false;

    disconnectSocket();
}

void ServerSocket::connectSocket()
{
    mutex.lock();

    qDebug() << "Connecting socket";

    if(socket == nullptr) {
        socket = new QTcpSocket(this);
        socket->connectToHost(address, port);
        connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
        connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
    }

    mutex.unlock();
}

void ServerSocket::disconnectSocket()
{
    mutex.lock();

    qDebug() << "Disconnecting socket";

    if(socket != nullptr) {
        socket->close();

        delete socket;
        socket = nullptr;
    }

    mutex.unlock();
}

void ServerSocket::restartSocket()
{
    qDebug() << "Reconnecting socket";

    if(!running)
        return;

    reconnecting = true;
    disconnectSocket();
    connectSocket();
    reconnecting = false;
}

void ServerSocket::socketStateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug() << "Socket state changed:" << socketState;

    emit newSocketState(socketState);

    if(!reconnecting
            && socketState == QAbstractSocket::UnconnectedState
            && running)
        QTimer::singleShot(2000, this, SLOT(restartSocket()));
}

void ServerSocket::writeLine(QString line)
{
    qDebug() << "Write line" << line;

    if(socket == nullptr || !socket->isOpen())
        return;

    line = line.simplified();
    if(line == lastLine)
        return;

    lastLine = line;

    line += "\n";
    socket->write(line.toLatin1());
}

void ServerSocket::readData()
{
    if(!socket->canReadLine())
        return;

    QByteArray rawData = socket->readLine();
    QString line = QString(rawData).simplified();

    if(line == lastLine)
        return;

    lastLine = line;
    qDebug() << "Read line:" << lastLine;

    emit newLine(line);
}
