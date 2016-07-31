#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <QObject>
#include <QString>
#include <QAbstractSocket>

#include "config/configuration.hpp"
#include "protocol/line.hpp"
#include "data/serversocket.hpp"

class DataHandler : public QObject
{
        Q_OBJECT
    public:
        explicit DataHandler(QObject *parent = 0);
        ~DataHandler();

    private:
        Configuration* config;
        QString lastLine;

        ServerSocket* serverSocket;

    public slots:
        void startHab();
        void stopHab();
        void startLocalGps();
        void stopLocalGps();
        void startServerSync();
        void stopServerSync();

    private slots:
        void handleNewLine(QString strLine);
        void handleServerSyncSocketEvent(QAbstractSocket::SocketState socketState);

    signals:
        void newLine(Line line);
        void newSocketState(QAbstractSocket::SocketState socketState);
};

#endif // DATAHANDLER_HPP
