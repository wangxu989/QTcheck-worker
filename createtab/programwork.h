#ifndef ProgramWork_H
#define ProgramWork_H

//#define MY_P
#include <QWidget>
#include<QDebug>
#include<QThread>
#include <database.h>
#include<QProcess>
#include"socket.h"
#include<process_bar.h>
#include<QProgressBar>
#include<QMessageBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QHeaderView>
#include<QMap>
#include<QScrollBar>
#include<base_program.h>
#include<keyboard.h>

//子功能1

namespace Ui {
class ProgramWork;
}

class ProgramWork :public MyWidget,public baseP
{
    Q_OBJECT
signals:
    //void change_widget(int);
    //void change_widget(QWidget*);
public:
    //friend class socket;改用信号
    explicit ProgramWork(const QString& name,QWidget *parent = nullptr);
    ~ProgramWork()override;
    int tabnum = 0;
   process_bar *pro_bar;
   mytab tab1;
   bool start_P()override;
   void finish_P()override;
   QWidget* widget;
   QWidget *tempw;
   keyboard_widget *keyboard;
   inline void link_database();
   MyWidget* get_widget(){return this;};

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
    void plot_enlarge();
    void plot_narrow();
    void in_keyboard(const int& row,const int& column);
    void gauge_add();
    void on_pushButton_clicked();

private:
    bool listen();
    //QSharedPointer<message_remind> m_remind;
    QMessageBox *messageBox;
    Ui::ProgramWork *ui;
    QProcess my_process;
    //QPushButton *button_quit;//退出
    QPushButton *button_ret;//返回
    //QPushButton *buttonej;//返回
    QHBoxLayout *templayout;
    //QTabWidget *tabwidget;
    QHBoxLayout *layout;
    QTableWidget *temp;
    QVBoxLayout *v_layout;
    QVBoxLayout *v_button_layout;
    //QProgressBar *progress_bar;
    QSharedPointer<progressbar1> progress_bar;
    //QPushButton *pre_page;
    //QPushButton *next_page;
   // QHBoxLayout *page_layout;
    //Ui::MainWindow *ui;
     void tabadd(QString name);
     int insertvalue(int row,int i,double valuel2,int column);
     void first_tablogic(int &row,int &column);
     void start_work();
     void check_identity();
     int result;
     int time_check(int column,int flag);
     //int mode;//0本地，1网络
     void draw_init();
     int pagevalue = 8;
     int ret_checkout[3] = {0};
     int start_flag = 0;
     //缩放
     QPushButton *narrow;
     QPushButton *enlarge;
     //数字键盘交互
     QPushButton *gauge;//检具
     QString thisname;
     //QString spc_e;//上报字符串
     socket *my_socket = socket::get_socket();
};

#endif // ProgramWork_H
