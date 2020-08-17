#ifndef PROGRAM2_H
#define PROGRAM2_H
#include<dialog.h>
#include <QWidget>
#include<QString>
#include<qrencode.h>
#include<QLabel>
#include<QProcess>
//子功能2
namespace Ui {
class Program2;
}

class Program2 : public QWidget,baseP
{
    Q_OBJECT

public:
    explicit Program2(const QString& name,QWidget *parent = 0);
    ~Program2();
    bool start_P()override;
    void finish_P()override;
signals:
    void change_widget(int);
private slots:
    void on_pushButton_5_clicked();
    void exec_button();
    void in_keyboard(const int &row,const int &column);

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void show_print_code(QString& s);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Program2 *ui;
    QSharedPointer<QHBoxLayout>key_lay;
    QSharedPointer<keyboard_widget>key;//只有static const primitive(内置)变量才能在声明时初始化
    void read_data();
    bool status = false;
    QSharedPointer<QLabel>label_2;
    QString thisname;
    QProcess my_progress;
    int now_click;//已执行，完成，终止

};

#endif // PROGRAM2_H
