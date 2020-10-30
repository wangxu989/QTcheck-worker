/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QFrame *line;
    QLabel *label_2;
    QFrame *line_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QFrame *line_3;
    QLabel *label_3;
    QFrame *line_4;
    QWidget *widget_3;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(736, 476);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/scan.png")));
        label->setScaledContents(true);

        verticalLayout->addWidget(label);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout->addWidget(widget);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 5);

        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral("font: 20pt \"Ubuntu\";"));

        horizontalLayout->addWidget(label_2);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 10);

        verticalLayout_2->addLayout(horizontalLayout);

        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));

        verticalLayout_2->addWidget(widget_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_3);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("font: 20pt \"Ubuntu\";"));

        horizontalLayout_2->addWidget(label_3);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_4);

        horizontalLayout_2->setStretch(0, 10);
        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 10);

        verticalLayout_2->addLayout(horizontalLayout_2);

        widget_3 = new QWidget(centralWidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));

        verticalLayout_2->addWidget(widget_3);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 5);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 5);

        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 3);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "\345\274\200\345\267\245\350\256\260\345\275\225", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "\345\256\214\345\267\245\350\256\260\345\275\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
