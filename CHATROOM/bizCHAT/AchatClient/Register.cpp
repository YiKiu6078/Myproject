#include "Register.h"
#include "ui_register.h"

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    setWindowTitle("注册用户");
    this->setMaximumSize(300,400);
    setStyleSheet("QDialog#Register{border-image:url(:/Img/picture/back.jpg)}");

    RegisterTcpsocket=new QTcpSocket;

    //将上次创建的用户数据清空
    IdLineEdit->clear();
    passwordLineEdit->clear();
    paswdAgainLineEdit->clear();
    nickNameLineEdit->clear();
    signatureLineEdit->clear();
    ageLineEdit->clear();
    emailLineEdit->clear();

    //限制用户ID只能为数字，限制用户密码不大于8位
    QRegExp regx("[0-9]+$");
    QValidator *validator=new QRegExpValidator(regx,IdLineEdit);
    IdLineEdit->setValidator(validator);
    IdLineEdit->setMaxLength(8);
    passwordLineEdit->setMaxLength(8);
    paswdAgainLineEdit->setMaxLength(8);
    passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);          //隐藏密码
    paswdAgainLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    nickNameLineEdit->setMaxLength(10);
    signatureLineEdit->setMaxLength(30);
    emailLineEdit->setMaxLength(20);
    headImgPathLineEdit->setFocusPolicy(Qt::NoFocus);
    sexComBox->addItem("男");
    sexComBox->addItem("女");

    connect(confirmBtn,&QPushButton::clicked,this,&Register::showConfirmCreateUserBtn);
    connect(cancelBtn,&QPushButton::clicked,this,&Register::showCancelCreateUserBtn);
    connect(headImgBtn,&QPushButton::clicked,this,&Register::showOpenImgFileBtn);

    //将输入信息的标签和lineedit放入一个布局中
    QGridLayout *registerLayout=new QGridLayout;
    registerLayout->addWidget(IdLabel,1,0);
    registerLayout->addWidget(IdLineEdit,1,1);
    registerLayout->addWidget(passwordLabel,2,0);
    registerLayout->addWidget(passwordLineEdit,2,1);
    registerLayout->addWidget(paswdAgainLabel,3,0);
    registerLayout->addWidget(paswdAgainLineEdit,3,1);
    registerLayout->addWidget(nickNameLabel,4,0);
    registerLayout->addWidget(nickNameLineEdit,4,1);
    registerLayout->addWidget(signatureLabel,5,0);
    registerLayout->addWidget(signatureLineEdit,5,1);
    registerLayout->addWidget(ageLabel,6,0);
    registerLayout->addWidget(ageLineEdit,6,1);
    registerLayout->addWidget(sexLabel,7,0);
    registerLayout->addWidget(sexComBox,7,1);
    registerLayout->addWidget(emailLabel,8,0);
    registerLayout->addWidget(emailLineEdit,8,1);
    registerLayout->addWidget(headImgBtn,9,0);
    registerLayout->addWidget(headImgPathLineEdit,9,1);

    //将确认和取消按钮加入另一个布局中
    QHBoxLayout *btnLayout=new QHBoxLayout;
    btnLayout->addWidget(confirmBtn);
    btnLayout->addWidget(cancelBtn);

    //将不同的布局放入整体布局
    QVBoxLayout *completeLayout=new QVBoxLayout(this);
    completeLayout->addLayout(registerLayout);
    completeLayout->addLayout(btnLayout);

}

/*
 * 选择头像按钮槽函数
 */
void Register::showOpenImgFileBtn()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",
                                                  tr("Images (*.png *.bmp *.jpg)"));
    if(filename.isEmpty())
        return;
    else
    {
        QImage img;
        if(!(img.load(filename))) //加载图像
        {
            QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
            return;
        }
        headImgPathLineEdit->setText(filename);
    }
}

/*
 * 取消注册用户槽函数
 */
void Register::showCancelCreateUserBtn()
{
    this->close();
}

/*
 * 确认注册用户槽函数
 */
void Register::showConfirmCreateUserBtn()
{
    if(IdLineEdit->text().length()!=8){
        QMessageBox::information(nullptr, "警告", "用户ID的长度必须为8位！",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if(passwordLineEdit->text().length()==0 || passwordLineEdit->text()!=paswdAgainLineEdit->text()){
        QMessageBox::information(nullptr, "警告", "两次密码不一致且密码不能为空！",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if(nickNameLineEdit->text().length()==0){
        QMessageBox::information(nullptr, "警告", "昵称不能为空！",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    tcpConnectedToServer();
}

/*
 * 连接服务器
 */
void Register::tcpConnectedToServer()
{
    QByteArray registerData;
    QDataStream out(&registerData,QIODevice::WriteOnly);
    RegisterTcpsocket->connectToHost(QHostAddress::LocalHost,ALLCHAT_PORT);
    if(!RegisterTcpsocket->waitForConnected(30000)){
        QMessageBox::information(this,"提示","无法连接到服务器");
        return;
    }
    //向服务器发送登录消息
    QBuffer buffer;
    QPixmap(headImgPathLineEdit->text()).save(&buffer,"JPG");
    out<<RegisterUser<<IdLineEdit->text()<<passwordLineEdit->text()<<nickNameLineEdit->text()<<signatureLineEdit->text()<<
         ageLineEdit->text()<<sexComBox->currentText()<<emailLineEdit->text()<<buffer.data();
    sendMessgae(registerData);
    out.device()->seek(0);
    connect(RegisterTcpsocket,SIGNAL(disconnected()),this,SLOT(tcpDisConnected()));
    connect(RegisterTcpsocket,SIGNAL(readyRead()),this,SLOT(tcpReadyRead()));
}

/*
 * 发送消息
 */
void Register::sendMessgae(QByteArray data)
{
    if(RegisterTcpsocket->write(data)<0){
        qDebug()<<"Send register message failed,Please try again"<<endl;
    }
    RegisterTcpsocket->flush();
}

/*
 * 断开连接
 */
void Register::tcpDisConnected()
{

}

/*
 * 读取消息
 */
void Register::tcpReadyRead()
{
    QDataStream in(RegisterTcpsocket);
    in.setVersion(QDataStream::Qt_5_9);
    int msgType;
    in>>msgType;
    switch (msgType) {
    case Invalid:
    {
        QString info;
        in>>info;
        QMessageBox::information(this,"提示",info);
        this->close();
        break;
    }
    case AgreeRegister:
    {
        QString info;
        in>>info;
        QMessageBox::information(this,"提示",info);
        this->close();
        break;
    }
    default:
        break;
    }
}
Register::~Register()
{
    delete ui;
}
