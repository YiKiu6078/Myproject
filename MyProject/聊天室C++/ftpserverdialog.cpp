/***********************************************
  文件名：ftpserverdialog.cpp
  作者：梁庚
  功能：实现服务器的功能
  完成日期：2009.12.17
  修改日期：2009.12.19
  版本号：01
  ***********************************************/


#include <QDir>
#include <QFileDialog>
#include <QProgressDialog>
#include <QApplication>
#include <QMessageBox>
#include "ftpserverdialog.h"

/**************************************************
  函数名：					FtpServerDialog
  功能：					构造所需类，实现文件发送界面
                                                和信号与槽的连接
****************************************************/
FtpServerDialog::FtpServerDialog(QWidget *parent)
    : QDialog(parent)
{
    /*******************初始化所有窗口部件********************/
    label = new QLabel(QString::fromUtf8("目标文件名:"));
    lineEdit = new QLineEdit;
    findButton = new QPushButton(QString::fromUtf8("浏览"));
    closeButton = new QPushButton(QString::fromUtf8("关闭"));
    SendButton = new QPushButton(QString::fromUtf8("发送"));
    SendButton->setEnabled(false);

    /**********************绑定信号与槽************************/

    connect(SendButton, SIGNAL(clicked()), this, SLOT(slotsStartSend()));
    connect(SendButton, SIGNAL(clicked()), this, SLOT(clearFileName()));
    connect(SendButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(findButton, SIGNAL(clicked()), this, SLOT(slotsOpenFile()));

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(clearFileName()));

    /**********************对窗口部件进行布局*********************/
    topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(SendButton);

    rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(QString::fromUtf8("请选择发送的文件!"));
    setFixedHeight(sizeHint().height());

    fileDialog = new QFileDialog(this, Qt::Dialog); 						/*定义文件操作对象*/
}

/*****************************************************
  函数名：					getServerAddress
  功能：					获取本地IP
  参数：					需要设置的IP
  返回值：					本地IP
  ****************************************************/
const QString & FtpServerDialog::getServerAddress() const
{
       return serverAddress;
}


/*****************************************************
  函数名：					setServerAddress
  功能：					获取本地IP
  参数：					需要设置的IP
  返回值：					本地IP
  ****************************************************/
void FtpServerDialog::setServerAddress(const QString &addr)
{
    serverAddress = addr;
}

/*******************************************************
   函数名：				getUrl
   功能：					返回所选文件路径
  ******************************************************/
const QString &FtpServerDialog::getUrl() const
{
    return url;
}

/*******************************************************
   函数名：				slotsOpenFile
   功能：					获取所选文件路径
  ******************************************************/
void FtpServerDialog::slotsOpenFile()
{
   QString initialName = lineEdit->text();
   QString fileName = fileDialog->getOpenFileName(this,
                                   tr("Choose File"),"/home");
   url = fileName;
   lineEdit->setText(fileName);
   SendButton->setEnabled(true);

   file.setFileName(url);
}

/*****************************************************
 函数名：					slotsStartSend
 功能：					实现进度条展示
 ******************************************************/
void FtpServerDialog::slotsStartSend()
{
	tcpThread.setHostName(serverAddress);                              /*设置传送文件主机IP地址*/
	tcpThread.setFileUrl(url);                                         /*设置将要传送文件名*/
	setFileName();                                                     /*设置文件名*/
	emit(sendFileMsg());                                               /*发送文件信号*/
}

/*****************************************************
 函数名：					～FtpServerDialog
 功能：					 释放资源
 ******************************************************/
FtpServerDialog::~FtpServerDialog()
{
	delete label;
	delete lineEdit;
	delete SendButton;
	delete fileDialog;
	delete findButton;
	delete closeButton;

	delete mainLayout;
	delete leftLayout;
	delete rightLayout;
	delete topLeftLayout;
}

/*****************************************************
 函数名:                   setFileName
 功能:                     设置文件名
******************************************************/
void FtpServerDialog::setFileName()
{
	QString str = "/";                                                //文件路径中目录分割符
	int num = url.lastIndexOf(str) + 1;                               //获得最后一个目录
	int size = url.size();                                            //获得文件尺寸
	int len = size - num;                                             //获得文件名长度
	fileName = url.right(len);                                        //获得文件名
}

/*****************************************************
 函数名:                    getFileName
 功能:                      获得文件名
******************************************************/
const QString &FtpServerDialog::getFileName() const
{
	return fileName;
}

/*****************************************************
 函数名:                    clearFileName
 功能:                      清除文件名
******************************************************/
void FtpServerDialog::clearFileName()
{
	lineEdit->clear();
}

/*****************************************************
 函数名:                    getFile
 功能:                      获得将要发送的文件信息
 返回值:                    将要返回的文件对象引用
******************************************************/
const QFile & FtpServerDialog::getFile() const
{
	return file;
}
