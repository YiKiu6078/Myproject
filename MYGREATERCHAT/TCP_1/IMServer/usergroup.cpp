#include "usergroup.h"
#include "ui_usergroup.h"

UserGroup::UserGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserGroup)
{
    ui->setupUi(this);
    ConnectToDatabase();

    stackWidget=new QStackedWidget;

    groupSummaryBtn=new QPushButton("用户群摘要");
    connect(groupSummaryBtn,SIGNAL(clicked()),
            this,SLOT(showGroupSummaryWidget()));
    createGroupBtn=new QPushButton("新建用户群");

    groupOptionsBox=new QGroupBox;
    groupOptionsBox->setTitle("用户群选项");
    personOfGroupBtn=new QPushButton("用户群成员");
    deleteGroupBtn=new QPushButton("删除用户群");
    groupOptionsBox->setVisible(false);
    QVBoxLayout *optionsLayout=new QVBoxLayout;
    optionsLayout->addWidget(personOfGroupBtn);
    optionsLayout->addWidget(deleteGroupBtn);
    optionsLayout->addStretch();
    groupOptionsBox->setLayout(optionsLayout);

    //左侧列表框
    QVBoxLayout *leftBtnLayout=new QVBoxLayout;
    leftBtnLayout->addWidget(groupSummaryBtn);
    leftBtnLayout->addWidget(groupOptionsBox);
    leftBtnLayout->addWidget(createGroupBtn);
    leftBtnLayout->addStretch();
    //用户群数据表格
    groupSummaryTbWdgt=new QTableWidget;
    QStringList strGroupListHeader;              //用户摘要数据表头
    strGroupListHeader<<"用户群ID"<<"群聊名称"<<"头像存储位置"<<"创建时间"<<"删除";
    groupSummaryTbWdgt->setHorizontalHeaderLabels(strGroupListHeader);
    groupSummaryTbWdgt->setColumnCount(5);
    groupSummaryTbWdgt->setColumnWidth(1,150);
    groupSummaryTbWdgt->setColumnWidth(2,350);
    groupSummaryTbWdgt->setColumnWidth(3,200);
    QString sqlStr="select ID,名称,头像存储位置,创建时间 from userGroupList";
    sqlQuery->prepare(sqlStr);
    if(sqlQuery->exec())
    {
       //读取查询到的记录
       while(sqlQuery->next())
       {
           int rowCount=groupSummaryTbWdgt->rowCount();
           groupSummaryTbWdgt->insertRow(rowCount);
           //ID信息
           groupSummaryTbWdgt->setItem(rowCount, 0, new QTableWidgetItem(sqlQuery->value(0).toString()));
           //名称
           QTableWidgetItem *nickNameItem = new QTableWidgetItem(sqlQuery->value(1).toString());
           groupSummaryTbWdgt->setItem(rowCount,1,nickNameItem);
           nickNameItem->setFlags(nickNameItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
           //头像存储信息
           QTableWidgetItem *headImgItem = new QTableWidgetItem(sqlQuery->value(2).toString());
           groupSummaryTbWdgt->setItem(rowCount,2,headImgItem);
           headImgItem->setFlags(headImgItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
           //创建时间
           QTableWidgetItem *createDateItem = new QTableWidgetItem(sqlQuery->value(3).toString());
           groupSummaryTbWdgt->setItem(rowCount,3,createDateItem);
           createDateItem->setFlags(createDateItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
           //删除
           QPushButton *deleteBtn=new QPushButton;
           deleteBtn->setStyleSheet("border:none");
           deleteBtn->setToolTip("删除");
           deleteBtn->setIcon(QIcon(QPixmap(":/Img/image/delete.jpg")));
           groupSummaryTbWdgt->setCellWidget(rowCount,4,deleteBtn);
       }
    }
    connect(groupSummaryTbWdgt,SIGNAL(cellDoubleClicked(int,int)),
            this,SLOT(showGroupListInfo(int,int)));
    QHBoxLayout* groupSumaryLayout=new QHBoxLayout;
    groupSumaryLayout->addWidget(groupSummaryTbWdgt);
    groupSummaryWidget=new QWidget;
    groupSummaryWidget->setLayout(groupSumaryLayout);
    stackWidget->addWidget(groupSummaryWidget);

    mainLayout=new QHBoxLayout(this);
    mainLayout->addLayout(leftBtnLayout);
    mainLayout->addWidget(stackWidget);
}

//连接到数据库
void UserGroup::ConnectToDatabase()
{
    //连接mysql数据库
    if(QSqlDatabase::contains("qt_sql_default_connection")){
      database = QSqlDatabase::database("qt_sql_default_connection");
    } else{
      database = QSqlDatabase::addDatabase("QMYSQL");
    }
    database.setUserName("root");
    database.setHostName("localhost");
    database.setPassword("1");
    database.setDatabaseName("IMSERVER");
    if(!database.open()){
        QMessageBox::critical(nullptr, QObject::tr("Databse Error"), database.lastError().text());
               qDebug()<<database.lastError()<<endl;
               qDebug()<<"Open mysql database failed！"<<endl;
    }
    //读取数据库中的用户概要信息，将其显示在tablewidget中
    sqlQuery=new QSqlQuery;
}

void UserGroup::showGroupSummaryWidget()
{
    groupOptionsBox->setVisible(false);
    stackWidget->setCurrentWidget(groupSummaryWidget);
}

void UserGroup::showGroupListInfo(int row,int colunm)
{
    groupOptionsBox->setVisible(true);
    groupId=groupSummaryTbWdgt->item(row,colunm)->text();
    connect(personOfGroupBtn,SIGNAL(clicked()),
            this,SLOT(showPersonOfGroup()));
    connect(deleteGroupBtn,SIGNAL(clicked()),
            this,SLOT(showDeleteOfGroup()));
}

void UserGroup::showPersonOfGroup()
{
    //用户好友列表
    userListTblWidget=new QTableWidget;
    userListTblWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);       //不可编辑
    userListTblWidget->setColumnCount(2);
    QStringList strUserListHeader;              //用户摘要数据表头
    strUserListHeader<<"成员ID"<<"删除";
    userListTblWidget->setHorizontalHeaderLabels(strUserListHeader);
    sqlQuery->prepare("select * from " + groupId + "GroupUserList");
    if(sqlQuery->exec())
    {
       //读取查询到的记录
       while(sqlQuery->next())
       {
           int rowCount=userListTblWidget->rowCount();
           userListTblWidget->insertRow(rowCount);
           //好友ID
           QTableWidgetItem *userIdItem = new QTableWidgetItem(sqlQuery->value(0).toString());
           userListTblWidget->setItem(rowCount,0,userIdItem);
           userIdItem->setFlags(userIdItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
           //删除
           QPushButton *deleteBtn=new QPushButton;
           deleteBtn->setStyleSheet("border:none");
           deleteBtn->setToolTip("删除");
           deleteBtn->setIcon(QIcon(QPixmap(":/Img/image/delete.jpg")));
           userListTblWidget->setCellWidget(rowCount,1,deleteBtn);

       }
    }
    //布局管理
    QHBoxLayout *userListLayout=new QHBoxLayout;
    userListLayout->addWidget(userListTblWidget);
    userListWidget=new QWidget;
    //userListWidget->setMaximumSize(350,400);
    userListWidget->setLayout(userListLayout);
    stackWidget->addWidget(userListWidget);
    stackWidget->setCurrentWidget(userListWidget);
}


void UserGroup::showDeleteOfGroup()
{
    QLabel *deleteLabel=new QLabel("确认删除该群组？");
    QFont labelFont;
    labelFont.setPointSize(16);
    deleteLabel->setFont(labelFont);
    QGridLayout *layout=new QGridLayout;
    layout->addWidget(deleteLabel,0,0,1,2);
    QPushButton *confirmBtn=new QPushButton("确认");
    QPushButton *cancelBtn=new QPushButton("取消");
    layout->addWidget(confirmBtn,1,0);
    layout->addWidget(cancelBtn,1,1);

    QWidget* deleteGroupWidget=new QWidget;
    deleteGroupWidget->setMaximumSize(200,200);
    deleteGroupWidget->setLayout(layout);
    stackWidget->addWidget(deleteGroupWidget);
    stackWidget->setCurrentWidget(deleteGroupWidget);
}

void UserGroup::showCreateGeoupsWidget()
{

}

UserGroup::~UserGroup()
{
    delete ui;
}
