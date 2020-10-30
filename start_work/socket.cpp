#include "socket.h"
QDataStream& operator >> (QDataStream &os,Equip &equip){
    os>>equip.test_place;
    os>>equip.equip;
    return os;
}
QDataStream& operator >> (QDataStream &os,worker_info &workInfo) {
    os>>workInfo.name;
    os>>workInfo.role;
    return os;
}
QDataStream& operator >> (QDataStream &os,local_env &localEnv){
    os>>localEnv.process;
    os>>localEnv.process_id;
    os>>localEnv.workstation;
    os>>localEnv.gauge_no;
    return os;
}
QDataStream& operator >> (QDataStream &os,message_worker_evn &messageWorkerEnv) {
    os>>messageWorkerEnv.workerInfo;
    os>>messageWorkerEnv.localEnv;
    return os;
}

QDataStream& operator>>(QDataStream& os,start_work& s){
    os>>s.ID>>s.EndTime>>s.MaterialInf>>s.StartUser>>s.EndCount>>s.ModeList>>s.StartTime>>s.DevID>>s.remaind_count;
    return os;
}
QDataStream& operator<<(QDataStream& os,const start_work& s){
    os<<s.ID<<s.EndTime<<s.MaterialInf<<s.StartUser<<s.EndCount<<s.ModeList<<s.StartTime<<s.DevID<<s.remaind_count;
    return os;
}

QDataStream& operator>>(QDataStream& os,finish_work& s){
    os>>s.ID>>s.EndTime>>s.MaterialInf>>s.EndCount>>s.onhand>>s.probatch>>s.isPrint>>s.residueNum;
    return os;
}

QDataStream& operator>>(QDataStream& in,ProcessInf& Processinf) {//获取plansteptab中的开工相关信息
    in>>Processinf.cMustQC>>Processinf.cStdCount>>Processinf.ElseInf;
    return in;
}

QDataStream& operator>>(QDataStream& os,ElseInf& inf) {//获取plansteptab中的开工相关信息
    os>>inf.ID>>inf.EndTime>>inf.MaterialInf>>inf.UserID>>inf.EndCount>>inf.probatch>>inf.residueNum;
    return os;
}

QQueue<start_work>q_startwork;
QQueue<finish_work>q_finishwork;
socket::socket()
{
    ip = "127.0.0.1";
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
    qDebug()<<"read";
    if (blockSize == 0) {
        if (this->bytesAvailable() < (long)sizeof(quint32)) {
            qDebug()<<"data small";
            return;
        }
        in>>blockSize;
        qDebug()<<blockSize<<" "<<this->bytesAvailable();
    }
    if(this->bytesAvailable() < blockSize || in.atEnd()) {
//        if (this->bytesAvailable() > 0) {
//            qDebug()<<blockSize<<" "<<this->bytesAvailable();
//            emit this->readyRead();
//        }
        return;
    }
    blockSize = 0;
    in>>flag;
    switch (flag) {
    case 5:
        in>>messageWorkerEnv.workerInfo;
        qDebug()<<messageWorkerEnv.workerInfo.name;
        emit insert_data(1);
        break;
    case 7:
        in>>messageWorkerEnv.equip;
        qDebug()<<messageWorkerEnv.equip.test_place;
        emit insert_data(3);
        break;

    case 8:
        emit insert_data(4);
        check_flag[0] = 0;
        break;
    case 9:
        emit insert_data(5);
        check_flag[1] = 0;
        break;
    case 10:
        emit insert_data(6);
        check_flag[2] = 0;
        break;
    case 49:
        in>>mode;
        qDebug()<<"act   "<<mode;
        emit act_mode(mode);
        break;
    case 80://开工记录
        in>>startInf;
        q_startwork.push_back(startInf);
        emit insert_data(7);
        break;
    case 81://完工记录
        in>>finishInf;
        q_finishwork.push_back(finishInf);
        emit insert_data(8);
        break;
    case 82:
        in>>size;
        emit set_tablesize(1,size);
        break;
    case 83:
        in>>size;
        emit set_tablesize(2,size);
        break;
    case 84:
        qDebug()<<Proinf.cMustQC<<"cMustqc";
        in>>Proinf;
        emit insert_data(2);
        break;
    case 85:
        emit change_status();
        break;
    case 86:
        in>>elseinf;
        emit send_rec_code(elseinf);
        break;
    case 87://开工确认
        emit confirm();
        break;
    case 88:
        emit change_table();
        break;
    case 89:
        emit delete_mes();
        break;
    case 90:
        status = false;//完工
        my_tablewidget::clear_all();
        break;
    case 91:
        status = true;//开工
        my_tablewidget::clear_all();
        break;
    case 92:
        in>>temp;
        my_tablewidget::insert("物料信息",temp);
        in>>temp;
        my_tablewidget::insert("设备",temp);
        break;
    case 93://完工确认
        in>>elseinf;
        emit confrim_finish(elseinf);
        break;
    case 94:
        emit finish_save();
        break;
    }

    if (this->bytesAvailable() > 0) {
        emit this->readyRead();
    }
}
