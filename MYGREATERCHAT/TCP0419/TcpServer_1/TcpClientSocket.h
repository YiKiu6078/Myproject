#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#endif // TCPCLIENTSOCKET_H
#include<QObject>
#include<QTcpSocket>
class TcpClientSocket:public QTcpSocket
{
    Q_OBJECT
    public:
    TcpClientSocket(QObject *parent=0);
    signals:
        void updateClients(QString,int);
        void disconnected(int);
    protected slots:
        void dataReceive();
        void slotDisconnected();

};
