#include "socket.h"
#include<QAbstractSocket>
#include<QFile>
QDataStream& operator<<(QDataStream &os,infomation &a) {
    os<<a.product_no;
    os<<a.warn_thr;
    os<<a.chk_warn_thr;
    os<<a.detect_mode;
    os<<a.time_interval;
    os<<a.cycle_time;
    os<<a.sample_cnt;
    os<<a.disp_element_cnt;
    os<<a.trend_warn_win;
    os<<a.lock_time;
    return os;
}
QDataStream& operator<<(QDataStream &os,tabinfo &a) {
    os<<a.featureid;
    os<<a.normvalue;
    os<<a.zgc;
    os<<a.fgc;
    os<<a.jddw;
    os<<a.ejjddw;
    os<<a.gauge;
    //os<<a.chk_warn_thr;
    //os<<a.warn_thr;
    os<<a.char_desc;
    return os;
}
socket::~socket(){
    //clientConnection->disconnectFromServer();
    clientConnection->disconnectFromHost();
}
socket::socket()
{
    server = new QTcpServer(this);
    QFile file("./data/ip");
    file.open(QIODevice::ReadOnly);
    QString ip = file.read(15);
    qDebug()<<ip;
    if (!server->listen(QHostAddress(ip),6666)) {
        QMessageBox box;
        box.setText("server listen failed!" + server->errorString());
        box.exec();
        return;
    }
    connect(server,&QTcpServer::newConnection,this,&socket::my_connection);//通过信号链接
    //server = new QLocalServer(this);
    //QLocalServer::removeServer("f3");
//    if (!server->listen("f3")) {
//        qDebug()<<"listen error";
//    }
//    else {
//        qDebug()<<"listening";
//    }
    //connect(server,&QLocalServer::newConnection,this,&socket::my_connection);//通过信号链接
    //connect(server,SIGNAL(acceptError(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
}
void socket::my_connection() {
    clientConnection = server->nextPendingConnection();
    //connect(clientConnection,&QLocalSocket::readyRead,this,&socket::read_message);
     connect(clientConnection,&QTcpSocket::readyRead,this,&socket::read_message);
    qDebug()<<"connected";
}
void socket::read_message() {
    qDebug()<<"read";
    QDataStream in;
    int flag;
    in.setDevice(clientConnection);
    in.setVersion(QDataStream::Qt_5_6);
    if (blocksize == 0) {
        if (clientConnection->bytesAvailable() < (long)sizeof(quint32)) {
            return;
        }
        in>>blocksize;
    }
    if (clientConnection->bytesAvailable() < blocksize||in.atEnd()) {
        return;
    }
    blocksize = 0;
    in>>flag;
//    qDebug()<<flag<<"flag";
//    qDebug()<<blocksize<<"blocksize";
    switch (flag) {
//    case 0:
//        qDebug()<<"ok";
//        in>>workInfo;
//        emit start_work();//发出信号
//        break;
    case 1:
        in>>workInfo.checker_id;
        qDebug()<<"signal check_ide";
        emit check_identity();
        break;
    case 2:
        in>>workInfo.worker_id;
        qDebug()<<workInfo.worker_id;
        emit check_info(1);
        break;
    case 3:
        in>>workInfo.instruction_id;
        emit check_info(2);
        break;
    case 4:
        in>>workInfo.product_id;
        emit check_info(3);
        break;
    }
    if (clientConnection->bytesAvailable() > 0) {
        emit clientConnection->readyRead();
    }
}
void socket::sendmessage(int flag,void *content,int num,int column,int user_ide,QString y,QString x)const {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_6);
    qDebug()<<"发送";
    switch(flag) {
    case 0://产品信息和工作信息
        qDebug()<<quint32(sizeof(*info) + sizeof((*createinfo).size()) + sizeof(*createinfo) + sizeof(flag));
        out << quint32(sizeof(*info) + sizeof((*createinfo).size()) + sizeof((*createinfo).size()*sizeof(tabinfo)) + sizeof(flag));
        out<<flag;
        out<<*info;
        out<<(*createinfo).size();
        for (int i= 0;i < (*createinfo).size();i++) {
            out<<(*createinfo)[i];
        }
        break;
    case 1://TAB切换
        qDebug()<<num;
        out<<quint32(sizeof(num) + sizeof(flag));
        out<<flag;
        out<<num;
        break;
    case 2://增加点坐标信息
        out<<quint32(sizeof(y)+sizeof(x)+sizeof(flag) + sizeof(num) + sizeof(column) + sizeof(user_ide));
        out<<flag;
        out<<num;
        out<<column;
        out<<y;
        out<<x;
        out<<user_ide;
        qDebug()<<QDateTime::currentDateTime().toTime_t();
        break;
    case 3://删除点坐标信息（修改中的删除操作）
        out<<quint32(sizeof(flag) + sizeof(num) + sizeof(column) + sizeof(user_ide));
        out<<flag;
        out<<num;
        out<<column;
        out<<user_ide;
        break;
    case 4://请求进程2使用扫码枪验证登录信息
        //out<<quint32(sizeof(flag));
        break;
    case 5://发送员工信息和设备信息
        out<<quint32(sizeof(flag) + sizeof(worker_info));
        out<<flag;
        out<<*(worker_info *)content;
        break;
     case 6:
        out<<quint32(sizeof(flag) + sizeof(local_env));
        out<<flag;
        out<<*(local_env *)content;
        break;
     case 7:
        out<<quint32(sizeof(flag) + sizeof(Equip));
        out<<flag;
        out<<*(Equip *)content;
        break;
     case 8://无用户信息
        out<<quint32(sizeof(flag));
        out<<flag;
        break;
     case 9://无工作信息
       out<<quint32(sizeof(flag));
       out<<flag;
        break;
     case 10://无指令信息
        out<<quint32(sizeof(flag));
        out<<flag;
        break;
     case 11://放大
        out<<quint32(sizeof(flag));
        out<<flag;
     case 12://缩小
        out<<quint32(sizeof(flag));
        out<<flag;
     case 13://增加gauge_no
        out<<quint32(sizeof(flag) + sizeof(int) + sizeof(QString));
        out<<flag<<num;
        out<<(*createinfo)[num].gauge;
        qDebug()<<(*createinfo)[num].gauge;
    }
    //    data.resize(sizeof(*info));
    //    memcpy(data.data(),info,sizeof(*info));
//    out.device()->seek(0);
//    out<<(quint32)(data.size() - sizeof(quint32));
    clientConnection->write(data);
    clientConnection->waitForBytesWritten();
    //clientConnection->flush();
    //clientConnection->disconnectFromServer();
}
void socket::delete_connect() {

}
void socket::sendpoit() {
    //clientConnection->write();
}
void socket::displayError(QAbstractSocket::SocketError) const {

}
