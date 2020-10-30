#ifndef SOCKET_H
#define SOCKET_H
#include<QtNetwork>
#include<QDataStream>
#include<my_tables.h>
typedef struct worker_info{
    QString name;
    int role;
    friend QDataStream& operator >> (QDataStream &os,worker_info &workInfo);
}worker_info;
typedef struct local_env{
    QString process;
    QString process_id;
    QString workstation;
    QString gauge_no;
    friend QDataStream& operator >> (QDataStream &os,local_env &localEnv);
}local_env;

typedef struct Equip{
    QString test_place;
    QString equip;
     friend QDataStream& operator >> (QDataStream &os,Equip & equip );
}Equip;
typedef struct message_worker_evn{
    worker_info workerInfo;
    local_env localEnv;
    Equip equip;
    friend QDataStream& operator >> (QDataStream &os,message_worker_evn &messageWorkerEnv);
}message_worker_evn;
typedef struct work_info{
    QString worker_id;
    QString product_id;
    QString instruction_id;
    friend QDataStream& operator<<(QDataStream &os,const struct work_info &info);
}work_info;

struct ProcessInf {
    QString cMustQC;
    QString cStdCount;
    QString ElseInf;
    friend QDataStream& operator >> (QDataStream& in,ProcessInf& Processinfo);
};

struct start_work{
    QString ID;
    QString EndTime;
    QString MaterialInf;
    QString StartUser;
    QString EndCount;
    QString ModeList;
    QString StartTime;
    QString DevID;
    QString remaind_count;
    friend QDataStream& operator>>(QDataStream& os,start_work& s);
    friend QDataStream& operator<<(QDataStream& os,const start_work& s);
    QString& operator[](int i) {
        return *static_cast<QString*>((void *)this + i*sizeof(QString));
        //return *(QString*)((void *)this + sizeof(QString)*i);
    }
};

struct finish_work{
    QString ID;
    QString EndTime;
    QString MaterialInf;
    QString EndCount;
    QString onhand;//待处理
    QString probatch;//产品批次
    QString isPrint;
    QString residueNum;//剩余数量
    friend QDataStream& operator>>(QDataStream& os,finish_work& s);
    QString& operator[](int i) {
        return *static_cast<QString*>((void *)this + i*sizeof(QString));
        //return *(QString*)((void *)this + sizeof(QString)*i);
    }
};
struct ElseInf {
    QString ID;
    QString EndTime;
    QString MaterialInf;
    QString UserID;
    QString EndCount;
    QString probatch;//产品批
    QString residueNum;//剩余数量
    friend QDataStream& operator>>(QDataStream& os,ElseInf& s);
    QString& operator[](int i) {
        //return *static_cast<QString*>((void *)this + i*sizeof(QString));
        return *(QString*)((void *)this + sizeof(QString)*i);
    }
};
class socket:public QTcpSocket
{
    Q_OBJECT
public:
    socket();
    template<typename T>
    void send_message(int flag,const T& t1) {
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_6);
        out<<quint32(sizeof(flag) + sizeof(t1))<<flag<<t1;
        write(data);
        waitForBytesWritten();
    }
    message_worker_evn messageWorkerEnv;
     int check_flag[4] = {0};
     volatile int tabnum = 0;
     ProcessInf Proinf;
     bool get_status() const {return status;}
signals:
    void insert_data(int);
    void set_tablesize(int,int);
    void act_mode(int);
    void change_status();
    void send_rec_code(ElseInf&);
    void confirm();
    void change_table();
    void delete_mes();
    void clear_tables();
    void confrim_finish(ElseInf&);
    void finish_save();
public slots:
    void read_msg();


private:
    QDataStream in;
    quint32 blockSize = 0;
    QString ip;
    start_work startInf;
    int size;
    finish_work finishInf;
    int mode;
    ElseInf elseinf;
    bool status = true;//开工/完工状态
    QString temp;
};

#endif // SOCKET_H
