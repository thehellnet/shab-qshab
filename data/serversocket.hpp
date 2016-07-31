#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <QObject>
#include <QTcpSocket>
#include <QString>

class ServerSocket : public QObject
{
        Q_OBJECT

    public:
        explicit ServerSocket(QObject *parent = 0);

    private:
        QTcpSocket* socket;
        QString lastLine;

    public slots:
        void start(QString address, quint16 port);
        void stop();
        void writeLine(QString line);

    private slots:
        void socketStateChanged(QAbstractSocket::SocketState socketState);
        void readData();

    signals:
        void newLine(QString newLine);
};

#endif // SERVERSOCKET_HPP