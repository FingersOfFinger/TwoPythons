#include "gamewindow.h"

GameWindow::GameWindow(QTcpSocket *inSocket, QString Login)
{
    socket = inSocket;
    login = Login;

    setFocus();

    this->setWindowTitle("TwoPythons");
    this->setWindowIcon(QIcon("image/window.png"));
    resize(DOT_WIDTH*FILD_WIDTH+DOT_WIDTH*3,DOT_HIGHT*FILD_HIGHT);

    drowElements();

    connect(socket,SIGNAL(readyRead()),this,SLOT(sockConnect()));
    connect(buttExit, SIGNAL(clicked(bool)), this, SLOT(closeGame()));

    char request[100];
    std::string request2="{\"globalType\":\"connection\",\"type\":\"test\"}\r\n\r\n";
    strcpy(request,request2.c_str());
    socket->write(request);

    repaint();
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    std::string strCallback;
    char str[100];
    int key=event->key();
    switch (key) {
    case Qt::Key_Left:
        strCallback="{\"globalType\":\"game\",\"type\":\"setDirectionPython\",\"directionPython\":\"left\"}\r\n\r\n";
        break;
    case Qt::Key_Right:
        strCallback="{\"globalType\":\"game\",\"type\":\"setDirectionPython\",\"directionPython\":\"right\"}\r\n\r\n";
        break;
    case Qt::Key_Down:
         strCallback="{\"globalType\":\"game\",\"type\":\"setDirectionPython\",\"directionPython\":\"down\"}\r\n\r\n";
        break;
    case Qt::Key_Up:
        strCallback="{\"globalType\":\"game\",\"type\":\"setDirectionPython\",\"directionPython\":\"up\"}\r\n\r\n";
        break;
    }
    strcpy(str,strCallback.c_str());
    socket->write(str);
}


void GameWindow::paintEvent(QPaintEvent *event)
{
    drowWindow();
}

void GameWindow::drowArea()
{
    QPainter painter(this);
    painter.setBrush((QBrush(Qt::black, Qt::SolidPattern)));
    for(int i=1;i*DOT_WIDTH<=DOT_WIDTH*FILD_WIDTH;i++){
        painter.drawLine(i*DOT_WIDTH,0,i*DOT_WIDTH,FILD_HIGHT*DOT_HIGHT);
    }
    for(int i=1;i*DOT_HIGHT<=DOT_WIDTH*FILD_WIDTH;i++){
        painter.drawLine(0,i*DOT_HIGHT,FILD_HIGHT*DOT_HIGHT,i*DOT_HIGHT);
    }

    if(pythons.size()>1){
         painter.setBrush((QBrush(myColor,Qt::SolidPattern)));
         painter.drawEllipse(DOT_WIDTH*20.6,DOT_HIGHT*6,FILD_WIDTH*4,FILD_HIGHT*4);
    }
}

void GameWindow::drowElements()
{
    buttExit = new QPushButton("Выход",this);
    buttExit->setGeometry(QRect(QPoint(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH-DOT_WIDTH*4.5,DOT_HIGHT*FILD_HIGHT-DOT_HIGHT*2),QSize(DOT_WIDTH*2,DOT_HIGHT)));
    score = new QLabel(this);
    score->setGeometry(QRect(QPoint(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH-DOT_WIDTH*4.5,DOT_HIGHT),QSize(DOT_HIGHT*2,DOT_HIGHT)));
    score->setStyleSheet(QString("font-size: %1px").arg(DOT_HIGHT/2));;
    score->setText("Очки: 0");
    timer = new QLabel(this);
    timer->setGeometry(QRect(QPoint(DOT_WIDTH*FILD_WIDTH+10*FILD_WIDTH-DOT_WIDTH*4.9,DOT_HIGHT+DOT_HIGHT),QSize(DOT_HIGHT*3,DOT_HIGHT)));
    timer->setStyleSheet(QString("font-size: %1px").arg(DOT_HIGHT/2));;
    timer->setText("Время: 0:00");
    preparation=new QLabel(this);
    preparation->setGeometry(QRect(QPoint(DOT_WIDTH*FILD_WIDTH+12.5*FILD_WIDTH-DOT_WIDTH*4.9,DOT_HIGHT*4),QSize(DOT_HIGHT*2,DOT_HIGHT)));
    preparation->setStyleSheet(QString("font-size: %1px").arg(DOT_HIGHT));;
    preparation->setText("7");
}


void GameWindow::drowPythons()
{
    for(int i=0;i<pythons.size();i++){

        QPainter painter(this);
        QBrush brush;
        QColor color=pythons[i]->color;
        color.setAlpha(180);

        for(int j=0;j<pythons[i]->dots.size();j++){

            painter.setBrush(QBrush(pythons[i]->color));
            if(j==0)
            {
                painter.setBrush(QBrush(color));
            }
            painter.drawRect(QRect(DOT_HIGHT*pythons[i]->dots[j].rx(), DOT_WIDTH*pythons[i]->dots[j].ry(), DOT_WIDTH, DOT_HIGHT));
        }
    }
}

void GameWindow::drowFruits()
{
    QPainter painter(this);
    painter.setBrush((QBrush(Qt::green)));

    for(int i=0;i<fruits.size();i++)
    {
        painter.drawRect(QRect(DOT_HIGHT*fruits[i].rx(), DOT_WIDTH*fruits[i].ry(), DOT_WIDTH, DOT_HIGHT));
    }
}

void GameWindow::sockConnect()
{
    if(socket->waitForConnected(50))
    {
        data = QString(socket->readLine()).trimmed();

        doc=QJsonDocument::fromJson(data.toUtf8(),&docERR);
        QPoint teamp;

        if(docERR.errorString()=="no error occurred")
        {
            if(doc.object().value(("type")).toString()=="setDisplay"){
                QJsonArray docArPythons=doc.object().value("pythons").toArray();
                QJsonArray docArPythonCoords;
                QJsonArray docArPythonCoolor;
                QJsonArray docArMyPythonCoolor=doc.object().value("myColor").toArray();

                QJsonArray docArFruits=doc.object().value("coordinatesFruits").toArray();
                for(int i=0;i<docArPythons.count();i++){
                    docArPythonCoords=docArPythons[i].toObject().value("coordinates").toArray();
                    docArPythonCoolor=docArPythons[i].toObject().value("color").toArray();
                    Python *python=new Python();
                    for(int j=0;j< docArPythonCoords.count();j++){
                        teamp.rx()=docArPythonCoords[j].toObject().value("x").toString().toInt();
                        teamp.ry()=docArPythonCoords[j].toObject().value("y").toString().toInt();
                        python->dots.append(teamp);
                    }
                    python->color.setRgb(docArPythonCoolor[0].toString().toInt(),docArPythonCoolor[1].toString().toInt(),docArPythonCoolor[2].toString().toInt());
                    pythons.append(python);
                }
                for(int i=0;i<docArFruits.count();i++)
                {
                    teamp.rx()=docArFruits[i].toObject().value("x").toString().toInt();
                    teamp.ry()=docArFruits[i].toObject().value("y").toString().toInt();
                    fruits.append(teamp);
                }
                myColor.setRgb(docArMyPythonCoolor[0].toString().toInt(),docArMyPythonCoolor[1].toString().toInt(),docArMyPythonCoolor[2].toString().toInt());
                qDebug()<<docArMyPythonCoolor[0].toString();
            }
            if(doc.object().value(("type")).toString()=="prepareTimer")
            {
                preparation->setText(doc.object().value(("time")).toString());
                if(doc.object().value(("time")).toString().toInt()==0)
                {
                    preparation->setText("");
                    startGame=true;
                }
            }
            score->setText("Очки: "+doc.object().value("points").toString());
            repaint();
            if(startGame)
            {
                pythons.clear();
                fruits.clear();
            }
        }
    }
}

void GameWindow::closeGame()
{
    QMessageBox msg(QMessageBox::Question,tr("Выход"),tr("Вы действительно хотите выйти?"),QMessageBox::Yes | QMessageBox::No,this);
    msg.setButtonText(QMessageBox::Yes, tr("Да"));
    msg.setButtonText(QMessageBox::No, tr("Нет"));
    if (msg.exec() == QMessageBox::Yes)
    {
        disconnect(socket,SIGNAL(readyRead()),this,SLOT(sockConnect()));
        socket->waitForDisconnected(50);
        Lobby *closeLobby = new Lobby(socket,login);
        this->hide();
        closeLobby->show();
    }
}

void GameWindow::drowWindow()
{
    drowArea();
    drowFruits();
    drowPythons();
}
