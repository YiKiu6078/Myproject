#ifndef FRIENDGROUPBTN_H
#define FRIENDGROUPBTN_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QtDebug>

namespace Ui {
class FriendGroupBtn;
}

class FriendGroupBtn : public QWidget
{
    Q_OBJECT

public:
    explicit FriendGroupBtn(QWidget *parent = nullptr);

    FriendGroupBtn(QString title);
    void mousePressEvent(QMouseEvent *e);
    ~FriendGroupBtn();
signals:
    void clicked();

private:
    Ui::FriendGroupBtn *ui;
    QHBoxLayout *layout;
    QLabel *head,*groupTitle;
};

#endif // FRIENDGROUPBTN_H
