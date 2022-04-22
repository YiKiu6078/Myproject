#ifndef SENDFILEDLG_H
#define SENDFILEDLG_H

#include <QDialog>
#include <QTcpSocket>
#include <QFileDialog>
#include <QtDebug>
#include <QMessageBox>
#include <QDataStream>
#include <QByteArray>
#include <QTimer>
#include "Register.h"

namespace Ui {
class SendFileDlg;
}

class SendFileDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SendFileDlg(QWidget *parent = nullptr);
    ~SendFileDlg();

    QTcpSocket *m_tcpSocket;
    QString rcvId;
private slots:
    void on_OpenFileBtn_clicked();
    void on_SendFIleBtn_clicked();
    void rcvFileCompeteSlot(int);
private:
    Ui::SendFileDlg *ui;
    int flag = 0;
    qint64 bytesWritten=0;
    QFile *file;//文件对象
    QString filePath;           //文件路径
    QString fileName;//文件名字
    qint64 fileSize;//文件大小
    qint64 sendSize;//已经发送文件大小

    QTimer timer;
    QByteArray sendData;
    void sendFileToServer();
};

#endif // SENDFILEDLG_H
