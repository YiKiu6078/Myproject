#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QMainWindow>
#include<QHostInfo>
#include"Server.h"
namespace Ui {
class tcpserver;
}

class tcpserver : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit tcpserver(QWidget *parent = 0);
    ~tcpserver();
    
private:
    Ui::tcpserver *ui;
    int port;
    Server *server;
protected slots:
    void slotCreateServer();
    void updateServer(QString,int);
};

#endif // TCPSERVER_H
