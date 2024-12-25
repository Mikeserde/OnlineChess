#include "NetworkClient.h"
#include <QDebug>
#include <QTimer>

NetworkClient::NetworkClient(const QString &host, quint16 port, QObject *parent)
    : QObject(parent)
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

    // Connect to the server immediately with the provided host and port
    connectToServer(host, port);
    connect(this, &NetworkClient::dataReceived, this, &NetworkClient::slot_dataReceived);

    qDebug().noquote() << "(client) Creating client connection to" << host << "on port" << port;
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
    qDebug().noquote() << "(client) Client connection destroyed";
}

void NetworkClient::connectToServer(const QString &host, quint16 port)
{
    qDebug().noquote() << "(client) Attempting to connect to" << host << "on port" << port;
    socket->connectToHost(host, port);
}

void NetworkClient::disconnectFromServer()
{
    qDebug().noquote() << "(client) Disconnecting from server";
    socket->disconnectFromHost();
}

void NetworkClient::sendMessage(const QString &message)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        qDebug().noquote() << "(client) Sending message:" << message;
        socket->write(message.toUtf8());
        socket->flush(); // Ensure the data is sent immediately
    } else {
        qDebug().noquote() << "(client) Attempted to send message, but not connected";
    }
}

void NetworkClient::onConnected()
{
    qDebug().noquote() << "(client) Connected to server";
    emit connected();
    connectionMonitorTimer->start(5000); // Start monitoring the connection
}

void NetworkClient::onReadyRead()
{
    if (socket) {
        QByteArray data = socket->readAll();
        QString message = QString::fromUtf8(data); // Assuming messages are UTF-8 encoded
        emit dataReceived(message);
    }
}

void NetworkClient::onDisconnected()
{
    qDebug().noquote() << "(client) Disconnected from server";
    emit disconnected();
    connectionMonitorTimer->stop();
}

void NetworkClient::onError(QAbstractSocket::SocketError socketError)
{
    QString errorString = socket->errorString();
    qDebug().noquote() << "(client) Socket error (" << socketError << "):" << errorString;
    emit errorOccurred(errorString);
}

void NetworkClient::slot_dataReceived(const QString &message)
{
    qDebug().noquote() << "(client) Message received from server:" << message;
}

void NetworkClient::checkConnectionStatus()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        qDebug().noquote() << "(client) Connection status: Connected";
    } else {
        qDebug().noquote() << "(client) Connection status: Disconnected";
        // Optionally, you could try to reconnect here if desired
        // connectToServer(host, port); // This would require storing host and port as class members
    }
    emit connectionStatusChanged(socket->state() == QAbstractSocket::ConnectedState);
}
