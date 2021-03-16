#ifndef CREATELOBBY_H
#define CREATELOBBY_H

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

class CreateLobby:public QWidget
{
    Q_OBJECT

public:
    explicit CreateLobby(QTcpSocket*, QString, QWidget *parent = 0);
    ~CreateLobby();

private:
    QString login;
    QLineEdit *nameLine;
    QPushButton *createButton;
    QPushButton *cancelButton;
    QLabel *nameLabel;

    QJsonDocument doc;
    QJsonParseError docError;

    QTcpSocket *socket;
    QByteArray Data;

    QLabel *image;
    QImage *i;

public slots:
    void sockDisc();
    void checkCorrectInput();
    void closeWindow();
    void drowElements();
    void signal();
    void createButtonPressed();
    void enableCreateButton();

};

#endif // CREATELOBBY_H
