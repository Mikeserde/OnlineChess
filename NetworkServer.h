#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>

class NetworkServer : public QObject {
    Q_OBJECT

public:
    explicit NetworkServer(QObject *parent = nullptr);
    ~NetworkServer();

    bool isListening() const;
    bool startServer(quint16 port = 5010);
    void stopServer();
    quint16 serverPort() const;
    void sendMessageToClients(const QByteArray& message);

signals:
    void clientDataReceived(QTcpSocket* clientSocket, const QByteArray& data);
    void clientConnected(const QString& ipAddress);
    void connectionStatusChanged(bool connected);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
    void checkConnections();

private:
    QTcpServer *server;
    QTimer *connectionMonitorTimer;
};

#endif // NETWORKSERVER_H
