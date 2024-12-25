#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QTimer>

class NetworkClient : public QObject
{
    Q_OBJECT

public:
    explicit NetworkClient(const QString &host, quint16 port, QObject *parent = nullptr);
    ~NetworkClient();

    void connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    void sendMessage(const QString &message);

signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString &error);
    void dataReceived(const QString &message);
    void connectionStatusChanged(bool connected);

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);
    void slot_dataReceived(const QString &message);
    void checkConnectionStatus();

private:
    QTcpSocket *socket;
    QTimer *connectionMonitorTimer;
    QString host; // Store host for potential reconnection
    quint16 port; // Store port for potential reconnection
};

#endif // NETWORKCLIENT_H
