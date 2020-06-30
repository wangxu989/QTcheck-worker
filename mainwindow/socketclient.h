#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H
#include <QDialog>
#include <QDataStream>
#include <QLocalSocket>
#include <QtNetwork>
#include"qcustomplot.h"
#include<QThread>
#include<QSemaphore>
#include<QLinearGradient>
#pragma pack(1)
typedef struct {

}SB;
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



class infomation{
public:
    friend QDataStream& operator>>(QDataStream &os,infomation &a);
    QString id;//产品号
    QString value0;//预警阈值
    QString value1;//复核报警阈值
    QString value2;//抽检方式
    QString value3;//抽检时间间隔
    QString value4;//加工时间
    QString value5;//抽检件数单位
    QString value6;//屏幕展示个数
};
class tabinfo{
public:
    friend QDataStream& operator>>(QDataStream &os,tabinfo&a);
    QString featureid;//零件特性号
    double normvalue;//规格值
    double zgc;//正公差
    double fgc;//负公差
    double jddw;//精度单位
    double ejjddw;//二级精度单位
    int chk_warn_thr;
    int warn_thr;
};
typedef struct {
    double x,y;
    volatile int tabnum;
} communication;
#pragma pack()
class socketclient:public QThread
{
    Q_OBJECT
public:
    explicit socketclient();//防止隐式匹配
    ~socketclient();
    infomation info;
    QVector<tabinfo>createinfo;
    QCustomPlot *pCustomPlot = new QCustomPlot();
    int count = 0;
    volatile bool stop;
    template <typename T>
    void send_message(const int &flag,const T &info) const{
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_6);
        switch (flag) {
        //    case 0:
        //        out<<quint32(sizeof(flag) + sizeof(info))<<flag<<info;
        //        break;
        case 1:
            out<<quint32(sizeof(flag) + sizeof(T))<<flag<<info;//审核员
            break;
        case 2:
            out<<quint32(sizeof(flag) + sizeof(T))<<flag<<info;//员工
            qDebug()<<info;
            break;
        case 3:
            out<<quint32(sizeof(flag)+sizeof(T))<<flag<<info;//指令
            qDebug()<<info;
            break;
        case 4:
            out<<quint32(sizeof(flag)+sizeof(T))<<flag<<info;//设备
            break;
        }
        socket->write(data);
        socket->waitForBytesWritten();
    }
    message_worker_evn messageWorkerEnv;
     QLabel *label1;
     int check_flag[3] = {0};
     volatile int tabnum = 0;
signals:
    void insert_data(int);
protected:
    void run();
public slots:
    void readmessage();
    void displayError(QLocalSocket::LocalSocketError socketError);
private:
    QDataStream in;
    quint32 blockSize = 0;
    QTcpSocket *socket;
    //QLocalSocket *socket;
    void initpcustomplot(int num);
    QQueue<communication>temp;
    QVector<QVector<double> >x;
    QVector<QVector<double> >y;
    double t;
    QSemaphore sem;
    int user_ide;
};

#endif // SOCKETCLIENT_H
