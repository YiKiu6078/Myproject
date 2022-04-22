/********************************************************************************
** Form generated from reading UI file 'PersonInfo.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERSONINFO_H
#define UI_PERSONINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_PersonInfo
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *IdLabel;
    QLabel *nickNameLabel;
    QLabel *signatureLabel;
    QLabel *ageLabel;
    QLabel *sexLabel;
    QLabel *emailLabel;

    void setupUi(QDialog *PersonInfo)
    {
        if (PersonInfo->objectName().isEmpty())
            PersonInfo->setObjectName(QString::fromUtf8("PersonInfo"));
        PersonInfo->resize(329, 334);
        label = new QLabel(PersonInfo);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 67, 17));
        label_2 = new QLabel(PersonInfo);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 80, 67, 17));
        label_3 = new QLabel(PersonInfo);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 120, 67, 17));
        label_4 = new QLabel(PersonInfo);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 160, 67, 17));
        label_5 = new QLabel(PersonInfo);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 200, 67, 17));
        label_6 = new QLabel(PersonInfo);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 240, 67, 17));
        IdLabel = new QLabel(PersonInfo);
        IdLabel->setObjectName(QString::fromUtf8("IdLabel"));
        IdLabel->setGeometry(QRect(120, 40, 67, 17));
        nickNameLabel = new QLabel(PersonInfo);
        nickNameLabel->setObjectName(QString::fromUtf8("nickNameLabel"));
        nickNameLabel->setGeometry(QRect(120, 80, 201, 17));
        signatureLabel = new QLabel(PersonInfo);
        signatureLabel->setObjectName(QString::fromUtf8("signatureLabel"));
        signatureLabel->setGeometry(QRect(120, 120, 201, 17));
        ageLabel = new QLabel(PersonInfo);
        ageLabel->setObjectName(QString::fromUtf8("ageLabel"));
        ageLabel->setGeometry(QRect(120, 160, 67, 17));
        sexLabel = new QLabel(PersonInfo);
        sexLabel->setObjectName(QString::fromUtf8("sexLabel"));
        sexLabel->setGeometry(QRect(120, 200, 67, 17));
        emailLabel = new QLabel(PersonInfo);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));
        emailLabel->setGeometry(QRect(120, 240, 201, 17));

        retranslateUi(PersonInfo);

        QMetaObject::connectSlotsByName(PersonInfo);
    } // setupUi

    void retranslateUi(QDialog *PersonInfo)
    {
        PersonInfo->setWindowTitle(QApplication::translate("PersonInfo", "Dialog", nullptr));
        label->setText(QApplication::translate("PersonInfo", "ID:", nullptr));
        label_2->setText(QApplication::translate("PersonInfo", "\346\230\265\347\247\260:", nullptr));
        label_3->setText(QApplication::translate("PersonInfo", "\344\270\252\346\200\247\347\255\276\345\220\215:", nullptr));
        label_4->setText(QApplication::translate("PersonInfo", "\345\271\264\351\276\204:", nullptr));
        label_5->setText(QApplication::translate("PersonInfo", "\346\200\247\345\210\253:", nullptr));
        label_6->setText(QApplication::translate("PersonInfo", "\347\224\265\345\255\220\351\202\256\344\273\266:", nullptr));
        IdLabel->setText(QApplication::translate("PersonInfo", "TextLabel", nullptr));
        nickNameLabel->setText(QApplication::translate("PersonInfo", "TextLabel", nullptr));
        signatureLabel->setText(QApplication::translate("PersonInfo", "TextLabel", nullptr));
        ageLabel->setText(QApplication::translate("PersonInfo", "TextLabel", nullptr));
        sexLabel->setText(QApplication::translate("PersonInfo", "TextLabel", nullptr));
        emailLabel->setText(QApplication::translate("PersonInfo", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PersonInfo: public Ui_PersonInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERSONINFO_H
