#include "AddFrdDlg.h"
#include "ui_AddFrdDlg.h"

AddFrdDlg::AddFrdDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFrdDlg)
{
    ui->setupUi(this);
}

AddFrdDlg::~AddFrdDlg()
{
    delete ui;
}

//确认按钮
void AddFrdDlg::on_ConfirmBtn_clicked()
{
    QString AddId=ui->IdLineEdit->text();
    if(AddId.length() != 8 && AddId.length() != 10){
        QMessageBox::information(this,"提示","请输入正确的用户ID或者群聊ID");
        return;
    }
    if(AddId == userId){
        QMessageBox::information(this,"提示","请不要添加自己");
        return;
    }
    if(AddId.length() == 8){
        //将添加好友信息传递到list界面
        emit sendAddUserId(AddId);
    }
    if(AddId.length() == 10){
        emit sendAddGroupId(AddId);
    }
    this->close();
}

//取消按钮
void AddFrdDlg::on_CancelBtn_clicked()
{
    this->close();
}
