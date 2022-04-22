/********************************************************************************
** Form generated from reading UI file 'usergroup.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERGROUP_H
#define UI_USERGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserGroup
{
public:

    void setupUi(QWidget *UserGroup)
    {
        if (UserGroup->objectName().isEmpty())
            UserGroup->setObjectName(QString::fromUtf8("UserGroup"));
        UserGroup->resize(400, 300);

        retranslateUi(UserGroup);

        QMetaObject::connectSlotsByName(UserGroup);
    } // setupUi

    void retranslateUi(QWidget *UserGroup)
    {
        UserGroup->setWindowTitle(QApplication::translate("UserGroup", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserGroup: public Ui_UserGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERGROUP_H
