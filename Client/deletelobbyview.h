#ifndef DELETELOBBYVIEW_H
#define DELETELOBBYVIEW_H

#include "deletelobby.h"
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

class DeleteLobbyView:public QWidget
{
    Q_OBJECT

public:
    explicit DeleteLobbyView(QWidget *parent = 0);
    ~DeleteLobbyView();

private:

public slots:
};

#endif // DELETELOBBYVIEW_H
