#ifndef Authorization_H
#define Authorization_H

#include "QWidget"
#include "Registration.h"
#include "Lobby.h"
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
    explicit Authorization(QWidget *parent = 0);
    ~Authorization();

private:
    static const int WIDTH=500;
    static const int HIGHT=180;
    void drowElements();
    QTcpSocket *socket;
    QByteArray Data;

    QJsonDocument doc;
    QJsonParseError docError;

    QLabel *image;
    QImage *i;

    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QPushButton *signInButton;
    QPushButton *registrationlButton;

public slots:
    bool checkTheEnteredData();
    void enableSignInButton(QString text);
    void signInButtonPressed();
    void registrationButtonPressed();
    void sockConnect();
    void sockDisc();
};

#endif // Authorization_H
