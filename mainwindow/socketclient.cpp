#include "socketclient.h"
#include<QMessageBox>
#include<QFile>
QDataStream& operator >> (QDataStream &os,Equip &equip){
    os>>equip.test_place;
    os>>equip.equip;
    return os;
}
QDataStream& operator >> (QDataStream &os,worker_info &workInfo) {
    os>>workInfo.name;
    os>>workInfo.role;
    return os;
}
QDataStream& operator >> (QDataStream &os,local_env &localEnv){
    os>>localEnv.process;
    os>>localEnv.process_id;
    os>>localEnv.workstation;
    os>>localEnv.gauge_no;
    return os;
}
QDataStream& operator >> (QDataStream &os,message_worker_evn &messageWorkerEnv) {
    os>>messageWorkerEnv.workerInfo;
    os>>messageWorkerEnv.localEnv;
    return os;
}
QDataStream& operator<<(QDataStream &os,const struct work_info &info) {
    os<<info.worker_id;
    os<<info.product_id;
    os<<info.instruction_id;
    return os;
}
QDataStream& operator>>(QDataStream &os,infomation &a) {
    os>>a.product_no;
    os>>a.warn_thr;
    os>>a.chk_warn_thr;
    os>>a.detect_mode;
    os>>a.time_interval;
    os>>a.cycle_time;
    os>>a.sample_cnt;
    os>>a.disp_element_cnt;
    os>>a.trend_warn_win;
    os>>a.lock_time;
    return os;
}
QDataStream& operator>>(QDataStream &os,tabinfo &a) {
    os>>a.featureid;
    os>>a.normvalue;
    os>>a.zgc;
    os>>a.fgc;
    os>>a.jddw;
    os>>a.ejjddw;
    //os>>a.chk_warn_thr;
    //os>>a.warn_thr;
    os>>a.char_desc;
    return os;
}
socketclient::socketclient()
{
    t = 0;
    stop = false;
    start();
    socket = new QTcpSocket(this);
    //socket = new QLocalSocket(this);
    //connect(socket, QOverload<QLocalSocket::LocalSocketError>::of(&QLocalSocket::error),this,&socketclient::displayError);
    in.setDevice(socket);
    in.setVersion(QDataStream::Qt_5_6);
    QFile file("./ip");
    file.open(QIODevice::ReadOnly);
    QString ip = file.read(15);
    socket->connectToHost(QHostAddress(ip),6666);
    //socket->connectToServer("f3");
    if (socket->waitForConnected()) {
        qDebug()<<"connected";
    }
    else {
        qDebug()<<"connect failed";
    }
    //send_message(0);
    connect(socket, &QTcpSocket::readyRead, this, &socketclient::readmessage,Qt::QueuedConnection);//信号排队调用
    pCustomPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator<font></font>
    pCustomPlot->legend->setVisible(true);
    //QFont legendFont(QFont::Black);  // start out with MainWindow's font..<font></font>
    //legendFont.setPointSize(9); // and make a bit smaller for legend<font></font>
    //pCustomPlot->legend->setFont(legendFont);
    pCustomPlot->legend->setBrush(QBrush(QColor(255,255,255,0)));//230
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:<font></font>
    pCustomPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignRight);
    pCustomPlot->setAutoAddPlottableToLegend(false);


}
void socketclient::readmessage(){
    if (blockSize == 0) {
        // Relies on the fact that QDataStream serializes a quint32 into
        // sizeof(quint32) bytes
        if (socket->bytesAvailable() < (long)sizeof(quint32))
            return;
        in>>blockSize;
    }
    if (socket->bytesAvailable() < blockSize|| in.atEnd()){//
        //qDebug()<<socket->bytesAvailable()<<" "<<blockSize;
        return;
    }
    blockSize = 0;
    int flag;
    in>>flag;
    int size;
    int i,j,column;
    QString x1,y1;
    QCPGraphData a;
    switch (flag) {
    case 0:
        in>>info;
        in>>size;
        //qDebug()<<size;
        createinfo.resize(size);
        x.resize(size*2);
        y.resize(size*2);
        x_range.resize(size);
        for (i =0;i < size;i++) {
            x[i*2].resize(info.disp_element_cnt.toInt());
            y[i*2].resize(info.disp_element_cnt.toInt());
            x[i*2+1].resize(info.disp_element_cnt.toInt());
            y[i*2+1].resize(info.disp_element_cnt.toInt());
            x_range[i] = temp_xr(time.toTime_t(),time.toTime_t() + 3600*24,0);
            in>>createinfo[i];
            initpcustomplot(i*2);
            initpcustomplot(i*2+1);
        }
        pCustomPlot->yAxis->setRange(createinfo[0].normvalue + createinfo[0].fgc - createinfo[0].jddw,createinfo[0].normvalue + createinfo[0].zgc + createinfo[0].jddw);//y轴范围
        pCustomPlot->yAxis->ticker()->setTickCount((createinfo[0].zgc - createinfo[0].fgc)/createinfo[0].jddw + 1 + 1);
        pCustomPlot->replot(QCustomPlot::rpQueuedReplot);//刷新图表
        //qDebug()<<pCustomPlot->
        break;
    case 1:
        in>>i;
        tabnum = i;
        //qDebug()<<i;
        for (j = 0;j < pCustomPlot->graphCount();j++) {//只展示当前graph，其他隐藏
            if (j == i*2 || j == i*2 + 1) {
                pCustomPlot->graph(j)->setVisible(true);
            }
            else {
                pCustomPlot->graph(j)->setVisible(false);
            }
            //设置画布颜色
//            QLinearGradient plotGradient;
//            plotGradient.setStart();
//            plotGradient.setFinalStop();
//            plotGradient.setColorAt(0,QColor(Qt::red));
//            plotGradient.setColorAt(1,QColor(Qt::red));
//            pCustomPlot->setBackground(plotGradient);
        }
        qDebug()<<pCustomPlot->graphCount()<<" "<<i;
        pCustomPlot->xAxis->setRange(x_range[tabnum].start,x_range[tabnum].end);
        pCustomPlot->yAxis->setRange(createinfo[i].normvalue + createinfo[i].fgc - createinfo[i].jddw,createinfo[i].normvalue + createinfo[i].zgc + createinfo[i].jddw);//y轴范围
        pCustomPlot->yAxis->ticker()->setTickCount((createinfo[i].zgc - createinfo[i].fgc)/createinfo[i].jddw + 1 + 1);
        //pCustomPlot->yAxis->
        pCustomPlot->replot(QCustomPlot::rpQueuedReplot);//刷新图表
        //qDebug()<<createinfo[i].normvalue;
        break;
    case 2://接收点坐标
        in>>i;
        tabnum = i;
        in>>column;
        in>>y1;
        in>>x1;
        in>>user_ide;
        if (user_ide == 1) {
            //temp.push_back({x1.toDouble(),y1.toDouble(),tabnum*2});
            x[tabnum*2][column] = QDateTime::currentDateTime().toTime_t();
            y[tabnum*2][column] = y1.toDouble();
            //temp.push_back({x1.toDouble(),y1.toDouble(),tabnum*2});
            pCustomPlot->graph(tabnum*2)->addData(QDateTime::currentDateTime().toTime_t(),y1.toDouble());
            qDebug()<<x1<<" "<<y1<<" "<<user_ide;
            qDebug()<<QDateTime::currentDateTime().toTime_t();
        }
        else if(user_ide == 2){
            //temp.push_back({x1.toDouble(),y1.toDouble(),tabnum*2 + 1});
            x[tabnum*2 + 1][column] = QDateTime::currentDateTime().toTime_t();
            y[tabnum*2 + 1][column] = y1.toDouble();
            //temp.push_back({x1.toDouble(),y1.toDouble(),tabnum*2 + 1});
            pCustomPlot->graph(tabnum*2 + 1)->addData(QDateTime::currentDateTime().toTime_t(),y1.toDouble());
            //pCustomPlot->graph(tabnum*2 + 1)->addData(x1.toDouble(),y1.toDouble());
            qDebug()<<x1<<" "<<y1<<" "<<user_ide;
        }
        pCustomPlot->replot(QCustomPlot::rpQueuedReplot);//QCustomPlot::rpQueuedReplot
        break;
    case 3://remove
        in>>i;
        tabnum = i;
        in>>column;
        in>>user_ide;
        qDebug()<<column<<tabnum;
        if (user_ide == 1) {
            pCustomPlot->graph(tabnum*2)->data()->remove(x[tabnum*2][column]);
        }
        else if (user_ide == 2) {
            pCustomPlot->graph(tabnum*2 + 1)->data()->remove(x[tabnum*2 + 1][column]);
        }
        pCustomPlot->replot(QCustomPlot::rpQueuedReplot);
        break;
    case 4://code scan

        break;
    case 5:
        in>>messageWorkerEnv.workerInfo;
        qDebug()<<messageWorkerEnv.workerInfo.name;
        emit insert_data(1);
        break;
    case 6:
        in>>messageWorkerEnv.localEnv;
        qDebug()<<messageWorkerEnv.localEnv.workstation;
        emit insert_data(2);
        break;
    case 7:
        in>>messageWorkerEnv.equip;
        qDebug()<<messageWorkerEnv.equip.test_place;
        emit insert_data(3);
        break;

    case 8:
        label1->setText("非法用户,请重新扫描");
        check_flag[0] = 0;
        break;
    case 9:
        label1->setText("无此工作,请重新扫描");
        check_flag[1] = 0;
        break;
    case 10:
        label1->setText("无此产品,请重新扫描");
        check_flag[2] = 0;
        break;
    }
    if (socket->bytesAvailable() > 0) {
        emit socket->readyRead();
    }
}
void socketclient::run(){
    //pCustomPlot->graph(0)->data()->clear();
    qDebug()<<"thread start";
    while(!stop) {
//        sem.acquire();
        pCustomPlot->xAxis->setLabel("时间轴" + QDateTime::currentDateTime().toString());
         pCustomPlot->replot(QCustomPlot::rpQueuedReplot);
         sleep(1);
//        if (!stop){
//            pCustomPlot->graph(temp.front().tabnum)->addData(temp.front().x,temp.front().y);
//            temp.pop_front();
//            pCustomPlot->replot(QCustomPlot::rpQueuedReplot);
//        }
    }
    qDebug()<<"thread destroy";
}
socketclient::~socketclient(){
    stop = true;
    //sem.release();
    delete  socket;
    wait();
}
void socketclient::initpcustomplot(int num){//初始化plot
    QCPGraph *pGraph = pCustomPlot->addGraph();
    if (num > 1) {
        pCustomPlot->legend->removeItem(num);
    }
    pCustomPlot->xAxis->setLabel("时间轴" + QDateTime::currentDateTime().toString());
    pCustomPlot->yAxis->setLabel("误差");
    QDateTime dateTime = QDateTime::currentDateTime();
    QString s = dateTime.toString().split(" ")[0] + " " + dateTime.toString().split(" ")[1] + " " + dateTime.toString().split(" ")[2] + " " + "08:30:00" + " " + dateTime.toString().split(" ")[4];
    time = QDateTime::fromString(s);
    double start = time.toTime_t();
    int showtime = 60*60*24;
    //pCustomPlot->yAxis->setRange(min,max);//y轴范围
    QSharedPointer<QCPAxisTickerDateTime>timer(new QCPAxisTickerDateTime);
    timer->setDateTimeFormat("hh:mm\nMMMM.dd\nyyyy");
    //timer->setDateTimeFormat("hh:mm");//yyyy.MM.dd-
    //设置刻度


    timer->setTickCount(info.disp_element_cnt.toInt());


    pCustomPlot->xAxis2->setTicks(false);
    pCustomPlot->yAxis2->setTicks(false);
    //pCustomPlot->xAxis->setTickLabelRotation(35);
    //pCustomPlot->yAxis->setNumberFormat("gbc");
    //pCustomPlot->yAxis->setNumberPrecision(0.01);
    timer->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);
    pCustomPlot->xAxis->setTicker(timer);
    pCustomPlot->xAxis->setRange(start,start + showtime);//x轴范围
    pCustomPlot->axisRect()->setupFullAxesBox();
    //pCustomPlot->graph(num)->setSelectable(QCP::stDataRange);
    //pCustomPlot->setMultiSelectModifier(Qt::KeyboardModifier::ControlModifier);
    pCustomPlot->graph(num)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc,8));//实心点
    if (num%2) {
        pCustomPlot->graph(num)->setLineStyle(QCPGraph::lsNone);
        pCustomPlot->graph(num)->setPen(QPen(Qt::blue));
        if (num <= 1) {
            pCustomPlot->graph(num)->setName("核验员");
            pCustomPlot->graph(num)->addToLegend();
        }
    }
    else {
        pCustomPlot->graph(num)->setLineStyle(QCPGraph::lsLine);
        pCustomPlot->graph(num)->setPen(QPen(Qt::green));
        if (num <= 1) {
            pCustomPlot->graph(num)->setName("操作员");
             pCustomPlot->graph(num)->addToLegend();

        }
    }
        pCustomPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables|QCP::iMultiSelect);
}
void socketclient::displayError(QLocalSocket::LocalSocketError socketError) {

    switch (socketError) {
    case QLocalSocket::ServerNotFoundError:

        qDebug()<< "The host was not found. Please make sure "
                   "that the server is running and that the "
                   "server name is correct.";
        break;
    case QLocalSocket::ConnectionRefusedError:
        qDebug()<<"The connection was refused by the peer. "
                  "Make sure the fortune server is running, "
                  "and check that the server name "
                  "is correct.";
        break;
    case QLocalSocket::PeerClosedError:
        break;
    default:
        qDebug()<< "The following error occurred";
    }
}

