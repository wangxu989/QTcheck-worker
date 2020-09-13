#include "socket.h"
#include<QFile>
QDataStream& operator>>(QDataStream& os,producttab& p) {
    os>>p.productID;
    os>>p.productName;
    os>>p.productState;
    os>>p.clientProductName;
    os>>p.clientDrawingID;
    os>>p.ourDrawingID;
    os>>p.clientVersion;
    return os;
}
QDataStream& operator>>(QDataStream& os,plansteptab& p1) {
    os>>p1.PlanStepID;
    os>>p1.cProcessIndex;
    os>>p1.cProcessName;
    os>>p1.cProcessDetail;
    os>>p1.cWorkShop;
    os>>p1.cWorkSection;
    os>>p1.cDevice;
    os>>p1.cProcessEquip;
    os>>p1.cWorkHour;
    os>>p1.cMustQC;
    os>>p1.cStdCount;
    os>>p1.cCountRatio;
    return os;
}
QDataStream& operator>>(QDataStream& os, plantab& p1) {
    os>>p1.PlanID;//计划号18位
    os>>p1.PlanCount;
    os>>p1.EndCount;
    os>>p1.PlanEndDate;
    os>>p1.PlanState;
    os>>p1.cCappName;
    os>>p1.ElseInf;//物料编码
    os>>p1.IsRework;
    os>>p1.CreateUser;
    os>>p1.CreateTime;
    return os;
}
socket::socket()
{
    in.setDevice(this);
    in.setVersion(QDataStream::Qt_5_6);
//    QFile file("./data/ip");
//    file.open(QIODevice::ReadOnly);
    //QString ip = file.read(15);
    ip = "127.0.0.1";
    this->connectToHost(QHostAddress(ip),6666);
    if (this->waitForConnected()) {
        qDebug()<<"connected";
    }
    else {
        qDebug()<<"connect failed";
    }
    connect(this,&QTcpSocket::readyRead,this,&socket::read_msg);
    this->setReadBufferSize(1024*100);
}
void socket::read_msg(){
    int flag;
    if (blockSize == 0) {
        if (this->bytesAvailable() < (long)sizeof(quint32)) {
            return;
        }
        in>>blockSize;
    }
    if(this->bytesAvailable() < blockSize || in.atEnd()) {
        return;
    }
    blockSize = 0;
    in>>flag;
    if (flag == 50) {//按概率从高到低
        plantab tab;
        in>>tab;
        //qDebug()<<tab.IsRework;
        emit insert_plantab(&tab);
    }
    else if (flag == 51) {
        int size;
        in>>size;
        qDebug()<<size;
        emit set_plantab_size(1,size);
    }
    else if (flag == 52) {
        plansteptab t;
        in>>t;
        emit insert_plansteptab(&t);
    }
    else if (flag == 53) {
        int size;
        in>>size;
        qDebug()<<size;
        emit set_plantab_size(2,size);
    }
    else if (flag == 49) {
        int mode;
        in>>mode;
        qDebug()<<"act   "<<mode;
        emit act_mode(mode);
    }
    else if (flag == 48) {
        producttab p;
        in>>p;
        emit insert_producttab(&p);
    }
    else if (flag == 47) {
        emit send_printString();
    }
    else if (flag == 54) {
        emit qrecode_show();
    }
    if (this->bytesAvailable() > 0) {
        emit this->readyRead();
    }
}
