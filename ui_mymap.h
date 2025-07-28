/********************************************************************************
** Form generated from reading UI file 'mymap.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMAP_H
#define UI_MYMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myMap
{
public:
    QComboBox *currPos;
    QLabel *label;
    QLabel *label_2;
    QComboBox *destPos;
    QLabel *label_3;
    QPlainTextEdit *wayList;
    QPushButton *editRouteBtn;
    QLabel *label_5;
    QComboBox *category;
    QLabel *label_6;
    QComboBox *traffic;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *routePlanBtn;
    QLineEdit *facilityInput;
    QPushButton *facilitySearch;
    QLabel *label_9;
    QComboBox *facilitySort;
    QPlainTextEdit *facilityResult;
    QLabel *label_10;
    QPushButton *backBtn;
    QCheckBox *multiChk;
    QLabel *label_11;
    QLineEdit *foodInput;
    QPushButton *foodSearch;
    QLabel *label_12;
    QLabel *label_13;
    QComboBox *foodSort;
    QLabel *label_14;
    QComboBox *restaurant;
    QPlainTextEdit *foodResult;
    QLabel *label_15;
    QComboBox *foodKind;

    void setupUi(QWidget *myMap)
    {
        if (myMap->objectName().isEmpty())
            myMap->setObjectName("myMap");
        myMap->resize(1155, 800);
        currPos = new QComboBox(myMap);
        currPos->setObjectName("currPos");
        currPos->setGeometry(QRect(560, 30, 261, 22));
        label = new QLabel(myMap);
        label->setObjectName("label");
        label->setGeometry(QRect(560, 0, 71, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label_2 = new QLabel(myMap);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(560, 90, 71, 31));
        label_2->setFont(font);
        destPos = new QComboBox(myMap);
        destPos->setObjectName("destPos");
        destPos->setGeometry(QRect(560, 120, 261, 22));
        label_3 = new QLabel(myMap);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(560, 150, 71, 31));
        label_3->setFont(font);
        wayList = new QPlainTextEdit(myMap);
        wayList->setObjectName("wayList");
        wayList->setEnabled(true);
        wayList->setGeometry(QRect(560, 180, 261, 141));
        wayList->setReadOnly(true);
        editRouteBtn = new QPushButton(myMap);
        editRouteBtn->setObjectName("editRouteBtn");
        editRouteBtn->setGeometry(QRect(620, 340, 101, 31));
        QFont font1;
        font1.setPointSize(11);
        editRouteBtn->setFont(font1);
        label_5 = new QLabel(myMap);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(560, 390, 71, 31));
        label_5->setFont(font);
        category = new QComboBox(myMap);
        category->addItem(QString());
        category->addItem(QString());
        category->setObjectName("category");
        category->setGeometry(QRect(560, 420, 251, 22));
        label_6 = new QLabel(myMap);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(560, 450, 71, 31));
        label_6->setFont(font);
        traffic = new QComboBox(myMap);
        traffic->addItem(QString());
        traffic->setObjectName("traffic");
        traffic->setGeometry(QRect(560, 480, 251, 22));
        label_7 = new QLabel(myMap);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(560, 60, 81, 31));
        label_7->setFont(font);
        label_8 = new QLabel(myMap);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(870, 0, 81, 31));
        label_8->setFont(font);
        routePlanBtn = new QPushButton(myMap);
        routePlanBtn->setObjectName("routePlanBtn");
        routePlanBtn->setGeometry(QRect(620, 530, 101, 31));
        routePlanBtn->setFont(font1);
        facilityInput = new QLineEdit(myMap);
        facilityInput->setObjectName("facilityInput");
        facilityInput->setGeometry(QRect(870, 40, 191, 31));
        facilitySearch = new QPushButton(myMap);
        facilitySearch->setObjectName("facilitySearch");
        facilitySearch->setGeometry(QRect(1070, 40, 51, 31));
        facilitySearch->setFont(font1);
        label_9 = new QLabel(myMap);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(870, 90, 71, 31));
        label_9->setFont(font);
        facilitySort = new QComboBox(myMap);
        facilitySort->addItem(QString());
        facilitySort->addItem(QString());
        facilitySort->addItem(QString());
        facilitySort->addItem(QString());
        facilitySort->addItem(QString());
        facilitySort->addItem(QString());
        facilitySort->addItem(QString());
        facilitySort->addItem(QString());
        facilitySort->addItem(QString());
        facilitySort->addItem(QString());
        facilitySort->addItem(QString());
        facilitySort->setObjectName("facilitySort");
        facilitySort->setGeometry(QRect(870, 120, 251, 22));
        facilityResult = new QPlainTextEdit(myMap);
        facilityResult->setObjectName("facilityResult");
        facilityResult->setEnabled(true);
        facilityResult->setGeometry(QRect(870, 180, 261, 141));
        facilityResult->setReadOnly(true);
        label_10 = new QLabel(myMap);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(870, 150, 81, 31));
        label_10->setFont(font);
        backBtn = new QPushButton(myMap);
        backBtn->setObjectName("backBtn");
        backBtn->setGeometry(QRect(620, 620, 91, 31));
        backBtn->setFont(font);
        multiChk = new QCheckBox(myMap);
        multiChk->setObjectName("multiChk");
        multiChk->setGeometry(QRect(710, 150, 131, 31));
        multiChk->setFont(font1);
        label_11 = new QLabel(myMap);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(870, 340, 81, 31));
        label_11->setFont(font);
        foodInput = new QLineEdit(myMap);
        foodInput->setObjectName("foodInput");
        foodInput->setGeometry(QRect(870, 380, 191, 31));
        foodSearch = new QPushButton(myMap);
        foodSearch->setObjectName("foodSearch");
        foodSearch->setGeometry(QRect(1070, 380, 51, 31));
        foodSearch->setFont(font1);
        label_12 = new QLabel(myMap);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(870, 430, 71, 31));
        label_12->setFont(font);
        label_13 = new QLabel(myMap);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(870, 490, 71, 31));
        label_13->setFont(font);
        foodSort = new QComboBox(myMap);
        foodSort->addItem(QString());
        foodSort->addItem(QString());
        foodSort->addItem(QString());
        foodSort->addItem(QString());
        foodSort->setObjectName("foodSort");
        foodSort->setGeometry(QRect(870, 460, 251, 22));
        label_14 = new QLabel(myMap);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(870, 550, 71, 31));
        label_14->setFont(font);
        restaurant = new QComboBox(myMap);
        restaurant->setObjectName("restaurant");
        restaurant->setGeometry(QRect(870, 580, 251, 22));
        foodResult = new QPlainTextEdit(myMap);
        foodResult->setObjectName("foodResult");
        foodResult->setEnabled(true);
        foodResult->setGeometry(QRect(870, 640, 261, 141));
        foodResult->setReadOnly(true);
        label_15 = new QLabel(myMap);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(870, 610, 61, 31));
        label_15->setFont(font);
        foodKind = new QComboBox(myMap);
        foodKind->setObjectName("foodKind");
        foodKind->setGeometry(QRect(870, 520, 251, 22));

        retranslateUi(myMap);

        QMetaObject::connectSlotsByName(myMap);
    } // setupUi

    void retranslateUi(QWidget *myMap)
    {
        myMap->setWindowTitle(QCoreApplication::translate("myMap", "Form", nullptr));
        label->setText(QCoreApplication::translate("myMap", "\345\275\223\345\211\215\344\275\215\347\275\256\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("myMap", "\347\233\256\347\232\204\345\234\260\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("myMap", "\351\200\224\347\273\217\344\275\215\347\275\256\357\274\232", nullptr));
        wayList->setPlainText(QString());
        editRouteBtn->setText(QCoreApplication::translate("myMap", "\347\274\226\350\276\221\351\200\224\347\273\217\344\275\215\347\275\256", nullptr));
        label_5->setText(QCoreApplication::translate("myMap", "\345\257\274\350\210\252\347\255\226\347\225\245\357\274\232", nullptr));
        category->setItemText(0, QCoreApplication::translate("myMap", "\350\267\235\347\246\273\346\234\200\347\237\255", nullptr));
        category->setItemText(1, QCoreApplication::translate("myMap", "\346\227\266\351\227\264\346\234\200\347\237\255", nullptr));

        label_6->setText(QCoreApplication::translate("myMap", "\344\272\244\351\200\232\346\226\271\345\274\217\357\274\232", nullptr));
        traffic->setItemText(0, QCoreApplication::translate("myMap", "\346\255\245\350\241\214", nullptr));

        label_7->setText(QCoreApplication::translate("myMap", "\350\267\257\347\272\277\350\247\204\345\210\222", nullptr));
        label_8->setText(QCoreApplication::translate("myMap", "\345\234\272\346\211\200\346\237\245\350\257\242", nullptr));
        routePlanBtn->setText(QCoreApplication::translate("myMap", "\350\277\233\350\241\214\350\267\257\347\272\277\350\247\204\345\210\222", nullptr));
        facilitySearch->setText(QCoreApplication::translate("myMap", "\346\220\234\347\264\242", nullptr));
        label_9->setText(QCoreApplication::translate("myMap", "\345\234\272\346\211\200\347\261\273\345\210\253", nullptr));
        facilitySort->setItemText(0, QCoreApplication::translate("myMap", "\346\227\240", nullptr));
        facilitySort->setItemText(1, QCoreApplication::translate("myMap", "\350\277\220\345\212\250\350\256\276\346\226\275", nullptr));
        facilitySort->setItemText(2, QCoreApplication::translate("myMap", "\351\243\237\345\240\202", nullptr));
        facilitySort->setItemText(3, QCoreApplication::translate("myMap", "\345\215\253\347\224\237\351\227\264", nullptr));
        facilitySort->setItemText(4, QCoreApplication::translate("myMap", "\345\225\206\345\272\227", nullptr));
        facilitySort->setItemText(5, QCoreApplication::translate("myMap", "\345\233\276\344\271\246\351\246\206", nullptr));
        facilitySort->setItemText(6, QCoreApplication::translate("myMap", "\345\214\273\351\231\242", nullptr));
        facilitySort->setItemText(7, QCoreApplication::translate("myMap", "\345\201\234\350\275\246\345\234\272", nullptr));
        facilitySort->setItemText(8, QCoreApplication::translate("myMap", "\345\205\254\345\257\223", nullptr));
        facilitySort->setItemText(9, QCoreApplication::translate("myMap", "\351\202\256\345\261\200", nullptr));
        facilitySort->setItemText(10, QCoreApplication::translate("myMap", "\346\231\257\350\247\202", nullptr));

        facilityResult->setPlainText(QString());
        label_10->setText(QCoreApplication::translate("myMap", "\346\237\245\350\257\242\347\273\223\346\236\234", nullptr));
        backBtn->setText(QCoreApplication::translate("myMap", "\350\277\224\345\233\236", nullptr));
        multiChk->setText(QCoreApplication::translate("myMap", "\344\275\277\347\224\250\345\244\232\347\202\271\350\247\204\345\210\222", nullptr));
        label_11->setText(QCoreApplication::translate("myMap", "\347\276\216\351\243\237\346\216\250\350\215\220", nullptr));
        foodSearch->setText(QCoreApplication::translate("myMap", "\346\220\234\347\264\242", nullptr));
        label_12->setText(QCoreApplication::translate("myMap", "\346\216\222\345\272\217\346\226\271\345\274\217", nullptr));
        label_13->setText(QCoreApplication::translate("myMap", "\347\276\216\351\243\237\347\247\215\347\261\273", nullptr));
        foodSort->setItemText(0, QCoreApplication::translate("myMap", "\347\203\255\345\272\246\344\274\230\345\205\210", nullptr));
        foodSort->setItemText(1, QCoreApplication::translate("myMap", "\350\257\204\345\210\206\344\274\230\345\205\210", nullptr));
        foodSort->setItemText(2, QCoreApplication::translate("myMap", "\346\214\211\347\247\215\347\261\273", nullptr));
        foodSort->setItemText(3, QCoreApplication::translate("myMap", "\346\214\211\351\244\220\345\216\205", nullptr));

        label_14->setText(QCoreApplication::translate("myMap", "\351\244\220\351\246\206\345\220\215\347\247\260", nullptr));
        foodResult->setPlainText(QString());
        label_15->setText(QCoreApplication::translate("myMap", "\346\237\245\350\257\242\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class myMap: public Ui_myMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMAP_H
