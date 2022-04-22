#include"Server.h"
#include<QDebug>
Server::Server(QObject *parent,int port):QTcpServer(parent)
{
    this->listen(QHostAddress::Any,port);
}
void Server::incomingConnection(int socketDescriptor)
{
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
    connect(tcpClientSocket,SIGNAL(updateClients(QString,int)),this,SLOT(updateClients(QString,int)));
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnect(int)));
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    TcpClientSocketList.append(tcpClientSocket);
}
void Server::updateClients(QString msg,int length)
{
    emit updateServer(msg,length);
    for (int i=0;i<TcpClientSocketList.count();i++)
    {
        QTcpSocket *item=TcpClientSocketList.at(i);
        if (item->write(msg.toLatin1(),length)!=length)
            continue;
    }
}
void Server::slotDisconnect(int socketDescriptor)
{
    for (int i=0;i<TcpClientSocketList.count();i++)
        if (TcpClientSocketList.at(i)->socketDescriptor()==socketDescriptor)
        {
            TcpClientSocketList.removeAt(i);
            return;
        }
}
