/********************************************************************************
** Form generated from reading UI file 'start_finish_work.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_FINISH_WORK_H
#define UI_START_FINISH_WORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_start_finish_work
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_4;

    void setupUi(QWidget *start_finish_work)
    {
        if (start_finish_work->objectName().isEmpty())
            start_finish_work->setObjectName(QStringLiteral("start_finish_work"));
        start_finish_work->resize(728, 516);
        horizontalLayout = new QHBoxLayout(start_finish_work);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(start_finish_work);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 60));

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(start_finish_work);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setEnabled(true);
        pushButton->setMinimumSize(QSize(0, 70));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(start_finish_work);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 70));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(start_finish_work);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(0, 70));
        pushButton_3->setIconSize(QSize(60, 100));

        verticalLayout->addWidget(pushButton_3);

        pushButton_5 = new QPushButton(start_finish_work);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(0, 70));

        verticalLayout->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(start_finish_work);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(0, 70));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/img/change2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon);
        pushButton_6->setIconSize(QSize(60, 30));

        verticalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(start_finish_work);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(0, 70));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/img/change1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon1);
        pushButton_7->setIconSize(QSize(60, 30));

        verticalLayout->addWidget(pushButton_7);

        pushButton_4 = new QPushButton(start_finish_work);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(0, 70));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/img/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon2);
        pushButton_4->setIconSize(QSize(30, 30));

        verticalLayout->addWidget(pushButton_4);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 4);
        horizontalLayout->setStretch(1, 1);

        retranslateUi(start_finish_work);

        QMetaObject::connectSlotsByName(start_finish_work);
    } // setupUi

    void retranslateUi(QWidget *start_finish_work)
    {
        start_finish_work->setWindowTitle(QApplication::translate("start_finish_work", "Form", Q_NULLPTR));
        pushButton->setText(QApplication::translate("start_finish_work", "\345\274\200\345\267\245", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("start_finish_work", "\345\210\207\346\215\242", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("start_finish_work", "\344\272\214\347\273\264\347\240\201", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("start_finish_work", "\345\210\240\351\231\244", Q_NULLPTR));
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class start_finish_work: public Ui_start_finish_work {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_FINISH_WORK_H
