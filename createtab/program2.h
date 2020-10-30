#ifndef PROGRAM2_H
#define PROGRAM2_H
#include<programwork.h>
#include <QWidget>
#include<QString>
#include<QLabel>
#include<QProcess>
#include<QPushButton>
#include<my_port.h>
#include<qrencodeh/qrencode.h>
//#define MY_P2
//子功能2
namespace Ui {
class Program2;
}
class button_ctl{
public:
    //注意定义过的static变量存在整个程序执行期间
    static QMap<int,button_ctl*>rec;
    static int size;//观察者计数
    virtual bool set_status() = 0;
    virtual bool onclicked() = 0;
    static int now_num;
    int num;
    static void notify(int now = -1){
        if (now_num >= 0) {
            rec[now_num]->set_status();
        }
        if (now >= 0) {
            rec[now]->onclicked();
            now_num = now;
        }
    }
    static void recover() {
        if (now_num >= 0) {
            rec[now_num]->onclicked();
        }
    }
    virtual ~button_ctl(){};
    button_ctl() {
        add_self();
    }
protected:
    void add_self() {
        rec[size] = this;
        num = size;
        size++;
    }
    void remove_self() {
        auto iter = rec.find(num);
        rec.erase(iter);
        size--;
        if (size = 0) {
            now_num = -1;
        }
    }
};
class noti_button:public button_ctl{
public:
    bool set_status()override {
        if (!data->isEnabled()) {
            data->setEnabled(true);
        }
        return true;
    }
    bool attach(QPushButton *p) {
        data = p;
    }
    bool onclicked()override{
        data->setEnabled(false);
    }
    noti_button() {}
    ~noti_button(){
        remove_self();
    }
private:
    QPushButton* data;
};

class Program2 :public MyWidget,public baseP
{
    Q_OBJECT
public:
    explicit Program2(const QString& name,QWidget *parent = 0);
    ~Program2()override;
    bool start_P()override;
    void finish_P()override;
    MyWidget* get_widget(){return this;};
signals:
    //void change_widget(int);
    //void change_widget(QWidget*);
private slots:
    void on_pushButton_5_clicked();
    void exec_button();
    void in_keyboard(const int &row,const int &column);

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void show_print_code(const QString& s);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Program2 *ui;
    QSharedPointer<QHBoxLayout>key_lay;
    QSharedPointer<keyboard_widget>key;//只有static const primitive(内置)变量才能在声明时初始化
    void read_data();
    bool status = false;
    QSharedPointer<QLabel>label_2;
    QString thisname;
    QProcess my_progress;
    int now_click;//已执行，完成，终止
    noti_button exe;
    noti_button finished;
    noti_button terminated;
    //print
    my_port port_print;
    socket *my_socket = socket::get_socket();
};

#endif // PROGRAM2_H
