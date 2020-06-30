#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QDebug>
#include<QThread>
#include <QMainWindow>
#include "database.h"
#include<QProcess>
#include"tab.h"
#include"socket.h"
#include<process_bar.h>
#include<QProgressBar>
#include<QMessageBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QHeaderView>
#include"dialog.h"
#include<QMap>
#include<QScrollBar>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //friend class socket;改用信号
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int tabnum = 0;
   process_bar *pro_bar;
   mytab tab1;
public slots:
    void onClicked(int row,int column);
    void pushButton_exit();
    void pushButtonclickedej();
    void pushButton_finish();
    void ejClicked(int row,int column);
    void pushform_button();
    void start_after();
private slots:
    //void on_pushButton_2_clicked();
    void tabchanged(int i);
    void login();
    void flash();
    void prePage();
    void nextPage();
    void check_info(int flag);
private:
    Dialog *dialog;
    QMessageBox *messageBox;
    Ui::MainWindow *ui;
    QProcess my_process;
    QPushButton *button_quit;//退出
    QPushButton *button_ret;//返回
    QPushButton *buttonej;//返回
    QWidget *tempw;
    QHBoxLayout *templayout;
    QWidget *widget;
    //QTabWidget *tabwidget;
    QHBoxLayout *layout;
    QVBoxLayout *v_layout;
    QVBoxLayout *v_button_layout;
    QProgressBar *progress_bar;
    //QPushButton *pre_page;
    //QPushButton *next_page;
   // QHBoxLayout *page_layout;
    //Ui::MainWindow *ui;
     void tabadd(QString name);
     database *data_server;//数据库类
     database *data_local;
     int insertvalue(int row,int i,double valuel2,int column);
     void first_tablogic(int &row,int &column);
     void start_work();
     void check_identity();
     int result;
     int time_check(int column,int flag);
     int mode;//0本地，1网络
     void draw_init();
     int pagevalue = 8;
     int ret_checkout[3] = {0};
     int start_flag = 0;

};
#endif // MAINWINDOW_H
