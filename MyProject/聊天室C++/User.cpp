/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							HostInfo.cpp
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#include "User.h"

User::User()
{

}
/*******************************************************
  函数名:                          User
  功能:                            代参数构造函数
  输入参数 userIp:                  用户Ip
        userName:                用户名
        userHead:                用户头像
        userWrite:               用户个性签名
        userHostName:            用户主机名
 *******************************************************/
User::User(QString userIp, QString userName, QString userHead, QString userWrite, QString userHostName)
{
	this->userIp = userIp;                                               //初始化用户ip
	this->userName = userName;                                           //初始化用户名
	this->userHead = userHead;                                           //初始化用户头像
	this->userWrite = userWrite;                                         //初始化用户个性签名
	this->userHostName = userHostName;                                   //初始化用户主机名
}

/*******************************************************
  函数名:                          setUserIp
  功能:                            设置用户Ip
  输入参数 userIp:                  用户Ip
 *******************************************************/
void User::setUserIp(const QString &userIp)
{
	this->userIp = userIp;
}

/*******************************************************
  函数名:                          setUserName
  功能:                            设置用户名
  输入参数 userName:                用户名
 *******************************************************/
void User::setUserName(const QString & userName)
{
	this->userName = userName;
}

/*******************************************************
  函数名:                          setUserHead
  功能:                            设置用户头像
  输入参数 userHead:                用户头像
 *******************************************************/
void User::setUserHead(const QString &userHead)
{
	this->userHead = userHead;
}

/*******************************************************
  函数名:                          setUserHostName
  功能:                            设置用户主机名
  输入参数 userHostName:            用户主机
 *******************************************************/
void User::setUserHostName(const QString &userHostName)
{
	this->userHostName = userHostName;
}

/*******************************************************
  函数名:                          setUserWrite
  功能:                            设置用户个性签名
  输入参数 userWrite:               用户个性签名
 *******************************************************/
void User::setUserWrite(const QString &userWrite)
{
	this->userWrite = userWrite;
}

/*******************************************************
  函数名:                          getUserHead
  功能:                            获得用户头像
  返回值:                          用户头像引用
 *******************************************************/
const QString & User::getUserHead() const
{
	return userHead;
}

/*******************************************************
  函数名:                          getUserIp
  功能:                            获得用户ip
  返回值:                          用户ip地址引用
 *******************************************************/
const QString & User::getUserIp() const
{
	return userIp;
}

/*******************************************************
  函数名:                          getUserName
  功能:                            获得用户名
  返回值:                          用户名引用
 *******************************************************/
const QString & User::getUserName() const
{
	return userName;
}

/*******************************************************
  函数名:                          getUserHostName
  功能:                            获得用户主机名
  返回值:                          用户主机名引用
 *******************************************************/
const QString & User::getUserHostName() const
{
	return userHostName;
}

/*******************************************************
  函数名:                          getUserWrite
  功能:                            获得用户个性签名
  返回值:                          用户个性签名引用
 *******************************************************/
const QString & User::getUserWrite() const
{
	return userWrite;
}

/*******************************************************
  函数名:                          operator =
  功能:                            赋值函数
  输入参数 user:                    赋值原对象的引用
  返回值:                          赋值目标用户对象引用
 *******************************************************/
User & User::operator =(const User &user)
{
	if (this == &user)                                                        //自身赋值直接返回
	{
		return *this;
	}

    this->userIp = user.userIp;                                               //赋值IP
    this->userName = user.userName;                                           //赋值用户名
    this->userHead = user.userHead;                                           //用户头像
    this->userWrite = user.userWrite;                                         //用户个性签名
    this->userHostName = user.userHostName;                                   //用户名主机名

    return *this;
}

/*******************************************************
  函数名:                          ~User
  功能:                            析构函数释放资源
 *******************************************************/
User::~User()
{

}

/*******************************************************
  函数名:                          operator =＝
  功能:                            判断释放两个用户是否相等
  输入参数 user:                    目标对象的引用
  返回值 TRUE:                      两个用户相同
       FALSE：                                       两个用户不同
 *******************************************************/
bool User::operator ==(const User &user) const
{
	if (this->getUserIp() != user.getUserIp())                                 //IP是否相同
	{
		return false;
	}

	return true;
}

/*******************************************************
  函数名:                          operator !＝
  功能:                            判断释放两个用户是否相等
  输入参数 user:                    目标对象的引用
  返回值 TRUE:                      两个用户不同
       FALSE：                                       两个用户相同
 *******************************************************/
bool User::operator !=(const User &user) const
{
	if (this->getUserIp() != user.getUserIp())                                //IP是否相同
	{
		return true;
	}

	return false;
}
