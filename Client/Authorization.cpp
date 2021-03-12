#include "authorization.h"

Authorization::Authorization(QTcpSocket *Socket,QWidget *parent) :
    QWidget(parent)
{
    socket = Socket;
    drowElements();
    signal();
}

void Authorization::signal()
{
    connect(signInButton, SIGNAL(clicked(bool)), this, SLOT(signInButtonPressed()));
    connect(registrationlButton, SIGNAL(clicked(bool)), this, SLOT(registrationButtonPressed()));

    connect(loginEdit, SIGNAL(textChanged(QString)), this, SLOT(enableSignInButton(QString)));
    connect(passwordEdit, SIGNAL(textChanged(QString)), this, SLOT(enableSignInButton(QString)));

    connect(socket,SIGNAL(readyRead()),this,SLOT(checkTheEnteredData()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

void Authorization::signInButtonPressed()
{

    /*
    QByteArray login = QByteArray::fromStdString(loginEdit->text().toStdString());
    QByteArray password = QByteArray::fromStdString(passwordEdit->text().toStdString());
    */

    char request[100];
    std::string login = loginEdit->text().toStdString();
    std::string password = passwordEdit->text().toStdString();
    std::string request2 = "{\"globalType\":\"connection\",\"type\":\"authorization\",\"login\":\""+login+"\",\"password\":\""+password+"\"}\r\n\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);
}

void Authorization::checkTheEnteredData()
{
    disconnect(socket,SIGNAL(readyRead()),this,SLOT(checkTheEnteredData()));
    socket->waitForDisconnected(50);
    QMessageBox::information(this,"Информация","Добро пожаловать, "+loginEdit->text()+"!");
    Lobby *openLobby = new Lobby(socket,loginEdit->text());
    this->hide();
    openLobby->show();

    Data = socket->readAll();
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);

    /*
    if (docError.errorString() == "no error occurred")
    {
        if ((doc.object().value("globalType").toString() == "connection") && (doc.object().value("type").toString() == "authorization") && (doc.object().value("access").toString() == "true"))
        {
            disconnect(socket,SIGNAL(readyRead()),this,SLOT(checkTheEnteredData()));
            socket->waitForDisconnected(50);
            QMessageBox::information(this,"Информация","Добро пожаловать, "+loginEdit->text()+"!");
            Lobby *openLobby = new Lobby(socket,loginEdit->text());
            this->hide();
            openLobby->show();
        }
        else
        {
            QMessageBox::critical(this, "Ошибка", "<div align=center>Неверный логин или пароль!</div> \n <div align = center>Пожалуйста, попробуйте ещё раз</div>");
        }
    }
    else
    {
        QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
    }
    */
}

void Authorization::registrationButtonPressed()
{
    disconnect(socket,SIGNAL(readyRead()),this,SLOT(checkTheEnteredData()));
    socket->waitForDisconnected(50);
    Registration *openRegistration = new Registration(socket);
    this->hide();
    openRegistration->show();
}

void Authorization::sockDisc()
{
    socket->deleteLater();
}

Authorization ::~Authorization()
{

}
