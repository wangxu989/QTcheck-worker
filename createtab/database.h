#ifndef DATABASE_H
#define DATABASE_H

#include<QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QDomDocument>
#include<tab.h>
//#include<mainwindow.h>
#include<QNetworkInterface>
#include<QTime>
#include<QMessageBox>
//#include<initializer_list>
#include<socket.h>
//重构数据库，单利模式
#pragma pack(1)
struct producttab{
    QString productID;
    QString productName;
    QString productState;
    QString clientProductName;
    QString clientDrawingID;
    QString ourDrawingID;
    QString clientVersion;
    friend QDataStream& operator<<(QDataStream& os,const producttab& p);
};

struct plansteptab{
    QString PlanStepID;
    QString cProcessIndex;
    QString  cProcessName;
    QString  cProcessDetail;
    QString  cWorkShop;
    QString cWorkSection;
    QString cDevice;
    QString cProcessEquip;
    QString cWorkHour;
    QString cMustQC;
    QString cStdCount;
    QString cCountRatio;
    friend QDataStream& operator<<(QDataStream& os,const plansteptab& p1);
};

struct plantab {
    QString PlanID;//计划号18位
    QString PlanCount;
    QString EndCount;
    QString PlanEndDate;
    QString PlanState;
    QString cCappName;
    QString ElseInf;//物料编码
    QString IsRework;
    QString CreateUser;
    QString CreateTime;
    friend QDataStream& operator<<(QDataStream& os,const plantab& p1);
};
#pragma pack()
typedef struct{
    QString hostname;
    QString port;
    QString databaseName;
    QString userName;
    QString passwd;
    QString status;
    //    friend QDataStream& operator<<(QDataStream &os,const struct network_plugin &a);
}database_plugin;
class database//数据库父类
{
public:
    database(database_plugin& p):plugin(p){};
    database()=default;
    ~database()=default;
    int flag = -1;//0员工信息不合法,1您无权访问此机器,2无对应工作信息
    work_info *workInfo;
    mytab *tab;
    static int last_insert_id;

protected:
    virtual bool connect_database()=0;
     database_plugin plugin = {"127.0.0.1","0","MYDB","root","arm","0"};
     QSqlDatabase db,db_data;
     QSqlQuery query;
};
class database_local:public database {//本地数据库
public:
    void insert_data(const double &data,const int &flag,const int &operaton_flag);
    bool connect_database() {
        db = QSqlDatabase::addDatabase("QSQLITE","local");
        db.setDatabaseName("./data/work_record");
        if (!db.open()) {
            QMessageBox box(QMessageBox::NoIcon,"sqlite","open filed!",NULL,NULL);
            box.exec();
            return false;
        }
        query = db.exec();
        return true;
    }
    database_local():database(){
        connect_database();
        createtable();//创建用于保存数据的本地数据库
//        insert_record();
    }
    ~database_local();
    void createtable();
    void insert_record();

};
class database_server:public database {//网络数据库

    //写一个控制器，读数据和传数据


public:
    void spc_event(QString type);

    void update_finish_time();

    void remove_t();
    bool connect_database() {
        db = QSqlDatabase::addDatabase("QMYSQL","network");
        createdatabase();
        //read_data();//首先读取client_cfg配置文件
        query = db.exec();
        return true;
    }
    database_server( database_plugin& p):database(p){
        connect_database();
    }
    ~database_server();
    void createdatabase();
    void read_data();
    bool read_plantab(const QString& s,const QString& flag);
    bool read_producttab(const QString &s);
    bool read__planstart2tab();
    bool update_step();
    void add_steptab();
    void add_tab();
    void reducetab();
    void reducesteptab();
private:
    int plantab_size;
    int plantab_now = 0;
    int planstep_size;
    int planstep_now = 0;
    QVector<plantab>rec_plantab;
    QString mac_address;
};


#endif // DATABASE_H
