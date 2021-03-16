#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include "authorization.h"
#include "gamewindow.h"
#include "deletelobby.h"
#include "createlobby.h"
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
#include <QFormLayout>

class mLobby {
public:
    mLobby(long long in_id,QString in_name,QString in_owner)
    {
        id = in_id;
        name = in_name;
        owner = in_owner;
    }
    long long id;
    QString name;
    QString owner;
};

class mStat {
public:
    mStat(QString in_winner,QString in_loser, int in_score)
    {
        winner = in_winner;
        loser = in_loser;
        score = in_score;
    }
    int score;
    QString winner;
    QString loser;
};

namespace Ui {
    class Lobby;
}

class Lobby:public QWidget
{
    Q_OBJECT

public:
    explicit Lobby(QTcpSocket*,QString,QWidget *parent = nullptr);
    ~Lobby();

private:
    Ui::Lobby *ui;

    QString login;
    QTcpSocket *socket;
    QVector<mLobby*> listLobby;
    QVector<mStat*> listStat;

public slots:
    void signal();
    void receiveLobby();
    void sockDisc();
    void enterLobby();
    void createLobby();
    void exitLobby();
    void deleteLobby();
    void refreshLobby();
    void statGame();
    void startGame();
    void exit();

};

#endif // LOBBY_H
