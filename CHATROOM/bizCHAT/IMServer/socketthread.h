#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QPixmap>
#include <QImageReader>
#include <QMessageBox>
#include <QDebug>
#include "udpSocketThread.h"

class SocketThread : public QThread
{
    Q_OBJECT
public:
    SocketThread(qintptr socketDescriptor,QObject *parent=nullptr);
    void run();
    void sendMessage(QByteArray data);

    QSqlQuery* sqlQuery;
    QBuffer buffer;
    QSqlDatabase database;
    int socketDescriptor;
    QString userId;
    QTcpSocket *tcpSocket;
    udpSocketThread *udpThread;

    QFile file;             //接收文件对象
    QFile sendFile;        //发送文件对象
    QString fileName;       //文件名字
    QString sendFileName;
    qint64 fileSize;        //文件大小
    qint64 recvSize = 0;        //已经接受文件大小
    qint64 countOfFilePack=0;
signals:
    void error(QTcpSocket::SocketError socketError);
    //更新用户状态
    void updateState(int,QString);
    //注册用户
    void addNewUser(QString, QString, QString, QString, QString);
    //传递添加好友消息
    void sendAddfrdToServer(QString,QString);
    //同意添加好友信号
    void sendAgreeAddFrd(QString,QString);
    //删除好友信号
    void sendDeleteFrdToServer(QString,QString);
    //传递添加群聊信息
    void sendAddGroupToServer(QString,QString);
    //将udp线程信息发送到主服务器上去
    void sendUdpSocketThread(udpSocketThread*);
    //将文件信息传递给接受者
    void sendFileHeadToRcv(QString,QString,QString,qint64);

private slots:
    void rcvTcpMsgFromClient();
    void rcvAddfrd(QString,QString);

private:
    void connectToDatabase();
    QTimer timer;
};

#endif // SOCKETTHREAD_H
