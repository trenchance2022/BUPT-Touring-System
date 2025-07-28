/********************************************************************************
** Form generated from reading UI file 'destinationrecommend.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESTINATIONRECOMMEND_H
#define UI_DESTINATIONRECOMMEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_destinationRecommend
{
public:
    QListView *listView;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;

    void setupUi(QWidget *destinationRecommend)
    {
        if (destinationRecommend->objectName().isEmpty())
            destinationRecommend->setObjectName("destinationRecommend");
        destinationRecommend->resize(786, 472);
        listView = new QListView(destinationRecommend);
        listView->setObjectName("listView");
        listView->setGeometry(QRect(30, 30, 501, 421));
        pushButton = new QPushButton(destinationRecommend);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(700, 50, 51, 20));
        lineEdit = new QLineEdit(destinationRecommend);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(550, 50, 131, 20));
        label = new QLabel(destinationRecommend);
        label->setObjectName("label");
        label->setGeometry(QRect(550, 90, 71, 21));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        label->setFont(font);
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        comboBox = new QComboBox(destinationRecommend);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(550, 120, 171, 22));
        label_2 = new QLabel(destinationRecommend);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(550, 160, 71, 21));
        label_2->setFont(font);
        label_3 = new QLabel(destinationRecommend);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(550, 230, 61, 21));
        label_3->setFont(font);
        comboBox_2 = new QComboBox(destinationRecommend);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(550, 190, 171, 22));
        comboBox_3 = new QComboBox(destinationRecommend);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");
        comboBox_3->setGeometry(QRect(550, 260, 171, 22));

        retranslateUi(destinationRecommend);

        QMetaObject::connectSlotsByName(destinationRecommend);
    } // setupUi

    void retranslateUi(QWidget *destinationRecommend)
    {
        destinationRecommend->setWindowTitle(QCoreApplication::translate("destinationRecommend", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("destinationRecommend", "\346\220\234\347\264\242", nullptr));
        label->setText(QCoreApplication::translate("destinationRecommend", "\346\250\241\345\274\217\351\200\211\346\213\251", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("destinationRecommend", "\346\216\250\350\215\220", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("destinationRecommend", "\346\237\245\350\257\242", nullptr));

        label_2->setText(QCoreApplication::translate("destinationRecommend", "\346\216\222\345\272\217\346\226\271\345\274\217", nullptr));
        label_3->setText(QCoreApplication::translate("destinationRecommend", "\345\205\264\350\266\243\345\201\217\345\245\275", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("destinationRecommend", "\347\203\255\345\272\246", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("destinationRecommend", "\350\257\204\345\210\206", nullptr));

        comboBox_3->setItemText(0, QCoreApplication::translate("destinationRecommend", "\345\255\246\344\271\240", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("destinationRecommend", "\346\225\243\346\255\245", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("destinationRecommend", "\345\206\222\351\231\251", nullptr));

    } // retranslateUi

};

namespace Ui {
    class destinationRecommend: public Ui_destinationRecommend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESTINATIONRECOMMEND_H
