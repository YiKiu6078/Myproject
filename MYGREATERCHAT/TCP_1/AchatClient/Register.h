#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTcpSocket>
#include <QtNetwork>

#define ALLCHAT_PORT 8888
//消息类型
enum MsgType{
    LogIn,          //登录
    Invalid,        //无效
    RegisterUser,   //注册用户
    FriendInfo,     //好友信息
    GroupInfo,      //群组信息
    ChatMsg,        //聊天消息
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

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

    void sendMessgae(QByteArray data);          //向服务器发送消息

public slots:
    void tcpConnectedToServer();
    void tcpDisConnected();
    void tcpReadyRead();

private slots:
    void showConfirmCreateUserBtn();
    void showCancelCreateUserBtn();
    void showOpenImgFileBtn();
private:
    Ui::Register *ui;
    QLabel *IdLabel=new QLabel("用户ID：*");
    QLineEdit *IdLineEdit=new QLineEdit;
    QLabel *passwordLabel=new QLabel("密码：*");
    QLineEdit *passwordLineEdit=new QLineEdit;
    QLabel *paswdAgainLabel=new QLabel("确认密码: *");
    QLineEdit *paswdAgainLineEdit=new QLineEdit;
    QLabel *nickNameLabel=new QLabel("昵称：*");
    QLineEdit *nickNameLineEdit=new QLineEdit;
    QLabel *signatureLabel=new QLabel("个性签名：");
    QLineEdit *signatureLineEdit=new QLineEdit;
    QLabel *ageLabel=new QLabel("年龄：");
    QLineEdit *ageLineEdit=new QLineEdit;
    QLabel *sexLabel=new QLabel("性别：");
    QComboBox *sexComBox=new QComboBox;
    QLabel *emailLabel=new QLabel("电子邮件");
    QLineEdit *emailLineEdit=new QLineEdit;
    QPushButton *headImgBtn=new QPushButton("选择头像");
    QLineEdit *headImgPathLineEdit=new QLineEdit;
    QPushButton *confirmBtn=new QPushButton("确认");
    QPushButton *cancelBtn=new QPushButton("取消");

    QTcpSocket *RegisterTcpsocket;
};

#endif // REGISTER_H
