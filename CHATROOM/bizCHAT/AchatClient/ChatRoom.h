#ifndef CHATROOM_H
#define CHATROOM_H

#include <QDialog>
#include <QDir>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QAction>
#include <QPalette>
#include <QFileDialog>
#include <QPushButton>
#include <QImage>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QListWidget>
#include <QStackedWidget>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include "FeedBackListItem.h"
#include "CaptureScreen.h"
#include "SendFileDlg.h"

namespace Ui {
class ChatRoom;
}

class ChatRoom : public QDialog
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();
    void addChatUser(QString strId,QString nickName,QImage frdheadImg);        //新的聊天信息
    void setBackColor(QString color);
    void setBackPixmap(QPixmap pixmap);
    void setInfoToChatRoomLeft(QString,QString,int,QImage);
    void setInfoToChatRoomRight(QString,QString,int);
    void clearChatItem();

    QString makeColorString(const QColor &color, const QString type);
    QTcpSocket *m_tcpSocket;
    QImage userHeadImage;
    QVector<QString> frdIdVector;
    QVector<QString> frdNickNameVctr;
    QVector<QImage> frdHeadImgVector;
    QVector<QString> groupIdVector;
    QVector<QString> groupNickNameVctr;
    QVector<QImage> groupHeadImgVector;
    QVector<QStringList> memberOfGroupListVtr;
    QVector<QString> groupMemberIdVtr;
    QVector<QImage> groupMemberImgVtr;
    QString userId;
    bool isClose=true;

private:
    Ui::ChatRoom *ui;
    QLabel *timeLabel;
    QListWidget *mbrOfGrpLstWdgt;
    SendFileDlg *sendFileDlg;
    CaptureScreen* captureHelper;
    QSqlDatabase database;
    QSqlQuery* sqlQuery;
    FeedBackListItem* chatItem;
    QListWidgetItem* item;
    QListWidgetItem* itemTime;
    void keyPressEvent(QKeyEvent *event);
    void startCatureImage();
    //鼠标拖动窗口
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //记录窗口当前的位置
    QPoint StartPos;

signals:
    void sendMsgToFrdList(QString,QString);
    void rcvFileCompeteSignal(int);

private slots:
    void on_minBtn_clicked();               //最小化按钮
    void on_closeBtn_clicked();             //关闭按钮          
    void on_screenShotBtn_clicked();        //截图按钮
    void on_sendImgBtn_clicked();           //发送图片
    void on_sendFileBtn_clicked();          //发送文件        
    void on_sendMsgBtn_clicked();           //发送消息按钮
    void on_cancelBtn_clicked();            //取消按钮
    void getItemSize(int, int);             //获取聊天内容尺寸
    void on_chatUserList_itemClicked(QListWidgetItem *item);
    void onCompleteCature(QPixmap captureImage);        //保存图片
    void onCustomizeSave(QPixmap captureImage);         //自定义保存图片
    void on_fontSizeComboBox_currentIndexChanged(int index);
    void rcvFileCompeteSlot(int);
};

#endif // CHATROOM_H
