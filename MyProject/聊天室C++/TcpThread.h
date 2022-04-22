/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							TcpThread.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#ifndef TCPTHREAD_H_
#define TCPTHREAD_H_
#include <QTimer>
#include <QThread>
#include <iostream>
#include <QTcpSocket>
#include <QProgressDialog>
#include <QAbstractSocket>
#include "shareData.h"
#include "TcpServerThread.h"

using namespace std;

/*******************************************************
 类名:                           TcpThread
 继承类:                          QThread
 功能:                           创建文件传送线程
 *******************************************************/
class TcpThread : public QThread
{
    Q_OBJECT

public:

	TcpThread();
	virtual ~TcpThread();
	void setHostName(const QString &hostName);                      //设置主机IP地址
    const QString &getHostName() const;                                 //获得主机IP地址
    void setFileUrl(const QString &fileUrl);                                //设置文件路径
    const QString &getFileUrl() const;                                      //获得文件路径
    void creatProgressDialog();
    static unsigned long sum;                                                //传送文件的数据

signals:
    void again();
    void finishSend();                                                           //发送信号

protected slots:
    void progressStop();
    void readFile();                                                              //读取文件
    void error();                                                                  //错误处理槽函数
    void getByteWritten(qint64);                                            //已经发送的数据槽
    void disconnectSocket();                                                //断开连接槽处理函数

protected:
    unsigned long getMaxSize(unsigned long fileSize);              //计算每次发送的数据长度
    virtual void run();                                                          //线程执行函数

private:

    QFile *file;
    QTcpSocket *client;
    QString hostName;                                                        //主机IP地址
    QString fileUrl;                                                             //文件路径
    unsigned long readSize;
    QProgressDialog *progressDialog;                                     //传送文件进度条
};

#endif /* TCPTHREAD_H_ */
