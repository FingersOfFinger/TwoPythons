#include "registration.h"

Registration::Registration(QTcpSocket *inSocket,QWidget *parent) :
    QWidget(parent)
{
    socket = inSocket;
    drowElements();
    signal();
}

void Registration::signal()
{
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(closeWindow()));
    connect(registerButton, SIGNAL(clicked(bool)), this, SLOT(registerButtonPressed()));

    connect(socket,SIGNAL(readyRead()),this,SLOT(checkCorrectInput()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

void Registration::registerButtonPressed()
{
    char request[100];
    std::string login = loginLine->text().toStdString();
    std::string password = passwordLine->text().toStdString();
    std::string request2 = "{\"globalType\":\"connection\",\"type\":\"registration\",\"login\":\""+login+"\",\"password\":\""+password+"\"}\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);
}

void Registration::checkCorrectInput()
{
    if(socket->waitForConnected(50))
    {
        socket->waitForReadyRead(50);
        Data = socket->readAll();
        qDebug() << Data;
        doc = QJsonDocument::fromJson(Data, &docError);
        if (docError.errorString() == "no error occurred")
        {
            if ((doc.object().value("globalType").toString() == "connection") && (doc.object().value("type").toString() == "registration") && (doc.object().value("access").toString() == "true"))
            {
                QMessageBox::information(this, "Информация","Приветствуем, "+loginLine->text()+"!");
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

void Registration::closeWindow()
{
    disconnect(socket,SIGNAL(readyRead()),this,SLOT(checkCorrectInput()));
    socket->waitForDisconnected(50);
    Authorization *closeReg = new Authorization(socket);
    this->hide();
    closeReg->show();
}

void Registration::sockDisc()
{
    socket->disconnect();
}

Registration::~Registration()
{
    sockDisc();
    delete i;
    delete image;
}
