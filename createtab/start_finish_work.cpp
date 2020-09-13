#include "start_finish_work.h"
#include "ui_start_finish_work.h"
extern database_server *data_server;
extern int mode;
start_finish_work::start_finish_work(const QString& name, QWidget *parent) :

    //QWidget(parent),
    ui(new Ui::start_finish_work),
    my_xml(xml::get_xml()),
    name_P(name)
{
    add_p(name,this);
    ui->setupUi(this);
}

start_finish_work::~start_finish_work()
{
    delete ui;
}
bool start_finish_work::start_P() {
    if (!listen(my_socket)) {
        return false;
    }
    //业务逻辑，此功能为开工/完工
    key = QSharedPointer<keyboard_widget>(new keyboard_widget("Enter"));
    ui->widget->setLayout(key->layout());
    my_progress.start("./plugin/start_work");
    //emit MyWidget::change_widget(this);
    connect(my_socket,&socket::check_info,this,&start_finish_work::check_info);
    connect(my_socket,&socket::transf_processID,this,&start_finish_work::deal_ProcessID);
    connect(my_socket,&socket::deal_rec,this,&start_finish_work::deal_rec);
    connect(my_socket,&socket::delete_start2tab,this,&start_finish_work::delete_start2tab);
    connect(my_socket,&socket::add_start2tab,this,&start_finish_work::add_start2tab);
    return true;
}
void start_finish_work::finish_P() {
    my_progress.close();
    remove_P(name_P);
    emit MyWidget::change_widget(nullptr);
    disconnect(my_socket,&socket::check_info,this,&start_finish_work::check_info);
    delete this;
}
void start_finish_work::check_info(int flag) {
    qDebug()<<"check_info"<<flag<<"mode :"<<mode;
    if (start_flag != 0) {
        return;
    }
    switch (flag) {
    case 1:
        //if (my_xml.read_local_authuser(my_socket->workInfo) == 0) {
            ret_checkout[0] = 1;//员工码
            if(my_socket->clientConnection) {
                //my_socket->sendmessage(5,my_xml.messageWorkerEvn.workerInfo);
                search_base();
                qDebug()<<"send workerinfo!";
            }
            else {
                qDebug()<<"send failed!";
            }
        //}
        //else {
          //  my_socket->sendmessage(8);
        //}
        //}
        // else if (mode == 1) {


        // }
        qDebug()<<my_xml.messageWorkerEvn.workerInfo.name;
        break;
    case 2:
        //if (mode == 0) {
        //if (my_xml.readxml(my_socket->workInfo,1) == 0) {
            ret_checkout[1] = 1;
            if (my_xml.read_local_env(my_socket->workInfo,0)==0) {

                if(my_socket->clientConnection) {
                    //my_socket->sendmessage(6,my_xml.messageWorkerEvn.localEnv);//图表信息
                    qDebug()<<"send workinfo!";
                    qDebug()<<my_xml.messageWorkerEvn.localEnv.workstation;
                }
                else {
                    qDebug()<<"send failed!";
                }
            }
        //}
        //else {
         //   my_socket->sendmessage(9);
        //}
        //}
        //else if (mode == 1) {

        //}

        break;
    case 3:
        //if (mode == 0) {
        //if (my_xml.read_local_env(my_socket->workInfo,1)==0) {
            if(my_socket->clientConnection) {
                //my_socket->sendmessage(7,my_xml.messageWorkerEvn.equip);
                qDebug()<<"send equipinfo!";
            }
            else {
                qDebug()<<"send failed!";
            }
            ret_checkout[2] = 1;//设备码
        //}
        //else {
          //  my_socket->sendmessage(10);
        //}
        //}
        //else if (mode == 1) {

        //}
        break;
    }
    if (ret_checkout[0] == 1 && ret_checkout[2] == 1) {
        ui->pushButton->setEnabled(true);
    }

}
void start_finish_work::search_base() {
    int time_scope = my_xml.read_start_finish_config();
    QDateTime time = QDateTime::fromTime_t(QDateTime::currentDateTime().toTime_t() - time_scope*24*3600);
    QString cmp_end = (time.date().year() < 10 ? "0":"") +  QString::number(time.date().year() - 2000) +
                  (time.date().month() < 10 ? "0":"") +  QString::number(time.date().month()) +
                  (time.date().day() < 10 ? "0":"") +  QString::number(time.date().day())+
                  (time.time().hour() < 10 ? "0":"") + QString::number(time.time().hour()) +
                  (time.time().minute() < 10 ? "0":"") + QString::number(time.time().minute()) +
                  (time.time().second() < 10 ? "0":"") + QString::number(time.time().second());
        QLocale locale = QLocale::English;//指定英文显示
        //QLocale locale = QLocale::Chinese;//指定中文显示
        //QLocale locale = QLocale::Japanese;//指定日文显示
        QString strFormat = "yyyy-MM-dd hh:mm:ss";
        QString cmp = locale.toString(time, strFormat);

    qDebug()<<"time         "<<cmp;

    QString s = "select * from planstart2tab where StartUser = " + my_socket->workInfo.worker_id.split(",")[1] + " and StartTime >= " + "'" + cmp + "'";
    QSqlQuery query =  data_server->query_ctl(s);
    start_rec start;
    if (query.size() > 0) {
        my_socket->sendmessage(82,query.size());
    }
    while(query.next()) {
        start.ID = query.value(0).toString();
        start.EndTime = query.value(1).toString();
        start.MaterialInf = query.value(2).toString();
        start.StartUser = query.value(6).toString();
        start.EndCount = query.value(4).toString();
        start.StartTime = query.value(7).toString();
        start.DevID = query.value(11).toString();
        start.remaind_count = query.value(9).toString();
        start.ModeList = query.value(12).toString();
        qDebug()<<start.ID;
        my_socket->sendmessage(80,start);
    }
    qDebug()<<cmp_end;
    s = "select * from planqrtab where s5 = " + my_socket->workInfo.worker_id.split(",")[1] + " and s2 >= " + "'" + cmp_end + "'";
    query = data_server->query_ctl(s);
    if (query.size() > 0) {
        my_socket->sendmessage(83,query.size());
    }
    finish_work finish;
    while(query.next()) {
        finish.ID = query.value(0).toString();
        finish.EndTime = query.value(2).toString();
        finish.EndCount = query.value(7).toString();
        finish.MaterialInf = query.value(14).toString();
        finish.onhand = query.value(8).toString();
        finish.isPrint = query.value(28).toString();
        finish.probatch = query.value(15).toString();
        finish.residueNum = query.value(27).toString();
        my_socket->sendmessage(81,finish);
    }

}

void start_finish_work::on_pushButton_4_clicked()
{
    finish_P();
}

void start_finish_work::on_pushButton_2_clicked()//切换,需要改变子程序状态
{
    status = !status;
    if (status) {
        ui->pushButton->setText("完工");
    }
    else {
         ui->pushButton->setText("开工");
    }
    my_socket->sendmessage(88);
}

void start_finish_work::on_pushButton_6_clicked()//reduce
{
    if (status) {//plansteptab
        data_server->reducesteptab(1);
    }
    else {//plantab
        data_server->reducetab(1);
    }
}

void start_finish_work::on_pushButton_7_clicked()//add
{
    if (status) {//2
        data_server->add_steptab(1);
    }
    else {
        data_server->add_tab(1);
    }
}

void start_finish_work::on_pushButton_5_clicked()//删除
{
    my_socket->sendmessage(89);
}
void start_finish_work::deal_ProcessID(QString &s) {//解析生产令
    QString temp = "select * from plansteptab where PlanStepID = '" + s.split(",")[1] + "'";
    QSqlQuery query = data_server->query_ctl(temp);
    qDebug()<<temp;
    if (query.size() > 0){
        ret_checkout[1] = 1;
    }
    while (query.next()) {
        ProInf.cMustQC = query.value(12).toString();
        ProInf.cStdCount = query.value(13).toString();

        qDebug()<<"CMustqc";
    }
    temp = "select * from plantab where PlanID = '" + s.split(",")[1].mid(0,s.split(",")[1].size() - 2) + "'";
    query = data_server->query_ctl(temp);
    qDebug()<<temp;
    while (query.next()) {
        ProInf.ElseInf = query.value(4).toString();
    }
     my_socket->sendmessage(84,ProInf);
}

void start_finish_work::on_pushButton_clicked()//开工
{
    if (ui->pushButton->text() == "确认") {
        ui->pushButton->setText("开工");
        ui->pushButton_2->setEnabled(true);//切换开
        my_socket->sendmessage(87);

    }
    else if (ui->pushButton->text() == "开工"){
        if (!(ret_checkout[0] == 1 && ret_checkout[1] == 1 && ret_checkout[2] == 1 && ret_checkout[3] == 1)) {//确认先决条件
            ui->pushButton->setEnabled(false);
        }
        ui->pushButton->setText("确认");
        ui->pushButton_2->setEnabled(false);//关切换
        my_socket->sendmessage(85);
    }
}
void start_finish_work::deal_rec(QString &s) {//生产记录
    QString key1 = s.split(",")[0];
    QString key2 = s.split(",")[2];
    QString temp = "select * from planqrtab where s0 = '"  + key1  + "'" + " and s2 = '" + key2 + "'";
    QSqlQuery query = data_server->query_ctl(temp);
    qDebug()<<temp<<" "<<query.size();
    if (query.size() > 0) {
        ret_checkout[3] = 1;
    }
    while(query.next()) {
        elseinf.ID = query.value(0).toString();
        elseinf.MaterialInf = query.value(14).toString();
        elseinf.EndCount = query.value(7).toString();
        elseinf.EndTime = query.value(2).toString();
        elseinf.UserID = query.value(5).toString();
        elseinf.probatch = query.value(15).toString();
        elseinf.residueNum = query.value(27).toString();
        my_socket->sendmessage(86,elseinf);
    }
    if (ret_checkout[0] == 1 && ret_checkout[1] == 1 && ret_checkout[2] == 1 && ret_checkout[3] == 1) {
        ui->pushButton->setEnabled(true);
    }
}
void start_finish_work::delete_start2tab(QString &s) {
    QString temp = "delete from planstart2tab where BlankID = '" + s + "'";
    data_server->query_ctl(temp);
}
void start_finish_work::add_start2tab(const start_rec &s) {
     QString temp = QString("insert into planstart2tab (BlankID,EndTime,MaterialInf,EndCount,StartUser,StartTime,DevID,MoldList)"
                    "values"
                    "('%1','%2','%3','%4','%5','%6','%7','%8')").arg(s.ID,s.EndTime,s.MaterialInf,s.EndCount,s.StartUser,s.StartTime,s.DevID,s.ModeList);
     data_server->query_ctl(temp);

}
