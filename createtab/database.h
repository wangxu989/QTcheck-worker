#ifndef DATABASE_H
#define DATABASE_H

#include<QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QDomDocument>
#include<tab.h>
#include<dialog.h>
#include<QNetworkInterface>
#include<QTime>
//#include<socket.h>
class database
{
public:
    database(database_plugin& net_plugin,mytab& tab1,work_info& workInfo);
    database(work_info& workInfo,mytab &tab1);
    ~database();
    int flag = -1;//0员工信息不合法,1您无权访问此机器,2无对应工作信息
    void insert_data(const double &data,const int &flag,const int &operaton_flag);//

    void spc_event(QString type);

private:
    database_plugin plugin = {"127.0.0.1","0","MYDB","root","arm","0"};
    QSqlDatabase db,db_data;
    void createdatabase();
    void createtable();
    void read_data(mytab& tab);
    QSqlQuery query;
    work_info& workInfo;
    void insert_record();
    int last_insert_id;
    mytab &tab;
    QString mac_address;
};

#endif // DATABASE_H
