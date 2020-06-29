#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QVector>
#include <QMainWindow>
#include"my_port.h"
#include <QWidget>
//#include"qcustomplot.h"
#include"socketclient.h"
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    virtual void draw();
    QQueue<double> *x;
    QQueue<double> *y;
    volatile int tabnum;
    QCustomPlot *pCustomPlot;
    volatile bool stopped;
    my_tablewidget *table_work,*table_worker,*table_product;
    QPushButton *button1;
    void change();
    //void initpcustomplot(int num);

private slots:
    void my_read();
    void insert_data_to_table(int flag);
    void enlarge_plot();
    void narrow_plot();
    void my_send1();
    void my_send2();
    void my_send3();
    void my_send4();
private:
    void my_init();
    Ui::MainWindow *ui;
    QVBoxLayout *Vlayout;
    QHBoxLayout *H_plot_layout;
    QHBoxLayout *Hlayout;
    QWidget *widget;
    QVBoxLayout *V_button;
    QPushButton *enlarge;
    QPushButton *narrow;
    my_port my_port1;
    work_info workInfo = {"YG,02294","SB,001073","ZL,20016101180122000101,17121618739,1,1800"};
    QLabel *label2 ;
    QSqlQuery query;
};

#endif // MAINWINDOW_H
