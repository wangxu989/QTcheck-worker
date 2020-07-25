#include "showdata.h"
#include<QtDebug>
#include<QQueue>
showdata::showdata(QObject *parent):
    QThread(parent){
    stopped = false;
}
void showdata::run() {
    //draw();
    //show();
//    QVector<double>x1,y1;
//    for (int i = 0;i < 10;i++) {
//        x1.push_back(i);
//        y1.push_back(2*i);
//    }
    while(!stopped) {
       //qDebug()<<tabnum;
       (*sem).acquire();
//        QVector<double>hzb;
//        QDateTime dateTime = QDateTime::currentDateTime();
//        for (int i = 0;i < (*x).size();i++) {
//            QString s = dateTime.toString().split(" ")[0] + " " + dateTime.toString().split(" ")[1] + " " + dateTime.toString().split(" ")[2] + " " + (*x)[i] + " " + dateTime.toString().split(" ")[4];
//            QDateTime time = QDateTime::fromString(s);
//            //qDebug()<<time;
//            hzb.push_back(time.toTime_t());
//        }
        if (!stopped){
            pCustomPlot->graph(tabnum)->addData(x->front(),y->front());
            //pCustomPlot->graph(tabnum)
            pCustomPlot->replot(QCustomPlot::rpQueuedReplot);
            y->pop_front();
            x->pop_front();
        }
        //sleep(3);
    }
    stopped = false;
}
