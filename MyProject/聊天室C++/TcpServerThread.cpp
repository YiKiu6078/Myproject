/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							TcpServerThread.h
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/
#include <iostream>
#include <QMessageBox>
#include <QApplication>
#include "TcpServer.h"

using namespace std;

/*******************************************************************
  函数名：						TcpServerThread
  功能：					        初始化接收文件线程
  ******************************************************************/
TcpServerThread::TcpServerThread()
{
	sum = 0;                                                                       //初始化传送文件尺寸

    progressDialog.setWindowModality(Qt::WindowModal);
    progressDialog.setMinimumDuration(5);
    progressDialog.setWindowTitle(QString::fromUtf8("请等待...."));
    progressDialog.setLabelText(QString::fromUtf8("传送中...."));
    progressDialog.setCancelButtonText(QString::fromUtf8("停止"));

    connect(&progressDialog, SIGNAL(canceled()), this, SLOT(progressStop()));
}

/*******************************************************************
  函数名：						~TcpServerThread
  功能：					        回收资源
  ******************************************************************/
TcpServerThread::~TcpServerThread()
{
    delete client;
}

void TcpServerThread::progressStop()
{
    progressDialog.hide();
    progressDialog.close();
}

/*******************************************************************
  函数名：						run
  功能：					        继承线程运行功能
  ******************************************************************/
void TcpServerThread::run()
{
    client = new TcpClient;
    connect(client, SIGNAL(disconnected()), this, SLOT(disConnectServer()));
    connect(client, SIGNAL(reciveSize(int)), this, SLOT(showProcess(int)));

    progressDialog.setLabelText(this->fileName+QString::fromUtf8(" 接收中...."));
    client->setFileName(fileName);											   //设置文件名
    client->setSocketDescriptor(socketId);									   //设置文件描述符
    exec();
}

/*******************************************************************
  函数名：						showProcess
  功能：					        显示接收进度
  传入参数 bytes:             发送字节数
  ******************************************************************/
void TcpServerThread::showProcess(int bytes)
{
    if (client->fileIsOpen())
    {
        sum += bytes;                                                     		    //累计发送的文件数据
        progressDialog.setValue(sum);                                     			//设置进度条显示传送百分比
        qApp->processEvents();                                                      //传送进程事件
    }
}

/*******************************************************************
  函数名：						setSocketId
  功能：					        设置文件描述符
  传入参数 socketId:           文件描述符Id
  ******************************************************************/
void TcpServerThread::setSocketId(int socketId)
{
	this->socketId = socketId;
}

/*******************************************************************
  函数名：						fileName
  功能：					        设置文件名
  传入参数 fileName:           文件名
  ******************************************************************/
void TcpServerThread::setFileName(const QString & fileName)
{
	this->fileName = fileName;
}

/*******************************************************************
  函数名：						setFileSize
  功能：					        设置文件尺寸
  传入参数 fileSize:           文件尺寸
  ******************************************************************/
void TcpServerThread::setFileSize(int fileSize)
{
	this->fileSize = fileSize;
	progressDialog.setRange(0, fileSize);                                       //设置进度条显示尺寸
}

/*******************************************************************
  函数名：						disConnectServer
  功能：					       断开连接
  ******************************************************************/
void TcpServerThread::disConnectServer()
{
	QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("接收文件完毕!"));
	emit disconnectServer();                                                    //发送断开连接信号
}
