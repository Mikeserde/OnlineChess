#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

class NetworkServer : public QObject
{
    Q_OBJECT

public:
    explicit NetworkServer(quint16 port, QObject *parent = nullptr);
    ~NetworkServer();

    bool isListening() const;
    void sendMessageToClients(const QByteArray &message);
    quint16 serverPort() const;
    bool startServer(quint16 port); // Added back the startServer method

public slots:
    void stopServer(); // Changed to public slot for better accessibility

signals:
    void clientDataReceived(QTcpSocket *clientSocket, const QByteArray &data);
    void clientConnected(const QString &ipAddress);
    void connectionStatusChanged(bool connected);
    void errorOccurred(const QString &error);
    void serverStopped();

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();
    void checkConnections();

private:
    QTcpServer *server;
    QTimer *connectionMonitorTimer;
    QList<QTcpSocket*> clientSockets;
};

#endif // NETWORKSERVER_H
