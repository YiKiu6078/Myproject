/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							TcpServer.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <QVector>
#include <QTcpServer>
#include "shareData.h"
#include "TcpServerThread.h"

/*******************************************************
 类名:                           TcpServer
 继承类:                          QTcpServer
 功能:                           创建服务器线程
 *******************************************************/

class TcpServer : QTcpServer
{
    Q_OBJECT

public:

	TcpServer(QObject *parent = 0);
	virtual ~TcpServer();
    void insertFileName(const QString &fileName);                                //插入接收文件容器中
    const QString & getLastFileName() const;                                     //获得容器中最后一个文件名
    void insertFileSize(int fileSize);                                           //插入接收文件尺寸容器
    int getFileSize() const;                                                     //获得容器中最后一个文件尺寸

public slots:
    void revThread(); 															 //回收线程资源

protected:

    virtual void incomingConnection(int socketDescriptor);         //新连接到达处理

private:

    QVector<int> fileSizeVector;                                           //文件尺寸容器
    QVector<QString> fileVector;                                          //文件容器
};

#endif /* TCPSERVER_H_ */
