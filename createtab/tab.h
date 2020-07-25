#ifndef TAB_H
#define TAB_H
#include<QWidget>
#include<QString>
#include <QFile>
#include<QtXml/QDomDocument>
#include<QTableWidget>
#include<QMouseEvent>
#include<QDateTime>
#include<QTime>
#include<QObject>
#include<QCoreApplication>
#include<QVector>
#include<QLabel>
#include<QApplication>
#include<QAbstractButton>
#include<QStyleOption>
#include<QStylePainter>
#include<QTableView>
#include<QHeaderView>
#include<QScrollArea>
#include<QAbstractScrollArea>
#include<QScrollBar>
#pragma pack(1)
//发送给进程2的信息（人员，设备信息）
typedef struct worker_info{
    QString name;
    int role;
    friend QDataStream& operator << (QDataStream &os,worker_info &workInfo);
}worker_info;
typedef struct local_env{
    QString process;
    QString process_id;
    //QString test_place;
    //QString equip;
    QString workstation;
    QString gauge_no;
    friend QDataStream& operator << (QDataStream &os,local_env &localEnv);
}local_env;
typedef struct Equip{
    QString test_place;
    QString equip;
    friend QDataStream& operator << (QDataStream &os,Equip & equip);
}Equip;
typedef struct message_worker_evn{
    worker_info workerInfo;
    local_env localEnv;
    Equip equip;
    friend QDataStream& operator << (QDataStream &os,message_worker_evn &messageWorkerEnv);
}message_worker_evn;



//接受扫码枪信息
typedef struct work_info{
    QString worker_id;
    QString product_id;
    QString instruction_id;
    QString checker_id;
    friend QDataStream& operator>>(QDataStream &os,struct work_info &info);
}work_info;
class infomation{
public:
    friend QDataStream& operator<<(QDataStream &os,infomation &a);
    QString product_no;//产品号
    QString warn_thr;//预警阈值
    QString chk_warn_thr;//复核报警阈值
    QString detect_mode;//抽检方式
    QString time_interval;//抽检时间间隔
    QString cycle_time;//加工时间
    QString sample_cnt;//抽检件数单位
    QString disp_element_cnt;//屏幕展示个数
    QString  trend_warn_win;//趋势预警
    QString lock_time;//锁定时间
};
typedef struct {
    int flag;//该列状态：初始值为0,1代表工人赋值,2代表审核员赋值
    int worker_row_flag;//操作员列标识
    int checker_row_flag;//审核员列标识
    int flash_flag;//是否被刷新过
    int recover_flag;//是否被恢复为当前工作时间
    QColor temp_worker_color;//操作员颜色暂存（用于操作员和核验员点击同一单元格）
    int t_time;//修改锁定时间
}tflag;
struct tabinfo{
    friend QDataStream& operator<<(QDataStream &os,tabinfo&a);
    QString gauge;
    QString featureid;//零件特性号
    QString char_desc;//特征描述(长宽，内径...)
    double normvalue;//规格值
    double zgc;//正公差
    double fgc;//负公差
    double jddw;//精度单位
    double ejjddw;//二级精度单位
    //int chk_warn_thr;//二级预警值
    //int warn_thr;//一级预警值
};
class my_tablewidget:public QTableWidget {
public:
    int gap;//工作时间间隔
    int trend_val = 0;//增长方向趋势值（超出配置预警）
    int temp_trend_val = 0;//暂存，用于修改。下个时间段初始赋值给上面的值
    int trend_plus_minus = 0;//该趋势是正/负趋势
    int temp_trend_plus_minus = 0;//暂存正负标识
    double val = -1;//上次次操作值.
    double temp_val = -1;//暂存本次操作值
    //int
    QVector<tflag>flag;//标记该列是否被赋值过
//    ~my_tablewidget() override{//无指针可以不用虚析构

//    }
    my_tablewidget(){
//        this->setStyleSheet("QTableView QTableCornerButton::section{padding:12px 0 0 10px"
//                            "background-position:center;");
         QAbstractButton *btn = this->findChild<QAbstractButton *>();
        if (btn) {
            btn->setText(QStringLiteral("范围/时间"));
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
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
    explicit my_tablewidget(const int& row,const int& column) {
       this->setColumnCount(column);
        this->setRowCount(row);
        this->horizontalHeader()->setHidden(true);
        this->verticalHeader()->setHidden(true);
        this->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        for (int i = 0;i < 4;i++) {
            for (int j = 0;j < 4;j++) {
                if (!(this->item(i,j))) {
                    this->setItem(i,j,new QTableWidgetItem());
                    this->item(i,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                }
            }
        }
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
};
typedef struct {
    QVector<QVector<double> >x;
    QVector<QVector<double> >y;
    volatile int tabnum;
} communication;
typedef struct {
    int hour;
    int minute;
    int second;
}create_time;
#pragma pack()
class mytab:public QTabWidget
{
    Q_OBJECT
public:
    //QVector<serialport_info>Serial_port;
    mytab();
    ~mytab();
    //QTabWidget *tabWidget;
    void tabadd(tabinfo& createinfo,infomation& info);
    int readxml(const work_info &work_info,int flag = 0);
    int read_local_authuser(const work_info &work_info);
    int read_local_env(const work_info &work_info,int flag);
    void flash_table(int current_time);
    int nekwork_or_local();
    QVector<my_tablewidget*> table;//所有表格对象的地址
    QVector<tabinfo> createinfo;//所有表格的基本信息
    //QVector<QVector<tflag>>flag;//标记表格
    communication my;
    infomation info;
    QVector<float>table_gap;
    QVector<QColor> color_scheme;//配色方案
    message_worker_evn messageWorkerEvn;
    QString  auto_zero(double from,double to);//自动补全'0'
    int start_time;//当前tab工作开始时间
    int work_start_time;//当天工作开始时间
    void read_gauge(work_info &workInfo);
    void modify_gauge(work_info &workInfo,int index);
private:
    bool eventFilter(QObject *watched, QEvent *event);
    void trend_warn();//趋势预警处理函数
    void showEvent(QShowEvent *);

private slots:

};

#endif // TAB_H
