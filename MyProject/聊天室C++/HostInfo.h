/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							HostInfo.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#ifndef HOSTINFO_H_
#define HOSTINFO_H_

#include <QList>
#include <QHostInfo>
#include <QNetworkInterface>

/*******************************************************
 类名:                           HostInfo
 功能:                           主要获得主机信息
 自定义功能:                      主要获得网络设备信息及主机信息
 *******************************************************/

class HostInfo                                                       //主机信息类
{

public:

	HostInfo();                                                      //初始化默认构造函数
	virtual ~HostInfo();                                             //虚析构函数
    const QString & getHostName() const ;                            //得到主机名
    const QString & getLocalIp() const;                              //得到IP地址
    bool setLocalIp();                                               //获得并设置IP地址
    QString getBroadcast();                                          //获得广播地址

private:

    QString  broadcast;                                              //广播地址
	QString hostName;                                                //主机名
	QString localIp;                                                 //本地IP
	QList<QNetworkInterface> list;                                   //网路接口
	QNetworkInterface interface;
};

#endif /* HOSTINFO_H_ */
