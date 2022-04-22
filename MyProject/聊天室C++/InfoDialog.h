#ifndef INFODIALOG_H_
#define INFODIALOG_H_

#include <QtGui>
#include <QStringList>
#include <QSqlDatabase>
#include "User.h"
#include "shareData.h"

/*******************************************************
 类名:                           InfoDialog
 功能:                           继承于QDialog主要新建按钮
                                                               主要完成用户信息修改框显示
 自定义功能:                      有专属自己的信号与槽
 *******************************************************/

class InfoDialog:public QDialog
{
	Q_OBJECT

public:

	InfoDialog(const User &user, QWidget *parent = 0, Qt::WindowFlags = 0);
	virtual ~InfoDialog();
    const User & getUserInfo();                                     //获得用户信息
    void initHeadList();                                            //初始化本地头像

public slots:

    void makeSure();                                                 //自定义确定按钮槽函数
    void updateHead();                                              //自定义取消按钮槽函数重置列表框头像

signals:

    void update();                                                    //个人信息被修改信号

protected:

    bool insertDatabase();                                          //将修改个人信息插入数据库

private:

    User user;                                                      //用户的个人信息

    QStringList headList;                                           //头像链表

    QLabel *ip;                                                     //本机IP
	QLabel *write;                                                  //个性签名
	QLabel *userHead;                                               //用户头像
	QLabel *userName;                                               //用户名

	QComboBox *headBox;                                             //用户头像
	QLineEdit *heartWrite;                                          //个性签名
	QLineEdit *userNameEdit;                                        //用户名
    QLineEdit *ipEdit;                                              //本机IP

	QPushButton *makesure;                                          //确定按钮
	QPushButton *cancel;                                            //关闭按钮

	QHBoxLayout *ipLayout;                                          //ip布局管理器
	QVBoxLayout *mainLayout;                                        //主体布局管理器
	QHBoxLayout *sureCancelLayout;                                  //确认与关闭按钮布局管理器
	QHBoxLayout *writeLayout;                                       //个性签名布局管理器
	QHBoxLayout *headBoxLayout;                                     //头像布局管理器
	QHBoxLayout *nameBoxLayout;                                     //用户名布局管理器
};

#endif /* INFODIALOG_H_ */
