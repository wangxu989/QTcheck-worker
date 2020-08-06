#ifndef BASE_PROGRAM_H
#define BASE_PROGRAM_H
#include<QVector>
#include<QDebug>
#include<QMap>
#include<QMessageBox>
//定义主程序类，统一管理可能出现的子程序类prototype设计模式
//提示消息总类
class message_remind{
public:
    inline message_remind(const QString& title){box = new QMessageBox(QMessageBox::NoIcon,title,"",nullptr,nullptr);}
    inline ~message_remind(){delete box;}
    message_remind(const message_remind& m) =delete;//禁止拷贝构造
    message_remind& operator=(const message_remind& m)=delete;//禁止拷贝赋值
    void show(const QString& s,const QString& title = "")const {
        box->setText(s);
        box->show();
    }
    void close()const {
        box->close();
    }

private:
    QMessageBox *box;
};
class my_messagebox:public QMessageBox{
protected:
    void showEvent(QShowEvent *event) {
        QMessageBox::showEvent(event);
        setFixedSize(300,300);
    }
};

class baseP {
//private:
//    baseP(){
//        qDebug()<<"create signal";
//    };
//protected:
//    baseP(const baseP& P){};
//public:
//    baseP& operator=(baseP &p)=delete;
//    QVector<baseP*> allP;
//    static baseP& p_init() {
//        static baseP mainP;
//        return mainP;
//    }
public:
    static void p_init() {
            if (allP == nullptr) {
                allP = QSharedPointer<QMap<QString,baseP*>>(new QMap<QString,baseP*>());
            }
    }
    static QSharedPointer<QMap<QString,baseP*>> allP;
    virtual bool start_P(){};
    virtual void finish_P(){};
private:
protected:
    static void add_p(const QString& name,baseP* P) {
        (*allP)[name] = P;
        qDebug()<<"add!!!!";
    }
    static void remove_P() {

    }
};




#endif // BASE_PROGRAM_H
