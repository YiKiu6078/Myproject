/*****************************************************
 Copyright (c), 2009-2019, 林勇
 文件名:							MasterControl.h
 作者:							林勇
 版本号:							版本1
 完成日期:					    2009/12/13
 修改日期:
 修改列表:
 ******************************************************/

#ifndef MASTERCONTROL_H_
#define MASTERCONTROL_H_

#include <QObject>
#include <QUdpSocket>
#include <QSqlDatabase>
#include "User.h"
#include "shareData.h"
#include "chat_drawer.h"
#include "ftpclientdialog.h"

/*******************************************************
 类名:                           MasterControl
 功能:                           主要控制整个程序的流程
 *******************************************************/

class MasterControl : public QObject
{
    Q_OBJECT

public:

	MasterControl(QObject *parent = 0);                                    //默认构造函数初始化资源
	virtual ~MasterControl();                                              //序析构函数释放资源
    bool initUserInfo();                                                   //初始化个人信息
    void sendPersonalInfo(int action = LOGIN);                             //发送个人资料
    void sendPersonalInfo(const User &toUser);                             //发送个人资料给特定某个人
    void showWindow();                                                     //展示主题窗口
    void parseMsg(MSG msg, const QByteArray &byteArray, QString ipAddress = NULL); //解析数据
    ToolButton * getButton(const QString &ipAddress);                      //根据ip地址得到用户按钮
    bool getIsRight() const;                                               //获得判断初始化变量是否正确变量
    bool isExit(const User user) const;                                    //判断是否该按钮已经存在

public slots:

    void dataReceived();                                                   //接收数据库报文
    void reOutLogin(const User &user);                                     //重新登录
    void outLogin();                                                       //退出登录的时候
    void acceptFile(const QString &fileName);                              //发送接收文件消息
    void refuseFile(const QString &fileName);                              //发送拒绝接受文件消息
    void revThread();													   //回收线程资源

private:

    User user;                                                             //本地个人用户
    bool isRight;                                                          //判断初始化环境是否正确
    ChatDrawer *draw;                                                      //画图显示
    QUdpSocket *udpSocket;                                                 //Udp通信
    ftpClientDialog *ftpClient;                                            //接收文件客户端
    TcpThread *sendFileThread;                                              //发送文件线程
};

#endif /* MASTERCONTROL_H_ */
