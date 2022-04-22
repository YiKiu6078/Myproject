#include "userui.h"
#include "ui_userui.h"
#include "socketserver.h"

UserUI::UserUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserUI)
{
    ui->setupUi(this);

    m_tcpserver = new SocketServer(this);
    m_tcpserver->listen(QHostAddress::Any,ALLCHAT_PORT);
    //用户摘要
    userSummaryBtn=new QPushButton;
    userSummaryBtn->setText(tr("用户摘要"));

    //用户属性组合框
    userAtrbuteGroupBox=new QGroupBox;
    userAtrbuteGroupBox->setTitle("用户属性");
    userAtrbuteBtn=new QPushButton("用户属性");
    userFrdListBtn=new QPushButton("用户好友");
    userFrdGroupBtn=new QPushButton("用户群组");
    userPasswordBtn=new QPushButton("修改密码");
    userDeleteBtn=new QPushButton("删除用户");

    QVBoxLayout* userAtrbuteVbLayout=new QVBoxLayout;
    userAtrbuteVbLayout->addWidget(userAtrbuteBtn);
    userAtrbuteVbLayout->addWidget(userFrdListBtn);
    userAtrbuteVbLayout->addWidget(userFrdGroupBtn);
    userAtrbuteVbLayout->addWidget(userPasswordBtn);
    userAtrbuteVbLayout->addWidget(userDeleteBtn);
    userAtrbuteVbLayout->addStretch();
    userAtrbuteGroupBox->setLayout(userAtrbuteVbLayout);
    //设置用户属性列表框隐藏，当在用户概要信息点击时在弹出
    userAtrbuteGroupBox->setVisible(false);
    //创建用户
    createUserBtn=new QPushButton("创建用户");
    sexComBox->addItem("男");
    sexComBox->addItem("女");

    //搜索用户
    searchUserBtn=new QPushButton("搜索用户");

    //左侧布局
    userLeftVBoxLayout=new QVBoxLayout;
    userLeftVBoxLayout->addWidget(userSummaryBtn);
    userLeftVBoxLayout->addWidget(userAtrbuteGroupBox);
    userLeftVBoxLayout->addWidget(createUserBtn);
    userLeftVBoxLayout->addWidget(searchUserBtn);
    userLeftVBoxLayout->addStretch();

    connect(userSummaryBtn,&QPushButton::clicked,this,&UserUI::showUserSummaryWidget);
    connect(createUserBtn,&QPushButton::clicked,this,&UserUI::showCreateUserWidget);
    connect(searchUserBtn,&QPushButton::clicked,this,&UserUI::showSearchUserWidget);

    //创建右侧页面
    userStackWidget=new QStackedWidget;

    //用户摘要按钮页面
    userSummaryLabel=new QLabel;
    userSummaryLabel->setText(tr("用户摘要"));
    userSummaryTblWidget=new QTableWidget;
    userSummaryTblWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);       //不可编辑
    userSummaryTblWidget->setColumnCount(10);
    QStringList strListHeader;              //用户摘要数据表头
    strListHeader<<"状态"<<"用户ID"<<"昵称"<<"年龄"<<"性别"<<"电子邮件"
                <<"用户群"<<"创建时间"<<"最近一次退出时间"<<"删除";
    userSummaryTblWidget->setColumnWidth(0,60);
    userSummaryTblWidget->setColumnWidth(1,90);
    userSummaryTblWidget->setColumnWidth(2,140);
    userSummaryTblWidget->setColumnWidth(3,40);
    userSummaryTblWidget->setColumnWidth(4,40);
    userSummaryTblWidget->setColumnWidth(5,160);
    userSummaryTblWidget->setColumnWidth(6,130);
    userSummaryTblWidget->setColumnWidth(7,180);
    userSummaryTblWidget->setColumnWidth(8,180);
    userSummaryTblWidget->setColumnWidth(9,40);
    userSummaryTblWidget->setHorizontalHeaderLabels(strListHeader);
    //连接mysql数据库
    if(QSqlDatabase::contains("qt_sql_default_connection")){
      database = QSqlDatabase::database("qt_sql_default_connection");
    } else{
      database = QSqlDatabase::addDatabase("QMYSQL");
    }
    database.setUserName("root");
    database.setHostName("localhost");
    database.setDatabaseName("IMSERVER");
    if(!database.open()){
        QMessageBox::critical(nullptr, QObject::tr("Databse Error"), database.lastError().text());
               qDebug()<<database.lastError()<<endl;
               qDebug()<<"Open mysql database failed！"<<endl;
    }
    //读取数据库中的用户概要信息，将其显示在tablewidget中
    sqlQuery=new QSqlQuery;
    updateUserTableWidet();
    //为ID列添加槽函数
    connect(userSummaryTblWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(showUserPersonInfo(int,int)));
    QHBoxLayout* userSumaryLayout=new QHBoxLayout;
    userSumaryLayout->addWidget(userSummaryTblWidget);
    userSummaryWidget=new QWidget;
    userSummaryWidget->setLayout(userSumaryLayout);
    userStackWidget->addWidget(userSummaryWidget);

    mainLayout=new QHBoxLayout(this);
    mainLayout->addLayout(userLeftVBoxLayout);
    mainLayout->addWidget(userStackWidget);

    connect(m_tcpserver,SIGNAL(updateState(int,QString)),this,SLOT(rcvUpdateState(int,QString)));
    connect(m_tcpserver,SIGNAL(addNewUser(QString, QString, QString, QString, QString)),
            this,SLOT(rcvAddNewUser(QString,QString,QString,QString,QString)));
}

//刷新用户摘要信息
void UserUI::updateUserTableWidet()
{
    QString sqlStr="select ID,密码,昵称,个性签名,年龄,性别,头像存储位置,群组信息,电子邮件,创建时间,最近一次退出 from userGenerInfo";
    sqlQuery->prepare(sqlStr);
    if(sqlQuery->exec())
    {
       //读取查询到的记录
       while(sqlQuery->next())
       {
           AddUserInfo(sqlQuery->value(0).toString(),sqlQuery->value(2).toString(),sqlQuery->value(4).toString(),
                       sqlQuery->value(5).toString(),sqlQuery->value(7).toString(),sqlQuery->value(8).toString(),sqlQuery->value(9).toString(),
                       sqlQuery->value(10).toString());
       }
    }
    sqlQuery->exec(sqlStr);
}

//展示用户摘要信息表槽函数
void UserUI::showUserSummaryWidget()
{
    userAtrbuteGroupBox->setVisible(false);
    userStackWidget->setCurrentWidget(userSummaryWidget);
}

//点击用户iD展示个人信息槽函数
void UserUI::showUserPersonInfo(int row,int column)
{
    userAtrbuteGroupBox->setVisible(true);
    strUserId=userSummaryTblWidget->item(row,column)->text();
    connect(userAtrbuteBtn,SIGNAL(clicked()),this,SLOT(showUserPersonInfo()));
    connect(userFrdListBtn,SIGNAL(clicked()),this,SLOT(showUserPersonFriend()));
    connect(userFrdGroupBtn,SIGNAL(clicked()),this,SLOT(showUserPersonGroup()));
    connect(userPasswordBtn,SIGNAL(clicked()),this,SLOT(showUserPersonPassword()));
    connect(userDeleteBtn,SIGNAL(clicked()),this,SLOT(showUserPersonDeleted()));
}

//展示用户个人详细信息槽函数
void UserUI::showUserPersonInfo()
{
    sqlQuery->prepare("select * from userGenerInfo where ID=:strUserId");
    sqlQuery->bindValue(":strUserId",strUserId);
    sqlQuery->exec();
    if(sqlQuery->first()){
        IdLabelInfo->setText(sqlQuery->value(0).toString());
        passwordLabelInfo->setText(sqlQuery->value(1).toString());
        nickNameLabelInfo->setText(sqlQuery->value(2).toString());
        signatureLabelInfo->setText(sqlQuery->value(3).toString());
        ageLabelInfo->setText(sqlQuery->value(4).toString());
        sexLabelInfo->setText(sqlQuery->value(5).toString());
        emailLabelInfo->setText(sqlQuery->value(8).toString());
        createTimeLabelInfo->setText(sqlQuery->value(9).toString());
        if(sqlQuery->value(10).toString()!=""){
            lastLeaveTimeInfo->setText(sqlQuery->value(10).toString());
        } else {
            lastLeaveTimeInfo->setText("从未登录");
        }
    }
    //网格布局管理
    QGridLayout *userPersonInfoLayout=new QGridLayout;
    userPersonInfoLayout->addWidget(personInfoLabel,0,0);
    userPersonInfoLayout->addWidget(IdLabel,1,0);
    userPersonInfoLayout->addWidget(IdLabelInfo,1,1);
    userPersonInfoLayout->addWidget(passwordLabel,2,0);
    userPersonInfoLayout->addWidget(passwordLabelInfo,2,1);
    userPersonInfoLayout->addWidget(nickNameLabel,3,0);
    userPersonInfoLayout->addWidget(nickNameLabelInfo,3,1);
    userPersonInfoLayout->addWidget(signatureLabel,4,0);
    userPersonInfoLayout->addWidget(signatureLabelInfo,4,1);
    userPersonInfoLayout->addWidget(ageLabel,5,0);
    userPersonInfoLayout->addWidget(ageLabelInfo,5,1);
    userPersonInfoLayout->addWidget(sexLabel,6,0);
    userPersonInfoLayout->addWidget(sexLabelInfo,6,1);
    userPersonInfoLayout->addWidget(emailLabel,7,0);
    userPersonInfoLayout->addWidget(emailLabelInfo,7,1);
    userPersonInfoLayout->addWidget(createTimeLabel,8,0);
    userPersonInfoLayout->addWidget(createTimeLabelInfo,8,1);
    userPersonInfoLayout->addWidget(lastLeaveTimeLabel,9,0);
    userPersonInfoLayout->addWidget(lastLeaveTimeInfo,9,1);

    userPersonInfoWidget=new QWidget;
    userPersonInfoWidget->setMaximumSize(350,400);
    userPersonInfoWidget->setLayout(userPersonInfoLayout);
    userStackWidget->addWidget(userPersonInfoWidget);
    userStackWidget->setCurrentWidget(userPersonInfoWidget);
}

//展示用户好友信息槽函数
void UserUI::showUserPersonFriend()
{
    //用户好友列表
    frdListTblWidget=new QTableWidget;
    frdListTblWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);       //不可编辑
    frdListTblWidget->setColumnCount(3);
    QStringList strFrdListHeader;              //用户摘要数据表头
    strFrdListHeader<<"好友ID"<<"分组信息"<<"删除";
    frdListTblWidget->setHorizontalHeaderLabels(strFrdListHeader);
    sqlQuery->prepare("select * from " + strUserId + "FriendList");
    if(sqlQuery->exec())
    {
       //读取查询到的记录
       while(sqlQuery->next())
       {
           int rowCount=frdListTblWidget->rowCount();
           frdListTblWidget->insertRow(rowCount);
           //好友ID
           QTableWidgetItem *frdIdItem = new QTableWidgetItem(sqlQuery->value(0).toString());
           frdListTblWidget->setItem(rowCount,0,frdIdItem);
           frdIdItem->setFlags(frdIdItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
           //分组
           QTableWidgetItem *frdGroupItem = new QTableWidgetItem(sqlQuery->value(1).toString());
           frdListTblWidget->setItem(rowCount,1,frdGroupItem);
           frdGroupItem->setFlags(frdGroupItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
           //删除
           QPushButton *deleteBtn=new QPushButton;
           deleteBtn->setStyleSheet("border:none");
           deleteBtn->setToolTip("删除");
           deleteBtn->setIcon(QIcon(QPixmap(":/Img/image/delete.jpg")));
           frdListTblWidget->setCellWidget(rowCount,2,deleteBtn);

           connect(deleteBtn,SIGNAL(clicked()),this,SLOT(showDeleteFrd()));
       }
    }
    //布局管理
    QHBoxLayout *frdListLayout=new QHBoxLayout;
    frdListLayout->addWidget(frdListTblWidget);

    userFrdListWidget=new QWidget;
    userFrdListWidget->setMaximumSize(350,400);
    userFrdListWidget->setLayout(frdListLayout);
    userStackWidget->addWidget(userFrdListWidget);
    userStackWidget->setCurrentWidget(userFrdListWidget);
}

//从用户好友列表中删除好友
void UserUI::showDeleteFrd()
{
    int currentRow=frdListTblWidget->currentRow();
    if(currentRow != -1) {
        QString selectFrdId=frdListTblWidget->item(currentRow,0)->text();
        if(QMessageBox::question(this,tr("提示"),QString("确定删除好友 %1 ？").arg(selectFrdId),
                                 QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes) {
            sqlQuery->prepare("delete from " + strUserId + "FriendList where ID='"+ selectFrdId + "'");
            sqlQuery->exec();
            frdListTblWidget->removeRow(currentRow);
        }
    }
}

//展示用户群组信息
void UserUI::showUserPersonGroup()
{

}

//展示用户密码信息
void UserUI::showUserPersonPassword()
{
    passwordLineEdit->clear();
    paswdAgainLineEdit->clear();
    passwordLineEdit->setMaxLength(8);
    paswdAgainLineEdit->setMaxLength(8);
    //隐藏密码
    passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    paswdAgainLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    QFont labelFont;
    labelFont.setPointSize(20);
    modifyPasswordLabel->setFont(labelFont);
    QGridLayout *passwordLayout=new QGridLayout;
    passwordLayout->addWidget(modifyPasswordLabel,0,0);
    passwordLayout->addWidget(passwordLabel,1,0);
    passwordLayout->addWidget(passwordLineEdit,1,1);
    passwordLayout->addWidget(paswdAgainLabel,2,0);
    passwordLayout->addWidget(paswdAgainLineEdit,2,1);
    //将确认和取消按钮加入另一个布局中
    QHBoxLayout *btnLayout=new QHBoxLayout;
    btnLayout->addWidget(confirmBtn);
    btnLayout->addWidget(cancelBtn);

    connect(confirmBtn,&QPushButton::clicked,this,&UserUI::showModifyPassword);
    connect(cancelBtn,&QPushButton::clicked,this,&UserUI::showCancelCreateUserBtn);
    //将不同的布局放入整体布局
    QVBoxLayout *layout=new QVBoxLayout;
    layout->addLayout(passwordLayout);
    layout->addLayout(btnLayout);

    modifyPasswordWidget=new QWidget;
    modifyPasswordWidget->setMaximumSize(300,300);
    modifyPasswordWidget->setLayout(layout);
    userStackWidget->addWidget(modifyPasswordWidget);
    userStackWidget->setCurrentWidget(modifyPasswordWidget);
}

//确认修改用户密码槽函数
void UserUI::showModifyPassword()
{
    if(passwordLineEdit->text().length()==0 || passwordLineEdit->text()!=paswdAgainLineEdit->text()){
        QMessageBox::information(nullptr, "警告", "两次密码不一致且密码不能为空！",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    } else {
        QString strModifyPassword="update userGenerInfo set 密码=:password where ID=:userId";
        sqlQuery->prepare(strModifyPassword);
        sqlQuery->bindValue(":password",passwordLineEdit->text());
        sqlQuery->bindValue(":userId",strUserId);
        if(!sqlQuery->exec()){
            QMessageBox::information(this,tr("警告"),tr("修改密码失败，请重试！"));
            qDebug()<<"sqlQuery error :"<<sqlQuery->lastError();
        }else{
            QMessageBox::information(this,tr("提示"),tr("修改密码成功！"));
        }
    }
}

//删除用户槽函数
void UserUI::showUserPersonDeleted()
{
    QLabel *deleteLabel=new QLabel("确认删除该用户？");
    QFont labelFont;
    labelFont.setPointSize(16);
    deleteLabel->setFont(labelFont);
    QGridLayout *layout=new QGridLayout;
    layout->addWidget(deleteLabel,0,0,1,2);
    layout->addWidget(confirmBtn,1,0);
    layout->addWidget(cancelBtn,1,1);

    connect(cancelBtn,&QPushButton::clicked,this,&UserUI::showCancelCreateUserBtn);

    deleteUserWidget=new QWidget;
    deleteUserWidget->setMaximumSize(200,200);
    deleteUserWidget->setLayout(layout);
    userStackWidget->addWidget(deleteUserWidget);
    userStackWidget->setCurrentWidget(deleteUserWidget);
}

//创建用户对应的槽函数
void UserUI::showCreateUserWidget()
{
    createUserlabel=new QLabel("创建用户");
    QFont labelFont;
    labelFont.setPointSize(20);
    createUserlabel->setFont(labelFont);
    //将上次创建的用户数据清空
    IdLineEdit->clear();
    passwordLineEdit->clear();
    paswdAgainLineEdit->clear();
    nickNameLineEdit->clear();
    signatureLineEdit->clear();
    ageLineEdit->clear();
    emailLineEdit->clear();

    //限制用户ID只能为数字，限制用户密码不大于8位
    QRegExp regx("[0-9]+$");
    QValidator *validator=new QRegExpValidator(regx,IdLineEdit);
    IdLineEdit->setValidator(validator);
    IdLineEdit->setMaxLength(8);
    passwordLineEdit->setMaxLength(8);
    paswdAgainLineEdit->setMaxLength(8);
    passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);          //隐藏密码
    paswdAgainLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    nickNameLineEdit->setMaxLength(10);
    signatureLineEdit->setMaxLength(30);
    emailLineEdit->setMaxLength(20);

    connect(confirmBtn,&QPushButton::clicked,this,&UserUI::showConfirmCreateUserBtn);
    connect(cancelBtn,&QPushButton::clicked,this,&UserUI::showCancelCreateUserBtn);

    //将输入信息的标签和lineedit放入一个布局中
    QGridLayout *createUserLayout=new QGridLayout;
    createUserLayout->addWidget(createUserlabel,0,0);
    createUserLayout->addWidget(IdLabel,1,0);
    createUserLayout->addWidget(IdLineEdit,1,1);
    createUserLayout->addWidget(passwordLabel,2,0);
    createUserLayout->addWidget(passwordLineEdit,2,1);
    createUserLayout->addWidget(paswdAgainLabel,3,0);
    createUserLayout->addWidget(paswdAgainLineEdit,3,1);
    createUserLayout->addWidget(nickNameLabel,4,0);
    createUserLayout->addWidget(nickNameLineEdit,4,1);
    createUserLayout->addWidget(signatureLabel,5,0);
    createUserLayout->addWidget(signatureLineEdit,5,1);
    createUserLayout->addWidget(ageLabel,6,0);
    createUserLayout->addWidget(ageLineEdit,6,1);
    createUserLayout->addWidget(sexLabel,7,0);
    createUserLayout->addWidget(sexComBox,7,1);
    createUserLayout->addWidget(emailLabel,8,0);
    createUserLayout->addWidget(emailLineEdit,8,1);

    //将确认和取消按钮加入另一个布局中
    QHBoxLayout *btnLayout=new QHBoxLayout;
    btnLayout->addWidget(confirmBtn);
    btnLayout->addWidget(cancelBtn);

    //将不同的布局放入整体布局
    QVBoxLayout *completeLayout=new QVBoxLayout;
    completeLayout->addLayout(createUserLayout);
    completeLayout->addLayout(btnLayout);

    createUserWidget=new QWidget;
    createUserWidget->setMaximumSize(400,400);
    createUserWidget->setLayout(completeLayout);
    userStackWidget->addWidget(createUserWidget);
    userStackWidget->setCurrentWidget(createUserWidget);
}

// 确认新建用户按钮槽函数
void UserUI::showConfirmCreateUserBtn()
{
    if(IdLineEdit->text().length()!=8){
        QMessageBox::information(nullptr, "警告", "用户ID的长度必须为8位！",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if(passwordLineEdit->text().length()==0 || passwordLineEdit->text()!=paswdAgainLineEdit->text()){
        QMessageBox::information(nullptr, "警告", "两次密码不一致且密码不能为空！",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if(nickNameLineEdit->text().length()==0){
        QMessageBox::information(nullptr, "警告", "昵称不能为空！",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    QDateTime currentDateTime =QDateTime::currentDateTime();
    //像用户概要数据表userGenerInfo写入注册的数据。
    //首先判断该ID是否已经被注册
    sqlQuery->exec("select * from userGenerInfo where ID='"+IdLineEdit->text()+"'");
    if(sqlQuery->next()){
        QMessageBox::information(this,tr("警告"),tr("该ID已经被注册了！"));
    }
    sqlQuery->prepare("insert into userGenerInfo(ID,密码,昵称,个性签名,年龄,性别,电子邮件,创建时间) values(?,?,?,?,?,?,?,?)");
    sqlQuery->addBindValue(IdLineEdit->text());
    sqlQuery->addBindValue(passwordLineEdit->text());
    sqlQuery->addBindValue(nickNameLineEdit->text());
    sqlQuery->addBindValue(signatureLineEdit->text());
    sqlQuery->addBindValue(ageLineEdit->text());
    sqlQuery->addBindValue(sexComBox->currentText());
    sqlQuery->addBindValue(emailLineEdit->text());
    sqlQuery->addBindValue(currentDateTime);
    if(!sqlQuery->exec()){
        QMessageBox::information(this,tr("警告"),tr("创建用户失败，请重试！"));
        qDebug()<<"sqlQuery error :"<<sqlQuery->lastError();
    }else{
        QMessageBox::information(this,tr("提示"),tr("创建用户成功！"));
    }
    QDateTime lastLeaveTime;
    QString groupInfo="";
    AddUserInfo(IdLineEdit->text(),nickNameLineEdit->text(),ageLineEdit->text(),sexComBox->currentText(),
                groupInfo,emailLineEdit->text(),currentDateTime.toString(),lastLeaveTime.toString());
}

//将新建用户添加到概况表中
void UserUI::AddUserInfo(QString Id, QString nickName, QString age,
                       QString sex, QString groupInfo,QString email, QString currentTime,QString lastLeaveTime)
{
    int rowCount=userSummaryTblWidget->rowCount();
    userSummaryTblWidget->insertRow(rowCount);
    //状态
    QPushButton *stateButton=new QPushButton;
    stateButton->setToolTip("离线");
    stateButton->setStyleSheet("border:none");
    stateButton->setIcon(QIcon(":/Img/image/offline.gif"));
    userSummaryTblWidget->setCellWidget(rowCount,0,stateButton);
    //ID信息
    userSummaryTblWidget->setItem(rowCount, 1, new QTableWidgetItem(Id));
    //昵称
    QTableWidgetItem *nickNameItem = new QTableWidgetItem(nickName);
    userSummaryTblWidget->setItem(rowCount,2,nickNameItem);
    nickNameItem->setFlags(nickNameItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    //年龄
    QTableWidgetItem *ageItem = new QTableWidgetItem(age);
    userSummaryTblWidget->setItem(rowCount,3,ageItem);
    ageItem->setFlags(ageItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    //性别
    QTableWidgetItem *sexItem = new QTableWidgetItem(sex);
    userSummaryTblWidget->setItem(rowCount,4,sexItem);
    sexItem->setFlags(sexItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    //电子邮件
    QTableWidgetItem *emailItem = new QTableWidgetItem(email);
    userSummaryTblWidget->setItem(rowCount,5,emailItem);
    emailItem->setFlags(emailItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    //群组信息
    groupComBox=new QComboBox;
    userSummaryTblWidget->setCellWidget(rowCount,6,groupComBox);
    QStringList groupList = groupInfo.split("#");
    for (int i = 0; i < groupList.size(); ++i) {
        if(groupList.at(i)!=""){
           groupComBox->addItem(groupList.at(i));
        }
    }
    //创建时间
    QTableWidgetItem *createDateItem = new QTableWidgetItem(currentTime);
    userSummaryTblWidget->setItem(rowCount,7,createDateItem);
    createDateItem->setFlags(createDateItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    //最近一次退出时间
    QTableWidgetItem *leaveDateItem;
    if(lastLeaveTime=="") {
       leaveDateItem = new QTableWidgetItem("从未登录");
    }else {
       leaveDateItem = new QTableWidgetItem(lastLeaveTime);
    }
    userSummaryTblWidget->setItem(rowCount,8,leaveDateItem);
    leaveDateItem->setFlags(leaveDateItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
    //删除
    QPushButton *deleteBtn=new QPushButton;
    deleteBtn->setStyleSheet("border:none");
    deleteBtn->setToolTip("删除");
    deleteBtn->setIcon(QIcon(QPixmap(":/Img/image/delete.jpg")));
    userSummaryTblWidget->setCellWidget(rowCount,9,deleteBtn);

    connect(deleteBtn,SIGNAL(clicked()),this,SLOT(showDeleteUser()));
}

//从摘要表中删除用户
void UserUI::showDeleteUser()
{
    int currentRow=userSummaryTblWidget->currentRow();
    if(currentRow != -1) {
        QString selectUserId=userSummaryTblWidget->item(currentRow,1)->text();
        if(QMessageBox::question(this,tr("提示"),QString("确定删除用户 %1 ？").arg(selectUserId),
                                 QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes) {
            sqlQuery->prepare("delete from userGenerInfo where ID='"+ selectUserId + "'");
            sqlQuery->exec();
            userSummaryTblWidget->removeRow(currentRow);
        }
    }
}

//取消新建用户按钮槽函数
void UserUI::showCancelCreateUserBtn()
{
    //跳回用户概要信息界面
    userStackWidget->setCurrentWidget(userSummaryWidget);
}

//搜索用户对应的槽函数
void UserUI::showSearchUserWidget()
{

}

//读取从线程中发来的有关用户更新的消息
void UserUI::rcvUpdateState(int msgType,QString userId)
{
    switch (msgType) {
    case LogIn:
    {
        for(int i=0;i<userSummaryTblWidget->rowCount();++i){
            if(userId==userSummaryTblWidget->item(i,1)->text())
            {
                QPushButton *stateButton=new QPushButton;
                stateButton->setToolTip("在线");
                stateButton->setStyleSheet("border:none");
                stateButton->setIcon(QIcon(":/Img/image/online.jpg"));
                userSummaryTblWidget->setCellWidget(i,0,stateButton);
                break;
            }
        }
        break;
    }
    case Leave:
    {
        QDateTime lastLeaveTime=QDateTime::currentDateTime();
        for(int i=0;i<userSummaryTblWidget->rowCount();++i){
            if(userId==userSummaryTblWidget->item(i,1)->text())
            {
                //修改状态
                QPushButton *stateButton=new QPushButton;
                stateButton->setToolTip("离线");
                stateButton->setStyleSheet("border:none");
                stateButton->setIcon(QIcon(":/Img/image/offline.gif"));
                userSummaryTblWidget->setCellWidget(i,0,stateButton);
                //修改最后一次退出时间
                QTableWidgetItem *leaveDateItem=new QTableWidgetItem(lastLeaveTime.toString());
                userSummaryTblWidget->setItem(i,8,leaveDateItem);
                leaveDateItem->setFlags(leaveDateItem->flags() & ~Qt::ItemIsEnabled & ~Qt::ItemIsSelectable);
                sqlQuery->prepare("update userGenerInfo set 最近一次退出=:lastLeaveTime where ID=:userId");
                sqlQuery->bindValue(":lastLeaveTime",lastLeaveTime);
                sqlQuery->bindValue(":userId",userId);
                if(!sqlQuery->exec()){
                    qDebug()<<"sqlQuery error :"<<sqlQuery->lastError();
                }
                break;
            }
        }
        break;
    }
    default:
        break;
    }
}

//读取线程中收到的用户注册的消息
void UserUI::rcvAddNewUser(QString Id,QString nickName,QString age,QString sex,QString email)
{
    QString strCurrentTime=QDateTime::currentDateTime().toString();
    QString groupInfo="";
    QString lastLeaveTime="";
    AddUserInfo(Id,nickName,age,sex,groupInfo,email,strCurrentTime,lastLeaveTime);
}

UserUI::~UserUI()
{
    delete ui;
}
