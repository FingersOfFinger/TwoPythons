#ifndef AUTHORIZATIONVIEW_H
#define AUTHORIZATIONVIEW_H

#include "authorization.h"
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

class AuthorizationView:public QWidget
{
    Q_OBJECT

public:
    explicit AuthorizationView(QWidget *parent = 0);
    ~AuthorizationView();

private:

public slots:

};

#endif // AUTHORIZATIONVIEW_H
