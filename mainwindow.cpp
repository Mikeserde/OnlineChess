#include <QHBoxLayout>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "chatpanel.h"
#include "chessboard.h"
#include "mainwindow.h"
#include "NetworkServer.h"
#include "NetworkClient.h"
#include "statuspanel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create a central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Instantiate the ChessBoard, StatusPanel, and ChatPanel
    chessBoard = new ChessBoard(this);
    statusPanel = new StatusPanel(this);
    chatPanel = new ChatPanel(this);

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
    const QString host = "127.0.0.1";
    client = new NetworkClient(host, 5010, this);
}

MainWindow::~MainWindow()
{
    if (server) {
        delete server;
    }

    if (client) {
        delete client;
    }
}
