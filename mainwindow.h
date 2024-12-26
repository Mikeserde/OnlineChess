#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "NetworkServer.h"
#include "NetworkClient.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class ChessBoard;
class StatusPanel;
class ChatPanel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onClientConnected(const QString& ipAddress);
    void onClientDataReceived(QTcpSocket* clientSocket, const QByteArray& data);
    void onConnectionStatusChanged(bool connected);
    void onSendMessageClicked(const QString& message);

private:
    void sendMessage(const QByteArray& message);

    ChessBoard* chessBoard;
    StatusPanel* statusPanel;
    ChatPanel* chatPanel;
    NetworkServer* server;
    NetworkClient* client;
};

#endif // MAINWINDOW_H
