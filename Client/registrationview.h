#ifndef REGISTRATIONVIEW_H
#define REGISTRATIONVIEW_H

#include "registration.h"
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

class RegistrationView:public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationView(QWidget *parent = 0);
    ~RegistrationView();

private:

public slots:

};

#endif // REGISTRATIONVIEW_H
