#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "NetworkClient.h"
#include "NetworkServer.h"

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

class ChessBoard;
class StatusPanel;
class ChatPanel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConnected(const QString &host, quint16 port);
    void onDataReceived(const QByteArray &data);
    void onConnectionStatusChanged(bool connected);
    void onSendMessageClicked(const QString &message);

private:
    void sendMessage(const QByteArray &message);
    bool eventFilter(QObject *obj, QEvent *event);
    ChessBoard *chessBoard;
    StatusPanel *statusPanel;
    ChatPanel *chatPanel;
    NetworkServer *server;
    NetworkClient *client;
};

#endif // MAINWINDOW_H
