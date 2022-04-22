#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QGridLayout>
#include <QDebug>
#include <QValidator>
#include <QIODevice>
#include <QDataStream>
#include <QMessageBox>
#include <QDir>
#include <QProcess>
#include <QTcpSocket>
#include <QtNetwork>
#include <QNetworkInterface>
#include <QBuffer>
#include <QImageReader>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include "FriendList.h"
#include "RcvFIleDlg.h"
#include "Register.h"

#define ALLCHAT_PORT 8888

namespace Ui {
class loginDlg;
}

class loginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit loginDlg(QWidget *parent = nullptr);
    ~loginDlg();

    void sendMessgae(QByteArray data);          //向服务器发送消息
    QString dataDir;           //存放数据的目录
    FriendList *frdlist;       //好友列表界面对象
    Register *regstr;          //注册用户对话框
    RcvFIleDlg *rcvFileDlg;    //接收文件对话框

private:
    Ui::loginDlg *ui;

    QLabel *logInLabel;
    QLabel *IdLabel;
    QLineEdit *IdLineEdit;
    QLabel *pwdlabel;
    QLineEdit *pwdLineEdit;
    QLabel *domainNameLabel;
    QLineEdit *domainNameLineEdit;
    QCheckBox *rmbCheckBox;
    QLabel *rmbPwdlabel;
    QPushButton *logInBtn;
    QPushButton *cancelBtn;
    QPushButton *enrolNewBtn;   //注册新用户
    QHBoxLayout *buttonLayout;
    QGridLayout *mainLayout;

    QFile *rcvFile;
    qint64 fileSize;
    qint64 recvSize=0;
    QTcpSocket *m_tcpsocket;
    QString userId;
    QByteArray sendData;

    QSqlDatabase sqlLiteDb;    //数据库
    QSqlQuery *sqlQuery;

    QString getIp();
    int clientPort;

signals:
    void disconnectToserver();
    void rcvFileCompeteSignal(int);
    void processSignal(qint64);

public slots:
    void tcpConnectedToServer();
    void tcpDisConnected();
    void tcpReadyRead();

private slots:
    void showLogInBtn();
    void showCancelBtn();
    void showRegsiterNewBtn();
};

#endif // LOGINDLG_H
