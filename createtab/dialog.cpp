#include "dialog.h"
#include "ui_dialog.h"
#include<QPixmap>
#include<QImage>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setStyleSheet("QWidget#Dialog{border-image: url(:/new/prefix1/img/bj.jpg);}");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    emit sendData();
}
