/********************************************************************************
** Form generated from reading ui file 'chat_drawer.ui'
**
** Created: Tue Jun 22 20:34:53 2010
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CHAT_DRAWER_H
#define UI_CHAT_DRAWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chat_DrawerClass
{
public:

    void setupUi(QWidget *Chat_DrawerClass)
    {
        if (Chat_DrawerClass->objectName().isEmpty())
            Chat_DrawerClass->setObjectName(QString::fromUtf8("Chat_DrawerClass"));
        Chat_DrawerClass->resize(400, 300);

        retranslateUi(Chat_DrawerClass);

        QMetaObject::connectSlotsByName(Chat_DrawerClass);
    } // setupUi

    void retranslateUi(QWidget *Chat_DrawerClass)
    {
        Chat_DrawerClass->setWindowTitle(QApplication::translate("Chat_DrawerClass", "Chat_Drawer", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Chat_DrawerClass);
    } // retranslateUi

};

namespace Ui {
    class Chat_DrawerClass: public Ui_Chat_DrawerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_DRAWER_H
