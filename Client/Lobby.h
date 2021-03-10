#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include "Registration.h"
#include "Authorization.h"
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QtGui>
#include <QColor>
#include <QGridLayout>
#include <QMessageBox>

namespace Ui {
class Lobby;
}

class Lobby : public QWidget
{
    Q_OBJECT

public:
    explicit Lobby(QString,QWidget *parent = nullptr);
    ~Lobby();

private:
    Ui::Lobby *ui;
    static const int WIDTH=500;
    static const int HIGHT=180;

    QString Login;
    QTcpSocket *socket;
    QByteArray Data;

    QJsonDocument doc;
    QJsonParseError docError;

public slots:
     void sockConnect();
     void sockDisc();
     void enterLobby();
     bool receiveEnterLobby();
     void createLobby();
     bool receiveCreateLobby();
     void exitLobby();
     bool receiveExitLobby();
     void deleteLobby();
     bool receiveDeleteLobby();
     void refreshLobby();
     void receiveGetLobby();
     void statGame();
     void receiveStatGame();
     void startGame();
     bool receiveStartGame();
     void exit();
};

#endif // LOBBY_H
