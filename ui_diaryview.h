/********************************************************************************
** Form generated from reading UI file 'diaryview.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIARYVIEW_H
#define UI_DIARYVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiaryView
{
public:
    QLabel *label_3;
    QPlainTextEdit *content;
    QLabel *label;
    QLineEdit *dest;
    QLineEdit *title;
    QLabel *label_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radio5;
    QRadioButton *radio3;
    QRadioButton *radio2;
    QRadioButton *radio4;
    QRadioButton *radio1;
    QLabel *label_4;
    QPushButton *confirmBnt;

    void setupUi(QWidget *DiaryView)
    {
        if (DiaryView->objectName().isEmpty())
            DiaryView->setObjectName("DiaryView");
        DiaryView->resize(665, 488);
        label_3 = new QLabel(DiaryView);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(30, 120, 51, 31));
        QFont font;
        font.setPointSize(12);
        label_3->setFont(font);
        content = new QPlainTextEdit(DiaryView);
        content->setObjectName("content");
        content->setGeometry(QRect(90, 130, 521, 221));
        content->setReadOnly(true);
        label = new QLabel(DiaryView);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 30, 51, 21));
        label->setFont(font);
        dest = new QLineEdit(DiaryView);
        dest->setObjectName("dest");
        dest->setGeometry(QRect(90, 80, 521, 21));
        dest->setReadOnly(true);
        title = new QLineEdit(DiaryView);
        title->setObjectName("title");
        title->setEnabled(true);
        title->setGeometry(QRect(90, 30, 521, 21));
        title->setReadOnly(true);
        label_2 = new QLabel(DiaryView);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 80, 51, 21));
        label_2->setFont(font);
        horizontalLayoutWidget = new QWidget(DiaryView);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(90, 370, 411, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        radio5 = new QRadioButton(horizontalLayoutWidget);
        radio5->setObjectName("radio5");
        radio5->setEnabled(true);
        radio5->setChecked(true);

        horizontalLayout->addWidget(radio5);

        radio3 = new QRadioButton(horizontalLayoutWidget);
        radio3->setObjectName("radio3");
        radio3->setChecked(false);

        horizontalLayout->addWidget(radio3);

        radio2 = new QRadioButton(horizontalLayoutWidget);
        radio2->setObjectName("radio2");

        horizontalLayout->addWidget(radio2);

        radio4 = new QRadioButton(horizontalLayoutWidget);
        radio4->setObjectName("radio4");

        horizontalLayout->addWidget(radio4);

        radio1 = new QRadioButton(horizontalLayoutWidget);
        radio1->setObjectName("radio1");

        horizontalLayout->addWidget(radio1);

        label_4 = new QLabel(DiaryView);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(30, 390, 51, 31));
        label_4->setFont(font);
        confirmBnt = new QPushButton(DiaryView);
        confirmBnt->setObjectName("confirmBnt");
        confirmBnt->setGeometry(QRect(530, 400, 91, 31));
        confirmBnt->setFont(font);

        retranslateUi(DiaryView);

        QMetaObject::connectSlotsByName(DiaryView);
    } // setupUi

    void retranslateUi(QWidget *DiaryView)
    {
        DiaryView->setWindowTitle(QCoreApplication::translate("DiaryView", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("DiaryView", "\345\206\205\345\256\271", nullptr));
        label->setText(QCoreApplication::translate("DiaryView", "\346\240\207\351\242\230", nullptr));
        label_2->setText(QCoreApplication::translate("DiaryView", "\347\233\256\347\232\204\345\234\260", nullptr));
        radio5->setText(QCoreApplication::translate("DiaryView", "5", nullptr));
        radio3->setText(QCoreApplication::translate("DiaryView", "4", nullptr));
        radio2->setText(QCoreApplication::translate("DiaryView", "3", nullptr));
        radio4->setText(QCoreApplication::translate("DiaryView", "2", nullptr));
        radio1->setText(QCoreApplication::translate("DiaryView", "1", nullptr));
        label_4->setText(QCoreApplication::translate("DiaryView", "\350\257\204\345\210\206", nullptr));
        confirmBnt->setText(QCoreApplication::translate("DiaryView", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DiaryView: public Ui_DiaryView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIARYVIEW_H
