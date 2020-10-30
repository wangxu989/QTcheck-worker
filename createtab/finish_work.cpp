#include "finish_work.h"
#include "ui_finish_work.h"
#include<QDebug>
my_time* my_time::time = nullptr;
extern database_server *data_server;
//计算工作时常
//
Program3::finish_work::finish_work(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::finish_work)
{
    ui->setupUi(this);
    layout = QSharedPointer<QHBoxLayout>(new QHBoxLayout());
    layout->addWidget(this);
    connect(ui->lineEdit_10,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit_11,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit_13,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit_4,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit_5,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit_6,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit_7,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit_8,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    connect(ui->lineEdit_9,&MyLEdit::clicked,this,&Program3::finish_work::label_change);
    last_time = QSharedPointer<time_update>(new time_update(ui->lineEdit_5));
}

Program3::finish_work::~finish_work()
{

    delete ui;
}
QString Program3::finish_work::text() const{
    if (now == nullptr) {return QString("");}
    qDebug()<<now->text();
    return now->text();
}
bool Program3::finish_work::setText(const QString&s) {
    if (now == nullptr) {return false;}
    qDebug()<<"Mylineedit";
    now->setText(s);
    return true;
}
void Program3::finish_work::label_change(MyLEdit *m) {
    now = m;
}
QString Program3::finish_work::getEndCount() {//成品数量
    return ui->lineEdit_6->text();
}
QString Program3::finish_work::getCurrentTime() {
        QDateTime dateTime = QDateTime::currentDateTime();
        QLocale locale;//指定英文显示
        QString strFormat = "yyyyMMddhhmm";
        return locale.toString(dateTime, strFormat);
}
QString Program3::finish_work::get_Finish_Count() {//待处理数量
    return ui->lineEdit_7->text();
}
QString Program3::finish_work::get_Probatch() {//产品批次
    return ui->lineEdit_8->text();
}
bool Program3::finish_work::check() {
    QString& s = my_socket->workInfo.instruction_id;
    QString instructionID;
    if (s.contains("ZL")) {//首次
        instructionID = s.split(",")[1];
    }
    else {
        instructionID = s.split(",")[0];
    }
    if (ui->lineEdit_11->text() != "" && ui->lineEdit_13->text() != "") {
        Mremind->show("热处理和表面处理不能呢同时出现！");
        return false;
    }
    //    if (ui->lineEdit_4->text()[ui->lineEdit_4->text().size() - 1] != 'Y') {
    //        Mremind->show("检验报告最后一位必须是Y!");
    //        return false;
    //    }
    //装模清单与生产令号不属于同一产品,比较生产令号3～8位
    if (ui->lineEdit_9->text() != "" && ui->lineEdit_9->text().left(6) != instructionID.left(8).right(6)) {
        Mremind->show("装模清单与生产令号不属于同一产品");
        return false;
    }
    // 对定义了标箱数的首工序进行提示   f1成品数，f2标箱数
    int f1 = ui->pushButton->text().toInt(),f2 = ui->pushButton_2->text().toInt();
    if (instructionID.right(2) == "01" && f2 > 1) {
        if (f1 < 0.9*f2)
        {
            QMessageBox messageBox(QMessageBox::NoIcon,
                                   "warnning", "成品数小于标箱数的90%%，请问成品数正确吗?",
                                   QMessageBox::Yes | QMessageBox::No, NULL); ;
            int result=messageBox.exec();
            if (result == QMessageBox::No) return false;
        }

        if (f1 > 1.1*f2)
        {
            QMessageBox messageBox(QMessageBox::NoIcon,
                                   "warnning", "成品数大于标箱数的1.1倍，请问成品数正确吗？",
                                   QMessageBox::Yes | QMessageBox::No, NULL); ;
            int result=messageBox.exec();
            if (result == QMessageBox::No) return false;
        }

    }
//    if ((ui->lineEdit_4->text() == "" ) || ui->lineEdit_5->text() == ""
//            || ui->lineEdit_6->text() == "" || (ui->lineEdit_7->text() == "")
//            || (ui->lineEdit_8->text() == "" && ui->lineEdit_8->isEnabled() == true) || (ui->lineEdit_9->text() == "")
//            || ui->lineEdit_10->text() == ""
//            || (ui->lineEdit_13->text() == "" &&  ui->lineEdit_11->text() == "")) {
    if(ui->lineEdit_6->text() == "" || ui->lineEdit_7->text() == "") {
         Mremind->show("信息不全");
        return false;
    }
    //更新上一工序的成品数量
    QString q = QString("update planstart2tab set EndCount = EndCount + %1 where CmdID = " + instructionID +
                        " and EndTime = " +  s.split(",")[2]).arg(getEndCount());
    data_server->query_ctl(q);
    //获取工作时常


    //组装二维码字符串
    GetBoxIndex(nPlanCappIndex,nBatchCappIndex,instructionID);

    return true;
}
QString Program3::finish_work::get_s10() {//热处理号
    return ui->lineEdit_11->text();
}
QString Program3::finish_work::get_s11() {//表面处理
    return ui->lineEdit_13->text();
}
QString Program3::finish_work::get_s12() {//检验报告
    return ui->lineEdit_4->text();
}
QString Program3::finish_work::get_sElesIf() {//备注信息
    //return ui->lineEdit_12->text();
}
QString Program3::finish_work::get_s16() {//装模清单
    return ui->lineEdit_9->text();
}
QString Program3::finish_work::get_worktime(){//工作时长
    return ui->lineEdit_10->text();
}
bool Program3::finish_work::check_s16() {
    QString temp = ui->lineEdit_9->text();
    if (temp.size() != 22) {
        Mremind->show("装模清单必须为22位数字字母组合");
        return false;
    }
    for (int i = 0;i < temp.size();i++) {
        //        if (temp[i] >= 'a' && temp[i] <= 'z') {
        //            temp[i] = 32;//65,97
        //        }
        if (!(temp[i] >= 'A' && temp[i] <= 'Z') || (temp[i] >= '1' && temp[i] <= '9')) {
            Mremind->show("装模清单必须为22位数字字母组合");
            return false;
        }
    }
    return true;
}

void Program3::finish_work::on_pushButton_clicked()//剩余数按钮
{

        ui->pushButton->setText(get_residueNum());


}

void Program3::finish_work::on_pushButton_2_clicked()
{
    //标箱数按钮
    QString& s = my_socket->workInfo.instruction_id;
    if (s.contains("ZL")) {
        ui->pushButton_2->setText("2900");
        return;
    }
    QString q = QString("select CountPerBox from planstart2tab where CmdID = " + s.split(",")[0] +
            " and EndTime = " +  s.split(",")[2]).arg(getEndCount());
    QSqlQuery query = data_server->query_ctl(q);
    while(query.next()) {
        QString cnt = query.value(0).toString();
        ui->pushButton_2->setText(cnt);
    }
}
void Program3::finish_work::init(const QString& s) {//读取数据库数据配置显示项目
    if (s.right(2) == "01") {
        ui->horizontalLayout_7->setEnabled(true);
    }
    else {
        ui->horizontalLayout_7->setEnabled(false);
    }
    QSqlQuery query = data_server->query_ctl(QString("SELECT cBatchNo, cCountRatio, EndCount FROM plansteptab WHERE PlanStepID = '%1'").arg(s));
    while(query.next()) {//产品批次是否需要强制录入
        QString cBatchNo = query.value(0).toString();
        QString cCountRatio = query.value(1).toString();
        QString EndCount = query.value(2).toString();
        if (cBatchNo == "1") {
            ui->lineEdit_8->setEnabled(true);
        }
    }
}
bool Program3::finish_work::GetBoxIndex(int &nPlanCappIndex,int &nBatchCappIndex,const QString& s) {
    nPlanCappIndex = 0;
    nBatchCappIndex = 0;
    // 1 得到总是存在的计划箱号
    QSqlQuery query = data_server->query_ctl(QString("SELECT ExeBoxIndex,cProcessName FROM plansteptab WHERE PlanStepID = '%1'").arg(s));
    if (query.size() == 0)
    {
        Mremind->show("数据库中不存在该生产令码");
        return false;
    }
    while(query.next()) {
        int lval = query.value(0).toInt();
        processname = query.value(1).toString();
        nPlanCappIndex = lval + 1;
    }

    // 2 得到可能存在的批次箱号

    // 2.1 批次号为空，则不存在批次箱号
    if (ui->lineEdit_8->text() == "")
    {
        nBatchCappIndex = 0;
        return true;
    }
    // 2.2 批次号非空，则存在批次箱号
    else { // a 查询批次箱号
        query = data_server->query_ctl(QString("SELECT ExeBoxIndex FROM batchnotab "
                               "WHERE BatchNo = '%1' AND CappStepID = '%2%3'").arg(ui->lineEdit_8->text(),s.left(8),s.right(2)));
    }
    // b 若存在，则得到后返回
    if (query.size() == 1)
    {
        nBatchCappIndex = query.value(0).toInt() + 1;
        return true;
    }

    // c 若不存在，则插入1行后返回
    data_server->query_ctl(QString("INSERT INTO batchnotab (BatchNo,CappStepID) VALUES "
                "('%1','%2%3')").arg(ui->lineEdit_8->text(),s.left(8),s.right(2)));
    nBatchCappIndex = 1;
    return true;
}
QString Program3::finish_work::get_residueNum() {
    QString& s = my_socket->workInfo.instruction_id;
    if (s.contains("ZL")) {
        //Mremind->show("首道工序无剩余数");
        return QString("0");
    }
    QString q = QString("select EndCount,CountPerBox from planstart2tab where CmdID = " + s.split(",")[0] +
            " and EndTime = " +  s.split(",")[2]);//.arg(getEndCount());
    QSqlQuery query = data_server->query_ctl(q);
    if(query.size() == 0) {
        Mremind->show("找不到开工记录!");
         return QString();
    }
    while(query.next()) {
        int cnt = query.value(0).toInt();
        int sum = query.value(1).toInt();
        qDebug()<<sum<<" 剩余数     "<<cnt;
        return QString::number(sum - cnt);
    }
}
