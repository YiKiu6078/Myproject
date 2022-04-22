/********************************************************************************
** Form generated from reading UI file 'itemfind.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ITEMFIND_H
#define UI_ITEMFIND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ItemFind
{
public:
    QLabel *labelAvantar;
    QLabel *labelName;
    QLabel *labelSex;
    QLabel *labelDomicile;
    QPushButton *pushButtonAdd;
    QLabel *labelAccount;

    void setupUi(QWidget *ItemFind)
    {
        if (ItemFind->objectName().isEmpty())
            ItemFind->setObjectName(QString::fromUtf8("ItemFind"));
        ItemFind->resize(130, 60);
        labelAvantar = new QLabel(ItemFind);
        labelAvantar->setObjectName(QString::fromUtf8("labelAvantar"));
        labelAvantar->setGeometry(QRect(0, 0, 60, 60));
        labelAvantar->setPixmap(QPixmap(QString::fromUtf8(":/icon.png")));
        labelAvantar->setScaledContents(true);
        labelAvantar->setAlignment(Qt::AlignCenter);
        labelName = new QLabel(ItemFind);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setGeometry(QRect(65, 3, 55, 18));
        labelSex = new QLabel(ItemFind);
        labelSex->setObjectName(QString::fromUtf8("labelSex"));
        labelSex->setGeometry(QRect(65, 20, 16, 18));
        labelDomicile = new QLabel(ItemFind);
        labelDomicile->setObjectName(QString::fromUtf8("labelDomicile"));
        labelDomicile->setGeometry(QRect(80, 20, 50, 18));
        pushButtonAdd = new QPushButton(ItemFind);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        pushButtonAdd->setGeometry(QRect(65, 40, 50, 20));
        pushButtonAdd->setStyleSheet(QString::fromUtf8("color:white;background-color:rgb(0,155,219)"));
        labelAccount = new QLabel(ItemFind);
        labelAccount->setObjectName(QString::fromUtf8("labelAccount"));
        labelAccount->setGeometry(QRect(120, 40, 55, 18));

        retranslateUi(ItemFind);

        QMetaObject::connectSlotsByName(ItemFind);
    } // setupUi

    void retranslateUi(QWidget *ItemFind)
    {
        ItemFind->setWindowTitle(QApplication::translate("ItemFind", "Form", nullptr));
        labelAvantar->setText(QString());
        labelName->setText(QApplication::translate("ItemFind", "\346\230\265\347\247\260", nullptr));
        labelSex->setText(QApplication::translate("ItemFind", "\346\200\247", nullptr));
        labelDomicile->setText(QApplication::translate("ItemFind", "\345\261\205\344\275\217\345\234\260", nullptr));
        pushButtonAdd->setText(QApplication::translate("ItemFind", "+\345\245\275\345\217\213", nullptr));
        labelAccount->setText(QApplication::translate("ItemFind", "ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ItemFind: public Ui_ItemFind {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ITEMFIND_H
