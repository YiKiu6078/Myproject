/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							UpdateGroupWnd.cpp
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#include <QSqlQuery>
#include "shareData.h"
#include "UpdateGroupWnd.h"

UpdateGroupWnd::UpdateGroupWnd(QWidget * parent, Qt::WindowFlags f)
                                                   : QDialog(parent, f)
{
    setWindowTitle(QString::fromUtf8("修改好友组"));
    updateGroupName = new QLabel(QString::fromUtf8("组名称:"));
    groupNameEdit = new QLineEdit;                                                   //组名称编辑框

    makeSure = new QPushButton(QString::fromUtf8("确定"));                            //确定按钮
    canle = new QPushButton(QString::fromUtf8("取消"));                               //取消按钮

    connect(makeSure, SIGNAL(clicked()), this, SLOT(updateGroup()));                 //连接确定按钮信号于槽
    connect(canle, SIGNAL(clicked()), this, SLOT(close()));                               //连接取消按钮信号于槽

    labelLayout = new QHBoxLayout;                                                   //编辑框布局管理器
    labelLayout->addWidget(updateGroupName);
    labelLayout->addWidget(groupNameEdit);

    buttonLayout = new QHBoxLayout;                                                  //按钮布局管理器
    buttonLayout->addWidget(makeSure);
    buttonLayout->addWidget(canle);

    mainLayout = new QVBoxLayout(this);                                              //窗口主布局管理器
    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setAlignment(buttonLayout, Qt::AlignRight);
}

/************************************************************
 函数名:                             updateGroup
 功能:                               修改好友分组组名
 ************************************************************/
void UpdateGroupWnd::updateGroup()
{
	QString newName = groupNameEdit->text();
	if (newName == NULL)
	{
		QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("好友组名称不能为空!"));
	}
	else
	{
		QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
		QSqlQuery query(db);
		QString sql = "update wn_user_group set group_name = '"+newName+"'"
				                      " where group_name = '"+updateName+"'";
		bool isRight = query.exec(sql);
		if (!isRight)
		{
			QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("修改数据库失败!"));
		}
		else
		{
			QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("修改成功!"));
			groupName.replace(updateIndex, newName);
			emit(updateGroupNameSignal(groupName));
			this->close();
		}

		query.clear();
	}
}

/************************************************************
 函数名:                             updateSelectedName
 功能:                               修改好友分组组名
 参数 name:                           将要修改的好友组名
 ************************************************************/
void UpdateGroupWnd::updateSelectedName(const QString name)
{
	updateIndex = groupName.indexOf(name);
	updateName = name;
	groupNameEdit->setText(name);
    this->show();
}

/************************************************************
 函数名:                             setGroupName
 功能:                               设置好友分组容器
 参数 groupName:                      新的好友分组容器
 ************************************************************/
void UpdateGroupWnd::setGroupName(const QVector<QString> groupName)
{
	this->groupName = groupName;
}

UpdateGroupWnd::~UpdateGroupWnd()
{
	delete canle;
	delete makeSure;
	delete mainLayout;
	delete labelLayout;
	delete buttonLayout;
	delete groupNameEdit;
	delete updateGroupName;
}
