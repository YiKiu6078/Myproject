/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							TcpClient.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

#include <QFile>
#include <QTcpSocket>
#include <QProgressDialog>
#include "shareData.h"


/*******************************************************
 类名:                           TcpClient
 继承类:                          QTcpServer
 功能:                            写文件
 *******************************************************/
class TcpClient : public QTcpSocket
{
	Q_OBJECT

public:

	TcpClient(QObject *parent = 0);
	virtual ~TcpClient();
    bool fileIsOpen() const;                                                     //文件当前状态
    void setFileName(const QString &fileName);                                   //设置发送文件文件名

public slots:

    void recivedData();                                                          //接收数据
    void diconnectSocket();                                                      //客户端断开连接

signals:

    void reciveSize(int);                                                        //已经接收的数据

private:

    QFile file;                                                                  //传送文件
    int fileSize;                                                                //传送文件尺寸
    QString fileName;                                                            //接收文件名
};

#endif /* TCPCLIENT_H_ */
