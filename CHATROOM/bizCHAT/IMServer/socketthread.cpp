#include "socketthread.h"

SocketThread::SocketThread(qintptr socketDescriptor,QObject *parent)
    :QThread (parent),socketDescriptor(socketDescriptor)
{
    connectToDatabase();
    sqlQuery=new QSqlQuery;
}

void SocketThread::run()
{
    tcpSocket=new QTcpSocket();
    if(!tcpSocket->setSocketDescriptor(socketDescriptor)){
        emit(tcpSocket->error());
        qDebug()<<"Set socketDescriptor fail！"<<endl;
        return;
    }
    if(!tcpSocket->waitForConnected(10000)){
        qDebug()<<"Connect Fail";
    }
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(rcvTcpMsgFromClient()),Qt::DirectConnection);
    tcpSocket->waitForReadyRead();
    exec();
}

//连接mysql数据库
void SocketThread::connectToDatabase()
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

//接收从客户端发来的消息
void SocketThread::rcvTcpMsgFromClient()
{
    int msgType;
    QByteArray sendData;
    QByteArray rcvData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    QString headImgPath;
    QDataStream in(tcpSocket);
    in>>msgType;
    QString rcvId,strInfo;
    switch (msgType)
    {
    case LogIn:
    {
        QString rcvPassword,clientIp;
        in>>rcvId>>rcvPassword>>clientIp;
        sqlQuery->prepare("select * from userGenerInfo where ID='"+rcvId+"'");
        sqlQuery->exec();
        //没有该账号
        if(!sqlQuery->next()){
            strInfo="该ID没有注册！";
            out<<Invalid<<strInfo;
            sendMessage(sendData);
            sendData.clear();
            out.device()->seek(0);
            tcpSocket->abort();
            return;
        }
        //密码错误
        if(sqlQuery->value(1).toString()!=rcvPassword){
            strInfo="输入的密码有误，请重试!";
            out<<Invalid<<strInfo;
            sendMessage(sendData);
            sendData.clear();
            out.device()->seek(0);
            tcpSocket->abort();
            return;
        }
        userId=rcvId;

        //开启udp接收线程
        udpThread=new udpSocketThread;
        udpThread->userId=userId;
        udpThread->clientIp=clientIp;
        udpThread->start();
        emit sendUdpSocketThread(udpThread);

        QString nickname=sqlQuery->value(2).toString(),
                signature=sqlQuery->value(3).toString(),
                age=sqlQuery->value(4).toString(),
                sex=sqlQuery->value(5).toString(),
                headImgPath=sqlQuery->value(6).toString(),
                groupInfo=sqlQuery->value(7).toString(),
                email=sqlQuery->value(8).toString();
        if(sqlQuery->value(6).toString()==""){
            headImgPath="/home/baixiaozhou/picture/0.jpg";
        }
        QPixmap(headImgPath).save(&buffer,"JPG");
        //将昵称，个性签名，年龄，性别，电子邮件，头像以及分组信息打包发送给客户端
        sqlQuery->prepare("select distinct 分组 from " + rcvId + "FriendList");
        sqlQuery->exec();
        QStringList strFrdList;
        while (sqlQuery->next()) {
            strFrdList<<sqlQuery->value(0).toString();
        }
        int clientPort=udpThread->portToClient;
        out<<AgreeLogin<<clientPort<<nickname<<signature<<age<<sex<<email<<buffer.data()<<strFrdList;
        sendMessage(sendData);
        out.device()->seek(0);
        sendData.clear();
        buffer.close();
        //向ui线程更新用户状态
        emit updateState(LogIn,rcvId);
        //同时向客户端发送对应的用户列表信息
        QVector<QStringList>frdList;
        sqlQuery->prepare("select * from " + rcvId + "FriendList");
        sqlQuery->exec();
        while (sqlQuery->next()) {
            QStringList strList;
            strList<<sqlQuery->value(0).toString()<<sqlQuery->value(1).toString();
            frdList.push_back(strList);
        }
        for(int i=0;i<frdList.size();++i){
            sqlQuery->prepare("select 昵称,头像存储位置 from userGenerInfo where ID='"+frdList[i].at(0)+"'");
            sqlQuery->exec();
            if(sqlQuery->first()){
                if(sqlQuery->value(1).toString()==""){
                    headImgPath="/home/baixiaozhou/picture/0.jpg";
                }else {
                    headImgPath=sqlQuery->value(1).toString();
                }
                QPixmap(headImgPath).save(&buffer,"JPG");
            }
            //将每一个好友的ID，昵称，头像，分组信息发送给客户端
            out<<FriendInfo<<frdList[i].at(0)<<frdList[i].at(1)<<sqlQuery->value(0).toString()
              <<buffer.data();
            sendMessage(sendData);
            usleep(150000);
            //回到字节流起始位置
            out.device()->seek(0);
            sendData.clear();
            buffer.close();
        }
        //向客户端发送群组信息
        QStringList groupList = groupInfo.split("#");
        QString groupNickName;
        for (int i = 0; i < groupList.size(); ++i) {
            if(groupList.at(i) != ""){
                sqlQuery->prepare("select * from userGroupList where ID=" + groupList.at(i));
                sqlQuery->exec();
                if(sqlQuery->first()){
                    if(sqlQuery->value(2).toString()==""){
                        headImgPath="/home/baixiaozhou/picture/0.jpg";
                    }else {
                        headImgPath=sqlQuery->value(2).toString();
                    }
                    QPixmap(headImgPath).save(&buffer,"JPG");
                    groupNickName = sqlQuery->value(1).toString();
                }
                //群聊成员
                QStringList memberOfGroupList;
                sqlQuery->prepare("select * from " + groupList.at(i) + "GroupUserList");
                sqlQuery->exec();
                while (sqlQuery->next()) {
                    memberOfGroupList<<sqlQuery->value(0).toString();
                }
                out<<GroupInfo<<groupList.at(i)<<groupNickName<<buffer.data()<<memberOfGroupList;
                sendMessage(sendData);
                usleep(150000);
                //回到字节流起始位置
                out.device()->seek(0);
                sendData.clear();
                buffer.close();
            }
        }
        break;
    }
    case RegisterUser:
    {
        QString rcvId,rcvPassword,rcvNickName,rcvSignature,rcvAge,rcvSex,rcvEmail;
        QByteArray ImgArray;
        in>>rcvId;
        sqlQuery->prepare("select * from userGenerInfo where ID='"+rcvId+"'");
        sqlQuery->exec();
        QString strInfo;
        if(sqlQuery->next()){
            strInfo="该ID已经被注册了，请不要重复注册";
            out<<Invalid<<strInfo;
            sendMessage(sendData);
            sendData.clear();
            out.device()->seek(0);
            tcpSocket->abort();
            return;
        }
        in>>rcvPassword>>rcvNickName>>rcvSignature>>rcvAge>>rcvSex>>rcvEmail>>ImgArray;
        QBuffer rcvImgBuffer(&ImgArray);
        QImageReader rcvReader(&rcvImgBuffer,"JPG");
        QImage rcvHeadImg=rcvReader.read();
        QString saveHeadImgPath="/home/baixiaozhou/picture/"+rcvId+".jpg";
        rcvHeadImg.save(saveHeadImgPath,"JPG");
        sqlQuery->prepare("insert into userGenerInfo(ID,密码,昵称,个性签名,年龄,性别,头像存储位置,电子邮件,创建时间) values(?,?,?,?,?,?,?,?,?)");
        sqlQuery->addBindValue(rcvId);
        sqlQuery->addBindValue(rcvPassword);
        sqlQuery->addBindValue(rcvNickName);
        sqlQuery->addBindValue(rcvSignature);
        sqlQuery->addBindValue(rcvAge);
        sqlQuery->addBindValue(rcvSex);
        sqlQuery->addBindValue(saveHeadImgPath);
        sqlQuery->addBindValue(rcvEmail);
        QDateTime currentDateTime =QDateTime::currentDateTime();
        sqlQuery->addBindValue(currentDateTime);
        if(!sqlQuery->exec()) {
            strInfo="注册用户失败，请重试！";
            out<<Invalid<<strInfo;
            sendMessage(sendData);
            sendData.clear();
            out.device()->seek(0);
            tcpSocket->abort();
            qDebug()<<"sqlQuery error :"<<sqlQuery->lastError();
        } else {
            strInfo="注册用户成功！";
            out<<AgreeRegister<<strInfo;
            sendMessage(sendData);
            sendData.clear();
            out.device()->seek(0);
            tcpSocket->abort();
        }
        emit addNewUser(rcvId,rcvNickName,rcvAge,rcvSex,rcvEmail);
        break;
    }
    case FriendInfo:
    {
        break;
    }
    case Leave:
    {
        in>>rcvId;
        //向ui线程更新用户状态 
        qDebug()<<"用户"<<rcvId<<"已下线"<<endl;
        emit updateState(Leave,rcvId);
        tcpSocket->abort();
        break;
    }
    case AddFriend:
    {
        QString rcvAddId;
        in>>rcvId>>rcvAddId;
        sqlQuery->exec("select * from userGenerInfo where ID='"+rcvAddId+"'");
        if(!sqlQuery->next()){
            strInfo="该用户还没有注册，请重新添加";
            out<<Invalid<<strInfo;
            sendMessage(sendData);
            sendData.clear();
            out.device()->seek(0);
            return;
        }
        emit sendAddfrdToServer(rcvId,rcvAddId);
        break;
    }
    case RemoveFried:{
        QString deleteId;
        in>>deleteId;
        sqlQuery->prepare("delete from " + userId + "FriendList where ID='" + deleteId + "'");
        if(!sqlQuery->exec()){
            qDebug()<<"Delete friend failed!"<<sqlQuery->lastError()<<endl;
        }

        sqlQuery->prepare("delete from " + deleteId + "FriendList where ID='" + userId + "'");
        if(!sqlQuery->exec()){
            qDebug()<<"Delete friend failed!"<<sqlQuery->lastError()<<endl;
        }
        emit sendDeleteFrdToServer(userId,deleteId);
        break;
    }
    case AddGroup:{
        QString rcvId,rcvGroupId;
        in>>rcvId>>rcvGroupId;
        qDebug()<<"用户ID:"<<rcvId<<"群聊Id:"<<rcvGroupId<<endl;
        sqlQuery->exec("select * from userGroupList where ID='"+rcvGroupId+"'");
        if(!sqlQuery->next()){
            strInfo="该群聊还没有创建，请重新添加";
            out<<Invalid<<strInfo;
            sendMessage(sendData);
            sendData.clear();
            out.device()->seek(0);
            return;
        }
        sqlQuery->prepare("insert into " + rcvGroupId + "GroupUserList(ID) values(?)");
        sqlQuery->addBindValue(rcvId);
        if(!sqlQuery->exec()) {
            qDebug()<<"Insert userId into group falied:"<<sqlQuery->lastError()<<endl;
        }
        sqlQuery->prepare("select 群组信息 from userGenerInfo where ID='" + rcvId +"'");
        QString newGroupInfo;
        if(!sqlQuery->exec()) {
            newGroupInfo = sqlQuery->value(0).toString() + rcvGroupId + "#";
        }
        sqlQuery->prepare("update userGenerInfo set 群组信息=:newGroupInfo where ID=:userId");
        sqlQuery->bindValue(":newGroupInfo",newGroupInfo);
        sqlQuery->bindValue(":userId",rcvId);
        if(!sqlQuery->exec()) {
            qDebug()<<"Update groupinfo into user falied:"<<sqlQuery->lastError()<<endl;
        }
        //将群组信息发送给用户
        sqlQuery->prepare("select * from userGroupList where ID=" + rcvGroupId);
        sqlQuery->exec();
        if(sqlQuery->value(2).toString()==""){
            headImgPath="/home/baixiaozhou/picture/0.jpg";
        }else {
            headImgPath=sqlQuery->value(2).toString();
        }
        QPixmap(headImgPath).save(&buffer,"JPG");
        QString groupNickName = sqlQuery->value(1).toString();
        //群聊成员
        QStringList memberOfGroupList;
        sqlQuery->prepare("select * from " + rcvGroupId + "GroupUserList");
        sqlQuery->exec();
        while (sqlQuery->next()) {
            memberOfGroupList<<sqlQuery->value(0).toString();
        }
        out<<AgreeAddGroup<<rcvGroupId<<groupNickName<<buffer.data()<<memberOfGroupList;
        sendMessage(sendData);
        //回到字节流起始位置
        out.device()->seek(0);
        sendData.clear();
        buffer.close();
        //emit sendAddGroupToServer(rcvId,rcvGroupId);
        break;
    }
    case FileHeader:{
        in>>rcvId>>fileName>>fileSize;
        file.setFileName(fileName);
        if (!file.open(QFile::WriteOnly)){
            qDebug() << "server: open file error!";
            return;
        }
        emit sendFileHeadToRcv(userId,rcvId,fileName,fileSize);
        break;
    }
    case FileInfo:
    {
        //取出接受的内容
        QByteArray buf;
        in>>buf;
        qint64 len = file.write(buf);
        if (len > 0){
            recvSize += len;
        }  
        if (recvSize == fileSize){
            out<<FileSuccess;
            sendMessage(sendData);
            sendData.clear();
            out.device()->seek(0);
            file.close();
            recvSize = 0;
        }
        break;
    }
    case AgreeAddFrd:
    {
        QString rcvAddId;
        in>>rcvId>>rcvAddId;
        QString selectStr="create table if not exists " + userId +"FriendList(ID varchar(8) not null, 分组 varchar(50), primary key(ID) );";
        sqlQuery->exec(selectStr);
        sqlQuery->prepare("insert into " + userId + "FriendList" +
                          "(ID,分组) values(?,?)");
        sqlQuery->addBindValue(rcvId);
        //默认添加到我的好友
        sqlQuery->addBindValue("我的好友");
        sqlQuery->exec();

        selectStr="create table if not exists " + rcvId +"FriendList(ID varchar(8) not null, 分组 varchar(50), primary key(ID) );";
        sqlQuery->exec(selectStr);
        sqlQuery->prepare("insert into " + rcvId + "FriendList" +
                          "(ID,分组) values(?,?)");
        sqlQuery->addBindValue(userId);
        //默认添加到我的好友
        sqlQuery->addBindValue("我的好友");
        sqlQuery->exec();
        //将同意添加好友的消息反馈给主线程，同时让主线程通知用户
        emit sendAgreeAddFrd(userId,rcvId);
        break;
    }
    case AgreeRcvFile:{
        qDebug()<<"同意接收文件"<<endl;
        QString sendFileName;
        qint64 sendfileSize;
        in>>sendFileName>>sendfileSize;
        qDebug()<<"文件名:"<<sendFileName<<"文件大小:"<<sendfileSize<<endl;
        sendFile.setFileName(sendFileName);
        if(!sendFile.open(QFile::ReadOnly)) {
            qDebug()<<"Open file failed!"<<sendFile.errorString()<<endl;
        }
        qint64 sendSize = 0;
        while (1) {
            QDataStream out(&sendData,QIODevice::WriteOnly);
            QByteArray fileInfo;
            fileInfo = sendFile.read(4096* 5);
            out<<FileInfo<<fileInfo;
            tcpSocket->write(sendData);
            tcpSocket->flush();
            usleep(50000);
            sendData.resize(0);
            sendSize += fileInfo.size();
            if(sendSize == sendfileSize) {
                return;
            }
        }
    }
    case FileSuccess:{
        sendFile.close();
        break;
    }
    default:{
        break;
    }
    }
}

//向客户端发消息
void SocketThread::sendMessage(QByteArray data)
{
    tcpSocket->write(data);
    tcpSocket->flush();
    tcpSocket->waitForBytesWritten();
}

void SocketThread::rcvAddfrd(QString rcvId,QString rcvAddId)
{
    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out<<AddFriend<<rcvId<<rcvAddId;
    sendMessage(sendData);
    out.device()->seek(0);
    sendData.clear();
}
