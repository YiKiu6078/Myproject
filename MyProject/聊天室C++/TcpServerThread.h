/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							TcpServerThread.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#ifndef TCPSERVERTREAD_H_
#define TCPSERVERTREAD_H_
#include <QObject>
#include <QThread>
#include <QProgressDialog>
#include "TcpClient.h"

/*******************************************************
 类名:                           TcpServerThread
 继承类:                          QThread
 功能:                           创建文件传送服务器线程
 *******************************************************/

class TcpServerThread : public QThread
{
    Q_OBJECT

public:

	TcpServerThread();                                                     //构造函数初始化资源
	virtual ~TcpServerThread();                                            //释放资源
    void setSocketId(int socketId);                                        //设置TcpSoecket文件描述符
    void setFileName(const QString &fileName);                             //设置文件名
    void setFileSize(int fileSize);                                        //设置文件尺寸

public slots:

    void progressStop();
    void showProcess(int bytes);                                           //显示进度条
    void disConnectServer();                                               //客户端与服务器断开

signals:

    void disconnectServer();                                               //客户端于服务器断开信号

protected:

	virtual void run();                                                    //线程运行函数

private:

	int sum;                                                               //接收文件数据
	int socketId;                                                          //Tcp通信的Socket文件描述符
	int fileSize;                                                          //传送文件的尺寸
	QString fileName;                                                      //传送文件的文件名
	TcpClient *client;
    QProgressDialog progressDialog;      				                   //传送文件进度条

};

#endif /* TCPSERVERTREAD_H_ */
