#include "ImuSocket.h"

ImuSocket_Task::ImuSocket_Task() {
    //端口号
    port = 1024;
    //初始化DLL
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockServer == INVALID_SOCKET)
    {
        std::cout<<"Failed Server socket() \n";
    }
    //向服务器发起请求
    memset(&addrServer, 0, sizeof(addrServer));  //每个字节都用0填充
    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrServer.sin_port = htons(port);
    if(bind(sockServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR))== SOCKET_ERROR)
        std::cout << "Failed Server bind() \n";
    listen(sockServer, 1);//监控连接数:1
}

ImuSocket_Task::~ImuSocket_Task()
{
    //关闭套接字
    closesocket(sockServer);
    closesocket(sockClient);
    //终止使用 DLL
    WSACleanup();
}

//会阻塞进程，直到有客户端连接上来为止
bool ImuSocket_Task::ImuAccept()
{
    int len = sizeof(SOCKADDR);
    const char *HelloStr = "You are already connect server!";
    sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &len);
    if (sockClient == INVALID_SOCKET)
        std::cout<<"Failed Client accept()"<<std::endl;
    else
        ImuSend(HelloStr, strlen(HelloStr));
    return true;
}

//向客户端发送信息
bool ImuSocket_Task::ImuSend(const char* buf, int len)
{
    send(sockClient, buf, len, NULL);
    return true;
}

//接受客户端返回的字符串
char* ImuSocket_Task::ImuReceive()
{
    char recvBuf[MAXBYTE];
    recv(sockClient, recvBuf, MAXBYTE, NULL);
    return recvBuf;
}
