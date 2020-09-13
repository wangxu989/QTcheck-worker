#ifndef BASE_PROGRAM_H
#define BASE_PROGRAM_H
#include<QVector>
#include<QDebug>
#include<QMap>
#include<QMessageBox>
#include<socket.h>
//后续可以将所有全局变量重构为单例模式
//定义主程序类，统一管理可能出现的子程序类策略加工厂
//提示消息总类
namespace Ui {
class Program2;
}
class my_messagebox:public QMessageBox{
protected:
    void showEvent(QShowEvent *event) {
        QMessageBox::showEvent(event);
        setFixedSize(300,300);
    }
};
//当时没理清楚，baseP应该直接继承qwidget
//因为qt信号元编程必须继承QObject
class MyWidget:public QWidget {
    Q_OBJECT
signals:
    void  change_widget(QWidget*);
};
class baseP{//策略定义接口
public:
    static void p_init() {
            if (allP == nullptr) {
                allP = QSharedPointer<QMap<QString,baseP*>>(new QMap<QString,baseP*>());
            }
    }
    static QSharedPointer<QMap<QString,baseP*>> allP;//保存所有正在执行子功能指针up_cast
    virtual bool start_P() = 0;
    virtual void finish_P() = 0;
    virtual ~baseP(){};
    virtual MyWidget* get_widget() = 0;
//signals:
//     void change_widget(QWidget*);
private:
protected:
    static void add_p(const QString& name,baseP* P) {
        (*allP)[name] = P;
        qDebug()<<"add!!!!";
    }
    static void remove_P(QString& name) {
        auto iter = allP.data()->find(name);
        if (iter != allP.data()->end()) {
            allP->erase(iter);
        }
    }
    bool listen(socket* s) {
        if (!s->status()) {
            return s->bind();
        }
        return true;
    }
};

class xml{//单例模式
public:
    ~xml(){}
    static xml& get_xml() {
        if (x == nullptr) {
            x = new xml();
        }
        return *x;
    }
    xml& operator=(const xml& x)=delete;
    int readxml(const work_info &work_info,int flag = 0);
    int read_local_authuser(const work_info &work_info);
    int read_local_env(const work_info &work_info,int flag);
    int read_start_finish_config();
    message_worker_evn messageWorkerEvn;
protected:
    static xml* x;
private:
    xml() {};
};




#endif // BASE_PROGRAM_H
