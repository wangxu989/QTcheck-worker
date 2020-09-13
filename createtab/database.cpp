#include "database.h"
#include<QFile>
#include<QSqlError>
#include<QMessageBox>
#include<stdlib.h>
#include<string>
int database::last_insert_id = -1;
QDataStream& operator<<(QDataStream& os,const producttab& p) {
    os<<p.productID;
    os<<p.productName;
    os<<p.productState;
    os<<p.clientProductName;
    os<<p.clientDrawingID;
    os<<p.ourDrawingID;
    os<<p.clientVersion;
    return os;
}
QDataStream& operator<<(QDataStream& os,const plansteptab& p1) {
    os<<p1.PlanStepID;
    os<<p1.cProcessIndex;
    os<<p1.cProcessName;
    os<<p1.cProcessDetail;
    os<<p1.cWorkShop;
    os<<p1.cWorkSection;
    os<<p1.cDevice;
    os<<p1.cProcessEquip;
    os<<p1.cWorkHour;
    os<<p1.cMustQC;
    os<<p1.cStdCount;
    os<<p1.cCountRatio;
    return os;
}

QDataStream& operator<<(QDataStream& os,const plantab& p1) {
    os<<p1.PlanID;//计划号18位
    os<<p1.PlanCount;
    os<<p1.EndCount;
    os<<p1.PlanEndDate;
    os<<p1.PlanState;
    os<<p1.cCappName;
    os<<p1.ElseInf;//物料编码
    os<<p1.IsRework;
    os<<p1.CreateUser;
    os<<p1.CreateTime;
    return os;
}

void database_server::createdatabase() {
    db.setHostName(plugin.hostname);
    db.setUserName(plugin.userName);
    db.setDatabaseName(plugin.databaseName);
    db.setPassword(plugin.passwd);
    qDebug()<<plugin.hostname<<" "<<plugin.userName<<" "<<plugin.databaseName<<" "<<plugin.passwd;
    if (!db.open()) {
        QSqlError error = db.lastError();
        QMessageBox box(QMessageBox::NoIcon,"title",error.databaseText(),NULL,NULL);
        box.exec();
        qDebug()<<"open database failed"<<error.databaseText();
    }
    else {
        query = db.exec();
        qDebug()<<"open datebase successfully";
    }

}

void database_server::read_data() {//读取远程数据库中工作信息
    //1.获取本机mac地址
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();//获取所有网络接口列表
    for (int i = 0;i < nets.count();i++) {
        if (nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning)) {
            mac_address = nets[i].hardwareAddress();//获取了
            qDebug()<<"mac_address:"<<mac_address;
            break;
        }
    }
    QString temp = "select * from client_cfg where client_mach_id = \"" + mac_address + "\"";
    qDebug()<<temp;
    this->query_ctl(temp);
    QString client_mach_id;
    QString mode;
    if (query.size() == 0) {
        QMessageBox box(QMessageBox::NoIcon,"title","非法机器访问",NULL,NULL);
        box.exec();
        exit(-1);
    }
    while (query.next()){
        int id = query.value(0).toInt();
        client_mach_id = query.value(1).toString();
        mode = query.value(2).toString();
        QString cmd = query.value(3).toString();
        qDebug()<<id<<" "<<client_mach_id<<" "<<mode<<" "<<cmd;
    }
    if (mode.toInt() == 1) {
        //正常工作模式
        //首先判断工作人员信息是否合法
        this->query_ctl("select * from auth_user where user_id = " + workInfo->worker_id.split(",")[workInfo->worker_id.split(",").size() - 1]);
        if (query.size() == 0) {
            QMessageBox box(QMessageBox::NoIcon,"title","员工信息不合法",NULL,NULL);
            box.exec();
            flag = 0;
            return;
        }
        while (query.next()) {
            QString name = query.value(3).toString();
            QString clien_mach_id = query.value(1).toString();
            if (clien_mach_id != mac_address) {
                QMessageBox box(QMessageBox::NoIcon,"title","您无权访问此机器",NULL,NULL);
                box.exec();
                flag = 1;
                return;
            }
        }

        //检索数据库寻找对应的工作信息
        QString find_work = workInfo->instruction_id.split(",")[1].mid(0,6);//暂定
        find_work = "select * from spc_schemes where product_no = " + find_work;
        this->query_ctl(find_work);
        int row_count = query.size();
        qDebug()<<row_count;
        if (row_count == 0) {
            QMessageBox box(QMessageBox::NoIcon,"title","无对应工作信息",NULL,NULL);
            box.exec();
            flag = 2;
            return;
        }
        qDebug()<<"start read net_sche_info";
        while (query.next()) {
            qDebug()<<"start read net_sche_info"<<query.value(0).toInt()<<" "<<query.value(1).toString();
            tab->info.product_no = query.value(1).toString();
            qDebug()<<"1   "<<tab->info.product_no;
            tab->info.warn_thr = query.value(9).toString();
            qDebug()<<"9";
            tab->info.chk_warn_thr = query.value(10).toString();
            tab->info.detect_mode = query.value(11).toString();
            tab->info.time_interval = query.value(12).toString();
            tab->info.cycle_time = query.value(13).toString();
            tab->info.sample_cnt = query.value(14).toString();
            tab->info.disp_element_cnt = query.value(15).toString();
            tab->info.trend_warn_win = query.value(17).toString();
            tab->info.lock_time = query.value(16).toString();
            tab->my.x.resize(row_count);
            tab->my.y.resize(row_count);
            tabinfo temp;
            temp.featureid = QString::number(query.value(2).toFloat());
            temp.char_desc = query.value(3).toString();
            temp.normvalue =query.value(4).toDouble();
            temp.zgc = query.value(5).toDouble();
            temp.fgc = query.value(6).toDouble();
            temp.jddw = query.value(7).toDouble();
            temp.ejjddw = query.value(8).toDouble();
            tab->createinfo.push_back(temp);
            qDebug()<<"网络版配置已读完";
            qDebug()<<tab->info.chk_warn_thr<<" "<<tab->info.cycle_time<<" "<<tab->info.detect_mode<<" "<<tab->info.disp_element_cnt<<" "<<tab->info.lock_time;
            tab->tabadd(temp,tab->info);
        }
    }
    else if (mode.toInt() == 2){//维护模式
        QMessageBox box(QMessageBox::NoIcon,"title","系统维护",NULL,NULL);
        box.exec();
        //维护逻辑
    }
    else if (mode.toInt() == 3) {
        //禁用模式
        QMessageBox box(QMessageBox::NoIcon,"title","系统禁用",NULL,NULL);
        box.exec();
        exit(-1);
    }
    //query.exec();


}
void database_local::createtable() {
    //work_record
    if (!query.exec("create table if not exists local_work_record(id integer primary key AUTOINCREMENT,"//记录号自增
                    "user_id varchar(32),"//员工码
                    "start_time varchar(32),"//开工时间
                    "finish_time varchar(32),"//完工时间
                    "work_state varchar(1),"//完工状态
                    "produce_id varchar(32),"//生产令
                    "equip_id varchar(32),"//设备
                    "workstation varchar(32),"//工位
                    "gauge_no varchar(32))")) {//检具号
        QSqlError error = query.lastError();
        QMessageBox box(QMessageBox::NoIcon,"mysql","本地数据库work_record创建失败" + error.databaseText(),NULL,NULL);
        box.exec();
    }
    if (!query.exec("create table if not exists local_measure_data(id integer primary key AUTOINCREMENT,"//记录号自增
                    "work_id int,"//开工记录号
                    "gauge_no varchar(32),"//检具号
                    "measure_time varchar(32),"//测量时间
                    "measure_value varchar(32),"//测量值
                    "checker varchar(32),"//复核员
                    "chk_time varchar(32),"//复核时间
                    "chk_value varchar(32),"//复核值
                    "meas_rlt_id varchar(1),"//测量结果标识
                    "chk_rlt varchar(1),"//复核结果标识
                    "char_id int,"//规格号
                    "element_SD int,"//零件流水号
                    "FOREIGN KEY(work_id) REFERENCES local_work_record(id) on delete cascade on update cascade)")) {//零件流水号
        QMessageBox box(QMessageBox::NoIcon,"mysql","本地数据库local_measure_data创建失败",NULL,NULL);
        box.exec();

    };
    if (!query.exec("PRAGMA foreign_keys = ON")) {
        qDebug()<<"foreign_key failed!";
    }
}
void database_local::insert_record() {

    query.prepare("insert into local_work_record (user_id,start_time,finish_time,"
                  "work_state,produce_id,equip_id,workstation,gauge_no)"
                  "values(?,?,?,?,?,?,?,?)");
    query.bindValue(0,workInfo->worker_id.split(",")[1].mid(0,6));
    QDateTime time = QDateTime::currentDateTime();
    //QString n = time.toUTC().toString();
    //qDebug()<<n;
    query.bindValue(1,QString::number(time.toTime_t()));
    query.bindValue(2,"");
    query.bindValue(3,'0');
    query.bindValue(4,workInfo->instruction_id.split(",")[1]);
    query.bindValue(5,workInfo->product_id.split(",")[1]);
    query.bindValue(6,tab->messageWorkerEvn.localEnv.workstation);
    query.bindValue(7,tab->messageWorkerEvn.localEnv.gauge_no);
    if (!query.exec()) {
        QSqlError error = query.lastError();
        qDebug()<<error.databaseText();
        QMessageBox box(QMessageBox::NoIcon,"mysql","本地数据库local_record插入失败" + error.databaseText(),NULL,NULL);
        box.exec();
    }
    last_insert_id = query.lastInsertId().toInt();
}
void database_local::insert_data(const double &data,const  int &flag,const int &operation_flag){//flag为是否合格
    QDateTime now = QDateTime::currentDateTime();
    qDebug()<<" "<<tab->table[tab->currentIndex()]->gap<<" "<<tab->currentIndex() + 1;
    int ele_SD = (now.time().hour()*3600 + now.time().minute()*60 + now.time().second() - tab->work_start_time)/tab->table[tab->currentIndex()]->gap *(tab->currentIndex() + 1);
    qDebug()<<ele_SD<<"SD";
    if (operation_flag == 0) {//操作员增加
        query.prepare("insert into local_measure_data(work_id,gauge_no,measure_time,measure_value,"
                      "checker,chk_time,chk_value,meas_rlt_id,chk_rlt,char_id,element_SD)"
                      "values(?,?,?,?,?,?,?,?,?,?,?)");
        query.bindValue(0,last_insert_id);
        query.bindValue(2,QString::number(now.toTime_t()));
        query.bindValue(1,tab->messageWorkerEvn.localEnv.gauge_no);
        query.bindValue(3,QString::number(data));
        query.bindValue(4,"");
        query.bindValue(5,"");
        query.bindValue(6,"");
        query.bindValue(7,flag);
        query.bindValue(8,"");
        query.bindValue(9,tab->createinfo[tab->currentIndex()].featureid.toInt());
        query.bindValue(10,ele_SD);
    }
    else if (operation_flag == 1) {//操作员修改
        query.prepare("update local_measure_data set measure_time = ?,measure_value = ?,meas_rlt_id = ? where element_SD = ? and work_id = ?");
        query.bindValue(0,QString::number(now.toTime_t()));
        query.bindValue(1,QString::number(data));
        query.bindValue(2,flag);
        query.bindValue(3,ele_SD);
        query.bindValue(4,last_insert_id);
    }
    else if (operation_flag == 2) {//核验员操作,和修改
        query.prepare("update local_measure_data set checker = ?,chk_time = ?,chk_value = ?,chk_rlt = ? where element_SD = ? and work_id = ?");
        query.bindValue(0,workInfo->checker_id);
        query.bindValue(1,QString::number(now.toTime_t()));
        query.bindValue(2,QString::number(data));
        query.bindValue(3,flag);
        query.bindValue(4,ele_SD);
        query.bindValue(5,last_insert_id);
    }
    if (!query.exec()) {
        QSqlError error = query.lastError();
        qDebug()<<error.databaseText();
        QMessageBox box(QMessageBox::NoIcon,"sqlite3","本地数据库local_record插入失败" + error.databaseText() + QString::number(last_insert_id),NULL,NULL);
        box.exec();
    }
}
void database_server::spc_event(QString type) {//上报
    QDateTime now = QDateTime::currentDateTime();
    QString s = QString("insert into spc_event (client_id,event_time,event_type,user_id,equip_id,work_id)"
                  "values('%1','%2','%3','%4','%5','%6')").arg(mac_address,now.toString("yyyyMMddhhmmss"),type,workInfo->worker_id.split(",")[1],
    workInfo->product_id.split(",")[1],
    workInfo->instruction_id.split(",")[1]);
    this->query_ctl(s,"上报失败 ");
}
void database_server::remove_t() {
    int id = query.lastInsertId().toInt();
    if (!this->query_ctl("delete from spc_event where id = " + QString::number(id)).isActive()) {
        QSqlError error = query.lastError();
        QMessageBox box(QMessageBox::NoIcon,"mysql","删除上条上报信息失败" + error.databaseText(),NULL,NULL);
        box.exec();
    }
}
bool database_server::read_plantab(const QString& s,const QString& flag) {
    //read_producttab
    QString prod = "select * from producttab where productID = " + s;
    qDebug()<<prod;
    this->query_ctl(prod,"Plantab");
    producttab prod_t;
    if (query.size() == 0 || last_error == false) {return false;}
    while (query.next()) {
        prod_t.productID = query.value(1).toString();
        prod_t.productName = query.value(2).toString();
        prod_t.clientProductName = query.value(4).toString();
        prod_t.clientDrawingID = query.value(5).toString();
        prod_t.productState = query.value(6).toString();
        prod_t.clientVersion = query.value(16).toString();
        prod_t.ourDrawingID = query.value(17).toString();
        my_socket->sendmessage(48,prod_t);
    }




    QString q = "select * from plantab where left(PlanID,6)=" + s + " and PlanState = " +"'" + flag + "'";

    this->query_ctl(q,"Plantab");
     if (query.size() == 0 || last_error == false) {return false;}

    plantab planTab;
    plantab_size = query.size();
    my_socket->sendmessage(51,plantab_size);
    qDebug()<<q<<query.size();

    rec_plantab.resize(plantab_size);
    int cnt = 0;
    while(query.next()) {
        planTab.PlanID = query.value(0).toString();
        planTab.CreateTime = query.value(1).toString();
        planTab.CreateUser = query.value(2).toString();
        planTab.PlanEndDate = query.value(3).toString();
        planTab.ElseInf = query.value(4).toString();
        planTab.PlanCount = query.value(5).toString();
        planTab.EndCount = query.value(6).toString();
        planTab.PlanState = query.value(8).toString();
        planTab.IsRework = query.value(22).toString();
        planTab.cCappName = query.value(9).toString();
        //qDebug()<< planTab.PlanID ;
        rec_plantab[cnt++] = planTab;
        my_socket->sendmessage(50,planTab);
    }
    plantab_now = 0;
    planstep_now = 0;
    if (plantab_size > 0) {
        update_step();
    }
    return true;
}
bool database_server::read_producttab(const QString &s) {
    QString q =  "select * from producttab where productID = " + s;
    if (!query.exec()) {
        QSqlError error = query.lastError();
        QMessageBox box(QMessageBox::NoIcon,"mysql","Plantab" + error.databaseText(),NULL,NULL);
        box.exec();
    }
    while(query.next()) {

    }
}
bool database_server::update_step() {
    planstep_now = 0;
    QString temp_S = "select * from plansteptab where left(PlanStepID,18) = '" + rec_plantab[plantab_now].PlanID + "'" ;
    this->query_ctl(temp_S,"Plantab");
     if (query.size() == 0 || last_error == false) {return false;}
    qDebug()<<temp_S<<" "<<query.size();
    planstep_size = query.size();
    plansteptab plan_step_tab;
    int size_t = query.size();
    my_socket->sendmessage(53,size_t);
    while (query.next()) {
        plan_step_tab.PlanStepID = query.value(0).toString();
        plan_step_tab.cProcessIndex = query.value(2).toString();
        plan_step_tab.cProcessName = query.value(3).toString();
        plan_step_tab.cProcessDetail = query.value(4).toString();
        plan_step_tab.cWorkShop = query.value(5).toString();
        plan_step_tab.cWorkSection = query.value(6).toString();
        plan_step_tab.cDevice = query.value(7).toString();
        plan_step_tab.cProcessEquip = query.value(8).toString();
        plan_step_tab.cWorkHour = query.value(9).toString();
        plan_step_tab.cMustQC = query.value(12).toString();
        plan_step_tab.cStdCount = query.value(13).toString();
        plan_step_tab.cCountRatio = query.value(15).toString();
        my_socket->sendmessage(52,plan_step_tab);
    }
}
void database_server::add_tab(int flag) {//plantab下add
    if (flag == 0 && plantab_now < plantab_size - 1) {
        plantab_now++;
        int act = 0;
        my_socket->sendmessage(49,act);
        update_step();
    }
    else {
         my_socket->sendmessage(49,0);
    }
    qDebug()<<plantab_now;
}
void database_server::reducetab(int flag) {
    if (flag == 0 && plantab_now > 0) {
        plantab_now--;
        int act = 1;
        my_socket->sendmessage(49,act);
        update_step();
    }
    else {
        my_socket->sendmessage(49,1);
    }
    qDebug()<<plantab_now;
}
void database_server::add_steptab(int flag) {
    if (flag == 0 && planstep_now < planstep_size - 1) {
        planstep_now++;
        int act = 2;
        my_socket->sendmessage(49,act);
    }
    else {
        my_socket->sendmessage(49,2);
    }
}
void database_server::reducesteptab(int flag) {
    if (flag == 0 && planstep_now > 0) {
        planstep_now--;
        int act = 3;
        my_socket->sendmessage(49,act);

    }
    else {
        my_socket->sendmessage(49,3);
    }
}
QSqlQuery& database_server::query_ctl(const QString &s,const QString& error_s){
    if(!this->isActive()) {
        last_error = false;
        return query;
    }
    if (!query.exec(s)) {
        QSqlError error = query.lastError();
        QMessageBox box(QMessageBox::NoIcon,"mysql",error_s + error.databaseText(),NULL,NULL);
        box.exec();
    }
    else {
        last_error = true;
    }
    return query;
}
bool database_server::isActive() {
    std::string ping_cmd = "ping -c 1 " + plugin.hostname.toLatin1().toStdString() ;
    qDebug()<<QString(ping_cmd.c_str());
    int ret = system(ping_cmd.c_str());
    if (ret != 0) {
        qDebug()<<"当前网络不稳定";
        Mremind->show("当前网络不稳定");
    }
    else {
        if (!db.isOpen()) {//网络稳定，此时保证数据库已打开
            db.open();
        }
    }
    return ret == 0;
}
