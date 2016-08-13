#include <QString>
#include <QByteArray>

#include "serversocket.hpp"

ServerSocket::ServerSocket(QObject *parent) : QObject(parent)
{
    socket = nullptr;
}

bool ServerSocket::isRunning() const
{
    return running;
}

void ServerSocket::start(QString address, quint16 port)
{
    if(socket != nullptr)
        return;

    lastLine = "";

    socket = new QTcpSocket(this);
    socket->connectToHost(address, port);
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));

    running = true;
}

void ServerSocket::stop()
{
    if(socket == nullptr)
        return;

    socket->close();

    delete socket;
    socket = nullptr;

    running = false;
}

void ServerSocket::socketStateChanged(QAbstractSocket::SocketState socketState)
{
    emit newSocketState(socketState);
}

void ServerSocket::writeLine(QString line)
{
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

    emit newLine(line);
}
