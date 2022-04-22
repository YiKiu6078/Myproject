/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							ToolButton.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#ifndef TOOLBUTTON_H_
#define TOOLBUTTON_H_

#include <QMenu>
#include <QUdpSocket>
#include <QToolButton>
#include <QMouseEvent>
#include "User.h"
#include "InfoDialog.h"
#include "chatwindow.h"
#include "NewGroupWnd.h"
#include "ManagerGroup.h"
#include "UpdateGroupWnd.h"

/*******************************************************
 类名:                           ToolButton
 功能:                           继承于QToolButton主要新建按钮
                                                               主要完成用户按钮的显示及相应操作
 自定义功能:                      有专属自己的信号与槽
 *******************************************************/

class ToolButton:public QToolButton
{
	Q_OBJECT

public:

	ToolButton(QWidget *parent = 0);                                         //构造函数
	ToolButton(const User &me, const User &user, QVector<QString> groupName, QWidget *parent = 0);//构造函数分配资源
    virtual ~ToolButton();                                                         //虚析构函数
	void setUser(const User &user);                                          //设置该按钮相应的用户信息
    const User & getUser();                                                     //获得用户信息
    QTimer * getTimer() const;                                                //获得时间触发器
	ChatWindow * getChatWindow() const;                                      //获得聊天句柄指针
	void setContextMenu(bool isLocal = false);                               //设置上下文菜单
	void setGroupId(int tmpId);                                              //设置用户好友分组号
	int getGroupId() const;                                                  //获得用户好友分组号
	void setGroupName(const QVector<QString> & tmpName);                     //设置好友组名
	void creatChildMenu();                                                   //创建子菜单
    void updateData(int newGroupId);                                         //修改本地数据库好友分组

protected:                                                                   //重写的两个鼠标响应

	virtual void mouseDoubleClickEvent(QMouseEvent * event);                 //响应按钮双击事件
    virtual void contextMenuEvent(QContextMenuEvent *event);                 //响应按钮右键单击菜单

signals:

    void update(User);                                                       //个人信息被修改
    void setAction(ToolButton *);                                            //查看该按钮是否是自己
    void moveToOtherGroup(ToolButton *, int);                                //将好友移动信号
    void insertGroupName(const QString);                                     //添加好友分组名
    void deleteGroupNameSignal(const QString);                               //删除好友分组名
    void updateGroupNameSignal(const QVector<QString>);                      //修改好友分组名容器

public slots:                                                                //自定义的槽函数

    void sendMsg();                                                          //发送消息菜单槽
	void sendFile();                                                         //发送文件菜单槽
	void updateGroupName(const QString);                                     //修改好友组名槽
	void updateUserInfo();                                                   //修改个人信息菜单槽
	void lookUserInfo();                                                     //查看个人信息菜单槽
	void addGroupInfo();                                                     //新建组信息菜单槽
	void manageGroupInfo();                                                  //管理组信息菜单槽
    void setUserSlot();                                                      //设置个人信息槽
    void moveToGroup(QAction *);                                             //将好友移动到另一个好友组
    void deleteGroupNameSlot(const QString);                                 //删除好友分组名
    void updateGroupNameSlot(const QVector<QString>);                        //修改好友分组名容器

private:

    User me;
	User user;                                                               //按钮相应的用户信息
	QMenu *menu;                                                             //用户 菜单
	QMenu *childMenu;                                                        //子菜单
	int groupId;                                                             //用户分组Id
	QTimer *timer;                                                           //按钮时间触发器
	ManagerGroup *managerGroup;                                              //管理好友组
	NewGroupWnd *newGroupWnd;                                                //新建好友组窗口
	ChatWindow *chatWindow;                                                  //聊天窗口
	InfoDialog *infoDialog;                                                  //个人消息对话框
	QVector<QString> groupName;                                              //好友分组组名容器
};

#endif /* TOOLBUTTON_H_ */
