#include <QObject>
#include <QStackedWidget>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "mainwindow.h"
#include "chesslobby.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "chess_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // 创建MainWindow实例以获取其大小
    MainWindow *mainWindow = new MainWindow;
    QSize mainWindowSize = mainWindow->size();

    // 创建ChessLobby实例并设置大小
    ChessLobby *lobby = new ChessLobby;
    lobby->resize(mainWindowSize); // 设置lobby的大小与mainwindow一致

    // 创建QStackedWidget
    QStackedWidget *stackedWidget = new QStackedWidget;

    // 将它们添加到QStackedWidget中
    stackedWidget->addWidget(lobby);
    stackedWidget->addWidget(mainWindow);

    // 设置ChessLobby为初始页面
    stackedWidget->setCurrentIndex(0);

    // 连接信号和槽
    QObject::connect(lobby, &ChessLobby::StartGame, [stackedWidget](){ stackedWidget->setCurrentIndex(1); });

    // 显示stackedWidget
    stackedWidget->show();

    return a.exec();
}
