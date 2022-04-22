/****************************************
文件名：ftpserverdialog.h
作者：梁庚
完成日期：2009.12.17
修改日期：2009.12.19
版本号：  1
*****************************************/
#ifndef FTPSERVERDIALOG_H
#define FTPSERVERDIALOG_H
#include <QFile>
#include <QLabel>
#include <QLayout>
#include <QDialog>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include "TcpThread.h"

/*******************************************************
 类名:                            FtpServerDialog
 继承类:                          QDialog
 功能:                            查找发送文件对话框
 *******************************************************/
class FtpServerDialog : public QDialog
{
    Q_OBJECT

public:

     FtpServerDialog(QWidget *parent = 0);
    ~FtpServerDialog();

    const QString & getUrl() const;                /*获取所选文件的绝对路径*/
    const QString & getServerAddress() const;      /*获取服务器IP*/
    void setServerAddress(const QString &addr);    /*设置服务器IP*/
    void setFileName();                            //设置文件名
    const QString &getFileName() const;            //获得文件名
    const QFile & getFile() const;                 //获得将要发送的文件信息

public slots:

    void slotsStartSend();                         /*发送文件槽*/
    void slotsOpenFile();                          /*获取文件路径*/
    void clearFileName();                          /*清除资源*/

signals:

    void sendFileMsg();                            /*发送文件信息信号*/

private:

    QFile file;                                    //将要发送文件
    QString url;                                   /*定义路径变量*/
    QString fileName;                              /*文件名*/
    QString serverAddress;                         /*定义IP变量*/

    QLabel *label;
    QLineEdit *lineEdit;                           /*显示文件绝对路径*/
    QPushButton *findButton;                       /*获取文件路径按钮*/
    QPushButton *closeButton;
    QPushButton *SendButton;                       /*发送文件按钮*/

    QVBoxLayout *leftLayout;                       /*图形界面布局管理器*/
    QHBoxLayout *mainLayout;
    QVBoxLayout *rightLayout;
    QHBoxLayout *topLeftLayout;

    QFileDialog *fileDialog;                       /*定义文件操作的类*/
    TcpThread tcpThread;                           /*传送文件线程*/
};


#endif // FTPSERVERDIALOG_H
