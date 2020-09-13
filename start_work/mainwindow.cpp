#include "mainwindow.h"
#include "ui_mainwindow.h"

extern QQueue<start_work>q_startwork;

extern QQueue<finish_work>q_finishwork;
QVector<base_table*> base_table::rec = QVector<base_table*>();
QSharedPointer<socket> my_socket;
int base_table::num = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_socket = QSharedPointer<socket>(new socket());

    connect(my_socket.data(),&socket::insert_data,this,&MainWindow::insert_data);
    connect(my_socket.data(),&socket::set_tablesize,this,&MainWindow::set_table_size);
    connect(my_socket.data(),&socket::act_mode,this,&MainWindow::act_mode);
    connect(my_port1.port1,SIGNAL(readyRead()),this,SLOT(my_read()));//扫码枪串口
    connect(my_socket.data(),&socket::change_status,this,&MainWindow::change_status);
    connect(my_socket.data(),&socket::send_rec_code,this,&MainWindow::insert_table2);
    connect(my_socket.data(),&socket::confirm,this,&MainWindow::confirm);
    connect(my_socket.data(),&socket::change_table,this,&MainWindow::change_table);
    connect(my_socket.data(),&socket::delete_mes,this,&MainWindow::delete_msg);
#ifdef MY_P
    QPushButton *send_work = new QPushButton("设备");
    QPushButton *send_worker = new QPushButton("员工");
    QPushButton *send_inst = new QPushButton("指令");
    QPushButton *sendProcessinf = new QPushButton("记录");
    connect(send_work,SIGNAL(clicked()),this,SLOT(my_send2()));
    connect(send_worker,SIGNAL(clicked()),this,SLOT(my_send1()));
    connect(send_inst,SIGNAL(clicked()),this,SLOT(my_send3()));
    connect(sendProcessinf,SIGNAL(clicked()),this,SLOT(my_send4()));
    QVBoxLayout *V_button = new QVBoxLayout();
    V_button->addWidget(send_work);
    V_button->addWidget(send_worker);
    V_button->addWidget(send_inst);
    V_button->addWidget(sendProcessinf);
    ui->horizontalLayout_3->addLayout(V_button);
#endif
    //table_work = new my_tablewidget(4,2,"工作信息");

    table_worker = new my_tablewidget(2,2,"员工信息");
    table_worker->item(1,0)->setText("工号");



    table_product = new my_tablewidget(3,2,"设备信息");
    table_product->item(1,0)->setText("设备");
    table_product->item(2,0)->setText("装模清单");


    table_process = new my_tablewidget(5,2,"工序");
    table_process->item(1,0)->setText("生产令号");
    table_process->item(2,0)->setText("物料信息");
    table_process->item(3,0)->setText("强制检验");
    table_process->item(4,0)->setText("标箱数量");


    table_layout = new QVBoxLayout(ui->widget);
    table_layout->addWidget(table_worker);
    //table_layout->addWidget(table_work);
    table_layout->addWidget(table_product);
    table_layout->addWidget(table_process);
    tablestart = QSharedPointer<my_table>(new my_table("开工记录",ui->label_2,ui->widget_2,"生产令号","完成时间","物料信息","员工号","成品数","产品批次","开工时间","设备","剩余数"));
    tablefinish = QSharedPointer<my_table>(new my_table("完工记录",ui->label_3,ui->widget_3,"生产令号","完成时间","物料信息","成品数","待处理","产品批次","打印","剩余数"));
    tablestart->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    tablestart->horizontalHeader()->setSectionResizeMode(6,QHeaderView::ResizeToContents);
    tablefinish->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    tablefinish->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::my_read() {
    my_port1.code_scan = my_port1.port1->readAll();
    if (my_port1.code_scan.contains("\r")) {
        my_port1.code_scan = my_port1.code_scan.remove(my_port1.code_scan.size() - 1,1);
        my_port1.temp_scan+=my_port1.code_scan;
        //string_scan.push_back(temp_scan);
        if (my_port1.temp_scan.contains("YG")) {
            workInfo.worker_id = my_port1.temp_scan;
            my_socket->send_message(2,my_port1.temp_scan);
            my_socket->check_flag[0] = 1;
            table_worker->item(1,1)->setText(my_port1.temp_scan.split(",")[1]);
        }
        else if (my_port1.temp_scan.contains("ZL")){
            workInfo.instruction_id = my_port1.temp_scan;
            table_process->item(1,1)->setText(workInfo.instruction_id.split(",")[1]);
            my_socket->send_message(50,my_port1.temp_scan);
            my_socket->check_flag[1] = 1;
        }
        else if (my_port1.temp_scan.contains("SB")) {
            workInfo.product_id = my_port1.temp_scan;
            my_socket->send_message(4,my_port1.temp_scan);
            my_socket->check_flag[2] = 1;
            table_product->item(1,1)->setText(my_port1.temp_scan.split(",")[1]);
        }

        else {//生产记录码
            if (workInfo.instruction_id.size() == 0) {
                ui->label->setText("请先扫生产令码");
                return;
            }

            qDebug()<<my_port1.temp_scan.mid(my_port1.temp_scan.size() - 2,2);
            qDebug()<<workInfo.instruction_id.split(",")[1].mid(workInfo.instruction_id.split(",")[1].size() - 2);
            if (workInfo.instruction_id.split(",")[1].mid(workInfo.instruction_id.split(",")[1].size() - 2,2).toInt() != my_port1.temp_scan.split(",")[0].mid(my_port1.temp_scan.split(",")[0].size() - 2,2).toInt() + 1) {
                ui->label->setText("工序错误");
                return;
            }
            if (rec_set.find(my_port1.temp_scan.split(" ")[0]) != rec_set.end()) {
                return;
            }
            else {
                rec_set.insert(my_port1.temp_scan.split(" ")[0]);
            }
            my_socket->send_message(51,my_port1.temp_scan);
            my_socket->check_flag[3] = 1;
        }
        qDebug()<<my_port1.temp_scan;
        my_port1.temp_scan.resize(0);
    }
    else {
        my_port1.temp_scan += my_port1.code_scan;
    }
}
void MainWindow::insert_data(int flag) {
    if (flag == 1) {

    }
    else if (flag == 2) {//填工序信息
        //生产
        qDebug()<<my_socket->Proinf.cMustQC<<" cMustqc";
        table_process->item(3,1)->setText(my_socket->Proinf.cMustQC);
        table_process->item(4,1)->setText(my_socket->Proinf.cStdCount);
        table_process->item(2,1)->setText(my_socket->Proinf.ElseInf);

    }
    else if (flag == 3) {

    }
    else if (flag == 4) {
        ui->label->setText("非法用户,请重新扫描");
    }
    else if (flag == 5) {
        ui->label->setText("无此工作,请重新扫描");
    }
    else if (flag == 6){
        ui->label->setText("无此产品,请重新扫描");
    }
    else if (flag == 7) {//开工
        tablestart->insert(q_startwork.front());
        q_startwork.pop_front();
    }
    else if (flag == 8) {//完工
        tablefinish->insert(q_finishwork.front());
        q_finishwork.pop_front();
    }
}
void MainWindow::set_table_size(int num,int size) {
    if (num == 1) {
        //table2.data()->clear();
        tablestart.data()->setRowCount(size);
        tablestart.data()->now_row = 0;
        for (int i = 0;i < tablestart.data()->rowCount();i++) {
            for (int j = 0;j < tablestart.data()->columnCount();j++) {
                tablestart.data()->setItem(i,j,new QTableWidgetItem());
                //tablestart.data()->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
        }
        tablestart.data()->setCurrentItem(tablestart.data()->item(0,0));
        ui->label_2->setText("开工记录[ " + QString::number(tablestart->rowCount()) + " ]");
    }
    else if (num == 2) {
        tablefinish.data()->setRowCount(size);
        tablefinish.data()->now_row = 0;

        for (int i = 0;i < tablefinish.data()->rowCount();i++) {
            for (int j = 0;j < tablefinish.data()->columnCount();j++) {
                tablefinish.data()->setItem(i,j,new QTableWidgetItem());
                //tablefinish.data()->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
        }
        tablefinish.data()->setCurrentItem(tablefinish.data()->item(0,0));
        ui->label_3->setText("完工记录[ " + QString::number(tablefinish->rowCount()) + " ]");
    }
}
void MainWindow::act_mode(int act) {
    if (table2.data() != nullptr && table2.data()->isVisible()) {
        if (act%2) {
            if (table2.data()->currentRow() - 1 >= 0) {
                table2.data()->setCurrentItem(table2.data()->item(table2.data()->currentRow() - 1,0));
            }
        }
        else {
            if (table2.data()->currentRow() + 1 < table2.data()->rowCount()) {
                table2.data()->setCurrentItem(table2.data()->item(table2.data()->currentRow() + 1,0));
            }
        }
        return;
    }
    switch (act) {
    case 0:
        if (tablestart.data()->currentRow() + 1 < tablestart.data()->rowCount()) {
            tablestart.data()->setCurrentItem(tablestart.data()->item(tablestart.data()->currentRow() + 1,0));
        }
        break;
    case 1:
        if (tablestart.data()->currentRow() - 1 >= 0) {
            tablestart.data()->setCurrentItem(tablestart.data()->item(tablestart.data()->currentRow() - 1,0));
        }
        break;
    case 2:
        if (tablefinish.data()->currentRow() + 1 < tablefinish.data()->rowCount()) {
            tablefinish.data()->setCurrentItem(tablefinish.data()->item(tablefinish.data()->currentRow() + 1,0));
        }
        break;
    case 3:
        if (tablefinish.data()->currentRow() - 1 >= 0) {
            tablefinish.data()->setCurrentItem(tablefinish.data()->item(tablefinish.data()->currentRow() - 1,0));
        }
        break;
    default:
        break;
    }
}
void MainWindow::change_status() {//进入开工模块
    table2 = QSharedPointer<my_table>(new my_table("开工模式",nullptr,nullptr,"生产令号","完成时间","物料信息","员工号","成品数","产品批次","剩余数"));
    ui->verticalLayout_2->removeWidget(ui->widget_2);
    ui->verticalLayout_2->removeWidget(ui->widget_3);
    ui->verticalLayout_2->removeItem(ui->horizontalLayout);
    ui->verticalLayout_2->removeItem(ui->horizontalLayout);
    ui->verticalLayout_2->removeItem(ui->horizontalLayout_2);
    ui->verticalLayout_2->addWidget(table2.data());
}

void MainWindow::my_send1() {
    QString temp = "YG,55045";//"YG,02294";
    workInfo.worker_id = temp;
    my_socket->send_message(2,temp);
    my_socket->check_flag[0] = 1;
    table_worker->item(1,1)->setText(temp.split(",")[1]);
}

void MainWindow::my_send2() {
    QString temp = "SB,001073";
    workInfo.product_id = temp;
    my_socket->send_message(4,temp);
    my_socket->check_flag[2] = 1;
    table_product->item(1,1)->setText(temp.split(",")[1]);
}

void MainWindow::my_send3() {
    QString temp = "ZL,20140101171120000102,E12001682XA,0,1800";//"ZL,20016101180122000101,17121618739,1,1800";;//"ZL,20016101180122000101,17121618739,1,1800";
    workInfo.instruction_id = temp;
    my_socket->send_message(50,temp);
    table_process->item(1,1)->setText(workInfo.instruction_id.split(",")[1]);
    my_socket->check_flag[1] = 1;
}
void MainWindow::my_send4() {//生产记录码
    if (workInfo.instruction_id.size() == 0) {
        ui->label->setText("请先扫生产令码");
        return;
    }

    QString temp = "20010001180321000101,200819121338,200903115125,7,0,50000,037013,300,0,11,,,,,245973,,,1,0,0,1,50000,001073,100,0,200815164731,0,300";

    if (rec_set.find(temp.split(" ")[0]) != rec_set.end()) {
        return;
    }
    else {
        rec_set.insert(temp.split(" ")[0]);
    }
    if (workInfo.instruction_id.split(",")[1].mid(workInfo.instruction_id.split(",")[1].size() - 2,2).toInt() != temp.split(",")[0].mid(temp.split(",")[0].size() - 2,2).toInt() + 1) {
        ui->label->setText("工序错误");
        return;
    }
    qDebug()<<workInfo.instruction_id.split(",")[1].mid(workInfo.instruction_id.split(",")[1].size() - 2,2).toInt()<<"生产记录码后两位";
    qDebug()<<temp.split(",")[0].mid(temp.split(",")[0].size() - 2,2).toInt() + 1;
    my_socket->send_message(51,temp);
    my_socket->check_flag[3] = 1;
}
void MainWindow::insert_table2(ElseInf &e) {
    if (table2.data() == nullptr) {
        ui->label->setText("请先进入开工模式");
        return;
    }
    if (workInfo.instruction_id.size() == 0) {
        ui->label->setText("请先扫生产令码");
        return;
    }
    table2->insert(e);
}
void MainWindow::confirm() {
    qDebug()<<"confirm";
    if (my_socket->check_flag[0] == 1 && my_socket->check_flag[1] == 1 && my_socket->check_flag[2] == 1 && my_socket->check_flag[3] == 1) {//4码全扫过了
        qDebug()<<table2.data()->rowCount();
        for (int i = 0;i < table2.data()->rowCount();i++) {
            start_work start;
            start.ID = table2.data()->item(i,0)->text();
            start.EndTime = table2.data()->item(i,1)->text();
            start.MaterialInf = table2.data()->item(i,2)->text();
            start.StartUser = table2.data()->item(i,3)->text();
            start.EndCount = table2.data()->item(i,4)->text();
            start.ModeList = table2.data()->item(i,5)->text();
            QDateTime dateTime = QDateTime::currentDateTime();
            QLocale locale;//指定英文显示
            //QLocale locale = QLocale::Chinese;//指定中文显示
            //QLocale locale = QLocale::Japanese;//指定日文显示
            QString strFormat = "yyyy-MM-dd hh:mm:ss";
            QString strDateTime = locale.toString(dateTime, strFormat);
            start.StartTime = strDateTime;
            qDebug()<<strDateTime;
            start.DevID = table_product->item(1,1)->text();
            start.remaind_count = table2.data()->item(i,6)->text();
            tablestart.data()->insert(start);//start插入

            //数据库要增加

            my_socket->send_message(53,start);

        }
        table2.data()->setVisible(false);
        ui->verticalLayout_2->removeWidget(table2.data());
        table2.clear();
        ui->verticalLayout_2->addItem(ui->horizontalLayout);
        ui->verticalLayout_2->addWidget(ui->widget_2);
        ui->verticalLayout_2->addItem(ui->horizontalLayout_2);
        ui->verticalLayout_2->addWidget(ui->widget_3);
        ui->label_2->setText("开工记录[ " + QString::number(tablestart->rowCount()) + " ]");

    }
}
void MainWindow::change_table() {
    base_table::change();
}
void my_table::focus() {
    if (this->label != nullptr) {
        this->label->setStyleSheet("color:red;");
    }
}
void my_table::unfocus() {
    if (this->label != nullptr) {
        this->label->setStyleSheet("color:black;");
    }
}
void MainWindow::delete_msg() {
    if (table2.data() != nullptr && table2.data()->isVisible()) {
        table2->remove();
        return;
    }
    base_table::remove_ctl();

}
void my_table::remove() {
    if (this->num == 0) {//只有start才删数据库
        my_socket->send_message(52,this->item(this->currentRow(),0)->text());
    }
    this->removeRow(this->currentRow());
    if (this->label != nullptr) {//配合一个QLabel显示
        this->label->setText(name + "[ " + QString::number(this->rowCount()) + " ]");
    }
    //数据库中删除该信息


}
