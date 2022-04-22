#include "PersonInfo.h"
#include "ui_PersonInfo.h"

PersonInfo::PersonInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonInfo)
{
    ui->setupUi(this);
    setWindowTitle("个人信息");
}


void PersonInfo::rcvPersonInfo(QString userId,QString nickName, QString signature,QString age,
                   QString sex, QString email)
{
    ui->IdLabel->setText(userId);
    ui->nickNameLabel->setText(nickName);
    ui->signatureLabel->setText(signature);
    ui->ageLabel->setText(age);
    ui->sexLabel->setText(sex);
    ui->emailLabel->setText(email);
}

PersonInfo::~PersonInfo()
{
    delete ui;
}
