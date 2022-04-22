#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QDialog>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTreeWidget>
#include <QMessageBox>
#include <QImageReader>
#include <QColorDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMediaPlayer>
#include "AddFrdDlg.h"
#include "Register.h"
#include "ChatRoom.h"
#include "PersonInfo.h"

#define UDP_SERVER_PORT 1234
#define UDP_PORT2 2345
#define MAX_FRDGROUP_COUNT 10       //好友分组上限
#define CHATROOM_LEFT 1
#define CHATROOM_RIGHT 2

namespace Ui {
class FriendList;
}

class FriendList : public QDialog
{
    Q_OBJECT

public:
    explicit FriendList(QWidget *parent = nullptr);
    ~FriendList();

    void rcvPersonInfo(QString nickName,QString signature,QString age,
                           QString sex,QString email,QImage headImg,QStringList frdGroupList);
    void rcvNewFrd(QString rcvId,QString nickName,QImage headImg);
    void rcvNewGroup(QString,QString,QByteArray,QStringList);
    void rcvDeleteFrd(QString);
    QString sex,age,email;
    QStringList frdGroupList;

    QVector<QString> frdIdVector;
    QVector<QString> frdNickNameVctr;
    QVector<QImage> frdHeadImgVector;
    QVector<QString> groupIdVector;
    QVector<QString> groupNickNameVctr;
    QVector<QImage> groupHeadImgVector;
    QVector<QStringList> memberOfGroupVctr;
    QVector<QString> groupMemberIdVtr;
    QVector<QImage> groupMemberImgVtr;

    QTcpSocket *m_tcpSocket;
    QString userId;
    int clientPort;
    QImage userHeadImg;
    void sendTcpMsg(QByteArray data);          //向服务器发送tcp消息
    void sendUdpMsg(QByteArray data);          //向服务器发送udp消息
    void initFrdGroupList();                   //初始化好友分组
    void initFrdGroupInfo(QString,QString,QString,QByteArray);
    void initGroupList(QString,QString,QByteArray,QStringList);


private:
    Ui::FriendList *ui;
    QMenu *m_ContextMenu;
    ChatRoom *chatRoom;
    PersonInfo *personInfo;
    QFile *sendFile;
    qint64 totalFileSize=0;               //文件大小
    qint64 writtenSize=0;                 //已发送大小
    qint64 tobeWrtieSize=0;               //待发送大小
    qint64 payloadSize=64*1024;

    QFile file;                           //文件对象
    QString fileName;                     //文件名字
    qint64 fileSize;                      //文件大小
    qint64 sendSize;                      //已经发送文件大小

    QTimer timer;
    QByteArray sendData;
    QSqlDatabase database;
    QSqlQuery* sqlQuery;
    QUdpSocket *m_udpSocket;
    QListWidget *chatListWidget;
    QListWidget *groupListWidget;
    QTreeWidget *frdTreeWdgt;
    QTreeWidgetItem *treeFrdGroupItem[MAX_FRDGROUP_COUNT];
    QWidget *chatWidget=new QWidget;
    QWidget *contactsWidget=new QWidget;
    QWidget *groupWidget=new QWidget;
    QString getIp();
    QString makeColorString(const QColor &, const QString);

    //鼠标拖动窗口
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //记录窗口当前的位置
    QPoint StartPos;

    void playAudio();               //有消息到到来时播放系统提示音
    void addChatUser(QString,QImage);           //增加会话列表

signals:
    void rcvFileCompeteSignal(int);

private slots:
    void showPersonInfo();                          //展示个人信息
    void disconnectToServer();                      //服务器断开链接
    void slotChatBtnClicked();                      //会话按钮
    void slotContBtnClicked();                      //l联系人按钮
    void slotGroupBtnClicked();                     //群组按钮
    void showChatRoom(QTreeWidgetItem*,int);
    void showChatRoom(QListWidgetItem*);            //展示聊天界面
    void showGroupChatRoom(QListWidgetItem*);       //群聊聊天室
    void showAddFrdBtn();                           //添加好友
    void showAddGroupBtn();
    void showColorThemeBtn();                       //颜色背景
    void showImgThemeBtn();                         //图片背景
    void showMoveFrdSlot();                         //移动分组
    void showDeleteFrdSlot();                       //删除好友
    void udpReadyRead();                            //读取UDP消息
    void rcvAddUserId(QString);            //接收从添加好友对话框传过来的ID信息
    void rcvAddGroupId(QString);
    void rcvMsgFromChatRoom(QString,QString);        //接收从聊天室传来的消息
    void on_closeBtn_clicked();
    void on_minBtn_clicked();
    void on_searchLineEdit_textChanged(const QString &str);

    void rcvFileCompeteSlot(int);          //服务器发来的文件接收完成消息
    void showTreeWidgetMenuSlot(QPoint);
};

#endif // FRIENDLIST_H
