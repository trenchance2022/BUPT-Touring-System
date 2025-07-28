/********************************************************************************
** Form generated from reading UI file 'functionselectpage.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FUNCTIONSELECTPAGE_H
#define UI_FUNCTIONSELECTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FunctionSelectPage
{
public:
    QComboBox *comboBox;
    QPushButton *btn_function_confirm;
    QPushButton *btn_function_quit;

    void setupUi(QWidget *FunctionSelectPage)
    {
        if (FunctionSelectPage->objectName().isEmpty())
            FunctionSelectPage->setObjectName("FunctionSelectPage");
        FunctionSelectPage->resize(260, 128);
        comboBox = new QComboBox(FunctionSelectPage);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(40, 30, 181, 31));
        btn_function_confirm = new QPushButton(FunctionSelectPage);
        btn_function_confirm->setObjectName("btn_function_confirm");
        btn_function_confirm->setGeometry(QRect(40, 80, 80, 21));
        btn_function_quit = new QPushButton(FunctionSelectPage);
        btn_function_quit->setObjectName("btn_function_quit");
        btn_function_quit->setGeometry(QRect(140, 80, 80, 21));

        retranslateUi(FunctionSelectPage);

        QMetaObject::connectSlotsByName(FunctionSelectPage);
    } // setupUi

    void retranslateUi(QWidget *FunctionSelectPage)
    {
        FunctionSelectPage->setWindowTitle(QCoreApplication::translate("FunctionSelectPage", "Form", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("FunctionSelectPage", "\346\270\270\345\255\246\346\216\250\350\215\220", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("FunctionSelectPage", "\346\227\245\350\256\260\347\256\241\347\220\206", nullptr));

        btn_function_confirm->setText(QCoreApplication::translate("FunctionSelectPage", "\347\241\256\345\256\232", nullptr));
        btn_function_quit->setText(QCoreApplication::translate("FunctionSelectPage", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FunctionSelectPage: public Ui_FunctionSelectPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FUNCTIONSELECTPAGE_H
