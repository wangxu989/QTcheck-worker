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
    QString product_no;//产品号
    QString warn_thr;//预警阈值
    QString chk_warn_thr;//复核报警阈值
    QString detect_mode;//抽检方式
    QString time_interval;//抽检时间间隔
    QString cycle_time;//加工时间
    QString sample_cnt;//抽检件数单位
    QString disp_element_cnt;//屏幕展示个数
    QString  trend_warn_win;//趋势预警
    QString lock_time;//锁定时间
};
class tabinfo{
public:
    friend QDataStream& operator>>(QDataStream &os,tabinfo&a);
    QString gauge;
    QString featureid;//零件特性号
    QString char_desc;//特征描述(长宽，内径...)
    double normvalue;//规格值
    double zgc;//正公差
    double fgc;//负公差
    double jddw;//精度单位
    double ejjddw;//二级精度单位
    //int chk_warn_thr;//二级预警值
    //int warn_thr;//一级预警值
};
typedef struct {
    double x,y;
    volatile int tabnum;
} communication;
struct temp_xr{
    explicit temp_xr(uint s = 0,uint e = 0,uint n = 0):start(s),end(e),narrow(n){};
    uint start;
    uint end;
    uint narrow;
    void operator=(const temp_xr &a) {
        this->start = a.start;
        this->end = a.end;
        this->narrow = a.narrow;
    }
};
#pragma pack()
class socketclient:public QThread
{
    Q_OBJECT
public:
    explicit socketclient();//防止隐式匹配
    QVector<temp_xr>x_range;
    QDateTime time;
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
        out<<quint32(sizeof(flag) + sizeof(T))<<flag<<info;
        socket->write(data);
        socket->waitForBytesWritten();
    }
    message_worker_evn messageWorkerEnv;
     QLabel *label1;
     int check_flag[3] = {0};
     volatile int tabnum = 0;
signals:
    void insert_data(int);
    void plot_enlarge();
    void plot_narrow();
    void gauge_no(const QString* const);
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
    void warn_line(int n);
    QVector<QVector<double>>warn_y,warn_x;
    void add_fun();
};

#endif // SOCKETCLIENT_H
