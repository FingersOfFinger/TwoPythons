#ifndef CREATELOBBY_H
#define CREATELOBBY_H

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

class CreateLobby:public QWidget
{
    Q_OBJECT

public:
    explicit CreateLobby(QTcpSocket*, QString, QWidget *parent = 0);
    ~CreateLobby();

private:
    QString Login;
    QTcpSocket *socket;
    QByteArray Data;

public slots:

};

#endif // CREATELOBBY_H
