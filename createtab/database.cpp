#include "database.h"
#include<QFile>
#include<QSqlError>
#include<QMessageBox>
database::database(database_plugin& net_plugin,mytab& tab1,work_info& Info):plugin(net_plugin),tab(tab),workInfo(Info)//网络版
{
    db = QSqlDatabase::addDatabase("QMYSQL","network");
    createdatabase();
    read_data(tab);//首先读取client_cfg配置文件
}
database::database(work_info& Info,mytab &tab1):workInfo(Info),tab(tab1)//保存本地工作信息
{
    db = QSqlDatabase::addDatabase("QSQLITE","local");
    db.setDatabaseName("word_record");
    if (!db.open()) {
        QMessageBox box(QMessageBox::NoIcon,"sqlite","open filed!",NULL,NULL);
        box.exec();
    }
    query = db.exec();
    //createdatabase();
    createtable();//创建用于保存数据的本地数据库
    insert_record();
}
database::~database() {

}

void database::createdatabase() {
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
void database::read_data(mytab& tab) {//读取远程数据库中工作信息
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
    query.exec(temp);
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
        query.exec("select * from auth_user where user_id = " + workInfo.worker_id.split(",")[workInfo.worker_id.split(",").size() - 1]);
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
        QString find_work = workInfo.instruction_id.split(",")[workInfo.instruction_id.split(",").size() - 1];//暂定
        query.prepare("select * from spc_schemes where product_no = ?");
        query.bindValue(0,find_work);
        query.exec();
        int row_count = query.size();
        qDebug()<<row_count;
        if (row_count == 0) {
            QMessageBox box(QMessageBox::NoIcon,"title","无对应工作信息",NULL,NULL);
            box.exec();
            flag = 2;
            return;
        }
        while (query.next()) {
            tab.info.product_no = query.value(1).toString();
            tab.info.warn_thr = query.value(9).toString();
            tab.info.chk_warn_thr = query.value(10).toString();
            tab.info.detect_mode = query.value(11).toString();
            tab.info.time_interval = query.value(12).toString();
            tab.info.cycle_time = query.value(13).toString();
            tab.info.sample_cnt = query.value(14).toString();
            tab.info.disp_element_cnt = query.value(15).toString();
            tab.info.trend_warn_win = query.value(16).toString();
            tab.info.lock_time = query.value(17).toString();
            tab.my.x.resize(row_count);
            tab.my.y.resize(row_count);
            tabinfo temp;
            temp.featureid = query.value(2).toString();
            temp.char_desc = query.value(3).toString();
            temp.normvalue =query.value(4).toDouble();
            temp.zgc = query.value(5).toDouble();
            temp.fgc = query.value(6).toDouble();
            temp.jddw = query.value(7).toDouble();
            temp.ejjddw = query.value(8).toDouble();
            tab.createinfo.push_back(temp);
            tab.tabadd(temp,tab.info);
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
void database::createtable() {
    //work_record
    if (!query.exec("create table if not exists local_work_record(id integer primary key AUTOINCREMENT,"//记录号
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
        ;
    if (!query.exec("create table if not exists local_measure_data(id integer primary key AUTOINCREMENT,"//记录号
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
               "CONSTRAINT linkkey FOREIGN KEY(work_id) REFERENCES local_work_record(id) on delete cascade on update cascade)")) {//零件流水号
        QMessageBox box(QMessageBox::NoIcon,"mysql","本地数据库local_measure_data创建失败",NULL,NULL);
        box.exec();

    };

}
void database::insert_record() {

    query.prepare("insert into local_work_record (user_id,start_time,finish_time,"
               "work_state,produce_id,equip_id,workstation,gauge_no)"
               "values(?,?,?,?,?,?,?,?)");
    query.bindValue(0,workInfo.worker_id.split(",")[1].mid(0,6));
    QDateTime time = QDateTime::currentDateTime();
    QString n = time.toUTC().toString();
    qDebug()<<n;
    query.bindValue(1,n);
    query.bindValue(2,"");
    query.bindValue(3,'0');
    query.bindValue(4,workInfo.instruction_id.split(",")[1].mid(0,10));
    query.bindValue(5,workInfo.product_id.split(",")[1].mid(0,10));
    query.bindValue(6,tab.messageWorkerEvn.localEnv.workstation);
    query.bindValue(7,tab.messageWorkerEvn.localEnv.gauge_no);
    if (!query.exec()) {
        QSqlError error = query.lastError();
        qDebug()<<error.databaseText();
        QMessageBox box(QMessageBox::NoIcon,"mysql","本地数据库local_record插入失败" + error.databaseText(),NULL,NULL);
        box.exec();
    }
    last_insert_id = query.lastInsertId().toInt();
}
void database::insert_data(const double &data,const  int &flag,QString &work_time,tabinfo &tabinfo) {
    QDateTime now = QDateTime::currentDateTime();
    query.prepare("insert into local_measure_data (work_id,gauge_no,measure_time,measure_value,"
                  "checker,chk_time,chk_value,meas_rlt_id,chk_rlt,char_id,element_SD)"
                  "values(?,?,?,?,?,?,?,?,?,?,?");
    query.bindValue(0,last_insert_id);
    query.bindValue(1,now.toString());
    query.bindValue(2,tab.messageWorkerEvn.localEnv.gauge_no);
    query.bindValue(3,QString::number(data));
    query.bindValue(4,"");
    query.bindValue(5,"");
    query.bindValue(6,"");
    query.bindValue(7,flag);
    query.bindValue(8,"");
    query.bindValue(9,tabinfo.featureid);
    query.bindValue(10,0);
    if (!query.exec()) {
        QSqlError error = query.lastError();
        qDebug()<<error.databaseText();
        QMessageBox box(QMessageBox::NoIcon,"mysql","本地数据库local_record插入失败" + error.databaseText(),NULL,NULL);
        box.exec();
    }
}
void database::spc_event(QString type) {
    QDateTime now = QDateTime::currentDateTime();
    query.prepare("insert into spc_event (client_id,event_time,event_type,user_id,equip_id,work_id)"
                  "values(?,?,?,?,?,?)");
    query.bindValue(0,mac_address);
    query.bindValue(1,now.toString());
    query.bindValue(2,type);
    query.bindValue(3,workInfo.worker_id);
    query.bindValue(4,workInfo.product_id);
    query.bindValue(5,workInfo.instruction_id);
}
