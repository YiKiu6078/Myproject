#include"TcpClientSocket.h"
#include<QDebug>
TcpClientSocket::TcpClientSocket(QObject *parent)
{

    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceive()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}
void TcpClientSocket::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}
void TcpClientSocket::dataReceive()
{
    qDebug()<<"QQWQW";
    while (bytesAvailable()>0)
    {
        int length=bytesAvailable();
        char buf[1024];
        read(buf,length);
        emit updateClients(QString(buf),length);
    }
}
