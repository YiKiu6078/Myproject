/********************************************************************************
** Form generated from reading UI file 'formfind.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMFIND_H
#define UI_FORMFIND_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormFind
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButtonFind;
    QListWidget *listWidget;

    void setupUi(QWidget *FormFind)
    {
        if (FormFind->objectName().isEmpty())
            FormFind->setObjectName(QString::fromUtf8("FormFind"));
        FormFind->resize(600, 450);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        FormFind->setWindowIcon(icon);
        verticalLayout_2 = new QVBoxLayout(FormFind);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(FormFind);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        pushButtonFind = new QPushButton(FormFind);
        pushButtonFind->setObjectName(QString::fromUtf8("pushButtonFind"));
        pushButtonFind->setFocusPolicy(Qt::NoFocus);
        pushButtonFind->setStyleSheet(QString::fromUtf8("color:white;background-color:rgb(0,155,219)"));

        horizontalLayout->addWidget(pushButtonFind);


        verticalLayout->addLayout(horizontalLayout);

        listWidget = new QListWidget(FormFind);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        listWidget->setIconSize(QSize(60, 60));
        listWidget->setMovement(QListView::Static);
        listWidget->setSpacing(5);
        listWidget->setViewMode(QListView::IconMode);

        verticalLayout->addWidget(listWidget);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(FormFind);

        QMetaObject::connectSlotsByName(FormFind);
    } // setupUi

    void retranslateUi(QWidget *FormFind)
    {
        FormFind->setWindowTitle(QApplication::translate("FormFind", "\346\237\245\346\211\276", nullptr));
        lineEdit->setPlaceholderText(QApplication::translate("FormFind", "\350\264\246\345\217\267/\346\230\265\347\247\260/\346\211\213\346\234\272\345\217\267\347\240\201/\351\202\256\347\256\261", nullptr));
        pushButtonFind->setText(QApplication::translate("FormFind", "\346\237\245\346\211\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormFind: public Ui_FormFind {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMFIND_H
