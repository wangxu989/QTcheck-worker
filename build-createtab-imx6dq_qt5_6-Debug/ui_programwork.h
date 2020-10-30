/********************************************************************************
** Form generated from reading UI file 'programwork.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRAMWORK_H
#define UI_PROGRAMWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProgramWork
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ProgramWork)
    {
        if (ProgramWork->objectName().isEmpty())
            ProgramWork->setObjectName(QStringLiteral("ProgramWork"));
        ProgramWork->resize(400, 300);
        horizontalLayout_2 = new QHBoxLayout(ProgramWork);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(ProgramWork);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("font: 40pt \"Ubuntu\";"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(ProgramWork);

        QMetaObject::connectSlotsByName(ProgramWork);
    } // setupUi

    void retranslateUi(QWidget *ProgramWork)
    {
        ProgramWork->setWindowTitle(QApplication::translate("ProgramWork", "Form", 0));
        label->setText(QApplication::translate("ProgramWork", "\350\257\267\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class ProgramWork: public Ui_ProgramWork {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRAMWORK_H
