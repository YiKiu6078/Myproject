/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QCheckBox *checkBoxRememberPassword;
    QLabel *labelAvatar;
    QPushButton *pushButtonFindPassword;
    QPushButton *pushButtonRegister;
    QLineEdit *lineEditAccount;
    QLineEdit *lineEditPassword;
    QCheckBox *checkBoxAutoLogin;
    QPushButton *pushButtonLogin;
    QLabel *labelBanner;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 10);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, -1, 0);
        checkBoxRememberPassword = new QCheckBox(centralWidget);
        checkBoxRememberPassword->setObjectName(QString::fromUtf8("checkBoxRememberPassword"));
        checkBoxRememberPassword->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(checkBoxRememberPassword, 3, 1, 1, 1);

        labelAvatar = new QLabel(centralWidget);
        labelAvatar->setObjectName(QString::fromUtf8("labelAvatar"));
        labelAvatar->setMaximumSize(QSize(80, 80));
        labelAvatar->setPixmap(QPixmap(QString::fromUtf8(":/icon.png")));
        labelAvatar->setScaledContents(false);
        labelAvatar->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelAvatar, 1, 0, 2, 1);

        pushButtonFindPassword = new QPushButton(centralWidget);
        pushButtonFindPassword->setObjectName(QString::fromUtf8("pushButtonFindPassword"));
        pushButtonFindPassword->setFocusPolicy(Qt::NoFocus);
        pushButtonFindPassword->setStyleSheet(QString::fromUtf8("color:rgb(0,155,219)"));
        pushButtonFindPassword->setFlat(true);

        gridLayout->addWidget(pushButtonFindPassword, 2, 3, 1, 1);

        pushButtonRegister = new QPushButton(centralWidget);
        pushButtonRegister->setObjectName(QString::fromUtf8("pushButtonRegister"));
        pushButtonRegister->setFocusPolicy(Qt::NoFocus);
        pushButtonRegister->setStyleSheet(QString::fromUtf8("color:rgb(0,155,219)"));
        pushButtonRegister->setFlat(true);

        gridLayout->addWidget(pushButtonRegister, 1, 3, 1, 1);

        lineEditAccount = new QLineEdit(centralWidget);
        lineEditAccount->setObjectName(QString::fromUtf8("lineEditAccount"));

        gridLayout->addWidget(lineEditAccount, 1, 1, 1, 2);

        lineEditPassword = new QLineEdit(centralWidget);
        lineEditPassword->setObjectName(QString::fromUtf8("lineEditPassword"));
        lineEditPassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEditPassword, 2, 1, 1, 2);

        checkBoxAutoLogin = new QCheckBox(centralWidget);
        checkBoxAutoLogin->setObjectName(QString::fromUtf8("checkBoxAutoLogin"));
        checkBoxAutoLogin->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(checkBoxAutoLogin, 3, 2, 1, 1);

        pushButtonLogin = new QPushButton(centralWidget);
        pushButtonLogin->setObjectName(QString::fromUtf8("pushButtonLogin"));
        pushButtonLogin->setFocusPolicy(Qt::NoFocus);
        pushButtonLogin->setStyleSheet(QString::fromUtf8("color:white;background-color:rgb(0,155,219)"));

        gridLayout->addWidget(pushButtonLogin, 5, 1, 1, 2);

        labelBanner = new QLabel(centralWidget);
        labelBanner->setObjectName(QString::fromUtf8("labelBanner"));
        labelBanner->setStyleSheet(QString::fromUtf8("background-image:url(\":/bg.jpg\")"));
        labelBanner->setPixmap(QPixmap(QString::fromUtf8(":/logo.png")));
        labelBanner->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelBanner, 0, 0, 1, 4);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\265\267\345\244\251\351\271\260\350\201\212\345\244\251", nullptr));
        checkBoxRememberPassword->setText(QApplication::translate("MainWindow", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
        labelAvatar->setText(QString());
        pushButtonFindPassword->setText(QApplication::translate("MainWindow", "\346\211\276\345\233\236\345\257\206\347\240\201", nullptr));
        pushButtonRegister->setText(QApplication::translate("MainWindow", "\346\263\250\345\206\214\350\264\246\345\217\267", nullptr));
        lineEditAccount->setPlaceholderText(QApplication::translate("MainWindow", "\350\264\246\345\217\267", nullptr));
        lineEditPassword->setPlaceholderText(QApplication::translate("MainWindow", "\345\257\206\347\240\201", nullptr));
        checkBoxAutoLogin->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\347\231\273\345\275\225", nullptr));
        pushButtonLogin->setText(QApplication::translate("MainWindow", "\347\231\273    \345\275\225", nullptr));
        labelBanner->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
