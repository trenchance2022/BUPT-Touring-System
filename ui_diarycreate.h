/********************************************************************************
** Form generated from reading UI file 'diarycreate.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIARYCREATE_H
#define UI_DIARYCREATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiaryCreate
{
public:
    QPlainTextEdit *content;
    QLineEdit *title;
    QLineEdit *dest;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *confirm;
    QPushButton *cancel;

    void setupUi(QWidget *DiaryCreate)
    {
        if (DiaryCreate->objectName().isEmpty())
            DiaryCreate->setObjectName("DiaryCreate");
        DiaryCreate->resize(642, 428);
        content = new QPlainTextEdit(DiaryCreate);
        content->setObjectName("content");
        content->setGeometry(QRect(80, 130, 521, 221));
        title = new QLineEdit(DiaryCreate);
        title->setObjectName("title");
        title->setGeometry(QRect(80, 30, 141, 21));
        dest = new QLineEdit(DiaryCreate);
        dest->setObjectName("dest");
        dest->setGeometry(QRect(80, 80, 141, 21));
        label = new QLabel(DiaryCreate);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 51, 21));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(DiaryCreate);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 80, 51, 21));
        label_2->setFont(font);
        label_3 = new QLabel(DiaryCreate);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 120, 51, 31));
        label_3->setFont(font);
        confirm = new QPushButton(DiaryCreate);
        confirm->setObjectName("confirm");
        confirm->setGeometry(QRect(420, 380, 81, 31));
        confirm->setFont(font);
        cancel = new QPushButton(DiaryCreate);
        cancel->setObjectName("cancel");
        cancel->setGeometry(QRect(520, 380, 81, 31));
        cancel->setFont(font);

        retranslateUi(DiaryCreate);

        QMetaObject::connectSlotsByName(DiaryCreate);
    } // setupUi

    void retranslateUi(QWidget *DiaryCreate)
    {
        DiaryCreate->setWindowTitle(QCoreApplication::translate("DiaryCreate", "Form", nullptr));
        label->setText(QCoreApplication::translate("DiaryCreate", "\346\240\207\351\242\230", nullptr));
        label_2->setText(QCoreApplication::translate("DiaryCreate", "\347\233\256\347\232\204\345\234\260", nullptr));
        label_3->setText(QCoreApplication::translate("DiaryCreate", "\345\206\205\345\256\271", nullptr));
        confirm->setText(QCoreApplication::translate("DiaryCreate", "\347\241\256\350\256\244", nullptr));
        cancel->setText(QCoreApplication::translate("DiaryCreate", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiaryCreate: public Ui_DiaryCreate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIARYCREATE_H
