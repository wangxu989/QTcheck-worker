#ifndef PROCESS_BAR_H
#define PROCESS_BAR_H
#include<QTime>
#include<QThread>
#include<QProgressBar>
#include<QSemaphore>
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
    void flash_progressBar(QTime);

};

#endif // PROCESS_BAR_H
