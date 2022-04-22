/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							ToolButton.cpp
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#include <QMenu>
#include <QtSql>
#include <QAction>
#include <QMessageBox>
#include "ToolButton.h"
#include "shareData.h"

/************************************************************
 函数名:                             ToolButton
 功能:                               初始化资源
 输入参数 parent:                     默认参数父类构造函数的参数
 ************************************************************/
ToolButton::ToolButton(QWidget *parent):QToolButton(parent)
{

}

/************************************************************
 函数名:                             ToolButton
 功能:                               初始化资源
 输入参数 parent:                     默认参数父类构造函数的参数
        User:                       传入用户信息与按钮绑定
 ************************************************************/
ToolButton::ToolButton(const User &me, const User &user, QVector<QString> groupName, QWidget *parent):QToolButton(parent)
{
	this->me = me;
	this->user = user;                                                            //初始化按钮相关的个人信息

	this->groupName = groupName;

	infoDialog = new InfoDialog(user, this);                                      //初始化个人信息对话框
    connect(infoDialog, SIGNAL(update()), this, SLOT(setUserSlot()));         //连接修改信号于个人信息槽

	chatWindow = new ChatWindow(this->me, this->user, this);

	timer = new QTimer(this);                                                     //初始化时间触发器
	connect(timer, SIGNAL(timeout()), this, SLOT(animateClick()));                //连接时间触发器于按钮跳动

	menu = new QMenu;                                                             //创建菜单
	childMenu = new QMenu(menu);

	QAction *action;

    action = menu->addAction(QString::fromUtf8("发送消息"));                        //发送消息菜单
    connect(action, SIGNAL(triggered()), this, SLOT(sendMsg()));                  //绑定信号与槽

    action = menu->addAction(QString::fromUtf8("发送文件"));                        //发送文件菜单
    connect(action, SIGNAL(triggered()), this, SLOT(sendFile()));                 //绑定信号与槽

    action = menu->addAction(QString::fromUtf8("修改个人信息"));                    //修改个人信息菜单
    connect(action, SIGNAL(triggered()), this, SLOT(updateUserInfo()));           //绑定信号与槽

    action = menu->addAction(QString::fromUtf8("查看个人信息"));                    //查看个人信息菜单
    connect(action, SIGNAL(triggered()), this, SLOT(lookUserInfo()));             //绑定信号与槽

    childMenu = menu->addMenu(QString::fromUtf8("将好友移动到..."));                //将好友移动到另外分组
    connect(childMenu, SIGNAL(triggered(QAction *)), this, SLOT(moveToGroup(QAction *)));

    action = menu->addAction(QString::fromUtf8("新建组"));                         //新建组菜单
    connect(action, SIGNAL(triggered()), this, SLOT(addGroupInfo()));             //绑定信号与槽

    action = menu->addAction(QString::fromUtf8("管理组"));                         //管理组菜单
    connect(action, SIGNAL(triggered()), this, SLOT(manageGroupInfo()));          //绑定信号与槽
    
    newGroupWnd = new NewGroupWnd(groupName, this);
    connect(newGroupWnd, SIGNAL(insertGroupName(const QString)), this, SLOT(updateGroupName(const QString)));   //连接添加好友组名信号与槽

    managerGroup = new ManagerGroup(this);
    managerGroup->setGroupName(groupName);
    managerGroup->setNewGroupWnd(newGroupWnd);

    connect(managerGroup, SIGNAL(deleteGroupName(const QString)), this, SLOT(deleteGroupNameSlot(const QString)));
    connect(managerGroup, SIGNAL(updateGroupNameSignal(const QVector<QString>)), this, SLOT(updateGroupNameSlot(const QVector<QString>)));
}

/************************************************************
 函数名:                             ~ToolButton
 功能:                               释放资源
 ************************************************************/
ToolButton::~ToolButton()
{
	delete menu;
	delete childMenu;
	delete timer;
	delete chatWindow;
    delete infoDialog;                                                            //释放个人信息对话框资源
    delete newGroupWnd;
    delete managerGroup;
}

/************************************************************
 函数名:                             setContextMenu
 功能:                               设置上下文菜单
 参数 isLocal TRUE:                   表示当前用户
             FALSE:                 表示在线用户
 ************************************************************/
void ToolButton::setContextMenu(bool isLocal)
{
	if (isLocal)                                                                  //表示当前用户
	{
		menu->actions().at(0)->setEnabled(false);                                 //不能给自己发送信息
		menu->actions().at(1)->setEnabled(false);                                 //将发送文件功能设置为无效
		menu->actions().at(3)->setEnabled(false);                                 //将查看个人信息设置为无效
		menu->actions().at(4)->setEnabled(false);                                 //不能移动自己
	}
	else
	{
		menu->actions().at(2)->setEnabled(false);                                 //将修改个人信息设置为无效
	}
}

/************************************************************
 函数名:                             setGroupId
 功能:                               设置当前登录好友分组号
 参数   groupId:                       好友分组号
 ************************************************************/
void ToolButton::setGroupId(int tmpId)
{
	this->groupId = tmpId;                                                        //设置好友分组号
}

/************************************************************
 函数名:                             updateGroupName
 功能:                               发送添加好友分组名称信号
 参数   name:                         新增好友组名称
 ************************************************************/
void ToolButton::updateGroupName(const QString name)
{
    emit(insertGroupName(name));                                                   //发送信号
    creatChildMenu();                                                              //重新创建菜单
    managerGroup->setGroupName(groupName);
}

void ToolButton::deleteGroupNameSlot(const QString name)
{
	emit(deleteGroupNameSignal(name));
	creatChildMenu();
    managerGroup->setGroupName(groupName);
}

void ToolButton::updateGroupNameSlot(const QVector<QString> groupName)
{
	emit(updateGroupNameSignal(groupName));
}

/************************************************************
 函数名:                             setGroupName
 功能:                               设置好友组
 参数   tmpName:                       好友组
 ************************************************************/
void ToolButton::setGroupName(const QVector<QString> & tmpName)
{
	this->groupName = tmpName;
	creatChildMenu();
}

/************************************************************
 函数名:                             creatChildMenu
 功能:                               创建子菜单
 ************************************************************/
void ToolButton::creatChildMenu()
{
    QAction *action;

    childMenu->clear();                                                              //将原来的菜单Action删掉
    for (int i=0; i<groupName.count(); i++)
    {
    	if (i != groupId)                                                            //不显示当前好友组
    	{
    	    action = childMenu->addAction(groupName.at(i));                          //显示有效移动好友组
    	}
    }
}

/************************************************************
 函数名:                             getGroupId
 功能:                               获得该好友组号
 ************************************************************/
int ToolButton::getGroupId() const
{
	return this->groupId;
}

/************************************************************
 函数名:                             moveToGroup
 功能:                               将好友移动到另一个好友组
 传入参数 action:                     将要移动到的菜单Action
 ************************************************************/
void ToolButton::moveToGroup(QAction * action)
{
    QString name = action->text();                                                   //获得被敲击菜单名称
    for (int i=0; i<groupName.count(); i++)
    {
    	if (name == groupName.at(i))                                                 //找到好友分组组号
    	{
    		updateData(i);                                                           //更新数据库
    		emit(moveToOtherGroup(this, i));                                         //发送移动好友信号
    		break;
    	}
    }
}

/************************************************************
 函数名:                             updateData
 功能:                               修改数据库中好友分组信息
 传入参数  newGroupId:                 新好友分组号
 ************************************************************/
void ToolButton::updateData(int newGroupId)
{
	QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
	QSqlQuery query(db);
	QString querySql = "select *from wn_user_ip where user_ip = '"+user.getUserIp()+"'";

	bool isRight = query.exec(querySql);
	if (!isRight)
	{
		QMessageBox::information(0, QString::fromUtf8("错误"), QString::fromUtf8("访问数据库失败!"));
	}
	else
	{
		if (query.first())
		{
			QString sql = "update wn_user_ip set user_group_id = '"+QString::number(newGroupId)+"'"
					                                       " where user_ip = '"+user.getUserIp()+"'";
			if (newGroupId == 0)
			{
				sql = "delete from wn_user_ip where user_ip = '"+user.getUserIp()+"'";
			}

			isRight = query.exec(sql);
			if (!isRight)
			{
				QMessageBox::information(0, QString::fromUtf8("错误"), QString::fromUtf8("修改数据库失败!"));
			}
		}
		else
		{
			QString sql = "insert into wn_user_ip(user_group_id, user_ip)"
					              " values('"+QString::number(newGroupId)+"', '"+user.getUserIp()+"')";
			bool isRight = query.exec(sql);
			if (!isRight)
			{
				QMessageBox::information(0, QString::fromUtf8("错误"), QString::fromUtf8("插入数据库失败!"));
			}
		}
	}

	query.clear();
}

/************************************************************
 函数名:                             mouseDoubleClickEvent
 功能:                               重写父类双击按钮功能
 输入参数  event:                      鼠标事件
 ************************************************************/
void ToolButton::mouseDoubleClickEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)                                        //判断是否是左键双击按钮
	{
		timer->stop();
        chatWindow->show();
	}
}

/************************************************************
 函数名:                             setUserSlot
 功能:                               设置个人信息槽函数
传入参数 user:                        被修改用户信息
 ************************************************************/
void ToolButton::setUserSlot()
{
    user = infoDialog->getUserInfo();                                          //从修改窗口中获得个人信息并设置
    emit(update(user));
}

/************************************************************
 函数名:                             contextMenuenuEvent
 功能:                               重写父类上下文菜单事件
 输入参数  event:                      鼠标事件
 ************************************************************/
void ToolButton::contextMenuEvent(QContextMenuEvent *event)
{
	if (event->reason() == QContextMenuEvent::Mouse)                              //判断是否是鼠标响应
	{
	    emit(setAction(this));                                                    //发送设置菜单信号

	    menu->show();                                                             //显示菜单
	    menu->exec(event->globalPos());                                           //上下文菜单显示
	}
}

/************************************************************
 函数名:                             setUser
 功能:                               设置按钮相关的个人信息
 输入参数  user:                       个人信息
 ************************************************************/
void ToolButton::setUser(const User &user)
{
	this->user = user;                                                            //设置按钮相关个人信息
}

/************************************************************
 函数名:                             sendMsg
 功能:                               发送消息菜单槽函数
 ************************************************************/
void ToolButton::sendMsg()
{
	timer->stop();                                                                //将按钮跳动时间停止
	chatWindow->show();                                                           //打开发送文件消息对话框
}

/************************************************************
 函数名:                             sendFile
 功能:                               发送文件菜单槽函数
 ************************************************************/
void ToolButton::sendFile()
{
	getChatWindow()->slotSendFile();
}

/************************************************************
 函数名:                             addGroupInfo
 功能:                               新建组菜单槽函数
 ************************************************************/
void ToolButton::addGroupInfo()
{
	newGroupWnd->show();
}

/************************************************************
 函数名:                             manageGroupInfo
 功能:                               管理组菜单槽函数
 ************************************************************/
void ToolButton::manageGroupInfo()
{
	managerGroup->show();
}

/************************************************************
 函数名:                              lookUserInfo
 功能:                               查看个人信息菜单槽函数
 ************************************************************/
void ToolButton::lookUserInfo()
{
	infoDialog->setWindowTitle(QString::fromUtf8("个人资料"));                      //显示 个人信息对话框
    infoDialog->resize(QSize(200, 200));                                          //设置显示尺寸
    infoDialog->setEnabled(false);
    infoDialog->show();
}

/************************************************************
 函数名:                             updateUserInfo
 功能:                               修改个人信息菜单槽函数
 ************************************************************/
void ToolButton::updateUserInfo()
{
	infoDialog->setWindowTitle(QString::fromUtf8("个人资料"));                      //显示 个人信息对话框
	infoDialog->resize(QSize(200, 200));                                          //设置显示尺寸
	infoDialog->show();
}

/************************************************************
 函数名:                             getUser
 功能:                               返回按钮个人信息
 ************************************************************/
const User & ToolButton::getUser()
{
	return this->user;
}

/************************************************************
 函数名:                             getTimer
 功能:                               返回时间触发器
 ************************************************************/
QTimer * ToolButton::getTimer() const
{
    return this->timer;
}

/************************************************************
 函数名:                             getChatWindown
 功能:                               返回聊天窗口句柄
 ************************************************************/
ChatWindow * ToolButton::getChatWindow() const
{
	return this->chatWindow;
}

