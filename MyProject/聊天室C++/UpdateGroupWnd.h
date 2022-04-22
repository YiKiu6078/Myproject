/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							UpdateGroupWnd.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#ifndef UPDATEGROUPWND_H_
#define UPDATEGROUPWND_H_

/*******************************************************
 类名:                           UpdateGroupWnd
 功能:                           继承于QDialog主要修改按钮
                                                               主要完成修改好友组
 自定义功能:                      有专属自己的信号与槽
 *******************************************************/

#include <QtGui>
#include <QVector>
#include <QSqlDatabase>

extern QSqlDatabase globDB;													//数据库全局变量

/*******************************************************
 类名:                           UpdateGroupWnd
 功能:                           继承于QDialog主要修改好友组名
 自定义功能:                      有专属自己的信号与槽
 *******************************************************/

class UpdateGroupWnd : public QDialog
{
	Q_OBJECT

public:

	UpdateGroupWnd(QWidget * parent = 0, Qt::WindowFlags f = 0);
	virtual ~UpdateGroupWnd();
	void setGroupName(const QVector<QString> groupName);				   //设置好友分组容器

signals:

	void updateGroupNameSignal(const QVector<QString>);

public slots:

    void updateGroup();                                                     //修改好友组
    void updateSelectedName(const QString);                                 //更新修改好友组名

private:

    int updateIndex;
    QString updateName;

	QLabel *updateGroupName;
	QLineEdit *groupNameEdit;
	QPushButton *makeSure;
	QPushButton *canle;

	QVBoxLayout *mainLayout;
    QHBoxLayout *labelLayout;
	QHBoxLayout *buttonLayout;
	QVector<QString> groupName;                                              //好友分组组名容器
};

#endif /* UPDATEGROUPWND_H_ */
