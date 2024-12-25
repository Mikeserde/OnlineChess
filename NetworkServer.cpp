#include "networkserver.h"

NetworkServer::NetworkServer(QObject *parent) : QObject(parent) {
    server = new QTcpServer(this);
    quint16 port = 5010;

    // Connect the newConnection signal to the onNewConnection slot
    connect(server, &QTcpServer::newConnection, this, &NetworkServer::onNewConnection);

    // Timer for monitoring connections
    connectionMonitorTimer = new QTimer(this);
    connect(connectionMonitorTimer, &QTimer::timeout, this, &NetworkServer::checkConnections);

    // Start the server immediately with the given port or default
    if (!startServer(port)) {
        qCritical() << "Failed to start server on port" << port;
    }
}

NetworkServer::~NetworkServer() {
    if (server) {
        server->close();
        delete server;
    }
    if (connectionMonitorTimer) {
        connectionMonitorTimer->stop();
        delete connectionMonitorTimer;
    }
}

bool NetworkServer::isListening() const {
    return server->isListening();
}

bool NetworkServer::startServer(quint16 port) {
    if (!server->isListening()) {
        if (server->listen(QHostAddress::Any, port)) {
            qDebug() << "Server is listening on port" << server->serverPort();
            connectionMonitorTimer->start(5000); // Start checking connections
            emit connectionStatusChanged(true); // Signal that the server has started
            return true;
        } else {
            qDebug() << "Server could not start on port" << port;
            return false;
        }
    }
    return true; // Server was already listening
}

void NetworkServer::stopServer() {
    if (server->isListening()) {
        server->close();
        connectionMonitorTimer->stop();
        emit connectionStatusChanged(false); // Notify that server is no longer listening
    }
}

quint16 NetworkServer::serverPort() const {
    return server->serverPort();
}

void NetworkServer::sendMessageToClients(const QByteArray& message) {
    for (QTcpSocket* socket : server->findChildren<QTcpSocket*>()) {
        if (socket->state() == QAbstractSocket::ConnectedState) {
            socket->write(message);
            socket->flush(); // Ensure the data is sent immediately
        }
    }
}

void NetworkServer::onNewConnection() {
    // Get the new connection socket
    QTcpSocket *clientSocket = server->nextPendingConnection();

    // Connect socket signals to slots
    connect(clientSocket, &QTcpSocket::readyRead, this, &NetworkServer::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &NetworkServer::onDisconnected);

    // Record and emit the IP address of the connected client
    QString ipAddress = clientSocket->peerAddress().toString();
    qDebug() << "New connection from:" << ipAddress;
    emit clientConnected(ipAddress);
}

void NetworkServer::onReadyRead() {
    // Get the socket that emitted the signal
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        QByteArray data = clientSocket->readAll();
        emit clientDataReceived(clientSocket, data); // Emit the signal
    }
}

void NetworkServer::onDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        QString ipAddress = clientSocket->peerAddress().toString();
        qDebug() << "Client disconnected:" << ipAddress;
        clientSocket->deleteLater(); // Clean up the socket
    }
}

void NetworkServer::checkConnections() {
    if (server->isListening()) { // Only check if server is listening
        bool anyConnected = false;
        for (QTcpSocket* socket : server->findChildren<QTcpSocket*>()) {
            if (socket->state() == QAbstractSocket::ConnectedState) {
                anyConnected = true;
                break;
            }
        }
        emit connectionStatusChanged(anyConnected);
    }
}
