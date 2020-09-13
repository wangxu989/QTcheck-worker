#include<base_program.h>
xml* xml::x = nullptr;
int xml::readxml(const work_info &workInfo,int flag) {
    QTime currenttime = QTime::currentTime();//获取当前时间
    int hour = 8;
    int minute = 30;
    int second = 0;
    //    int hour = currenttime.hour();
    //    int minute = currenttime.minute();
    //    int second = currenttime.second();
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
                QString product_no = e.attribute("product_no");
                if (product_no == workInfo.instruction_id.split(",")[1].mid(0,6)){
                    return 0;
                }
            }
        }
        n = n.nextSibling();
    }
    return -1;
}

int xml::read_local_authuser(const work_info &workInfo) {
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
int xml::read_local_env(const work_info &workInfo,int flag) {
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
int xml::read_start_finish_config() {
    QFile file("./data/StartFinishConfig.xml");
    file.open(QIODevice::ReadOnly);
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
            if (e.tagName() == "Start") {
                return e.attribute("scope").toInt();
            }
        }
    }
    return 1;
}
