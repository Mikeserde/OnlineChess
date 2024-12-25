#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "NetworkServer.h"

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

class ChessBoard;
class StatusPanel;
class ChatPanel;
class NetworkClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ChessBoard *chessBoard;
    StatusPanel *statusPanel;
    ChatPanel *chatPanel;
    NetworkServer *server;
    NetworkClient *client;
};

#endif // MAINWINDOW_H
