#include "program2.h"
#include "ui_program2.h"
#include<QHBoxLayout>
#include<database.h>
extern database_server *data_server;
extern database_local *data_local;
extern socket *my_socket;
QMap<int,button_ctl*> button_ctl::rec;
int button_ctl::size = 0;
int button_ctl::now_num = -1;
Program2::Program2(const QString& name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Program2),thisname(name)
{
    ui->setupUi(this);
    add_p(thisname,this);
}
bool Program2::start_P() {
    if (my_socket->status()) {
        key_lay = QSharedPointer<QHBoxLayout>(new QHBoxLayout());
        key = QSharedPointer<keyboard_widget>(new keyboard_widget("打印"));
        key_lay->addWidget(key.data());
        connect(key->figure,&QTableWidget::cellClicked,this,&Program2::in_keyboard);

        ui->widget->setLayout(key_lay.data());
        connect(ui->pushButton,&QPushButton::clicked,this,&Program2::exec_button);
        connect(my_socket,&socket::print_String,this,&Program2::show_print_code);
        label_2 =  QSharedPointer<QLabel>(new QLabel());

        exe.attach(ui->pushButton);
        finished.attach(ui->pushButton_2);
        terminated.attach(ui->pushButton_3);
        my_progress.start("./plugin/program2");
        return true;
    }
    return false;
}
void Program2::finish_P() {
    my_progress.close();
    remove_P(thisname);
    disconnect(key->figure,&QTableWidget::cellClicked,this,&Program2::in_keyboard);
    disconnect(ui->pushButton,&QPushButton::clicked,this,&Program2::exec_button);
    disconnect(my_socket,&socket::print_String,this,&Program2::show_print_code);
    delete this;
}

Program2::~Program2()
{
    delete ui;
}

void Program2::on_pushButton_5_clicked()
{
    emit change_widget(10);
}
void Program2::read_data() {

}
void Program2::exec_button() {
    qDebug()<<"执行中"<<key.data()->getVal();
    if (!key.data()->getVal().isEmpty() ) {
        if (data_server->read_plantab(key.data()->getVal(),"执行中")) {
            button_ctl::notify(exe.num);
            key->flash();
            now_click = 1;
        }
        else {
            now_click = 0;
        }

    }
}
void Program2::on_pushButton_2_clicked()//已完成
{
    if (!key.data()->getVal().isEmpty()) {
        if (data_server->read_plantab(key.data()->getVal(),"已完成")) {
            button_ctl::notify(finished.num);
            key->flash();
            now_click = 2;
        }
        else {
            now_click = 0;
        }
    }
}
void Program2::on_pushButton_3_clicked()
{
    if (!key.data()->getVal().isEmpty()) {
        if (data_server->read_plantab(key.data()->getVal(),"已终止")) {
            button_ctl::notify(terminated.num);
            key->flash();
            now_click = 3;
        }
        else {
            now_click = 0;
        }
    }
}

void Program2::in_keyboard(const int &row,const int &column) {
    if (row == 0 && column == 3) {//delete
        key->removeText();
    }
    else if (row == 2 && column == 3) {//enter
        //打印
        qDebug()<<"打印";
        my_socket->sendmessage(47);

    }
    else {
        key->addText(row,column);
    }
    if (key->getVal() != key->lastquery()) {//软件盘发生改变了
        button_ctl::notify();
    }
    else {
        button_ctl::recover();
    }

}

void Program2::on_pushButton_4_clicked()//change
{
    status = !status;
}

void Program2::on_pushButton_6_clicked()//reduce
{
    if (now_click == 0) {return;}
    if (status) {//plansteptab
        data_server->reducesteptab();
    }
    else {//plantab
        data_server->reducetab();
    }
}

void Program2::on_pushButton_7_clicked()//add
{
    if (now_click == 0) {return;}
    if (status) {//2
        data_server->add_steptab();
    }
    else {
        data_server->add_tab();
    }
}
void Program2::show_print_code(QString &s) {
    qDebug()<<"printString "<<s;
    QRcode *qrcode;
    qrcode = QRcode_encodeString(s.toStdString().c_str(), 2, QR_ECLEVEL_Q, QR_MODE_8, 1);
    qint32 temp_width=label_2->width(); //二维码图片的大小
    qint32 temp_height=label_2->height();
    qint32 qrcode_width = qrcode->width > 0 ? qrcode->width : 1;
    double scale_x = (double)temp_width / (double)qrcode_width; //二维码图片的缩放比例
    double scale_y =(double) temp_height /(double) qrcode_width;
    QImage mainimg=QImage(temp_width,temp_height,QImage::Format_ARGB32);
    QPainter painter(&mainimg);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, temp_width, temp_height);
    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    for( qint32 y = 0; y < qrcode_width; y ++)
    {
        for(qint32 x = 0; x < qrcode_width; x++)
        {
            unsigned char b = qrcode->data[y * qrcode_width + x];
            if(b & 0x01)
            {
                QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }
    QPixmap mainmap=QPixmap::fromImage(mainimg);
    label_2->setPixmap(mainmap);
    label_2->setVisible(true);
}
