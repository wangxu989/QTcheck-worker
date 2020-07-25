#ifndef DIALOG_H
#define DIALOG_H
#include<QPair>
#include <QDialog>
#include<QPushButton>
#include<QHBoxLayout>
#include<QMap>
#include<QVBoxLayout>
namespace Ui {
class Dialog;
}
class my_button : public QPushButton {
    Q_OBJECT
public:
    static int num;
    static void init_num() {
        static int num = 0;
    }
private:
signals:
    //void clicked(int num);
};

typedef  struct serialport{
    QString portName;
    QString baudRate;
    QString dataBits;
    QString stopBits;
    QString parity;
    QString writeBufferSize;
    QString readBufferSize;
}serialport_info;
typedef struct{
    QString hostname;
    QString port;
    QString databaseName;
    QString userName;
    QString passwd;
    QString status;
    //    friend QDataStream& operator<<(QDataStream &os,const struct network_plugin &a);
}database_plugin;
class Dialog : public QDialog
{
    Q_OBJECT
signals:
    void app1();
    void app2();
    void app3();
    void app4();
    void ctl(int);
public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    int mode;//网络版还是单机版
    QMap<QString,serialport_info>Serial_port;//串口信息
    database_plugin net_plugin;//网络配置
    using app_info =  QPair<QString,QString>;
    QVector<app_info>app_name;
private slots:

private:
    Ui::Dialog *ui;
    int read_generalxml();
    int application_nums;
    void draw_init();
    QVBoxLayout *V_layout1;
    QVBoxLayout *V_layout2;
    QHBoxLayout *H_layout;
    QVector<my_button*>app_button;
};

#endif // DIALOG_H
