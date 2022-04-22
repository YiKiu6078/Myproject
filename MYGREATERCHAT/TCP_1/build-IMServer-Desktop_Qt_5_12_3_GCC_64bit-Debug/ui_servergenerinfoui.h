/********************************************************************************
** Form generated from reading UI file 'servergenerinfoui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERGENERINFOUI_H
#define UI_SERVERGENERINFOUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerGenerInfoUI
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;

    void setupUi(QWidget *ServerGenerInfoUI)
    {
        if (ServerGenerInfoUI->objectName().isEmpty())
            ServerGenerInfoUI->setObjectName(QString::fromUtf8("ServerGenerInfoUI"));
        ServerGenerInfoUI->resize(400, 389);
        label = new QLabel(ServerGenerInfoUI);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 111, 17));
        label_2 = new QLabel(ServerGenerInfoUI);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(180, 40, 131, 17));
        label_3 = new QLabel(ServerGenerInfoUI);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 140, 121, 17));
        label_4 = new QLabel(ServerGenerInfoUI);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(180, 140, 191, 17));
        label_5 = new QLabel(ServerGenerInfoUI);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 190, 67, 17));
        label_6 = new QLabel(ServerGenerInfoUI);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(180, 190, 191, 17));
        label_7 = new QLabel(ServerGenerInfoUI);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(40, 90, 101, 17));
        label_8 = new QLabel(ServerGenerInfoUI);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(180, 90, 151, 17));
        label_9 = new QLabel(ServerGenerInfoUI);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(40, 240, 111, 17));
        label_10 = new QLabel(ServerGenerInfoUI);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(180, 240, 67, 17));
        label_11 = new QLabel(ServerGenerInfoUI);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(40, 290, 67, 17));
        label_12 = new QLabel(ServerGenerInfoUI);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(180, 290, 171, 17));

        retranslateUi(ServerGenerInfoUI);

        QMetaObject::connectSlotsByName(ServerGenerInfoUI);
    } // setupUi

    void retranslateUi(QWidget *ServerGenerInfoUI)
    {
        ServerGenerInfoUI->setWindowTitle(QApplication::translate("ServerGenerInfoUI", "Form", nullptr));
        label->setText(QApplication::translate("ServerGenerInfoUI", "\346\234\215\345\212\241\345\231\250\345\220\215\347\247\260:", nullptr));
        label_2->setText(QApplication::translate("ServerGenerInfoUI", "NUISTChatServer", nullptr));
        label_3->setText(QApplication::translate("ServerGenerInfoUI", "\346\234\215\345\212\241\345\231\250\345\210\233\345\273\272\346\227\266\351\227\264:", nullptr));
        label_4->setText(QApplication::translate("ServerGenerInfoUI", "2022-04-26T14:53:00", nullptr));
        label_5->setText(QApplication::translate("ServerGenerInfoUI", "\346\234\215\345\212\241\345\231\250ip:", nullptr));
        label_6->setText(QApplication::translate("ServerGenerInfoUI", "192.168.2.114", nullptr));
        label_7->setText(QApplication::translate("ServerGenerInfoUI", "\346\234\215\345\212\241\345\231\250\347\211\210\346\234\254:", nullptr));
        label_8->setText(QApplication::translate("ServerGenerInfoUI", "NUISTChatServer1.0", nullptr));
        label_9->setText(QApplication::translate("ServerGenerInfoUI", "\346\234\215\345\212\241\345\231\250\346\213\245\346\234\211\344\272\272:", nullptr));
        label_10->setText(QApplication::translate("ServerGenerInfoUI", "\345\210\230\351\242\220\346\247\220", nullptr));
        label_11->setText(QApplication::translate("ServerGenerInfoUI", "\350\201\224\347\263\273\346\226\271\345\274\217:", nullptr));
        label_12->setText(QApplication::translate("ServerGenerInfoUI", "1907783893@qq.com", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerGenerInfoUI: public Ui_ServerGenerInfoUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERGENERINFOUI_H
