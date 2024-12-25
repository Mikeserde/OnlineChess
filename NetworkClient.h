#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QString>

class NetworkClient : public QObject {
    Q_OBJECT

public:
    explicit NetworkClient(const QString &host, quint16 port, QObject *parent);
    ~NetworkClient();

    void connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    void sendMessage(const QString &message);

signals:
    void connected();
    void disconnected();
    void errorOccurred(const QString& error);
    void dataReceived(const QString &message);
private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);
    void slot_dataReceived(const QString &message);
private:
    QTcpSocket *socket;
};

#endif // NETWORKCLIENT_H
