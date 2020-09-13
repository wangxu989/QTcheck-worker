#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QPair>
#include <programwork.h>
#include<QPushButton>
#include<QHBoxLayout>
#include<QMap>
#include<QVBoxLayout>
#include<base_program.h>
#include<program2.h>
#include<database.h>
#include<start_finish_work.h>
#include<base_factory.h>
#include<qmessage_remind.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class my_button : public QPushButton {
    Q_OBJECT
public:
    static int num;
    static void init_num() {
    }
private:
signals:
    //void clicked(int num);
};

typedef  struct serialport{
    QString portName;
    QString baudRate;
    QString dataBits;
    QString stopBits;
    QString parity;
    QString writeBufferSize;
    QString readBufferSize;
}serialport_info;
class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
//    void app1();
//    void app2();
//    void app3();
//    void app4();
    void ctl(int);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

private:

    Ui::MainWindow *ui;
    int read_generalxml();
    int application_nums;
    void draw_init();
    QVBoxLayout *V_layout1;
    QVBoxLayout *V_layout2;
    QHBoxLayout *H_layout;
    QVector<my_button*>app_button;
    //baseP mainP;
    QWidget *main_widget;
    ProgramWork* P1;
    Program2*P2;
    start_finish_work*P3;
    void change_widget(QWidget*);
    baseP* BaseP;
};
#endif // MAINWINDOW_H
