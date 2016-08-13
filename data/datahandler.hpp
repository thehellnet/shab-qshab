#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <QObject>
#include <QString>
#include <QAbstractSocket>
#include <QGeoCoordinate>
#include <QTimer>

#include "config/configuration.hpp"
#include "protocol/line.hpp"
#include "protocol/client.hpp"
#include "data/serversocket.hpp"
#include "data/gpshandler.hpp"

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
        QTimer* localUpdateTimer;
        Client* localClient;
        QList<Client*>* remoteClients;

        ServerSocket* serverSocket;
        GPSHandler* gpsHandler;

        void parseNewLine(Line* line);
        Client* findClientById(QString id);
        void toogleLocalPositionUpdateTimer();

    public slots:
        void startHab();
        void stopHab();
        void startLocalGps();
        void stopLocalGps();
        void startServerSync();
        void stopServerSync();
        void reloadLocalClient();

    private slots:
        void handleNewLine(QString strLine);
        void handleServerSyncSocketEvent(QAbstractSocket::SocketState socketState);
        void handleLocalGpsNewPosition(QGeoCoordinate newPosition);
        void sendLocalClientUpdates();

    signals:
        void newLine(QString line);
        void newSocketState(QAbstractSocket::SocketState socketState);
        void updateClientsList();
        void removeAllRemoteClients();
        void updateLocalClient(Client* client);
        void addRemoteClient(Client* client);
        void updateRemoteClient(Client* client);
        void removeRemoteClient(Client* client);
};

#endif // DATAHANDLER_HPP
