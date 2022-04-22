/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							HostInfo.cpp
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/
#include <QMessageBox>
#include <QNetworkAddressEntry>
#include "HostInfo.h"
#include "shareData.h"

/********************************************************
  函数名:                          HostInfo
  功能:                            初始化数据
 ********************************************************/
HostInfo::HostInfo()
{
	QNetworkInterface interFace;

	QList<QNetworkInterface> netList;
	netList = QNetworkInterface::allInterfaces();                                //获得网络接口列表

	hostName = QHostInfo::localHostName();                                       //获得主机名
	interface = netList.at(DEVIECE_INDEX);                                       //获得网路接口
}

/********************************************************
  函数名:                          getHostName
  功能:                            获得主机名
  返回值:                          主机名
 ********************************************************/
const QString & HostInfo::getHostName() const
{
	return this->hostName;                                                        //获取主机名
}

/********************************************************
  函数名:                          getLocalIp
  功能:                            获得主机IP
  返回值:                          主机IP
 ********************************************************/
const QString & HostInfo::getLocalIp() const
{
	return this->localIp;                                                         //获取IP地址
}

/********************************************************
  函数名:                          setLocalIp
  功能:                            从网路设备中设置当地IP
  返回值  true:                     设置成功
       false:                    设置失败
 ********************************************************/
bool HostInfo::setLocalIp()
{
	QList<QNetworkAddressEntry> entryList = interface.addressEntries();           //获取网络地址设备

	if (entryList.isEmpty())
	{
		QMessageBox::information(0, QString::fromUtf8("错误"), QString::fromUtf8("网络未设置好!"));
		return false;
	}

	QNetworkAddressEntry entry = entryList.first();                               //第一个网络地址设备

	localIp = entry.ip().toString();                                              //设置IP
	broadcast = entry.broadcast().toString();                                                //设置广播地址

	if (localIp.isEmpty())                                                        //设置IP不成功
	{
		localIp = LOOKBACKIP;                                                     //设置本机环回网络地址
	}

	if (broadcast.isEmpty())                                                      //设置广播地址不成功
	{
		broadcast = QHostAddress::Broadcast;                                      //设置默认广播地址
	}

	return true;
}

/********************************************************
  函数名:                           getBroadcast
  功能:                             获得广播地址
 ********************************************************/
QString HostInfo::getBroadcast()
{
	return broadcast;
}

/********************************************************
  函数名:                           ~HostInfo
  功能:                            释放资源
 ********************************************************/
HostInfo::~HostInfo()
{

}
