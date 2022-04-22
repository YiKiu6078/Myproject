/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonAvantar;
    QVBoxLayout *verticalLayout;
    QLabel *labelName;
    QLabel *labelSignature;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonHomepage;
    QPushButton *pushButtonMail;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidgetContact;
    QWidget *tab_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonMenu;
    QPushButton *pushButtonAdd;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(300, 700);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        Form->setWindowIcon(icon);
        verticalLayout_3 = new QVBoxLayout(Form);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, -1, 5, -1);
        pushButtonAvantar = new QPushButton(Form);
        pushButtonAvantar->setObjectName(QString::fromUtf8("pushButtonAvantar"));
        pushButtonAvantar->setMinimumSize(QSize(60, 60));
        pushButtonAvantar->setMaximumSize(QSize(60, 60));
        pushButtonAvantar->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonAvantar->setFocusPolicy(Qt::NoFocus);
        pushButtonAvantar->setIcon(icon);
        pushButtonAvantar->setIconSize(QSize(60, 60));
        pushButtonAvantar->setFlat(true);

        horizontalLayout->addWidget(pushButtonAvantar);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(5, -1, -1, -1);
        labelName = new QLabel(Form);
        labelName->setObjectName(QString::fromUtf8("labelName"));
        labelName->setMaximumSize(QSize(100, 16777215));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        labelName->setFont(font);

        verticalLayout->addWidget(labelName);

        labelSignature = new QLabel(Form);
        labelSignature->setObjectName(QString::fromUtf8("labelSignature"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelSignature->sizePolicy().hasHeightForWidth());
        labelSignature->setSizePolicy(sizePolicy);
        labelSignature->setMinimumSize(QSize(215, 0));
        labelSignature->setMaximumSize(QSize(215, 16777215));

        verticalLayout->addWidget(labelSignature);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonHomepage = new QPushButton(Form);
        pushButtonHomepage->setObjectName(QString::fromUtf8("pushButtonHomepage"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonHomepage->sizePolicy().hasHeightForWidth());
        pushButtonHomepage->setSizePolicy(sizePolicy1);
        pushButtonHomepage->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonHomepage->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/qzone.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonHomepage->setIcon(icon1);
        pushButtonHomepage->setFlat(true);

        horizontalLayout_2->addWidget(pushButtonHomepage);

        pushButtonMail = new QPushButton(Form);
        pushButtonMail->setObjectName(QString::fromUtf8("pushButtonMail"));
        sizePolicy1.setHeightForWidth(pushButtonMail->sizePolicy().hasHeightForWidth());
        pushButtonMail->setSizePolicy(sizePolicy1);
        pushButtonMail->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonMail->setFocusPolicy(Qt::NoFocus);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/mail.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonMail->setIcon(icon2);
        pushButtonMail->setFlat(true);

        horizontalLayout_2->addWidget(pushButtonMail);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        lineEdit = new QLineEdit(Form);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);

        tabWidget = new QTabWidget(Form);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        tableWidgetContact = new QTableWidget(tab);
        if (tableWidgetContact->columnCount() < 11)
            tableWidgetContact->setColumnCount(11);
        tableWidgetContact->setObjectName(QString::fromUtf8("tableWidgetContact"));
        tableWidgetContact->setMouseTracking(true);
        tableWidgetContact->setContextMenuPolicy(Qt::CustomContextMenu);
        tableWidgetContact->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidgetContact->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetContact->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetContact->setIconSize(QSize(40, 40));
        tableWidgetContact->setShowGrid(false);
        tableWidgetContact->setColumnCount(11);
        tableWidgetContact->horizontalHeader()->setVisible(false);
        tableWidgetContact->verticalHeader()->setVisible(false);
        tableWidgetContact->verticalHeader()->setMinimumSectionSize(52);
        tableWidgetContact->verticalHeader()->setDefaultSectionSize(30);

        verticalLayout_4->addWidget(tableWidgetContact);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget->addTab(tab_4, QString());

        verticalLayout_2->addWidget(tabWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButtonMenu = new QPushButton(Form);
        pushButtonMenu->setObjectName(QString::fromUtf8("pushButtonMenu"));
        sizePolicy1.setHeightForWidth(pushButtonMenu->sizePolicy().hasHeightForWidth());
        pushButtonMenu->setSizePolicy(sizePolicy1);
        pushButtonMenu->setFocusPolicy(Qt::NoFocus);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/menu.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonMenu->setIcon(icon3);
        pushButtonMenu->setIconSize(QSize(16, 16));
        pushButtonMenu->setFlat(true);

        horizontalLayout_3->addWidget(pushButtonMenu);

        pushButtonAdd = new QPushButton(Form);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
        sizePolicy1.setHeightForWidth(pushButtonAdd->sizePolicy().hasHeightForWidth());
        pushButtonAdd->setSizePolicy(sizePolicy1);
        pushButtonAdd->setFocusPolicy(Qt::NoFocus);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAdd->setIcon(icon4);
        pushButtonAdd->setFlat(true);

        horizontalLayout_3->addWidget(pushButtonAdd);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(Form);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "\346\265\267\345\244\251\351\271\260\350\201\212\345\244\251", nullptr));
        pushButtonAvantar->setText(QString());
        labelName->setText(QApplication::translate("Form", "\346\230\265\347\247\260", nullptr));
        labelSignature->setText(QApplication::translate("Form", "\347\255\276\345\220\215", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonHomepage->setToolTip(QApplication::translate("Form", "\344\270\273\351\241\265", nullptr));
#endif // QT_NO_TOOLTIP
        pushButtonHomepage->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButtonMail->setToolTip(QApplication::translate("Form", "\351\202\256\347\256\261", nullptr));
#endif // QT_NO_TOOLTIP
        pushButtonMail->setText(QString());
        lineEdit->setPlaceholderText(QApplication::translate("Form", "\346\220\234\347\264\242", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Form", "\350\201\224\347\263\273\344\272\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Form", "\347\276\244\350\201\212", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Form", "\347\251\272\351\227\264", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Form", "\344\274\232\350\257\235", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonMenu->setToolTip(QApplication::translate("Form", "\350\217\234\345\215\225", nullptr));
#endif // QT_NO_TOOLTIP
        pushButtonMenu->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButtonAdd->setToolTip(QApplication::translate("Form", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
#endif // QT_NO_TOOLTIP
        pushButtonAdd->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
