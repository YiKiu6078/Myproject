#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QHostInfo>
#include <QMessageBox>

TcpClient::TcpClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    setWindowTitle(tr("TCP Client"));

    serverIP = new QHostAddress();

    QObject::connect(ui->enterBtn,SIGNAL(clicked()),this,SLOT(slotEnter()));
    connect(ui->sendButton,SIGNAL(clicked()),this,SLOT(slotSend()));

    ui->sendButton->setEnabled(false);
    this->status=false;
}

TcpClient::~TcpClient()
{
    delete ui;
}


void TcpClient::slotEnter()
{
    if(!status)
    {
        QString ip = ui->serverIPLineEdit->text();
        if(!serverIP->setAddress(ip))
        {
            QMessageBox::information(this,tr("error"),tr("server ip address error!"));
            return;
        }

        if(ui->userNameLineEdit->text()==" ")
        {
            QMessageBox::information(this,tr("error"),tr("User name error!"));
            return;
        }

        userName = ui->userNameLineEdit->text();

        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket,SIGNAL(connected()),this,SLOT(slotConnected()));
        connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
        connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotError(QAbstractSocket::SocketError)));
        connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
        port=ui->portLineEdit->text().toInt();
        tcpSocket->connectToHost(*serverIP,port);
        status=true;
    }
    else
    {
        int length = 0;
        QString msg = userName+tr(":leave chat Room");
        if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg.length())
        {
            return;
        }
        tcpSocket->disconnectFromHost();

        status=false;
    }
}

void TcpClient::slotConnected()
{
    ui->sendButton->setEnabled(true);
    ui->enterBtn->setText(tr("leave"));
    int length = 0;
    QString msg = userName + tr(":Enter Chat room");
    if((length=tcpSocket->write(msg.toLatin1(),msg.length()))!=msg.length())
    {
        return;
    }
}
void TcpClient::slotError(QAbstractSocket::SocketError)
{
    QMessageBox::information(this,tr("Error"),tr("Error"));
}
void TcpClient::slotSend()
{
    if(ui->sendLineEdit->text()==" ")
    {
        return;
    }

    QString msg = userName+":"+ui->sendLineEdit->text();

    tcpSocket->write(msg.toLatin1(),msg.length());
    ui->sendLineEdit->clear();
}

void TcpClient::dataReceived()
{
    while(tcpSocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        datagram.resize(tcpSocket->bytesAvailable());

        QHostAddress sender;
        tcpSocket->read(datagram.data(),datagram.size());

        QString msg = datagram.data();
        ui->contentListWidget->addItem(msg.left(datagram.size()));
    }
}

void TcpClient::slotDisconnected()
{
    QMessageBox::information(this,tr("Disconnected!"),tr("Disconnected!"));
    ui->sendButton->setEnabled(false);
    ui->enterBtn->setText(tr("Enter"));
}
