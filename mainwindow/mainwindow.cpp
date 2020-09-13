#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPixmap>
#include<QThread>
#include<unistd.h>
socketclient *my_client;
extern const int N = 5;//每个任务的线条数
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint); // 去掉标题栏,去掉任务栏显示，窗口置顶
    ui->setupUi(this);
    my_client = new socketclient();
    pCustomPlot = my_client->pCustomPlot;
    connect(my_port1.port1,SIGNAL(readyRead()),this,SLOT(my_read()));//扫码枪串口
    connect(my_client,&socketclient::insert_data,this,&MainWindow::insert_data_to_table);
    connect(my_client,SIGNAL(plot_enlarge()),this,SLOT(enlarge_plot()));
    connect(my_client,SIGNAL(plot_narrow()),this,SLOT(narrow_plot()));
    connect(my_client,SIGNAL(gauge_no(const QString* const)),this,SLOT(gauge_no_flash(const QString* const)));
    my_init();
    my_client->label1 = label2;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","local");
    db.setDatabaseName("./data/work_record");
    if (!db.open()) {
        qDebug()<<"open local_sqlite failed!";
        QMessageBox box(QMessageBox::NoIcon,"sqlite","open filed!",NULL,NULL);
        box.exec();
    }
    query = db.exec();

}
void MainWindow::insert_data_to_table(int flag) {
    if (flag == 1) {
        qDebug()<<"worker info"<<workInfo.worker_id;
//        table_worker->setSpan(1,2,2,2);
//        QPixmap pix(":/img/员工.png");  //图片路径
//        QLabel *label1 = new QLabel();
//        label1->setScaledContents(true);//设置图片适应label
//        label1->setPixmap(pix);
//        table_worker->setCellWidget(1,2,label1);
        table_worker->item(1,0)->setText("姓名");
        table_worker->item(1,1)->setText(my_client->messageWorkerEnv.workerInfo.name);
        table_worker->item(2,0)->setText("工号");
        QString temp = my_client->messageWorkerEnv.workerInfo.role == 0?"操作员":"核验员";
        qDebug()<<workInfo.worker_id;
        table_worker->item(2,1)->setText(workInfo.worker_id.split(",")[1]);
    }
    else if (flag == 2) {
                qDebug()<<"process info"<<workInfo.instruction_id;
        table_work->item(1,0)->setText("过程");
        table_work->item(2,0)->setText("工序号");
        table_work->item(3,0)->setText("产品");
        //table_work->item(4,0)->setText("工位");


        table_work->item(1,1)->setText(my_client->messageWorkerEnv.localEnv.process);
        table_work->item(2,1)->setText(workInfo.instruction_id.split(",")[1].mid(6,2));
        table_work->item(3,1)->setText(workInfo.instruction_id.split(",")[1].mid(0,6));
        //table_work->item(4,1)->setText(my_client->messageWorkerEnv.localEnv.workstation);
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
            my_client->send_message(2,my_port1.temp_scan);
            my_client->check_flag[0] = 1;
        }
        else if (my_port1.temp_scan.contains("ZL")){
            workInfo.instruction_id = my_port1.temp_scan;
            my_client->send_message(3,my_port1.temp_scan);
            my_client->check_flag[1] = 1;
        }
        else if (my_port1.temp_scan.contains("SB")) {
            workInfo.product_id = my_port1.temp_scan;
            my_client->send_message(4,my_port1.temp_scan);
            my_client->check_flag[2] = 1;
        }
        //        if ((my_port1.flag[0] == 0||my_port1.flag[1] == 0||my_port1.flag[2] == 0)&&my_port1.check_first(*table_work,*table_worker,*table_product,workInfo)) {
        //            my_client->send_message(0,(void *)&workInfo);
        //        }
        //else {//此时为识别核验员身份
        if (my_port1.temp_scan.contains("YG") && my_client->check_flag[0] == 1 && my_client->check_flag[1] == 1 && my_client->check_flag[2] == 1) {
            qDebug()<<"send 1";
            my_client->send_message(1,my_port1.temp_scan);
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
    V_button = new QVBoxLayout();
    table_work = new my_tablewidget(4,2,"工作信息");
    table_worker = new my_tablewidget(3,2,"员工信息");
    table_product = new my_tablewidget(3,2,"设备信息");
    local_gauge = new my_tablewidget(1,2);
    local_gauge->item(0,0)->setText("检具号");
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
    delete local_gauge;
    delete label2;
    delete Vlayout;
    delete H_plot_layout;
    delete  Hlayout;
    delete widget;
}
void MainWindow::draw() {
    button1 = new QPushButton("登陆确认");
    QPixmap pix(":/img/scan.png");  //图片路径
    label2 = new QLabel();
    label2->setScaledContents(true);//设置图片适应label
    label2->setPixmap(pix);
    Vlayout->addWidget(label2);
    Vlayout->addWidget(table_worker);
    Vlayout->addWidget(table_work);
    Vlayout->addWidget(table_product);
    Vlayout->addWidget(local_gauge);
    Vlayout->setStretchFactor(label2,1);
    Vlayout->setStretchFactor(table_worker,2);
    Vlayout->setStretchFactor(table_work,2);
    Vlayout->setStretchFactor(table_product,2);
    Vlayout->setStretchFactor(local_gauge,1);
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
    //sssssssssssssssssssss
#ifdef _TEXT
    V_button->addWidget(send_work);
    V_button->addWidget(send_worker);
    V_button->addWidget(send_inst);
    V_button->addWidget(send_checker);
#endif
    //xxxxxxxxxxxxxxxxxxxxxxxx
    H_plot_layout->addWidget(pCustomPlot);
    H_plot_layout->addLayout(V_button);
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
    if (plot_narrow.isEmpty()) {
        return;
    }
    my_client->x_range[my_client->tabnum].narrow--;
    QVector<uint> &temp_large = plot_narrow.top();
    foreach (uint x, temp_large) {
        pCustomPlot->graph((my_client->tabnum)*N)->data()->remove(x);
    }
    plot_narrow.pop();
    //double dCenter = pCustomPlot->xAxis->range().center();
    //缩小区间 (放大 plotTables 鼠标向外滚动)
    //pCustomPlot->xAxis->scaleRange(0.5, dCenter);
    set_range();
    pCustomPlot->replot(QCustomPlot::rpQueuedReplot);
}
QString MainWindow::set_range(){
    uint start = my_client->time.toTime_t();
    uint com_s = my_client->time.toTime_t();
    QString temp_s("");
    switch( my_client->x_range[my_client->tabnum].narrow) {
    case 1://two days
        start =start - 3600*48;
        temp_s = "and local_measure_data.measure_time > " + QString::number(start) + " and local_measure_data.measure_time < " + QString::number(com_s + 3600*24);
        break;
    case 2://four daysw
        start =start -  3600*24*4;
        temp_s = "and local_measure_data.measure_time > " + QString::number(start) + " and local_measure_data.measure_time < " + QString::number(com_s - 3600*48);
        break;
    case 3://eight days
        start =start - 3600*24*8;
        temp_s = "and local_measure_data.measure_time > " + QString::number(start) + " and local_measure_data.measure_time < " + QString::number(com_s - 3600*24*4);
        break;
    case 4:// one month
        start =start - 3600*24*30;
        temp_s = "and local_measure_data.measure_time > " + QString::number(start) + " and local_measure_data.measure_time < " + QString::number(com_s - 3600*24*8);
        break;
    case 5://one year
        start =start - 3600*24*365;
        temp_s = "and local_measure_data.measure_time > " + QString::number(start) + " and local_measure_data.measure_time < " + QString::number(com_s - 3600*24*30);
        break;
    }
    pCustomPlot->xAxis->setRange(start,my_client->time.toTime_t() + 3600*24);
    my_client->x_range[my_client->tabnum].start = start;
    my_client->x_range[my_client->tabnum].end = my_client->time.toTime_t() + 3600*24;
    return temp_s;
}
void MainWindow::narrow_plot(){
    if (my_client->x_range[my_client->tabnum].narrow >= 5) {
        return;
    }
    my_client->x_range[my_client->tabnum].narrow++;
    //double dCenter = pCustomPlot->xAxis->range().center();
    // 扩大区间 （缩小 plottables 鼠标向内滚动）
    QString temp_s = set_range();
    //QSharedPointer<QCPAxisTicker>timer = pCustomPlot->xAxis->ticker();
    QString q_t = "select * from local_measure_data join local_work_record on local_work_record.id  = local_measure_data.work_id where local_work_record.user_id = ? "
                  "and local_work_record.produce_id = ? and local_measure_data.char_id = ? " + temp_s;
    qDebug()<<q_t;
    qDebug()<<workInfo.worker_id.split(",")[1]<<workInfo.instruction_id.split(",")[1]<<my_client->createinfo[my_client->tabnum].featureid;
    query.prepare(q_t);
    query.bindValue(0,workInfo.worker_id.split(",")[1]);
    query.bindValue(1,workInfo.instruction_id.split(",")[1]);
    query.bindValue(2,my_client->createinfo[my_client->tabnum].featureid);
    if (!query.exec()) {
        QMessageBox box(QMessageBox::NoIcon,"sqlite","导出数据失败!",NULL,NULL);
    }
    qDebug()<<"查询结果："<<query.size();
    QVector<uint>temp_narrow;
    while (query.next()) {
        uint time = query.value(3).toUInt();
        double value = query.value(4).toDouble();
        qDebug()<<time<<" "<<value;
        pCustomPlot->graph(my_client->tabnum*N)->addData(time,value);
        temp_narrow.push_back(time);
    }
    plot_narrow.push(temp_narrow);
    pCustomPlot->replot(QCustomPlot::rpQueuedReplot);
    //(QCPAxisTickerDateTime*)pCustomPlot->xAxis->ticker()->setDateTimeFormat("d. MMMM\nyyyy");
}

void MainWindow::my_send1() {
    QString temp = "YG,02294";
    workInfo.worker_id = temp;
    my_client->send_message(2,temp);
    my_client->check_flag[0] = 1;
}

void MainWindow::my_send2() {
    QString temp = "SB,001073";
    workInfo.product_id = temp;
    my_client->send_message(4,temp);
    my_client->check_flag[2] = 1;
}

void MainWindow::my_send3() {
    QString temp = "ZL,20820203200708000103,E12001682XA,0,1800";//"ZL,20016101180122000101,17121618739,1,1800";
    workInfo.instruction_id = temp;
    my_client->send_message(3,temp);
    my_client->check_flag[1] = 1;
}
void MainWindow::my_send4() {
     QString temp = "YG,02294";
     my_client->send_message(1,temp);
}
void MainWindow::gauge_no_flash(const QString * const s) {
    if (s->size()) {
        local_gauge->item(0,1)->setText(*s);
    }
    else {
        local_gauge->item(0,1)->setText("检具未录入");
    }
}

