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
    void sendmessage(int flag,void *content = NULL,const int num = 0,int column = 0,int user_ide = 0,const QString y = "",const QString x = "")const;
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
private slots:
    void read_message();
};

#endif // SOCKET_H
