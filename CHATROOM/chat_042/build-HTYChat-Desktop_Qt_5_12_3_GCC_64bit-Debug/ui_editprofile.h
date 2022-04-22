/********************************************************************************
** Form generated from reading UI file 'editprofile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITPROFILE_H
#define UI_EDITPROFILE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EditProfile
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QTextEdit *textEditSignature;
    QDateEdit *dateEditBirthday;
    QLabel *label_6;
    QLabel *label_11;
    QLabel *label_13;
    QComboBox *comboBoxSex;
    QLineEdit *lineEditDomicile;
    QLabel *label_8;
    QLineEdit *lineEditPhoneNumber;
    QLineEdit *lineEditEmail;
    QLabel *label_12;
    QLabel *label_9;
    QLabel *label_7;
    QLineEdit *lineEditHomepage;
    QLineEdit *lineEditName;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonSave;
    QPushButton *pushButtonClose;
    QLabel *labelAvantar;
    QLineEdit *lineEditAvantar;

    void setupUi(QWidget *EditProfile)
    {
        if (EditProfile->objectName().isEmpty())
            EditProfile->setObjectName(QString::fromUtf8("EditProfile"));
        EditProfile->resize(381, 500);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        EditProfile->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(EditProfile);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textEditSignature = new QTextEdit(EditProfile);
        textEditSignature->setObjectName(QString::fromUtf8("textEditSignature"));

        gridLayout->addWidget(textEditSignature, 8, 1, 1, 1);

        dateEditBirthday = new QDateEdit(EditProfile);
        dateEditBirthday->setObjectName(QString::fromUtf8("dateEditBirthday"));
        dateEditBirthday->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(dateEditBirthday, 3, 1, 1, 1);

        label_6 = new QLabel(EditProfile);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        label_11 = new QLabel(EditProfile);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 6, 0, 1, 1);

        label_13 = new QLabel(EditProfile);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_13, 8, 0, 1, 1);

        comboBoxSex = new QComboBox(EditProfile);
        comboBoxSex->setObjectName(QString::fromUtf8("comboBoxSex"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxSex->sizePolicy().hasHeightForWidth());
        comboBoxSex->setSizePolicy(sizePolicy);

        gridLayout->addWidget(comboBoxSex, 2, 1, 1, 1);

        lineEditDomicile = new QLineEdit(EditProfile);
        lineEditDomicile->setObjectName(QString::fromUtf8("lineEditDomicile"));

        gridLayout->addWidget(lineEditDomicile, 4, 1, 1, 1);

        label_8 = new QLabel(EditProfile);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 3, 0, 1, 1);

        lineEditPhoneNumber = new QLineEdit(EditProfile);
        lineEditPhoneNumber->setObjectName(QString::fromUtf8("lineEditPhoneNumber"));

        gridLayout->addWidget(lineEditPhoneNumber, 5, 1, 1, 1);

        lineEditEmail = new QLineEdit(EditProfile);
        lineEditEmail->setObjectName(QString::fromUtf8("lineEditEmail"));

        gridLayout->addWidget(lineEditEmail, 6, 1, 1, 1);

        label_12 = new QLabel(EditProfile);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_12, 7, 0, 1, 1);

        label_9 = new QLabel(EditProfile);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_9, 4, 0, 1, 1);

        label_7 = new QLabel(EditProfile);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 2, 0, 1, 1);

        lineEditHomepage = new QLineEdit(EditProfile);
        lineEditHomepage->setObjectName(QString::fromUtf8("lineEditHomepage"));

        gridLayout->addWidget(lineEditHomepage, 7, 1, 1, 1);

        lineEditName = new QLineEdit(EditProfile);
        lineEditName->setObjectName(QString::fromUtf8("lineEditName"));

        gridLayout->addWidget(lineEditName, 1, 1, 1, 1);

        label_10 = new QLabel(EditProfile);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_10, 5, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonSave = new QPushButton(EditProfile);
        pushButtonSave->setObjectName(QString::fromUtf8("pushButtonSave"));

        horizontalLayout->addWidget(pushButtonSave);

        pushButtonClose = new QPushButton(EditProfile);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));

        horizontalLayout->addWidget(pushButtonClose);


        gridLayout->addLayout(horizontalLayout, 9, 1, 1, 1);

        labelAvantar = new QLabel(EditProfile);
        labelAvantar->setObjectName(QString::fromUtf8("labelAvantar"));
        sizePolicy.setHeightForWidth(labelAvantar->sizePolicy().hasHeightForWidth());
        labelAvantar->setSizePolicy(sizePolicy);
        labelAvantar->setMinimumSize(QSize(60, 60));
        labelAvantar->setMaximumSize(QSize(60, 60));
        labelAvantar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelAvantar, 0, 0, 1, 1);

        lineEditAvantar = new QLineEdit(EditProfile);
        lineEditAvantar->setObjectName(QString::fromUtf8("lineEditAvantar"));

        gridLayout->addWidget(lineEditAvantar, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(EditProfile);

        QMetaObject::connectSlotsByName(EditProfile);
    } // setupUi

    void retranslateUi(QWidget *EditProfile)
    {
        EditProfile->setWindowTitle(QApplication::translate("EditProfile", "\347\274\226\350\276\221\350\265\204\346\226\231", nullptr));
        dateEditBirthday->setDisplayFormat(QApplication::translate("EditProfile", "yyyy/M/d", nullptr));
        label_6->setText(QApplication::translate("EditProfile", "\346\230\265\347\247\260", nullptr));
        label_11->setText(QApplication::translate("EditProfile", "\347\224\265\345\255\220\351\202\256\347\256\261", nullptr));
        label_13->setText(QApplication::translate("EditProfile", "\347\255\276\345\220\215", nullptr));
        label_8->setText(QApplication::translate("EditProfile", "\347\224\237\346\227\245", nullptr));
        label_12->setText(QApplication::translate("EditProfile", "\344\270\273\351\241\265", nullptr));
        label_9->setText(QApplication::translate("EditProfile", "\346\211\200\345\234\250\345\234\260", nullptr));
        label_7->setText(QApplication::translate("EditProfile", "\346\200\247\345\210\253", nullptr));
        label_10->setText(QApplication::translate("EditProfile", "\346\211\213\346\234\272\345\217\267\347\240\201", nullptr));
        pushButtonSave->setText(QApplication::translate("EditProfile", "\344\277\235\345\255\230", nullptr));
        pushButtonClose->setText(QApplication::translate("EditProfile", "\345\205\263\351\227\255", nullptr));
        labelAvantar->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class EditProfile: public Ui_EditProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITPROFILE_H
