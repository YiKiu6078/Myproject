#ifndef FTPCLIENTDIALOG_H
#define FTPCLIENTDIALOG_H

#include <QFile>
#include <QLabel>
#include <QDialog>
#include <QLayout>
#include <QString>
#include <QLineEdit>
#include <QPushButton>
#include "TcpServer.h"

/*******************************************************
 类名:                           ftpClientDialog
 继承类:                          QDialog
 功能:                            文件到达时对话框
 *******************************************************/

class ftpClientDialog : public QDialog
{
    Q_OBJECT

public:

    ftpClientDialog(QWidget *parent = 0);
    ~ftpClientDialog();

    void setServerAddress(const QString &addr);                                    //设置发送方地址
    const QString &getServerAddress() const;                                       //获得发送方IP地址
    void setFileName(const QString &fileName);                                     //设置发送文件名
    const QString &getFileName() const;                                            //获得发送文件名
    void setFileSize(int fileSize);                                                //设置发送文件的尺寸
    int getFileSize() const;                                                       //获得发送文件的尺寸

signals:

    void acceptFile(const QString &);                                              //接受文件信号
    void refuseFile(const QString &);                                              //拒绝接受文件信号

public slots:

    void slotsgetFile();														   //接受文件槽
    void slotRefuseFile();														   //拒绝文件槽

private:

    int fileSize;															       //文件尺寸
    QString serverAddress;														   //发送文件地址
    QString fileName;															   //文件名

    QLabel* actionLabel;
    QPushButton* closeButton;													   //关闭按钮
    QPushButton* acceptButton;                                                     //接受按钮
    QPushButton* exitButton;													   //退出按钮

    QHBoxLayout *hbLayout;														   //布局管理器
    QVBoxLayout *vbLayout;
    TcpServer *tcpServer;                                                          //服务器
};

#endif // FTPCLIENTDIALOG_H
