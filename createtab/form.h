#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include"qcustomplot.h"
#include<QWidget>
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    virtual void draw();
    void stop();
    QHBoxLayout *layout;
    QQueue<double> *x;
    QQueue<double> *y;
    volatile int tabnum;
    Ui::Form *ui;
    QCustomPlot *pCustomPlot;
    volatile bool stopped;
    QSemaphore *sem;
    QTableWidget *t1,*t2,*t3;
    QWidget *w1;
    void Table_init();
    QPushButton *button1;
    void change();
private:
    QVBoxLayout *Vlayout;
    QHBoxLayout *Hlayout;
    //void mythreadstop();
protected:
    void closeEvent(QCloseEvent *event);//关闭线程
};

#endif // FORM_H
