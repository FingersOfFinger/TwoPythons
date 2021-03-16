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
    signal();
}

void Lobby::signal()
{
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
    QByteArray Data = socket->readAll();
    qDebug() << Data;
    QJsonParseError docError;
    QJsonDocument doc = QJsonDocument::fromJson(Data, &docError);

    if (docError.errorString() == "no error occurred")
    {
        //Start
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveStartLobby"))
        {
            disconnect(socket,SIGNAL(readyRead()),this,SLOT(receiveLobby()));
            socket->waitForDisconnected(50);

            GameWindow *openGame = new GameWindow(socket,login);
            this->hide();
            openGame->show();
        }
        //Stat
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveStatGame"))
        {
            listStat.clear();
            QJsonArray JsonlistStat = doc.object().value("userScore").toArray();
            QStandardItemModel *model = new QStandardItemModel(nullptr);
            model->setHorizontalHeaderLabels(QStringList()<<"Победитель"<<"Проигравший"<<"Счёт");

            for (int i=0; i<JsonlistStat.count(); i++)
            {
                listStat.append(new mStat(JsonlistStat[i].toObject().value("winner").toString(),JsonlistStat[i].toObject().value("loser").toString(),JsonlistStat[i].toObject().value("score").toString().toInt()));
            }
            for (int i=0; i<listStat.count(); i++)
            {
                QList<QStandardItem *> items;
                QStandardItem *winner = new QStandardItem(listStat[i]->winner);
                items.append(winner);
                QStandardItem *loser = new QStandardItem(listStat[i]->loser);
                items.append(loser);
                QStandardItem *score = new QStandardItem(listStat[i]->score);
                qDebug() << listStat[i]->score;
                items.append(score);
                model->appendRow(items);
            }
            ui->tableView->setModel(model);
        }
        //Enter
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveEnterLobby") && (doc.object().value("access").toString() == "true"))
        {
            QMessageBox::information(this,"Информация","Вы вошли в лобби!");
        }
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveEnterLobby") && (doc.object().value("access").toString() == "false"))
        {
            QMessageBox::critical(this, "Информация","Вы уже состоите в лобби!");
        }
        //Get
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveGetLobby"))
        {
            listLobby.clear();
            QJsonArray JsonlistLobby = doc.object().value("lobby").toArray();
            QStandardItemModel *model = new QStandardItemModel(nullptr);

            model->setHorizontalHeaderLabels(QStringList()<<"Название"<<"Создатель");
            for (int i=0; i<JsonlistLobby.count(); i++)
            {
                listLobby.append(new mLobby(JsonlistLobby[i].toObject().value("id").toString().toLongLong(),JsonlistLobby[i].toObject().value("name").toString(),JsonlistLobby[i].toObject().value("owner").toString()));
            }

            for (int i=0; i<listLobby.count(); i++)
            {
                QList<QStandardItem *> items;
                QStandardItem *name = new QStandardItem(listLobby[i]->name);
                items.append(name);
                QStandardItem *owner = new QStandardItem(listLobby[i]->owner);
                items.append(owner);
                model->appendRow(items);
            }
            ui->tableView->setModel(model);
        }
        //Exit
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveExitLobby") && (doc.object().value("access").toString() == "true"))
        {
           QMessageBox::information(this,"Информация","Вы вышли из лобби!");
        }
        if ((doc.object().value("globalType").toString() == "lobby") && (doc.object().value("type").toString() == "receiveExitLobby") && (doc.object().value("access").toString() == "false"))
        {
            QMessageBox::critical(this, "Информация","Вы не состоите в лобби!");
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

    if (id_number != -1)
    {
        std::string id = std::to_string(listLobby[id_number]->id);

        char request[100];
        std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"startGame\",\"id\":\""+id+"\"}\r\n";
        strcpy(request,request2.c_str());
        socket->write(request);
        socket->waitForBytesWritten(50);
    }
    else
    {
        QMessageBox::critical(this,"Информация","Лобби не выделено!");
    }
}

void Lobby::statGame()
{
    char request[100];
    std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"getStatGame\",\"login\":\""+login.toStdString()+"\"}\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);
}

void Lobby::deleteLobby()
{
    int id_number = ui->tableView->selectionModel()->currentIndex().row();

    if (id_number != -1)
    {
        QString name = listLobby[id_number]->name;
        std::string id = std::to_string(listLobby[id_number]->id);

        disconnect(socket,SIGNAL(readyRead()),this,SLOT(receiveLobby()));
        socket->waitForDisconnected(50);
        DeleteLobby *openDeleteLobby = new DeleteLobby(socket,id,name,login);
        this->hide();
        openDeleteLobby->show();
    }
    else
    {
        QMessageBox::critical(this,"Информация","Лобби не выделено!");
    }
}

void Lobby::exitLobby()
{
    int id_number = ui->tableView->selectionModel()->currentIndex().row();

    if (id_number != -1)
    {
        std::string id = std::to_string(listLobby[id_number]->id);

        char request[100];
        std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"exitLobby\",\"id\":\""+id+"\"}\r\n";
        strcpy(request,request2.c_str());
        socket->write(request);
        socket->waitForBytesWritten(50);
    }
    else
    {
        QMessageBox::critical(this,"Информация","Лобби не выделено!");
    }
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
    int id_number = ui->tableView->selectionModel()->currentIndex().row();

    if (id_number != -1)
    {
        std::string id = std::to_string(listLobby[id_number]->id);

        char request[100];
        std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"enterLobby\",\"id\":\""+id+"\"}\r\n";
        strcpy(request,request2.c_str());
        socket->write(request);
        socket->waitForBytesWritten(50);
    }
    else
    {
        QMessageBox::critical(this,"Информация","Лобби не выделено!");
    }
}

void Lobby::refreshLobby()
{
    char request[100];
    std::string request2 = "{\"globalType\":\"lobby\",\"type\":\"getLobby\"}\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);
    socket->waitForBytesWritten(50);
}

void Lobby::exit()
{
    disconnect(socket,SIGNAL(readyRead()),this,SLOT(receiveLobby()));
    socket->waitForDisconnected(50);
    Authorization *openAuth = new Authorization(socket);
    this->hide();
    openAuth->show();
}

void Lobby::sockDisc()
{
    socket->disconnect();
}

Lobby::~Lobby()
{
    sockDisc();
    delete ui;
}
