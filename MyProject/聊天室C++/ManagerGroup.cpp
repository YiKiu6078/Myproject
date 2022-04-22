/*****************************************************
 Copyright (c), 2009-2019, 林勇
 文件名:							ToolButton.h
 作者:							林勇
 版本号:							版本1
 完成日期:					    2009/4/3
 修改日期:
 修改列表:
 ******************************************************/

#include <QSqlQuery>
#include "shareData.h"
#include "ManagerGroup.h"

/************************************************************
 函数名:                             ManagerGroup
 功能:                               构造函数
 默认参数 parent:                     父类
        f:                          父类标志
 ************************************************************/
ManagerGroup::ManagerGroup(QWidget * parent, Qt::WindowFlags f)
                                             : QDialog(parent, f)
{
	setWindowTitle(QString::fromUtf8("管理好友组"));                                 //设置窗口标题

	creatModel();                                                                  //创建模型
	creatView();      															   //创建试图

	resize(400, 200);															   //设置大小
	this->setMaximumSize(400, 200);
	this->setMinimumSize(400, 200);

	newGroup = new QPushButton(QString::fromUtf8("新建组"));
	updateGroup = new QPushButton(QString::fromUtf8("修改组"));
	deleteGroupButton = new QPushButton(QString::fromUtf8("删除组"));
	canel = new QPushButton(QString::fromUtf8("退出"));

	connect(canel, SIGNAL(clicked()), this, SLOT(close()));
	connect(updateGroup, SIGNAL(clicked()), this, SLOT(selectUpdateGroup()));
	connect(deleteGroupButton, SIGNAL(clicked()), this, SLOT(deleteGroup()));
	connect(newGroup, SIGNAL(clicked()), this, SLOT(insertGroup()));

	buttonLayout = new QVBoxLayout;
	buttonLayout->addWidget(newGroup);
    buttonLayout->addWidget(updateGroup);
	buttonLayout->addWidget(deleteGroupButton);
	buttonLayout->addWidget(canel);

	mainLayout = new QHBoxLayout;
	mainLayout->addWidget(groupNameList);
	mainLayout->addLayout(buttonLayout);


	updateGroupWnd = new UpdateGroupWnd(this);
	connect(this, SIGNAL(selectedName(const QString)), updateGroupWnd, SLOT(updateSelectedName(const QString)));
    connect(updateGroupWnd, SIGNAL(updateGroupNameSignal(const QVector<QString>)), this, SLOT(updateGroupName(const QVector<QString>)));

    this->setLayout(mainLayout);
}

/************************************************************
 函数名:                             deleteGroup
 功能:                               删除好友分组
 ************************************************************/
void ManagerGroup::deleteGroup()
{
    QModelIndex index = groupNameList->currentIndex();                               //获得当前选择好友组
    if (index.row() < DEFAULT_GROUP_COUNT)                                           //判断是否是默认分组
    {
    	QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("不能删除默认分组!"));
    }
    else if(deleteData(groupName.at(index.row())))                                   //删除数据是否成功
    {
        if (QMessageBox::Yes == QMessageBox::warning(this, QString::fromUtf8("提示"), QString::fromUtf8("你想删除该组吗?"),
    					                                              QMessageBox::Yes | QMessageBox::No))
    	{
    		if (deleteGroupData(index.row()))                                        //删除数据
    		{
                model->removeRows(index.row(), 1, QModelIndex());
                emit(deleteGroupName(groupName.at(index.row())));                    //发送信号
    		}
    	}
    }
}

/************************************************************
 函数名:                             deleteGroupData
 功能:                               删除好友分组数据
 传入参数 groupId:                    好友组号
 返回值  true:                        删除成功
       false:                      删除失败
 ************************************************************/
bool ManagerGroup::deleteGroupData(int groupId)
{
	QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
	QSqlQuery query(db);														//创建数据库查询对象
	QString sql = "delete from wn_user_ip where user_group_id = '"+QString::number(groupId)+"'";

	bool isRight = query.exec(sql);
	if (!isRight)
	{
		QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("修改数据库失败!"));
		return false;
	}

	query.clear();

	return true;
}

/************************************************************
 函数名:                             selectUpdateGroup
 功能:                               删除好友分组名称
 ************************************************************/
void ManagerGroup::selectUpdateGroup()
{
	QModelIndex index = groupNameList->currentIndex();
	if (index.row() < DEFAULT_GROUP_COUNT)                                          //判断是否为默认分组
	{
		QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("不能修改默认分组!"));
	}
	else
	{
		emit(selectedName(groupName.at(index.row())));                               //发送信号
	}
}

/************************************************************
 函数名:                             deleteData
 功能:                               删除好友分组数据
 传入参数 name:                       好友分组名
 ************************************************************/
bool ManagerGroup::deleteData(QString name)
{
	QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
    QSqlQuery query(db);
    QString sql = "delete from wn_user_group where group_name = '"+name+"'";

    bool isRight = query.exec(sql);
    if (!isRight)
    {
    	QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("数据库操作失败!"));
    	return false;
    }

    query.clear();

    return true;
}

/************************************************************
 函数名:                             insertGroup
 功能:                              添加好友分组
 ************************************************************/
void ManagerGroup::insertGroup()
{
	newGroupWnd->show();
}

/************************************************************
 函数名:                             setNewGroupWnd
 功能:                              设置新建好友组窗口
 传入参数 tmpWnd:                    新建好友组窗口
 ************************************************************/
void ManagerGroup::setNewGroupWnd(NewGroupWnd *tmpWnd)
{
	this->newGroupWnd = tmpWnd;
}

/************************************************************
 函数名:                             clearList
 功能:                               清空好友分组列表
 ************************************************************/
void ManagerGroup::clearList()
{
	model->removeRows(0, groupName.count(), QModelIndex());
}

/************************************************************
 函数名:                             showGroupName
 功能:                               显示好友分组列表
 ************************************************************/
void ManagerGroup::showGroupName()
{
    clearList();																//清空好友分组列表
	for (int i=0; i<groupName.count(); i++)
	{
		model->insertRows(i, 1, QModelIndex());
		model->setData(model->index(i), groupName.at(i));
	}
}

/************************************************************
 函数名:                             setGroupName
 功能:                               显示好友分组容器
 ************************************************************/
void ManagerGroup::setGroupName(const QVector<QString> groupName)
{
    this->groupName = groupName;
	updateGroupWnd->setGroupName(groupName);                                   //设置管理好友分组容器
    showGroupName();                                                           //显示好友分组
}

/************************************************************
 函数名:                             updateGroupName
 功能:                               修改好友分组容器
 ************************************************************/
void ManagerGroup::updateGroupName(const QVector<QString> groupName)
{
    this->groupName = groupName;
    showGroupName();
    emit(updateGroupNameSignal(groupName));
}

/************************************************************
 函数名:                             creatModel
 功能:                               创建模型
 ************************************************************/
void ManagerGroup::creatModel()
{
	QStringList strList;
	model = new StringListModel(strList, this);
}

/************************************************************
 函数名:                             creatView
 功能:                               创建视图
 ************************************************************/
void ManagerGroup::creatView()
{
	groupNameList = new QListView(this);
	groupNameList->setModel(model);
}

/************************************************************
 函数名:                             ～ManagerGroup
 功能:                               析构函数
 ************************************************************/
ManagerGroup::~ManagerGroup()
{
	delete model;
	delete canel;
	delete newGroup;
	delete updateGroup;
	delete newGroupWnd;
	delete buttonLayout;
	delete mainLayout;
    delete groupNameList;
    delete updateGroupWnd;
    delete deleteGroupButton;
}
