#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include "registration.h"
#include "authorization.h"
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

namespace Ui {
class Lobby;
}

class Lobby : public QWidget
{
    Q_OBJECT

public:
    explicit Lobby(QTcpSocket*,QString,QWidget *parent = nullptr);
    ~Lobby();

private:
    Ui::Lobby *ui;
    static const int WIDTH=500;
    static const int HIGHT=180;

    QString Login;
    QTcpSocket *socket;
    QByteArray Data;
    int id;

    QJsonDocument doc;
    QJsonParseError docError;

public slots:
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
