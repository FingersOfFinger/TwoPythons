#include "createlobby.h"

CreateLobby::CreateLobby(QTcpSocket *inSocket, QString Login, QWidget *parent) :
    QWidget(parent)
{
    socket = inSocket;
    login = Login;
    drowElements();
    signal();
}

void CreateLobby::signal()
{
    connect(createButton, SIGNAL(clicked(bool)), this, SLOT(createButtonPressed()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));

    connect(nameLine, SIGNAL(textChanged(QString)), this, SLOT(enableCreateButton()));

    connect(socket,SIGNAL(readyRead()),this,SLOT(checkCorrectInput()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

void CreateLobby::createButtonPressed()
{
    std::string name = nameLine->text().toStdString();
    char request[100];
    std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"createLobby\",\"name\":\""+name+"\",\"owner\":\""+login.toStdString()+"\"}\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);
}

void CreateLobby::checkCorrectInput()
{
    if(socket->waitForConnected(50))
    {
        socket->waitForReadyRead(50);
        Data = socket->readAll();
        qDebug() << Data;
        doc = QJsonDocument::fromJson(Data, &docError);
        if (docError.errorString() == "no error occurred")
        {
            if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveCreateLobby") && (doc.object().value("access").toString() == "true"))
            {
                QMessageBox::information(this, "Информация","Лобби: "+nameLine->text()+" создано!");
                closeWindow();
            }
            else
            {
                QMessageBox::critical(this, "Ошибка", "<div align=center>Ошибка корректности ввода данных!</div>");
            }
        }
        else
        {
            QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
        }
    }
}

void CreateLobby::closeWindow()
{
    disconnect(socket,SIGNAL(readyRead()),this,SLOT(checkCorrectInput()));
    socket->waitForDisconnected(50);
    Lobby *closeLobby = new Lobby(socket,login);
    this->hide();
    closeLobby->show();
}

void CreateLobby::sockDisc()
{
    socket->disconnect();
}

CreateLobby ::~CreateLobby()
{
    sockDisc();
}
