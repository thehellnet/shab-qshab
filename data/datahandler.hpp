#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <QObject>
#include <QString>
#include <QAbstractSocket>
#include <QGeoCoordinate>
#include <QTimer>

#include "config/configuration.hpp"
#include "protocol/hab.hpp"
#include "protocol/line.hpp"
#include "protocol/client.hpp"
#include "data/serversocket.hpp"
#include "data/gpshandler.hpp"
#include "data/habhandler.hpp"

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

        Hab* hab;
        Client* localClient;
        QList<Client*>* remoteClients;

        ServerSocket* serverSocket;
        GPSHandler* gpsHandler;
        HabHandler* habHandler;

        QTimer* heartBeatTimer;
        QDateTime lastPingTime;

        QList<int> ratioLines;
        QList<bool> errorLines;

        void parseNewLine(Line* line);
        Client* findClientById(QString id);
        void toogleLocalPositionUpdateTimer();

        void checkRatio();
        void checkErrors(bool isLineGood);

    public slots:
        void startHab();
        void stopHab();
        void startLocalGps();
        void stopLocalGps();
        void startServerSync();
        void stopServerSync();
        void reloadLocalClient();

    private slots:
        void handleSerialNewLine(QString strLine);
        void handleSocketNewLine(QString strLine);
        void handleNewLine(QString strLine, int type);
        void handleServerSyncSocketEvent(QAbstractSocket::SocketState socketState);
        void handleLocalGpsNewPosition(QGeoCoordinate newPosition);
        void sendLocalClientUpdates();
        void heartBeatCheck();

    signals:
        void newLine(QString line);
        void newSocketState(QAbstractSocket::SocketState socketState);
        void updateClientsList();
        void removeAllRemoteClients();
        void updateLocalClient(Client* client);
        void addRemoteClient(Client* client);
        void updateRemoteClient(Client* client);
        void removeRemoteClient(Client* client);
        void habPositionUpdated(Hab* hab);
        void habImageSlice(Hab* hab);
        void habTelemetryUpdated(Hab* hab);
        void newImage(QByteArray data);
        void updateRatio(int radioLines, int socketLines);
        void updateErrors(int errors, int lines);
};

#endif // DATAHANDLER_HPP
