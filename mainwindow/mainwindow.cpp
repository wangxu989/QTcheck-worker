#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QThread>
#include<unistd.h>
socketclient *my_client;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_client = new socketclient();
    pCustomPlot = my_client->pCustomPlot;
    connect(my_port1.port1,SIGNAL(readyRead()),this,SLOT(my_read()));//扫码枪串口
    connect(my_client,SIGNAL(insert_data(int)),this,SLOT(insert_data_to_table(int)));
    my_init();
    my_client->label1 = label2;


}
void MainWindow::insert_data_to_table(int flag) {
    if (flag == 1) {
        qDebug()<<"worker info"<<workInfo.worker_id;
        table_worker->setSpan(1,2,2,2);
        QPixmap pix(":/img/员工.png");  //图片路径
        QLabel *label1 = new QLabel();
        label1->setScaledContents(true);//设置图片适应label
        label1->setPixmap(pix);
        table_worker->setCellWidget(1,2,label1);
        table_worker->item(1,0)->setText("姓名");
        table_worker->item(1,1)->setText(my_client->messageWorkerEnv.workerInfo.name);
        table_worker->item(2,0)->setText("角色");
        QString temp = my_client->messageWorkerEnv.workerInfo.role == 0?"操作员":"核验员";
        qDebug()<<workInfo.worker_id;
        table_worker->item(2,1)->setText(workInfo.worker_id.split(",")[1]);
    }
    else if (flag == 2) {
                qDebug()<<"process info"<<workInfo.instruction_id;
        table_work->item(1,0)->setText("过程");
        table_work->item(2,0)->setText("工序号");
        table_work->item(3,0)->setText("产品");
        table_work->item(4,0)->setText("工位");
        table_work->item(5,0)->setText("检具号");


        table_work->item(1,1)->setText(my_client->messageWorkerEnv.localEnv.process);
        table_work->item(2,1)->setText(workInfo.instruction_id.split(",")[1].mid(6,2));
        table_work->item(3,1)->setText(workInfo.instruction_id.split(",")[1].mid(0,6));
        table_work->item(4,1)->setText(my_client->messageWorkerEnv.localEnv.workstation);
        table_work->item(5,1)->setText(my_client->messageWorkerEnv.localEnv.gauge_no);
    }
    else if (flag == 3) {
                qDebug()<<"product info";
        table_product->item(1,0)->setText("设备");
        table_product->item(1,1)->setText(my_client->messageWorkerEnv.equip.equip);
        table_product->item(2,1)->setText(my_client->messageWorkerEnv.equip.test_place);
        table_product->item(2,0)->setText("检测场所");
    }
}
void MainWindow::my_read() {
    my_port1.code_scan = my_port1.port1->readAll();
    if (my_port1.code_scan.contains("\r")) {
        my_port1.code_scan = my_port1.code_scan.remove(my_port1.code_scan.size() - 1,1);
        my_port1.temp_scan+=my_port1.code_scan;
        //string_scan.push_back(temp_scan);
        if (my_port1.temp_scan.contains("YG")) {
            workInfo.worker_id = my_port1.temp_scan;
            my_client->send_message(2,(void *)&my_port1.temp_scan);
            my_client->check_flag[0] = 1;
        }
        else if (my_port1.temp_scan.contains("ZL")){
            workInfo.instruction_id = my_port1.temp_scan;
            my_client->send_message(3,(void *)&my_port1.temp_scan);
            my_client->check_flag[1] = 1;
        }
        else if (my_port1.temp_scan.contains("SB")) {
            workInfo.product_id = my_port1.temp_scan;
            my_client->send_message(4,(void *)&my_port1.temp_scan);
            my_client->check_flag[2] = 1;
        }
        //        if ((my_port1.flag[0] == 0||my_port1.flag[1] == 0||my_port1.flag[2] == 0)&&my_port1.check_first(*table_work,*table_worker,*table_product,workInfo)) {
        //            my_client->send_message(0,(void *)&workInfo);
        //        }
        //else {//此时为识别核验员身份
        if (my_port1.temp_scan.contains("YG") && my_client->check_flag[0] == 1 && my_client->check_flag[1] == 1 && my_client->check_flag[2] == 1) {
            qDebug()<<"send 1";
            my_client->send_message(1,(void*) &my_port1.temp_scan);
        }
        //}
        qDebug()<<my_port1.temp_scan;
        my_port1.temp_scan.resize(0);
    }
    else {
        my_port1.temp_scan += my_port1.code_scan;
    }
}
void MainWindow::my_init() {
    label2 = new QLabel();
    Vlayout = new QVBoxLayout();//存放工作信息
    Hlayout = new QHBoxLayout();//总表
    H_plot_layout = new QHBoxLayout();//存放图表和按钮
    narrow = new QPushButton("缩小");
    enlarge = new QPushButton("放大");
    narrow->setFixedSize(50,50);
    enlarge->setFixedSize(50,50);
    V_button = new QVBoxLayout();//存放按钮
    table_work = new my_tablewidget(6,2,"工作信息");
    table_worker = new my_tablewidget(3,4,"员工信息");
    table_product = new my_tablewidget(3,2,"设备信息");
    draw();
    widget = new QWidget(this);
    widget->setLayout(Hlayout);
    this->takeCentralWidget();
    this->setCentralWidget(widget);
}
MainWindow::~MainWindow()
{
    delete  my_client;
    delete ui;
    delete table_work;
    delete table_worker;
    delete table_product;
    delete label2;
    delete Vlayout;
    delete narrow;
    delete enlarge;
    delete V_button;
    delete H_plot_layout;
    delete  Hlayout;
    delete widget;
}
void MainWindow::draw() {
    button1 = new QPushButton("登陆确认");
    QPixmap pix(":/img/扫码.png");  //图片路径
    label2 = new QLabel();
    label2->setScaledContents(true);//设置图片适应label
    label2->setPixmap(pix);
    Vlayout->addWidget(label2);
    Vlayout->addWidget(table_worker);
    Vlayout->addWidget(table_work);
    Vlayout->addWidget(table_product);
    Vlayout->setStretchFactor(label2,1);
    Vlayout->setStretchFactor(table_worker,2);
    Vlayout->setStretchFactor(table_work,2);
    Vlayout->setStretchFactor(table_product,2);
    QPushButton *send_work = new QPushButton("员工");
    QPushButton *send_worker = new QPushButton("设备");
    QPushButton *send_inst = new QPushButton("指令");
    QPushButton *send_checker = new QPushButton("核验");
    send_work->setFixedSize(50,50);
    send_worker->setFixedSize(50,50);
    send_inst->setFixedSize(50,50);
    send_checker->setFixedSize(50,50);
    connect(send_checker,SIGNAL(clicked()),this,SLOT(my_send4()));
    connect(send_work,SIGNAL(clicked()),this,SLOT(my_send2()));
    connect(send_worker,SIGNAL(clicked()),this,SLOT(my_send1()));
    connect(send_inst,SIGNAL(clicked()),this,SLOT(my_send3()));
    V_button->addWidget(enlarge);
    V_button->addWidget(narrow);
    V_button->addWidget(send_work);
    V_button->addWidget(send_worker);
    V_button->addWidget(send_inst);
    V_button->addWidget(send_checker);
    connect(enlarge,SIGNAL(clicked()),this,SLOT(enlarge_plot()));
    connect(narrow,SIGNAL(clicked()),this,SLOT(narrow_plot()));
    H_plot_layout->addWidget(pCustomPlot);
    H_plot_layout->addLayout(V_button);
    H_plot_layout->setStretchFactor(V_button,1);
    H_plot_layout->setStretchFactor(pCustomPlot,10);
    Hlayout->addLayout(Vlayout);
    Hlayout->addLayout(H_plot_layout);
    Hlayout->setStretchFactor(Vlayout,1);
    //Hlayout->setStretchFactor(button1,1);
    Hlayout->setStretchFactor(H_plot_layout,3);
    //setLayout(Hlayout);
}
void MainWindow::change() {
    Hlayout->removeWidget(button1);
    Hlayout->removeItem(Vlayout);
    Hlayout->addWidget(pCustomPlot);

}
void MainWindow::enlarge_plot(){
    double dCenter = pCustomPlot->xAxis->range().center();
    ///缩小区间 (放大 plotTables 鼠标向外滚动)
    pCustomPlot->xAxis->scaleRange(0.5, dCenter);
}
void MainWindow::narrow_plot(){
    double dCenter = pCustomPlot->xAxis->range().center();
    // 扩大区间 （缩小 plottables 鼠标向内滚动）
    pCustomPlot->xAxis->scaleRange(2.0, dCenter);
    QSharedPointer<QCPAxisTicker>timer = pCustomPlot->xAxis->ticker();
    //(QCPAxisTickerDateTime*)pCustomPlot->xAxis->ticker()->setDateTimeFormat("d. MMMM\nyyyy");
}

void MainWindow::my_send1() {
    QString temp = "YG,02294";
    my_client->send_message(2,(void *)&temp);
    my_client->check_flag[0] = 1;
}

void MainWindow::my_send2() {
    QString temp = "SB,001073";
    my_client->send_message(4,(void *)&temp);
    my_client->check_flag[2] = 1;
}

void MainWindow::my_send3() {
    QString temp = "ZL,20016101180122000101,17121618739,1,1800";
    my_client->send_message(3,(void *)&temp);
    my_client->check_flag[1] = 1;
}
void MainWindow::my_send4() {
     QString temp = "YG,02294";
     my_client->send_message(1,(void*)&temp);
}
