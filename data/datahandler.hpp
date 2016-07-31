#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <QObject>

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

    signals:
        void newLine(Line line);
};

#endif // DATAHANDLER_HPP
