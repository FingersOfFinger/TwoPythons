#include "createlobby.h"

CreateLobby::CreateLobby(QTcpSocket *inSocket, QString login, QWidget *parent) :
    QWidget(parent)
{
    socket = inSocket;
    Login = login;

    char str[100];
    std::string str2 = "{\"globalType\":\"lobby\",\"type\":\"createLobby\"}\r\n\r\n";
    strcpy(str,str2.c_str());
    socket->write(str);
    socket->waitForBytesWritten(50);
}

CreateLobby ::~CreateLobby()
{

}
