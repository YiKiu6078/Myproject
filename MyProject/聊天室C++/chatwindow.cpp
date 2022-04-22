/******************************************************
Copyright (c), 2009-2019,           程凡凡
filename:                           chatwindow.cpp
author:                             程凡凡
function:                           Create a Qt window,use
                                    for chat.
version:                            version1
finish date:                        2009/12/14
modification date:
modification list:
******************************************************/

#include <QTime>
#include <QtGui>
#include <QIcon>
#include <QDateTime>
#include <QUdpSocket>
#include <QSqlQuery>
#include <QByteArray>
#include <QHostAddress>
#include "chatwindow.h"

ChatWindow::ChatWindow(const User &me, const User &user,QWidget * parent)
                                           : QDialog(parent)
{
    setWindowTitle(QString::fromUtf8("与")+user.getUserName()+QString::fromUtf8("聊天"));      //设置窗口标题

																							  /*设置window的大小*/
    this->resize(600, 450);
    this->setMinimumSize(QSize(600, 450));
    this->setMaximumSize(QSize(600, 450));

    this->me = me;  																		          //设置本地用户
    this->user = user;     																    	  //设置好友用户

    gridLayout = new QGridLayout;                                                             //窗口布局管理器

    textEdit_receive = new QTextEdit;                                                         //创建接收信息窗口
    textEdit_receive->setFixedSize(400, 180);
    textEdit_receive->setReadOnly(true);

    toolButton_color = new QToolButton;                                                       //设置颜色按钮
    toolButton_color->setIcon(QIcon("./images/color.png"));

    toolButton_bold = new QToolButton;												          //设置字体加粗按钮
    toolButton_bold->setIcon(QIcon("./images/bold.png"));
    toolButton_bold->setCheckable(true);

    toolButton_italic = new QToolButton;                                                      //设置字体斜体按钮
    toolButton_italic->setIcon(QIcon("./images/italic.png"));
    toolButton_italic->setCheckable(true);

    toolButton_underline= new QToolButton;													  //设置字体下划线按钮
    toolButton_underline->setIcon(QIcon("./images/underline.png"));
    toolButton_underline->setCheckable(true);

    label_font = new QLabel(QString::fromUtf8("字体"));

    comboBox_font = new QFontComboBox;                                                        //选择字体大小
    comboBox_font->setFixedSize(100, 25);
    comboBox_font->setFontFilters(QFontComboBox::ScalableFonts);

    textEdit_send = new QTextEdit;                                                            //发送信息框

    label_size = new QLabel(QString::fromUtf8("字号"));
    comboBox_size = new QComboBox;

    int fontSize = textEdit_send->currentFont().pointSize();        //获得当前文本编辑框的字体尺寸

    int defaultItem = 0;                                            //与缺省字体尺寸相等的索引号
    QFontDatabase db;                                               //取系统可用字号
    foreach(int size, db.standardSizes())                           //设置可用字号
    {
    	if (size < 8)                                               //获取字体库中8－22号字体
    	{
    		continue;
    	}

    	if (size > 22)
    	{
    		break;
    	}

    	if (fontSize == size)                                        //记录于默认字体号相匹配所以号
    	{
    		defaultItem = comboBox_size->count();
    	}

        comboBox_size->addItem(QString::number(size));               //添加进下拉菜单
    }
    comboBox_size->setCurrentIndex(defaultItem);                     //设置当前字体索引号

    gridLayout->addWidget(textEdit_receive, 0, 0);                   //添加接收信息框进布局管理器

    midLayout = new QHBoxLayout;                                     //主布局管理器
    midLayout->addWidget(toolButton_color);
    midLayout->addWidget(toolButton_bold);
    midLayout->addWidget(toolButton_italic);
    midLayout->addWidget(toolButton_underline);
    midLayout->addWidget(label_size);
    midLayout->addWidget(comboBox_size);
    midLayout->addWidget(label_font);
    midLayout->addWidget(comboBox_font);

    gridLayout->addLayout(midLayout, 1, 0);


    textEdit_send->setFixedSize(400, 143);

    gridLayout->addWidget(textEdit_send, 2, 0);

    pushButton_log = new QPushButton(QString::fromUtf8("聊天记录"));     //聊天记录按钮
    pushButton_sendMessage = new QPushButton(QString::fromUtf8("发送消息"));      //发送信息按钮
    pushButton_sendFile = new QPushButton(QString::fromUtf8("发送文件"));         //发送文件按钮
    pushButton_close = new QPushButton(QString::fromUtf8("关闭"));               //关闭窗口按钮

    baseLayout = new QHBoxLayout;
    baseLayout->addWidget(pushButton_log);
    baseLayout->addWidget(pushButton_close);
    baseLayout->addWidget(pushButton_sendFile);
    baseLayout->addWidget(pushButton_sendMessage);

    gridLayout->addLayout(baseLayout, 3, 0);

    title = new QLabel(QString::fromUtf8("基本资料"));                            //用户基本资料显示

    headName = new QLabel(QString::fromUtf8("头像:"));
    labelHead = new QLabel;
    labelHead->setPixmap(QPixmap(user.getUserHead()));

    userName = new QLabel(QString::fromUtf8("用户名:"));
    labelUserName = new QLabel(user.getUserName());

    hostName = new QLabel(QString::fromUtf8("主机名:"));
    labelHostName = new QLabel(user.getUserHostName());

    ip = new QLabel("IP:");
    labelIp = new QLabel(user.getUserIp());

    write = new QLabel(QString::fromUtf8("个性签名:"));
    labelWrite = new QLabel(user.getUserWrite());

    infoLayout = new QGridLayout;
    infoLayout->addWidget(title, 0, 0, 1, 2, Qt::AlignCenter);
    infoLayout->addWidget(headName, 1, 0);
    infoLayout->addWidget(labelHead, 1, 1);
    infoLayout->addWidget(userName, 2, 0);
    infoLayout->addWidget(labelUserName, 2, 1);
    infoLayout->addWidget(hostName, 3, 0);
    infoLayout->addWidget(labelHostName, 3, 1);
    infoLayout->addWidget(ip, 4, 0);
    infoLayout->addWidget(labelIp, 4, 1);
    infoLayout->addWidget(write, 5, 0);
    infoLayout->addWidget(labelWrite, 5, 1);

    mainLayout = new QHBoxLayout;
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(infoLayout);

    setLayout(mainLayout);

    /***信号和槽函数****/
    connect(comboBox_font, SIGNAL(activated(QString)), this, SLOT(slotFont(QString)));     //连接设置字体信号与槽
    connect(comboBox_size, SIGNAL(activated(QString)), this, SLOT(slotSize(QString)));     //连接设置字体大小与槽
    connect(toolButton_bold, SIGNAL(clicked()), this, SLOT(slotBold()));                   //连接设置字体加粗信号与槽
    connect(toolButton_italic, SIGNAL(clicked()), this, SLOT(slotItalic()));               //连接设置斜体字体信号与槽
    connect(toolButton_underline, SIGNAL(clicked()), this, SLOT(slotUnder()));             //连接设置下划线信号于槽
    connect(toolButton_color, SIGNAL(clicked()), this, SLOT(slotColor()));                 //连接设置字体颜色信号与槽

    connect(pushButton_close, SIGNAL(clicked()), this, SLOT(close()));                    //关闭聊天窗口

    connect(pushButton_sendMessage, SIGNAL(clicked()), this, SLOT(slotsendmsg()));
    connect(pushButton_sendFile, SIGNAL(clicked()), this, SLOT(slotSendFile()));

    chatLogWnd = new QDialog(this);                                                         //创建聊天记录窗口
    logEdit = new QTextEdit(chatLogWnd);                                                    //创建文本编辑器
    logLayout = new QVBoxLayout(chatLogWnd);                                                //创建布局管理器
    clearLog = new QPushButton(QString::fromUtf8("清除聊天记录"));                            //清除聊天记录按钮
    closeLog = new QPushButton(QString::fromUtf8("关闭"));                                   //关闭聊天记录窗口
    connect(closeLog, SIGNAL(clicked()), this, SLOT(closeLogWnd()));                        //关闭聊天记录窗口信号槽

    logHLayout = new QHBoxLayout;

    connect(clearLog, SIGNAL(clicked()), this, SLOT(clearChatLog()));                       //点击该按钮将聊天记录删除
    creatLogWindow();                                                                       //创建聊天记录窗口

    connect(pushButton_log, SIGNAL(clicked()), this, SLOT(slotExtension()));                //显示聊天记录窗口

    udpsocket = new QUdpSocket;                                                             //发送消息Socket

    ftpServer = new FtpServerDialog(this);                                                  //创建这个发送文件对话框
    connect(ftpServer, SIGNAL(sendFileMsg()), this, SLOT(sendFileMsg()));
}

void ChatWindow::setMeInfo(const User &me)
{
	this->me = me;
}

/******************************************************************
函数名：                   sendFileMsg
函数功能：                发送文件信息
*******************************************************************/
void ChatWindow::sendFileMsg()
{
    MSG msg;                                                            //消息结构体
    msg.headId = HEADID;                                                //通信协议头
    msg.msgFlag = SENDFILE;                                             //信息标识
    msg.fileUrlLen = ftpServer->getFileName().length();                 //获得文件名长度
    msg.fileSize = ftpServer->getFile().size();

    QByteArray byteArray;
    byteArray.append((char *)&msg, sizeof (msg));                       //添加消息结构体进发送字节流

    QTextCodec *codec = QTextCodec::codecForName("utf8");     //转换编码
    QByteArray fileName = codec->fromUnicode(ftpServer->getFileName());  //添加用户名
    byteArray.append(fileName);                                             //添加文件名进发送字节流

    int length = udpsocket->writeDatagram(byteArray, QHostAddress(user.getUserIp()), MSGPORT); //发送数据报文
    if (length != byteArray.length())                                   //是否发送完全
    {
    	QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("发送消息报文出错"));
    }
}

/*****************************************************************
函数名：                                                                 mergeFormat
函数功能：                                                             设置字体
传入参数   format：                                              设置对象
******************************************************************/

void ChatWindow::mergeFormat(QTextCharFormat format)
{
    textEdit_send->selectAll();                                                    //选择发送所有信息
    QTextCursor cursor = textEdit_send->textCursor();                              //获得光标
    cursor.mergeCharFormat(format);                                                //将信息格式化
    textEdit_send->mergeCurrentCharFormat(format);
}

/****************************************************************
函数名：                                                                slotFont
函数功能：                    					     设置字体
传入参数   f：                                                        字符串
*****************************************************************/
void ChatWindow::slotFont(QString f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);                                                          //设置字体
    mergeFormat(fmt);                                                              //格式化字体
}

/*****************************************************************
函数名： 								    slotSize
函数功能：                                                            设置字体尺寸
传入参数  num：                                                    字号
******************************************************************/
void ChatWindow::slotSize(QString num)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(num.toFloat());										   //设置字体号
    format = fmt;
    mergeFormat(fmt);
}

/*****************************************************************
函数名:								  slotBold
函数功能：                      					    加粗字体
******************************************************************/
void ChatWindow::slotBold()
{
	QTextCharFormat fmt;
    fmt.setFontWeight(toolButton_bold->isChecked() ? QFont::Bold : QFont::Normal);
    textEdit_send->mergeCurrentCharFormat(fmt);                                   //将字体加粗
}

/******************************************************************
函数名：               						  slotItalic
函数功能：							  设置斜体
*******************************************************************/
void ChatWindow::slotItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(toolButton_italic->isChecked());
    textEdit_send->mergeCurrentCharFormat(fmt);
}

/******************************************************************
函数名：							        slotUnder
函数功能：                                                        加下划线
********************************************************************/
void ChatWindow::slotUnder()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(toolButton_underline->isChecked());
    mergeFormat(fmt);
}

/******************************************************************
函数名：                                                           slotColor
函数功能：				                        设置字体颜色
*******************************************************************/
void ChatWindow::slotColor()
{
    QColor color = QColorDialog::getColor (Qt::red,this);
    if(color.isValid())
    {
        QTextCharFormat fmt;
        fmt.setForeground(color);
        mergeFormat(fmt);
    }
}

/******************************************************************
函数名：                                                                 setSendFileButton
函数功能：                                                              将发送文件按钮失效
传入参数  isEnable true:                  将按钮恢复可用
                 false:                 将按钮不可用
*******************************************************************/
void ChatWindow::setSendFileButton(bool isEnable)
{
	pushButton_sendFile->setEnabled(isEnable);                                //将发送文件按钮失效
}

/******************************************************************
函数名：									slotCurrentCharFormatChanged
函数功能：								当前字体改变
传入参数 fmt：								改变字
*******************************************************************/
void ChatWindow::slotCurrentCharFormatChanged(const QTextCharFormat &fmt)
{
    comboBox_font->setCurrentIndex(comboBox_font->findText(fmt.fontFamily()));
    comboBox_size->setCurrentIndex(comboBox_size->findText(QString::number(fmt.fontPointSize())));
    toolButton_bold->setChecked(fmt.font().bold());
    toolButton_italic->setChecked(fmt.fontItalic());
    toolButton_underline->setChecked(fmt.fontUnderline());
}

/*****************************************************************
函数名：       								slotsendmsg
函数功能：								发送信息槽函数
******************************************************************/
void ChatWindow::slotsendmsg()
{  
    if (CheckMsg(textEdit_send->toPlainText()))                               //检查发送信息是否可用
    {
    	QString msg;
    	msg = textEdit_send->toHtml();
    	message_show(msg, me.getUserName());
    	textEdit_send->clear();

        MSG sendMsg; 													      //封装消息
        sendMsg.headId = HEADID;
        sendMsg.msgFlag = SENDMSG;
        sendMsg.msgLen = msg.length();

        QByteArray byteArray;
        byteArray.append((char *)&sendMsg, sizeof (sendMsg));

        QTextCodec *codec = QTextCodec::codecForName("utf8");
        QByteArray data = codec->fromUnicode(msg);
        byteArray.append(data);

        udpsocket->writeDatagram(byteArray, QHostAddress(user.getUserIp()), MSGPORT);    //发送消息
    }
}

/******************************************************************
 函数名:                                        paresLog
 功能:                                          解析聊天记录
 传入参数 tmpLog:                                聊天记录
 返回值:                                        html中的body部分
 ******************************************************************/
QString ChatWindow::paresLog(QString &tmpLog)
{
    tmpLog.replace('"', '|');                                              //替换引号
    tmpLog.replace('\'', '|');                                             //替换单引号

    QString tmpStr = "</head>";                                            //获得Html中的body
	int startPos = tmpLog.indexOf("</head>");
	startPos += tmpStr.length();
	int endPos = tmpLog.indexOf("</html>") - startPos;

    return tmpLog.mid(startPos, endPos);
}

/*****************************************************************
函数名：                                                                     closeEvent
函数功能：                                                                  关闭聊天窗口操作
传入参数 event：                                                          窗口关闭事件
返回值  ：
******************************************************************/
void ChatWindow::closeEvent(QCloseEvent * event)
{
     if (!textEdit_receive->toPlainText().isEmpty())                             //是否聊天记录为空
     {
         this->slotWriteLog();                                                         //将聊天记录写入数据库
         this->clearChat();                                                             //发送框与接收框清除
     }
     event->accept();
}

/*****************************************************************
函数名：          slotWriteLog
函数功能：        主要实现查看聊天记录的槽函数
传入参数：
返回值：
******************************************************************/
void ChatWindow::slotWriteLog()
{
	QString tmpLog = textEdit_receive->toHtml();

	if (!textEdit_receive->toPlainText().isEmpty())                             //是否聊天记录为空
	{
        QString logStr = paresLog(tmpLog);                                      //解析当前聊天记录

        QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
		QSqlQuery query(db);                                                //初始化数据库
		QString sql = "insert into wn_user_chatinfo(from_user_ip, message) "
				" values('"+user.getUserIp()+"', '"+logStr+"')";

		bool isRight = query.exec(sql);                                         //执行数据库操作
		if (!isRight)                                                           //数据库操作失败
		{
			QMessageBox::information(0, QString::fromUtf8("错误"), QString::fromUtf8("操作数据库失败!"));
		}
    }
}

/*****************************************************************
函数名：             clearChat
函数功能：           主要实现清除聊天窗口
                     信息的槽函数
******************************************************************/
void ChatWindow::clearChat()
{
	textEdit_receive->clear();
	textEdit_send->clear();
}

/*****************************************************************
函数名：              clearChatLog
函数功能：            主要实现清除记录的槽函数
******************************************************************/
void ChatWindow::clearChatLog()
{

	if (logEdit->toPlainText().isEmpty())                                            //判断是否聊天记录为空
	{
		QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("聊天记录为空!"));
	}
	else
	{
		if (QMessageBox::Yes == QMessageBox::warning(this, QString::fromUtf8("提示"), QString::fromUtf8("你想清空聊天记录吗?"),
				                                              QMessageBox::Yes | QMessageBox::No))
		{
	        logEdit->clear();                                                        //清除聊天记录窗口记录

	        QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
	        QSqlQuery query(db);                                                 //删除聊天记录
            QString sql = "delete from wn_user_chatinfo where from_user_ip = '"+user.getUserIp()+"'";

            bool isRight = query.exec(sql);
            if (!isRight)
            {
    	        QMessageBox::information(0, QString::fromUtf8("错误"), QString::fromUtf8("操作数据库失败!"));
            }
		}
	}
}

/****************************************************************
函数名：										CheckMsg
函数功能：         								检查字符串是否有效
传入参数 msg：                                  				将要检查字符串
返回值     true：								表示有效
        false:                              表示无效
*****************************************************************/
bool ChatWindow::CheckMsg(QString msg)
{
    if (msg == "")																	 //消息为空
    {
        QMessageBox::information(0, QString::fromUtf8("提示"), QString::fromUtf8("发送内容不能空！"));
        return false;
    }
    if (msg.length() > 1500)                                                         //消息太长
    {
        QMessageBox::critical(0, QString::fromUtf8("提示"), QString::fromUtf8("消息的过长，请分条发送。"));
        return false;
    }

    return true;
}

/****************************************************************
函数名：                        void message_show(Qstring msg)
函数功能：                    将消息显示到消息显示窗口，并且添加时间标识。
传入参数 msg：             需要显示的消息。
       sender：       发送消息人的呢称。
****************************************************************/
void ChatWindow::message_show(const QString &msg, QString sender)
{
    QTime time = QTime::currentTime();											      //获得当前时间
    QString stringtime = time.toString("H:m:s");

    textEdit_receive->insertHtml("<font color=#0099FF size=3>"+sender + " " + stringtime + "</font><br>");  //以Html形式显示
    textEdit_receive->insertHtml(msg);
    textEdit_receive->insertHtml("<br>");

    textEdit_receive->verticalScrollBar()->setValue(textEdit_receive->verticalScrollBar()->maximumHeight());
}

/*****************************************************************
函数名：                                                                                   creatLogWindow
函数功能：                                                                                创建聊天记录窗口
******************************************************************/
void ChatWindow::creatLogWindow()
{
    chatLogWnd->setFixedSize(QSize(400,  200));                                       //设置聊天记录窗口大小
    chatLogWnd->setWindowTitle(QString::fromUtf8("与")+user.getUserName()
    		                                 +QString::fromUtf8("聊天记录"));
    logEdit->setReadOnly(true);                                                       //设置只读属性

    clearLog->setFixedSize(100, 30);                                                  //设置按钮大小
    closeLog->setFixedSize(80, 30);

    logHLayout->addWidget(clearLog);												  //添加按钮
    logHLayout->addWidget(closeLog);
    logHLayout->setAlignment(Qt::AlignRight);

    logLayout->addWidget(logEdit);
    logLayout->addLayout(logHLayout);

    chatLogWnd->setLayout(logLayout);

    chatLogWnd->hide();                                                               //隐藏聊天记录窗口
}

/*****************************************************************
函数名：                                                                                   closeLogWnd
函数功能：                                                                                隐藏聊天记录窗口
******************************************************************/
void ChatWindow::closeLogWnd()
{
	chatLogWnd->hide();
}

/*****************************************************************
函数名：                                                                                   slotExtension
函数功能：                                                                                实现窗口的扩展功能
******************************************************************/
void ChatWindow::slotExtension()
{
    if (chatLogWnd->isHidden())                                                      //聊天记录窗口隐藏
    {
    	QSqlDatabase db = QSqlDatabase::database(DATABASE_NAME);
     	QSqlQuery query(db);                                                     //创建数据库查询对象
        QString sql = "select *from wn_user_chatinfo where from_user_ip = '"+user.getUserIp()+"'";
        bool isRight = query.exec(sql);                                              //访问数据库
        if (!isRight)                                                                //访问失败
        {
        	QMessageBox::information(0, QString::fromUtf8("错误"), QString::fromUtf8("访问数据库失败!"));
        }
        else
        {
        	QString logStr;
        	while (query.next())                                                     //下一个记录
        	{
        		logStr += query.value(2).toString();
        	}

        	logStr.replace('|', '"');
        	logEdit->setText(logStr);                                                //显示聊天记录
        }

        query.clear();
        chatLogWnd->show();                                                          //显示聊天记录窗口
    }
    else
    {
    	chatLogWnd->hide();                                                          //隐藏聊天记录窗口
    }
}

/*****************************************************************
函数名：                                                                                   slotSendFile
函数功能：                                                                                发送文件窗口显示
******************************************************************/
void ChatWindow::slotSendFile()
{
	ftpServer->setServerAddress(user.getUserIp());
	ftpServer->show();
}

/*****************************************************************
函数名：                                                                                   getFileDialog
函数功能：                                                                                获得发送文件对话框
******************************************************************/
const FtpServerDialog *ChatWindow::getFileDialog() const
{
    return ftpServer;
}
/*****************************************************************
函数名：                                                                                   ～ChatWindow
函数功能：                                                                                释放资源
******************************************************************/
ChatWindow::~ChatWindow()
{
	delete ip;
	delete write;
	delete userName;
	delete hostName;

	delete label_font;
	delete label_size;
	delete comboBox_font;
	delete comboBox_size;

	delete toolButton_bold;
	delete toolButton_color;
	delete toolButton_italic;
	delete toolButton_underline;

	delete labelIp;
	delete labelHead;
	delete labelWrite;
	delete labelHostName;
	delete labelUserName;

	delete closeLog;
	delete clearLog;
	delete logEdit;
	delete chatLogWnd;
	delete logLayout;

	delete textEdit_send;
	delete textEdit_receive;

	delete pushButton_log;
	delete pushButton_close;
    delete pushButton_sendFile;
	delete pushButton_sendMessage;

	delete ftpServer;
    delete hBoxLayout;
    delete infoLayout;
	delete udpsocket;
	delete gridLayout;
	delete logHLayout;
}
