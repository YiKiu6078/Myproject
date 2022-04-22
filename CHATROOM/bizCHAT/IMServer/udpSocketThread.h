#ifndef UDPSOCKETTHREAD_H
#define UDPSOCKETTHREAD_H

#include <QThread>
#include <QUdpSocket>
#include <QDataStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QBuffer>

#define ALLCHAT_PORT 8888
#define UDP_SERVER_PORT 1234
#define UDP_CLIENT_PORT 2345

enum MsgType{
    LogIn,          //登录
    Invalid,        //无效
    RegisterUser,   //注册用户
    FriendInfo,     //好友信息
    GroupInfo,      //群组信息
    ChatMsg,        //个人聊天消息
    GroupChatMsg,   //群聊信息
    Leave,          //退出
    AddFriend,      //添加好友
    RemoveFried,    //删除好友
    AddGroup,       //加入群聊
    AgreeAddGroup,  //同意加入群聊
    ExitGroup,      //退出群聊
    FileHeader,     //文件头部信息
    FileInfo,       //文件信息
    AgreeLogin,     //同意登录
    AgreeRegister,  //同意注册
    AgreeAddFrd,    //同意添加好友
    AgreeRcvFile,   //同意接收文件
    FileSuccess,    //文件接收完成
    ImgOfGroupMbr,  //群聊用户头像信息
    Refuse          //拒绝
};

class udpSocketThread : public QThread
{
    Q_OBJECT
public:
    udpSocketThread(QObject *parent=nullptr);
    void run();
    void sendUdpMsg(QByteArray data);          //向服务器发送udp消息
    QString userId;
    QString clientIp;
    int portToClient;

signals:
    void ChatMsgSignal(QString,QString,QString);
    void memberOfGroupImg(QString,QString);

private:
    QUdpSocket *udpSocket;
    QList<QUdpSocket* >udpSocketList;

private slots:
    void rcvUdpMsgFromClient();
};

#endif // UDPSOCKETTHREAD_H
