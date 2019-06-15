/**
* @file     ImuSocket.h
* @class    ImuSocket
* @brief    this file includes class(ImuSocket) used to convert data to python program.
* @author   Flame
* @date     13.04.2019
*/

#ifndef IMUSOCKET_H
#define IMUSOCKET_H

#include <winsock.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
class ImuSocket_Task
{

public:
    WSAData wsaData;
    SOCKET sockServer;
    SOCKADDR_IN addrServer;
    SOCKET sockClient;
    SOCKADDR_IN addrClient;
    int port;
    //#include<QtNetwork/QtNetwork>
    //QTcpServer *tcpServer;
    //QList<QTcpSocket*> tcpClient;
    //QTcpSocket *currentClient;
public:
    ImuSocket_Task();
    ~ImuSocket_Task();
    bool ImuAccept();
    bool ImuSend(const char* buf, int len);
    char* ImuReceive();
};

#endif // IMUSOCKET_H
