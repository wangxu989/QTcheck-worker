#ifndef FINISH_WORK_H
#define FINISH_WORK_H
#include<QThread>
#include <QWidget>
#include<QHBoxLayout>
#include<myledit.h>
#include<QDateTime>
#include<QLocale>
#include<qmessage_remind.h>
#include<database.h>
//子功能3完工信息页面

namespace Ui{
class finish_work;
}
class my_time{
public:
    static my_time* get_time() {
        if (time == nullptr) {
            time = new my_time();
        }
        return time;
    }
    ~my_time() {
        delete time;
    }
    QString get_currenttime() {
        QDateTime dateTime = QDateTime::currentDateTime();
        QLocale locale1;//指定英文显示
        QString strFormat = "yyyy-MM-dd hh:mm:ss";
        //return std::move(locale1.toString(dateTime, strFormat));
        return locale1.toString(dateTime, strFormat);
    }
    QString get_time_format1(int time_scope = 0) {
        QDateTime time = QDateTime::fromTime_t(QDateTime::currentDateTime().toTime_t() - time_scope*24*3600);
        QString cmp_end = (time.date().year() - 2000 < 10 ? "0":"") +  QString::number(time.date().year() - 2000) +
                      (time.date().month() < 10 ? "0":"") +  QString::number(time.date().month()) +
                      (time.date().day() < 10 ? "0":"") +  QString::number(time.date().day())+
                      (time.time().hour() < 10 ? "0":"") + QString::number(time.time().hour()) +
                      (time.time().minute() < 10 ? "0":"") + QString::number(time.time().minute()) +
                      (time.time().second() < 10 ? "0":"") + QString::number(time.time().second());
        return cmp_end;
    }

protected:
    static my_time* time;
    my_time(){}
private:

};

namespace Program3 {

class time_update:public QThread{
    Q_OBJECT
public:
    time_update(MyLEdit *line):my_line(line) {
        time = my_time::get_time();
        start();
    }
    void run() {
        while(!stop) {
            sleep(1);
            my_line->setText(time->get_currenttime());
        }
    }
    ~time_update() {
        stop = true;
        wait();
    }

private:
    volatile bool stop = false;
    MyLEdit* my_line;
    my_time* time;
};

class finish_work : public QWidget
{
    Q_OBJECT
    //friend time_update;
public:
    explicit finish_work(QWidget *parent = 0);
    ~finish_work();
//    QHBoxLayout* get_layout() {
//        return layout.data();
//    }
    bool setText(const QString&);
    QString text()const;
    QString getEndCount();
    QString getCurrentTime();
    QString get_Finish_Count();
    QString get_Probatch();
    QString get_s10();
    QString get_s11();
    QString get_s12();
    QString get_sElesIf();
    QString get_s16();
    QString get_worktime();
    bool check();
    bool check_s16();
    void init(const QString& s);
    bool GetBoxIndex(int& nPlanCappIndex, int& nBatchCappIndex,const QString& ID);
    QString Qrencode;
    QString starttime;
    int nPlanCappIndex,nBatchCappIndex;
    QString processname;
    QString get_residueNum();

private:
    QSharedPointer<QHBoxLayout>layout;
    Ui::finish_work *ui;
    MyLEdit* now;
    QSharedPointer<time_update>last_time;
    message_remind* Mremind = message_remind::get_Mremind();
    socket* my_socket = socket::get_socket();
private slots:
    void label_change(MyLEdit*);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};
}

#endif // FINISH_WORK_H
