#ifndef MY_PORT_H
#define MY_PORT_H
#include<QSerialPort>
#include<QDebug>
#include<QSerialPortInfo>
#include<QTableWidget>
#include<QHeaderView>
#include<QSemaphore>
#include<socketclient.h>
#include<QtXml/QDomDocument>
#include<QFile>
#include<QMessageBox>
#include<qmessage_remind.h>
struct P_scanner{
    QString name;
    QString baudRate;
    QString dataBits;
    QString stopBits;
    QString parity;
    QString writeBufferSize;
    QString readBufferSize;
};
//class my_SerialPort :public QSerialPort{

//};

class my_port:QObject
{
    Q_OBJECT
public:
    my_port();
    ~my_port();
    QSerialPort *port1;
    void write(const QString& s);
private:
    enum Except{
        WRITE,
        READ
    };

    void lookup(void);
    void start_port();
    QString name;
    QSerialPortInfo my_info;
    QSemaphore sem;
    P_scanner scanner;
    bool exception(const Except& e);
    bool find_port();
    message_remind* Mremind = message_remind::get_Mremind();
};

#endif // MY_PORT_H
