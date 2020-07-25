#ifndef SHOWDATA_H
#define SHOWDATA_H
#include<QThread>
#include<QVector>
#include"form.h"
class showdata:public QThread,public Form
{
protected:
    void run();
public:
    explicit showdata(QObject *parent = 0);
private:
};

#endif // SHOWDATA_H
