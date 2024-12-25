#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QIcon>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

#include "statuspanel.h"
#include "mainwindow.h"
#include "chessboard.h"
#include "networkserver.h"
#include "chatpanel.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    // Create a central widget
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Instantiate the ChessBoard, StatusPanel, and ChatPanel
    chessBoard = new ChessBoard(this);
    statusPanel = new StatusPanel(this);
    chatPanel = new ChatPanel(this);

    // Connect ChessBoard and StatusPanel
    chessBoard->setStatusPanel(statusPanel);
    statusPanel->setChessBoard(chessBoard);

    // Create a horizontal layout to hold the chessboard, status panel, and chat panel
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // Chessboard Layout
    QVBoxLayout* chessBoardLayout = new QVBoxLayout;
    chessBoardLayout->addWidget(chessBoard);
    mainLayout->addLayout(chessBoardLayout);

    // Status Panel Layout
    QVBoxLayout* statusLayout = new QVBoxLayout;
    statusLayout->addWidget(statusPanel);
    mainLayout->addLayout(statusLayout);

    // Chat Panel Layout
    QVBoxLayout* chatLayout = new QVBoxLayout;
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
    server = new NetworkServer(this);

    // Connect server signals to appropriate slots
    connect(server, &NetworkServer::clientConnected, this, &MainWindow::onClientConnected);
    connect(server, &NetworkServer::clientDataReceived, this, &MainWindow::onClientDataReceived);
    connect(server, &NetworkServer::connectionStatusChanged, this, &MainWindow::onConnectionStatusChanged);
    connect(chatPanel, &ChatPanel::messageSent, this, &MainWindow::onSendMessageClicked);

    // Optionally start the server here if you want it to start automatically
    // server->startServer();
}

MainWindow::~MainWindow()
{
    server->stopServer();
}

void MainWindow::onClientConnected(const QString& ipAddress)
{
    qDebug() << "Client connected from" << ipAddress;
}

void MainWindow::onClientDataReceived(QTcpSocket* clientSocket, const QByteArray& data)
{
    QString message = QString::fromUtf8(data);
    chatPanel->receiveMessage(message);
}

void MainWindow::onConnectionStatusChanged(bool connected)
{
    if (connected) {
        qDebug() << "Server is now connected to clients";
    } else {
        qDebug() << "Server is no longer connected to any clients";
    }
}

void MainWindow::onSendMessageClicked(const QString& message)
{
    sendMessage(message.toUtf8());
}

void MainWindow::sendMessage(const QByteArray& message)
{
    // Check if there's any connected client
    for (QTcpSocket* socket : server->findChildren<QTcpSocket*>()) {
        if (socket->state() == QAbstractSocket::ConnectedState) {
            socket->write(message);
            socket->flush(); // Ensure the data is sent immediately
        }
    }
}
