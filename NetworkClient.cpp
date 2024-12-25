#include "NetworkClient.h"

NetworkClient::NetworkClient(const QString &host, quint16 port, QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);

    // Connect socket signals to slots
    connect(socket, &QTcpSocket::connected, this, &NetworkClient::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &NetworkClient::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &NetworkClient::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &NetworkClient::onError);

    // Connect to the server immediately with the provided host and port
    connectToServer(host, port);
    connect(this, &NetworkClient::dataReceived, this, &NetworkClient::slot_dataReceived);
}

NetworkClient::~NetworkClient() {
    if (socket) {
        socket->close();
        delete socket;
    }
}

void NetworkClient::connectToServer(const QString &host, quint16 port) {
    socket->connectToHost(host, port);
}

void NetworkClient::disconnectFromServer() {
    socket->disconnectFromHost();
}

void NetworkClient::sendMessage(const QString &message) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(message.toUtf8());
        socket->flush(); // Ensure the data is sent immediately
    }
}

void NetworkClient::onConnected() {
    qDebug() << "Connected to server";
    emit connected();
}

void NetworkClient::onReadyRead() {
    if (socket) {
        QByteArray data = socket->readAll();
        QString message = QString::fromUtf8(data); // 假设消息是UTF-8编码的
        emit dataReceived(message);
    }
}

void NetworkClient::onDisconnected() {
    qDebug() << "Disconnected from server";
    emit disconnected();
}

void NetworkClient::onError(QAbstractSocket::SocketError socketError) {
    QString errorString = socket->errorString();
    qDebug() << "Socket error (" << socketError << "):" << errorString;
    emit errorOccurred(errorString);
}
void NetworkClient::slot_dataReceived(const QString &message) {
    qDebug() << "Message received from server:" << message.toUtf8();
}

