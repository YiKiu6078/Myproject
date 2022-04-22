/********************************************************************************
** Form generated from reading UI file 'FriendList.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDLIST_H
#define UI_FRIENDLIST_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FriendList
{
public:
    QLineEdit *searchLineEdit;
    QPushButton *contactsBtn;
    QLabel *signatureLabel;
    QLabel *nickNameLabel;
    QLabel *headImgLabel;
    QStackedWidget *stackWidget;
    QWidget *ContactPage;
    QWidget *ChatPage;
    QWidget *GroupPage;
    QPushButton *chatBtn;
    QPushButton *groupBtn;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *optionBtn;
    QToolButton *minBtn;
    QToolButton *closeBtn;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *ImgThemeBtn;
    QPushButton *addGroupBtn;
    QPushButton *addFrdBtn;
    QPushButton *colorThemeBtn;
    QLabel *Titlelabel;
    QLabel *cloudLabel;

    void setupUi(QDialog *FriendList)
    {
        if (FriendList->objectName().isEmpty())
            FriendList->setObjectName(QString::fromUtf8("FriendList"));
        FriendList->resize(300, 650);
        FriendList->setMinimumSize(QSize(300, 650));
        FriendList->setMaximumSize(QSize(300, 650));
        searchLineEdit = new QLineEdit(FriendList);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(0, 120, 301, 31));
        contactsBtn = new QPushButton(FriendList);
        contactsBtn->setObjectName(QString::fromUtf8("contactsBtn"));
        contactsBtn->setGeometry(QRect(100, 150, 101, 25));
        signatureLabel = new QLabel(FriendList);
        signatureLabel->setObjectName(QString::fromUtf8("signatureLabel"));
        signatureLabel->setGeometry(QRect(90, 80, 181, 20));
        QFont font;
        font.setPointSize(9);
        signatureLabel->setFont(font);
        nickNameLabel = new QLabel(FriendList);
        nickNameLabel->setObjectName(QString::fromUtf8("nickNameLabel"));
        nickNameLabel->setGeometry(QRect(90, 30, 171, 41));
        QFont font1;
        font1.setPointSize(14);
        nickNameLabel->setFont(font1);
        headImgLabel = new QLabel(FriendList);
        headImgLabel->setObjectName(QString::fromUtf8("headImgLabel"));
        headImgLabel->setGeometry(QRect(20, 40, 60, 60));
        headImgLabel->setMinimumSize(QSize(60, 60));
        headImgLabel->setMaximumSize(QSize(60, 60));
        stackWidget = new QStackedWidget(FriendList);
        stackWidget->setObjectName(QString::fromUtf8("stackWidget"));
        stackWidget->setGeometry(QRect(0, 180, 301, 441));
        ContactPage = new QWidget();
        ContactPage->setObjectName(QString::fromUtf8("ContactPage"));
        stackWidget->addWidget(ContactPage);
        ChatPage = new QWidget();
        ChatPage->setObjectName(QString::fromUtf8("ChatPage"));
        stackWidget->addWidget(ChatPage);
        GroupPage = new QWidget();
        GroupPage->setObjectName(QString::fromUtf8("GroupPage"));
        stackWidget->addWidget(GroupPage);
        chatBtn = new QPushButton(FriendList);
        chatBtn->setObjectName(QString::fromUtf8("chatBtn"));
        chatBtn->setGeometry(QRect(0, 150, 101, 25));
        groupBtn = new QPushButton(FriendList);
        groupBtn->setObjectName(QString::fromUtf8("groupBtn"));
        groupBtn->setGeometry(QRect(200, 150, 101, 25));
        horizontalLayoutWidget = new QWidget(FriendList);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(210, 0, 91, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        optionBtn = new QToolButton(horizontalLayoutWidget);
        optionBtn->setObjectName(QString::fromUtf8("optionBtn"));
        optionBtn->setFont(font1);
        optionBtn->setStyleSheet(QString::fromUtf8("/* \350\256\276\347\275\256\346\214\211\351\222\256\347\232\204\345\261\236\346\200\247 */\n"
"QPushButton[objectName=\"menuPushButton\"] {\n"
"border:0px; /*\345\217\226\346\266\210\346\214\211\351\222\256\350\276\271\347\225\214\357\274\214\344\275\277\346\214\211\351\222\256\351\200\217\346\230\216*/\n"
"color:white;\n"
"}\n"
"QPushButton[objectName=\"menuPushButton\"]:hover {\n"
"image:url(:/image/menu_hover.png);/*\351\274\240\346\240\207\346\224\276\344\270\212\345\216\273\346\230\257\346\230\276\347\244\272\347\232\204\346\225\210\346\236\234*/\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../\346\226\207\346\241\243/QT download/QQ_Manager-master/image/right_on_menu.png"), QSize(), QIcon::Normal, QIcon::Off);
        optionBtn->setIcon(icon);

        horizontalLayout->addWidget(optionBtn);

        minBtn = new QToolButton(horizontalLayoutWidget);
        minBtn->setObjectName(QString::fromUtf8("minBtn"));
        minBtn->setStyleSheet(QString::fromUtf8("/* \350\256\276\347\275\256\346\214\211\351\222\256\347\232\204\345\261\236\346\200\247 */\n"
"\n"
"QToolButton[objectName=\"miniButton\"] {\n"
"border:0px; /*\345\217\226\346\266\210\346\214\211\351\222\256\350\276\271\347\225\214\357\274\214\344\275\277\346\214\211\351\222\256\351\200\217\346\230\216*/\n"
"color:white;\n"
"}\n"
"QToolButton[objectName=\"miniButton\"]:hover {\n"
"image:url(:/image/menu_hover.png);/*\351\274\240\346\240\207\346\224\276\344\270\212\345\216\273\346\230\257\346\230\276\347\244\272\347\232\204\346\225\210\346\236\234*/\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Img/picture/minWindow.png"), QSize(), QIcon::Normal, QIcon::Off);
        minBtn->setIcon(icon1);

        horizontalLayout->addWidget(minBtn);

        closeBtn = new QToolButton(horizontalLayoutWidget);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));
        closeBtn->setStyleSheet(QString::fromUtf8("/* \350\256\276\347\275\256\346\214\211\351\222\256\347\232\204\345\261\236\346\200\247 */\n"
"\n"
"QToolButton[objectName=\"exitButton\"] {\n"
"border:0px; /*\345\217\226\346\266\210\346\214\211\351\222\256\350\276\271\347\225\214\357\274\214\344\275\277\346\214\211\351\222\256\351\200\217\346\230\216*/\n"
"color:white;\n"
"}\n"
"QToolButton[objectName=\"exitButton\"]:hover {\n"
"image:url(:/image/menu_hover.png);/*\351\274\240\346\240\207\346\224\276\344\270\212\345\216\273\346\230\257\346\230\276\347\244\272\347\232\204\346\225\210\346\236\234*/\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../\346\226\207\346\241\243/QT download/QQ_Manager-master/image/right_on_exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        closeBtn->setIcon(icon2);

        horizontalLayout->addWidget(closeBtn);

        horizontalLayoutWidget_3 = new QWidget(FriendList);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(0, 620, 141, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        ImgThemeBtn = new QPushButton(horizontalLayoutWidget_3);
        ImgThemeBtn->setObjectName(QString::fromUtf8("ImgThemeBtn"));

        horizontalLayout_3->addWidget(ImgThemeBtn);

        addGroupBtn = new QPushButton(horizontalLayoutWidget_3);
        addGroupBtn->setObjectName(QString::fromUtf8("addGroupBtn"));

        horizontalLayout_3->addWidget(addGroupBtn);

        addFrdBtn = new QPushButton(horizontalLayoutWidget_3);
        addFrdBtn->setObjectName(QString::fromUtf8("addFrdBtn"));

        horizontalLayout_3->addWidget(addFrdBtn);

        colorThemeBtn = new QPushButton(horizontalLayoutWidget_3);
        colorThemeBtn->setObjectName(QString::fromUtf8("colorThemeBtn"));

        horizontalLayout_3->addWidget(colorThemeBtn);

        Titlelabel = new QLabel(FriendList);
        Titlelabel->setObjectName(QString::fromUtf8("Titlelabel"));
        Titlelabel->setGeometry(QRect(20, 10, 41, 17));
        cloudLabel = new QLabel(FriendList);
        cloudLabel->setObjectName(QString::fromUtf8("cloudLabel"));
        cloudLabel->setGeometry(QRect(220, 36, 61, 60));
        cloudLabel->setStyleSheet(QString::fromUtf8("border:0px; /*\345\217\226\346\266\210\346\214\211\351\222\256\350\276\271\347\225\214\357\274\214\344\275\277\346\214\211\351\222\256\351\200\217\346\230\216*/\n"
"color:white;"));
        cloudLabel->setPixmap(QPixmap(QString::fromUtf8(":/Img/picture/cloud.jpg")));
        cloudLabel->setScaledContents(true);

        retranslateUi(FriendList);

        stackWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(FriendList);
    } // setupUi

    void retranslateUi(QDialog *FriendList)
    {
        FriendList->setWindowTitle(QApplication::translate("FriendList", "Dialog", nullptr));
        contactsBtn->setText(QApplication::translate("FriendList", "\350\201\224\347\263\273\344\272\272", nullptr));
        signatureLabel->setText(QApplication::translate("FriendList", "TextLabel", nullptr));
        nickNameLabel->setText(QApplication::translate("FriendList", "TextLabel", nullptr));
        headImgLabel->setText(QApplication::translate("FriendList", "TextLabel", nullptr));
        chatBtn->setText(QApplication::translate("FriendList", "\344\274\232\350\257\235", nullptr));
        groupBtn->setText(QApplication::translate("FriendList", "\347\276\244\347\273\204", nullptr));
#ifndef QT_NO_TOOLTIP
        optionBtn->setToolTip(QApplication::translate("FriendList", "\351\200\211\351\241\271", nullptr));
#endif // QT_NO_TOOLTIP
        optionBtn->setText(QApplication::translate("FriendList", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        minBtn->setToolTip(QApplication::translate("FriendList", "\346\234\200\345\260\217\345\214\226", nullptr));
#endif // QT_NO_TOOLTIP
        minBtn->setText(QApplication::translate("FriendList", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        closeBtn->setToolTip(QApplication::translate("FriendList", "\345\205\263\351\227\255", nullptr));
#endif // QT_NO_TOOLTIP
        closeBtn->setText(QApplication::translate("FriendList", "...", nullptr));
#ifndef QT_NO_TOOLTIP
        ImgThemeBtn->setToolTip(QApplication::translate("FriendList", "\345\233\276\347\211\207\344\270\273\351\242\230", nullptr));
#endif // QT_NO_TOOLTIP
        ImgThemeBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        addGroupBtn->setToolTip(QApplication::translate("FriendList", "\346\267\273\345\212\240\347\276\244\350\201\212", nullptr));
#endif // QT_NO_TOOLTIP
        addGroupBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        addFrdBtn->setToolTip(QApplication::translate("FriendList", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
#endif // QT_NO_TOOLTIP
        addFrdBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        colorThemeBtn->setToolTip(QApplication::translate("FriendList", "\351\242\234\350\211\262\344\270\273\351\242\230", nullptr));
#endif // QT_NO_TOOLTIP
        colorThemeBtn->setText(QString());
        Titlelabel->setText(QApplication::translate("FriendList", "AChat", nullptr));
        cloudLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FriendList: public Ui_FriendList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDLIST_H
