#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->showMaximized();
    setWindowTitle("欢迎来到校园即时通信系统服务器！");

    serverIconLabel=new QLabel;
    serverIconLabel->setFixedSize(100,100);
    QPixmap logoMap(":/Img/image/logo.jpg");
    logoMap.scaled(serverIconLabel->size(), Qt::KeepAspectRatio);
    serverIconLabel->setScaledContents(true);
    serverIconLabel->setPixmap(logoMap);
    welcomeToServerLabel=new QLabel("欢迎来到NUISTChat 服务器！");
    QFont font("Microsoft YaHei",20,75);
    welcomeToServerLabel->setFont(font);

    QHBoxLayout *labelLayout=new QHBoxLayout;
    labelLayout->addWidget(serverIconLabel);
    labelLayout->addWidget(welcomeToServerLabel);

    //创建QstackWidget对象
    stackWidget = new QStackedWidget;
    list = new QListWidget;
    //创建按钮对象 --用户、用户组、服务器信息
    Btn_User=new QPushButton();
    Btn_User->setText("用户");
    Btn_User->setMaximumWidth(100);
    Btn_UserGroup=new QPushButton();
    Btn_UserGroup->setText("用户群");
    Btn_UserGroup->setMaximumWidth(100);
    Btn_ServerInfo=new QPushButton;
    Btn_ServerInfo->setText("服务器");
    Btn_ServerInfo->setMaximumWidth(100);

    QHBoxLayout *btnLayout=new QHBoxLayout;
    btnLayout->setAlignment(Qt::AlignLeft);
    btnLayout->addWidget(Btn_ServerInfo);
    btnLayout->setMargin(10);
    btnLayout->addWidget(Btn_User);
    btnLayout->setMargin(10);
    btnLayout->addWidget(Btn_UserGroup);

    connect(Btn_User,&QPushButton::clicked,this,&Widget::showUserSummaryWidget);
    connect(Btn_UserGroup,&QPushButton::clicked,this,&Widget::showGroupSummaryWidget);
    connect(Btn_ServerInfo,&QPushButton::clicked,this,&Widget::showServerInfoWidget);

    stackWidget=new QStackedWidget;
    userUi= new UserUI;
    groupUi=new UserGroup;
    ServerInfoUi=new ServerGenerInfoUI;

    QHBoxLayout *userLayout = new QHBoxLayout(this);
    userLayout->addWidget(userUi);
    userUiWidget=new QWidget;
    userUiWidget->setLayout(userLayout);

    stackWidget->addWidget(userUiWidget);
    mainLayout=new QVBoxLayout(this);
    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(btnLayout);
    mainLayout->addWidget(stackWidget);
}

Widget::~Widget()
{
    delete ui;
}

//展示用户摘要界面
void Widget::showUserSummaryWidget()
{
    stackWidget->setCurrentWidget(userUiWidget);
}

//展示用户群摘要界面
void Widget::showGroupSummaryWidget()
{
    stackWidget->addWidget(groupUi);
    stackWidget->setCurrentWidget(groupUi);
}

//展示服务器信息界面
void Widget::showServerInfoWidget()
{
    stackWidget->addWidget(ServerInfoUi);
    stackWidget->setCurrentWidget(ServerInfoUi);
}
