#include "lobby.h"
#include "ui_lobby.h"

Lobby::Lobby(QTcpSocket *inSocket, QString Login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lobby)
{
    ui->setupUi(this);

    socket = inSocket;
    login = Login;
    ui->Nickname->setText(login);

    connect(ui->Stat_game,SIGNAL(clicked()),this,SLOT(statGame()));
    connect(ui->Refresh_lobby,SIGNAL(clicked()),this,SLOT(refreshLobby()));
    connect(ui->Delete_lobby,SIGNAL(clicked()),this,SLOT(deleteLobby()));
    connect(ui->Exit_lobby,SIGNAL(clicked()),this,SLOT(exitLobby()));
    connect(ui->Create_lobby,SIGNAL(clicked()),this,SLOT(createLobby()));
    connect(ui->Enter_lobby,SIGNAL(clicked()),this,SLOT(enterLobby()));
    connect(ui->Start_game,SIGNAL(clicked()),this,SLOT(startGame()));
    connect(ui->Exit,SIGNAL(clicked()),this,SLOT(exit()));

    connect(socket,SIGNAL(readyRead()),this,SLOT(receiveLobby()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

void Lobby::receiveLobby()
{
    Data = socket->readAll();
    qDebug() << Data;
    doc = QJsonDocument::fromJson(Data, &docError);

    if (docError.errorString() == "no error occurred")
    {
        //Start
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveStartLobby") )
        {
            disconnect(socket,SIGNAL(readyRead()),this,SLOT(receiveLobby()));
            socket->waitForDisconnected(50);
            //
        }
        //Stat
        else if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveStatGame"))
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
                QStandardItem *score = new QStandardItem(docAr[i].toObject().value("score").toString());
                items.append(score);
                model->appendRow(items);
            }
            ui->tableView->setModel(model);
        }
        //Delete
        else if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveDeleteLobby") && (doc.object().value("access").toString() == "true"))
        {
            //
        }
        //Exit
        else if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveExitLobby") && (doc.object().value("access").toString() == "true"))
        {
           //
        }
        //Enter
        else if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveEnterLobby") && (doc.object().value("access").toString() == "true"))
        {
            //
        }
        //Get
        else if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveGetLobby"))
        {
            QJsonArray docAr = doc.object().value("lobby").toArray();
            QStandardItemModel *model = new QStandardItemModel(nullptr);
            QList<QStandardItem *> items;
            model->setHorizontalHeaderLabels(QStringList()<<"Id"<<"Название"<<"Создатель");
            for (int i=0; i<docAr.count(); i++)
            {
                QStandardItem *id = new QStandardItem(docAr[i].toObject().value("id").toString());
                items.append(id);
                QStandardItem *name = new QStandardItem(docAr[i].toObject().value("name").toString());
                items.append(name);
                QStandardItem *owner = new QStandardItem(docAr[i].toObject().value("owner").toString());
                items.append(owner);
                model->appendRow(items);
            }
            ui->tableView->setModel(model);
        }
        else
        {
            QMessageBox::information(this, "Информация","Не выбрано лобби!");
        }
    }
    else
    {
        QMessageBox::information(this, "Информация","Ошибка с форматом передачи данных: "+docError.errorString());
    }
}

void Lobby::startGame()
{
    int id_number = ui->tableView->selectionModel()->currentIndex().row();
    QJsonArray docAr = doc.object().value("lobby").toArray();
    std::string id = docAr[id_number].toObject().value("id").toString().toUtf8().constData();
    qDebug() << docAr[id_number].toObject().value("id").toString();
    char request[100];
    std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"startGame\",\"id\":\""+id+"\"}\r\n\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);
}

void Lobby::statGame()
{
    char request[100];
    std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"getStatGame\",\"login\":\""+login.toStdString()+"\"}\r\n\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);
}

void Lobby::deleteLobby()
{
    char request[100];
    std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"deleteLobby\"}\r\n\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);
}

void Lobby::exitLobby()
{
    char request[100];
    std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"exitLobby\"}\r\n\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);
}

void Lobby::createLobby()
{
    disconnect(socket,SIGNAL(readyRead()),this,SLOT(receiveLobby()));
    socket->waitForDisconnected(50);
    CreateLobby *openCreateLobby = new CreateLobby(socket,login);
    this->hide();
    openCreateLobby->show();
}

void Lobby::enterLobby()
{
    char request[100];
    std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"enterLobby\"}\r\n\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);
}

void Lobby::refreshLobby()
{
    char request[100];
    std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"getLobby\"}\r\n\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);
}

void Lobby::exit()
{
    this->hide();
}

void Lobby::sockDisc()
{
    socket->deleteLater();
}

Lobby::~Lobby()
{
    delete ui;
}
