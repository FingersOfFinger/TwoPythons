#ifndef CREATELOBBYVIEW_H
#define CREATELOBBYVIEW_H

#include "createlobby.h"
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

class CreateLobbyView:public QWidget
{
    Q_OBJECT

public:
    explicit CreateLobbyView(QWidget *parent = 0);
    ~CreateLobbyView();

private:
    QLabel *image;
    QImage *i;

public slots:

};

#endif // CREATELOBBYVIEW_H
