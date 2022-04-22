/********************************************************************************
** Form generated from reading UI file 'SendFileDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDFILEDLG_H
#define UI_SENDFILEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SendFileDlg
{
public:
    QLabel *label;
    QPushButton *OpenFileBtn;
    QPushButton *SendFIleBtn;
    QLabel *label_2;
    QLineEdit *FileName;
    QProgressBar *progressBar;
    QPushButton *CanCelBtn;

    void setupUi(QDialog *SendFileDlg)
    {
        if (SendFileDlg->objectName().isEmpty())
            SendFileDlg->setObjectName(QString::fromUtf8("SendFileDlg"));
        SendFileDlg->resize(358, 223);
        label = new QLabel(SendFileDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 40, 131, 17));
        OpenFileBtn = new QPushButton(SendFileDlg);
        OpenFileBtn->setObjectName(QString::fromUtf8("OpenFileBtn"));
        OpenFileBtn->setGeometry(QRect(140, 40, 89, 25));
        SendFIleBtn = new QPushButton(SendFileDlg);
        SendFIleBtn->setObjectName(QString::fromUtf8("SendFIleBtn"));
        SendFIleBtn->setGeometry(QRect(40, 120, 89, 25));
        label_2 = new QLabel(SendFileDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 80, 91, 17));
        FileName = new QLineEdit(SendFileDlg);
        FileName->setObjectName(QString::fromUtf8("FileName"));
        FileName->setGeometry(QRect(140, 80, 191, 25));
        progressBar = new QProgressBar(SendFileDlg);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(140, 120, 191, 23));
        progressBar->setValue(0);
        CanCelBtn = new QPushButton(SendFileDlg);
        CanCelBtn->setObjectName(QString::fromUtf8("CanCelBtn"));
        CanCelBtn->setGeometry(QRect(240, 180, 89, 25));

        retranslateUi(SendFileDlg);

        QMetaObject::connectSlotsByName(SendFileDlg);
    } // setupUi

    void retranslateUi(QDialog *SendFileDlg)
    {
        SendFileDlg->setWindowTitle(QApplication::translate("SendFileDlg", "Dialog", nullptr));
        label->setText(QApplication::translate("SendFileDlg", "\351\200\211\346\213\251\346\226\207\344\273\266:", nullptr));
        OpenFileBtn->setText(QApplication::translate("SendFileDlg", "\346\211\223\345\274\200", nullptr));
        SendFIleBtn->setText(QApplication::translate("SendFileDlg", "\345\217\221\351\200\201", nullptr));
        label_2->setText(QApplication::translate("SendFileDlg", "\346\226\207\344\273\266\347\233\256\345\275\225:", nullptr));
        CanCelBtn->setText(QApplication::translate("SendFileDlg", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SendFileDlg: public Ui_SendFileDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDFILEDLG_H
