#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>

namespace Ui {
class TcpClient;
}

class TcpClient : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TcpClient(QWidget *parent = 0);
    ~TcpClient();
    
private:
    Ui::TcpClient *ui;

    bool status;
    int port;
    QHostAddress *serverIP;
    QString userName;
    QTcpSocket *tcpSocket;

public slots:
    void slotEnter();
    void slotConnected();
    void slotDisconnected();
    void slotError(QAbstractSocket::SocketError);
    void dataReceived();
    void slotSend();
};

#endif // TCPCLIENT_H
