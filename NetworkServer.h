#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QList>

class NetworkServer : public QObject
{
    Q_OBJECT

public:
    explicit NetworkServer(quint16 port, QObject *parent = nullptr);
    ~NetworkServer();

    void stopServer();
    bool isListening() const;
    quint16 serverPort() const;
    void sendMessageToClient(const QByteArray &message, bool moveInfo = false);
    bool startServer(quint16 port);

signals:
    void clientDataReceived(const QByteArray &data);
    void clientMoveReceived(const QByteArray &data);
    void clientConnected(const QString &ipAddress, quint16 port);
    void connectionStatusChanged(bool connected);
    void serverStopped();
    void serverError(const QString &error);

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onError();
    void checkConnectionStatus();

public slots:
    void sendMoveMessageToClient(int startRow, int startCol, int endRow, int endCol);

private:
    QTcpServer *server;
    QTimer *connectionMonitorTimer;
    QList<QTcpSocket *> clientSockets;
    quint16 port;
    bool m_lastConnectionState;

    static const char* SERVER_PREFIX;
};

#endif // NETWORKSERVER_H

