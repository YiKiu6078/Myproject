#include "SendFileDlg.h"
#include "ui_SendFileDlg.h"

SendFileDlg::SendFileDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendFileDlg)
{
    ui->setupUi(this);
    ui->progressBar->reset();
    ui->SendFIleBtn->setEnabled(false);
    ui->CanCelBtn->setEnabled(false);
}

//选择文件
void SendFileDlg::on_OpenFileBtn_clicked()
{
    filePath=QFileDialog::getOpenFileName(this);
    if(!filePath.isEmpty()) {
        ui->FileName->setText(filePath);
        ui->SendFIleBtn->setEnabled(true);
        ui->CanCelBtn->setEnabled(true);
    }
}

//发送
void SendFileDlg::on_SendFIleBtn_clicked()
{
    ui->OpenFileBtn->setEnabled(false);
    connect(&timer,&QTimer::timeout,
            [=]()
            {     //发送文件
        sendFileToServer();
    });
    QFileInfo info(filePath);
    fileName = info.fileName();     //获取文件名字
    fileSize = info.size();         //获取文件大小
    sendSize = 0;                   //已经发送文件的大小
    file=new QFile(filePath);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum((int)fileSize/1024);
    ui->progressBar->setValue(0);
    if(!file->open(QFile::ReadOnly)) {
        QMessageBox::warning(this,tr("应用程序"),tr("无法读取文件%1:\n%2").arg(fileName)
                             .arg(file->errorString()));
        return;
    }
    QDataStream out(&sendData,QIODevice::WriteOnly);
    out<<FileHeader<<rcvId<<fileName<<fileSize;
    if(m_tcpSocket->write(sendData) <= 0){
        qDebug()<<"Send FileHeader to receiver falied!"<<endl;
    } else {
        //防止粘包
        timer.start(20);
        sendData.resize(0);
    }
}

void SendFileDlg::sendFileToServer()
{
    QDataStream out(&sendData,QIODevice::WriteOnly);
    QByteArray fileInfo;
    fileInfo = file->read(4096* 5);
    out<<FileInfo<<fileInfo;
    if(m_tcpSocket->write(sendData) < 0) {
        qDebug()<<"Send file info failed!"<<m_tcpSocket->errorString()<<endl;
    }
    m_tcpSocket->flush();
    sendData.resize(0);
    sendSize += fileInfo.size();
    ui->progressBar->setValue((int)sendSize/1024);
    //是否发送文件完毕
    if (sendSize == fileSize)
    {   
        ui->progressBar->setValue((int)fileSize/1024);
    }
}

void SendFileDlg::rcvFileCompeteSlot(int type)
{
    if(type == FileSuccess) {
        file->close();
        timer.stop();       //关闭定时器
        this->close();
    }
}

SendFileDlg::~SendFileDlg()
{
    delete ui;
}

