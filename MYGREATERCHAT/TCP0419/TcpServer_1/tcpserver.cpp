#include "tcpserver.h"
#include "ui_tcpserver.h"
#include<QNetworkInterface>
tcpserver::tcpserver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tcpserver)
{
    ui->setupUi(this);
    port=12347;
    QString address = QNetworkInterface::allAddresses().first().toString();
    QList<QHostAddress> list2 = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list2)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            ui->ldt_IP->setText(address.toString());
    }
    ui->ldt_Port->setText(QString::number(port));
    connect(ui->btn_Create,SIGNAL(clicked()),this,SLOT(slotCreateServer()));
}

tcpserver::~tcpserver()
{
    delete ui;
}
void tcpserver::slotCreateServer()
{
    server=new Server(this,port);
    connect(server,SIGNAL(updateServer(QString,int)),this,SLOT(updateServer(QString,int)));
    ui->btn_Create->setEnabled(false);
}
void tcpserver::updateServer(QString msg, int length)
{
    ui->lwt_Text->addItem(msg.left(length));
}
