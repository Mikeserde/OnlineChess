#ifndef CHESSLOBBY_H
#define CHESSLOBBY_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>

class ChessLobby : public QWidget
{
    Q_OBJECT

public:
    explicit ChessLobby(QWidget *parent = nullptr);
    ~ChessLobby();

signals:
    void StartAsHost();
    void StartAsMember(QString hostIP);
    void StartGame();
private slots:
    void OnModeChanged(bool checked);
    void OnConnectClicked();
    void OnNewConnection();
    void OnConnected();
    void OnDisconnected();
    void OnReadyRead();

private:
    QRadioButton *hostButton;
    QRadioButton *memberButton;
    QLineEdit *ipInput;
    QTcpServer *server;
    QTcpSocket *socket;
    QPushButton *startGameButton; // 开始游戏按钮
};

#endif // CHESSLOBBY_H
