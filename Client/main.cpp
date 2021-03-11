#include <iostream>
#include <authorization.h>
#include <QApplication>
using namespace std;

int main(int argc,char *argv[])
{
    QApplication app(argc,argv);
    Authorization game;
    game.show();
    return app.exec();
}
