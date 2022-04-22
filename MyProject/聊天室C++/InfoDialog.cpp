#include <QtSql>
#include <QPixmap>
#include "InfoDialog.h"

/************************************************************
 函数名:                             InfoDialog
 功能:                               初始话个人信息对话框资源
 输入参数 p:                          默认参数父类构造函数的参数
        f:                          默认参数父类构造函数参数
       User:                        传入用户信息与按钮绑定
 ************************************************************/
InfoDialog::InfoDialog(const User &user, QWidget *p, Qt::WindowFlags f)
                                 :QDialog(p, f)
{
	this->user = user;                                                    //个人信息
	headBoxLayout = new QHBoxLayout;                                      //初始化头像布局管理器

	userHead = new QLabel(QString::fromUtf8("头像:"));                     //头像

	headBox = new QComboBox;                                              //新建头像列表框
	headBox->setIconSize(QSize(40,40));                                   //设置头像列表框头像大小
	initHeadList();                                                       //初始化头像列表框

	headBoxLayout->addWidget(userHead);                                   //添加进布局管理器
	headBoxLayout->addWidget(headBox);

	ipLayout = new QHBoxLayout;                                           //IP布局管理器

	ip = new QLabel(QString::fromUtf8("本机IP:"));                         //IP文本显示框
	ipEdit = new QLineEdit(user.getUserIp());                             //IP文本编辑框
    ipEdit->setReadOnly(true);

	ipLayout->addWidget(ip);                                              //添加进IP布局管理器
	ipLayout->addWidget(ipEdit);

	nameBoxLayout = new QHBoxLayout;                                      //初始化用户名布局管理器

	userName = new QLabel(QString::fromUtf8("用户名:"));
	userNameEdit = new QLineEdit(user.getUserName());

	nameBoxLayout->addWidget(userName);                                   //添加进布局管理器
	nameBoxLayout->addWidget(userNameEdit);

    writeLayout = new QHBoxLayout;                                        //初始化个性签名布局管理员

    write = new QLabel(QString::fromUtf8("个性签名:"));
    heartWrite = new QLineEdit(user.getUserWrite());

    writeLayout->addWidget(write);                                        //添加进布局管理器
	writeLayout->addWidget(heartWrite);

    sureCancelLayout = new QHBoxLayout();                                 //确定与取消按钮布局管理器

    makesure = new QPushButton(QString::fromUtf8("确认"));
    connect(makesure, SIGNAL(clicked()), this, SLOT(makeSure()));         //连接点击信号与处理槽

    cancel = new QPushButton(QString::fromUtf8("关闭"));
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));              //连接点击信号与处理槽
    connect(cancel, SIGNAL(clicked()), this, SLOT(updateHead()));         //关闭按钮点击信号与处理槽

    sureCancelLayout->addWidget(makesure);                                //将按钮添加进布局管理器
    sureCancelLayout->addWidget(cancel);

    mainLayout = new QVBoxLayout(this);                                   //初始化主体布局管理器

    mainLayout->addLayout(headBoxLayout);                                 //添加头像布局管理器
    mainLayout->addLayout(ipLayout);                                      //添加IP布局管理器
    mainLayout->addLayout(nameBoxLayout);                                 //添加用户名布局管理器
    mainLayout->addLayout(writeLayout);                                   //添加个性签名布局管理器
    mainLayout->addLayout(sureCancelLayout);                              //添加确定于取消布局管理器

    this->setMaximumSize(QSize(200,200));                                 //设置最大尺寸
    this->setMinimumSize(QSize(200,200));                                 //设置最小尺寸
}

/************************************************************
 函数名:                             ~ToolButton
 功能:                               释放资源
 ************************************************************/
InfoDialog::~InfoDialog()
{
	delete ip;
	delete write;
	delete userHead;
	delete userName;
	delete ipEdit;
	delete headBox;
	delete heartWrite;
	delete userNameEdit;
	delete mainLayout;
	delete makesure;
	delete cancel;
	delete sureCancelLayout;
	delete writeLayout;
	delete headBoxLayout;
	delete nameBoxLayout;
}

/************************************************************
 函数名:                             initHeadList
 功能:                               初始化头像列表
 输入参数 myHead:                     本地用户的头像
 ************************************************************/
void InfoDialog::initHeadList()
{
	QDir dir(DEFAULT_PATH);                                               //默认的头像的文件夹
	if (!dir.isReadable())                                                //是否该路径可读
	{
		QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("头像文件路径不正确"));
	}

    int myHeadIndex = 0;
	QString myHead = user.getUserHead();                                  //获得当前用户的头像

	headList = dir.entryList(QDir::Files);                                //获得文件夹的所有文件

	for (int i=0; i<headList.count(); i++)
	{
		QString fileName = dir.filePath(headList.at(i));                  //设置文件相对路径名
		if (fileName == myHead)                                           //记录当前用户头像索引
		{
			myHeadIndex = i;
		}

		headBox->addItem(QIcon(fileName), NULL);                          //添加进列表框
	}

	headBox->setCurrentIndex(myHeadIndex);                                //显示当前本地头像
}

/************************************************************
 函数名:                             updateHead
 功能:                               修改列表框头像
 ************************************************************/
void InfoDialog::updateHead()
{
	QDir dir(DEFAULT_PATH);                                               //默认的头像的文件夹
	if (!dir.isReadable())                                                //是否该路径可读
	{
			QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("头像文件路径不正确"));
	}

    int myHeadIndex = 0;
	QString myHead = user.getUserHead();                                  //获得当前用户的头像

	for (int i=0; i<headList.count(); i++)
	{
		QString fileName = dir.filePath(headList.at(i));
		if (fileName == myHead)                                           //记录当前用户头像索引
		{
			myHeadIndex = i;
			break;
		}
	}

	headBox->setCurrentIndex(myHeadIndex);                                //显示当前本地头像
}

/************************************************************
 函数名:                             getUserInfo
 功能:                               获得个人信息
 返回值 :                             个人用户信息
 ************************************************************/
const User & InfoDialog::getUserInfo()
{
	return this->user;                                                    //返回用户信息
}

/************************************************************
 函数名:                             makeSure
 功能:                               确定按钮槽函数
 ************************************************************/
void InfoDialog::makeSure()
{
	bool isUpdate = false;                                                //判断是否更新变量

	if (this->userNameEdit->isModified() || this->heartWrite->isModified() ||
			                    this->ipEdit->isModified())
	{
		QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
		QSqlQuery query(db);                                              //获得数据库连接创建查询对象

		QString ip = ipEdit->text();                                      //获得修改后的IP
        QString name = userNameEdit->text();                      //获得修改后的用户名
        QString write = heartWrite->text();                            //获得个性签名
        user.setUserName(name);
        user.setUserWrite(write);
        user.setUserIp(ip);

		QString sql("update wn_user_info set user_name = '"+name+"', "    //修改个人信息数据库
                "user_ip = '"+ip+"', user_write = '"+write+"' where id = 1");

        bool isRight = query.exec(sql);                                   //执行修改个人信息
        if (!isRight)                                                            //修改失败
		{
		  	QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("修改数据库失败!"));
		}

		isUpdate = true;
	}

	QDir dir(DEFAULT_PATH);
	if (!dir.isReadable())                                                //是否该路径可读
	{
			QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("头像文件路径不正确"));
	}

	int index = headBox->currentIndex();                                 //获得选择头像索引
	QString head = dir.filePath(headList.at(index));
	if (user.getUserHead() != head)                                      //是否头像已经更改
	{
		user.setUserHead(head);                                          //设置本地当前用户头像
		QString sql("update wn_user_info set user_head = '"+head+"' where id = 1");

		QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
		QSqlQuery query(db);
		bool isRight = query.exec(sql);                                  //执行修改个人信息
        if (!isRight)                                                           //修改失败
		{
    	  QMessageBox::critical(0, QString::fromUtf8("错误"), QString::fromUtf8("修改数据库失败!"));
		}

		isUpdate = true;                                                  //设置临时修改变量
	}

	if (isUpdate)                                                         //是否个人信息被修改
	{
        QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("修改成功"));
        emit(update());                                                  //发送个人信息修改信号
		this->close();                                                    //关闭修改对话框
	}

    this->close();                                                        //关闭修改对话框
}
