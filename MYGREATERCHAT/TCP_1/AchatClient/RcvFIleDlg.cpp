#include "RcvFIleDlg.h"
#include "ui_RcvFIleDlg.h"

RcvFIleDlg::RcvFIleDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RcvFIleDlg)
{
    ui->setupUi(this);
    setWindowTitle("接收文件信息");
}

//接受进度
void RcvFIleDlg::processSlot(qint64 currentPro)
{
    ui->progressBar->setMaximum((int)fileTotalSize/1024);
    ui->progressBar->setValue((int)currentPro/1024);
    if(currentPro == fileTotalSize) {
        QMessageBox::information(this,"提示",tr("文件接收完成,位于 %1 目录下").arg(userId),
                                         QMessageBox::Ok);
        this->close();
    }
}

RcvFIleDlg::~RcvFIleDlg()
{
    delete ui;
}
