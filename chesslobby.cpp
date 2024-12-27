#include "chesslobby.h"

ChessLobby::ChessLobby(QWidget *parent)
    : QWidget(parent)
    , server(nullptr)
    , socket(nullptr)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // 添加选择模式的单选按钮
    hostButton = new QRadioButton("成为房主");
    memberButton = new QRadioButton("加入房间");
    connect(hostButton, &QRadioButton::toggled, this, &ChessLobby::OnModeChanged);
    connect(memberButton, &QRadioButton::toggled, this, &ChessLobby::OnModeChanged);
    mainLayout->addWidget(hostButton);
    mainLayout->addWidget(memberButton);

    // 添加IP输入框和标签
    QHBoxLayout *ipLayout = new QHBoxLayout;
    QLabel *ipLabel = new QLabel("房主IP地址:");
    ipInput = new QLineEdit;
    ipInput->setEnabled(false);
    ipLayout->addWidget(ipLabel);
    ipLayout->addWidget(ipInput);
    mainLayout->addLayout(ipLayout);

    // 添加连接/监听按钮
    QPushButton *connectButton = new QPushButton("连接/监听");
    connect(connectButton, &QPushButton::clicked, this, &ChessLobby::OnConnectClicked);
    mainLayout->addWidget(connectButton);

    // 添加开始游戏按钮
    startGameButton = new QPushButton("开始游戏");
    connect(startGameButton, &QPushButton::clicked, this, &ChessLobby::StartGame); // 连接按钮点击信号到StartGame信号
    mainLayout->addWidget(startGameButton);

    setLayout(mainLayout);
}


ChessLobby::~ChessLobby()
{
    delete server;
    delete socket;
}

void ChessLobby::OnModeChanged(bool checked)
{
    QRadioButton *button = qobject_cast<QRadioButton*>(sender());
    if (button && button->text() == "加入成员")
    {
        ipInput->setEnabled(checked);
    }
    else
    {
        ipInput->setEnabled(!checked);
    }
}

void ChessLobby::OnConnectClicked()
{
    if (hostButton->isChecked())
    {
        // 如果是房主，启动服务器监听
        if (!server)
        {
            server = new QTcpServer(this);
            if (!server->listen(QHostAddress::Any, 12345))
            {
                QMessageBox::critical(this, "错误", "无法启动服务器: " + server->errorString());
                return;
            }
            connect(server, &QTcpServer::newConnection, this, &ChessLobby::OnNewConnection);
            QMessageBox::information(this, "成功", "服务器已启动，正在监听连接...");
        }
        emit StartAsHost();
    }
    else
    {
        // 如果是成员，尝试连接到服务器
        if (!socket)
        {
            QString ip = ipInput->text();
            if (ip.isEmpty())
            {
                QMessageBox::warning(this, "警告", "请输入房主的IP地址");
                return;
            }
            socket = new QTcpSocket(this);
            connect(socket, &QTcpSocket::connected, this, &ChessLobby::OnConnected);
            connect(socket, &QTcpSocket::disconnected, this, &ChessLobby::OnDisconnected);
            socket->connectToHost(ip, 12345);
            emit StartAsMember(ip);
        }
    }
}

void ChessLobby::OnNewConnection()
{
    socket = server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &ChessLobby::OnReadyRead);
    QMessageBox::information(this, "连接成功", "一个玩家已连接");
}

void ChessLobby::OnConnected()
{
    QMessageBox::information(this, "连接成功", "已成功连接到房主");
}

void ChessLobby::OnDisconnected()
{
    QMessageBox::information(this, "断开连接", "与房主已断开连接");
}

void ChessLobby::OnReadyRead()
{
    // 处理来自客户端的数据
    // 这里可以根据需要添加逻辑来处理接收到的数据
}
