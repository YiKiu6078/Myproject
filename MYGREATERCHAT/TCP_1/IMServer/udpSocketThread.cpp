#include "udpSocketThread.h"

udpSocketThread::udpSocketThread(QObject *parent)
    :QThread (parent)
{

}

void udpSocketThread::run()
{
    udpSocket=new QUdpSocket;
   // QString ip = "127.0.0.1";//windows  ip地址
   // QHostAddress CliAddress(ip);
   // if(!udpSocket->bind(CliAddress,UDP_SERVER_PORT,QAbstractSocket::ShareAddress))
    if(!udpSocket->bind(QHostAddress::Any,UDP_SERVER_PORT,QAbstractSocket::ShareAddress))
    {
        qDebug()<<"Udp socket bind failed!"<<endl;
    }
    connect(udpSocket,SIGNAL(readyRead()),this,SLOT(rcvUdpMsgFromClient()),Qt::BlockingQueuedConnection);
    exec();
}

void udpSocketThread::rcvUdpMsgFromClient()
{
    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    QByteArray datagram;
    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(),datagram.size());//接收一个数据报，并将其存储在data中。返回的是数据报的长度
    //将读取到的不大于datagram.size()大小数据输入到datagram.data()中，datagram.data()返回的是一个字节数组中存储
    //数据位置的指针
    QDataStream in(&datagram,QIODevice::ReadOnly);
    int msgType;
    in >> msgType;
    switch (msgType) {
    case ChatMsg:
    {
        QString sendId,rcvId,chatInfo;
        in>>sendId>>rcvId>>chatInfo;
        emit ChatMsgSignal(sendId,rcvId,chatInfo);
        break;
    }
    case ImgOfGroupMbr:
    {
        QString memberId;
        in>>memberId;
        emit memberOfGroupImg(userId,memberId);
        break;
    }
    default:
        break;
    }
}

void udpSocketThread::sendUdpMsg(QByteArray data)
{
/*    if(udpSocket->writeDatagram(data,QHostAddress(clientIp),portToClient)<0)*/
    if(udpSocket->writeDatagram(data,QHostAddress::AnyIPv4,portToClient)<0){
        qDebug()<<"send udp message failed"<<endl;
    }
}


