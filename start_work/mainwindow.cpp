#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTimer>
extern QQueue<start_work>q_startwork;

extern QQueue<finish_work>q_finishwork;
QMap<QString,int> my_tablewidget::res;
QVector<base_table*> base_table::rec = QVector<base_table*>();
QSharedPointer<socket> my_socket;
int base_table::num = 0;
my_tablewidget* my_tablewidget::my = NULL;
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
    connect(my_socket.data(),&socket::confrim_finish,this,&MainWindow::confirm_finish);
    connect(my_socket.data(),&socket::finish_save,this,&MainWindow::finish_save);
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

    table = new my_tablewidget(12,1,"工号","设备","生产令号","物料信息","强制检验","标箱数量");

    qDebug()<<"create";
    table2 = QSharedPointer<my_table>(new my_table("开工模式",nullptr,nullptr,"生产令号","完成时间","物料信息","员工号","成品数","产品批次","剩余数"));
    table3 = QSharedPointer<my_table>(new my_table("完工模式",nullptr,nullptr,"生产令号","完成时间","物料信息","员工号","成品数","产品批次","剩余数"));
    table_layout = new QVBoxLayout(ui->widget);
    table_layout->addWidget(table);
    tablestart = QSharedPointer<my_table>(new my_table("开工记录",ui->label_2,ui->widget_2,"生产令号","完成时间","物料信息","员工号","成品数","产品批次","开工时间","设备","剩余数"));
    tablefinish = QSharedPointer<my_table>(new my_table("完工记录",ui->label_3,ui->widget_3,"生产令号","完成时间","物料信息","成品数","待处理","产品批次","打印","剩余数"));
    tablestart->hideColumn(3);
    tablestart->hideColumn(5);
    tablestart->hideColumn(7);
    tablefinish->hideColumn(5);
    tablefinish->hideColumn(6);
    tablestart->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    tablestart->horizontalHeader()->setSectionResizeMode(6,QHeaderView::ResizeToContents);
    tablefinish->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);     //然后设置要根据内容使用宽度的列
    tablefinish->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    table2->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    table3->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    table2->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    table3->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
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
        qDebug()<<my_port1.temp_scan;
        if (!is_work) {
            if (my_port1.temp_scan.contains("YG")) {
                workInfo.worker_id = my_port1.temp_scan;
                my_socket->send_message(2,my_port1.temp_scan);
                my_socket->check_flag[0] = 1;
                table->insert("工号",my_port1.temp_scan.split(",")[1]);
            }
            my_port1.temp_scan.resize(0);
            return;
        }
        if (my_port1.temp_scan.contains("YG")) {
            workInfo.worker_id = my_port1.temp_scan;
            my_socket->send_message(2,my_port1.temp_scan);
            my_socket->check_flag[0] = 1;
            table->insert("工号",my_port1.temp_scan.split(",")[1]);
        }
        else if (my_port1.temp_scan.contains("ZL")){//生产令码
            if (my_socket->get_status()) {//开工
                qDebug()<<"开工";
                qDebug()<<my_port1.temp_scan<<"开工";
                if (my_port1.temp_scan.split(",")[1].right(2) == "01") {
                    QMessageBox box(QMessageBox::NoIcon,"","首工序不能开工");
                    QTimer::singleShot(1500,&box,SLOT(close()));
                    box.exec();
                    return;
                }
                workInfo.instruction_id = my_port1.temp_scan;
                table->insert("生产令号",workInfo.instruction_id.split(",")[1]);
                my_socket->send_message(50,my_port1.temp_scan);
                my_socket->check_flag[1] = 1;
            }
            else {//完工
                qDebug()<<my_port1.temp_scan.split(",")[1].right(2)<<"第一道工序";
                if (my_port1.temp_scan.split(",")[1].right(2) == QString("01")) {//第一道工序
                    workInfo.instruction_id = my_port1.temp_scan;
                    table->insert("生产令号",my_port1.temp_scan.split(",")[1]);
                    my_socket->send_message(50,my_port1.temp_scan);
                    my_socket->check_flag[1] = 1;
                }
                else {
                    QMessageBox box(QMessageBox::NoIcon,"","非第一道工序请扫生产记录码");
                    QTimer::singleShot(1500,&box,SLOT(close()));
                    box.exec();
                }
            }
        }
        else if (my_port1.temp_scan.contains("SB")) {
            if (workInfo.instruction_id == "" ||(!my_socket->get_status()) && workInfo.instruction_id != "" && workInfo.instruction_id.split(",")[1].right(2) != QString("01")) {//开工
                QMessageBox box(QMessageBox::NoIcon,"","非第一道工序不可扫码");
                QTimer::singleShot(1500,&box,SLOT(close()));
                box.exec();
                return;
            }
            workInfo.product_id = my_port1.temp_scan;
            my_socket->send_message(4,my_port1.temp_scan);
            my_socket->check_flag[2] = 1;
            table->insert("设备",my_port1.temp_scan.split(",")[1]);
        }

        else {//生产记录码
            if (my_socket->get_status() == false) {//完工
                table->insert("生产令号",my_port1.temp_scan.split(",")[0]);
                my_socket->send_message(54,my_port1.temp_scan);
                qDebug()<<"完工";
            }
            else {
                if (workInfo.instruction_id.size() == 0) {
                    ui->label->setText("请先扫生产令码");
                    return;
                }

                qDebug()<<workInfo.instruction_id.split(",")[1].right(2).toInt();
                qDebug()<<my_port1.temp_scan.split(",")[0].right(2).toInt();
                qDebug()<<"工序比较";
                if (workInfo.instruction_id.split(",")[1].right(2).toInt() != my_port1.temp_scan.split(",")[0].right(2).toInt() + 1) {
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
        table->insert("强制检验",my_socket->Proinf.cMustQC);
        table->insert("标箱数量",my_socket->Proinf.cStdCount);
        table->insert("物料信息",my_socket->Proinf.ElseInf);

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
    if (table3.data() != nullptr && table3.data()->isVisible()) {
        if (act%2) {
            if (table3.data()->currentRow() - 1 >= 0) {
                table3.data()->setCurrentItem(table3.data()->item(table3.data()->currentRow() - 1,0));
            }
        }
        else {
            if (table3.data()->currentRow() + 1 < table3.data()->rowCount()) {
                table3.data()->setCurrentItem(table3.data()->item(table3.data()->currentRow() + 1,0));
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
void MainWindow::change_status() {//进入开工/完工模块
    is_work = true;
    ui->verticalLayout_2->removeWidget(ui->widget_2);
    ui->verticalLayout_2->removeWidget(ui->widget_3);
    ui->verticalLayout_2->removeItem(ui->horizontalLayout);
    ui->verticalLayout_2->removeItem(ui->horizontalLayout);
    ui->verticalLayout_2->removeItem(ui->horizontalLayout_2);
    if (my_socket->get_status()) {//开工
        qDebug()<<"开工";
        table->unhidden();
        ui->verticalLayout_2->addWidget(table2.data());
    }
    else {//完工

        qDebug()<<"完工";
        table->hidden();
        ui->verticalLayout_2->addWidget(table3.data());
    }
    //table2 = QSharedPointer<my_table>(new my_table("开工模式",nullptr,nullptr,"生产令号","完成时间","物料信息","员工号","成品数","产品批次","剩余数"));
}

void MainWindow::my_send1() {
    if (!is_work){return;}
    QString temp = "YG,55045";//"YG,02294";
    workInfo.worker_id = temp;
    my_socket->send_message(2,temp);
    my_socket->check_flag[0] = 1;
    table->insert("工号",temp.split(",")[1]);
}

void MainWindow::my_send2() {
    if (!is_work){return;}
    QString temp = "SB,001073";
    workInfo.product_id = temp;
    my_socket->send_message(4,temp);
    my_socket->check_flag[2] = 1;
    table->insert("设备",temp.split(",")[1]);
}

void MainWindow::my_send3() {
    if (!is_work){return;}
    QString temp = "ZL,20016101180122000102,E12001682XA,0,1800";//"ZL,20016101180122000101,17121618739,1,1800";;//"ZL,20016101180122000101,17121618739,1,1800";
    if (my_socket->get_status()) {//开工
        workInfo.instruction_id = temp;
        my_socket->send_message(50,temp);
        table->insert("生产令号",workInfo.instruction_id.split(",")[1]);
        my_socket->check_flag[1] = 1;
    }
    else {//完工
        if (temp.split(",")[1].right(2) == QString("01")) {//第一道工序
            workInfo.instruction_id = my_port1.temp_scan;
            //is_first = true;
            table->insert("生产令号",temp.split(",")[1]);
            my_socket->send_message(50,temp);//
            my_socket->check_flag[1] = 1;
        }
        else {
            QMessageBox box(QMessageBox::NoIcon,"","非第一道工序请扫生产记录码");
            QTimer::singleShot(1500,&box,SLOT(close()));
            box.exec();
        }
    }
}
void MainWindow::my_send4() {//生产记录码20010001180321000101,200903115125
    if (!is_work){return;}
    QString temp = "20016101180122000101,,201027154713,1,0,YG,55045,SB,001073,2900,0,60,2222,,444,外协机加进料检,17121618739,,016101,";//"20016101180122000102,200819121338,200515163814,7,0,50000,037013,300,0,11,,,,,245973,,,1,0,0,1,50000,001073,100,0,200815164731,0,300";

    if (my_socket->get_status() == false) {//完工
        table->insert("生产令号",temp.split(",")[0]);
        my_socket->send_message(54,temp);
        qDebug()<<"完工";
        return;
    }
    if (workInfo.instruction_id.size() == 0) {
        ui->label->setText("请先扫生产令码");
        return;
    }

    if (rec_set.find(temp.split(" ")[0]) != rec_set.end()) {
        return;
    }
    else {
        rec_set.insert(temp.split(" ")[0]);
    }
    qDebug()<<workInfo.instruction_id.split(",")[1].right(2).toInt()<<" "<<temp.split(",")[0].right(2).toInt()<<"工序";
    if (workInfo.instruction_id.split(",")[1].right(2).toInt()  != temp.split(",")[0].right(2).toInt() + 1) {
        ui->label->setText("工序错误");
        return;
    }
    qDebug()<<workInfo.instruction_id.split(",")[1].mid(workInfo.instruction_id.split(",")[1].size() - 2,2).toInt()<<"生产记录码后两位";
    qDebug()<<temp.split(",")[0].mid(temp.split(",")[0].size() - 2,2).toInt() + 1;
    my_socket->send_message(51,temp);
    my_socket->check_flag[3] = 1;
}
void MainWindow::insert_table2(ElseInf &e) {
    QSharedPointer<my_table>temp;
    if (my_socket->get_status()) {//开工
        temp = table2;
    }
    else {
        temp = table3;
    }
    if (temp.data() == nullptr) {
        ui->label->setText("请先进入开工模式");
        return;
    }
    if (workInfo.instruction_id.size() == 0) {
        ui->label->setText("请先扫生产令码");
        return;
    }
    temp->insert(e);
}
void MainWindow::confirm() {//开工
    is_work = false;
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
            start.DevID = table->get_val("设备");
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
        this->label->setStyleSheet("color:blue;font: 20pt;");
        this->setStyleSheet("background:rgb(144,238,144)");
    }
}
void my_table::unfocus() {
    if (this->label != nullptr) {
        this->label->setStyleSheet("color:black;font: 20pt;");
        this->setStyleSheet("background:white;");
    }
}
void MainWindow::delete_msg() {
    if (table2.data() != nullptr && table2.data()->isVisible()) {
        table2->remove();
        return;
    }
    if (table3.data() != nullptr && table3.data()->isVisible()) {
        table3->remove();
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
void MainWindow::confirm_finish(ElseInf& elseinf){
    is_work = false;
    //elseinf.UserID = table->get_val("工号");
    elseinf.MaterialInf = table->get_val("物料信息");
    elseinf.ID = table->get_val("生产令号");
    table3->insert(elseinf);
}
void MainWindow::finish_save() {//完工保存
    for (int i = 0;i < table3.data()->rowCount();i++) {
        finish_work inf;
        inf.ID = table3.data()->item(i,0)->text();
        inf.EndTime = table3.data()->item(i,1)->text();
        inf.MaterialInf = table3.data()->item(i,2)->text();
        //inf.isPrint = "1";
        inf.onhand = table3.data()->item(i,3)->text();
        inf.EndCount = table3.data()->item(i,4)->text();
        inf.probatch = table3.data()->item(i,5)->text();
        inf.residueNum = table3.data()->item(i,6)->text();
        tablefinish->insert(inf);//start插入
        //数据库要增加
    }
    table3.data()->setVisible(false);
    ui->verticalLayout_2->removeWidget(table3.data());
    table3.clear();
    ui->verticalLayout_2->addItem(ui->horizontalLayout);
    ui->verticalLayout_2->addWidget(ui->widget_2);
    ui->verticalLayout_2->addItem(ui->horizontalLayout_2);
    ui->verticalLayout_2->addWidget(ui->widget_3);

}
