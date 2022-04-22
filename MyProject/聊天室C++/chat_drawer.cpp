#include <QSize>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "shareData.h"
#include "chat_drawer.h"

/************************************************************
 函数名:                             ChatDrawer
 功能:                               构造函数初始化图形显示界面
 ************************************************************/
ChatDrawer::ChatDrawer(QWidget *parent, Qt::WindowFlags f)
    : QToolBox(parent, f)
{
	setWindowTitle(QString::fromUtf8("凯凯聊天"));                                      //界面的标题

	if (!initGroup())                                                                 //初始化好友组
	{
		QMessageBox::information(0, QString::fromUtf8("错误"), QString::fromUtf8("初始化数据库失败!"));
	}

    creatGroup();                                                                     //创建好友组

    this->setMinimumSize(QSize(182,450));                                             //设置界面最小尺寸
	this->setMaximumSize(QSize(182,450));                                             //设置界面最大尺寸
}

/************************************************************
 函数名:                             initDatabase
 功能:                               初始化数据库
 返回值 TRUE:                         表示成功
      FALSE:                        表示失败
 ************************************************************/
bool ChatDrawer::initDatabase()
{
	QSqlDatabase globDB = QSqlDatabase::addDatabase(DRIVER, DATABASE_NAME);                //将加载数据库驱动以及连接名称
	globDB.setDatabaseName(DATABASE_NAME);                                    //设置数据库名
	if (!globDB.open())                                                       //打开数据库
	{
		QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("连接数据库失败!"));
		return false;
	}

	return true;                                                              //初始化数据库成功
}

/************************************************************
 函数名:                             initGroup
 功能:                               初始化好友组
 返回值 TRUE:                         表示成功
      FALSE:                        表示失败
 ************************************************************/
bool ChatDrawer::initGroup()
{
    if (!initDatabase())                                                       //初始化数据库
    {
    	return false;
    }

    QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
    QSqlQuery query(db);                                                   //创建查询结果集对象
    QString sql = "select *from wn_user_group";

    bool isRight = query.exec(sql);                                            //查询好友分组
    if (!isRight)
    {
    	return false;
    }

    while (query.next())
    {
    	groupName.append(query.value(1).toString());                           //添加好友分组组名
        QGroupBox * tmpGroup = new QGroupBox();                                //添加好友分组
        friendGroup.append(tmpGroup);
    }

    query.clear();

    return true;
}

/************************************************************
 函数名:                             creatGroup
 功能:                               创建好友组
 ************************************************************/
void ChatDrawer::creatGroup()
{
	QVBoxLayout *tmpLayout;
	QGroupBox *tmpGroup;

    for (int i=0; i<friendGroup.count(); i++)                                   //创建好友分组
    {
    	tmpGroup = friendGroup.at(i);
    	tmpLayout = new QVBoxLayout(tmpGroup);                                  //创建好友分组布局管理器
    	tmpLayout->setAlignment(Qt::AlignTop);

    	groupLayout.append(tmpLayout);
    	this->addItem((QWidget *)tmpGroup, groupName.at(i));                    //添加好友分组
    }
}

/************************************************************
 函数名:                             ~ChatDrawer
 功能:                               释放图形界面资源
 ************************************************************/
ChatDrawer::~ChatDrawer()
{
    for (int i=0; i<pButtonVector.count(); i++)                                        //释放在线用户按钮
    {
    	delete pButtonVector.at(i);
    }

    for (int i=0; i<friendGroup.count(); i++)                                          //释放好友分组
    {
    	delete friendGroup.at(i);
    }

    for (int i=0; i<groupLayout.count(); i++)
    {
    	delete groupLayout.at(i);
    }

}


/************************************************************
 函数名:                             updateInfo
 功能:                               个人信息被修改发送信号
 ************************************************************/
void ChatDrawer::updateInfo(const User &user)
{
	emit(update(user));                                                                //发送个人信息被修改信号
}

/************************************************************
 函数名:                               setUser
 功能:                                 设置本地当前用户
 输入参数 user:                         源用户信息
 ************************************************************/
void ChatDrawer::setUser(const User &user)
{
    this->user = user;
}

/************************************************************
 函数名:                             drawUserFace
 功能:                               绘出特定的用户按钮
 输入参数 newUser:                    将要绘制按钮的用户信息
 ************************************************************/
void ChatDrawer::drawUserFace(const User &newUser)
{
   QString info = newUser.getUserName();                                                  //获得用户名
   info += "\n" + newUser.getUserIp() +"\n" + newUser.getUserWrite();                    //获得IP于个性签名

	user_button = new ToolButton(user, newUser, groupName, this);                          //新建用户按钮
    user_button->setText(info);                                                            //设置按钮显示信息
	user_button->setIcon(QIcon(newUser.getUserHead()));                                    //设置头像
	user_button->setIconSize(QSize(40, 40));                                               //设置头像尺寸
    user_button->setAutoRaise(true);
    user_button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);                         //设置按钮的风格

	connect(user_button, SIGNAL(update(User)), this, SLOT(updateInfo(const User)));
	connect(user_button, SIGNAL(setAction(ToolButton *)), this, SLOT(setActionSlot(ToolButton *)));
	connect(user_button, SIGNAL(moveToOtherGroup(ToolButton *, int )), this, SLOT(moveFriend(ToolButton *, int)));
    connect(user_button, SIGNAL(insertGroupName(const QString)), this, SLOT(updateGroupName(const QString)));
    connect(user_button, SIGNAL(deleteGroupNameSignal(const QString)), this, SLOT(deleteGroupNameSlot(const QString)));
    connect(user_button, SIGNAL(updateGroupNameSignal(const QVector<QString>)), this, SLOT(updateGroupNameSlot(const QVector<QString>)));

    insertGroup(newUser, user_button);                                                     //将在线用户分组
	user_button->creatChildMenu();
    pButtonVector.append(user_button);                                                     //添加到在线用户容器中

    setFunction();                                                                         //设置当前用户发送文件按钮失效
}

/************************************************************
 函数名:                             updateGroupName
 功能:                               修改好友分组组名称
 输入参数 name:                       新增好友分组组名
 ************************************************************/
void ChatDrawer::updateGroupName(const QString name)
{
	groupName.append(name);                                                                //新组好友组名添加进容器

	for (int i=0; i<pButtonVector.count(); i++)                                            //修改每个按钮中的好友组名容器
	{
		pButtonVector.at(i)->setGroupName(groupName);
	}

    QGroupBox * tmpGroup = new QGroupBox();                                                //添加好友分组
    friendGroup.append(tmpGroup);

    QVBoxLayout *tmpLayout = new QVBoxLayout(tmpGroup);                                    //创建好友分组布局管理器
    tmpLayout->setAlignment(Qt::AlignTop);

    groupLayout.append(tmpLayout);                                                         //添加进布局管理器容器
    this->addItem((QWidget *)tmpGroup, name);                                              //添加好友分组                                                                          //重新创建好友分组框
}

void ChatDrawer::updateGroupNameSlot(const QVector<QString> groupName)
{
    int index = 0;

	for (int i=0; i<groupName.count(); i++)
	{
		if (this->groupName.at(i) != groupName.at(i))
		{
			index = i;
			break;
		}
	}

	this->groupName = groupName;
	this->setItemText(index, this->groupName.at(index));

	for (int i=0; i<pButtonVector.count(); i++)                                            //修改每个按钮中的好友组名容器
	{
		pButtonVector.at(i)->setGroupName(groupName);
	}
}

void ChatDrawer::deleteGroupNameSlot(const QString name)
{
	int index = groupName.indexOf(name);
	groupName.remove(index);

	for (int i=0; i<pButtonVector.count(); i++)                                            //修改每个按钮中的好友组名容器
	{
		ToolButton *tmpButton = pButtonVector.at(i);
		tmpButton->setGroupName(groupName);
		if (tmpButton->getGroupId() == index)
		{
			moveFriend(tmpButton, DEFAULT_GROUP_INDEX);
		}
	}

	friendGroup.remove(index);
	groupLayout.remove(index);
	this->removeItem(index);
}

/************************************************************
 函数名:                             queryGroup
 功能:                               查询用户所在组ID
 输入参数 tmpUser:                    用户对象
        tmpButton:                  用户按钮
 ************************************************************/
void ChatDrawer::insertGroup(const User &tmpUser, ToolButton *tmpButton)
{
	QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
    QSqlQuery query(db);                                                               //创建查询数据库对象
    QString sql = "select *from wn_user_ip where user_ip = '"+tmpUser.getUserIp()+"'";

    bool isRight = query.exec(sql);                                                        //查询数据库
    if (!isRight)
    {
    	QMessageBox::information(0, QString::fromUtf8("错误"), QString::fromUtf8("访问数据库失败!"));
    }

    if (query.first())                                                                     //当前存在分组记录
    {
    	int tmpId = query.value(1).toInt();
    	tmpButton->setGroupId(tmpId);                                                      //设置好友分组号
        groupLayout.at(tmpId)->addWidget((QWidget *)tmpButton);                            //添加好友按钮
    }
    else
    {
    	tmpButton->setGroupId(0);                                                          //默认分组
    	groupLayout.at(0)->addWidget((QWidget *)tmpButton);                                //采用默认分组记录
    }

    query.clear();
}

/************************************************************
 函数名:                             moveFriend
 功能:                               移动好友
 输入参数 friendButton:               用户按钮
        newGroupId:                 新组Id
 ************************************************************/
void ChatDrawer::moveFriend(ToolButton * friendButton, int newGroupId)
{
    for (int i=0; i<pButtonVector.count(); i++)                                             //查找将要移动按钮
	{
		if (friendButton == pButtonVector.at(i))
		{
		    friendButton->hide();                                                         //将要移动按钮隐藏
		    for (int j=0; j<groupLayout.count(); j++)
		    {
		    	if (friendButton->getGroupId() == j)                                      //找到移动的组号
		    	{
		    		groupLayout.at(j)->removeWidget(friendButton);                        //布局管理器中移除按钮
                    break;
		    	}
		    }

		    break;
		}
	}

	friendButton->setGroupId(newGroupId);                                                  //设置新组号
	friendButton->creatChildMenu();                                                        //创建新菜单
	groupLayout.at(newGroupId)->addWidget(friendButton);                                   //新组中添加按钮
	friendButton->show();
}

/************************************************************
 函数名:                             setActionSlot
 功能:                               设置按钮上下文菜单功能
 输入参数 userButton:                 用户按钮
 ************************************************************/
void ChatDrawer::setActionSlot(ToolButton *userButton)
{
	for (int i=0; i<pButtonVector.count(); i++)
	{
		if ((userButton == pButtonVector.at(i)) && i == 0)                                 //判断是否为当前用户按钮
		{
			userButton->setContextMenu(true);                                              //设置当前用户上下文菜单公能
            break;
		}
		else
		{
			userButton->setContextMenu(false);                                             //设置非当前用户上下文菜单功能
			break;
		}
	}
}

/************************************************************
 函数名:                             setFunction
 功能:                               设置当前用户上下文菜单功能
 ************************************************************/
void ChatDrawer::setFunction()
{
	if (!pButtonVector.isEmpty())
	{
		pButtonVector.at(0)->getChatWindow()->setSendFileButton(false);                    //将当前用户发送文件菜单失效
	}
}

/************************************************************
 函数名:                             removeUser
 功能:                               从在线用户容器中删除某个用户
 输入参数 user:                       将要删除的用户信息
 ************************************************************/
void ChatDrawer::removeUser(const User & user)
{
	if (!pButtonVector.isEmpty())                                                          //是否在线用户容器为空
	{
        ToolButton *tmpButton;                                                             //临时按钮
		for(int i=0; i <pButtonVector.count(); i++)                                        //检索在线用户容器
		{
			tmpButton = pButtonVector.at(i);                                               //获得用户按钮
			if (tmpButton->getUser() == user)                                              //匹配是否将要删除对象
			{
				tmpButton->hide();                                                         //隐藏按钮
				pButtonVector.remove(i);                                                   //从在线用户容器中删除
				break;
			}
		}
	}
}

/************************************************************
 函数名:                             removeAll
 功能:                               从在线用户容器中删除所有用户
 ************************************************************/
void ChatDrawer::removeAll()
{
	int count = pButtonVector.count();
	if (!pButtonVector.isEmpty())                                                          //是否在线用户容器为空
	{
		for(int i=0; i<count; i++)                                        //检索在线用户容器
		{
			pButtonVector.at(0)->hide();                                                   //将按钮从容器中删除
			pButtonVector.remove(0);
		}
	}
}

/************************************************************
 函数名:                             getVector
 功能:                               获得在线用户容器
 返回值:                             在线用户的容器
 ************************************************************/
const QVector<ToolButton *> & ChatDrawer::getVector() const
{
	return this->pButtonVector;                                                           //返回在线用户容器
}

/************************************************************
 函数名:                             getFriendGroup
 功能:                               获得好友分组容器
 返回值:                              好友分组容器
 ************************************************************/
QVector<QGroupBox *> & ChatDrawer::getFriendGroup()
{
	return this->friendGroup;                                                             //返回好友分组容器
}

