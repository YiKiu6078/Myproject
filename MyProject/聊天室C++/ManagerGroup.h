/*****************************************************
 Copyright (c), 2009-2019, 林勇
 文件名:							ManagerGroup.h
 作者:							林勇
 版本号:							版本1
 完成日期:					    2009/4/2
 修改日期:
 修改列表:
 ******************************************************/

#ifndef MANAGERGROUP_H_
#define MANAGERGROUP_H_

#include <QtGui>
#include <QDialog>
#include <QSqlDatabase>
#include "NewGroupWnd.h"
#include "stringListModel.h"
#include "UpdateGroupWnd.h"

/*******************************************************
 类名:                           ManagerGroup
 功能:                           继承于QDialog主要用户管理好友分组
 自定义功能:                      有专属自己的信号与槽
 *******************************************************/


class ManagerGroup : public QDialog
{
   Q_OBJECT

public:

	ManagerGroup(QWidget * parent = 0, Qt::WindowFlags f = 0);
	virtual ~ManagerGroup();
	void setGroupName(const QVector<QString> groupName);                                //设置好友分组容器
	void showGroupName();                                          						//显示好友分组
	void creatModel();                                                                  //创建模型
	void creatView();																	//创建视图
	void setNewGroupWnd(NewGroupWnd *tmpWnd);                      						//设置新建好友窗口
	void clearList();																	//清空列表
    bool deleteData(QString name);														//删除数据
    bool deleteGroupData(int groupId);                                                  //删除好友分组

signals:

    void updateGroupNameSignal(const QVector<QString>);
	void deleteGroupName(const QString);
    void selectedName(const QString);

public slots:

    void deleteGroup();
    void insertGroup();
    void updateGroupName(const QVector<QString>);
    void selectUpdateGroup();

private:

	QPushButton *newGroup;
	QPushButton *updateGroup;
	QPushButton *deleteGroupButton;
	QPushButton *canel;
	NewGroupWnd *newGroupWnd;
	UpdateGroupWnd *updateGroupWnd;                                          //修改好友分组窗口
	QVBoxLayout *buttonLayout;
	QHBoxLayout *mainLayout;
	QVector<QString> groupName;
	QListView *groupNameList;
	StringListModel *model;
    QString name;
};

#endif /* MANAGERGROUP_H_ */
