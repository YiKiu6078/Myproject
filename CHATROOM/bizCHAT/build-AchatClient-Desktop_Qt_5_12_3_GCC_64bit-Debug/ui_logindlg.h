/********************************************************************************
** Form generated from reading UI file 'logindlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDLG_H
#define UI_LOGINDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_loginDlg
{
public:

    void setupUi(QDialog *loginDlg)
    {
        if (loginDlg->objectName().isEmpty())
            loginDlg->setObjectName(QString::fromUtf8("loginDlg"));
        loginDlg->setEnabled(true);
        loginDlg->resize(400, 300);

        retranslateUi(loginDlg);

        QMetaObject::connectSlotsByName(loginDlg);
    } // setupUi

    void retranslateUi(QDialog *loginDlg)
    {
        loginDlg->setWindowTitle(QApplication::translate("loginDlg", "loginDlg", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginDlg: public Ui_loginDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDLG_H
