/*****************************************************
 Copyright (c), 2009-2019, 林勇
 文件名:							MasterControl.cpp
 作者:							林勇
 版本号:							版本1
 完成日期:					    2009/12/13
 修改日期:
 修改列表:
 ******************************************************/

#include <QtGui>
#include <QString>
#include <QSqlQuery>
#include "HostInfo.h"
#include "TcpThread.h"
#include "ToolButton.h"
#include "MasterControl.h"

/************************************************************
 函数名:                             MasterControl
 功能:                               初始化资源
 输入参数 pObject:                    默认参数父类构造函数的参数于子对象
             p:                    子对象参数
             f:                    自对象参数
 ************************************************************/
MasterControl::MasterControl(QObject *pObject)
                                 : QObject(pObject)
{
	isRight = true;

    udpSocket = new QUdpSocket;                                                    //创建UDPSocket
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));           //连接可读数据信号于处理槽函数

    bool result = udpSocket->bind(MSGPORT);                                        //帮定发送报文端口
    if(!result)
    {
        QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("绑定端口失败!"));
        isRight = false;
    }

    draw = new ChatDrawer;
    connect(draw, SIGNAL(update(User)), this, SLOT(reOutLogin(const User)));                          //连接用户修改个人信息然后重新登录

	ftpClient = new ftpClientDialog;                                                                  //客户端接收窗口
	connect(ftpClient, SIGNAL(acceptFile(const QString &)), this, SLOT(acceptFile(const QString &))); //连接用户接收文件请求于发送接受文件信息
	connect(ftpClient, SIGNAL(refuseFile(const QString &)), this, SLOT(refuseFile(const QString &))); //连接用户拒绝接受文件请求于发送拒绝接受文件信息
}

/************************************************************
 函数名:                             ~MasterControl
 功能:                               释放资源
 ************************************************************/
MasterControl::~MasterControl()
{
	delete udpSocket;
	delete ftpClient;
}

/************************************************************
 函数名:                             reOutLogin
 功能:                               修改信息后重新登录
 ************************************************************/
void MasterControl::reOutLogin(const User &user)
{
	sendPersonalInfo(OUT);
	draw->removeAll();                                                        //移除所有用户按钮
	this->user = user;
	sendPersonalInfo();                                                      //重新发送登录消息
}

/************************************************************
 函数名:                             getIsRight
 功能:                               获得判断初始化环境变量
 返回值 TRUE:                         表示成功
      FALSE:                        表示失败
 ************************************************************/
bool MasterControl::getIsRight() const
{
	return isRight;
}

/************************************************************
 函数名:                             initUserInfo
 功能:                               初始化个人信息
 返回值 true:                         初始化成功
      false:                        初始化失败
 ************************************************************/
bool MasterControl::initUserInfo()
{
	HostInfo hostInfo;                                                        //当前主机信息
   	if (!hostInfo.setLocalIp())                                               //根据主机信息设置IP
   	{
   		return false;
   	}

   	QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
    QSqlQuery query(db);
    bool isRight = query.exec(QString("select *from wn_user_info"));          //查询个人信息;
    if (!isRight)                                                             //查询失败
    {
    	QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("查询数据库失败!"));
    	return false;
    }

    if (!query.first())                                                       //是否已经存在数据
    {
	   	QString hostName = hostInfo.getHostName();                            //获得主机名
	   	QString localIp = hostInfo.getLocalIp();                              //获得当前IP
	   	isRight = query.exec("insert into wn_user_info(user_head, user_ip, user_host_name) "
	   			                  "values('"+DEFAULT_HEAD+"', '"+localIp+"','"+hostName+"')");     //插入个人信息
	   	if (!isRight)                                                         //插入失败
	   	{
	   	    QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("插入数据库失败!"));
	   	    return false;
	   	}

	   	user.setUserName(DEFAULT_USER_NAME);                                   //封装用户信息
	   	user.setUserIp(localIp);
	   	user.setUserHostName(hostName);
	   	user.setUserHead(DEFAULT_HEAD);
	 }
	 else                                                                      //个人信息存在直接读取
     {
        isRight = query.exec("update wn_user_info set user_ip = '"+hostInfo.getLocalIp()+ "' where id = 1");
        if (!isRight)
        {
        	QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("修改数据库失败!"));
        	return false;
        }

        isRight = query.exec("select *from wn_user_info");
        if (!isRight)
        {
        	QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("访问数据库失败!"));
        	return false;
        }

        query.first();
    	QString info;                                                          //封装个人信息
    	info = query.value(1).toString();
    	user.setUserName(info);
    	info = query.value(2).toString();
    	user.setUserHead(info);
    	info = query.value(3).toString();
    	user.setUserIp(info);
    	info = query.value(4).toString();
    	user.setUserHostName(info);
        info = query.value(5).toString();
    	user.setUserWrite(info);
    }

    query.clear();
    draw->setUser(user);
    return true;
}

/************************************************************
 函数名:                             sendPersonalInfo
 功能:                               广播发送个人信息
 输入参数  action:                     默认参数参数是LOGIN以登录方式
************************************************************/
void MasterControl::sendPersonalInfo(int action)
{
    MSG msg;                                                                      //通信协议结构体
    msg.headId = HEADID;                                                     //通信协议头
    msg.msgFlag = action;                                                     //通信类型标识

    QTextCodec *codec = QTextCodec::codecForName("utf8");     //转换编码
    QByteArray userName = codec->fromUnicode(user.getUserName());  //添加用户名
    msg.nameLen = userName.length();                                          //设置用户名长度

    msg.headLen = user.getUserHead().length();                        //设置用户头像长度

    QString hostName = codec->fromUnicode(user.getUserHostName());          //添加主机名
    msg.hostNameLen = hostName.length();                                   //设置用户主机名长度

    msg.IpLen = user.getUserIp().length();                                //设置用户IP地址长度

    QString userWrite = codec->fromUnicode(user.getUserWrite());                //添加个性签名
    msg.writeLen = userWrite.length();                                         //设置用户个人签名长度

    QByteArray byteArray;                                                       //设置发出报文
    byteArray.append((char *)&msg, sizeof (msg));                     //添加固定消息结构体

    byteArray.append(userName);
    byteArray.append(user.getUserHead());                               //添加头像
    byteArray.append(hostName);
    byteArray.append(user.getUserIp());                                    //添加IP
    byteArray.append(userWrite);

    HostInfo hostInfo;
    hostInfo.setLocalIp();

    QUdpSocket udpSocket;                                                       //建立UDPSocket
    int length = udpSocket.writeDatagram(byteArray, QHostAddress(hostInfo.getBroadcast()), MSGPORT);   //广播发送报文
    if (length != byteArray.size())                                             //发送失败
    {
    	QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("发送消息失败"));
    }
}

/************************************************************
 函数名:                             sendPersonalInfo
 功能:                               发送个人信息给特定某个人
 输入参数  toUser:                     将要发送的人的信息
************************************************************/
void MasterControl::sendPersonalInfo(const User &toUser)
{
    if (user != toUser)                                                             //是否是于本地当前用户相同
	{
	    MSG msg;                                                                    //通信协议结构体
	    msg.headId = HEADID;                                                        //通信协议头
	    msg.msgFlag = LOGIN;                                                        //通信类型标识

        QTextCodec *codec = QTextCodec::codecForName("utf8");     //转换编码
        QByteArray userName = codec->fromUnicode(user.getUserName());  //添加用户名
        msg.nameLen = userName.length();                                          //设置用户名长度

        msg.headLen = user.getUserHead().length();                        //设置用户头像长度

        QString hostName = codec->fromUnicode(user.getUserHostName());          //添加主机名
        msg.hostNameLen = hostName.length();                                   //设置用户主机名长度

        msg.IpLen = user.getUserIp().length();                                //设置用户IP地址长度

        QString userWrite = codec->fromUnicode(user.getUserWrite());                //添加个性签名
        msg.writeLen = userWrite.length();                                         //设置用户个人签名长度

        QByteArray byteArray;                                                       //设置发出报文
        byteArray.append((char *)&msg, sizeof (msg));                     //添加固定消息结构体

        byteArray.append(userName);
        byteArray.append(user.getUserHead());                               //添加头像
        byteArray.append(hostName);
        byteArray.append(user.getUserIp());                                    //添加IP
        byteArray.append(userWrite);

	    QUdpSocket udpSocket;
	    int length = udpSocket.writeDatagram(byteArray, QHostAddress(toUser.getUserIp()), MSGPORT); //发送报文
	    if (length != byteArray.size())                                             //发送失败
	    {
	    	QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("发送消息失败"));
	    }
	}
}

/************************************************************
 函数名:                            isExit
 功能:                              判断上线用户是否存在
 参数 user:                         上线用户
 返回值 true:                       表示存在
      false:                      表示不存在
************************************************************/
bool MasterControl::isExit(const User user) const
{
    QVector<ToolButton *> tmpVector = draw->getVector();                             //获得好友容器
    for (int i=0; i<tmpVector.count(); i++)
    {
        if (user == tmpVector.at(i)->getUser())                                     //判断该用户存在
        {
            return true;
        }
    }

    return false;
}

/************************************************************
 函数名:                             dataReceived
 功能:                               接收数据报文
************************************************************/
void MasterControl::dataReceived()
{
    while (udpSocket->hasPendingDatagrams())                                         //查看是否有数据报文可读
    {
    	int length = udpSocket->pendingDatagramSize();                               //报文的长度
    	if (length == -1)                                                            //出错
    	{
            QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("接收数据错误!"));
    	}
    	else
    	{
    		QByteArray byteArray;                                                    //流字节对象
    		byteArray.resize(length);
    		QHostAddress address;
            udpSocket->readDatagram(byteArray.data(), length, &address);             //读取数据库报文

            MSG msg;
            char *string = byteArray.left(sizeof(msg)).data();                       //解析出固定长度通信协议
            msg = *((MSG *)string);

            if (msg.headId == HEADID)                                                //通信协议相同
            {
                parseMsg(msg, byteArray, address.toString());                        //解析通信协议
            }
    	}
    }
}

/************************************************************
 函数名:                             showWindow
 功能:                               显示窗口
************************************************************/
void MasterControl::showWindow()
{
	QDesktopWidget desk;

	int width = desk.screenGeometry().width();                                       //获得显示器客户区的宽度
	int height = desk.screenGeometry().height();                                     //获得显示器客户区的高度

	draw->resize(180, 450);                                                           //设置显示尺寸
    draw->setGeometry(width-200, height-600, width-20, height-200);
	draw->show();                                                                     //显示窗口
}

/************************************************************
 函数名:                             outLogin
 功能:                               退出登录的时候调用该槽函数
************************************************************/
void MasterControl::outLogin()
{
    this->sendPersonalInfo(OUT);                                                         //广播当前用户退出消息
}

/************************************************************
 函数名:                             parseMsg
 功能:                               解析个人信息
 输入参数  msg:                        通信协议
        ByteArray:                  读取的数据报文
************************************************************/
void MasterControl::parseMsg(MSG msg, const QByteArray &byteArray, QString ipAddress)
{
    switch(msg.msgFlag)                                                                 //根据信息标识解释起作用
    {
    case LOGIN:                                                                         //登录信息
    {
         int sum = 0;
         sum += sizeof (msg);                                                           //固定长度的信息

         User tmpUser;
         QTextCodec *codec = QTextCodec::codecForName("utf8");

         QString tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.nameLen).data());     //获得消息
         tmpUser.setUserName(tmpMsg);                                                   //设置临时用户名
         sum += msg.nameLen;

         tmpMsg.clear();
         tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.headLen).data());
         tmpUser.setUserHead(tmpMsg);                                                   //设置临时用户头像长度
         sum += msg.headLen;

         tmpMsg.clear();
         tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.hostNameLen).data());
         tmpUser.setUserHostName(tmpMsg);
         sum += msg.hostNameLen;                                                       //设置临时用户主机名

         tmpMsg.clear();
         tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.IpLen).data());
         tmpUser.setUserIp(tmpMsg);                                                   //设置临时用户IP地址
         sum += msg.IpLen;

         tmpMsg.clear();
         tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.writeLen).data());
         tmpUser.setUserWrite(tmpMsg);                                                //设置临时用户个性签名
         sum += msg.writeLen;

         if (!isExit(tmpUser))
         {
             draw->drawUserFace(tmpUser);                                            //显示出用户界面
             this->sendPersonalInfo(tmpUser);                                        //发送个人信息给特定对象
         }

    	 break;
    }
    case OUT:                                                                        //退出信息标识
    {
         int sum = 0;
         sum += sizeof (msg);

         User tmpUser;
         QTextCodec *codec = QTextCodec::codecForName("utf8");

         QString tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.nameLen).data());  //获得消息
         tmpUser.setUserName(tmpMsg);                                                //设置临时用户名
         sum += msg.nameLen;

         tmpMsg.clear();
         tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.headLen).data());
         tmpUser.setUserHead(tmpMsg);                                                //设置临时用户头像长度
         sum += msg.headLen;

         tmpMsg.clear();
         tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.hostNameLen).data());
         tmpUser.setUserHostName(tmpMsg);
         sum += msg.hostNameLen;                                                     //设置临时用户主机名

         tmpMsg.clear();
         tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.IpLen).data());
         tmpUser.setUserIp(tmpMsg);                                                 //设置临时用户IP地址
         sum += msg.IpLen;

         tmpMsg.clear();
         tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.writeLen).data());
         tmpUser.setUserWrite(tmpMsg);                                             //设置临时用户个性签名
         sum += msg.writeLen;

         if (tmpUser != this->user)
         {
             draw->removeUser(tmpUser);                                           //删除对象
         }

    	 break;
    }
    case SENDMSG:                                                                //接收到发送的信息
    {
    	 int sum = 0;
    	 sum += sizeof (msg);

         QTextCodec *codec = QTextCodec::codecForName("utf8");
         QString tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.msgLen).data());    //获得消息

    	 ToolButton *tmpButton = getButton(ipAddress);                                //根据ip地址获得用户按钮
         if (tmpButton != NULL)                                                                //是否获得按钮句柄为空
    	 {
    		 ChatWindow *tmpWindow = tmpButton->getChatWindow();                      //获得聊天窗口句柄
             if (tmpWindow->isVisible())                                                                //聊天窗口是否显示
    		 {
    			 tmpWindow->message_show(tmpMsg, tmpButton->getUser().getUserName()); //显示聊天信息
    		 }
    		 else
    		 {
    			 tmpButton->getTimer()->start(600);                                   //触动时间触发器
    			 tmpWindow->message_show(tmpMsg, tmpButton->getUser().getUserName());
    		 }
    	 }

    	 break;
    }
    case SENDFILE:                                                                    //接收到发送的文件的信息
    {
    	 int sum = 0;
    	 sum += sizeof (msg);                                                         //计算固定通信协议结构体

         QTextCodec *codec = QTextCodec::codecForName("utf8");
         QString tmpMsg = codec->toUnicode(byteArray.mid(sum, msg.fileUrlLen).data());//获得服务器上文件绝对路径

    	 ftpClient->setServerAddress(ipAddress);                                      //设置服务器地址
    	 ftpClient->setFileName(tmpMsg);                                              //设置服务器文件绝对路径
    	 ftpClient->setFileSize(msg.fileSize);                                        //设置服务器文件的尺寸
    	 ftpClient->show();                                                           //显示接收文件对话框

    	 break;
    }
    case ACCEPTFILE:
    {
   	     ToolButton *tmpButton = getButton(ipAddress);                                 //根据ip地址获得用户按钮
   	     if (tmpButton != NULL)                                                        //是否获得按钮句柄为空
   	     {
   		     ChatWindow *tmpWindow = tmpButton->getChatWindow();                       //获得聊天窗口句柄
   		     const FtpServerDialog *fileDialog = tmpWindow->getFileDialog();           //获得发送文件窗口句柄

             sendFileThread = new TcpThread;
             connect(sendFileThread, SIGNAL(finishSend()), this, SLOT(revThread()));  //回收线程
             sendFileThread->setHostName(ipAddress);                                   //设置发送文件IP地址
             sendFileThread->setFileUrl(fileDialog->getUrl());                         //设置发送文件的URL
             sendFileThread->start();                                                  //开始运行线程
   	     }

    	break;
    }
    case REFUSEFILE:                                                                   //拒绝接受文件
    {
    	break;
    }
    default:
    {
    	break;
    }
    }
}

/************************************************************
 函数名:                             revThread
 功能:                               回收线程资源
 ************************************************************/
void MasterControl::revThread()
{
    sendFileThread->quit();																//停止线程
	wait();																				//回收线程资源
}

/************************************************************
 函数名:                             getButton
 功能:                               从在线用户容器中得到用户按钮
 返回值 NULL:                         表示不存在该在线用户
                                                                       成功时返回用户按钮
 ************************************************************/
ToolButton * MasterControl::getButton(const QString &ipAddress)
{
    const QVector<ToolButton *> &vector = draw->getVector();                            //获得在线用户容器
    ToolButton *tmp;

    for (int i=0; i<vector.count(); i++)                                               //循环查询
    {
    	tmp = vector.at(i);
    	if (tmp->getUser().getUserIp() == ipAddress)                                   //匹配ip
    	{
    		return tmp;                                                                //返回按钮指针
    	}
    }

    return NULL;                                                                       //没有匹配返回空
}

/************************************************************
 函数名:                              accpteFile
 功能:                                发送接受文件信息
 ************************************************************/
void MasterControl::acceptFile(const QString &fileName)
{
	MSG msg;                                                                            //接受文件消息

	msg.headId = HEADID;                                                                //通信协议头
	msg.msgFlag = ACCEPTFILE;                                                           //消息标识类型

	msg.fileUrlLen = fileName.length();

	QByteArray byteArray;                                                               //消息字节流
	byteArray.append((char *)&msg, sizeof (msg));                                       //添加固定消息结构体
    byteArray.append(fileName);                                                         //添加文件名

	QUdpSocket udpSocket;
	int length = udpSocket.writeDatagram(byteArray, QHostAddress(ftpClient->getServerAddress()), MSGPORT); //发送消息
	if (length != byteArray.length())                                                   //发送消息错误
	{
		QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("发送接受文件消息失败!"));
	}
}

/************************************************************
 函数名:                              accpteFile
 功能:                                发送接受文件信息
 ************************************************************/
void MasterControl::refuseFile(const QString &fileName)
{
    MSG msg;                                                                             //发送拒绝文件消息

    msg.headId = HEADID;                                                                 //通信协议头
    msg.msgFlag = REFUSEFILE;                                                            //消息类型

    msg.fileUrlLen = fileName.length();

    QByteArray byteArray;                                                                //消息字节流
    byteArray.append((char *)&msg, sizeof (msg));                                        //添加消息结构体
    byteArray.append(fileName);                                                          //添加文件名

    QUdpSocket udpSocket;
    int length = udpSocket.writeDatagram(byteArray, QHostAddress(ftpClient->getServerAddress()), MSGPORT); //发送消息
    if (length != byteArray.length())                                                    //发送消息出错
    {
    	QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("发送拒绝文件消息失败!"));
    }
}
