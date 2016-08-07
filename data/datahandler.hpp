#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <QObject>
#include <QString>
#include <QAbstractSocket>

#include "config/configuration.hpp"
#include "protocol/line.hpp"
#include "protocol/client.hpp"
#include "data/serversocket.hpp"

class DataHandler : public QObject
{
        Q_OBJECT

    public:
        explicit DataHandler(QObject *parent = 0);
        ~DataHandler();

        QList<Client*>* getClients() const;

    private:
        Configuration* config;
        QString lastLine;
        QList<Client*>* clients;

        ServerSocket* serverSocket;

        void initLocalClient();
        void parseNewLine(Line* line);
        Client*findClientById(QString id);

    public slots:
        void startHab();
        void stopHab();
        void startLocalGps();
        void stopLocalGps();
        void startServerSync();
        void stopServerSync();
        void updateLocalClient();

    private slots:
        void handleNewLine(QString strLine);
        void handleServerSyncSocketEvent(QAbstractSocket::SocketState socketState);

    signals:
        void newLine(Line* line);
        void newLine(QString line);
        void newSocketState(QAbstractSocket::SocketState socketState);
        void updateClientsList();
};

#endif // DATAHANDLER_HPP
