#include "mainwindow.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QEvent>
#include "chatpanel.h"
#include "chessboard.h"
#include "NetworkServer.h"
#include "statuspanel.h"
#include "NetworkClient.h"

const bool playerColor = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 创建中央部件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 实例化棋盘、状态面板和聊天面板
    chessBoard = new ChessBoard(this);
    chatPanel = new ChatPanel(this);
    statusPanel = new StatusPanel(playerColor, this);

    // 连接棋盘和状态面板
    chessBoard->setStatusPanel(statusPanel);
    statusPanel->setChessBoard(chessBoard);

    // 创建一个水平布局来容纳棋盘、状态面板和聊天面板
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // 棋盘布局
    QVBoxLayout *chessBoardLayout = new QVBoxLayout;
    chessBoardLayout->addWidget(chessBoard);
    mainLayout->addLayout(chessBoardLayout);

    // 状态面板布局
    QVBoxLayout *statusLayout = new QVBoxLayout;
    statusLayout->addWidget(statusPanel);
    mainLayout->addLayout(statusLayout);

    // 聊天面板布局
    QVBoxLayout *chatLayout = new QVBoxLayout;
    chatLayout->addWidget(chatPanel);
    mainLayout->addLayout(chatLayout);

    // 设置布局的伸缩因子
    mainLayout->setStretch(0, 3); // 棋盘占用3份空间
    mainLayout->setStretch(1, 1); // 状态面板占用1份空间
    mainLayout->setStretch(2, 1); // 聊天面板占用1份空间

    // 设置中央部件的布局
    centralWidget->setLayout(mainLayout);

    // 计算新的大小，但不要设置固定大小
    int newWidth = chessBoard->minimumSize().width() * 1.5;
    int newHeight = chessBoard->minimumSize().height();

    // 设置初始大小而不是固定大小
    resize(newWidth * 1.2, newHeight);

    setWindowIcon(QIcon(":/images/chess_icon.jpg"));

    // 创建网络服务器
    server = new NetworkServer(5010, this);

    // 连接服务器信号到相应的槽
    connect(server, &NetworkServer::clientConnected, this, &MainWindow::onConnected);
    connect(server, &NetworkServer::clientDataReceived, this, &MainWindow::onDataReceived);
    connect(server, &NetworkServer::connectionStatusChanged, this, &MainWindow::onConnectionStatusChanged);
    connect(chessBoard, &ChessBoard::moveMessageSent, server, &NetworkServer::sendMoveMessageToClient);

    chessBoard->initial(playerColor);

    // 创建网络客户端
    const QString &host = "127.0.0.1";
    client = new NetworkClient(host, 5010, this);

    connect(client, &NetworkClient::serverConnected, this, &MainWindow::onConnected);
    connect(client, &NetworkClient::serverDataReceived, this, &MainWindow::onDataReceived);
    connect(client, &NetworkClient::connectionStatusChanged, this, &MainWindow::onConnectionStatusChanged);
    connect(chessBoard, &ChessBoard::moveMessageSent, client, &NetworkClient::sendMoveMessageToServer);

    connect(chatPanel, &ChatPanel::messageSent, this, &MainWindow::onSendMessageClicked);

    // 覆盖 resizeEvent 方法以确保在大小改变时重新调整布局
    this->installEventFilter(this);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::Resize) {
        centralWidget()->layout()->invalidate(); // 重新布局
        centralWidget()->updateGeometry(); // 更新几何
    }
    return QMainWindow::eventFilter(obj, event);
}

MainWindow::~MainWindow()
{
    if (server) {
        server->stopServer();
        delete server;
    }
    if (client) {
        delete client;
    }
}

void MainWindow::onConnected(const QString &ipAddress, quint16 port)
{
    qDebug() << "(server) Client connected from ip:" << ipAddress << " and port:" << port;
}

void MainWindow::onDataReceived(const QByteArray &data)
{
    QString message = QString::fromUtf8(data);
    chatPanel->receiveMessage(message);
}

void MainWindow::onConnectionStatusChanged(bool connected)
{
    if (connected) {
        qDebug() << "(server) Server is now connected to clients";
    } else {
        qDebug() << "(server) Server is no longer connected to any clients";
    }
}

void MainWindow::onSendMessageClicked(const QString &message)
{
    sendMessage(message.toUtf8());
}

void MainWindow::sendMessage(const QByteArray &message)
{
    if (server) {
        server->sendMessageToClient(message);
    }

    if (client) {
        client->sendMessageToServer(message);
    }
}
