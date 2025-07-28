/********************************************************************************
** Form generated from reading UI file 'diarymanagement.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIARYMANAGEMENT_H
#define UI_DIARYMANAGEMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_diaryManagement
{
public:
    QListView *diaryView;
    QLineEdit *diarySearch;
    QComboBox *comboMethod;
    QComboBox *comboSort;
    QPushButton *btnSearch;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboInterest;
    QPushButton *creatBnt;
    QPushButton *backBnt;

    void setupUi(QWidget *diaryManagement)
    {
        if (diaryManagement->objectName().isEmpty())
            diaryManagement->setObjectName("diaryManagement");
        diaryManagement->resize(786, 472);
        QFont font;
        font.setBold(false);
        diaryManagement->setFont(font);
        diaryView = new QListView(diaryManagement);
        diaryView->setObjectName("diaryView");
        diaryView->setGeometry(QRect(30, 30, 501, 421));
        diarySearch = new QLineEdit(diaryManagement);
        diarySearch->setObjectName("diarySearch");
        diarySearch->setGeometry(QRect(550, 50, 131, 20));
        comboMethod = new QComboBox(diaryManagement);
        comboMethod->addItem(QString());
        comboMethod->addItem(QString());
        comboMethod->addItem(QString());
        comboMethod->setObjectName("comboMethod");
        comboMethod->setGeometry(QRect(550, 120, 171, 22));
        comboSort = new QComboBox(diaryManagement);
        comboSort->addItem(QString());
        comboSort->addItem(QString());
        comboSort->addItem(QString());
        comboSort->addItem(QString());
        comboSort->setObjectName("comboSort");
        comboSort->setGeometry(QRect(550, 190, 171, 22));
        btnSearch = new QPushButton(diaryManagement);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setGeometry(QRect(700, 50, 51, 20));
        label = new QLabel(diaryManagement);
        label->setObjectName("label");
        label->setGeometry(QRect(550, 90, 71, 21));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        label->setFont(font1);
        label_2 = new QLabel(diaryManagement);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(550, 160, 71, 21));
        label_2->setFont(font1);
        label_3 = new QLabel(diaryManagement);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(550, 230, 61, 21));
        label_3->setFont(font1);
        comboInterest = new QComboBox(diaryManagement);
        comboInterest->addItem(QString());
        comboInterest->addItem(QString());
        comboInterest->addItem(QString());
        comboInterest->addItem(QString());
        comboInterest->addItem(QString());
        comboInterest->addItem(QString());
        comboInterest->addItem(QString());
        comboInterest->addItem(QString());
        comboInterest->setObjectName("comboInterest");
        comboInterest->setGeometry(QRect(550, 260, 171, 22));
        creatBnt = new QPushButton(diaryManagement);
        creatBnt->setObjectName("creatBnt");
        creatBnt->setGeometry(QRect(620, 330, 91, 31));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(false);
        creatBnt->setFont(font2);
        backBnt = new QPushButton(diaryManagement);
        backBnt->setObjectName("backBnt");
        backBnt->setGeometry(QRect(620, 380, 91, 21));

        retranslateUi(diaryManagement);

        QMetaObject::connectSlotsByName(diaryManagement);
    } // setupUi

    void retranslateUi(QWidget *diaryManagement)
    {
        diaryManagement->setWindowTitle(QCoreApplication::translate("diaryManagement", "Form", nullptr));
        comboMethod->setItemText(0, QCoreApplication::translate("diaryManagement", "\346\214\211\345\234\260\347\202\271\346\220\234\347\264\242", nullptr));
        comboMethod->setItemText(1, QCoreApplication::translate("diaryManagement", "\346\214\211\346\240\207\351\242\230\346\220\234\347\264\242", nullptr));
        comboMethod->setItemText(2, QCoreApplication::translate("diaryManagement", "\346\214\211\345\206\205\345\256\271\346\220\234\347\264\242", nullptr));

        comboSort->setItemText(0, QCoreApplication::translate("diaryManagement", "\346\227\240", nullptr));
        comboSort->setItemText(1, QCoreApplication::translate("diaryManagement", "\350\257\204\345\210\206\345\211\215\345\215\201", nullptr));
        comboSort->setItemText(2, QCoreApplication::translate("diaryManagement", "\344\272\272\346\260\224\345\211\215\345\215\201", nullptr));
        comboSort->setItemText(3, QCoreApplication::translate("diaryManagement", "\346\214\211\345\205\264\350\266\243\347\232\204\344\272\272\346\260\224\345\211\215\345\215\201", nullptr));

        btnSearch->setText(QCoreApplication::translate("diaryManagement", "\346\220\234\347\264\242", nullptr));
        label->setText(QCoreApplication::translate("diaryManagement", "\346\220\234\347\264\242\346\226\271\345\274\217", nullptr));
        label_2->setText(QCoreApplication::translate("diaryManagement", "\346\216\222\345\272\217\346\226\271\345\274\217", nullptr));
        label_3->setText(QCoreApplication::translate("diaryManagement", "\345\205\264\350\266\243\345\201\217\345\245\275", nullptr));
        comboInterest->setItemText(0, QCoreApplication::translate("diaryManagement", "\347\247\221\346\212\200", nullptr));
        comboInterest->setItemText(1, QCoreApplication::translate("diaryManagement", "\350\211\272\346\234\257", nullptr));
        comboInterest->setItemText(2, QCoreApplication::translate("diaryManagement", "\346\225\231\350\202\262", nullptr));
        comboInterest->setItemText(3, QCoreApplication::translate("diaryManagement", "\345\214\273\345\255\246", nullptr));
        comboInterest->setItemText(4, QCoreApplication::translate("diaryManagement", "\351\207\221\350\236\215", nullptr));
        comboInterest->setItemText(5, QCoreApplication::translate("diaryManagement", "\345\210\222\350\210\271", nullptr));
        comboInterest->setItemText(6, QCoreApplication::translate("diaryManagement", "\347\231\273\345\261\261", nullptr));
        comboInterest->setItemText(7, QCoreApplication::translate("diaryManagement", "\345\276\222\346\255\245", nullptr));

        creatBnt->setText(QCoreApplication::translate("diaryManagement", "\345\210\233\345\273\272\346\227\245\350\256\260", nullptr));
        backBnt->setText(QCoreApplication::translate("diaryManagement", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class diaryManagement: public Ui_diaryManagement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIARYMANAGEMENT_H
