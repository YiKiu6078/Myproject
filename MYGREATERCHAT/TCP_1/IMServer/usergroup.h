#ifndef USERGROUP_H
#define USERGROUP_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QGroupBox>
#include <QComboBox>
#include <QWidget>
#include <QLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class UserGroup;
}

class UserGroup : public QWidget
{
    Q_OBJECT

public:
    explicit UserGroup(QWidget *parent = nullptr);
    ~UserGroup();

public slots:
    void showGroupSummaryWidget();
    void showPersonOfGroup();
    void showCreateGeoupsWidget();
    void showGroupListInfo(int,int);        //展示用户群成员信息
    void showDeleteOfGroup();               //删除群组
private:
    Ui::UserGroup *ui;

    QString groupId;
    QSqlDatabase database;
    QSqlQuery *sqlQuery;
    QStackedWidget *stackWidget;
    //用户群
    QPushButton *groupSummaryBtn;           //用户群摘要按钮
    QGroupBox *groupOptionsBox;             //用户群选项按钮
    QPushButton *personOfGroupBtn;              //编辑用户群按钮
    QPushButton *deleteGroupBtn;            //删除用户群按钮
    QPushButton *createGroupBtn;            //创建用户群按钮

    //用户群摘要
    QLabel *groupSummaryLabel;              //用户群摘要标签
    QTableWidget *groupSummaryTbWdgt;       //用户群组信息
    QComboBox *memberCombox;                //用户群成员信息

    QWidget *groupSummaryWidget;
    QHBoxLayout *mainLayout;

    QTableWidget *userListTblWidget;        //用户群成员
    QWidget *userListWidget;
    void ConnectToDatabase();
};

#endif // USERGROUP_H
