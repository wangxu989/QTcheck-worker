#ifndef SOCKET_H
#define SOCKET_H
#include"tab.h"
#include<QtNetwork>
//#include<ProgramWork.h>
#include<QSemaphore>
//#include<database.h>
#include<qmessage_remind.h>
struct ProcessInf {
    QString cMustQC;
    QString cStdCount;
    QString ElseInf;
    //QString ElseInf;
    friend QDataStream& operator << (QDataStream& os,const ProcessInf& Processinfo);
};
struct start_rec{
    QString ID;
    QString EndTime;
    QString MaterialInf;
    QString StartUser;
    QString EndCount;
    QString StartTime;
    QString DevID;
    QString ModeList;
    QString remaind_count;
    friend QDataStream& operator<<(QDataStream& os,const start_rec& s);
    friend QDataStream& operator>>(QDataStream& os,start_rec& s);
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
    friend QDataStream& operator<<(QDataStream& os,const finish_work& s);
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
    friend QDataStream& operator<<(QDataStream& os,const ElseInf& s);
    QString& operator[](int i) {
        return *static_cast<QString*>((void *)this + i*sizeof(QString));
        //return *(QString*)((void *)this + sizeof(QString)*i);
    }
};
class QLocalServer;
class QTcpServer;
class socket:public QObject
{
    Q_OBJECT
public:
    static socket* get_socket() {
        if (my_socket == nullptr) {
            my_socket = new socket();
        }
        return my_socket;
    }

    ~socket();
    bool status() {return server->isListening();}
    //sendmessage有待改善，做成template.      已改进
    //还是得用模板重写这个，太难看了
    template<typename T,typename...Types>
    quint32 size(const T& t,const Types&... types) {
        return size(types...) + sizeof(T);
    }
    quint32 size() {return 0;}
    template<typename... Types>
    void sendmessage(quint32 flag,const Types&... types) {
        if (!this->clientConnection->isValid()) {
            Mremind->show("与客户端链接断开");
            return;
        }
        QByteArray data;
        QDataStream out(&data,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_6);
        if (flag == 0) {//
            qDebug()<<quint32(sizeof(*info) + sizeof((*createinfo).size()) + sizeof(*createinfo) + sizeof(flag));
            out << quint32(sizeof(*info) + sizeof((*createinfo).size()) + sizeof((*createinfo).size()*sizeof(tabinfo)) + sizeof(flag));
            out<<flag;
            out<<*info;
            out<<(*createinfo).size();
            for (int i= 0;i < (*createinfo).size();i++) {
                out<<(*createinfo)[i];
            }
            clientConnection->write(data);
            clientConnection->waitForBytesWritten();
        }
        else {
            quint32 s = size(types...) + sizeof(flag);
            qDebug()<<flag<<"flag!!!!!!!!!!!!!!!!!!!!"<<s + sizeof(s);
            out<<s<<flag;
            send(data,out,types...);
        }
    }

    template<typename T,typename... Types>
    void send(QByteArray& data,QDataStream& out,const T& t,const Types&... types) {
        out<<t;
        send(data,out,types...);
    }


    void send(QByteArray& data,QDataStream& out) {
        qDebug()<<data.size();
        clientConnection->write(data);
        clientConnection->waitForBytesWritten();
    }
    infomation *info;
    QVector<tabinfo> *createinfo;
    int rule;//0为传createinfo和info,1传tab切换信息,2传point
    //QLocalSocket *clientConnection = NULL;
    QTcpSocket *clientConnection = NULL;
    work_info workInfo = {"YG,2294","SB,001073","ZL,20016101180122000101,171216",""};
    bool bind();

signals:
    void start_work();
    void check_identity();
    void check_info(int);
    void print_String(QString&);
    void transf_processID(QString&s);
    void deal_rec(QString&s);
    void delete_start2tab(QString&s);
    void add_start2tab(start_rec&s);
public slots:
    void my_connection();
    void delete_connect();
    void sendpoit();
    void displayError(QAbstractSocket::SocketError)const ;
private:
    QTcpServer *server;
    //QLocalServer *server;
    int blocksize = 0;
    //QMap<QString,QTcpSocket*>client_C;
    QString ip;
    QString print;
    QString pro_rec;
    QString start2tabID;
    start_rec startrec;
    message_remind *Mremind = message_remind::get_Mremind();
    socket();
    static socket* my_socket;

private slots:
    void read_message();
};

#endif // SOCKET_H
