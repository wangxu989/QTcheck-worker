#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    draw_init();
    my_socket = QSharedPointer<socket>(new socket());
    connect(my_socket.data(),&socket::insert_plantab,this,&MainWindow::insert_plantab);
    connect(my_socket.data(),&socket::set_plantab_size,this,&MainWindow::set_plantab_size);
    connect(my_socket.data(),&socket::insert_plansteptab,this,&MainWindow::insert_plansteptab);
    connect(my_socket.data(),&socket::act_mode,this,&MainWindow::act_mode);
    connect(my_socket.data(),&socket::insert_producttab,this,&MainWindow::insert_producttab);
    connect(my_socket.data(),&socket::send_printString,this,&MainWindow::send_printString);
    connect(my_socket.data(),&socket::qrecode_show,this,&MainWindow::qrecode_show);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::draw_init() {
    //tablewidget1
    table1 = QSharedPointer<my_table>(new my_table("计划编号","计划数量","完成数量","计划结束日期","计划状态","生产工艺","物料信息","返工信息","创建人","创建时间"));
    table1->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    table1->horizontalHeader()->setSectionResizeMode(table1->columnCount() - 1,QHeaderView::ResizeToContents);
    ui->verticalLayout_7->addWidget(table1.data());


    //tablewidget2
    table2 = QSharedPointer<my_table>(new my_table("生产令号","工序号","工序名称","工序内容","车间","工程","设备","二序装备（编号）","工时","强制质检","标准数","数量比"));
    table2->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    ui->verticalLayout_8->addWidget(table2.data());

}
void MainWindow::insert_plantab(plantab *tab) {
    table1.data()->insert(*tab);
}
void MainWindow::insert_plansteptab(plansteptab *tab) {
    table2.data()->insert(*tab);
}
void MainWindow::set_plantab_size(int num,int size) {
    if (num == 1) {
        //table2.data()->clear();
        table1.data()->setRowCount(size);
        table1.data()->now_row = 0;
        for (int i = 0;i < table1.data()->rowCount();i++) {
            for (int j = 0;j < table1.data()->columnCount();j++) {
                table1.data()->setItem(i,j,new QTableWidgetItem());
                table1.data()->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
        }
        table1.data()->setCurrentItem(table1.data()->item(0,0));
    }
    else if (num == 2) {
        table2.data()->setRowCount(size);
        table2.data()->now_row = 0;

        for (int i = 0;i < table2.data()->rowCount();i++) {
            for (int j = 0;j < table2.data()->columnCount();j++) {
                table2.data()->setItem(i,j,new QTableWidgetItem());
                table2.data()->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
        }
        table2.data()->setCurrentItem(table2.data()->item(0,0));

    }
}
void MainWindow::act_mode(int act) {
    switch (act) {
    case 0:
        table1.data()->setCurrentItem(table1.data()->item(table1.data()->currentRow() + 1,0));
        break;
    case 1:
         table1.data()->setCurrentItem(table1.data()->item(table1.data()->currentRow() - 1,0));
        break;
    case 2:
        table2.data()->setCurrentItem(table2.data()->item(table2.data()->currentRow() + 1,0));
        break;
    case 3:
        table2.data()->setCurrentItem(table2.data()->item(table2.data()->currentRow() - 1,0));
        break;
    default:
        break;
    }
}
void MainWindow::insert_producttab(producttab *p) {
    ui->lineEdit->setText(p->productID);
    ui->lineEdit_2->setText(p->productState);
    ui->lineEdit_3->setText(p->productName);
    ui->lineEdit_4->setText(p->clientProductName);
    ui->lineEdit_9->setText(p->clientDrawingID);
    ui->lineEdit_10->setText(p->ourDrawingID);
    ui->lineEdit_11->setText(p->clientVersion);
}
void MainWindow::send_printString() {
    QString temp;
    int row = table2.data()->currentRow();
    temp += table2.data()->item(row,0)->text() + "," + table2.data()->item(row,1)->text() + "," + table2.data()->item(row,2)->text();
    qDebug()<<"send_PrintString  "<<temp;
    my_socket->send_message(20,temp);
}
void MainWindow::qrecode_show() {
    QPixmap p;
    qDebug()<<"Pixmap";
    p.load("./buffer/buf_img.png");
    ui->label_5->setFixedSize(80,80);
    ui->label_5->setPixmap(p);
}
