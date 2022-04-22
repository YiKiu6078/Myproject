/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							TcpClient.cpp
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/
#include <QMessageBox>
#include <QApplication>
#include "TcpClient.h"

/*******************************************************************
  函数名：						TcpClient
  功能：					        初始化资源
  ******************************************************************/
TcpClient::TcpClient(QObject *parent) : QTcpSocket(parent)
{
	fileName = "download/";
    connect(this, SIGNAL(readyRead()), this, SLOT(recivedData()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    connect(this, SIGNAL(disconnected()), this, SLOT(diconnectSocket()));
}

/*******************************************************************
  函数名：						～TcpClient
  功能：					        释放资源
  ******************************************************************/
TcpClient::~TcpClient()
{

}

/*******************************************************************
  函数名：						recivedData
  功能：					        接收数据
  ******************************************************************/
void TcpClient::recivedData()
{
	int bytes = this->bytesAvailable();
	if (bytes != 0)
	{
	    QByteArray byteArray;
	    byteArray = read(bytes);
	    emit(reciveSize(bytes));
	    file.write(byteArray);													//将得到的数据写入文件中
	}
}

/*******************************************************************
  函数名：						setFileName
  功能：					        设置文件名
 传入参数 fileName:            文件名
  ******************************************************************/
void TcpClient::setFileName(const QString & fileName)
{
	this->fileName += fileName;
    file.setFileName(this->fileName);											//设置文件名
    if (!file.open(QFile::WriteOnly))
    {
    	QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("读取文件出错!"));
    }
}

/*******************************************************************
  函数名：						diconnectSocket
  功能：					        接收数据
  ******************************************************************/
void TcpClient::diconnectSocket()
{
	file.close();                                                               //关闭文件
}

/*******************************************************************
  函数名：						fileIsOpen
  功能：					        获得文件当前状态
  返回值 TRUE:                 文件打开
            FALSE:               文件关闭
  ******************************************************************/
bool TcpClient::fileIsOpen() const
{
    return file.isOpen();
}

