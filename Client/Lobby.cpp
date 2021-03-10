#include "Lobby.h"
#include "ui_Lobby.h"

Lobby::Lobby(QString login,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lobby)
{
    ui->setupUi(this);

    Login = login;
    ui->Nickname->setText(Login);

    connect(ui->Stat_game,SIGNAL(clicked()),this,SLOT(statGame()));
    connect(ui->Refresh_lobby,SIGNAL(clicked()),this,SLOT(refreshLobby()));
    connect(ui->Delete_lobby,SIGNAL(clicked()),this,SLOT(deleteLobby()));
    connect(ui->Exit_lobby,SIGNAL(clicked()),this,SLOT(exitLobby()));
    connect(ui->Create_lobby,SIGNAL(clicked()),this,SLOT(createLobby()));
    connect(ui->Enter_lobby,SIGNAL(clicked()),this,SLOT(enterLobby()));
    connect(ui->Start_game,SIGNAL(clicked()),this,SLOT(startGame()));
    connect(ui->Exit,SIGNAL(clicked()),this,SLOT(exit()));

    socket = new QTcpSocket(this);
    socket->connectToHost("104.154.224.15",49002);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockConnect()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    char str[100];
    std::string str2 = "{\"globalType\":\"connection\",\"type\":\"lobby\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
}

void Lobby::startGame()
{
    //,\"id\":\""+id.id().toInt()+"\"
    char str[100];
    std::string str2 = "{\"globalType\":\"lobby\",\"type\":\"startGame\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
    socket->waitForBytesWritten(50);

    if (receiveStartGame())
    {

    }
    else
    {
        QMessageBox::information(this, "Информация","Не выбрано лобби!");
    }
}

bool Lobby::receiveStartGame()
{
    Data = socket->readAll();
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);
    if (docError.errorString() == "no error occurred")
    {
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveStartLobby"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
        return false;
    }
}

void Lobby::statGame()
{
    char str[100];
    std::string str2 = "{\"globalType\":\"lobby\",\"type\":\"getStatGame\",\"login\":\""+Login.toStdString()+"\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
    socket->waitForBytesWritten(50);

    receiveStatGame();
}

void Lobby::receiveStatGame()
{
    Data = socket->readAll();
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);
    if (docError.errorString() == "no error occurred")
    {
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveStatGame"))
        {
            QStandardItemModel *model = new QStandardItemModel(nullptr);
            model->setHorizontalHeaderLabels(QStringList()<<"Победитель"<<"Проигравший"<<"Счёт");
            QList<QStandardItem *> items;

            QJsonArray docAr = doc.object().value("userScore").toArray();
            for (int i=0; i<docAr.count(); i++)
            {  
                QStandardItem *winner = new QStandardItem(docAr[i].toObject().value("winner").toString());
                items.append(winner);
                QStandardItem *loser = new QStandardItem(docAr[i].toObject().value("loser").toString());
                items.append(loser);
                QStandardItem *score = new QStandardItem(docAr[i].toObject().value("score").toInt());
                items.append(score);
                model->appendRow(items);
            }
            ui->tableView->setModel(model);
        }
        else
        {
            QMessageBox::information(this, "Информация","Список лобби пуст!");
        }
    }
    else
    {
        QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
    }
}

void Lobby::deleteLobby()
{
    char str[100];
    std::string str2 = "{\"globalType\":\"lobby\",\"type\":\"deleteLobby\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
    socket->waitForBytesWritten(50);

    if (receiveDeleteLobby())
    {

    }
    else
    {
        QMessageBox::information(this, "Информация","Не выбрано лобби!");
    }
}

bool Lobby::receiveDeleteLobby()
{
    Data = socket->readAll();
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);
    if (docError.errorString() == "no error occurred")
    {
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveDeleteLobby") && (doc.object().value("access").toString() == "true"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
        return false;
    }
}

void Lobby::exitLobby()
{
    char str[100];
    std::string str2 = "{\"globalType\":\"lobby\",\"type\":\"exitLobby\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
    socket->waitForBytesWritten(50);

    if (receiveExitLobby())
    {

    }
    else
    {
        QMessageBox::information(this, "Информация","Не выбрано лобби!");
    }
}

bool Lobby::receiveExitLobby()
{
    Data = socket->readAll();
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);
    if (docError.errorString() == "no error occurred")
    {
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveExitLobby") && (doc.object().value("access").toString() == "true"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
        return false;
    }
}

void Lobby::createLobby()
{
    char str[100];
    std::string str2 = "{\"globalType\":\"lobby\",\"type\":\"createLobby\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
    socket->waitForBytesWritten(50);

    if (receiveCreateLobby())
    {

    }
    else
    {
        QMessageBox::information(this, "Информация","Не выбрано лобби!");
    }
}

bool Lobby::receiveCreateLobby()
{
    Data = socket->readAll();
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);
    if (docError.errorString() == "no error occurred")
    {
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveCreateLobby") && (doc.object().value("access").toString() == "true"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
        return false;
    }
}

void Lobby::enterLobby()
{
    char str[100];
    std::string str2 = "{\"globalType\":\"lobby\",\"type\":\"enterLobby\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
    socket->waitForBytesWritten(50);

    if (receiveEnterLobby())
    {

    }
    else
    {
        QMessageBox::information(this, "Информация","Не выбрано лобби!");
    }
}

bool Lobby::receiveEnterLobby()
{
    Data = socket->readAll();
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);
    if (docError.errorString() == "no error occurred")
    {
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveEnterLobby") && (doc.object().value("access").toString() == "true"))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
        return false;
    }
}

void Lobby::refreshLobby()
{
    char str[100];
    std::string str2 = "{\"globalType\":\"lobby\",\"type\":\"getLobby\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
    socket->waitForBytesWritten(50);

    receiveGetLobby();
}

void Lobby::receiveGetLobby()
{
    Data = socket->readAll();
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);
    if (docError.errorString() == "no error occurred")
    {
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveGetLobby"))
        {
            QJsonArray docAr = doc.object().value("lobby").toArray();
            QStandardItemModel *model = new QStandardItemModel(nullptr);
            model->setHorizontalHeaderLabels(QStringList()<<"Id"<<"Name"<<"Owner");
            for (int i=0; i<docAr.count(); i++)
            {
                QStandardItem *id = new QStandardItem(docAr[i].toObject().value("id").toInt());
                model->appendRow(id);
                QStandardItem *name = new QStandardItem(docAr[i].toObject().value("name").toString());
                model->appendRow(name);
                QStandardItem *owner = new QStandardItem(docAr[i].toObject().value("owner").toString());
                model->appendRow(owner);
            }
            ui->tableView->setModel(model);
        }
        else
        {
            QMessageBox::information(this, "Информация","Список лобби пуст ");
        }
    }
    else
    {
        QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
    }
}

void Lobby::exit()
{
    this->hide();
}

void Lobby::sockConnect()
{
    if(socket->waitForConnected(50))
    {
        socket->waitForReadyRead(50);
    }
}

void Lobby::sockDisc()
{
    socket->deleteLater();
}

Lobby::~Lobby()
{
    delete ui;
}
