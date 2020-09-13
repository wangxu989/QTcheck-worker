#ifndef SOCKET_H
#define SOCKET_H
#include<QtNetwork>
#include<QDataStream>
#pragma pack(1)
struct producttab{
    QString productID;
    QString productName;
    QString productState;
    QString clientProductName;
    QString clientDrawingID;
    QString ourDrawingID;
    QString clientVersion;
    friend QDataStream& operator >>(QDataStream& os,producttab& p);
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
    friend QDataStream& operator>>(QDataStream& os,plansteptab& p1);
    QString& operator[](const int n)const {
        return *(QString*)((void *)this + sizeof(QString)*n);
    }
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
    friend QDataStream& operator>>(QDataStream& os,plantab& p1);
    QString& operator[](const int n)const {
        return *(QString*)((void *)this + sizeof(QString)*n);
    }
};
#pragma pack()
class socket:public QTcpSocket
{
    Q_OBJECT
public:
    socket();
    template<typename T>
    void send_message(int flag,T t1) {
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_6);
        out<<quint32(sizeof(flag) + sizeof(t1))<<flag<<t1;
        write(data);
        waitForBytesWritten();
    }

private:
    QDataStream in;
    quint32 blockSize = 0;
    QString ip;
private slots:
    void read_msg();
signals:
    void insert_plantab(plantab *);
    void set_plantab_size(int,int);
    void insert_plansteptab(plansteptab *);
    void insert_producttab(producttab*);
    void act_mode(int);
    void send_printString();
    void qrecode_show();
};

#endif // SOCKET_H
