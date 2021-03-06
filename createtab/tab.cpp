#include "tab.h"
#include <QHeaderView>
#include<QHBoxLayout>
//#include<qcustomplot.h>
#include<QDebug>
#include<QVector>
#include<QMessageBox>
#include<QScrollBar>
#include<QResizeEvent>
extern const double eps;//double 比较精度
extern bool cmp_eq(const double& a,const double& b);

extern bool cmp_eg (const double& a,const double& b);
QDataStream& operator << (QDataStream &os,const worker_info &workInfo) {
    os<<workInfo.name;
    os<<workInfo.role;
    return os;
}
QDataStream& operator << (QDataStream &os,const local_env &localEnv){
    os<<localEnv.process;
    os<<localEnv.process_id;
    os<<localEnv.workstation;
    os<<localEnv.gauge_no;
    return os;
}
QDataStream& operator << (QDataStream &os,const Equip &equip){
    os<<equip.test_place;
    os<<equip.equip;
    return os;
}
QDataStream& operator << (QDataStream &os,const message_worker_evn &messageWorkerEnv) {
    os<<messageWorkerEnv.workerInfo;
    os<<messageWorkerEnv.localEnv;
    return os;
}

QDataStream& operator>>(QDataStream &os,struct work_info &info) {
    os>>info.worker_id;
    os>>info.product_id;
    os>>info.instruction_id;
    return os;
}
mytab::mytab() {
    //this->tabBar()->setMinimumWidth(80);
    color_scheme.resize(8);
    color_scheme[0] = Qt::green;
    color_scheme[1] = Qt::yellow;
    color_scheme[2] = Qt::red;
    color_scheme[3] = QColor::fromRgb(QRgb(0xFF8C00));//橙色
    color_scheme[4] = QColor::fromRgb(QRgb(0xC71585));//紫罗兰色
    color_scheme[5] = Qt::gray;
    color_scheme[6] = Qt::white;
    color_scheme[7] = Qt::blue;
    work_start_time = 8*3600 + 60*30;
    qDebug()<<work_start_time<<" work_start_time";

}
mytab::~mytab(){
    for (int i = 0;i < table.size();i++) {//释放所有tablewidget空间
        delete table[i];
    }
}
void mytab::showEvent(QShowEvent *) {
    int width = this->width();
    int tabcnt = this->count();

    int e_width = width/tabcnt;
    this->setStyleSheet( QString("QTabWidget{"
                         "background-color:transparent;"
                         "}"
                         "QTabWidget::pane{"
                         "    border:2px;"
                         "}"
                         "QTabWidget::tab-bar{"
                         "        alignment:left;"
                         "}"
                         "QTabBar::tab{"
                         "    background:rgb(14, 106, 175);"
                         "    color:white;"
                         "    min-width:%1px;"
                         "    min-height:50px;"
                         "}"
                         "QTabBar::tab:hover{"
                         "    background:rgb(255, 255, 255, 100);"
                         "color:black;"
                         "}"
                         "QTabBar::tab:selected{"
                         "    border-color: black;"
                         "    background:red;"
                         "    color:white;"
                         "}"
                         "QTabBar::scroller{width:50}"

                       ).arg(e_width));
    //this->tabBar()->setStyleSheet("QTabBar::scroller{width:50}");
//    this->setStyleSheet(QString("QTabBar::tab{height: 50px;min-width:%1px;}").arg(e_width));
}

bool mytab::eventFilter(QObject *o, QEvent *e) {
    if (o == this->tabBar()) {
        if (e->type() == QEvent::Wheel) {
            return true;
        }
        return QWidget::eventFilter(o,e);
    }
    return false;
}
void mytab::resizeEvent(QResizeEvent *e) {
    //this->tabBar()->resize(QSize(30,30));
   // e->ignore();
}

void mytab::flash_table(int start) {

    int numcolumn = info.disp_element_cnt.toInt();//总共
    QStringList verticalhead;
    for (int i = 0;i < numcolumn;i++) {
        QString m;
        if (start%3600) {
            m = start/60%60/10 >0 ?"":"0";
            m += QString::number(start/60%60);
        }
        else {
            m+="00";
        }
        if (start%60) {//gap默认是个小值,此时可能为非分钟为单位的记件，要表示到秒
            QString mt = start%60/10 > 0? "":"0";
            mt += QString::number(start%60);
            m = m + ":"  + mt;
            //qDebug()<<m;
        }
        verticalhead<<QString::number((start/3600)%24) + ":" + m;
        start+=this->table[0]->gap;
    }//暂时公用一个gap
    for (int i = 0;i < this->table.size();i++) {//恢复颜色和内容
        for (int j = 0;j < this->table[i]->columnCount();j++) {
            if (this->table[i]->flag[j].worker_row_flag >=0) {
                this->table[i]->item(this->table[i]->flag[j].worker_row_flag,j)->setBackground(QBrush(color_scheme[5]));
                this->table[i]->item(this->table[i]->flag[j].worker_row_flag,j)->setText("");

            }
            if (this->table[i]->flag[j].checker_row_flag >=0) {
                this->table[i]->item(this->table[i]->flag[j].checker_row_flag,j)->setBackground(QBrush(color_scheme[5]));
                this->table[i]->item(this->table[i]->flag[j].checker_row_flag,j)->setText("");
            }
            this->table[i]->flag[j] = {0,-1,-1,0,0,color_scheme[6],0};
        }
        this->table[i]->setHorizontalHeaderLabels(verticalhead);//水平表头
    }
}
void mytab::tabadd(tabinfo& createinfo,infomation& info) {//在mainwindow类中增加了一个可以动态增加tab的方法,传参为tab名
    qDebug()<<createinfo.fgc<<" "<<createinfo.zgc<<" "<<createinfo.jddw;
    QString temp;
    QString name = createinfo.char_desc + +"[ "  + "Φ" +  QString::number(createinfo.normvalue)  + " ]";
    if (createinfo.zgc - createinfo.fgc < createinfo.jddw) {
        QMessageBox box(QMessageBox::NoIcon,"输入错误","正负公差差值小于一级精度",NULL,NULL);
        box.exec();
        //exit(-1);
    }
    int numrow = cmp_eq(createinfo.normvalue,0)?2: (int)((createinfo.zgc - createinfo.fgc)/createinfo.jddw) + 1 + 1;//行数
    //OK,NG和普通版本


    qDebug()<<"正公差:"<<createinfo.zgc<<"负公差 "<<createinfo.fgc<<"精度单位 "<<createinfo.jddw;
    double gap;//按秒
    if (info.detect_mode == "0") {//按时间
        gap = info.time_interval.toDouble()*60;//时间间隔
    }
    else /*if (info.value2 == "1")*/{//按记件数
        gap = info.cycle_time.toDouble()*info.sample_cnt.toDouble();
        qDebug()<<gap;
    }
    double sum = createinfo.normvalue + createinfo.zgc;
    int numcolumn = info.disp_element_cnt.toInt();//总共
    QTime current_time =  QTime::currentTime();
    int hour = 8;
    int minute = 30;
    int second = 0;
    int start = hour*3600 + minute*60 + second;

    QWidget *widget = new QWidget();//泄漏了!!!!!
    QHBoxLayout *table_layout = new QHBoxLayout();
    my_tablewidget *t = new my_tablewidget();
    t->gap = gap;//   间隔
    qDebug()<<numrow<<" "<<numcolumn;

    table_layout->addWidget(t);
    qDebug()<<"debug";
    widget->setLayout(table_layout);
    t->setRowCount(numrow);
    t->setColumnCount(numcolumn);
    qDebug()<<"debug";
    QVector<tflag> columnc(numcolumn,{0,-1,-1,0,0,color_scheme[6],0});//flag初始化
    t->flag = columnc;
    table.push_back(t);//



    QStringList verticalhead;
    for (int i = 0;i < numcolumn;i++) {
        QString m;
        if (start%3600) {
            m = start/60%60/10 >0 ?"":"0";
            m += QString::number(start/60%60);
        }
        else {
            m+="00";
        }
        if (start%60) {//gap默认是个小值,此时可能为非分钟为单位的记件，要表示到秒
            QString mt = start%60/10 > 0? "":"0";
            mt += QString::number(start%60);
            m = m + ":"  + mt;
            //qDebug()<<m;
        }
        verticalhead<<QString::number((start/3600)%24) + ":" + m;
        start+=gap;
    }
    t->setHorizontalHeaderLabels(verticalhead);//水平表头
    //纵表头
    QStringList verti;
    if (cmp_eq(createinfo.normvalue,0)) {
        verti<<"OK"<<"NG";
        t->setVerticalHeaderLabels(verti);
    }
    else {
        verti.append(auto_zero(createinfo.jddw,createinfo.normvalue + createinfo.zgc) + "<X");
        for (int i = 1;i < numrow - 1;i++) {
            double temp = (sum - createinfo.jddw) < (createinfo.normvalue + createinfo.fgc)? createinfo.normvalue + createinfo.fgc:sum - createinfo.jddw;
            QString left = auto_zero(createinfo.jddw,temp);
            QString right = auto_zero(createinfo.jddw,sum);
            if (i != numrow - 2) {
                verti.append(left + "<" + "X" + "≤" + right);
            }
            else {
                verti.append(left + "≤" + "X" + "≤" + right);
            }
            sum = temp;
        }
        verti.append("X<"+ auto_zero(createinfo.jddw,createinfo.normvalue + createinfo.fgc));
        t->setVerticalHeaderLabels(verti);
        qDebug()<<t->rowCount()<<" "<<t->columnCount();
        t->verticalHeaderItem(0)->setBackground(QBrush(color_scheme[2]));
        qDebug()<<"color head end";
        t->verticalHeaderItem(t->rowCount()-1)->setBackground(QBrush(color_scheme[2]));
        t->warn_thr = info.warn_thr.toInt();
        while (t->rowCount() - 2 <= t->warn_thr*2) {
            t->warn_thr--;
        }
        qDebug()<<info.warn_thr<<"warn_thr";
        for (int i = 1;i <= t->rowCount() - 2;i++) {//设置垂直表头颜色
            if (i <= t->warn_thr || t->rowCount() -1 - i <= t->warn_thr) {
                t->verticalHeaderItem(i)->setBackground(QBrush(color_scheme[1]));//黄色
            }
            else {
                t->verticalHeaderItem(i)->setBackground(QBrush(color_scheme[0]));//绿色
            }

        }
        qDebug()<<"color head end";
    }
    for (int i = 0;i < numcolumn;i++) {
        for (int j = 0;j < numrow;j++) {
            if (!(t->item(j,i))) {
                t->setItem(j,i,new QTableWidgetItem());
                t->item(j,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                t->item(j,i)->setBackground(QBrush(color_scheme[5]));
            }
        }
    }
    t->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    t->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    t->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //t->setSelectionBehavior(QAbstractItemView::SelectItems);
    //t->setSelectionMode(QAbstractItemView::SingleSelection);//选中一行
    //t->setSelectionMode(QAbstractItemView::NoSelection);//取消选中样式
    t->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->addTab(widget,name);
}
int mytab::readxml(const work_info &workInfo,int flag) {
    QTime currenttime = QTime::currentTime();//获取当前时间
    int hour = 8;
    int minute = 30;
    int second = 0;
    //    int hour = currenttime.hour();
    //    int minute = currenttime.minute();
    //    int second = currenttime.second();
    start_time = hour*3600 + minute*60 + second;//初始化工作时间
    QFile file("./data/LocalSchemes.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"open failed !!!"<<endl;
        return -1;
    }
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        qDebug()<<"read xml failed !!!"<<endl;
        return -1;
    }
    file .close();
    QDomElement docelem = doc.documentElement();
    QDomNode n = docelem.firstChild();
    while(!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            QDomNodeList list = e.childNodes();
            QString name;
            if (e.tagName() == "Scheme") {
                info.product_no = e.attribute("product_no");
                if (info.product_no == workInfo.instruction_id.split(",")[1].mid(0,6)) {
                    info.warn_thr = e.attribute("warn_thr");
                    info.chk_warn_thr = e.attribute("chk_warn_thr");
                    info.detect_mode = e.attribute("detect_mode");
                    info.time_interval = e.attribute("time_interval");
                    info.cycle_time = e.attribute("cycle_time");
                    info.sample_cnt = e.attribute("sample_cnt");
                    info.disp_element_cnt = e.attribute("disp_element_cnt");
                    info.trend_warn_win = e.attribute("trend_warn_win");
                    info.lock_time = e.attribute("lock_time");
                    my.x.resize(list.count());
                    my.y.resize(list.count());
                    for (int i = 0;i < list.count();i++) {
                        QDomNode node = list.at(i);
                        QString comment = node.toElement().tagName();
                        if (comment == "Item") {
                            tabinfo temp;
                            temp.featureid = node.toElement().attribute("char_no");
                            temp.char_desc = node.toElement().attribute("char_desc");
                            temp.normvalue = node.toElement().attribute("spec_val").toDouble();
                            temp.zgc = node.toElement().attribute("tolerance").toDouble();
                            temp.fgc = node.toElement().attribute("n_tolerance").toDouble();
                            temp.jddw = node.toElement().attribute("pre_unit").toDouble();
                            temp.ejjddw = node.toElement().attribute("snd_pre_unit").toDouble();
                            //temp.chk_warn_thr = info.chk_warn_thr.toInt();
                            //temp.warn_thr = info.warn_thr.toInt();
                            if (flag == 0) {
                                createinfo.push_back(temp);//
                                qDebug()<<"tabadd";
                                tabadd(temp,info);
                            }
                        }
                    }
                    // exit(0);
                    return 0;
                }
            }
        }
        n = n.nextSibling();
    }
    return -1;
}

int mytab::read_local_authuser(const work_info &workInfo) {
    QFile file("./data/LocalAuthUser.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"open failed !!!"<<endl;
        return -1;
    }
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        qDebug()<<"read xml failed !!!"<<endl;
        return -1;
    }
    file.close();
    QDomElement docelem = doc.documentElement();
    QDomNode n = docelem.firstChild();
    while(!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            if (e.tagName() == "user") {
                if (e.attribute("user_id") == workInfo.worker_id.split(",")[1]) {
                    messageWorkerEvn.workerInfo.name = e.attribute("user_name");
                    messageWorkerEvn.workerInfo.role = e.attribute("role").toInt();
                    break;
                }
            }
        }
        n = n.nextSibling();
    }
    if (n.isNull()) {//遍历一遍未找到
        QMessageBox box(QMessageBox::NoIcon,"local_error","非法用户访问",NULL,NULL);
        box.exec();
        return -1;
    }
    //read_gauge(workInfo);
    return 0;
}
void mytab::read_gauge(work_info &workInfo) {
    QFile file("./data/LocalGauge.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"open gaugeinfo failed !!!"<<endl;
        return ;
    }
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        qDebug()<<"read xml failed !!!"<<endl;
        return ;
    }
    file.close();
    QDomElement docelem = doc.documentElement();
    QDomNode n = docelem.firstChild();
    qDebug()<<"open Gaugexml";
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            if (e.tagName() == "User") {
                if (e.attribute("user_id") == workInfo.worker_id.split(",")[1]) {
                    QDomNodeList list = e.childNodes();
                    for (int i = 0;i < list.size();i++) {
                        QDomNode node = list.at(i);
                        QDomElement e_node = node.toElement();
                        QString t = workInfo.instruction_id.split(",")[1].mid(0,6);
                        qDebug()<<t<<" "<<e_node.attribute("product_no");
                        if (e_node.tagName() == "Item" && e_node.attribute("product_no") == t && e_node.attribute("char_no").toInt()<= createinfo.size()) {
                            createinfo[e_node.attribute("char_no").toInt() - 1].gauge = e_node.attribute("gauge_no");
                            qDebug()<<createinfo[e_node.attribute("char_no").toInt() - 1].gauge<<"gauge_no!!!";
                        }
                    }
                }
            }
        }
        n = n.nextSibling();
    }
}

int mytab::read_local_env(const work_info &workInfo,int flag) {
    QFile file("./data/LocalEnv.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"open failed !!!"<<endl;
        return -1;
    }
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        qDebug()<<"read xml failed !!!"<<endl;
        return -1;
    }
    file.close();
    QDomElement docelem = doc.documentElement();
    QDomNode n = docelem.firstChild();
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            if (flag == 0) {
                if (e.tagName() == "ProProcess") {
                    QDomNodeList list = e.childNodes();
                    int i;
                    for (i = 0;i < list.size();i++){
                        QDomElement node_e = list.at(i).toElement();
                        qDebug()<<workInfo.instruction_id.split(",")[2].mid(6,2)<<"process_id"<<workInfo.instruction_id;
                        if (node_e.tagName() == "env" && node_e.attribute("process_id") == workInfo.instruction_id.split(",")[1].mid(6,2)) {
                            messageWorkerEvn.localEnv.process = node_e.attribute("process");
                            messageWorkerEvn.localEnv.process_id = workInfo.instruction_id.split("")[1].mid(6,2);
                            break;
                        }

                    }
                    if (i == list.size()) {
                        return -1;
                    }
                    qDebug()<<messageWorkerEvn.localEnv.process<<"process";
                    //查找是否有该产品号
                }
                else if (e.tagName() == "LocalEnv") {
                    QDomNodeList list = e.childNodes();
                    for (int i = 0;i < list.size();i++){
                        QDomElement node_e = list.at(i).toElement();
                        if (node_e.tagName() == "env") {

                            messageWorkerEvn.localEnv.workstation = node_e.attribute("workstation");
                            messageWorkerEvn.localEnv.gauge_no = node_e.attribute("gauge_no");
                        }

                    }
                }
            }
            if (flag == 1) {
                if (e.tagName() == "LocaleEquip") {
                    QDomNodeList list = e.childNodes();
                    int node_tmp = 0;
                    for (int i = 0;i < list.size();i++){
                        QDomElement node_e = list.at(i).toElement();
                        qDebug()<<workInfo.product_id.split(",")[1].mid(0,4);
                        if (node_e.tagName() == "Equip" && node_e.attribute("equip_id") == workInfo.product_id.split(",")[1].mid(0,4)) {

                            messageWorkerEvn.equip.equip = node_e.attribute("equip");
                            node_tmp = 1;
                            break;
                        }

                    }
                    if (node_tmp == 0) {
                        return -1;
                    }
                }
                else if (e.tagName() == "TestPlace") {
                    QDomNodeList list = e.childNodes();
                    int node_tmp = 0;
                    for (int i = 0;i < list.size();i++){
                        QDomElement node_e = list.at(i).toElement();
                        qDebug()<<workInfo.product_id.split(",")[1].mid(4,2);
                        if (node_e.tagName() == "Place" && node_e.attribute("place_id") == workInfo.product_id.split(",")[1].mid(4,2)) {

                            messageWorkerEvn.equip.test_place = node_e.attribute("test_place");
                            node_tmp = 1;
                            break;
                        }

                    }
                    if (node_tmp == 0) {
                        return -2;
                    }
                }
            }

        }

        n = n.nextSibling();
    }
    return 0;
}

int  mytab::nekwork_or_local() {//0为网络版1为本地版
    //    QFile file("./data/GeneralConfig.xml");
    //    if (!file.open(QIODevice::ReadOnly)) {
    //        QMessageBox messageBox;
    //        messageBox.setText("open ./GeneralConfig.xml failed !");
    //        messageBox.exec();
    //        return -1;
    //    }
    //    QDomDocument doc;
    //    if (!doc.setContent(&file)) {
    //        file.close();
    //        QMessageBox messageBox;
    //        messageBox.setText("read GeneralConfig.xml failed !");
    //        messageBox.exec();
    //        return -1;
    //    }
    //    file.close();
    //    QDomElement domele = doc.documentElement();
    //    QDomNode n = domele.firstChild();
    //    while (!n.isNull()) {
    //        if (n.isElement()) {
    //            QDomElement e = n.toElement();
    //            if (e.tagName() == "WorkMode") {
    //                net_plugin.status = e.attribute("mode");
    //            }
    //            else if (e.tagName() == "DatabaseConnect") {
    //                QDomNodeList list = e.childNodes();
    //                qDebug()<<list.count()<<"databaseconnect";
    //                for (int i = 0;i < list.count();i++) {
    //                    if (list.at(i).toElement().tagName() == "RemoteDatabase") {
    //                        net_plugin.hostname = list.at(i).toElement().attribute("hostName");
    //                        net_plugin.port = list.at(i).toElement().attribute("port");
    //                        net_plugin.databaseName = list.at(i).toElement().attribute("databaseName");
    //                        net_plugin.userName =list.at(i).toElement().attribute("userName");
    //                        net_plugin.passwd = list.at(i).toElement().attribute("password");
    //                        qDebug()<<net_plugin.status<<" "<<net_plugin.hostname<<" "<<net_plugin.port;
    //                    }
    //                }
    //            }
    //            else if (e.tagName() == "SerialPorts") {
    //                QDomNodeList list = e.childNodes();
    //                //qDebug()<<list.count()<<"serialPorts";
    //                for (int i = 0;i < list.count();i++) {
    //                    QDomElement temp = list.at(i).toElement();
    //                    qDebug()<<temp.tagName();
    //                    if (temp.tagName() == "SerialPort") {
    //                        Serial_port[temp.attribute("device")] = {temp.attribute("portName"),
    //                                temp.attribute("baudRate"),temp.attribute("dataBits"),temp.attribute("stopBits"),
    //                                temp.attribute("parity"),temp.attribute("writeBufferSize"),
    //                                temp.attribute("readBufferSize")};

    //                        //qDebug()<<Serial_port[temp.attribute("device")].parity;

    //                    }
    //                }
    //            }
    //        }
    //        n = n.nextSibling();
    //    }
    //    return net_plugin.status.toInt();
}
QString mytab::auto_zero(double from, double to) {
    QString tos = QString::number(to);
    QString froms = QString::number(from);
    if (cmp_eq(from,0)) {
        froms = "0";
    }
    if (cmp_eq(to,0)) {
        tos = "0";
    }
    if (froms.contains(".")) {
        if (tos.contains(".")) {
            int zero_size = froms.split(".")[1].size() - tos.split(".")[1].size();
            QString zero(zero_size,'0');
            tos += zero;
        }
        else {
            int zero_size = froms.split(".")[1].size();
            QString zero(zero_size,'0');
            tos = tos + "." + zero;
        }
    }
    else {
        qDebug()<<"该精度无小数点";
    }
    return tos;
}
void mytab::trend_warn() {//趋势预警处理函数

}
void mytab::modify_gauge(work_info &workInfo, int index) {
    QFile file("./data/LocalGauge.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"open gaugeinfo failed !!!"<<endl;
        return ;
    }
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        qDebug()<<"read xml failed !!!"<<endl;
        return ;
    }
    file.close();
    QDomElement docelem = doc.documentElement();
    QDomNode n = docelem.firstChild();
    qDebug()<<"open Gaugexml";
    while (!n.isNull()) {
        if (n.isElement()) {
            QDomElement e = n.toElement();
            if (e.tagName() == "User") {
                if (e.attribute("user_id") == workInfo.worker_id.split(",")[1]) {
                    QDomNodeList list = e.childNodes();
                    int i = 0;
                    for (;i < list.size();i++) {
                        QDomNode node = list.at(i);
                        QDomElement e_node = node.toElement();
                        if (e_node.tagName() == "Item" &&  e_node.attribute("char_no").toInt() == index + 1) {
                            //modify
                            e_node.setAttribute("gauge_no",this->createinfo[index].gauge);
                            break;
                        }
                    }
                    if (i == list.size()) {
                        //add
                        QDomElement addInfo=doc.createElement("Item");
                        addInfo.setAttribute("product_no",workInfo.instruction_id.split(",")[1].mid(0,6));
                        addInfo.setAttribute("char_no",index + 1);
                        addInfo.setAttribute("char_desc",createinfo[index].char_desc);
                        addInfo.setAttribute("gauge_no",createinfo[index].gauge);
                        e.appendChild(addInfo);
                    }
                }
            }
        }
        n = n.nextSibling();
    }
    if(!file.open(QFile::WriteOnly|QFile::Truncate)){ return;} //先读进来，再重写，如果不用truncate就是在后面追加内容，就无效了
    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();
}


