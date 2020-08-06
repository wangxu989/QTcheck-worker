#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QPair>
#include <QDialog>
#include<QPushButton>
#include<QHBoxLayout>
#include<QMap>
#include<QVBoxLayout>
#include<base_program.h>
#include<dialog.h>
#include<program2.h>
#include<database.h>
//#include<qpa
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class my_button : public QPushButton {
    Q_OBJECT
public:
    static int num;
    static void init_num() {
        static int num = 0;
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
    baseP mainP;
    QWidget *main_widget;
    Dialog* P1;
    QSharedPointer<Program2>P2;
    void change_widget(int);
};
#endif // MAINWINDOW_H
