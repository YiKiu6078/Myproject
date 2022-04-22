#include "socketserver.h"
#include "userui.h"

SocketServer::SocketServer(QObject *parent)
    :QTcpServer(parent)
{
    connectToDatabase();
    sqlQuery=new QSqlQuery;
    UDP_CLIENTPORT=8888 ;  //udp port
}

void SocketServer::incomingConnection(qintptr socketDescriptor)
{
    QThread *newThread;
    newThread=new QThread(this);
    thread=new SocketThread(socketDescriptor);//以socketDescriptor初始化线程
    thread->moveToThread(newThread);
    tcpThreadList.append(thread);
    connect(thread,SIGNAL(updateState(int,QString)),SLOT(rcvUpdateState(int,QString)));
    connect(thread,SIGNAL(addNewUser(QString,QString,QString,QString,QString)),
            this,SLOT(rcvRegisterNewUser(QString,QString,QString,QString,QString)));
    connect(thread,SIGNAL(sendAddfrdToServer(QString,QString)),
            SLOT(rcvAddFrd(QString,QString)));
    connect(thread,SIGNAL(sendAgreeAddFrd(QString,QString)),
            this,SLOT(AgreeAddFriend(QString,QString)));
    connect(this,SIGNAL(AddfrdSignal(QString,QString)),
            thread,SLOT(rcvAddfrd(QString,QString)));
    connect(thread,SIGNAL(sendDeleteFrdToServer(QString,QString)),
            this,SLOT(rcvDeleteFrd(QString,QString)));
    connect(thread,SIGNAL(sendUdpSocketThread(udpSocketThread*)),
            this,SLOT(RcvUdpThread(udpSocketThread*)));
    connect(thread,SIGNAL(sendFileHeadToRcv(QString,QString,QString,qint64)),
            this,SLOT(rcvFileHeadToRcv(QString,QString,QString,qint64)));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();
}

//更新用户状态
void SocketServer::rcvUpdateState(int msgType,QString userId)
{
    emit updateState(msgType,userId);
    if(msgType==Leave){
        for (int i = 0; i < tcpThreadList.size(); ++i) {
            if(userId == tcpThreadList.at(i)->userId){
                tcpThreadList.removeAt(i);
            }
        }
        for (int i = 0 ; i < udpThreadList.size(); ++i) {
            if(userId == udpThreadList.at(i)->userId){
                udpThreadList.removeAt(i);
            }
        }
    }
}

//注册用户
void SocketServer::rcvRegisterNewUser(QString Id,QString nickName,QString age,QString sex,QString email)
{
    emit addNewUser(Id,nickName,age,sex,email);
}

//连接数据库
void SocketServer::connectToDatabase()
{
    if(QSqlDatabase::contains("qt_sql_default_connection")){
      database = QSqlDatabase::database("qt_sql_default_connection");
    } else{
      database = QSqlDatabase::addDatabase("QMYSQL");
    }
    database.setUserName("root");
    database.setHostName("localhost");
    database.setPassword("1");
    database.setDatabaseName("IMSERVER");
    if(!database.open()){
        QMessageBox::critical(nullptr, QObject::tr("Databse Error"), database.lastError().text());
        qDebug()<<database.lastError()<<endl;
        qDebug()<<"Open mysql database failed！"<<endl;
    }
}

//接收到用户添加用户的信息
void SocketServer::rcvAddFrd(QString rcvId,QString rcvAddId)
{
    for(int i=0;i<tcpThreadList.size();++i){
        if(rcvAddId == tcpThreadList.at(i)->userId){
            sqlQuery->prepare("select * from UserInfo where ID='"+rcvId+"'");
            sqlQuery->exec();
            sqlQuery->first();
            QByteArray sendData;
            QDataStream out(&sendData,QIODevice::WriteOnly);
            QString nickname=sqlQuery->value(2).toString(),
                    signature=sqlQuery->value(3).toString(),
                    age=sqlQuery->value(4).toString(),
                    sex=sqlQuery->value(5).toString(),
                    headImgPath=sqlQuery->value(6).toString(),
                    email=sqlQuery->value(8).toString();
            if(sqlQuery->value(6).toString()==""){
                headImgPath="/home/yikiu/图片/0.jpg";
            }
            QBuffer buffer;
            QPixmap(headImgPath).save(&buffer,"JPG");
            out<<AddFriend<<rcvId<<nickname<<signature<<age<<sex<<email<<buffer.data();
            if(tcpThreadList.at(i)->tcpSocket->write(sendData)<0){
                qDebug()<<"Send message failed!"<<endl;
            }
            tcpThreadList.at(i)->tcpSocket->flush();
       }
    }
}

//同意添加用户
void SocketServer::AgreeAddFriend(QString Id,QString rcvId)
{
    for(int i = 0;i < tcpThreadList.size();++i){
        if(rcvId == tcpThreadList.at(i)->userId){
            sqlQuery->prepare("select * from UserInfo where ID='"+Id+"'");
            sqlQuery->exec();
            sqlQuery->first();
            QByteArray sendData;
            QDataStream out(&sendData,QIODevice::WriteOnly);
            QString nickname=sqlQuery->value(2).toString(),
                    signature=sqlQuery->value(3).toString(),
                    age=sqlQuery->value(4).toString(),
                    sex=sqlQuery->value(5).toString(),
                    headImgPath=sqlQuery->value(6).toString(),
                    email=sqlQuery->value(8).toString();
            if(sqlQuery->value(6).toString()==""){
                headImgPath="/home/yikiu/图片/0.jpg";
            }
            QBuffer buffer;
            QPixmap(headImgPath).save(&buffer,"JPG");
            out<<AgreeAddFrd<<Id<<nickname<<signature<<age<<sex<<email<<buffer.data();
            if(tcpThreadList.at(i)->tcpSocket->write(sendData)<0){
                qDebug()<<"Send message failed!"<<endl;
            }
            tcpThreadList.at(i)->tcpSocket->flush();
       }
    }
}

//删除用户
void SocketServer::rcvDeleteFrd(QString rcvId,QString deleteId)
{
    for(int i=0;i<tcpThreadList.size();++i){
        if(deleteId == tcpThreadList.at(i)->userId) {
            QByteArray sendData;
            QDataStream out(&sendData,QIODevice::WriteOnly);
            out<<RemoveFried<<rcvId;
            if(tcpThreadList.at(i)->tcpSocket->write(sendData)<0){
                qDebug()<<"Send message failed!"<<endl;
            }
            tcpThreadList.at(i)->tcpSocket->flush();
            sendData.clear();
            out.device()->seek(0);
        }
    }
}

//将udp线程放入主线程的list链表中
void SocketServer::RcvUdpThread(udpSocketThread *udpThread)
{
    if(udpThreadList.size() == 0) {
        udpThread->portToClient = UDP_CLIENTPORT++;
    }
    for (int i = 0;i < udpThreadList.size();++i) {
        if(udpThread->clientIp == udpThreadList.at(i)->clientIp){
            udpThread->portToClient = UDP_CLIENTPORT++;
        }else {
            udpThread->portToClient = UDP_CLIENTPORT;
        }
    }
    udpThreadList.append(udpThread);

    //触发发送聊天消息的信号和槽
    connect(udpThread,SIGNAL(ChatMsgSignal(QString,QString,QString)),
            this,SLOT(ChatMsgSlot(QString,QString,QString)));
    //触发群聊用户的id和头像信息
    connect(udpThread,SIGNAL(memberOfGroupImg(QString,QString)),
            this,SLOT(memberOfGroupImg(QString,QString)));
}

//处理群聊成员头像
void SocketServer::memberOfGroupImg(QString userId,QString memberId)
{
    sqlQuery->prepare("select HeadImgPath from UserInfo where ID='" + memberId + "'");
    sqlQuery->exec();
    QString headImgPath;
    QByteArray sendData;
    QBuffer buffer;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    while (sqlQuery->next()) {
        if(sqlQuery->value(0).toString()==""){
            headImgPath = "/home/yikiu/picture/0.jpg";
        } else {
            headImgPath = sqlQuery->value(0).toString();
        }
        QPixmap(headImgPath).save(&buffer,"JPG");
        out<<ImgOfGroupMbr<<memberId<<buffer.data();
        for (int i = 0; i < udpThreadList.size(); ++i) {
            if(udpThreadList.at(i)->userId == userId) {
                udpThreadList.at(i)->sendUdpMsg(sendData);
            }
        }
        out.device()->seek(0);
        sendData.clear();
        buffer.close();
    }
}

//接收到udp线程的聊天消息
void SocketServer::ChatMsgSlot(QString sendId,QString rcvId,QString chatInfo)
{
    if (rcvId.length() == 8) {
        //表示是发送给用户的消息
        for (int i = 0 ;i < udpThreadList.size(); ++i) {
            if(rcvId == udpThreadList.at(i)->userId){
                QByteArray chatMsgData;
                QDataStream out(&chatMsgData,QIODevice::WriteOnly);
                out<<ChatMsg<<sendId<<chatInfo;
                udpThreadList.at(i)->sendUdpMsg(chatMsgData);
            }
        }
    } else {
        //表示是群聊的消息
        QString str="select * from " + rcvId + "GroupUserList";
        sqlQuery->prepare(str);
        if(sqlQuery->exec())
        {
           //读取查询到的记录
           while(sqlQuery->next())
           {
               for (int i = 0 ;i < udpThreadList.size(); ++i) {
                   if((sqlQuery->value(0).toString() == udpThreadList.at(i)->userId) &&
                           (sqlQuery->value(0).toString() != sendId)){
                       QByteArray chatMsgData;
                       QDataStream out(&chatMsgData,QIODevice::WriteOnly);
                       out<<GroupChatMsg<<rcvId<<sendId<<chatInfo;
                       udpThreadList.at(i)->sendUdpMsg(chatMsgData);
                   }
               }
           }
        }
    }
}

//接收到文件信息
void SocketServer::rcvFileHeadToRcv(QString sendId,QString rcvId,QString fileName,qint64 fileSize)
{
    for (int i = 0; i < tcpThreadList.count(); ++i) {
        if(tcpThreadList.at(i)->userId == rcvId){
            QByteArray sendData;
            QDataStream out(&sendData,QIODevice::WriteOnly);
            out<<FileHeader<<sendId<<fileName<<fileSize;
            if(tcpThreadList.at(i)->tcpSocket->write(sendData) < 0){
                qDebug()<<"调用线程中socket失败"<<endl;
            }
            tcpThreadList.at(i)->tcpSocket->flush();
            sendData.clear();
            out.device()->seek(0);
        }
    }
}
