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
    connect(my_socket,&socket::print_String,this,&Program2::show_print_code);

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
void Program2::on_pushButton_2_clicked()//已完成
{
     data_server->read_plantab(key.data()->getVal(),"已完成");
}
void Program2::on_pushButton_3_clicked()
{
    data_server->read_plantab(key.data()->getVal(),"已终止");
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

}

void Program2::on_pushButton_4_clicked()//change
{
    status = !status;
}

void Program2::on_pushButton_6_clicked()//reduce
{
    if (status) {//plansteptab
        data_server->reducesteptab();
    }
    else {//plantab
        data_server->reducetab();
    }
}

void Program2::on_pushButton_7_clicked()//add
{
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
    qint32 temp_width=ui->label_2->width(); //二维码图片的大小
    qint32 temp_height=ui->label_2->height();
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
    ui->label_2->setPixmap(mainmap);
    ui->label_2->setVisible(true);
}
