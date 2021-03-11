#include "authorization.h"

Authorization::Authorization(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowTitle("Авторизация");
    this->setWindowIcon(QIcon("image/window.png"));
    this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    AuthorizationView();

    //loginEdit = login;

    socket = new QTcpSocket(this);
    socket->connectToHost("104.154.224.15",49002);
    connect(socket,SIGNAL(readyRead()),this,SLOT(checkTheEnteredData()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

void Authorization::enableSignInButton(QString text)
{
    signInButton->setEnabled(!loginEdit->text().isEmpty() && !passwordEdit->text().isEmpty());
}

void Authorization::signInButtonPressed()
{
    /*
    QByteArray login = QByteArray::fromStdString(loginEdit->text().toStdString());
    QByteArray password = QByteArray::fromStdString(passwordEdit->text().toStdString());
    QByteArray str = "{\"globalType\":\"connection\",\"type\":\"authorization\",\"login\":\""+login+"\",\"password\":\""+password+"\"}\r\n\r\n";
    */
    char str[100];
    std::string login = loginEdit->text().toStdString();
    std::string password = passwordEdit->text().toStdString();
    std::string str2 = "{\"globalType\":\"connection\",\"type\":\"authorization\",\"login\":\""+login+"\",\"password\":\""+password+"\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
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
