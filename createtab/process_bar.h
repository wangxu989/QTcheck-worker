#ifndef PROCESS_BAR_H
#define PROCESS_BAR_H
#include<QTime>
#include<QThread>
#include<QProgressBar>
#include<QSemaphore>
#include<QMap>
//进度条
//观察者模式
class event_progressbar{
public:
    virtual void setValue(float a) = 0;
    static QMap<QString,event_progressbar*> progressbars;
    virtual const int value()const =0;
    event_progressbar(){};
    virtual ~event_progressbar(){};
    static void notify(float num) {//目前就只有一个观察者，先偷懒不改原先代码。
        for (auto& a:progressbars) {
            a->setValue(num);
        }
    }

protected:
    void add_self(const QString& s) {
        progressbars[s] = this;
    }
    void remove_self(const QString& s) {
        progressbars.remove(s);
    }
};
class progressbar1:public event_progressbar{
  public:
    progressbar1(const QString& s):name(s) {
        bar = QSharedPointer<QProgressBar>(new QProgressBar());
        add_self(s);
        bar->setRange(0,100);
    }
    void setValue(float a) override{
        bar->setValue(a);
        if (bar->value() >= 80) {
            bar->setStyleSheet("QProgressBar {   border: 2px solid grey;   border-radius: 5px;   background-color: #FFFFFF;}QProgressBar::chunk {   background-color: #FF0000;   width: 20px;}QProgressBar {   border: 2px solid grey;   border-radius: 5px;   text-align: center;}");//red
        }
        else if (bar->value() >= 50) {
            bar->setStyleSheet("QProgressBar {   border: 2px solid grey;   border-radius: 5px;   background-color: #FFFFFF;}QProgressBar::chunk {   background-color: #FFFF00;   width: 20px;}QProgressBar {   border: 2px solid grey;   border-radius: 5px;   text-align: center;}");//yellow
        }
        else {
            bar->setStyleSheet("QProgressBar {   border: 2px solid grey;   border-radius: 5px;   background-color: #FFFFFF;}QProgressBar::chunk {   background-color: #05B8CC;   width: 20px;}QProgressBar {   border: 2px solid grey;   border-radius: 5px;   text-align: center;}");//blue
        }
    };
    ~progressbar1(){
        remove_self(name);
    }
    QProgressBar*const get_bar()const {return this->bar.data();}
    const int value()const override{
        return bar->value();
    }

private:
    QSharedPointer<QProgressBar>bar;
    QString name;
};
class process_bar:public QThread
{
    Q_OBJECT
public:
    process_bar(QObject *parent);
     ~process_bar();
private:
    void run();
    volatile bool stopped;
    int hour;
    int minute;
    double gap;
    QSemaphore sem;
private slots:

signals:
    void flash_progressBar();

};

#endif // PROCESS_BAR_H
