#ifndef SERVER_H
#define SERVER_H

#endif // SERVER_H
#include<QObject>
#include<QTcpServer>
#include"TcpClientSocket.h"
class Server:public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parents=0,int port=0);
    QList<TcpClientSocket*>TcpClientSocketList;
signals:
    void updateServer(QString,int);
public slots:
    void updateClients(QString,int);
    void slotDisconnect(int);
//    void slotnewconnection();
   protected:
    void incomingConnection(int socketDescriptor);
};
