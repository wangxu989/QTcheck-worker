#ifndef DIALOG_H
#define DIALOG_H
#include<QDebug>
#include<QThread>
#include <database.h>
#include<QProcess>
#include"tab.h"
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
//子功能1
namespace Ui {
class Dialog;
}

class keyboard_widget:public QWidget {
public:
    my_tablewidget *figure;
    ~keyboard_widget(){
        delete figure;
        delete fig_key;
    }

    keyboard_widget(const QString& s) {
        display = new QLabel();
        display->setStyleSheet("border:2px solid black;");
        QFont ft;//字体大小
        ft.setPointSize(30);
        display->setFont(ft);
        figure = new my_tablewidget(4,4);
        fig_key = new QVBoxLayout();
        fig_key->addWidget(display);
        fig_key->addWidget(figure);
        fig_key->setStretchFactor(display,1);
        fig_key->setStretchFactor(figure,4);
        this->setLayout(fig_key);
        figure->setSpan(0,3,2,1);
        figure->setSpan(2,3,2,1);
        figure->setSpan(3,0,1,2);
        figure->item(3,2)->setText(".");
        figure->item(2,3)->setText(s);
        for (int i = 0;i <3;i++) {
            for (int j = 0;j < 3;j++) {
                figure->item(i,j)->setText(QString::number(7 - i*3 + j));
            }
        }
        QLabel *t_label = new QLabel();
        t_label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        t_label->setPixmap(QPixmap(":/new/prefix1/img/cancel.png"));
        figure->setCellWidget(0,3,t_label);
        figure->item(3,0)->setText("0");
        figure->setFont(ft);
    }
    inline void setText(const QString& s) {display->setText(s);}
    inline void removeText() {display->setText(display->text().mid(0,display->text().size() - 1));}
    inline QString getVal() {return display->text();}
    inline void addText(int row,int column,const QString&& s = ""){display->setText( display->text() + figure->item(row,column)->text() + s);}

private:
    QLabel *display;
    QVBoxLayout *fig_key;

};

class Dialog : public QDialog,public baseP
{
    Q_OBJECT
signals:
    void change_widget(int);
public:
    //friend class socket;改用信号
    Dialog(const QString& name,QWidget *parent = nullptr);
    ~Dialog();
    int tabnum = 0;
   process_bar *pro_bar;
   mytab tab1;
   bool start_P()override;
   void finish_P()override;
   QWidget* widget;
   QWidget *tempw;
   keyboard_widget *keyboard;
   inline void link_database();

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
private:
    bool listen();
    //QSharedPointer<message_remind> m_remind;
    QMessageBox *messageBox;
    Ui::Dialog *ui;
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
    QProgressBar *progress_bar;
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

     //QString spc_e;//上报字符串
};

#endif // DIALOG_H
