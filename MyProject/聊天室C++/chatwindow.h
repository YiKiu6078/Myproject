/*********************************************************
Copyright (c), 2009-2019,           程凡凡
filename:                           chatwindow.h
author:                             程凡凡
function:                           Create a Qt window,use
                                    for chat.
version:                            version1
finish date:                        2009/12/14
modification date:
modification list:
***********************************************************/

#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QtGui>
#include <QVBoxLayout>
#include <QTextCursor>
#include <QUdpSocket>
#include <QSqlDatabase>
#include <QTextCharFormat>
#include "User.h"
#include "shareData.h"
#include "ftpserverdialog.h"

/*******************************************************
 类名:                           ChatWindow
 功能:                           主要显示聊天窗口继承于QDialog
 *******************************************************/

class ChatWindow : public QDialog
{
    Q_OBJECT

public:

    User me;									//本地用户
    User user;  								//当前用户

    QPushButton *closeLog;						//关闭按钮
    QPushButton *clearLog;                      //清除聊天记录按钮
    QHBoxLayout *logHLayout;
    QTextEdit *logEdit;                         //编辑框
    QDialog *chatLogWnd;
    FtpServerDialog *ftpServer;                 //发送文件窗口
    QUdpSocket *udpsocket;                      //发送消息

    QTextCharFormat format;
    QVBoxLayout *logLayout;						//布局管理器
    QHBoxLayout *baseLayout;
    QHBoxLayout *midLayout;
    QHBoxLayout *mainLayout;
    QGridLayout *gridLayout;
    QGridLayout *infoLayout;
    QHBoxLayout *hBoxLayout;

    QLabel *title;								//个人信息
    QLabel *headName;
    QLabel *userName;
    QLabel *hostName;
    QLabel *write;
    QLabel *ip;

    QLabel *labelUserName;
    QLabel *labelHead;
    QLabel *labelHostName;
    QLabel *labelWrite;
    QLabel *labelIp;

    QTextEdit *textEdit_receive;                //接收信息框
    QTextEdit *textEdit_send;                   //发送消息框

    QPushButton *pushButton_log;                //显示聊天记录
    QPushButton *pushButton_sendMessage;        //发送消息
    QPushButton *pushButton_close;              //关闭聊天窗口
    QPushButton *pushButton_sendFile;

    QLabel *label_font;
    QLabel *label_size;

    QFontComboBox *comboBox_font;               //设置字体

    QComboBox *comboBox_size;                   //设置字体大小
    QToolButton *toolButton_color;              //设置字体颜色
    QToolButton *toolButton_bold;               //设置粗体
    QToolButton *toolButton_italic;             //设置斜体
    QToolButton *toolButton_underline;          //设置下划线


public:

    ChatWindow(const User &me, const User &user, QWidget * parent = 0);            //构造函数
    ~ChatWindow();                                                 //析构函数
    QString paresLog(QString &tmpLog);                             //解析聊天记录
    void creatLogWindow();                                         //创建聊天记录窗口
    void mergeFormat(QTextCharFormat);
    bool CheckMsg(QString);                                        //对消息的检查
    void message_show(const QString &msg,
                      QString sender = NULL);                      //显示收到的消息，添加相应的时间和发送人。
    const FtpServerDialog *getFileDialog() const;                  //获得文件对话框句柄
    void setSendFileButton(bool isEnable = true);                  //设置发送文件按钮
    void setMeInfo(const User &me);

signals:

    void currentFontSize(QString);

protected:

    virtual  void closeEvent ( QCloseEvent * event );           //聊天窗口被关闭消息函数

public slots:                                   //槽函数

    void clearChat();                           //清除聊天窗口信息
    void closeLogWnd();                         //关闭聊天记录窗口
    void clearChatLog();                        //清除聊天记录
    void slotExtension();                       //显示聊天窗口
    void slotWriteLog();                        //查看聊天记录
    void slotSendFile();
    void slotFont(QString);
    void slotSize(QString);
    void slotBold();
    void slotItalic();
    void slotUnder();
    void slotColor();
    void slotCurrentCharFormatChanged(const QTextCharFormat &fmt);
    void slotsendmsg();
    void sendFileMsg();                         //发送文件信息
};

#endif // CHATWINDOW_H
