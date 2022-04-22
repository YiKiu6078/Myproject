#include "ChatRoom.h"
#include "ui_ChatRoom.h"

ChatRoom::ChatRoom(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatRoom)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);
    this->setStyleSheet("background-color: white");
    //this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setWindowFlag(Qt::FramelessWindowHint);
    QAction *searchAction = new QAction(ui->searchLineEdit);
    searchAction->setIcon(QIcon(":/Img/picture/search.jpg"));
    ui->searchLineEdit->setPlaceholderText(tr("搜索联系人"));
    ui->searchLineEdit->addAction(searchAction,QLineEdit::LeadingPosition);

    ui->minBtn->setIcon(QIcon(":/Img/picture/min.jpg"));
    ui->minBtn->setStyleSheet("border:none");
    ui->closeBtn->setIcon(QIcon(":/Img/picture/close.jpg"));
    ui->closeBtn->setStyleSheet("border:none");
    ui->screenShotBtn->setIcon(QIcon(":/Img/picture/screenShot.jpg"));
    ui->screenShotBtn->setStyleSheet("border:none");
    ui->sendImgBtn->setIcon(QIcon(":/Img/picture/Img.jpg"));
    ui->sendImgBtn->setStyleSheet("border:none");
    ui->sendFileBtn->setIcon(QIcon(":/Img/picture/file.jpg"));
    ui->sendFileBtn->setStyleSheet("border:none");
    
    ui->chatTextEdit->setPlaceholderText(tr("请输入聊天内容"));
    ui->chatUserList->setStyleSheet("background-color: yellow");
    QLabel *rightWidgetLabel=new QLabel;
    rightWidgetLabel->setPixmap(QPixmap(":/Img/picture/rightWidget.jpg"));
    QVBoxLayout *rightLayout=new QVBoxLayout;
    rightLayout->addWidget(rightWidgetLabel);
    ui->RightWidget->setLayout(rightLayout);

    captureHelper = new CaptureScreen();

    if(QSqlDatabase::contains("qt_sql_default_connection")) {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }else {
        database = QSqlDatabase::addDatabase("QSQLITE");
    }
    QString dataPath = QDir::currentPath() + "/" + userId +"/" + userId + ".db";
    database.setDatabaseName(dataPath);
    if(!database.open()) {
       qDebug() << "Open person database failed";
    }
    sqlQuery=new QSqlQuery;
}

//鼠标拖动窗口
void ChatRoom::mouseMoveEvent(QMouseEvent *event)
{
    QPoint EndPos;
    if ( event->buttons() == Qt::LeftButton )
    {
        EndPos = event->globalPos() - StartPos;
        this->move(EndPos);
    }
}

void ChatRoom::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton) {
        //记录窗口此时的坐标
        StartPos = event->globalPos() - this->frameGeometry().topLeft();
    }
}

//建立新的聊天
void ChatRoom::addChatUser(QString strId,QString nickName,QImage frdheadImg)
{
    for (int i = 0; i < ui->chatUserList->count();++i) {
        if(strId == ui->chatUserList->item(i)->text()){
            ui->chatUserLabel->setText(nickName);
            ui->chatUserList->setCurrentRow(i);
            return;
        }
    }
    QListWidgetItem *item=new QListWidgetItem;
    item->setSizeHint(QSize(100,40));
    QPixmap pixmap(40,40);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0, 0, 40, 40);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, 40, 40,QPixmap::fromImage(frdheadImg));
    item->setIcon(QIcon(pixmap));
    item->setText(strId);
    ui->chatUserList->insertItem(0,item);
    ui->chatUserList->setCurrentRow(0);
    ui->chatUserLabel->setText(nickName);

    clearChatItem();
    QImage groupMemberImg;
    sqlQuery->prepare("select * from ChatMsgWith" + ui->chatUserList->currentItem()->text());
    if(sqlQuery->exec())
    {
       //读取查询到的记录
       while(sqlQuery->next())
       {
           if(sqlQuery->value(0).toString() != userId){
               QString labelInfo;
               if(ui->chatUserList->currentItem()->text().length() == 8){

                   QString timeStr = sqlQuery->value(2).toString();
                   labelInfo = timeStr.remove(timeStr.size() - 4,4);
                   setInfoToChatRoomLeft(sqlQuery->value(1).toString(),labelInfo,1,frdheadImg);
               } else {
                   QString timeStr = sqlQuery->value(2).toString();
                   labelInfo = sqlQuery->value(0).toString() + " " + timeStr.remove(timeStr.size() - 4,4);
                   for (int i = 0; i < groupMemberIdVtr.size(); ++i) {
                       if(sqlQuery->value(0).toString() == groupMemberIdVtr[i]) {
                           groupMemberImg = groupMemberImgVtr[i];
                           break;
                       }
                   }
                   setInfoToChatRoomLeft(sqlQuery->value(1).toString(),labelInfo,1,groupMemberImg);
               }
           }else {
               QString timeStr = sqlQuery->value(2).toString();
               setInfoToChatRoomRight(sqlQuery->value(1).toString(),timeStr.remove(timeStr.size() - 4,4),2);
           }
       }
    }
    maximumSize();
}

//清空聊天室
void ChatRoom::clearChatItem()
{
    ui->chatContentList->clear();
}

//最小化按钮
void ChatRoom::on_minBtn_clicked()
{
    isClose = false;
    showMinimized();
}

//关闭按钮
void ChatRoom::on_closeBtn_clicked()
{
    isClose=true;
    this->close();
}

//截图按钮
void ChatRoom::on_screenShotBtn_clicked()
{
    connect(captureHelper, SIGNAL(signalCompleteCature(QPixmap)), this, SLOT(onCompleteCature(QPixmap)));
    connect(captureHelper, SIGNAL(signalCustomizeSave(QPixmap)),this,SLOT(onCustomizeSave(QPixmap)));
    captureHelper->show();
}

//监控键盘事件;
void ChatRoom::keyPressEvent(QKeyEvent *event)
{
    // 监控Ctrl + Alt + F键;
    if (event->key() == Qt::Key_F && event->modifiers() == (Qt::AltModifier | Qt::ControlModifier))
    {
        startCatureImage();
    }
}

//按下Ctrl+Alt+D键，开始截图;
void ChatRoom::startCatureImage()
{
    // 点击截图按钮开始截图;
    CaptureScreen* m_captureHelper = new CaptureScreen();
    connect(m_captureHelper, SIGNAL(signalCompleteCature(QPixmap)), this, SLOT(onCompleteCature(QPixmap)));
    connect(m_captureHelper, SIGNAL(signalCustomizeSave(QPixmap)),this,SLOT(onCustomizeSave(QPixmap)));
    m_captureHelper->show();
}

//保存图片
void ChatRoom::onCompleteCature(QPixmap captureImage)
{
    QDateTime dt = QDateTime::currentDateTime();
    QString fileName = QDir::currentPath() +"/CaptureScreen/" + dt.toString() + ".jpg";
    captureImage.save(fileName);
}

//自定义保存图片
void ChatRoom::onCustomizeSave(QPixmap captureImage)
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("save license"),tr("picture.jpg"));
    captureImage.save(fileName);
}

//发送图片
void ChatRoom::on_sendImgBtn_clicked()
{

}

//发送文件
void ChatRoom::on_sendFileBtn_clicked()
{
    sendFileDlg=new SendFileDlg;
    sendFileDlg->rcvId=ui->chatUserList->currentItem()->text();
    sendFileDlg->m_tcpSocket=m_tcpSocket;
    sendFileDlg->show();
    connect(this,SIGNAL(rcvFileCompeteSignal(int)),
            sendFileDlg,SLOT(rcvFileCompeteSlot(int)));
}

//文件接收完成
void ChatRoom::rcvFileCompeteSlot(int)
{
    emit rcvFileCompeteSignal(FileSuccess);
}

//发送消息
void ChatRoom::on_sendMsgBtn_clicked()
{
    QString sendMsgText=ui->chatTextEdit->toPlainText();
    if(sendMsgText.length() == 0) {
        QMessageBox::information(nullptr, "提示", "发送内容不能为空", QMessageBox::Ok);
        return;
    }
    if(sendMsgText.length() >= 150) {
        QMessageBox::information(nullptr, "提示", "字符长度不得超过150", QMessageBox::Ok);
        return;
    }
    chatItem=new FeedBackListItem(this,sendMsgText,2);
    chatItem->rightImage = userHeadImage;
    item=new QListWidgetItem(ui->chatContentList);
    item->setSizeHint(QSize(this->width() - 900,this->height()));
    ui->chatContentList->setItemWidget(item,chatItem);
    ui->chatContentList->scrollToBottom();
    ui->chatTextEdit->clear();
    emit sendMsgToFrdList(ui->chatUserList->currentItem()->text(),sendMsgText);
    connect(chatItem,SIGNAL(sendItemSize(int,int)),this,SLOT(getItemSize(int,int)));
}

//设置左侧的会话消息
void ChatRoom::setInfoToChatRoomLeft(QString chatInfo, QString labelInfo,int type, QImage leftImage)
{
    chatItem=new FeedBackListItem(this,chatInfo,type);
    chatItem->leftImage = leftImage;
    timeLabel=new QLabel(ui->chatContentList);
    timeLabel->setText(labelInfo);
    timeLabel->setFixedHeight(20);
    timeLabel->setAlignment(Qt::AlignLeft);
    itemTime=new QListWidgetItem(ui->chatContentList);
    item=new QListWidgetItem(ui->chatContentList);
    item->setSizeHint(QSize(this->width()-900,this->height() / 10));
    ui->chatContentList->setItemWidget(itemTime,timeLabel);
    ui->chatContentList->setItemWidget(item,chatItem);
    ui->chatContentList->scrollToBottom();
    connect(chatItem,SIGNAL(sendItemSize(int,int)),this,SLOT(getItemSize(int,int)));
}

//设置右侧自己发出的会话消息
void ChatRoom::setInfoToChatRoomRight(QString chatInfo,QString labelInfo, int type)
{
    chatItem=new FeedBackListItem(this,chatInfo,type);
    chatItem->rightImage = userHeadImage;
    timeLabel=new QLabel(ui->chatContentList);
    timeLabel->setText(labelInfo);
    timeLabel->setFixedHeight(20);
    timeLabel->setAlignment(Qt::AlignRight);
    itemTime=new QListWidgetItem(ui->chatContentList);
    item=new QListWidgetItem(ui->chatContentList);
    item->setSizeHint(QSize(this->width() - 900,this->height() / 10));
    ui->chatContentList->setItemWidget(itemTime,timeLabel);
    ui->chatContentList->setItemWidget(item,chatItem);
    ui->chatContentList->scrollToBottom();
    connect(chatItem,SIGNAL(sendItemSize(int,int)),this,SLOT(getItemSize(int,int)));
}

//获取聊天内容尺寸
void ChatRoom::getItemSize(int ,int)
{
    item->setSizeHint(QSize(ui->chatContentList->width(),
                            ui->chatContentList->height()/4));
}

//取消
void ChatRoom::on_cancelBtn_clicked()
{
    ui->chatTextEdit->clear();
}

//点击会话框列表中的联系人
void ChatRoom::on_chatUserList_itemClicked(QListWidgetItem *item)
{
    QString text=item->text();
    QString nickName;
    QImage frdHeadImg;
    if(text.length() == 8){
        //表示是好友
        for (int i = 0; i < frdIdVector.size(); ++i) {
            if(text == frdIdVector[i]){
                frdHeadImg=frdHeadImgVector[i];
                nickName = frdNickNameVctr[i];
                break;
            }
        }
    } else {
        //表示是群聊
        for (int i = 0; i < groupIdVector.size(); ++i) {
            if(text == groupIdVector[i]){
                nickName = groupNickNameVctr[i];
                frdHeadImg = groupHeadImgVector[i];
                break;
            }
        }
    }
    ui->chatUserLabel->setText(nickName);
    clearChatItem();
    QImage groupMemberImg;
    sqlQuery->prepare("select * from ChatMsgWith" + text);
    if(sqlQuery->exec())
    {
       //读取查询到的记录
       while(sqlQuery->next())
       {
           if(sqlQuery->value(0).toString() != userId){
               QString labelInfo;
               if(ui->chatUserList->currentItem()->text().length() == 8){
                   QString timeStr = sqlQuery->value(2).toString();
                   labelInfo = timeStr.remove(timeStr.size() - 4,4);
                   setInfoToChatRoomLeft(sqlQuery->value(1).toString(),labelInfo,1,frdHeadImg);
               } else {
                   QString timeStr = sqlQuery->value(2).toString();
                   labelInfo = sqlQuery->value(0).toString() + " " + timeStr.remove(timeStr.size() - 4,4);
                   for (int i = 0; i < groupMemberIdVtr.size(); ++i) {
                       if(sqlQuery->value(0).toString() == groupMemberIdVtr[i]) {
                           groupMemberImg = groupMemberImgVtr[i];
                           setInfoToChatRoomLeft(sqlQuery->value(1).toString(),labelInfo,1,groupMemberImg);
                           break;
                       }
                   }      
               }
           }else {
               QString timeStr = sqlQuery->value(2).toString();
               setInfoToChatRoomRight(sqlQuery->value(1).toString(),timeStr.remove(timeStr.size() - 4,4),2);
           }
       }
    }
}

//设置背景色
void ChatRoom::setBackColor(QString color)
{
    ui->chatUserList->setStyleSheet("background-color: " + color);
}

//设置背景图片
void ChatRoom::setBackPixmap(QPixmap pixmap)
{
    QPalette palette = ui->chatUserList->palette();
    palette.setBrush(backgroundRole(), QBrush(QPixmap(pixmap)));
    ui->chatUserList->setPalette(palette);
}

//修改字体大小
void ChatRoom::on_fontSizeComboBox_currentIndexChanged(int index)
{
   index=ui->fontComboBox->currentIndex();
   QFont chatEditFont;
   chatEditFont.setPointSize(ui->fontSizeComboBox->currentText().toInt());
   ui->chatTextEdit->setFont(chatEditFont);
}

ChatRoom::~ChatRoom()
{
    sendFileDlg->close();
    delete ui;
}
