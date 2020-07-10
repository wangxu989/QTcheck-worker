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
class my_tablewidget:public QTableWidget {
public:
    int row,column;
    my_tablewidget(const int &row,const int &column,const QString &info = ""):row(row),column(column){
        this->setColumnCount(column);
        this->setRowCount(row);
        this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        this->verticalHeader()->setHidden(true);
        this->horizontalHeader()->setHidden(true);
        for (int i = 0;i < row;i++) {
            for (int j = 0;j < column;j++) {
                this->setItem(i,j,new QTableWidgetItem());
                this->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
        }
        if (info.size()) {
            this->setSpan(0,0,1,this->columnCount());
            this->item(0,0)->setText(info);
        }
    }
};
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
    int flag[3] = {0};
    QByteArray code_scan;
    QVector<QString>string_scan;
    QString temp_scan;
    int check_first(const my_tablewidget &a,const my_tablewidget &b,const my_tablewidget &c,work_info& info);
private:
    void lookup(void);
    void start_port();
    QString name;
    QSerialPortInfo my_info;
    QSemaphore sem;
    P_scanner scanner;
};

#endif // MY_PORT_H
