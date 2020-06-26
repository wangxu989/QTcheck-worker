#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    //draw();
    layout = new QHBoxLayout();
    Vlayout = new QVBoxLayout();
    Hlayout = new QHBoxLayout();
    t1 = new QTableWidget();
    t2 = new QTableWidget();
    t3 = new QTableWidget();
    w1 = new QWidget();
    t1->setColumnCount(2);
    t1->setRowCount(2);
    t2->setColumnCount(2);
    t2->setRowCount(2);
    t3->setColumnCount(2);
    t3->setRowCount(2);
    //t1->item(0,0) = new QTableWidgetItem("haha");
}

Form::~Form()
{
    delete ui;
    delete t1;
    delete t2;
    delete t3;
}
void Form::draw() {
    button1 = new QPushButton("登陆确认");
    Vlayout->addWidget(t1);
    Vlayout->addWidget(t2);
    Vlayout->addWidget(t3);
    Hlayout->addLayout(Vlayout);
    Hlayout->addWidget(pCustomPlot);
    Hlayout->setStretchFactor(Vlayout,1);
    //Hlayout->setStretchFactor(button1,1);
    Hlayout->setStretchFactor(pCustomPlot,3);
    setLayout(Hlayout);
}
void Form::closeEvent(QCloseEvent *event) {
    //stop();
}
void Form::stop(){
    stopped = true;
    (*sem).release();
}
void Form::Table_init() {

}
void Form::change() {
    Hlayout->removeWidget(button1);
    Hlayout->removeItem(Vlayout);
    Hlayout->addWidget(pCustomPlot);

}
