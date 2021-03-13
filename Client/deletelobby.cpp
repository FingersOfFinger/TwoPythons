#include "deletelobby.h"

DeleteLobby::DeleteLobby(QTcpSocket *inSocket, std::string Id, QString Name, QString Login, QWidget *parent) :
    QWidget(parent)
{
    name = Name;
    login = Login;
    id = Id;
    socket = inSocket;
    drowElements();
    signal();
}

void DeleteLobby::signal()
{
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteButtonPressed()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));

    connect(socket,SIGNAL(readyRead()),this,SLOT(checkCorrectInput()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

void DeleteLobby::deleteButtonPressed()
{
    char request[100];
    std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"deleteLobby\",\"id\":\""+id+"\",\"login\":\""+login.toStdString()+"\"}\r\n\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);

    Data = socket->readAll();
    qDebug() << Data;
}

void DeleteLobby::checkCorrectInput()
{
    if(socket->waitForConnected(50))
    {
        socket->waitForReadyRead(50);
        Data = socket->readAll();
        qDebug() << Data;
        doc = QJsonDocument::fromJson(Data, &docError);
        if (docError.errorString() == "no error occurred")
        {
            if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveDeleteLobby") && (doc.object().value("access").toString() == "true"))
            {
                QMessageBox::information(this, "Информация","Лобби: "+name+" удалено!");
                closeWindow();
            }
            else
            {
                QMessageBox::critical(this, "Ошибка", "<div align=center>Вы не являетесь создателем лобби!</div>");
                closeWindow();
            }
        }
        else
        {
            QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
        }
    }
}

void DeleteLobby::closeWindow()
{
    disconnect(socket,SIGNAL(readyRead()),this,SLOT(checkCorrectInput()));
    socket->waitForDisconnected(50);
    Lobby *closeLobby = new Lobby(socket,login);
    this->hide();
    closeLobby->show();
}

void DeleteLobby::sockDisc()
{
    socket->deleteLater();
}

DeleteLobby ::~DeleteLobby()
{

}
