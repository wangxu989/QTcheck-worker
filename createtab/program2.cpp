#include "program2.h"
#include "ui_program2.h"
#include<QHBoxLayout>
#include<database.h>
extern database_server *data_server;
extern database_local *data_local;
extern socket *my_socket;
Program2::Program2(const QString& name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Program2)
{
    add_p(name,this);
    key_lay = QSharedPointer<QHBoxLayout>(new QHBoxLayout());
    key = QSharedPointer<keyboard_widget>(new keyboard_widget("打印"));
    key_lay->addWidget(key.data());
    connect(key->figure,&QTableWidget::cellClicked,this,&Program2::in_keyboard);
    ui->setupUi(this);
    ui->widget->setLayout(key_lay.data());
    connect(ui->pushButton,&QPushButton::clicked,this,&Program2::exec_button);

}

Program2::~Program2()
{
    delete ui;
}

void Program2::on_pushButton_5_clicked()
{
    emit change_widget(0);
}
void Program2::read_data() {

}
void Program2::exec_button() {
    qDebug()<<"执行中"<<key.data()->getVal();
    data_server->read_plantab(key.data()->getVal(),"执行中");
}
void Program2::in_keyboard(const int &row,const int &column) {
    if (row == 0 && column == 3) {//delete
        key->removeText();
    }
    else if (row == 2 && column == 3) {//enter
        //打印
    }
    else {
        key->addText(row,column);
    }

}

void Program2::on_pushButton_4_clicked()//change
{
    status = !status;
}

void Program2::on_pushButton_6_clicked()//reduce
{
    if (status) {//plansteptab
        int act = 3;
        my_socket->sendmessage(49,(void *)&act);
    }
    else {//plantab
        data_server->reducetab();
    }
}

void Program2::on_pushButton_7_clicked()//add
{
    if (status) {//2
        int act = 2;
        my_socket->sendmessage(49,(void *)&act);
    }
    else {
        data_server->add_tab();
    }
}

