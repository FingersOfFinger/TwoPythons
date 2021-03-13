#ifndef Authorization_H
#define Authorization_H

#include "QWidget"
#include "authorizationview.h"
#include "registration.h"
#include "lobby.h"
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

class Authorization:public QWidget
{
    Q_OBJECT

public:
    explicit Authorization(QTcpSocket*,QWidget *parent = 0);
    ~Authorization();

private:
    QTcpSocket *socket;
    QByteArray Data;

    QLabel *image;
    QImage *i;

    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QPushButton *signInButton;
    QPushButton *registrationlButton;

    QJsonDocument doc;
    QJsonParseError docError;

public slots:
    void checkTheEnteredData();
    void enableSignInButton();
    void signInButtonPressed();
    void registrationButtonPressed();
    void sockDisc();

    void drowElements();
    void signal();
};

#endif // Authorization_H
