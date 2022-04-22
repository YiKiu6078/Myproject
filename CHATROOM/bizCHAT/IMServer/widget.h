#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <QUdpSocket>
#include "userui.h"
#include "usergroup.h"
#include "servergenerinfoui.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:

    void showUserSummaryWidget();    //切换服务器页面的槽函数
    void showGroupSummaryWidget();
    void showServerInfoWidget();
private:
    Ui::Widget *ui;
    QStackedWidget *stackWidget;

    QLabel *serverIconLabel;
    QLabel *welcomeToServerLabel;
    QPushButton *Btn_User;          //用户标签按钮
    QPushButton *Btn_UserGroup;     //用户群组标签按钮
    QPushButton *Btn_ServerInfo;    //服务器基本信息
    QListWidget *list;

    QWidget *userUiWidget;
    UserUI *userUi;

    QWidget *groupUiWidget=new QWidget;
    UserGroup *groupUi;

    QWidget *serverGenerInfoWidget=new QWidget;
    ServerGenerInfoUI *ServerInfoUi;

    QVBoxLayout *mainLayout;

};

#endif // WIDGET_H
