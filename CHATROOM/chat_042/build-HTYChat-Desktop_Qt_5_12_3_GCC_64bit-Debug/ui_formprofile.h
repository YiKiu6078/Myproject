/********************************************************************************
** Form generated from reading UI file 'formprofile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMPROFILE_H
#define UI_FORMPROFILE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormProfile
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_10;
    QLabel *label_3;
    QLabel *label_11;
    QLabel *label;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *labelRegTime;
    QLabel *label_7;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *labelSex;
    QLabel *labelID;
    QHBoxLayout *horizontalLayout;
    QLabel *labelName;
    QLabel *labelAvantarUrl;
    QPushButton *pushButtonEdit;
    QLabel *labelDomicile;
    QLabel *labelBirthday;
    QLabel *labelPhoneNumber;
    QLabel *labelEmail;
    QLabel *labelHomepage;
    QLabel *labelSignature;
    QLabel *labelAvantar;

    void setupUi(QWidget *FormProfile)
    {
        if (FormProfile->objectName().isEmpty())
            FormProfile->setObjectName(QString::fromUtf8("FormProfile"));
        FormProfile->resize(380, 450);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        FormProfile->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(FormProfile);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_10 = new QLabel(FormProfile);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_10, 8, 0, 1, 1);

        label_3 = new QLabel(FormProfile);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        label_11 = new QLabel(FormProfile);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 9, 0, 1, 1);

        label = new QLabel(FormProfile);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 3, 0, 1, 1);

        label_8 = new QLabel(FormProfile);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 6, 0, 1, 1);

        label_9 = new QLabel(FormProfile);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_9, 7, 0, 1, 1);

        labelRegTime = new QLabel(FormProfile);
        labelRegTime->setObjectName(QString::fromUtf8("labelRegTime"));

        gridLayout->addWidget(labelRegTime, 4, 1, 1, 1);

        label_7 = new QLabel(FormProfile);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        label_12 = new QLabel(FormProfile);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_12, 10, 0, 1, 1);

        label_13 = new QLabel(FormProfile);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_13, 11, 0, 1, 1);

        labelSex = new QLabel(FormProfile);
        labelSex->setObjectName(QString::fromUtf8("labelSex"));

        gridLayout->addWidget(labelSex, 5, 1, 1, 1);

        labelID = new QLabel(FormProfile);
        labelID->setObjectName(QString::fromUtf8("labelID"));

        gridLayout->addWidget(labelID, 3, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelName = new QLabel(FormProfile);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        labelName->setFont(font);

        horizontalLayout->addWidget(labelName);

        labelAvantarUrl = new QLabel(FormProfile);
        labelAvantarUrl->setObjectName(QString::fromUtf8("labelAvantarUrl"));

        horizontalLayout->addWidget(labelAvantarUrl);

        pushButtonEdit = new QPushButton(FormProfile);
        pushButtonEdit->setObjectName(QString::fromUtf8("pushButtonEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButtonEdit->sizePolicy().hasHeightForWidth());
        pushButtonEdit->setSizePolicy(sizePolicy);
        pushButtonEdit->setMinimumSize(QSize(0, 0));
        pushButtonEdit->setMaximumSize(QSize(60, 16777215));
        pushButtonEdit->setFlat(true);

        horizontalLayout->addWidget(pushButtonEdit);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        labelDomicile = new QLabel(FormProfile);
        labelDomicile->setObjectName(QString::fromUtf8("labelDomicile"));

        gridLayout->addWidget(labelDomicile, 7, 1, 1, 1);

        labelBirthday = new QLabel(FormProfile);
        labelBirthday->setObjectName(QString::fromUtf8("labelBirthday"));

        gridLayout->addWidget(labelBirthday, 6, 1, 1, 1);

        labelPhoneNumber = new QLabel(FormProfile);
        labelPhoneNumber->setObjectName(QString::fromUtf8("labelPhoneNumber"));

        gridLayout->addWidget(labelPhoneNumber, 8, 1, 1, 1);

        labelEmail = new QLabel(FormProfile);
        labelEmail->setObjectName(QString::fromUtf8("labelEmail"));

        gridLayout->addWidget(labelEmail, 9, 1, 1, 1);

        labelHomepage = new QLabel(FormProfile);
        labelHomepage->setObjectName(QString::fromUtf8("labelHomepage"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labelHomepage->sizePolicy().hasHeightForWidth());
        labelHomepage->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(labelHomepage, 10, 1, 1, 1);

        labelSignature = new QLabel(FormProfile);
        labelSignature->setObjectName(QString::fromUtf8("labelSignature"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelSignature->sizePolicy().hasHeightForWidth());
        labelSignature->setSizePolicy(sizePolicy2);
        labelSignature->setMinimumSize(QSize(0, 100));
        labelSignature->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        labelSignature->setWordWrap(true);

        gridLayout->addWidget(labelSignature, 11, 1, 1, 1);

        labelAvantar = new QLabel(FormProfile);
        labelAvantar->setObjectName(QString::fromUtf8("labelAvantar"));
        sizePolicy.setHeightForWidth(labelAvantar->sizePolicy().hasHeightForWidth());
        labelAvantar->setSizePolicy(sizePolicy);
        labelAvantar->setMinimumSize(QSize(60, 60));
        labelAvantar->setMaximumSize(QSize(60, 60));
        labelAvantar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelAvantar, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(FormProfile);

        QMetaObject::connectSlotsByName(FormProfile);
    } // setupUi

    void retranslateUi(QWidget *FormProfile)
    {
        FormProfile->setWindowTitle(QApplication::translate("FormProfile", "\350\265\204\346\226\231", nullptr));
        label_10->setText(QApplication::translate("FormProfile", "\346\211\213\346\234\272\345\217\267\347\240\201", nullptr));
        label_3->setText(QApplication::translate("FormProfile", "\346\263\250\345\206\214\346\227\266\351\227\264", nullptr));
        label_11->setText(QApplication::translate("FormProfile", "\347\224\265\345\255\220\351\202\256\347\256\261", nullptr));
        label->setText(QApplication::translate("FormProfile", "\350\264\246\345\217\267", nullptr));
        label_8->setText(QApplication::translate("FormProfile", "\347\224\237\346\227\245", nullptr));
        label_9->setText(QApplication::translate("FormProfile", "\346\211\200\345\234\250\345\234\260", nullptr));
        labelRegTime->setText(QString());
        label_7->setText(QApplication::translate("FormProfile", "\346\200\247\345\210\253", nullptr));
        label_12->setText(QApplication::translate("FormProfile", "\344\270\273\351\241\265", nullptr));
        label_13->setText(QApplication::translate("FormProfile", "\347\255\276\345\220\215", nullptr));
        labelSex->setText(QString());
        labelID->setText(QString());
        labelName->setText(QApplication::translate("FormProfile", "\346\230\265\347\247\260", nullptr));
        labelAvantarUrl->setText(QString());
        pushButtonEdit->setText(QApplication::translate("FormProfile", "\344\277\256\346\224\271\350\265\204\346\226\231", nullptr));
        labelDomicile->setText(QString());
        labelBirthday->setText(QString());
        labelPhoneNumber->setText(QString());
        labelEmail->setText(QString());
        labelHomepage->setText(QString());
        labelSignature->setText(QString());
        labelAvantar->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FormProfile: public Ui_FormProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMPROFILE_H
