#include <iostream>
#include <authorization.h>
#include <QApplication>
using namespace std;

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);

    QTcpSocket *socket = new QTcpSocket();
    socket->connectToHost("104.154.224.15",49002);

    Authorization *game = new Authorization(socket);
    game->show();
    return app.exec();
}
