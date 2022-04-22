/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							NewGroupWnd.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/


#ifndef NEWGROUPWND_H_
#define NEWGROUPWND_H_

#include <QtGui>
#include <QVector>
#include <QSqlDatabase>

/*******************************************************
 类名:                           NewGroupWnd
 功能:                           继承于QDialog主要新建按钮
                                                               主要完成新建好友组
 自定义功能:                      有专属自己的信号与槽
 *******************************************************/

class NewGroupWnd : public QDialog
{
	Q_OBJECT

public:

	NewGroupWnd(QVector<QString> groupName, QWidget * parent = 0, Qt::WindowFlags f = 0);
	virtual ~NewGroupWnd();

signals:

	void insertGroupName(const QString);

public slots:

    void clear();                                                           //清空编辑框
    void newGroup();                                                        //新建好友组

private:

	QLabel *newGroupName;
	QLineEdit *groupNameEdit;
	QPushButton *makeSure;
	QPushButton *canle;

	QVBoxLayout *mainLayout;
    QHBoxLayout *labelLayout;
	QHBoxLayout *buttonLayout;
	QVector<QString> groupName;                                              //好友分组组名容器
};

#endif /* NEWGROUPWND_H_ */
