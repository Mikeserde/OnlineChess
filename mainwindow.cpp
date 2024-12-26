#include "mainwindow.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include "chatpanel.h"
#include "chessboard.h"
#include "NetworkServer.h"
#include "statuspanel.h"
#include "NetworkClient.h"

const bool playerColor = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create a central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Instantiate the ChessBoard, StatusPanel, and ChatPanel
    chessBoard = new ChessBoard(this);
    chatPanel = new ChatPanel(this);
    statusPanel = new StatusPanel(playerColor, this);

    // Connect ChessBoard and StatusPanel
    chessBoard->setStatusPanel(statusPanel);
    statusPanel->setChessBoard(chessBoard);

    // Create a horizontal layout to hold the chessboard, status panel, and chat panel
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Chessboard Layout
    QVBoxLayout *chessBoardLayout = new QVBoxLayout;
    chessBoardLayout->addWidget(chessBoard);
    mainLayout->addLayout(chessBoardLayout);

    // Status Panel Layout
    QVBoxLayout *statusLayout = new QVBoxLayout;
    statusLayout->addWidget(statusPanel);
    mainLayout->addLayout(statusLayout);

    // Chat Panel Layout
    QVBoxLayout *chatLayout = new QVBoxLayout;
    chatLayout->addWidget(chatPanel);
    mainLayout->addLayout(chatLayout);

    // Set stretch factors for layouts
    mainLayout->setStretch(0, 3); // Chessboard gets 3 parts of the space
    mainLayout->setStretch(1, 1); // Status panel gets 1 part of the space
    mainLayout->setStretch(2, 1); // Chat panel gets 1 part of the space

    // Set the layout to the central widget
    centralWidget->setLayout(mainLayout);

    // Calculate the new minimum width and height based on the chessboard size
    int newWidth = chessBoard->minimumSize().width() * 1.5;
    int newHeight = chessBoard->minimumSize().height();

    // Set the fixed size of the MainWindow
    setFixedSize(newWidth * 1.2, newHeight);

    setWindowIcon(QIcon(":/images/chess_icon.jpg"));

    // Create the NetworkServer
    server = new NetworkServer(5010, this);

    // Connect server signals to appropriate slots
    connect(server, &NetworkServer::clientConnected, this, &MainWindow::onConnected);
    connect(server, &NetworkServer::clientDataReceived, this, &MainWindow::onDataReceived);
    connect(server, &NetworkServer::connectionStatusChanged, this, &MainWindow::onConnectionStatusChanged);
    connect(chessBoard, &ChessBoard::moveMessageSent, server, &NetworkServer::sendMoveMessageToClient);

    chessBoard->initial(playerColor);

    // Create the NetworkClient
    const QString &host = "127.0.0.1";
    client = new NetworkClient(host, 5010, this);

    connect(client, &NetworkClient::serverConnected, this, &MainWindow::onConnected);
    connect(client, &NetworkClient::serverDataReceived, this, &MainWindow::onDataReceived);
    connect(client, &NetworkClient::connectionStatusChanged, this, &MainWindow::onConnectionStatusChanged);
    connect(chessBoard, &ChessBoard::moveMessageSent, client, &NetworkClient::sendMoveMessageToServer);

    connect(chatPanel, &ChatPanel::messageSent, this, &MainWindow::onSendMessageClicked);
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
