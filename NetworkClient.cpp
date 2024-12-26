#include "NetworkClient.h"
#include <QDebug>
#include <QTimer>

const char* NetworkClient::CLIENT_PREFIX = "(client)";

NetworkClient::NetworkClient(const QString &host, quint16 port, QObject *parent)
    : QObject(parent), host(host), port(port), m_lastConnectionState(false)
{
    socket = new QTcpSocket(this);

    // Connect socket signals to slots
    connect(socket, &QTcpSocket::connected, this, &NetworkClient::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &NetworkClient::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &NetworkClient::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &NetworkClient::onError);

    // Timer for monitoring connection status
    connectionMonitorTimer = new QTimer(this);
    connect(connectionMonitorTimer, &QTimer::timeout, this, &NetworkClient::checkConnectionStatus);
    connectionMonitorTimer->start(5000); // Start timer with 5 seconds interval

    // Attempt to connect to the server immediately with the provided host and port
    socket->connectToHost(host, port);

    qDebug().noquote() << CLIENT_PREFIX << "Creating client connection to" << host << "on port" << port;
}

NetworkClient::~NetworkClient()
{
    if (socket) {
        socket->close();
        delete socket;
    }
    if (connectionMonitorTimer) {
        connectionMonitorTimer->stop();
        delete connectionMonitorTimer;
    }
    qDebug().noquote() << CLIENT_PREFIX << "Client connection destroyed";
}

void NetworkClient::onConnected()
{
    emit serverConnected(host, port);
    qDebug().noquote() << CLIENT_PREFIX << "Connected to" << host << "on port" << port;
}

void NetworkClient::onReadyRead()
{
    if (socket) {
        QByteArray data = socket->readAll();
        if (data.startsWith("[MOVE]")) {
            // Handle move data
            data = data.mid(5); // Remove the prefix
            emit serverMoveReceived(data);
            qDebug().noquote() << CLIENT_PREFIX << "Move data received from server:" << data;
        } else if (data.startsWith("[MSG]")) {
            // Handle regular message
            data = data.mid(4); // Remove the prefix
            emit serverDataReceived(data);
            qDebug().noquote() << CLIENT_PREFIX << "Chat message received from server:" << data;
        } else {
            qDebug().noquote() << CLIENT_PREFIX << "Received invalid message from server:" << data;
        }
    }
}


void NetworkClient::onDisconnected()
{
    qDebug().noquote() << CLIENT_PREFIX << "Disconnected from server";
    emit connectionStatusChanged(false);
}

void NetworkClient::onError()
{
    qDebug().noquote() << CLIENT_PREFIX << "Error occurred:" << socket->errorString();
}

void NetworkClient::sendMessageToServer(const QByteArray &message, bool moveInfo)
{
    QByteArray messageWithPrefix;

    if (moveInfo) {
        messageWithPrefix = "[MOVE]" + message;
    } else {
        messageWithPrefix = "[MSG]" + message;
    }

    if (socket->state() == QAbstractSocket::ConnectedState) {
        qDebug().noquote() << CLIENT_PREFIX << "Sending message:" << messageWithPrefix;
        if (socket->write(messageWithPrefix) != -1) {
            socket->flush(); // Ensure the data is sent immediately
        } else {
            qDebug().noquote() << CLIENT_PREFIX << "Failed to send message.";
        }
    } else {
        qDebug().noquote() << CLIENT_PREFIX << "Attempted to send message, but not connected";
    }
}

void NetworkClient::checkConnectionStatus()
{
    bool isConnected = socket->state() == QAbstractSocket::ConnectedState;
    if (m_lastConnectionState != isConnected) {
        m_lastConnectionState = isConnected;
        emit connectionStatusChanged(isConnected);
        qDebug().noquote() << CLIENT_PREFIX << "Connection status:" << (isConnected ? "Connected" : "Disconnected");
    }
}


void NetworkClient::sendMoveMessageToServer(int startRow, int startCol, int endRow, int endCol)
{

}
