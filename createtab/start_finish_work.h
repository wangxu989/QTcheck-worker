#ifndef START_FINISH_WORK_H
#define START_FINISH_WORK_H
#include<base_program.h>
#include <QWidget>
#include<socket.h>
#include<QProcess>
#include<base_program.h>
#include<QSqlQuery>
#include<QDateTime>
//#include<finish_work.h>
//#include<mylabel.h>
#include<database.h>
#include<programwork.h>
#include<keyboard.h>
#include<qrencodeh/qrencode.h>
#include<my_port.h>
//#define MY_P3
//子功能3
namespace Ui {
class start_finish_work;
}
const int N = 4;//扫码数
class start_finish_work :public MyWidget,public baseP
{
    Q_OBJECT
signals:
    //void change_widget(QWidget*);
public:
    explicit start_finish_work(const QString& name,QWidget *parent = 0);
    ~start_finish_work();
    bool start_P()override;
    void finish_P()override;
     MyWidget* get_widget(){return this;};

private:
    message_remind *Mremind = message_remind::get_Mremind();
    QProcess my_progress;
    Ui::start_finish_work *ui;
    QSharedPointer<keyboard_widget> key;
    xml& my_xml;
    int start_flag = 0;
    int ret_checkout[N] = {0};
    void flash_rec() {
        ret_checkout[1] = 0;
        ret_checkout[3] = 0;
        //memset(ret_checkout + 2,0,(N-2)*sizeof(int));
    }

    void search_base();
    QString name_P;
    bool status = false;
    ProcessInf ProInf;
    ElseInf elseinf;
    socket* my_socket = socket::get_socket();
    QSharedPointer<Program3::finish_work>finish_widget;
    MyLEdit* now;
    start_rec start;
    my_time* time = my_time::get_time();
    std::tuple<QString,QString>res_finish_sb_and_material;
    QString Qrencode;
    my_port port_print;
    QString start_time;


private slots:
    void check_info(int flag);
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_5_clicked();
    void deal_ProcessID(QString&);
    void on_pushButton_clicked();
    void deal_rec(QString&);
    void delete_start2tab(QString&);
    void add_start2tab(const start_rec&s);
    void in_keyboard(const int &row,const int &column);
    void finish_work_processID(QString&);
    void on_pushButton_3_clicked();
};

#endif // START_FINISH_WORK_H
