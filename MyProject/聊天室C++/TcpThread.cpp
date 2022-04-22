/*****************************************************
 Copyright (c), 2022-2032, 刘颐槐
 文件名:							TcpThread.cpp
 作者:							刘颐槐
 版本号:							版本1
 完成日期:					    2022/03/26
 修改日期:
 修改列表:
 ******************************************************/
#include <QFile>
#include <QApplication>
#include <QMessageBox>
#include <QTcpSocket>
#include "TcpServer.h"
#include "TcpThread.h"

unsigned long TcpThread::sum = 0;                                               //初始化传送文件数据量

/************************************************************
 函数名:                             TcpThread
 功能:                               初始化资源
************************************************************/
TcpThread::TcpThread()
{
    creatProgressDialog();
    connect(this, SIGNAL(again()), this, SLOT(readFile()));
}

/************************************************************
 函数名:                             ~TcpThread
 功能:                               释放初始化资源
************************************************************/
TcpThread::~TcpThread()
{
    delete file;
    delete client;
}

/************************************************************
 函数名:                              run
 功能:                               线程运行函数
************************************************************/
void TcpThread::run()
{

    client = new QTcpSocket();                                                                               //发送文件TcpSocket
    file = new QFile;                                                                                           //创建将要传送的文件对象

    connect(client, SIGNAL(bytesWritten(qint64)), this, SLOT(getByteWritten(qint64)));    //绑定发送数据量于显示发送数据量
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnectSocket()));                //绑定断开连接于处理断开连接的槽函数

    QHostAddress addr(hostName);
    client->connectToHost(addr, FILEPORT);                                                            //连接主机

    file->setFileName(fileUrl);                                                                              //设置发送文件路径
    bool isRight = file->open(QFile::ReadOnly);                                                       //打开文件
    if (!isRight)
    {
        cout << "打开文件失败!" << endl;
    }
    else
    {
        progressDialog->setLabelText(file->fileName()+QString::fromUtf8(" 传送中...."));
        progressDialog->setMaximum (file->size());                             //设置进度条显示尺寸
        readFile();                                                                                               //获得发送数据长度
    }

    exec();                                                                                                       //开始线程事件循环
}

void TcpThread::creatProgressDialog()
{
    progressDialog = new QProgressDialog;
    progressDialog->setWindowModality(Qt::WindowModal);                //显示进度条
    progressDialog->setMinimumDuration(5);
    progressDialog->setMinimum (0);
    progressDialog->setWindowTitle(QString::fromUtf8("请等待...."));
    progressDialog->setCancelButtonText(QString::fromUtf8("停止"));

    connect(progressDialog, SIGNAL(canceled()), this, SLOT(progressStop()));
}

void TcpThread::progressStop()
{
    client->close();
    file->close();
    
    sum = 0;
    progressDialog->hide();
    progressDialog->close();
}

/************************************************************
 函数名:                                                                  readFile
 功能:                                                                     读取文件
************************************************************/
void TcpThread::readFile()
{
    if (!file->atEnd() && file->isOpen())                                                                                           //是否读取完毕
    {
        QByteArray byteArray = file->read(MAXSIZE);                                                   //读取文件数据
        client->write(byteArray);                                                                             //发送文件数据
    }
}

/************************************************************
 函数名:                             socketError
 功能:                               错误处理槽函数
************************************************************/
void TcpThread::error()
{
    QMessageBox::critical(0, QString::fromUtf8("Socket错误"), QString::fromUtf8("Socket错误!"));
}

/************************************************************
 函数名:                              setHostName
 功能:                                设置主机IP地址
 输入参数  hostName:                    主机IP地址
************************************************************/
void TcpThread::setHostName(const QString &hostName)
{
	this->hostName = hostName;                                         //设置主机IP地址
}

/************************************************************
 函数名:                             getHostName
 功能:                               获得主机IP地址
 返回值:                             主机IP地址引用
************************************************************/
const QString &TcpThread::getHostName() const
{
    return hostName;                                                        //获得主机IP地址
}

/************************************************************
 函数名:                              setFileUrl
 功能:                                设置文件地址
 输入参数  fileUrl:                     设置文件路径
************************************************************/
void TcpThread::setFileUrl(const QString &fileUrl)
{
    this->fileUrl = fileUrl;                                                      //设置文件路径
    QFile file(fileUrl);                                                          //将要传送的文件
}

/************************************************************
 函数名:                             getFileUrl
 功能:                               获得将要发送文件路径
 返回值:                             将要发送文件路径引用
************************************************************/
const QString &TcpThread::getFileUrl() const
{
	return fileUrl;                                                    //获得文件路径
}

/************************************************************
 函数名:                             getByteWritten
 功能:                               获得发送出去数据量槽函数
输入参数 bytes:                       发送出去的数据量
************************************************************/
void TcpThread::getByteWritten(qint64 bytes)
{

   if (file->isOpen())
    {
        sum += bytes;                                                      //累计发送的文件数据
        progressDialog->setValue(sum);                               //设置进度条显示传送百分比

        if (sum == (unsigned long)progressDialog->maximum() && file->isOpen())                    //发送完毕
        {
            client->close();                                                 //关闭socket
            file->close();                                                    //关闭文件
            QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("发送完毕!"));
        }
        else
        {
            emit again();                                                    //继续发送文件
        }
    }
}

/************************************************************
 函数名:                             disconnectSocket
 功能:                               客户端于服务器断断开连接槽函数
************************************************************/
void TcpThread::disconnectSocket()
{
	emit (finishSend());											   //发送完成信号
}
