#include "networkserver.h"
#include <QHostAddress>
#include <QTcpSocket>
#include <QTimer>
#include <QDebug>

NetworkServer::NetworkServer(quint16 port, QObject *parent)
    : QObject(parent)
{
    server = new QTcpServer(this);

    // Connect the newConnection signal to the onNewConnection slot
    connect(server, &QTcpServer::newConnection, this, &NetworkServer::onNewConnection);

    // Timer for monitoring connections
    connectionMonitorTimer = new QTimer(this);
    connect(connectionMonitorTimer, &QTimer::timeout, this, &NetworkServer::checkConnections);

    // Start the server immediately with the given port
    if (!startServer(port)) {
        qCritical().noquote() << "(server) Failed to start server on port" << port << "Error:" << server->errorString();
        emit errorOccurred(server->errorString());
    } else {
        qDebug().noquote() << "(server) Server started on port" << server->serverPort();
    }
}

NetworkServer::~NetworkServer()
{
    if (server) {
        server->close();
        delete server;
        qDebug().noquote() << "(server) Server closed";
    }
    if (connectionMonitorTimer) {
        connectionMonitorTimer->stop();
        delete connectionMonitorTimer;
        qDebug().noquote() << "(server) Connection monitor timer stopped";
    }
}

bool NetworkServer::isListening() const
{
    return server->isListening();
}

/**
 * @brief Starts the server on the specified port.
 * @param port The port number on which the server should listen.
 * @return True if the server was successfully started, false otherwise.
 */
bool NetworkServer::startServer(quint16 port)
{
    if (!server->isListening()) {
        if (server->listen(QHostAddress::Any, port)) {
            qDebug().noquote() << "(server) Server is listening on port" << server->serverPort();
            connectionMonitorTimer->start(5000); // Start checking connections
            emit connectionStatusChanged(true);
            return true;
        } else {
            qCritical().noquote() << "(server) Server could not start on port" << port << "Error:" << server->errorString();
            emit errorOccurred(server->errorString());
            return false;
        }
    }
    return true; // Server was already listening
}

void NetworkServer::stopServer()
{
    if (server->isListening()) {
        server->close();
        connectionMonitorTimer->stop();
        emit serverStopped();
        emit connectionStatusChanged(false);
        qDebug().noquote() << "(server) Server stopped";
    }
}

quint16 NetworkServer::serverPort() const
{
    return server->serverPort();
}

void NetworkServer::sendMessageToClients(const QByteArray &message)
{
    for (QTcpSocket *socket : clientSockets) {
        if (socket->state() == QAbstractSocket::ConnectedState) {
            socket->write(message);
            socket->flush(); // Ensure the data is sent immediately
            qDebug().noquote() << "(server) Sent message to client" << socket->peerAddress().toString() << ":" << message;
        }
    }
}

void NetworkServer::onNewConnection()
{
    // Get the new connection socket
    QTcpSocket *clientSocket = server->nextPendingConnection();
    clientSockets.append(clientSocket); // Add to the list

    // Connect socket signals to slots
    connect(clientSocket, &QTcpSocket::readyRead, this, &NetworkServer::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &NetworkServer::onDisconnected);

    // Record and emit the IP address of the connected client
    QString ipAddress = clientSocket->peerAddress().toString();
    qDebug().noquote() << "(server) New connection from:" << ipAddress;
    emit clientConnected(ipAddress);
}

void NetworkServer::onReadyRead()
{
    // Get the socket that emitted the signal
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket) {
        QByteArray data = clientSocket->readAll();
        QString ipAddress = clientSocket->peerAddress().toString();
        qDebug().noquote() << "(server) Data received from client" << ipAddress << ":" << data;
        emit clientDataReceived(clientSocket, data); // Emit the signal
    }
}

void NetworkServer::onDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket) {
        QString ipAddress = clientSocket->peerAddress().toString();
        qDebug().noquote() << "(server) Client disconnected:" << ipAddress;
        clientSockets.removeOne(clientSocket); // Remove from list
        clientSocket->deleteLater(); // Clean up the socket
    }
}

void NetworkServer::checkConnections()
{
    if (server->isListening()) { // Only check if server is listening
        bool anyConnected = !clientSockets.isEmpty();
        qDebug().noquote() << "(server) Connection status:" << (anyConnected ? "Connected" : "No connections");
        emit connectionStatusChanged(anyConnected);
    }
}
