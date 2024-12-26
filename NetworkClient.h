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

    void sendMessageToServer(const QByteArray &message, bool moveInfo = false);

signals:
    void connectionStatusChanged(bool connected);
    void serverDataReceived(const QByteArray &data);
    void serverMoveReceived(const QByteArray &data);
    void serverConnected(const QString &host, quint16 port);

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onError();
    void checkConnectionStatus();

public slots:
    void sendMoveMessageToServer(int startRow, int startCol, int endRow, int endCol);

private:
    QTcpSocket *socket;
    QTimer *connectionMonitorTimer;
    QString host;
    quint16 port;
    bool m_lastConnectionState;

    static const char* CLIENT_PREFIX;
};

#endif // NETWORKCLIENT_H

