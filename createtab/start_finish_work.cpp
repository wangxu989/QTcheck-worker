#include "start_finish_work.h"
#include "ui_start_finish_work.h"
extern database_server *data_server;
extern int mode;
start_finish_work::start_finish_work(const QString& name, QWidget *parent) :

    //QWidget(parent),
    ui(new Ui::start_finish_work),
    my_xml(xml::get_xml()),
    name_P(name)
{
    add_p(name,this);
    ui->setupUi(this);
}

start_finish_work::~start_finish_work()
{
    delete ui;
}
bool start_finish_work::start_P() {
    if (!listen(my_socket)) {
        qDebug()<<"start failed!";
        return false;
    }
    //业务逻辑，此功能为开工/完工
    qDebug()<<"P3";
    key = QSharedPointer<keyboard_widget>(new keyboard_widget("Enter",new composite_label_factory()));
    connect(key->figure,&QTableWidget::cellClicked,this,&start_finish_work::in_keyboard);
    ui->widget->setLayout(key->layout());
#ifdef MY_P3
    my_progress.start("./plugin/start_work");
#else
    my_progress.startDetached("./plugin/3.sh");
#endif
    //emit MyWidget::change_widget(this);
    connect(my_socket,&socket::check_info,this,&start_finish_work::check_info);
    connect(my_socket,&socket::transf_processID,this,&start_finish_work::deal_ProcessID);
    connect(my_socket,&socket::deal_rec,this,&start_finish_work::deal_rec);
    connect(my_socket,&socket::delete_start2tab,this,&start_finish_work::delete_start2tab);
    connect(my_socket,&socket::add_start2tab,this,&start_finish_work::add_start2tab);
    connect(my_socket,&socket::finish_work_processID,this,&start_finish_work::finish_work_processID);
    return true;
}
void start_finish_work::finish_P() {
#ifdef MY_P3
    my_progress.close();
#endif
    remove_P(name_P);
    emit MyWidget::change_widget(nullptr);
    disconnect(my_socket,&socket::check_info,this,&start_finish_work::check_info);
    disconnect(my_socket,&socket::transf_processID,this,&start_finish_work::deal_ProcessID);
    disconnect(my_socket,&socket::deal_rec,this,&start_finish_work::deal_rec);
    disconnect(my_socket,&socket::delete_start2tab,this,&start_finish_work::delete_start2tab);
    disconnect(my_socket,&socket::add_start2tab,this,&start_finish_work::add_start2tab);
    disconnect(my_socket,&socket::finish_work_processID,this,&start_finish_work::finish_work_processID);
    disconnect(key->figure,&QTableWidget::cellClicked,this,&start_finish_work::in_keyboard);
    system("killall start_work");
    delete this;
}
void start_finish_work::check_info(int flag) {
    qDebug()<<ui->pushButton->text();
    qDebug()<<"check_info"<<flag<<"mode :"<<mode;
    if (start_flag != 0) {
        return;
    }
    switch (flag) {
    case 1:
        //if (my_xml.read_local_authuser(my_socket->workInfo) == 0) {
        ret_checkout[0] = 1;//员工码
        if(my_socket->clientConnection) {
            //my_socket->sendmessage(5,my_xml.messageWorkerEvn.workerInfo);
            search_base();
            qDebug()<<"send workerinfo!";
        }
        else {
            qDebug()<<"send failed!";
        }
        //}
        //else {
        //  my_socket->sendmessage(8);
        //}
        //}
        // else if (mode == 1) {
        // }
        qDebug()<<my_xml.messageWorkerEvn.workerInfo.name;
        break;
    case 2:
        //if (mode == 0) {
        //if (my_xml.readxml(my_socket->workInfo,1) == 0) {
        ret_checkout[1] = 1;
        if (my_xml.read_local_env(my_socket->workInfo,0)==0) {
            if(my_socket->clientConnection) {
                //my_socket->sendmessage(6,my_xml.messageWorkerEvn.localEnv);//图表信息
                qDebug()<<"send workinfo!";
                qDebug()<<my_xml.messageWorkerEvn.localEnv.workstation;
            }
            else {
                qDebug()<<"send failed!";
            }
        }
        //}
        //else {
        //   my_socket->sendmessage(9);
        //}
        //}
        //else if (mode == 1) {
        //}
        break;
    case 3:
        //if (mode == 0) {
        //if (my_xml.read_local_env(my_socket->workInfo,1)==0) {
        if(my_socket->clientConnection) {
            //my_socket->sendmessage(7,my_xml.messageWorkerEvn.equip);
            qDebug()<<"send equipinfo!";
        }
        else {
            qDebug()<<"send failed!";
        }
        ret_checkout[2] = 1;//设备码
        //}
        //else {
        //  my_socket->sendmessage(10);
        //}
        //}
        //else if (mode == 1) {
        //}
        break;
    }
}
void start_finish_work::search_base() {
    int time_scope = my_xml.read_start_finish_config();
    QString cmp_end = time->get_time_format1(time_scope);
    QString cmp =time->get_currenttime();
    qDebug()<<"time         "<<cmp;
    QString s = "select * from planstart2tab where StartUser = " + my_socket->workInfo.worker_id.split(",")[1] + " and StartTime >= " + "'" + cmp + "'";
    QSqlQuery query =  data_server->query_ctl(s);

    if (query.size() > 0) {
        my_socket->sendmessage(82,query.size());
    }
    while(query.next()) {
        start.ID = query.value(0).toString();
        start.EndTime = query.value(1).toString();
        start.MaterialInf = query.value(2).toString();
        start.StartUser = query.value(6).toString();
        start.EndCount = query.value(4).toString();
        start.StartTime = query.value(7).toString();
        start.DevID = query.value(11).toString();
        start.remaind_count = query.value(9).toString();
        start.ModeList = query.value(12).toString();
        qDebug()<<start.ID;
        my_socket->sendmessage(80,start);
    }
    qDebug()<<cmp_end;
    s = "select * from planqrtab where s5 = " + my_socket->workInfo.worker_id.split(",")[1] + " and s2 >= " + "'" + cmp_end + "'";
    query = data_server->query_ctl(s);
    if (query.size() > 0) {
        my_socket->sendmessage(83,query.size());
    }
    finish_work finish;
    while(query.next()) {
        finish.ID = query.value(0).toString();
        finish.EndTime = query.value(2).toString();
        finish.EndCount = query.value(7).toString();
        finish.MaterialInf = query.value(14).toString();
        finish.onhand = query.value(8).toString();
        finish.isPrint = query.value(28).toString();
        finish.probatch = query.value(15).toString();
        finish.residueNum = query.value(27).toString();
        my_socket->sendmessage(81,finish);
    }

}

void start_finish_work::on_pushButton_4_clicked()
{
    finish_P();
}

void start_finish_work::on_pushButton_2_clicked()//切换,需要改变子程序状态
{
    status = !status;
    if (status) {//开工
        ui->pushButton->setText("完工");
    }
    else {//完工
        ui->pushButton->setText("开工");
    }
    my_socket->sendmessage(88);
}

void start_finish_work::on_pushButton_6_clicked()//reduce
{
    if (status) {//plansteptab
        data_server->reducesteptab(1);
    }
    else {//plantab
        data_server->reducetab(1);
    }
}

void start_finish_work::on_pushButton_7_clicked()//add
{
    if (status) {//2
        data_server->add_steptab(1);
    }
    else {
        data_server->add_tab(1);
    }
}

void start_finish_work::on_pushButton_5_clicked()//删除
{
    my_socket->sendmessage(89);
}
void start_finish_work::deal_ProcessID(QString &s) {//解析生产令
    QString temp = "select * from plansteptab where PlanStepID = '" + s.split(",")[1] + "'";
    QSqlQuery query = data_server->query_ctl(temp);
    qDebug()<<temp;
    if (query.size() > 0){
        ret_checkout[1] = 1;
    }
    while (query.next()) {
        ProInf.cMustQC = query.value(12).toString();
        ProInf.cStdCount = query.value(13).toString();

        qDebug()<<"CMustqc";
    }
    temp = "select * from plantab where PlanID = '" + s.split(",")[1].mid(0,s.split(",")[1].size() - 2) + "'";
    query = data_server->query_ctl(temp);
    qDebug()<<temp;
    while (query.next()) {
        std::get<0>(res_finish_sb_and_material) = query.value(4).toString();//material
        ProInf.ElseInf = query.value(4).toString();
    }
    my_socket->sendmessage(84,ProInf);
    Program3::finish_work *t = dynamic_cast<Program3::finish_work*>((dynamic_cast<composite_label*>(key.data()->get_display()))->get_widget());
    t->init(s.split(",")[1]);
}

void start_finish_work::on_pushButton_clicked()//开工
{
    if (ui->pushButton->text() == "开工确认") {
        if(ret_checkout[0] != 1) {
            Mremind->show("请扫描员工码");
            return;
        }
        else if (ret_checkout[1] != 1) {
            Mremind->show("请扫描生产令码");
            return;
        }
        else if (ret_checkout[2] != 1) {
             Mremind->show("请扫描设备码");
             return;
        }
        else if (ret_checkout[3] != 1) {
             Mremind->show("请扫描生产记录码");
             return;
        }
        ui->pushButton->setText("开工");
        ui->pushButton_2->setEnabled(true);//切换开
        my_socket->sendmessage(87);
        flash_rec();
    }
    else if (ui->pushButton->text() == "开工"){
        my_socket->sendmessage(91);
        ui->pushButton->setText("开工确认");
        ui->pushButton_2->setEnabled(false);//关切换
        my_socket->sendmessage(85);
    }
    else if (ui->pushButton->text() == "完工") {
        ui->pushButton->setText("完工确认");
        //ui->widget->layout()->removeWidget(key->get_widget());
        //ui->widget->layout()->addWidget(finish_widget.data());
        ui->pushButton_2->setEnabled(false);//关切换
        my_socket->sendmessage(90);
        my_socket->sendmessage(85);
    }
    else if (ui->pushButton->text() == "完工确认") {
        if(ret_checkout[0] != 1) {
            Mremind->show("请扫描员工码");
            return;
        }
        else if (!((ret_checkout[2] == 1 && ret_checkout[1] == 1)|| ret_checkout[3] == 1)) {
            Mremind->show("首工序请扫生产记录码，其余工序请扫生产令和生产记录码");
            return;
        }
        Program3::finish_work *temp = dynamic_cast<Program3::finish_work*>((dynamic_cast<composite_label*>(key.data()->get_display()))->get_widget());
        if (!temp->check()) {//检查数据合理性，以及更新数据
            return;
        }
        qDebug()<<"check successed!";
        //数据库内新增数据
        ElseInf inf;
        inf.EndTime = temp->getCurrentTime();
        inf.EndCount = temp->getEndCount();
        inf.residueNum = temp->get_residueNum();
        if(inf.residueNum == "") {
            return;
        }
        inf.probatch = temp->get_Probatch();
        inf.UserID = temp->get_Finish_Count();
        my_socket->sendmessage(93,inf);
        QString instruction_ID = my_socket->workInfo.instruction_id.contains("ZL") ? my_socket->workInfo.instruction_id.split(",")[1]:my_socket->workInfo.instruction_id.split(",")[0];
        QString end_time = time->get_time_format1();
        if (start_time  == "") {//首工序开工时间为空
            start_time  = end_time;
        }
        QString s = QString("insert into planqrtab (s0,s1,s2,s5,s6,s7,s8,s10,s11,s12,s14,s15,s16)"
                            "values('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11','%12','%13')").arg(instruction_ID).arg(start_time).arg(end_time).arg(my_socket->workInfo.worker_id.split(",")[1])
                .arg((std::get<1>(res_finish_sb_and_material) != "" ?std::get<1>(res_finish_sb_and_material):my_socket->workInfo.product_id.split(",")[1])).arg(temp->getEndCount()).arg(temp->get_Finish_Count())
                .arg(temp->get_s10()).arg(temp->get_s11()).arg(temp->get_s12()).arg(std::get<0>(res_finish_sb_and_material)).arg(temp->get_Probatch()).arg(temp->get_s16());
        qDebug()<<end_time<<"time";
        qDebug()<< my_socket->workInfo.product_id<<" "<<std::get<0>(res_finish_sb_and_material);
        qDebug()<<s;
        data_server->query_ctl(s);
//        // A 信息头部
//                // [0]20位生产令号,[1]12位开始时间,[2]12位结束时间,[3]计划箱号,[4]批次箱号,
//                // [5]工号,[6]设备号,[7]成品数,[8]待处理品数,[9]工作时长,[10]热处理号,[11]表面处理号,[12]检验报告,
//                // [13]工序名称,[14]物料信息,[15]产品批次号,[16]装模清单,[17]1位二维码类别（1一对一，2多对一）,
//    //            sCodeInf.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,2,",
//    //                sEnd[0], sStartTime, sEnd[5], sCappIndex, sBatchIndex, sEnd[13],
//    //                sEnd[6], sEnd[7], sEnd[8], sEnd[9], sEnd[10], sEnd[11],
//    //                sEnd[12], sEnd[1], sEnd[2], sEnd[3], sEnd[4]);

//                // B 信息中部（形式上一样，含义不同：前工序信息的生产令号均相同，前热处理、前表面处理通过合并同类项得到）
//                // [18]前热处理数量：数量,
//                // [19]前表面处理数量：数量,
//                // [20]前工序信息数量：数量,
//                // C 信息尾部
//                // [21]前热处理：号1,号2,...,
//                // [21 + [18]] 前表面处理：号1,号2,...,
//                // [21 + [18] + [19]]前工序信息：[工号1,设备1,成品数1,待处理品数1,完成时间1,剩余数1,生产数1],...,
        Qrencode =  (instruction_ID + ","  + start_time + "," + end_time + "," +  QString::number(temp->nPlanCappIndex) + "," + QString::number(temp->nBatchCappIndex)
                + "," + my_socket->workInfo.worker_id.split(",")[1] + "," + my_socket->workInfo.product_id.split(",")[1] + "," + temp->getEndCount() + "," + temp->get_Finish_Count()
                + "," + temp->get_worktime() + "," + temp->get_s10() + "," + temp->get_s11() + "," + temp->get_s12() + "," + temp->processname + "," + std::get<0>(res_finish_sb_and_material)
                + "," + temp->get_Probatch() + "," + temp->get_s16() + ",");
        qDebug()<<Qrencode;
        ui->pushButton->setText("完工结束");
        flash_rec();
    }
    else if (ui->pushButton->text() == "完工结束") {
        my_socket->sendmessage(94);
        ui->pushButton->setText("完工");
        ui->pushButton_2->setEnabled(true);//切换开
    }
}
void start_finish_work::deal_rec(QString &s) {//生产记录
    QString key1 = s.split(",")[0];
    QString key2 = s.split(",")[2];
    QString temp = "select * from planqrtab where s0 = '"  + key1  + "'" + " and s2 = '" + key2 + "'";
    QSqlQuery query = data_server->query_ctl(temp);
    qDebug()<<temp<<" "<<query.size();
    if (query.size() > 0) {
        ret_checkout[3] = 1;
    }
    while(query.next()) {
        elseinf.ID = query.value(0).toString();
        elseinf.MaterialInf = query.value(14).toString();
        elseinf.EndCount = query.value(7).toString();
        elseinf.EndTime = query.value(2).toString();
        elseinf.UserID = query.value(5).toString();
        elseinf.probatch = query.value(15).toString();
        elseinf.residueNum = query.value(27).toString();
        my_socket->sendmessage(86,elseinf);
    }
    if (ret_checkout[0] == 1 && ret_checkout[1] == 1 && ret_checkout[2] == 1 && ret_checkout[3] == 1) {
        ui->pushButton->setEnabled(true);
    }
}
void start_finish_work::delete_start2tab(QString &s) {
    QString temp = "delete from planstart2tab where BlankID = '" + s + "'";
    data_server->query_ctl(temp);
}
void start_finish_work::add_start2tab(const start_rec &s) {
    QString cmdid = s.ID;
    cmdid = QString::number(cmdid.toInt() + 1);
    QString temp = QString("insert into planstart2tab (BlankID,EndTime,MaterialInf,EndCount,StartUser,StartTime,DevID,CmdID)"
                           "values"
                           "('%1','%2','%3','%4','%5','%6','%7','%8')").arg(s.ID,s.EndTime,s.MaterialInf,s.EndCount,s.StartUser,s.StartTime,s.DevID,cmdid);
    data_server->query_ctl(temp);

}
void start_finish_work::in_keyboard(const int &row,const int &column) {//键盘
    qDebug()<<row<<" "<<column;
    if (row == 0 && column == 3) {//delete
        key->removeText();
    }
    else if (row == 2 && column == 3) {//enter
        //打印
        qDebug()<<"打印";
        //my_socket->sendmessage(47);

    }
    else {
        key->addText(row,column);
    }
    //    if (key->getVal() != key->lastquery()) {//软件盘发生改变了
    //        button_ctl::notify();
    //    }
    //    else {
    //        button_ctl::recover();
    //    }
}
void start_finish_work::finish_work_processID(QString &s) {//非首道工序将物料、设备信息发送给客户端
    ret_checkout[3] = 1;
    if(s.contains("ZL")) {//首道工序
        return;
    }
//    if(s.contains("ZL")) {
//        elseinf.ID = s.split(",")[1];
//    }
//    else {
        elseinf.ID = s.split(",")[0];
    //}
    QString instructionID = s.split(",")[0];
    QString q = "select * from planstart2tab where CmdID = " + s.split(",")[0] + " and EndTime = " +  s.split(",")[2];
    qDebug()<<q;
    QSqlQuery query = data_server->query_ctl(q);
    if (query.size() == 0 && s.split(",")[0].right(2) != "01") {
        Mremind->show("非首工序，请录入开工信息");
        return;
    }
    qDebug()<<query.size();
    while(query.next()) {
        if (start_time == "") {
            start_time = query.value(7).toString();
        }
        QString tempID = query.value(0).toString();
        if(tempID.left(18) != instructionID.left(18))
        {
            Mremind->show("开工信息和完工信息必须属于同一生产计划。");
            return;
        }
        if (tempID.right(2).toInt() + 1 != instructionID.right(2).toInt()) {
            qDebug()<<tempID<<" "<<instructionID;
            Mremind->show("开工工序和完工序必须顺序相邻。");
            return;
        }
        std::get<0>(res_finish_sb_and_material) = query.value(2).toString();//m
        std::get<1>(res_finish_sb_and_material) = query.value(11).toString();//sb

        my_socket->workInfo.product_id = std::get<1>(res_finish_sb_and_material);
        my_socket->sendmessage(92,std::get<0>(res_finish_sb_and_material),std::get<1>(res_finish_sb_and_material));
    }
    QDateTime dateTime = QDateTime::fromString(start_time);
    QLocale locale;//指定英文显示
    QString strFormat = "yyyyMMddhhmm";
    start_time = locale.toString(dateTime, strFormat);
    qDebug()<<"start_time:   "<<start_time;
    Program3::finish_work *temp = dynamic_cast<Program3::finish_work*>((dynamic_cast<composite_label*>(key.data()->get_display()))->get_widget());
    temp->init(s.split(",")[0]);
}

void start_finish_work::on_pushButton_3_clicked()
{
    QString s = Qrencode;
    qDebug()<<Qrencode;
    QRcode *qrcode;
    qrcode = QRcode_encodeString(s.toStdString().c_str(), 2, QR_ECLEVEL_Q, QR_MODE_8, 1);
    qint32 temp_width=80; //二维码图片的大小
    qint32 temp_height=80;
    qint32 qrcode_width = qrcode->width > 0 ? qrcode->width : 1;
    double scale_x = (double)temp_width / (double)qrcode_width; //二维码图片的缩放比例
    double scale_y =(double) temp_height /(double) qrcode_width;
    QImage mainimg=QImage(temp_width,temp_height,QImage::Format_ARGB32);
    QPainter painter(&mainimg);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, temp_width, temp_height);
    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    for( qint32 y = 0; y < qrcode_width; y ++)
    {
        for(qint32 x = 0; x < qrcode_width; x++)
        {
            unsigned char b = qrcode->data[y * qrcode_width + x];
            if(b & 0x01)
            {
                QRectF r(x * scale_x, y * scale_y, scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }
    QPixmap mainmap=QPixmap::fromImage(mainimg);
    mainmap.save("./buffer/buf_img.png");
    my_socket->sendmessage(54);
    //发数据给串口
    port_print.write("\r\n");
    port_print.write("SIZE 60 mm,40 mm\r\n");
    port_print.write("GAP 0\r\n");
    port_print.write("DENSITY 8\r\n");
    port_print.write("SPEED 5\r\n");
    port_print.write("DIRECTION 0\r\n");
    port_print.write("REFERENCE 0,0\r\n");
    port_print.write("CLS\r\n");
    port_print.write("QRCODE 20,16,L,5,A,0,\""+s+"\"\r\n");
    port_print.write("PRINT 1,1\r\n");
}
