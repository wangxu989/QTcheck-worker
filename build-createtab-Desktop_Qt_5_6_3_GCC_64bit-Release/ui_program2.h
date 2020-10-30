/********************************************************************************
** Form generated from reading UI file 'program2.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRAM2_H
#define UI_PROGRAM2_H

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

QT_BEGIN_NAMESPACE

class Ui_Program2
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;

    void setupUi(QWidget *Program2)
    {
        if (Program2->objectName().isEmpty())
            Program2->setObjectName(QStringLiteral("Program2"));
        Program2->resize(675, 523);
        horizontalLayout = new QHBoxLayout(Program2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(Program2);
        widget->setObjectName(QStringLiteral("widget"));

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(Program2);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(label);

        pushButton = new QPushButton(Program2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(0, 60));

        verticalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(Program2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 60));

        verticalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(Program2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(0, 60));

        verticalLayout->addWidget(pushButton_3);

        pushButton_6 = new QPushButton(Program2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(0, 60));
        pushButton_6->setStyleSheet(QStringLiteral("/*QWidget{border-image: url(:/new/prefix1/img/change2.png);}"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/img/change2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_6->setIcon(icon);
        pushButton_6->setIconSize(QSize(80, 80));

        verticalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(Program2);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(0, 60));
        pushButton_7->setStyleSheet(QStringLiteral("/*QWidget{border-image: url(:/new/prefix1/img/change1.png);}"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/img/change1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon1);
        pushButton_7->setIconSize(QSize(80, 80));
        pushButton_7->setAutoDefault(false);

        verticalLayout->addWidget(pushButton_7);

        pushButton_4 = new QPushButton(Program2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(0, 60));

        verticalLayout->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(Program2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setMinimumSize(QSize(0, 60));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/img/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_5->setIcon(icon2);
        pushButton_5->setIconSize(QSize(30, 30));

        verticalLayout->addWidget(pushButton_5);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 2);
        verticalLayout->setStretch(3, 2);
        verticalLayout->setStretch(4, 2);
        verticalLayout->setStretch(5, 2);
        verticalLayout->setStretch(6, 2);

        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 10);

        retranslateUi(Program2);

        pushButton_7->setDefault(false);


        QMetaObject::connectSlotsByName(Program2);
    } // setupUi

    void retranslateUi(QWidget *Program2)
    {
        Program2->setWindowTitle(QApplication::translate("Program2", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("Program2", "\347\224\237\344\272\247\350\256\241\345\210\222\347\255\233\351\200\211:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Program2", "\346\211\247\350\241\214\344\270\255", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Program2", "\345\267\262\345\256\214\346\210\220", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Program2", "\345\267\262\347\273\210\346\255\242", Q_NULLPTR));
        pushButton_6->setText(QString());
        pushButton_7->setText(QString());
        pushButton_4->setText(QApplication::translate("Program2", "\345\210\207\346\215\242", Q_NULLPTR));
        pushButton_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Program2: public Ui_Program2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRAM2_H
