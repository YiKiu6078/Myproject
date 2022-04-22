/******************************************************************
  文件名：ftpclientdialog.cpp
  功能：使用ftp协议实现文件传输
  作者：梁庚
  完成日期：2009.12.19
  修改日期：2009.12.20
  版本号：01
  ******************************************************************/
#include <QMessageBox>
#include "ftpclientdialog.h"

/*******************************************************************
  函数名：						ftpClientDialog
  功能：						实现所需要的对象和接受文件的界面
  ******************************************************************/
ftpClientDialog::ftpClientDialog(QWidget *parent)
    : QDialog(parent)
{
    /***********************接受文件界面****************************/
    setWindowTitle(QString::fromUtf8("文件消息"));
    acceptButton = new QPushButton(QString::fromUtf8("接收"));
    exitButton = new QPushButton(QString::fromUtf8("拒绝"));
    actionLabel = new QLabel(QString::fromUtf8("您有文件到达!"));

    hbLayout = new QHBoxLayout;
    hbLayout->addWidget(acceptButton);
    hbLayout->addWidget(exitButton);

    vbLayout = new QVBoxLayout;
    vbLayout->addWidget(actionLabel);
    vbLayout->addLayout(hbLayout);

    setLayout(vbLayout);

    /**********************信号与槽的连接****************************/
    connect(acceptButton,SIGNAL(clicked()),this,SLOT(slotsgetFile()));
    connect(acceptButton,SIGNAL(clicked()), this, SLOT(close()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(slotRefuseFile()));

    tcpServer = new TcpServer;                                                      //开启接收文件服务器
}

/*****************************************************************
 函数名：						slotsgetFile
 功能：						   使用ftp协议获取文件
 *****************************************************************/
void ftpClientDialog::slotsgetFile()
{
	tcpServer->insertFileName(fileName);                                            //插入发送文件名容器
	tcpServer->insertFileSize(fileSize);                                            //插入发送文件尺寸容器
    emit(acceptFile(fileName));                                                     //发送接受文件请求信号
}

/************************************************************
 函数名:                             setServerAddress
 功能:                               设置发送文件地址
 传入参数 addr:                       发送文件地址
 ************************************************************/
void ftpClientDialog::setServerAddress(const QString &addr)
{
    serverAddress = addr;
}

/************************************************************
 函数名:                             setFileName
 功能:                               设置文件名
 传入参数 fileName:                   接受文件名
 ************************************************************/
void ftpClientDialog::setFileName(const QString &fileName)
{
	this->fileName = fileName;
}

/************************************************************
 函数名:                             getFileName
 功能:                               获得文件名
返回参数 :							接收文件名
 ************************************************************/
const QString &ftpClientDialog::getFileName() const
{
	return this->fileName;
}

/************************************************************
 函数名:                             slotRefuseFile
 功能:                               拒绝接收文件
 ************************************************************/
void ftpClientDialog::slotRefuseFile()
{
    emit(refuseFile(fileName));                                                     //发送拒绝接受文件信号
}

/************************************************************
 函数名:                             getServerAddress
 功能:                               获得发送文件地址
 ************************************************************/
const QString &ftpClientDialog::getServerAddress() const
{
	return serverAddress;
}

/************************************************************
 函数名:                             setFileSize
 功能:                               设置接受文件尺寸
 ************************************************************/
void ftpClientDialog::setFileSize(int fileSize)
{
	this->fileSize = fileSize;
}

/************************************************************
 函数名:                             getFileSize
 功能:                               获得接受文件尺寸
 ************************************************************/
int ftpClientDialog::getFileSize() const
{
	return fileSize;
}

ftpClientDialog::~ftpClientDialog()
{
	delete acceptButton;
	delete exitButton;
	delete actionLabel;

	delete hbLayout;
	delete vbLayout;

	delete tcpServer;
}
