/********************************************************************************
** Form generated from reading UI file 'finish_work.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINISH_WORK_H
#define UI_FINISH_WORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myledit.h"

QT_BEGIN_NAMESPACE

class Ui_finish_work
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    MyLEdit *lineEdit_5;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_13;
    MyLEdit *lineEdit_12;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    MyLEdit *lineEdit_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    MyLEdit *lineEdit_6;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    MyLEdit *lineEdit_7;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    MyLEdit *lineEdit_9;
    QPushButton *pushButton_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_9;
    MyLEdit *lineEdit_8;
    QPushButton *pushButton_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_11;
    MyLEdit *lineEdit_10;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_12;
    MyLEdit *lineEdit_11;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_14;
    MyLEdit *lineEdit_13;

    void setupUi(QWidget *finish_work)
    {
        if (finish_work->objectName().isEmpty())
            finish_work->setObjectName(QStringLiteral("finish_work"));
        finish_work->resize(1258, 561);
        verticalLayout_5 = new QVBoxLayout(finish_work);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(finish_work);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        lineEdit_5 = new MyLEdit(finish_work);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setEnabled(false);
        lineEdit_5->setMinimumSize(QSize(0, 40));
        lineEdit_5->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_3->addWidget(lineEdit_5);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 10);

        horizontalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_13 = new QLabel(finish_work);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_15->addWidget(label_13);

        lineEdit_12 = new MyLEdit(finish_work);
        lineEdit_12->setObjectName(QStringLiteral("lineEdit_12"));
        lineEdit_12->setMinimumSize(QSize(0, 40));

        horizontalLayout_15->addWidget(lineEdit_12);

        horizontalLayout_15->setStretch(0, 1);
        horizontalLayout_15->setStretch(1, 5);

        horizontalLayout_5->addLayout(horizontalLayout_15);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(finish_work);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        lineEdit_4 = new MyLEdit(finish_work);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setMinimumSize(QSize(0, 40));

        horizontalLayout_6->addWidget(lineEdit_4);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 7);

        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_7 = new QLabel(finish_work);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_4->addWidget(label_7);

        lineEdit_6 = new MyLEdit(finish_work);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setMinimumSize(QSize(0, 40));

        horizontalLayout_4->addWidget(lineEdit_6);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(finish_work);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(finish_work);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        horizontalLayout_7->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(finish_work);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_9->addWidget(label_8);

        lineEdit_7 = new MyLEdit(finish_work);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setMinimumSize(QSize(0, 40));

        horizontalLayout_9->addWidget(lineEdit_7);

        pushButton_3 = new QPushButton(finish_work);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(70, 40));

        horizontalLayout_9->addWidget(pushButton_3);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 5);
        horizontalLayout_9->setStretch(2, 1);

        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_10 = new QLabel(finish_work);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_10->addWidget(label_10);

        lineEdit_9 = new MyLEdit(finish_work);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setMinimumSize(QSize(0, 40));

        horizontalLayout_10->addWidget(lineEdit_9);

        pushButton_4 = new QPushButton(finish_work);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(70, 40));

        horizontalLayout_10->addWidget(pushButton_4);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 5);
        horizontalLayout_10->setStretch(2, 1);

        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_9 = new QLabel(finish_work);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_2->addWidget(label_9);

        lineEdit_8 = new MyLEdit(finish_work);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(lineEdit_8);

        pushButton_5 = new QPushButton(finish_work);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(70, 40));

        horizontalLayout_2->addWidget(pushButton_5);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 5);
        horizontalLayout_2->setStretch(2, 1);

        verticalLayout_4->addLayout(horizontalLayout_2);


        horizontalLayout_7->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_11 = new QLabel(finish_work);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_12->addWidget(label_11);

        lineEdit_10 = new MyLEdit(finish_work);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        lineEdit_10->setMinimumSize(QSize(0, 40));

        horizontalLayout_12->addWidget(lineEdit_10);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 5);

        verticalLayout_3->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_12 = new QLabel(finish_work);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_13->addWidget(label_12);

        lineEdit_11 = new MyLEdit(finish_work);
        lineEdit_11->setObjectName(QStringLiteral("lineEdit_11"));
        lineEdit_11->setMinimumSize(QSize(0, 40));

        horizontalLayout_13->addWidget(lineEdit_11);

        horizontalLayout_13->setStretch(0, 1);
        horizontalLayout_13->setStretch(1, 5);

        verticalLayout_3->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        label_14 = new QLabel(finish_work);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_14->addWidget(label_14);

        lineEdit_13 = new MyLEdit(finish_work);
        lineEdit_13->setObjectName(QStringLiteral("lineEdit_13"));
        lineEdit_13->setMinimumSize(QSize(0, 40));

        horizontalLayout_14->addWidget(lineEdit_13);

        horizontalLayout_14->setStretch(0, 1);
        horizontalLayout_14->setStretch(1, 5);

        verticalLayout_3->addLayout(horizontalLayout_14);


        horizontalLayout_7->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(horizontalLayout_7);

        verticalLayout_5->setStretch(0, 1);
        verticalLayout_5->setStretch(1, 10);

        retranslateUi(finish_work);

        QMetaObject::connectSlotsByName(finish_work);
    } // setupUi

    void retranslateUi(QWidget *finish_work)
    {
        finish_work->setWindowTitle(QApplication::translate("finish_work", "Form", 0));
        label_5->setText(QApplication::translate("finish_work", "\345\275\223\345\211\215\346\227\266\351\227\264", 0));
        label_13->setText(QApplication::translate("finish_work", "\345\244\207\346\263\250\344\277\241\346\201\257", 0));
        label_6->setText(QApplication::translate("finish_work", "\346\243\200\351\252\214\346\212\245\345\221\212", 0));
        label_7->setText(QApplication::translate("finish_work", "\346\210\220\345\223\201\346\225\260\351\207\217", 0));
        pushButton->setText(QApplication::translate("finish_work", "\345\211\251\344\275\231\346\225\260", 0));
        pushButton_2->setText(QApplication::translate("finish_work", "\346\240\207\347\256\261\346\225\260", 0));
        label_8->setText(QApplication::translate("finish_work", "\345\276\205\345\244\204\347\220\206\346\225\260\351\207\217", 0));
        pushButton_3->setText(QApplication::translate("finish_work", "\347\274\226\350\276\221", 0));
        label_10->setText(QApplication::translate("finish_work", "\350\243\205\346\250\241\346\270\205\345\215\225    ", 0));
        pushButton_4->setText(QApplication::translate("finish_work", "\346\270\205\351\231\244", 0));
        label_9->setText(QApplication::translate("finish_work", "\344\272\247\345\223\201\346\211\271\346\254\241    ", 0));
        pushButton_5->setText(QApplication::translate("finish_work", "\345\275\225\345\205\245", 0));
        label_11->setText(QApplication::translate("finish_work", "\345\267\245\344\275\234\346\227\266\351\225\277", 0));
        lineEdit_10->setPlaceholderText(QApplication::translate("finish_work", "\345\210\206\351\222\237", 0));
        label_12->setText(QApplication::translate("finish_work", "\347\203\255\345\244\204\347\220\206\345\217\267", 0));
        label_14->setText(QApplication::translate("finish_work", "\350\241\250\351\235\242\345\244\204\347\220\206", 0));
    } // retranslateUi

};

namespace Ui {
    class finish_work: public Ui_finish_work {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINISH_WORK_H
