/********************************************************************************
** Form generated from reading UI file 'formreg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMREG_H
#define UI_FORMREG_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormReg
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *lineEditHomepage;
    QPushButton *pushButtonDisplayPassword;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_7;
    QLineEdit *lineEditDomicile;
    QLabel *label;
    QLabel *labelAvantar;
    QLabel *label_8;
    QLineEdit *lineEditAvantar;
    QLabel *label_9;
    QComboBox *comboBoxSex;
    QLineEdit *lineEditPhoneNumber;
    QLineEdit *lineEditPassword;
    QLabel *label_4;
    QLineEdit *lineEditEmail;
    QLineEdit *lineEditName;
    QLabel *label_5;
    QDateEdit *dateEditBirthday;
    QLabel *labelAccount;
    QLabel *label_10;
    QLineEdit *lineEdit_verificationCode;
    QPushButton *pushButton_genVerificationCode;
    QPushButton *pushButtonRegister;

    void setupUi(QWidget *FormReg)
    {
        if (FormReg->objectName().isEmpty())
            FormReg->setObjectName(QString::fromUtf8("FormReg"));
        FormReg->resize(300, 457);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        FormReg->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(FormReg);
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEditHomepage = new QLineEdit(FormReg);
        lineEditHomepage->setObjectName(QString::fromUtf8("lineEditHomepage"));

        gridLayout->addWidget(lineEditHomepage, 9, 1, 1, 1);

        pushButtonDisplayPassword = new QPushButton(FormReg);
        pushButtonDisplayPassword->setObjectName(QString::fromUtf8("pushButtonDisplayPassword"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonDisplayPassword->sizePolicy().hasHeightForWidth());
        pushButtonDisplayPassword->setSizePolicy(sizePolicy);
        pushButtonDisplayPassword->setMaximumSize(QSize(50, 16777215));
        pushButtonDisplayPassword->setCheckable(true);

        gridLayout->addWidget(pushButtonDisplayPassword, 3, 2, 1, 1);

        label_6 = new QLabel(FormReg);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        label_3 = new QLabel(FormReg);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(FormReg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 9, 0, 1, 1);

        label_7 = new QLabel(FormReg);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        lineEditDomicile = new QLineEdit(FormReg);
        lineEditDomicile->setObjectName(QString::fromUtf8("lineEditDomicile"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditDomicile->sizePolicy().hasHeightForWidth());
        lineEditDomicile->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditDomicile, 6, 1, 1, 1);

        label = new QLabel(FormReg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        labelAvantar = new QLabel(FormReg);
        labelAvantar->setObjectName(QString::fromUtf8("labelAvantar"));
        sizePolicy.setHeightForWidth(labelAvantar->sizePolicy().hasHeightForWidth());
        labelAvantar->setSizePolicy(sizePolicy);
        labelAvantar->setMinimumSize(QSize(60, 60));
        labelAvantar->setMaximumSize(QSize(60, 60));
        labelAvantar->setPixmap(QPixmap(QString::fromUtf8(":/icon.png")));

        gridLayout->addWidget(labelAvantar, 1, 0, 1, 1);

        label_8 = new QLabel(FormReg);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        lineEditAvantar = new QLineEdit(FormReg);
        lineEditAvantar->setObjectName(QString::fromUtf8("lineEditAvantar"));

        gridLayout->addWidget(lineEditAvantar, 1, 1, 1, 1);

        label_9 = new QLabel(FormReg);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        comboBoxSex = new QComboBox(FormReg);
        comboBoxSex->setObjectName(QString::fromUtf8("comboBoxSex"));
        sizePolicy.setHeightForWidth(comboBoxSex->sizePolicy().hasHeightForWidth());
        comboBoxSex->setSizePolicy(sizePolicy);
        comboBoxSex->setMinimumSize(QSize(50, 0));
        comboBoxSex->setMaximumSize(QSize(50, 16777215));
        comboBoxSex->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout->addWidget(comboBoxSex, 4, 1, 1, 1);

        lineEditPhoneNumber = new QLineEdit(FormReg);
        lineEditPhoneNumber->setObjectName(QString::fromUtf8("lineEditPhoneNumber"));
        sizePolicy1.setHeightForWidth(lineEditPhoneNumber->sizePolicy().hasHeightForWidth());
        lineEditPhoneNumber->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditPhoneNumber, 7, 1, 1, 1);

        lineEditPassword = new QLineEdit(FormReg);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));
        sizePolicy1.setHeightForWidth(lineEditPassword->sizePolicy().hasHeightForWidth());
        lineEditPassword->setSizePolicy(sizePolicy1);
        lineEditPassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEditPassword, 3, 1, 1, 1);

        label_4 = new QLabel(FormReg);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineEditEmail = new QLineEdit(FormReg);
        lineEditEmail->setObjectName(QString::fromUtf8("lineEditEmail"));
        sizePolicy1.setHeightForWidth(lineEditEmail->sizePolicy().hasHeightForWidth());
        lineEditEmail->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditEmail, 8, 1, 1, 1);

        lineEditName = new QLineEdit(FormReg);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));
        sizePolicy1.setHeightForWidth(lineEditName->sizePolicy().hasHeightForWidth());
        lineEditName->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditName, 2, 1, 1, 1);

        label_5 = new QLabel(FormReg);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        dateEditBirthday = new QDateEdit(FormReg);
        dateEditBirthday->setObjectName(QString::fromUtf8("dateEditBirthday"));
        sizePolicy.setHeightForWidth(dateEditBirthday->sizePolicy().hasHeightForWidth());
        dateEditBirthday->setSizePolicy(sizePolicy);
        dateEditBirthday->setDate(QDate(1980, 1, 1));

        gridLayout->addWidget(dateEditBirthday, 5, 1, 1, 1);

        labelAccount = new QLabel(FormReg);
        labelAccount->setObjectName(QString::fromUtf8("labelAccount"));

        gridLayout->addWidget(labelAccount, 0, 1, 1, 1);

        label_10 = new QLabel(FormReg);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_10, 10, 0, 1, 1);

        lineEdit_verificationCode = new QLineEdit(FormReg);
        lineEdit_verificationCode->setObjectName(QString::fromUtf8("lineEdit_verificationCode"));

        gridLayout->addWidget(lineEdit_verificationCode, 10, 1, 1, 1);

        pushButton_genVerificationCode = new QPushButton(FormReg);
        pushButton_genVerificationCode->setObjectName(QString::fromUtf8("pushButton_genVerificationCode"));
        pushButton_genVerificationCode->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(pushButton_genVerificationCode, 10, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        pushButtonRegister = new QPushButton(FormReg);
        pushButtonRegister->setObjectName(QString::fromUtf8("pushButtonRegister"));
        sizePolicy.setHeightForWidth(pushButtonRegister->sizePolicy().hasHeightForWidth());
        pushButtonRegister->setSizePolicy(sizePolicy);
        pushButtonRegister->setStyleSheet(QString::fromUtf8("color:white;background-color:rgb(0,155,219)"));

        verticalLayout->addWidget(pushButtonRegister, 0, Qt::AlignHCenter);

        QWidget::setTabOrder(lineEditAvantar, lineEditName);
        QWidget::setTabOrder(lineEditName, lineEditPassword);
        QWidget::setTabOrder(lineEditPassword, comboBoxSex);
        QWidget::setTabOrder(comboBoxSex, dateEditBirthday);
        QWidget::setTabOrder(dateEditBirthday, lineEditDomicile);
        QWidget::setTabOrder(lineEditDomicile, lineEditPhoneNumber);
        QWidget::setTabOrder(lineEditPhoneNumber, lineEditEmail);
        QWidget::setTabOrder(lineEditEmail, lineEditHomepage);
        QWidget::setTabOrder(lineEditHomepage, pushButtonRegister);
        QWidget::setTabOrder(pushButtonRegister, pushButtonDisplayPassword);

        retranslateUi(FormReg);

        QMetaObject::connectSlotsByName(FormReg);
    } // setupUi

    void retranslateUi(QWidget *FormReg)
    {
        FormReg->setWindowTitle(QApplication::translate("FormReg", "\346\263\250\345\206\214", nullptr));
        lineEditHomepage->setPlaceholderText(QApplication::translate("FormReg", "http://", nullptr));
        pushButtonDisplayPassword->setText(QApplication::translate("FormReg", "\346\230\276\347\244\272", nullptr));
        label_6->setText(QApplication::translate("FormReg", "\347\224\237\346\227\245", nullptr));
        label_3->setText(QApplication::translate("FormReg", "\346\230\265\347\247\260", nullptr));
        label_2->setText(QApplication::translate("FormReg", "\344\270\273\351\241\265", nullptr));
        label_7->setText(QApplication::translate("FormReg", "\346\211\200\345\234\250\345\234\260", nullptr));
        label->setText(QApplication::translate("FormReg", "\350\264\246\345\217\267", nullptr));
        labelAvantar->setText(QString());
        label_8->setText(QApplication::translate("FormReg", "\346\211\213\346\234\272\345\217\267\347\240\201", nullptr));
        lineEditAvantar->setPlaceholderText(QApplication::translate("FormReg", "http://", nullptr));
        label_9->setText(QApplication::translate("FormReg", "\347\224\265\345\255\220\351\202\256\347\256\261", nullptr));
        lineEditPhoneNumber->setPlaceholderText(QApplication::translate("FormReg", "86", nullptr));
        label_4->setText(QApplication::translate("FormReg", "\345\257\206\347\240\201", nullptr));
        label_5->setText(QApplication::translate("FormReg", "\346\200\247\345\210\253", nullptr));
        dateEditBirthday->setDisplayFormat(QApplication::translate("FormReg", "yyyy-M-d", nullptr));
        labelAccount->setText(QApplication::translate("FormReg", "ID", nullptr));
        label_10->setText(QApplication::translate("FormReg", "\351\252\214\350\257\201\347\240\201", nullptr));
        pushButton_genVerificationCode->setText(QApplication::translate("FormReg", "abcd", nullptr));
        pushButtonRegister->setText(QApplication::translate("FormReg", "\347\253\213\345\215\263\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FormReg: public Ui_FormReg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMREG_H
