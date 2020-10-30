#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<socket.h>
#include<QPushButton>
#include<QVBoxLayout>
#include<QTableWidget>
#include<QHeaderView>
#include<QApplication>
#include<QStylePainter>
#include<my_port.h>
#include<QLabel>
#include<my_tables.h>
//#define MY_P
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     work_info workInfo;

private:
    Ui::MainWindow *ui;
    my_tablewidget *table,*table1;//_work,*table_worker,*table_product ,*table_process;
    QVBoxLayout *table_layout;
    QSharedPointer<my_table> tablestart,tablefinish,table2,table3;//table2:二级逻辑表格(开工),table3:二级逻辑表格（完工）
    my_port my_port1;
    bool status;
    bool is_work = false;
    QSet<QString> rec_set;
    bool is_first;
    void finish_save();

private slots:
    void insert_data(int flag);
    void my_send1();
    void my_send2();
    void my_send3();
    void my_send4();
    void set_table_size(int num,int size);
    void act_mode(int act);
    void my_read();
    void change_status();
    void insert_table2(ElseInf&);
    void confirm();
    void change_table();
    void delete_msg();
    void confirm_finish(ElseInf&);
};

#endif // MAINWINDOW_H
