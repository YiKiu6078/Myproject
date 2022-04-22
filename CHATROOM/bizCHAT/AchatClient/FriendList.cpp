#include "FriendList.h"
#include "ui_FriendList.h"

FriendList::FriendList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FriendList)
{
    ui->setupUi(this);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setStyleSheet("background-color: #729FCF");

    chatRoom = new ChatRoom;
    connect(chatRoom,SIGNAL(sendMsgToFrdList(QString,QString)),
            this,SLOT(rcvMsgFromChatRoom(QString,QString)));
    connect(this,SIGNAL(rcvFileCompeteSignal(int)),
            chatRoom,SLOT(rcvFileCompeteSlot(int)));
    QMenu *optionMenu=new QMenu();
    QAction *OnlineAction=new QAction("重新上线");
    OnlineAction->setIcon(QIcon(":/Img/picture/Online.jpeg"));
    optionMenu->addAction(OnlineAction);
    QAction *OfflineAction=new QAction("离线");
    OfflineAction->setIcon(QIcon(":/Img/picture/OffLine.jpg"));
    optionMenu->addAction(OfflineAction);
    QAction *personInfoAction=new QAction("查看个人信息");
    optionMenu->addAction(personInfoAction);
    connect(personInfoAction,SIGNAL(triggered()),this,SLOT(showPersonInfo()));
    QAction *changePswdAction=new QAction("修改密码");
    optionMenu->addAction(changePswdAction);
    QAction *manageFrdGroupAction=new QAction("管理好友分组");
    optionMenu->addAction(manageFrdGroupAction);
    QAction *exitAction=new QAction("退出");
    exitAction->setIcon(QIcon(":/Img/picture/exit.jpg"));
    optionMenu->addAction(exitAction);
    ui->optionBtn->setPopupMode(QToolButton::InstantPopup   );
    ui->optionBtn->setMenu(optionMenu);

    //修改相对路径为exe目录路径
    QDir dir;
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    QAction *searchAction = new QAction(ui->searchLineEdit);
    searchAction->setIcon(QIcon("./picture/search1.jpg"));
    ui->searchLineEdit->setPlaceholderText(tr("搜索联系人"));
    ui->searchLineEdit->addAction(searchAction,QLineEdit::LeadingPosition);
    ui->searchLineEdit->setStyleSheet("background-color: white");

    connect(ui->chatBtn,SIGNAL(clicked()),this,SLOT(slotChatBtnClicked()));
    connect(ui->contactsBtn,SIGNAL(clicked()),this,SLOT(slotContBtnClicked()));
    connect(ui->groupBtn,SIGNAL(clicked()),this,SLOT(slotGroupBtnClicked()));

    frdTreeWdgt=new QTreeWidget;
    frdTreeWdgt->setIndentation(7);
    frdTreeWdgt->setContextMenuPolicy(Qt::CustomContextMenu);
    m_ContextMenu = new QMenu;
    QAction *m_moveAction = new QAction("移动分组", this);
    connect(m_moveAction,SIGNAL(triggered()),this,SLOT(showMoveFrdSlot()));
    QAction *m_delAction = new QAction("删除好友", this);
    connect(m_delAction,SIGNAL(triggered()),this,SLOT(showDeleteFrdSlot()));
    m_ContextMenu->addAction(m_moveAction);
    m_ContextMenu->addAction(m_delAction);

    //和该策略对应的信号，showListWidgetMenuSlot为自己定义的槽函数.
    connect(frdTreeWdgt, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showTreeWidgetMenuSlot(QPoint)));

    chatListWidget=new QListWidget;
    groupListWidget=new QListWidget;

    ui->stackWidget->setStyleSheet("background-color: white");
    QHBoxLayout *contactLayout=new QHBoxLayout;
    contactLayout->addWidget(frdTreeWdgt);
    contactsWidget->setLayout(contactLayout);

    QHBoxLayout *chatLayout=new QHBoxLayout;
    chatLayout->addWidget(chatListWidget);
    chatWidget->setLayout(chatLayout);

    QHBoxLayout *groupLayout=new QHBoxLayout;
    groupLayout->addWidget(groupListWidget);
    groupWidget->setLayout(groupLayout);

    ui->stackWidget->addWidget(contactsWidget);
    ui->stackWidget->addWidget(chatWidget);
    ui->stackWidget->addWidget(groupWidget);
    connect(frdTreeWdgt,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this,SLOT(showChatRoom(QTreeWidgetItem*,int)));
    connect(chatListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,SLOT(showChatRoom(QListWidgetItem*)));
    connect(groupListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this,SLOT(showGroupChatRoom(QListWidgetItem*)));

    ui->addFrdBtn->setIcon(QIcon(":/Img/picture/AddFriend.jpg"));
    ui->addGroupBtn->setIcon(QIcon(":/Img/picture/add.jpg"));
    ui->colorThemeBtn->setIcon(QIcon(":/Img/picture/theme.jpg"));
    ui->ImgThemeBtn->setIcon(QIcon(":/Img/picture/ImgTheme.jpg"));

    ui->chatBtn->setStyleSheet("background-color: white");
    ui->groupBtn->setStyleSheet("background-color: white");;
    ui->contactsBtn->setStyleSheet("background-color: white");
    ui->addFrdBtn->setStyleSheet("background-color: white");
    ui->addGroupBtn->setStyleSheet("background-color: white");;
    ui->colorThemeBtn->setStyleSheet("background-color: white");
    ui->ImgThemeBtn->setStyleSheet("background-color: white");

    connect(ui->addFrdBtn,SIGNAL(clicked()),this,SLOT(showAddFrdBtn()));
    connect(ui->addGroupBtn,SIGNAL(clicked()),this,SLOT(showAddGroupBtn()));
    connect(ui->colorThemeBtn,SIGNAL(clicked()),this,SLOT(showColorThemeBtn()));
    connect(ui->ImgThemeBtn,SIGNAL(clicked()),this,SLOT(showImgThemeBtn()));

    m_udpSocket=new QUdpSocket;

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

void FriendList::mouseMoveEvent(QMouseEvent *event)
{
    QPoint EndPos;
    if ( event->buttons() == Qt::LeftButton )
    {
        EndPos = event->globalPos() - StartPos;
        this->move(EndPos);
    }
}

void FriendList::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton) {
        //记录窗口此时的坐标
        StartPos = event->globalPos() - this->frameGeometry().topLeft();
    }
}

//接收服务器发来的个人信息
void FriendList::rcvPersonInfo(QString nickName, QString signature,QString age,
               QString sex, QString email,QImage headImg,QStringList frdGroupList)
{
    ui->nickNameLabel->setText(nickName);
    ui->signatureLabel->setText(signature);
    userHeadImg=headImg;
    QPixmap pixmap(60,60);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0, 0, 60, 60);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, 60, 60,QPixmap::fromImage(headImg));
    ui->headImgLabel->setPixmap(pixmap);
    this->sex=sex;
    this->age=age;
    this->email=email;
    this->frdGroupList=frdGroupList;

    initFrdGroupList();

    personInfo=new PersonInfo;
    personInfo->rcvPersonInfo(userId,nickName,signature,age,sex,email);

    if(!m_udpSocket->bind(QHostAddress("192.168.2.131"),clientPort,QAbstractSocket::ShareAddress)){
        qDebug()<<"Udp socket bind failed!"<<m_udpSocket->errorString()<<endl;
    }
    connect(m_udpSocket,SIGNAL(readyRead()),this,SLOT(udpReadyRead()),Qt::DirectConnection);   
}

//获取IpV4地址
QString FriendList::getIp()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)   //我们使用IPv4地址
        {
            if(address.toString().contains("127.0."))
                continue;
            return address.toString();
        }
    }
    return nullptr;
}

//展示个人信息
void FriendList::showPersonInfo()
{
    personInfo->show();
}

//向服务器发送tcp消息
void FriendList::sendTcpMsg(QByteArray data)
{
    if(m_tcpSocket->write(data) < 0){
        qDebug()<<"Send Message Failed!"<<endl;
    }
    m_tcpSocket->flush();
}

//服务器断开连接
void FriendList::disconnectToServer()
{
    ui->headImgLabel->setEnabled(false);
}

//向服务器发送udp消息
void FriendList::sendUdpMsg(QByteArray data)
{
    if(m_udpSocket->writeDatagram(data,QHostAddress("192.168.2.131"),UDP_SERVER_PORT)<0){
        qDebug()<<"send udp message failed"<<endl;
    }
}

//播放提示音效
void FriendList::playAudio()
{
    QMediaPlayer * player = new QMediaPlayer;
    QString runPath = QCoreApplication::applicationDirPath();//获取当前exe所在路径
    QString audioPath = runPath + "/MsgMusic.mp3";
    player->setMedia(QUrl::fromLocalFile(audioPath));
    player->setVolume(50);
    player->play();
}

//读取服务器发来的udp消息
void FriendList::udpReadyRead()
{
    QByteArray datagram;
    datagram.resize(m_udpSocket->pendingDatagramSize());
    m_udpSocket->readDatagram(datagram.data(),datagram.size());//接收一个数据报，并将其存储在data中。返回的是数据报的长度
    QDataStream in(&datagram,QIODevice::ReadOnly);
    int msgType;
    in >> msgType;
    switch (msgType) {
    case ChatMsg:
    {
        QString sendId,chatInfo;
        in>>sendId>>chatInfo;
        QImage frdheadImg;
        for (int i = 0; i < frdIdVector.size(); ++i) {
            if(frdIdVector[i] == sendId){
               frdheadImg = frdHeadImgVector[i];
               break;
            }
        }
        //播放提示音效
        playAudio();
        ui->chatBtn->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        ui->chatBtn->setIcon(QIcon(":/Img/picture/Msg.jpeg"));
        addChatUser(sendId,frdheadImg);
        //将接收到消息的用户的字体设置为红色,用于标示接收到消息
        for (int i = 0; i < chatListWidget->count();++i) {
            if(sendId == chatListWidget->item(i)->text()){
                chatListWidget->item(i)->setTextColor(QColor(255,0,0,255));
                chatListWidget->setStyleSheet("selection-color:red");
                break;
            }
        }
        sqlQuery->prepare("insert into chatMsgWith" + sendId + "(ID,聊天消息,时间) values(?,?,?)");
        sqlQuery->addBindValue(sendId);
        sqlQuery->addBindValue(chatInfo);
        sqlQuery->addBindValue(QDateTime::currentDateTime());
        sqlQuery->exec();
        break;
    }
    case GroupChatMsg:{
        QString rcvGroupId,sendId,chatInfo;
        in>>rcvGroupId>>sendId>>chatInfo;
        QImage groupHeadImg;
        for (int i = 0; i < groupIdVector.size(); ++i) {
            if(groupIdVector[i] == rcvGroupId){
               groupHeadImg = groupHeadImgVector[i];
               break;
            }
        }
        //播放提示音效
        playAudio();
        ui->chatBtn->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        ui->chatBtn->setIcon(QIcon(":/Img/picture/Msg.jpeg"));
        addChatUser(rcvGroupId,groupHeadImg);
        //将接收到消息的群聊的字体设置为红色,用于标示接收到消息
        for (int i = 0; i < chatListWidget->count();++i) {
            if(rcvGroupId == chatListWidget->item(i)->text()){
                chatListWidget->item(i)->setTextColor(QColor(255,0,0,255));
                chatListWidget->setStyleSheet("selection-color:red");
                break;
            }
        }
        sqlQuery->prepare("insert into chatMsgWith" + rcvGroupId + "(ID,聊天消息,时间) values(?,?,?)");
        sqlQuery->addBindValue(sendId);
        sqlQuery->addBindValue(chatInfo);
        sqlQuery->addBindValue(QDateTime::currentDateTime());
        if(!sqlQuery->exec()) {
            qDebug()<<"Insert chat infomation to table failed:"<<sqlQuery->lastError()<<endl;
        }
        break;
    }
    case ImgOfGroupMbr:
    {
        QString memberId;
        QByteArray ImgArray;
        in>>memberId>>ImgArray;
        QBuffer ImgBuffer(&ImgArray);
        QImageReader reader(&ImgBuffer,"JPG");
        QImage headImg=reader.read();
        for (int i = 0;i < groupMemberIdVtr.size();++i) {
            if(memberId == groupMemberIdVtr[i]){
                return;
            }
        }
        groupMemberIdVtr.push_back(memberId);
        groupMemberImgVtr.push_back(headImg);

        break;
    }
    default:
        break;
    }
}

//初始化分组列表
void FriendList::initFrdGroupList()
{
    frdTreeWdgt->headerItem()->setText(0,QString());
    frdTreeWdgt->headerItem()->setHidden(true);
    frdTreeWdgt->setIconSize(QSize(40,40));
    int countOfGroup=frdGroupList.size();
    if(countOfGroup == 0) {
        QTreeWidgetItem *treeItem = new QTreeWidgetItem(frdTreeWdgt, QStringList(QString("我的好友")));
        QTreeWidgetItem *treeItem1 = new QTreeWidgetItem(treeItem, QStringList(QString("QQ小冰")));
        QVariant var0(0);
        treeItem->setData(0,Qt::UserRole,var0);
        treeItem->setSizeHint(0,QSize(40,40));
        QPixmap pixmap(40,40);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        QPainterPath path;
        path.addEllipse(0, 0, 40, 40);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, 40, 40,QPixmap(":/Img/picture/QQ.jpg"));
        treeItem1->setIcon(0,QIcon(pixmap));
        treeItem->addChild(treeItem1);
        ui->stackWidget->setCurrentWidget(chatWidget);
    } else {
        frdTreeWdgt->setRootIsDecorated(true);
        frdTreeWdgt->setExpandsOnDoubleClick(false);
        for(int i = 0; i < countOfGroup; ++i){
            treeFrdGroupItem[i] = new QTreeWidgetItem(frdTreeWdgt, QStringList(frdGroupList.at(i)));
        }
        QTreeWidgetItem *treeItem = new QTreeWidgetItem(treeFrdGroupItem[0], QStringList(QString("QQ小冰")));
        QVariant var0(0);
        treeItem->setData(0,Qt::UserRole,var0);
        treeItem->setSizeHint(0,QSize(40,40));
        QPixmap pixmap(40,40);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        QPainterPath path;
        path.addEllipse(0, 0, 40, 40);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, 40, 40,QPixmap(":/Img/picture/QQ.jpg"));
        treeItem->setIcon(0,QIcon(pixmap));
        treeFrdGroupItem[0]->addChild(treeItem);
        ui->stackWidget->setCurrentWidget(chatWidget);
        QTreeWidgetItemIterator it(frdTreeWdgt);
    }
}

//初始化好友分组
void FriendList::initFrdGroupInfo(QString id, QString nickName, QString groupName,
                                  QByteArray headImgArray)
{
    for (int i = 0; i < frdGroupList.size(); ++i) {
        if(groupName == treeFrdGroupItem[i]->text(0)){
            QTreeWidgetItem *treeItem = new QTreeWidgetItem(treeFrdGroupItem[i], QStringList(id));
            QVariant var1(1);
            treeItem->setData(0,Qt::UserRole,var1);
            treeItem->setSizeHint(0,QSize(50,50));
            //读取图像信息
            QBuffer ImgBuffer(&headImgArray);
            QImageReader reader(&ImgBuffer,"JPG");
            QImage headImg=reader.read();
            //设置图像
            QPixmap pixmap(40,40);
            pixmap.fill(Qt::transparent);
            QPainter painter(&pixmap);
            painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
            QPainterPath path;
            path.addEllipse(0, 0, 40, 40);
            painter.setClipPath(path);
            painter.drawPixmap(0, 0, 40, 40,QPixmap::fromImage(headImg));
            treeItem->setIcon(0,QIcon(pixmap));

            treeFrdGroupItem[i]->addChild(treeItem);
            frdIdVector.push_back(id);
            frdNickNameVctr.push_back(nickName);
            frdHeadImgVector.push_back(headImg);
        }
    }
}

//改变好友分组
void FriendList::showMoveFrdSlot()
{

}

//删除好友信号
void FriendList::showDeleteFrdSlot()
{
    if(QMessageBox::question(this,tr("提示"),QString("确定删除好友 %1 ？").arg(frdTreeWdgt->currentItem()->text(0)),
                             QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
        QDataStream out(&sendData,QIODevice::WriteOnly);
        out<<RemoveFried<<frdTreeWdgt->currentItem()->text(0);
        sendTcpMsg(sendData);
        sendData.clear();
        out.device()->seek(0);
        QTreeWidgetItem *currentItem = frdTreeWdgt->currentItem();
        delete currentItem->parent()->takeChild(frdTreeWdgt->currentIndex().row());
    }
}

//接收到删除好友信息
void FriendList::rcvDeleteFrd(QString deleteId)
{
    QTreeWidgetItemIterator it(frdTreeWdgt);
    while(*it) {
        QVariant var = (*it)->data(0,Qt::UserRole);
        if((*it)->text(0) == deleteId && (var == 1)) {
            delete (*it)->parent()->takeChild(frdTreeWdgt->currentIndex().row());
            for (int i = 0 ; i < frdIdVector.size(); ++i) {
                if(deleteId == frdIdVector[i]) {
                    frdIdVector.removeAt(i);
                    frdNickNameVctr.removeAt(i);
                    frdHeadImgVector.removeAt(i);
                }
            }
            return;
        }
        ++it;
    }
}

//初始化群组列表
void FriendList::initGroupList(QString groupId,QString groupNickName,QByteArray groupHeadImg,QStringList memberOfGroup)
{
    QListWidgetItem *item=new QListWidgetItem;
    item->setSizeHint(QSize(100,40));
    //读取图像信息
    QBuffer ImgBuffer(&groupHeadImg);
    QImageReader reader(&ImgBuffer,"JPG");
    QImage groupheadImg=reader.read();
    //设置图像
    QPixmap pixmap(40,40);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0, 0, 40, 40);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, 40, 40,QPixmap::fromImage(groupheadImg));
    item->setIcon(QIcon(pixmap));
    item->setText(groupId);
    groupListWidget->insertItem(0,item);

    groupIdVector.push_back(groupId);
    groupNickNameVctr.push_back(groupNickName);
    groupHeadImgVector.push_back(groupheadImg);
    memberOfGroupVctr.push_back(memberOfGroup);
    //请求群聊用户的头像信息
    for (int i = 0; i < memberOfGroup.size(); ++i) {
        QDataStream out(&sendData,QIODevice::WriteOnly);
        out<<ImgOfGroupMbr<<memberOfGroup.at(i);
        sendUdpMsg(sendData);
        sendData.clear();
        out.device()->seek(0);
    }
}

//会话按钮槽函数
void FriendList::slotChatBtnClicked()
{
    ui->chatBtn->setIcon(QIcon(""));
    ui->stackWidget->setCurrentWidget(chatWidget);
}

//联系人按钮槽函数
void FriendList::slotContBtnClicked()
{
    chatRoom->userId = userId;
    chatRoom->frdIdVector=frdIdVector;
    chatRoom->frdNickNameVctr=frdNickNameVctr;
    chatRoom->frdHeadImgVector=frdHeadImgVector;
    ui->stackWidget->setCurrentWidget(contactsWidget);
}

//群聊按钮槽函数
void FriendList::slotGroupBtnClicked()
{
    chatRoom->groupIdVector=groupIdVector;
    chatRoom->groupNickNameVctr=groupNickNameVctr;
    chatRoom->groupHeadImgVector=groupHeadImgVector;
    chatRoom->memberOfGroupListVtr=memberOfGroupVctr;
    chatRoom->groupMemberIdVtr=groupMemberIdVtr;
    chatRoom->groupMemberImgVtr=groupMemberImgVtr;
    ui->stackWidget->setCurrentWidget(groupWidget);
}

//好友列表右键菜单
void FriendList::showTreeWidgetMenuSlot(QPoint pos)
{
    QTreeWidgetItem* curItem = frdTreeWdgt->itemAt(pos);  //获取当前被点击的节点
    if(curItem == nullptr)
        return;           //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
    QVariant var = curItem->data(0,Qt::UserRole);
    if(var == 1) {
        m_ContextMenu->exec(QCursor::pos());
    }
}

//双击联系人列表打开聊天室
void FriendList::showChatRoom(QTreeWidgetItem*,int)
{
    chatListWidget->setStyleSheet("selection-color:white");
    for (int i = 0; i < frdGroupList.count(); ++i) {
        if(frdTreeWdgt->currentItem()->text(0) == frdGroupList.at(i)){
            return;
        }
    }
    QImage frdheadImg;
    QString nickName;
    for (int i = 0; i < frdIdVector.size(); ++i) {
        if(frdIdVector[i] == frdTreeWdgt->currentItem()->text(0)){
           frdheadImg = frdHeadImgVector[i];
           nickName = frdNickNameVctr[i];
           break;
        }
    }
    chatRoom->clearChatItem();
    sqlQuery->prepare("select * from ChatMsgWith" + frdTreeWdgt->currentItem()->text(0));
    if(sqlQuery->exec())
    {
       //读取查询到的记录
       while(sqlQuery->next())
       {
           if(sqlQuery->value(0).toString() == frdTreeWdgt->currentItem()->text(0)){
               QString timeStr=sqlQuery->value(2).toString();  //时间的显示格式
               chatRoom->setInfoToChatRoomLeft(sqlQuery->value(1).toString(),timeStr,CHATROOM_LEFT,frdheadImg);
           }else if (sqlQuery->value(0).toString() == userId) {
               QString timeStr=sqlQuery->value(2).toString();  //时间的显示格式
               chatRoom->setInfoToChatRoomRight(sqlQuery->value(1).toString(),timeStr,CHATROOM_RIGHT);
           }
       }
    }
    if(chatRoom->isClose==true){
        chatRoom->show();
    }else {
        chatRoom->setWindowState((chatRoom->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    }

    chatRoom->m_tcpSocket = m_tcpSocket;

    chatRoom->userHeadImage=userHeadImg;
    chatRoom->addChatUser(frdTreeWdgt->currentItem()->text(0),nickName,frdheadImg);
    addChatUser(frdTreeWdgt->currentItem()->text(0),frdheadImg);

}

//双击会话列表打开聊天室
void FriendList::showChatRoom(QListWidgetItem *item)
{
    chatRoom->groupIdVector=groupIdVector;
    chatRoom->groupNickNameVctr=groupNickNameVctr;
    chatRoom->groupHeadImgVector=groupHeadImgVector;
    chatRoom->memberOfGroupListVtr=memberOfGroupVctr;
    chatRoom->groupMemberIdVtr=groupMemberIdVtr;
    chatRoom->groupMemberImgVtr=groupMemberImgVtr;
    chatListWidget->setStyleSheet("selection-color:white");
    QImage headImg;
    QString nickName;
    if(item->text().length() == 8){
        //表示与好友对话
        item->setTextColor(QColor(Qt::black));
        for (int i = 0; i < frdIdVector.size(); ++i) {
            if(frdIdVector[i] == item->text()){
               headImg = frdHeadImgVector[i];
               nickName = frdNickNameVctr[i];
               break;
            }
        }
    } else {
        //表示群聊会话
        item->setTextColor(QColor(Qt::black));
        for (int i = 0; i < groupIdVector.size(); ++i) {
            if(groupIdVector[i] == item->text()){
               nickName = groupNickNameVctr[i];
               break;
            }
        }
    }
    chatRoom->clearChatItem();
    chatRoom->userHeadImage = userHeadImg;
    sqlQuery->prepare("select * from ChatMsgWith" + item->text());
    if(sqlQuery->exec())
    {
       //读取查询到的记录
       while(sqlQuery->next())
       {
           if (sqlQuery->value(0).toString() == userId) {
               QString timeStr=sqlQuery->value(2).toString();  //时间的显示格式
               chatRoom->setInfoToChatRoomRight(sqlQuery->value(1).toString(),timeStr,CHATROOM_RIGHT);
           } else {
               if(item->text().length() == 10) {
                   for (int i = 0; i < groupMemberIdVtr.size(); ++i) {
                       if(sqlQuery->value(0).toString() == groupMemberIdVtr[i]) {
                           headImg = groupMemberImgVtr[i];
                           QString timeStr=sqlQuery->value(2).toString();  //时间的显示格式
                           QString labelInfo=sqlQuery->value(0).toString() + timeStr.remove(timeStr.size() - 4,4);
                           chatRoom->setInfoToChatRoomLeft(sqlQuery->value(1).toString(),labelInfo,CHATROOM_LEFT,headImg);
                           break;
                       }
                   }
               } else {
                   QString timeStr=sqlQuery->value(2).toString();  //时间的显示格式
                   chatRoom->setInfoToChatRoomLeft(sqlQuery->value(1).toString(),timeStr.remove(timeStr.size() - 4,4),CHATROOM_LEFT,headImg);
               }

           }
       }
    }
    if(chatRoom->isClose==true){
        chatRoom->show();
    }else {
        chatRoom->setWindowState((chatRoom->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    }
    chatRoom->m_tcpSocket = m_tcpSocket;
    chatRoom->addChatUser(item->text(),nickName,headImg);
}

//双击群聊对象打开群聊聊天室
void FriendList::showGroupChatRoom(QListWidgetItem*item)
{
    QImage groupHeadImg;
    QString nickName;
    for (int i = 0; i < groupIdVector.size(); ++i) {
        if(groupIdVector[i] == item->text()){
           groupHeadImg = groupHeadImgVector[i];
           nickName = groupNickNameVctr[i];
           break;
        }
    }
    chatRoom->clearChatItem();
    chatRoom->userHeadImage = userHeadImg;
    sqlQuery->prepare("select * from ChatMsgWith" + item->text());
    if(sqlQuery->exec())
    {
       //读取查询到的记录
       while(sqlQuery->next())
       {
           if(sqlQuery->value(0).toString() != userId){
               QString timeStr = sqlQuery->value(2).toString();
               QString labelInfo=sqlQuery->value(0).toString() + timeStr.remove(timeStr.size() - 4,4);
               chatRoom->setInfoToChatRoomLeft(sqlQuery->value(1).toString(),labelInfo,CHATROOM_LEFT,groupHeadImg);
           }else {
               QString timeStr=sqlQuery->value(2).toString();  //时间的显示格式
               chatRoom->setInfoToChatRoomRight(sqlQuery->value(1).toString().remove(timeStr.size() - 4,4),
                                                timeStr,CHATROOM_RIGHT);
           }
       }
    }
    if(chatRoom->isClose==true){
        chatRoom->show();
    }else {
        chatRoom->setWindowState((chatRoom->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
    }
    chatRoom->m_tcpSocket = m_tcpSocket;
    chatRoom->addChatUser(item->text(),nickName,groupHeadImg);
    addChatUser(item->text(),groupHeadImg);
}

//增加会话列表
void FriendList::addChatUser(QString strId, QImage frdHeadImg)
{
    //同时会话列表中也要相应增加窗口
    for (int i = 0; i < chatListWidget->count();++i) {
        if(strId == chatListWidget->item(i)->text()){
            chatListWidget->setCurrentRow(i);
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
    painter.drawPixmap(0, 0, 40, 40,QPixmap::fromImage(frdHeadImg));
    item->setIcon(QIcon(pixmap));
    item->setText(strId);
    chatListWidget->insertItem(0,item);
    chatListWidget->setCurrentRow(0);
}

//接收从聊天室发来的会话消息
void FriendList::rcvMsgFromChatRoom(QString chatId,QString chatInfo)
{
    sqlQuery->prepare("insert into chatMsgWith" + chatId + "(ID,聊天消息,时间) values(?,?,?)");
    sqlQuery->addBindValue(userId);
    sqlQuery->addBindValue(chatInfo);
    sqlQuery->addBindValue(QDateTime::currentDateTime());
    sqlQuery->exec();
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out<<ChatMsg<<userId<<chatId<<chatInfo;
    sendUdpMsg(sendData);
    sendData.clear();
    out.device()->seek(0);
}

//添加好友
void FriendList::showAddFrdBtn()
{
    AddFrdDlg *addFrdDlg=new AddFrdDlg;
    addFrdDlg->setWindowTitle("添加好友");
    addFrdDlg->userId=userId;
    addFrdDlg->show();
    connect(addFrdDlg,SIGNAL(sendAddUserId(QString)),this,SLOT(rcvAddUserId(QString)));
}

//添加群聊
void FriendList::showAddGroupBtn()
{
    AddFrdDlg *addFrdDlg=new AddFrdDlg;
    addFrdDlg->setWindowTitle("添加群聊");
    addFrdDlg->userId=userId;
    addFrdDlg->show();
    connect(addFrdDlg,SIGNAL(sendAddGroupId(QString)),this,SLOT(rcvAddGroupId(QString)));
}

//颜色转换成字符串
QString FriendList::makeColorString(const QColor &color, const QString type)
{
    if(type == "RGBA") {
         return QString("rgba(%1, %2, %3, %4)")
                    .arg(color.red())
                    .arg(color.green())
                    .arg(color.blue())
                    .arg(color.alpha());
    }
    if(type == "RGB") {
        return QString("rgba(%1, %2, %3)")
                    .arg(color.red())
                    .arg(color.green())
                    .arg(color.blue());
    }
    if(type == "HEX") {

        return QString().sprintf("#%1%02X%02X%02X",
                                     color.red(),
                                     color.green(),
                                     color.blue()).arg(color.alpha() != 255 ? QString().sprintf("%02X", color.alpha()) : QString());
    }
    return color.name();
}

//更换颜色皮肤
void FriendList::showColorThemeBtn()
{
    QColor color = QColorDialog::getColor(Qt::red, this,tr("颜色对话框"),QColorDialog::ShowAlphaChannel);
    QString strColor=makeColorString(color,"RGBA");
    this->setStyleSheet("background-color: " + strColor);
    chatRoom->setBackColor(strColor);
}

//更换图片皮肤
void FriendList::showImgThemeBtn()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("选择图像"),"",
                                                  tr("Images (*.png *.bmp *.jpg)"));
    if(fileName.isEmpty()){
        return;
    } else {
        QPixmap pixmap;
        if(!(pixmap.load(fileName))) //加载图像
        {
            QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
            return;
        }
        chatRoom->setBackPixmap(pixmap);
    }
    setStyleSheet("QDialog#FriendList{border-image:url(" + fileName + ")}");
}

//将添加的好友信息发送给服务器
void FriendList::rcvAddUserId(QString addId)
{
    QTreeWidgetItemIterator it(frdTreeWdgt);
    while (*it) {
        if(addId == (*it)->text(0)){
            QMessageBox::information(this,"提示","您的好友列表已经有该好友了，请不要重复添加");
            return;
        }
        ++it;
    }
    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out<<AddFriend<<userId<<addId;
    sendTcpMsg(sendData);
    sendData.clear();
}

//新添加的好友
void FriendList::rcvNewFrd(QString rcvId, QString nickName, QImage headImg)
{
    frdIdVector.push_back(rcvId);
    frdNickNameVctr.push_back(nickName);
    frdHeadImgVector.push_back(headImg);
    QTreeWidgetItemIterator it(frdTreeWdgt);
    while (*it) {
        if((*it)->text(0) == "我的好友"){
            QTreeWidgetItem *treeItem = new QTreeWidgetItem((*it), QStringList(rcvId));
            treeItem->setSizeHint(0,QSize(50,50));
            //设置图像
            QPixmap pixmap(40,40);
            pixmap.fill(Qt::transparent);
            QPainter painter(&pixmap);
            painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
            QPainterPath path;
            path.addEllipse(0, 0, 40, 40);
            painter.setClipPath(path);
            painter.drawPixmap(0, 0, 40, 40,QPixmap::fromImage(headImg));
            treeItem->setIcon(0,QIcon(pixmap));
            (*it)->addChild(treeItem);
            frdIdVector.push_back(rcvId);
            frdHeadImgVector.push_back(headImg);
            return;
        }
        ++it;
    }
}

//将添加群聊的信息发给服务器
void FriendList::rcvAddGroupId(QString groupId)
{
    for (int i = 0; i < groupListWidget->count(); ++i) {
        if(groupId == groupListWidget->item(i)->text()) {
            QMessageBox::information(this,"提示","您已经在该群聊中了，请不要重复添加");
            return;
        }
    }
    QByteArray sendData;
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out<<AddGroup<<userId<<groupId;
    sendTcpMsg(sendData);
    sendData.clear();
}

//新添加的群聊
void FriendList::rcvNewGroup(QString groupId,QString groupNickName,QByteArray groupHeadImg,QStringList memberOfGroup)
{
    QListWidgetItem *item=new QListWidgetItem;
    item->setSizeHint(QSize(100,40));
    //读取图像信息
    QBuffer ImgBuffer(&groupHeadImg);
    QImageReader reader(&ImgBuffer,"JPG");
    QImage groupheadImg=reader.read();
    //设置图像
    QPixmap pixmap(40,40);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QPainterPath path;
    path.addEllipse(0, 0, 40, 40);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, 40, 40,QPixmap::fromImage(groupheadImg));
    item->setIcon(QIcon(pixmap));
    item->setText(groupId);
    groupListWidget->insertItem(0,item);

    groupIdVector.push_back(groupId);
    groupNickNameVctr.push_back(groupNickName);
    groupHeadImgVector.push_back(groupheadImg);
    memberOfGroupVctr.push_back(memberOfGroup);
}

//最小化
void FriendList::on_minBtn_clicked()
{
    showMinimized();
}

//关闭按钮
void FriendList::on_closeBtn_clicked()
{
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out<<Leave<<userId;
    sendTcpMsg(sendData);
    sendData.clear();
    chatRoom->close();
    this->close();
}

//搜索功能
void FriendList::on_searchLineEdit_textChanged(const QString &str)
{
    QTreeWidgetItemIterator it(frdTreeWdgt);
    if(str.length() == 0) {
        while (*it) {
            (*it)->setBackgroundColor(0,QColor(Qt::white));
            ++it;
        }
        return;
    }
    while (*it)
    {
        if((*it)->text(0).contains(str))
        {
            (*it)->setBackgroundColor(0,QColor(Qt::green));
            QTreeWidgetItem *item = *it;
            //显示父节点
            while (item->parent())
            {
                item->parent()->setBackgroundColor(0,QColor(Qt::green));
                item = item->parent();
            }
        } else {
            (*it)->setBackgroundColor(0,QColor(Qt::white));
        }
        ++it;
    }
}

//服务器文件接收完成消息
void FriendList::rcvFileCompeteSlot(int)
{
    emit rcvFileCompeteSignal(FileSuccess);
}

FriendList::~FriendList()
{
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out<<Leave<<userId;
    sendTcpMsg(sendData);
    sendData.clear();
    chatRoom->close();
    delete ui;
}





