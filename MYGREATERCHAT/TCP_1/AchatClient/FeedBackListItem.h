#ifndef FEEDBACKLISTITEM_H
#define FEEDBACKLISTITEM_H


#define     COLOR_WHITE         Qt::white
#define     ITEM_HEIGHT         40
#define     ITEM_SPACE          5
#define     HeaderBgColor       QColor(219, 238, 252)
#define     HeaderTextColor     QColor(55, 100, 151)
#define     COLOR_BLACK         Qt::black
#define     HEAD_W_H            40
#define     TEACHER_HEAD        QString::fromLocal8Bit("联系人")
#define     DAFENQI_HEAD        QString::fromLocal8Bit("自己")

enum Orientation{
    None,
    Left,
    Right
};

#include <QWidget>
#include <QPainter>
#include <QEvent>
#include <QDateTime>
#include <QtDebug>
#include <QIcon>
class FeedBackListItem : public QWidget
{
    Q_OBJECT

public:
    FeedBackListItem(QWidget *parent,QString text,int Ori);
    ~FeedBackListItem();

    QImage rightImage;
    QImage leftImage;

private:
    QString     m_text;
    int         m_width;
    int         m_oritation;
    QWidget     *m_parent;
    QSize       getItemSize(int ,int );
    void        drawBg(QPainter *painter);
    void        drawItems(QPainter *painter);
signals:
    void sendItemSize(int,int);
protected:
    bool eventFilter(QObject *, QEvent *);

};


#endif // FEEDBACKLISTITEM_H
