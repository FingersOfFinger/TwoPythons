#ifndef DELETELOBBY_H
#define DELETELOBBY_H

#include "lobby.h"
#include <QWidget>
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

class DeleteLobby:public QWidget
{
    Q_OBJECT

public:
    explicit DeleteLobby(QTcpSocket*, std::string, QString, QString, QWidget *parent = 0);
    ~DeleteLobby();

private:
    QJsonDocument doc;
    QJsonParseError docError;

    QPushButton *deleteButton;
    QPushButton *cancelButton;

    QTcpSocket *socket;
    QByteArray Data;

    std::string id;
    QString login;
    QString name;

public slots:
    void deleteButtonPressed();
    void checkCorrectInput();
    void signal();
    void sockDisc();
    void drowElements();
    void closeWindow();
};

#endif // DELETELOBBY_H
