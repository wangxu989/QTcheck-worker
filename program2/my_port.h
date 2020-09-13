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
struct P_scanner{
    QString name;
    QString baudRate;
    QString dataBits;
    QString stopBits;
    QString parity;
    QString writeBufferSize;
    QString readBufferSize;
};
class my_port
{
public:
    my_port();
    ~my_port();
    QSerialPort *port1;
private:
    void lookup(void);
    void start_port();
    QString name;
    QSerialPortInfo my_info;
    P_scanner scanner;
};

#endif // MY_PORT_H
