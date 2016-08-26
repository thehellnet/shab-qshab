#ifndef SERVERSOCKET_HPP
#define SERVERSOCKET_HPP

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QMutex>
#include <QTimer>

class ServerSocket : public QObject
{
        Q_OBJECT

    public:
        explicit ServerSocket(QObject *parent = 0);

        bool isRunning() const;
        bool isSocketConnected();

    private:
        bool running;
        QString address;
        quint16 port;
        QTcpSocket* socket;
        QString lastLine;
        QMutex mutex;

        bool reconnecting;

        void connectSocket();
        void disconnectSocket();

    public slots:
        void start(QString address, quint16 port);
        void stop();
        void writeLine(QString line);
        void restartSocket();

    private slots:
        void socketStateChanged(QAbstractSocket::SocketState socketState);
        void readData();

    signals:
        void newLine(QString newLine);
        void newSocketState(QAbstractSocket::SocketState socketState);
};

#endif // SERVERSOCKET_HPP
