#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include<QTcpServer>
#include<QSqlDatabase>
#include<QMetaObject>
#include "socketthread.h"
#include "udpSocketThread.h"

#define UDP_SERVER_PORT 6666

class UserUI;
class SocketServer : public QTcpServer
{
    Q_OBJECT
public:
    SocketServer(QObject *parent=nullptr);
    int UDP_CLIENTPORT;
protected:
    virtual void incomingConnection(qintptr socketDescriptor);

signals:
    void updateState(int,QString);
    void addNewUser(QString,QString,QString,QString,QString);
    void AddfrdSignal(QString,QString);
    void sendChatMsgToRcver(QString,QString);

private slots:
    void rcvUpdateState(int,QString);
    void rcvRegisterNewUser(QString,QString,QString,QString,QString);
    void rcvAddFrd(QString,QString);
    void AgreeAddFriend(QString,QString);
    void rcvDeleteFrd(QString,QString);
    void RcvUdpThread(udpSocketThread*);
    void ChatMsgSlot(QString,QString,QString);
    void rcvFileHeadToRcv(QString,QString,QString,qint64);              //接收文件信息
    void memberOfGroupImg(QString,QString);             //群聊成员头像信息
private:
    UserUI *userUi;
    QSqlDatabase database;
    QSqlQuery* sqlQuery;
    void connectToDatabase();
    SocketThread *thread;
    QList<SocketThread*> tcpThreadList;
    QList<udpSocketThread *> udpThreadList;
};

#endif // SOCKETSERVER_H
