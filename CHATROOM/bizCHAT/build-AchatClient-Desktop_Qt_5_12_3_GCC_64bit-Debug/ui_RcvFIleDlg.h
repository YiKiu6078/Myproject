/********************************************************************************
** Form generated from reading UI file 'RcvFIleDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RCVFILEDLG_H
#define UI_RCVFILEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_RcvFIleDlg
{
public:
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QDialog *RcvFIleDlg)
    {
        if (RcvFIleDlg->objectName().isEmpty())
            RcvFIleDlg->setObjectName(QString::fromUtf8("RcvFIleDlg"));
        RcvFIleDlg->resize(342, 117);
        label = new QLabel(RcvFIleDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 50, 71, 21));
        progressBar = new QProgressBar(RcvFIleDlg);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(110, 50, 211, 23));
        progressBar->setValue(0);

        retranslateUi(RcvFIleDlg);

        QMetaObject::connectSlotsByName(RcvFIleDlg);
    } // setupUi

    void retranslateUi(QDialog *RcvFIleDlg)
    {
        RcvFIleDlg->setWindowTitle(QApplication::translate("RcvFIleDlg", "Dialog", nullptr));
        label->setText(QApplication::translate("RcvFIleDlg", "\346\216\245\346\224\266\350\277\233\345\272\246:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RcvFIleDlg: public Ui_RcvFIleDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RCVFILEDLG_H
