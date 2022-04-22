#ifndef USERUI_H
#define USERUI_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QStackedWidget>
#include <QGroupBox>
#include <QMessageBox>
#include <QButtonGroup>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QtDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QValidator>
#include <QDateTime>
#include <QTcpServer>
#include <QTcpSocket>
#include <QBuffer>

#define ALLCHAT_PORT 10086

namespace Ui {
class UserUI;
}

class SocketServer;
class UserUI : public QWidget
{
    Q_OBJECT

public:
    explicit UserUI(QWidget *parent = nullptr);
    ~UserUI();

protected:
    //将用户信息添加到概况表中
    void AddUserInfo(QString Id,QString nickName,QString age,QString sex,QString groupInfo,
                     QString email,QString currentTime,QString lastLeaveTime);

public slots:
    void showUserSummaryWidget();                   //用户摘要页面槽函数
    void showCreateUserWidget();                    //创建用户页面槽函数
    void showSearchUserWidget();                    //搜索用户页面槽函数
    void showConfirmCreateUserBtn();                //确认新建用户槽函数
    void showCancelCreateUserBtn();                 //取消新建用户槽函数
    void showUserPersonInfo(int row,int column);    //通过点击用户iD展示个人信息
    void showUserPersonInfo();                      //展示用户个人属性信息
    void showUserPersonFriend();                    //展示用户好友信息
    void showUserPersonGroup();                     //展示用户群组信息
    void showUserPersonPassword();                  //展示用户密码信息
    void showUserPersonDeleted();                   //删除用户槽函数
    void showModifyPassword();                      //确认修改用户密码槽函数
    void showDeleteUser();                          //从用户概要表中删除用户
    void showDeleteFrd();                           //从用户好友列表中删除好友
private:
    Ui::UserUI *ui;

    QSqlQuery* sqlQuery;
    QString strUserId;

    //用户摘要
    QLabel *userSummaryLabel;                  //用户摘要按钮
    QPushButton *userSummaryBtn;               //用户摘要按钮
    QTableWidget *userSummaryTblWidget;        //用户摘要数据表格
    QComboBox *groupComBox;                    //群组信息

    //用户属性
    QGroupBox *userAtrbuteGroupBox;        //用户属性组合框
    QPushButton *userAtrbuteBtn;           //用户属性按钮
    QPushButton *userFrdListBtn;           //用户好友按钮
    QPushButton *userFrdGroupBtn;          //用户群按钮
    QPushButton *userPasswordBtn;          //用户密码按钮
    QPushButton *userDeleteBtn;            //删除用户按钮

    void updateUserTableWidet();           //刷新用户概况信息

    //用户个人属性
    QLabel *personInfoLabel=new QLabel("个人信息");
    QLabel *IdLabelInfo=new QLabel;
    QLabel *passwordLabelInfo=new QLabel;
    QLabel *nickNameLabelInfo=new QLabel;
    QLabel *signatureLabelInfo=new QLabel;
    QLabel *ageLabelInfo=new QLabel;
    QLabel *sexLabelInfo=new QLabel;
    QLabel *emailLabelInfo=new QLabel;
    QLabel *createTimeLabel=new QLabel("创建时间:");
    QLabel *createTimeLabelInfo=new QLabel;
    QLabel *lastLeaveTimeLabel=new QLabel("最近一次退出时间:");
    QLabel *lastLeaveTimeInfo=new QLabel;

    //修改密码
    QLabel *modifyPasswordLabel=new QLabel("修改密码");

    //创建用户
    QPushButton *createUserBtn;            //创建用户按钮

    //创建用户所需要的所有组件
    QLabel *createUserlabel;
    QLabel *IdLabel=new QLabel("用户ID：*");
    QLineEdit *IdLineEdit=new QLineEdit;
    QLabel *passwordLabel=new QLabel("密码：*");
    QLineEdit *passwordLineEdit=new QLineEdit;
    QLabel *paswdAgainLabel=new QLabel("确认密码: *");
    QLineEdit *paswdAgainLineEdit=new QLineEdit;
    QLabel *nickNameLabel=new QLabel("昵称：*");
    QLineEdit *nickNameLineEdit=new QLineEdit;
    QLabel *signatureLabel=new QLabel("个性签名：");
    QLineEdit *signatureLineEdit=new QLineEdit;
    QLabel *ageLabel=new QLabel("年龄：");
    QLineEdit *ageLineEdit=new QLineEdit;
    QLabel *sexLabel=new QLabel("性别：");
    QComboBox *sexComBox=new QComboBox;
    QLabel *emailLabel=new QLabel("电子邮件");
    QLineEdit *emailLineEdit=new QLineEdit;
    QPushButton *confirmBtn=new QPushButton("确认");
    QPushButton *cancelBtn=new QPushButton("取消");

    //用户好友列表
    QTableWidget *frdListTblWidget;
    //搜索用户
    QPushButton *searchUserBtn;            //搜索用户按钮

    //创建分页页面
    QStackedWidget *userStackWidget;
    QWidget *userSummaryWidget;            //用户摘要界面
    QWidget *userPersonInfoWidget;         //用户个人信息界面
    QWidget *userFrdListWidget;            //用户好友列表
    QWidget *createUserWidget;             //创建用户界面
    QWidget *modifyPasswordWidget;         //修改密码页面
    QWidget *deleteUserWidget;             //删除用户界面

    //服务器主界面用户信息界面左侧标签总体布局
    QVBoxLayout *userLeftVBoxLayout;

    //主布局
    QHBoxLayout *mainLayout;

    //socket信息
    QTcpSocket *m_tcpsocket;
    SocketServer *m_tcpserver;
    int count;

    QBuffer buffer;
    QSqlDatabase database;

private slots:
    void rcvUpdateState(int,QString);
    void rcvAddNewUser(QString,QString,QString,QString,QString);
};

#endif // USERUI_H
