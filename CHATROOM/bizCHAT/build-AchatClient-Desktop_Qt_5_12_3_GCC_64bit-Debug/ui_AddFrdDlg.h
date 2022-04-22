/********************************************************************************
** Form generated from reading UI file 'AddFrdDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRDDLG_H
#define UI_ADDFRDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddFrdDlg
{
public:
    QLabel *label;
    QPushButton *ConfirmBtn;
    QPushButton *CancelBtn;
    QLineEdit *IdLineEdit;

    void setupUi(QDialog *AddFrdDlg)
    {
        if (AddFrdDlg->objectName().isEmpty())
            AddFrdDlg->setObjectName(QString::fromUtf8("AddFrdDlg"));
        AddFrdDlg->resize(274, 136);
        label = new QLabel(AddFrdDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 67, 17));
        ConfirmBtn = new QPushButton(AddFrdDlg);
        ConfirmBtn->setObjectName(QString::fromUtf8("ConfirmBtn"));
        ConfirmBtn->setGeometry(QRect(30, 80, 89, 25));
        CancelBtn = new QPushButton(AddFrdDlg);
        CancelBtn->setObjectName(QString::fromUtf8("CancelBtn"));
        CancelBtn->setGeometry(QRect(140, 80, 89, 25));
        IdLineEdit = new QLineEdit(AddFrdDlg);
        IdLineEdit->setObjectName(QString::fromUtf8("IdLineEdit"));
        IdLineEdit->setGeometry(QRect(70, 20, 141, 31));

        retranslateUi(AddFrdDlg);

        QMetaObject::connectSlotsByName(AddFrdDlg);
    } // setupUi

    void retranslateUi(QDialog *AddFrdDlg)
    {
        AddFrdDlg->setWindowTitle(QApplication::translate("AddFrdDlg", "Dialog", nullptr));
        label->setText(QApplication::translate("AddFrdDlg", "ID:", nullptr));
        ConfirmBtn->setText(QApplication::translate("AddFrdDlg", "\347\241\256\350\256\244", nullptr));
        CancelBtn->setText(QApplication::translate("AddFrdDlg", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddFrdDlg: public Ui_AddFrdDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRDDLG_H
