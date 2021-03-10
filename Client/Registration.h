#ifndef Registration_H
#define Registration_H
#include "QWidget"
#include "Authorization.h"
#include <QPainter>
#include <QPushButton>
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
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFileDialog>

class Registration:public QWidget
{
    Q_OBJECT
public:
    explicit Registration(QWidget *parent = 0);
    ~Registration();

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

    QLineEdit *loginLine;
    QLineEdit *passwordLine;
    QPushButton *registerButton;
    QPushButton *cancelButton;
    QLabel *loginLabel;
    QLabel *passwordLabel;

public slots:
    void sockConnect();
    void sockDisc();
    void enableRegisterButton(QString text);
    void registerButtonPressed();
    bool checkCorrectInput();
    void closeWindow();
};

#endif // Registration_H
