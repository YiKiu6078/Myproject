/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							HostInfo.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#ifndef USER_H_
#define USER_H_

#include <QString>
#include <QPixmap>

/*******************************************************
 类名:                           User
 功能:                           主要完成用户信息封装
 *******************************************************/

class User
{
public:

	User();
	User(QString userIp, QString userName, QString userHead, QString userWrite, QString userHostName);
	virtual ~User();
	User & operator =(const User &user);                              //赋值函数
	bool operator ==(const User &user) const;                         //用户相同
	bool operator !=(const User &user) const;                         //用户不同
    void setUserIp(const QString &userIp);                            //设置用户Ip
    void setUserName(const QString &userName);                        //设置用户名
    void setUserHead(const QString &userHead);                        //设置用户头像
    void setUserWrite(const QString &userWrite);                      //设置用户个性签名
    void setUserHostName(const QString &userHostName);                //设置用户主机名
    const QString & getUserIp() const;                                            //获得用户ip
    const QString & getUserName() const;                                          //获得用户名
    const QString & getUserWrite() const;                                         //获得用户个性签名
    const QString & getUserHostName() const;                                      //获得用户主机名
    const QString & getUserHead() const;                                          //获得用户头像

private:

    QString userIp;                                                   //用户ip地址
	QString userName;                                                 //用户名
	QString userHead;                                                 //用户头像
	QString userWrite;                                                //用户个性签名
	QString userHostName;                                             //用户主机名
};

#endif /* USER_H_ */
