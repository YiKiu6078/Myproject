#include "logindlg.h"
#include "ui_logindlg.h"

loginDlg::loginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDlg)
{
    ui->setupUi(this);
    setWindowTitle(tr("AllChat"));
    this->setAutoFillBackground(true);
    this->setMaximumSize(300,300);    //设置背景图片
    setStyleSheet("QDialog#loginDlg{border-image:url(:/Img/picture/Back.jpg)}");
    //修改相对路径为exe目录路径
    QDir dir;
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    m_tcpsocket=new QTcpSocket(this);
    logInLabel=new QLabel(tr("登录AllChat:"));

    IdLabel=new QLabel(tr("用户ID"));
    IdLineEdit=new QLineEdit;
    QRegExp regx("[0-9]+$");
    QValidator *validator=new QRegExpValidator(regx,IdLineEdit);
    IdLineEdit->setValidator(validator);
    IdLineEdit->setMaxLength(8);
    pwdlabel=new QLabel(tr("密码"));
    pwdLineEdit=new QLineEdit;
    pwdLineEdit->setEchoMode(QLineEdit::Password);
    logInBtn=new QPushButton(tr("登录"));
    cancelBtn=new QPushButton(tr("取消"));
    enrolNewBtn=new QPushButton(tr("注册新用户"));

    buttonLayout=new QHBoxLayout;
    buttonLayout->addWidget(logInBtn);
    buttonLayout->addWidget(cancelBtn);
    mainLayout=new QGridLayout(this);
    mainLayout->setMargin(10);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(logInLabel,0,0);
    mainLayout->addWidget(IdLabel,1,0);
    mainLayout->addWidget(IdLineEdit,1,1);
    mainLayout->addWidget(pwdlabel,2,0);
    mainLayout->addWidget(pwdLineEdit,2,1);
    mainLayout->addLayout(buttonLayout,3,0,1,2);
    mainLayout->addWidget(enrolNewBtn,4,0,1,2);

    connect(logInBtn,SIGNAL(clicked()),this,SLOT(showLogInBtn()));
    connect(cancelBtn,SIGNAL(clicked()),this,SLOT(showCancelBtn()));
    connect(enrolNewBtn,SIGNAL(clicked()),this,SLOT(showRegsiterNewBtn()));

    //sqlQuery=new QSqlQuery;
}

//登录按钮槽函数
void loginDlg::showLogInBtn()
{
    if(IdLineEdit->text().length()!=8){
        QMessageBox::warning(this,tr("Warning"),
                             tr("帐号ID必须为8位，请重新输入！"),QMessageBox::Ok);
        return;
    }
    tcpConnectedToServer();
}

//向服务器发送消息
void loginDlg::sendMessgae(QByteArray data)
{
    if(m_tcpsocket->write(data) < 0){
        qDebug()<<"Send Message Failed!"<<endl;
    }
    m_tcpsocket->flush();
}

//tcp socket连接槽函数
void loginDlg::tcpConnectedToServer()
{  
    QDataStream out(&sendData,QIODevice::WriteOnly);
    m_tcpsocket->connectToHost(QHostAddress::LocalHost,ALLCHAT_PORT);
    if(!m_tcpsocket->waitForConnected(30000)){
        QMessageBox::information(this,"提示","无法连接到服务器");
        return;
    }
    //向服务器发送登录消息
    QString ip=getIp();
    out<<LogIn<<IdLineEdit->text()<<pwdLineEdit->text()<<ip;
    sendMessgae(sendData);
    out.device()->seek(0);
    sendData.clear();
    userId=IdLineEdit->text();
    connect(m_tcpsocket,SIGNAL(disconnected()),this,SLOT(tcpDisConnected()));
    connect(m_tcpsocket,SIGNAL(readyRead()),this,SLOT(tcpReadyRead()));
}

//tcp socket读取服务器发来的信息槽函数
void loginDlg::tcpReadyRead()
{
    QDataStream out(&sendData,QIODevice::WriteOnly);
    QDataStream in(m_tcpsocket);
    int msgType;
    in>>msgType;
    switch (msgType) {
    case Invalid:
    {
        QString info;
        in>>info;
        QMessageBox::information(this,"提示",info);
        return;
    }
    case AgreeLogin:
    {
        //获取年龄、性别、昵称，个性签名，电子邮件，头像以及分组信息
        QString nickname,signature,age,sex,email;
        QByteArray ImgArray;
        QStringList strFrdGroupList;
        in>>clientPort>>nickname>>signature>>age>>sex>>email>>ImgArray>>strFrdGroupList;
        QBuffer ImgBuffer(&ImgArray);
        QImageReader reader(&ImgBuffer,"JPG");
        QImage headImg=reader.read();
        frdlist=new FriendList;
        frdlist->clientPort=clientPort;
        frdlist->m_tcpSocket=m_tcpsocket;
        frdlist->userId=userId;
        frdlist->rcvPersonInfo(nickname,signature,age,sex,email,headImg,strFrdGroupList);  
        frdlist->show();
        connect(this,SIGNAL(disconnectToserver()),frdlist,SLOT(disconnectToServer()));
        connect(this,SIGNAL(rcvFileCompeteSignal(int)),frdlist,SLOT(rcvFileCompeteSlot(int)));
        this->minimumSize();
        this->close();
        //同时创建一个以ID号为目标的目录用于存放数据
        dataDir=QDir::currentPath()+"/"+IdLineEdit->text();
        QDir IdDir;
        if (!IdDir.exists(dataDir))
        {
            if(!IdDir.mkpath(dataDir)){
               qDebug()<<"目录创建失败："<<endl;
            }
        }
        dataDir=QDir::currentPath()+"/"+IdLineEdit->text() + "/File";
        QDir IdFileDir;
        if (!IdFileDir.exists(dataDir))
        {
            if(!IdFileDir.mkpath(dataDir)){
               qDebug()<<"目录创建失败："<<endl;
            }
        }

        if(QSqlDatabase::contains("qt_sql_default_connection")) {
            sqlLiteDb = QSqlDatabase::database("qt_sql_default_connection");
        }else {
            sqlLiteDb = QSqlDatabase::addDatabase("QSQLITE");
        }
        QString dataPath = QDir::currentPath() + "/" + userId +"/"
                + userId + ".db";
        sqlLiteDb.setDatabaseName(dataPath);
        if(!sqlLiteDb.open()) {
           qDebug() << "Open person database failed"<<endl;
        }
        sqlQuery=new QSqlQuery;
        break;
    }
    case FriendInfo:
    {
        QString frdId,frdGroup,frdNickname;
        QByteArray frdHeadImgArray;
        in>>frdId>>frdGroup>>frdNickname>>frdHeadImgArray;
        QString createStr="create table if not exists ChatMsgWith" + frdId
                + "(ID varchar(8) not null, 聊天消息 varchar(150), 时间 datetime not null);";
        sqlQuery->prepare(createStr);
        if(!sqlQuery->exec()){
            qDebug()<<"Create user's chat table failed:"<<sqlQuery->lastError()<<endl;
        }
        frdlist->initFrdGroupInfo(frdId,frdNickname,frdGroup,frdHeadImgArray);
        break;
    }
    case GroupInfo:
    {
        QString groupId,groupNickName;
        QStringList memberOfGroup;
        QByteArray groupHeadImgArray;
        in>>groupId>>groupNickName>>groupHeadImgArray>>memberOfGroup;
        QString createStr="create table if not exists ChatMsgWith" + groupId
                + "(ID varchar(8) not null, 聊天消息 varchar(150), 时间 datetime not null);";
        sqlQuery->prepare(createStr);
        if(!sqlQuery->exec()){
            qDebug()<<"Create user's chat table failed:"<<sqlQuery->lastError()<<endl;
        }
        frdlist->initGroupList(groupId,groupNickName,groupHeadImgArray,memberOfGroup);
        break;
    }
    case AddFriend:
    {
        QString rcvId;
        in>>rcvId;
        if(QMessageBox::question(this,tr("请求连接"),QString("%1  请求添加您为好友").arg(rcvId),
                                 QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes) {
            QString nickname,signature,age,sex,email;
            QByteArray ImgArray;
            in>>nickname>>signature>>age>>sex>>email>>ImgArray;
            QBuffer ImgBuffer(&ImgArray);
            QImageReader reader(&ImgBuffer,"JPG");
            QImage headImg=reader.read();
            frdlist->rcvNewFrd(rcvId,nickname,headImg);
            out<<AgreeAddFrd<<rcvId;
            sendMessgae(sendData);
            out.device()->seek(0);
            sendData.clear();
            //同时创建聊天数据表
            QString createStr="create table if not exists ChatMsgWith" + rcvId
                    + "(ID varchar(8) not null, 聊天消息 varchar(150), 时间 datetime not null);";
            sqlQuery->prepare(createStr);
            if(!sqlQuery->exec()){
                qDebug()<<"Create user's chat table failed:"<<sqlQuery->lastError()<<endl;
            }
        }
        break;
    }
    case RemoveFried:{
        QString deleteId;
        in>>deleteId;
        frdlist->rcvDeleteFrd(deleteId);
        break;
    }
    case AgreeAddGroup:{
        QString groupId,groupNickName;
        QStringList memberOfGroup;
        QByteArray groupHeadImgArray;
        in>>groupId>>groupNickName>>groupHeadImgArray>>memberOfGroup;
        QString createStr="create table if not exists ChatMsgWith" + groupId
                + "(ID varchar(8) not null, 聊天消息 varchar(150), 时间 datetime not null);";
        sqlQuery->prepare(createStr);
        if(!sqlQuery->exec()){
            qDebug()<<"Create user's chat table failed:"<<sqlQuery->lastError()<<endl;
        }
        frdlist->rcvNewGroup(groupId,groupNickName,groupHeadImgArray,memberOfGroup);
        break;
    }
    case FileHeader:
    {
        QString sendId,fileName;
        in>>sendId>>fileName>>fileSize;
        rcvFile=new QFile(userId + "/File/" + fileName);
        QString str = QString("用户 %1 向你发送了文件:[%2:%3kb],确定接收吗?").arg(sendId).arg(fileName).arg(fileSize/1024);
        if(QMessageBox::question(this, "提示",str,QMessageBox::Ok|QMessageBox::Cancel,
                              QMessageBox::Ok) == QMessageBox::Ok)
        {
            out<<AgreeRcvFile<<fileName<<fileSize;
            sendMessgae(sendData);
            out.device()->seek(0);
            sendData.clear();
            rcvFileDlg = new RcvFIleDlg;
            rcvFileDlg->show();
            rcvFileDlg->fileTotalSize = fileSize;
            rcvFileDlg->userId = userId;
            connect(this,SIGNAL(processSignal(qint64)),
                    rcvFileDlg,SLOT(processSlot(qint64)));
        }
        if(!rcvFile->open(QFile::WriteOnly)){
            qDebug()<<"Open receive file failed!"<<endl;
        }
        break;
    }
    case FileInfo:{
        //取出接受的内容
        QByteArray buf;
        in>>buf;
        qint64 len = rcvFile->write(buf);
        if (len > 0){
            recvSize += len;
            emit processSignal(recvSize);
        }
        if (recvSize == fileSize){
            out<<FileSuccess;
            sendMessgae(sendData);
            sendData.clear();
            out.device()->seek(0);
            rcvFile->close();
            recvSize = 0;
        }
        break;
    }
    case AgreeAddFrd:
    {
        QString rcvId,nickname,signature,age,sex,email;
        QByteArray ImgArray;
        in>>rcvId>>nickname>>signature>>age>>sex>>email>>ImgArray;
        QBuffer ImgBuffer(&ImgArray);
        QImageReader reader(&ImgBuffer,"JPG");
        QImage headImg=reader.read();
        frdlist->rcvNewFrd(rcvId,nickname,headImg);
        //同时创建聊天数据表
        QString createStr="create table if not exists ChatMsgWith" + rcvId
                + "(ID varchar(8) not null, 聊天消息 varchar(150), 时间 datetime not null);";
        sqlQuery->prepare(createStr);
        if(!sqlQuery->exec()){
            qDebug()<<"Create user's chat table failed:"<<sqlQuery->lastError()<<endl;
        }
        break;
    }
    case FileSuccess:{
        QMessageBox::information(nullptr, "提示", "文件传输完毕", QMessageBox::Ok);
        emit rcvFileCompeteSignal(FileSuccess);
        break;
    }
    default:
    {
        break;
    }
    }
}

//tcp socket断开连接槽函数
void loginDlg::tcpDisConnected()
{
    qDebug()<<"The server is disconnected!"<<endl;
    emit disconnectToserver();
}

//取消按钮槽函数
void loginDlg::showCancelBtn()
{
    this->close();
}

//注册按钮槽函数
void loginDlg::showRegsiterNewBtn()
{
    regstr=new Register;
    regstr->show();
}

//获取IP
QString loginDlg::getIp()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)   //我们使用IPv4地址
        {
            if(address.toString().contains("127.0."))
                continue;
            return address.toString();
        }
    }
    return nullptr;
}

loginDlg::~loginDlg()
{
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out<<Leave<<userId;
    sendMessgae(sendData);
    sendData.clear();
    m_tcpsocket->disconnect();
    delete ui;
}
