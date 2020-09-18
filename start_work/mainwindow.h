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
#define MY_P
namespace Ui {
class MainWindow;
}
class my_tablewidget:public QTableWidget {//显示扫码信息
public:
    int row,column;
    my_tablewidget(const int &row,const int &column,const QString &info = ""):row(row),column(column){
        this->setColumnCount(column);
        this->setRowCount(row);
        this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        this->verticalHeader()->setHidden(true);
        this->horizontalHeader()->setHidden(true);
        for (int i = 0;i < row;i++) {
            for (int j = 0;j < column;j++) {
                this->setItem(i,j,new QTableWidgetItem());
                this->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
        }
        if (info.size()) {
            this->setSpan(0,0,1,this->columnCount());
            this->item(0,0)->setText(info);
        }
    }
};

class base_table{
public:
    static int num;
    static QVector<base_table*>rec;
    base_table(){}
    virtual ~base_table(){};
    virtual void focus() = 0;
    virtual void unfocus() = 0;
    virtual void remove() = 0;
    static void change() {
       if (rec.size() > 0) {
        rec[num]->unfocus();
        num = (num + 1)%rec.size();
        rec[num]->focus();
       }
    }
    static void remove_ctl() {
        rec[num]->remove();
    }

protected:
    void add_self(base_table* table) {
        if (rec.size() == 0) {
            table->focus();
        }
        rec.push_back(table);
    }
};

//使用variable template设计构造函数
class my_table:public QTableWidget,public base_table {
public:
    ~my_table()override{};
    void focus()override;
    void unfocus()override;
    void remove() override;

    QLabel *label = nullptr;
    //explicit my_table(const QString& name):corner_name(name){}
    int now_row = 0;
    template<typename... Types>
    my_table(QString name0,QLabel*lab,QWidget *parent,Types... T):label(lab),name(name0){//:QTableWidget(parent) {
        if (lab != nullptr) {
            add_self(this);
        }
        h_layout = QSharedPointer<QHBoxLayout>(new QHBoxLayout(parent));
        h_layout->addWidget(this);
        horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);    //x先自适应宽度
        //verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        setStyleSheet("selection-background-color: blue");//选中行颜色
        setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
        setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行
        QAbstractButton *btn = this->findChild<QAbstractButton *>();
        if (btn) {
            btn->setText(QStringLiteral("序号"));
            btn->installEventFilter(this);
            //btn->setStyleSheet("QAbstractButton{text-align : right;}");
            QStyleOptionHeader opt;
            opt.text = btn->text();
            QSize s = (btn->style()->sizeFromContents(QStyle::CT_HeaderSection, &opt, QSize(), btn).expandedTo(QApplication::globalStrut()));
            if (s.isValid()){
                this->verticalHeader()->setMinimumWidth(s.width());
                //t->verticalHeader()->setMinimumSize(btn->size());
            }
        }
        //去掉横竖scrollbar
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        //不可修改
        this->setEditTriggers(QAbstractItemView::NoEditTriggers);

        this->setColumnCount(sizeof...(T));
        head_init(T...);
    }
    template<typename T>
    bool insert(T& tab) {//向表格插入数据
       this->setRowCount(now_row + 1);
       for (int i = 0;i < this->columnCount();i++) {
           if (!this->item(this->now_row,i)) {
               this->setItem(this->now_row,i,new QTableWidgetItem());
           }
           qDebug()<<tab[i];
           this->item(this->now_row,i)->setText(tab[i]);
       }
       this->now_row++;
       //qDebug()<<this->now_row;
       return true;
    }
    void head_init(){
        this->setHorizontalHeaderLabels(list_head);
    }
    template<typename T,typename... Types>
    void head_init(const T& t1,const Types&... types) {
        list_head<<t1;
        qDebug()<<t1;
        head_init(types...);
    }
    bool eventFilter(QObject *o, QEvent *e) {
        if (e->type() == QEvent::Paint)
        {
            QAbstractButton* btn = qobject_cast<QAbstractButton*>(o);
            if (btn)
            {
                // paint by hand (borrowed from QTableCornerButton)

                QStyleOptionHeader opt;
                opt.init(btn);
                QStyle::State state = QStyle::State_None;
                if (btn->isEnabled())
                    state |= QStyle::State_Enabled;
                if (btn->isActiveWindow())
                    state |= QStyle::State_Active;
                if (btn->isDown())
                    state |= QStyle::State_Sunken;
                opt.textAlignment = Qt::AlignCenter;//居中
                opt.state = state;
                opt.rect = btn->rect();
                opt.text = btn->text(); // this line is the only difference to QTableCornerButton

                opt.position = QStyleOptionHeader::OnlyOneSection;
                QStylePainter painter(btn);
                painter.drawControl(QStyle::CE_Header, opt);
                return true; // eat event

            }
        }
        return false;
    }

    my_table& operator =(const my_table& t1)=delete;
    my_table(const my_table& t1)=delete;

private:
    QString corner_name;
    QStringList list_head;
    QSharedPointer<QHBoxLayout> h_layout;
    QString name;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     work_info workInfo;

private:
    Ui::MainWindow *ui;
    my_tablewidget *table_work,*table_worker,*table_product ,*table_process;
    QVBoxLayout *table_layout;
    QSharedPointer<my_table> tablestart,tablefinish,table2;//table2:二级逻辑表格，复用
    my_port my_port1;
    bool status;
    QSet<QString> rec_set;

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
};

#endif // MAINWINDOW_H
