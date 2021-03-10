#include <iostream>
#include <Authorization.h>
#include <Lobby.h>
#include <QApplication>
using namespace std;

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    Authorization game;
    game.show();
    return app.exec();
}
