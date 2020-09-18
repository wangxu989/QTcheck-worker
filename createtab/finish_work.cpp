#include "finish_work.h"
#include "ui_finish_work.h"
#include<QDebug>
Program3::finish_work::finish_work(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::finish_work)
{
    ui->setupUi(this);
    layout = QSharedPointer<QHBoxLayout>(new QHBoxLayout());
    layout->addWidget(this);
    connect(ui->lineEdit_10,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit_11,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit_12,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit_13,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
}

Program3::finish_work::~finish_work()
{
    delete ui;
}
QString Program3::finish_work::text() {
    if (now == nullptr) {return QString("");}
    qDebug()<<now->text();
    return now->text();
}
bool Program3::finish_work::setText(const QString&s) {
    if (now == nullptr) {return false;}
    qDebug()<<"Mylineedit";
    now->setText(s);
    return true;
}
void Program3::finish_work::label_change(MyLEdit *m) {
    now = m;
}
