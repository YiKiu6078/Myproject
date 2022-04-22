/********************************************************************************
** Form generated from reading UI file 'formchat.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMCHAT_H
#define UI_FORMCHAT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormChat
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonSend;
    QPushButton *pushButtonAvartar;
    QPushButton *pushButtonName;
    QTextBrowser *textBrowser;
    QSpacerItem *horizontalSpacer;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButtonHomepage;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonImg;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonHistory;

    void setupUi(QWidget *FormChat)
    {
        if (FormChat->objectName().isEmpty())
            FormChat->setObjectName(QString::fromUtf8("FormChat"));
        FormChat->resize(600, 546);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        FormChat->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(FormChat);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(5);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonClose = new QPushButton(FormChat);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonClose->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pushButtonClose);

        pushButtonSend = new QPushButton(FormChat);
        pushButtonSend->setObjectName(QString::fromUtf8("pushButtonSend"));
        pushButtonSend->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonSend->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(pushButtonSend);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 4);

        pushButtonAvartar = new QPushButton(FormChat);
        pushButtonAvartar->setObjectName(QString::fromUtf8("pushButtonAvartar"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonAvartar->sizePolicy().hasHeightForWidth());
        pushButtonAvartar->setSizePolicy(sizePolicy);
        pushButtonAvartar->setMinimumSize(QSize(50, 50));
        pushButtonAvartar->setMaximumSize(QSize(50, 50));
        pushButtonAvartar->setSizeIncrement(QSize(0, 0));
        pushButtonAvartar->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonAvartar->setFocusPolicy(Qt::NoFocus);
        pushButtonAvartar->setIcon(icon);
        pushButtonAvartar->setIconSize(QSize(50, 50));
        pushButtonAvartar->setFlat(true);

        gridLayout->addWidget(pushButtonAvartar, 0, 0, 1, 1);

        pushButtonName = new QPushButton(FormChat);
        pushButtonName->setObjectName(QString::fromUtf8("pushButtonName"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonName->sizePolicy().hasHeightForWidth());
        pushButtonName->setSizePolicy(sizePolicy1);
        pushButtonName->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonName->setFocusPolicy(Qt::NoFocus);
        pushButtonName->setIconSize(QSize(0, 0));
        pushButtonName->setFlat(true);

        gridLayout->addWidget(pushButtonName, 0, 1, 1, 1);

        textBrowser = new QTextBrowser(FormChat);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setMinimumSize(QSize(0, 300));

        gridLayout->addWidget(textBrowser, 1, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        plainTextEdit = new QPlainTextEdit(FormChat);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setMinimumSize(QSize(0, 100));
        plainTextEdit->setMaximumSize(QSize(16777215, 150));

        gridLayout->addWidget(plainTextEdit, 4, 0, 1, 4);

        pushButtonHomepage = new QPushButton(FormChat);
        pushButtonHomepage->setObjectName(QString::fromUtf8("pushButtonHomepage"));
        pushButtonHomepage->setMinimumSize(QSize(0, 0));
        pushButtonHomepage->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonHomepage->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/qzone.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonHomepage->setIcon(icon1);
        pushButtonHomepage->setFlat(true);

        gridLayout->addWidget(pushButtonHomepage, 0, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonImg = new QPushButton(FormChat);
        pushButtonImg->setObjectName(QString::fromUtf8("pushButtonImg"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButtonImg->sizePolicy().hasHeightForWidth());
        pushButtonImg->setSizePolicy(sizePolicy2);
        pushButtonImg->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonImg->setFocusPolicy(Qt::NoFocus);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/img.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonImg->setIcon(icon2);
        pushButtonImg->setIconSize(QSize(20, 15));
        pushButtonImg->setFlat(true);

        horizontalLayout_2->addWidget(pushButtonImg);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pushButtonHistory = new QPushButton(FormChat);
        pushButtonHistory->setObjectName(QString::fromUtf8("pushButtonHistory"));
        sizePolicy2.setHeightForWidth(pushButtonHistory->sizePolicy().hasHeightForWidth());
        pushButtonHistory->setSizePolicy(sizePolicy2);
        pushButtonHistory->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonHistory->setFocusPolicy(Qt::NoFocus);
        pushButtonHistory->setFlat(true);

        horizontalLayout_2->addWidget(pushButtonHistory);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 4);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(FormChat);

        QMetaObject::connectSlotsByName(FormChat);
    } // setupUi

    void retranslateUi(QWidget *FormChat)
    {
        FormChat->setWindowTitle(QApplication::translate("FormChat", "\350\201\212\345\244\251", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonClose->setToolTip(QApplication::translate("FormChat", "Alt + C", nullptr));
#endif // QT_NO_TOOLTIP
        pushButtonClose->setText(QApplication::translate("FormChat", "\345\205\263\351\227\255", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonSend->setToolTip(QApplication::translate("FormChat", "Ctrl + \345\233\236\350\275\246", nullptr));
#endif // QT_NO_TOOLTIP
        pushButtonSend->setText(QApplication::translate("FormChat", "\345\217\221\351\200\201", nullptr));
        pushButtonAvartar->setText(QString());
        pushButtonName->setText(QApplication::translate("FormChat", "\346\230\265\347\247\260", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonHomepage->setToolTip(QApplication::translate("FormChat", "\346\211\223\345\274\200\344\270\273\351\241\265", nullptr));
#endif // QT_NO_TOOLTIP
        pushButtonHomepage->setText(QString());
        pushButtonImg->setText(QString());
        pushButtonHistory->setText(QApplication::translate("FormChat", "\346\266\210\346\201\257\350\256\260\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormChat: public Ui_FormChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMCHAT_H
