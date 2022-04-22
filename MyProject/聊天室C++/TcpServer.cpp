/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							TcpServer.cpp
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/

#include <QMessageBox>
#include "TcpClient.h"
#include "TcpServer.h"
#include "TcpServerThread.h"


/*******************************************************************
  函数名：						TcpServer
  功能：					        初始化服务器
  ******************************************************************/
TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
    if (!listen(QHostAddress::Any, FILEPORT))                                         //监听连接
    {
    	QMessageBox::information(0, QString::fromUtf8("Socket错误"),
    			                    QString::fromUtf8("监听连接错误!"));
    }
}

/*******************************************************************
  函数名：						～TcpServer
  功能：					        释放资源
  ******************************************************************/
TcpServer::~TcpServer()
{

}

/*******************************************************************
  函数名：						incomingConnection
  功能：					        有新连接
 传入参数 socketId:            新连接描述符
  ******************************************************************/
void TcpServer::incomingConnection(int socketId)
{
    TcpServerThread *serverThread = new TcpServerThread;                              //创建文件接收线程
    connect(serverThread, SIGNAL(disconnectServer()), this, SLOT(revThread()));   //回收线程资源

	  serverThread->setFileName(fileVector.last());                                     //设置文件名
	  serverThread->setFileSize(fileSizeVector.last());                                 //设置文件名
	  serverThread->setSocketId(socketId);                                              //设置文件描述符
    serverThread->start();                                                                  //开始线程
}

/*******************************************************************
  函数名：						revThread
  功能：					        回收线程资源
  ******************************************************************/
void TcpServer::revThread()
{
    wait();																		       //回收线程资源
}

/*******************************************************************
  函数名：						insertFileName
  功能：					        添加进文件名容器
  传入参数 fileName:           插入的文件名
  ******************************************************************/
void TcpServer::insertFileName(const QString &fileName)
{
	fileVector.append(fileName);
}

/*******************************************************************
  函数名：						getLastFileName
  功能：					        获得最后一个文件名
  ******************************************************************/
const QString & TcpServer::getLastFileName() const
{
	return fileVector.last();
}

/*******************************************************************
  函数名：						insertFileSize
  功能：					        插入文件尺寸容器
 传入参数 fileSize:            文件尺寸
  ******************************************************************/
void TcpServer::insertFileSize(int fileSize)
{
	fileSizeVector.append(fileSize);
}

/*******************************************************************
  函数名：						getFileSize
  功能：					       获得最后一个文件尺寸
  ******************************************************************/
int TcpServer::getFileSize() const
{
	return fileSizeVector.last();
}
