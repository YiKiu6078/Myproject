/********************************************************************************
** Form generated from reading UI file 'ChatRoom.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATROOM_H
#define UI_CHATROOM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatRoom
{
public:
    QLabel *chatUserLabel;
    QPushButton *closeBtn;
    QPushButton *sendFileBtn;
    QWidget *RightWidget;
    QPushButton *sendImgBtn;
    QLineEdit *searchLineEdit;
    QListWidget *chatContentList;
    QPushButton *screenShotBtn;
    QListWidget *chatUserList;
    QPushButton *minBtn;
    QTextEdit *chatTextEdit;
    QPushButton *sendMsgBtn;
    QPushButton *cancelBtn;
    QFontComboBox *fontComboBox;
    QComboBox *fontSizeComboBox;

    void setupUi(QDialog *ChatRoom)
    {
        if (ChatRoom->objectName().isEmpty())
            ChatRoom->setObjectName(QString::fromUtf8("ChatRoom"));
        ChatRoom->setEnabled(true);
        ChatRoom->resize(983, 557);
        chatUserLabel = new QLabel(ChatRoom);
        chatUserLabel->setObjectName(QString::fromUtf8("chatUserLabel"));
        chatUserLabel->setGeometry(QRect(440, 10, 211, 17));
        closeBtn = new QPushButton(ChatRoom);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setGeometry(QRect(950, 0, 31, 31));
        QIcon icon;
        icon.addFile(QString::fromUtf8("picture/close.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        closeBtn->setIcon(icon);
        closeBtn->setIconSize(QSize(20, 20));
        sendFileBtn = new QPushButton(ChatRoom);
        sendFileBtn->setObjectName(QString::fromUtf8("sendFileBtn"));
        sendFileBtn->setGeometry(QRect(230, 370, 31, 31));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("picture/file.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        sendFileBtn->setIcon(icon1);
        sendFileBtn->setIconSize(QSize(20, 20));
        RightWidget = new QWidget(ChatRoom);
        RightWidget->setObjectName(QString::fromUtf8("RightWidget"));
        RightWidget->setGeometry(QRect(819, 30, 171, 531));
        sendImgBtn = new QPushButton(ChatRoom);
        sendImgBtn->setObjectName(QString::fromUtf8("sendImgBtn"));
        sendImgBtn->setGeometry(QRect(200, 370, 31, 31));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("picture/Img.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        sendImgBtn->setIcon(icon2);
        sendImgBtn->setIconSize(QSize(20, 20));
        searchLineEdit = new QLineEdit(ChatRoom);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(0, 10, 171, 31));
        chatContentList = new QListWidget(ChatRoom);
        chatContentList->setObjectName(QString::fromUtf8("chatContentList"));
        chatContentList->setGeometry(QRect(170, 30, 651, 341));
        screenShotBtn = new QPushButton(ChatRoom);
        screenShotBtn->setObjectName(QString::fromUtf8("screenShotBtn"));
        screenShotBtn->setGeometry(QRect(170, 370, 31, 31));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("picture/screenShot.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        screenShotBtn->setIcon(icon3);
        screenShotBtn->setIconSize(QSize(25, 25));
        chatUserList = new QListWidget(ChatRoom);
        chatUserList->setObjectName(QString::fromUtf8("chatUserList"));
        chatUserList->setGeometry(QRect(0, 40, 171, 521));
        minBtn = new QPushButton(ChatRoom);
        minBtn->setObjectName(QString::fromUtf8("minBtn"));
        minBtn->setGeometry(QRect(920, 0, 31, 31));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("picture/min.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        minBtn->setIcon(icon4);
        minBtn->setIconSize(QSize(20, 20));
        chatTextEdit = new QTextEdit(ChatRoom);
        chatTextEdit->setObjectName(QString::fromUtf8("chatTextEdit"));
        chatTextEdit->setGeometry(QRect(170, 400, 651, 151));
        chatTextEdit->setFrameShape(QFrame::NoFrame);
        sendMsgBtn = new QPushButton(ChatRoom);
        sendMsgBtn->setObjectName(QString::fromUtf8("sendMsgBtn"));
        sendMsgBtn->setGeometry(QRect(640, 530, 89, 25));
        cancelBtn = new QPushButton(ChatRoom);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(730, 530, 89, 25));
        fontComboBox = new QFontComboBox(ChatRoom);
        fontComboBox->setObjectName(QString::fromUtf8("fontComboBox"));
        fontComboBox->setGeometry(QRect(260, 370, 111, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        fontComboBox->setFont(font);
        fontSizeComboBox = new QComboBox(ChatRoom);
        fontSizeComboBox->addItem(QString());
        fontSizeComboBox->addItem(QString());
        fontSizeComboBox->addItem(QString());
        fontSizeComboBox->addItem(QString());
        fontSizeComboBox->addItem(QString());
        fontSizeComboBox->addItem(QString());
        fontSizeComboBox->addItem(QString());
        fontSizeComboBox->addItem(QString());
        fontSizeComboBox->setObjectName(QString::fromUtf8("fontSizeComboBox"));
        fontSizeComboBox->setEnabled(true);
        fontSizeComboBox->setGeometry(QRect(370, 370, 51, 25));
        QFont font1;
        font1.setPointSize(12);
        fontSizeComboBox->setFont(font1);
        fontSizeComboBox->setEditable(false);
        fontSizeComboBox->setFrame(false);

        retranslateUi(ChatRoom);

        fontSizeComboBox->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(ChatRoom);
    } // setupUi

    void retranslateUi(QDialog *ChatRoom)
    {
        ChatRoom->setWindowTitle(QApplication::translate("ChatRoom", "Dialog", nullptr));
        chatUserLabel->setText(QApplication::translate("ChatRoom", "TextLabel", nullptr));
#ifndef QT_NO_TOOLTIP
        closeBtn->setToolTip(QApplication::translate("ChatRoom", "\345\205\263\351\227\255", nullptr));
#endif // QT_NO_TOOLTIP
        closeBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        sendFileBtn->setToolTip(QApplication::translate("ChatRoom", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
#endif // QT_NO_TOOLTIP
        sendFileBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        sendImgBtn->setToolTip(QApplication::translate("ChatRoom", "\345\217\221\351\200\201\345\233\276\347\211\207", nullptr));
#endif // QT_NO_TOOLTIP
        sendImgBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        screenShotBtn->setToolTip(QApplication::translate("ChatRoom", "\346\210\252\345\233\276(Ctrl+Alt+f)", nullptr));
#endif // QT_NO_TOOLTIP
        screenShotBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        minBtn->setToolTip(QApplication::translate("ChatRoom", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_NO_TOOLTIP
        minBtn->setText(QString());
        sendMsgBtn->setText(QApplication::translate("ChatRoom", "\345\217\221\351\200\201", nullptr));
        cancelBtn->setText(QApplication::translate("ChatRoom", "\345\217\226\346\266\210", nullptr));
#ifndef QT_NO_TOOLTIP
        fontComboBox->setToolTip(QApplication::translate("ChatRoom", "\351\200\211\346\213\251\345\255\227\344\275\223", nullptr));
#endif // QT_NO_TOOLTIP
        fontComboBox->setCurrentText(QApplication::translate("ChatRoom", "Ubuntu", nullptr));
        fontSizeComboBox->setItemText(0, QApplication::translate("ChatRoom", "6", nullptr));
        fontSizeComboBox->setItemText(1, QApplication::translate("ChatRoom", "8", nullptr));
        fontSizeComboBox->setItemText(2, QApplication::translate("ChatRoom", "10", nullptr));
        fontSizeComboBox->setItemText(3, QApplication::translate("ChatRoom", "12", nullptr));
        fontSizeComboBox->setItemText(4, QApplication::translate("ChatRoom", "14", nullptr));
        fontSizeComboBox->setItemText(5, QApplication::translate("ChatRoom", "16", nullptr));
        fontSizeComboBox->setItemText(6, QApplication::translate("ChatRoom", "18", nullptr));
        fontSizeComboBox->setItemText(7, QApplication::translate("ChatRoom", "20", nullptr));

#ifndef QT_NO_TOOLTIP
        fontSizeComboBox->setToolTip(QApplication::translate("ChatRoom", "\345\255\227\344\275\223\345\244\247\345\260\217", nullptr));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class ChatRoom: public Ui_ChatRoom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATROOM_H
