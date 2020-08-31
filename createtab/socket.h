#ifndef SOCKET_H
#define SOCKET_H
#include"tab.h"
#include<QtNetwork>
//#include<dialog.h>
#include<QSemaphore>
#include<database.h>
class QLocalServer;
class QTcpServer;
class socket:public QObject
{
    Q_OBJECT
public:
    ~socket();
    socket();
    bool status() {return server->isListening();}
    //sendmessage有待改善，做成template
    //还是得用模板重写这个，太难看了
    template<typename T,typename...Types>
    quint32 size(T& t,Types&... types) {
        return size(types...) + sizeof(T);
    }
    int size() {return 0;}
    template<typename... Types>
    void sendmessage(int flag,const Types&... types) {
        QByteArray data;
        QDataStream out(&data,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_6);
        if (flag == 0) {
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
           //qDebug()<<flag<<"flag!!!!!!!!!!!!!!!!!!!!"<<s;
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
        clientConnection->write(data);
        clientConnection->waitForBytesWritten();

    }

    //void sendmessage(int flag,void *content = NULL,const int num = 0,int column = 0,int user_ide = 0,const QString y = "",const QString x = "")const;
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
private slots:
    void read_message();
};

#endif // SOCKET_H
