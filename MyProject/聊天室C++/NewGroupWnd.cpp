/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							NewGroupWnd.cpp
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#include <QSqlQuery>
#include "shareData.h"
#include "NewGroupWnd.h"

NewGroupWnd::NewGroupWnd(QVector<QString> groupName, QWidget * parent, Qt::WindowFlags f)
                                             : QDialog(parent, f)
{
     setWindowTitle(QString::fromUtf8("新建好友组"));                                   //窗口名称

     newGroupName = new QLabel(QString::fromUtf8("组名称:"));
     groupNameEdit = new QLineEdit;                                                   //组名称编辑框

     makeSure = new QPushButton(QString::fromUtf8("确定"));                            //确定按钮
     canle = new QPushButton(QString::fromUtf8("取消"));                               //取消按钮

     connect(makeSure, SIGNAL(clicked()), this, SLOT(newGroup()));                    //连接确定按钮信号于槽
     connect(canle, SIGNAL(clicked()), this, SLOT(clear()));                          //连接取消按钮信号于槽

     labelLayout = new QHBoxLayout;                                                   //编辑框布局管理器
     labelLayout->addWidget(newGroupName);
     labelLayout->addWidget(groupNameEdit);

     buttonLayout = new QHBoxLayout;                                                  //按钮布局管理器
     buttonLayout->addWidget(makeSure);
     buttonLayout->addWidget(canle);

     mainLayout = new QVBoxLayout(this);                                              //窗口主布局管理器
     mainLayout->addLayout(labelLayout);
     mainLayout->addLayout(buttonLayout);
     mainLayout->setAlignment(buttonLayout, Qt::AlignRight);

     this->groupName = groupName;                                                     //好友组名容器
}

/************************************************************
 函数名:                             clear
 功能:                               清空编辑框
 ************************************************************/
void NewGroupWnd::clear()
{
	groupNameEdit->clear();
	this->close();
}

/************************************************************
 函数名:                             newGroup
 功能:                               新建好友组
 ************************************************************/
void NewGroupWnd::newGroup()
{
	QString name = groupNameEdit->text();                                                 //是否编辑框为空
	if (name == NULL)
	{
		QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("组名称为空!"));
	}
	else
	{
		bool isExit = false;
		for (int i=0; i<groupName.count(); i++)                                          //是否该组名承已经存在
		{
            if (name == groupName.at(i))
            {
            	QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("组名称已经存在!"));
            	isExit = true;                                                           //该组名已经存在
            	break;
            }
		}

		if (!isExit)
		{
			QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
            QSqlQuery query(db);                                                     //创建数据库操作对象
            QString sql = "insert into wn_user_group(group_name) values('"+name+"')";

            bool isRight = query.exec(sql);                                              //插入数据库
            if (!isRight)
            {
            	QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("更新数据库失败!"));
            }
            else
            {
            	QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("新建成功!"));
            	groupName.append(name);                                                 //添加进组名称容器
                emit(insertGroupName(name));                                            //发送添加组名称信号
            	this->clear();                                                          //清空组名称编辑框
            }

            query.clear();
		}
	}
}

NewGroupWnd::~NewGroupWnd()
{
    delete canle;
    delete makeSure;
    delete newGroupName;
    delete groupNameEdit;
    delete labelLayout;
    delete buttonLayout;
    delete mainLayout;
}
