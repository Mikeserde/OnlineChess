QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChatPanel.cpp \
    ChessBoard.cpp \
    NetworkClient.cpp \
    NetworkServer.cpp \
    PromotionDialog.cpp \
    StatusPanel.cpp \
    chesslobby.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Bishop.h \
    ChatPanel.h \
    ChessBoard.h \
    ChessPiece.h \
    King.h \
    Knight.h \
    NetworkClient.h \
    NetworkServer.h \
    Pawn.h \
    PromotionDialog.h \
    Queen.h \
    Rook.h \
    StatusPanel.h \
    chesslobby.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Network-app_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
