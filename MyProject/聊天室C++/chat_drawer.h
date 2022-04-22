/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							chat_drawew.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#ifndef CHAT_DRAWER_H
#define CHAT_DRAWER_H

#include <QtGui>
#include <QVector>
#include <QByteArray>
#include <QUdpSocket>
#include <QSqlDatabase>
#include "User.h"
#include "ToolButton.h"
#include "ui_chat_drawer.h"

/*******************************************************
 类名:                           QToolBox
 功能:                           主要显示在线用户继承于QToolBox
 *******************************************************/

class ChatDrawer : public QToolBox
{
    Q_OBJECT

public:

    ChatDrawer(QWidget *parent = 0, Qt::WindowFlags flags = 0);                      //构造函数
    virtual ~ChatDrawer();                                                           //虚析构函数
    void setUser(const User &newUser);                                               //设置用户
    void drawUserFace(const User &newUser);                                          //显示用户
    bool initGroup();                                                                //初始化好友组
    bool initDatabase();                                                             //初始化数据库
    void creatGroup();                                                               //创建用户组
    void insertGroup(const User &tmpUser, ToolButton *tmpButton);                    //查询用户组
    void removeAll();                                                                //删除所有用户
    void removeUser(const User &user);                                               //移除用户
    void setFunction();                                                              //设置聊天窗口功能
    const QVector<ToolButton *> & getVector() const;                                 //获得当前在线用户容器
    QVector<QGroupBox *> & getFriendGroup();                                         //获得当前好友分组容器

signals:

    void update(User);                                                                //个人信息被修改信号

public slots:

    void updateInfo(const User &user);                                                //个人信息被修改槽
    void setActionSlot(ToolButton *userButton);                                       //设置每个按钮的菜单功能
    void moveFriend(ToolButton *, int);                                               //移动好友
    void updateGroupName(const QString);                                              //修该好友分组组名
    void deleteGroupNameSlot(const QString);                                          //删除好友分组组名
    void updateGroupNameSlot(const QVector<QString>);                                 //修改好友分组名容器

private:

    User user;                                                                       //当前用户

    ToolButton *user_button;                                                         //用户显示按钮                                                          //UdpSocket

    QVector<ToolButton *> pButtonVector;                                             //在线用户容器
    QVector<QGroupBox *> friendGroup;                                                //好友分组容器
    QVector<QVBoxLayout *> groupLayout;                                              //好友分组布局管理器容器
    QVector<QString> groupName;                                                      //好友分组组名容器
};

#endif // CHAT_DRAWER_H
