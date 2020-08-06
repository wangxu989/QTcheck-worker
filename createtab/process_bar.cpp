#include "process_bar.h"
#include<QProgressBar>
#include<QDebug>
process_bar::process_bar(QObject *parent):QThread(parent)
{
    stopped = false;
    sem.release();
}
void process_bar::run() {
    while(!stopped) {
        QTime current_time = QTime::currentTime();
        hour = current_time.hour();
        minute = current_time.minute();
        emit flash_progressBar();
        //sleep(60 - current_time.second());
        sleep(1);
    }
    qDebug()<<"thread destroy";
}
process_bar::~process_bar() {
    stopped = true;
    wait();
    //terminate();
}
