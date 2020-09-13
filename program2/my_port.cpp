#include "my_port.h"
#include<QTime>
#include<QThread>
#include<sys/stat.h>
my_port::my_port()
{
    lookup();
    start_port();
}
my_port::~my_port() {
    port1->close();
    delete port1;
}
void my_port::lookup() {
    //first readxml
    QFile file("./data/GeneralConfig.xml");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox box(QMessageBox::NoIcon,"config","open GeneralConfig.xml failed!",NULL,NULL);
        return;
    }
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        QMessageBox messageBox;
        messageBox.setText("read GeneralConfig.xml failed !");
        messageBox.exec();
        return ;
    }
    file.close();
    QDomElement domele = doc.documentElement();
    QDomNode n = domele.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement();
        QDomNodeList list = e.childNodes();
        if (e.tagName() == "SerialPorts") {
            for(int i = 0;i < list.size();i++){
                QDomNode node = list.at(i);
                QDomElement E_temp = node.toElement();
                if (E_temp.attribute("device") == "Printer") {
                    scanner.name = E_temp.attribute("portName");
                    scanner.baudRate = E_temp.attribute("baudRate");
                    scanner.dataBits = E_temp.attribute("dataBits");
                    scanner.stopBits = E_temp.attribute("stopBits");
                    scanner.parity = E_temp.attribute("parity");
                    scanner.writeBufferSize = E_temp.attribute("writeBufferSize");
                    scanner.readBufferSize = E_temp.attribute("readBufferSize");
                    qDebug()<<scanner.name;
                }

            }
        }
        n = n.nextSibling();

    }
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {

        if (info.portName() == scanner.name) {//info.serialNumber() == "A7434VMK"
            qDebug() << "Name : " << info.portName();
            qDebug() << "Description : " << info.description();
            qDebug() << "Manufacturer: " << info.manufacturer();
            qDebug() << "Serial Number: " << info.serialNumber();
            qDebug() << "System Location: " << info.systemLocation();
            my_info = info;
            name = info.portName();
        }
    }
}
void my_port::start_port(){
    port1 = new QSerialPort();
    if (port1->isOpen()) {
        port1->clear();
        port1->close();
    }
    port1->setPort(my_info);
    if (!port1->open(QIODevice::ReadWrite)) {
        qDebug()<<port1->errorString();
        qDebug()<<"open port failed";
        //exit(0);
    }
    //qDebug()<<name;
    port1->setBaudRate(QSerialPort::Baud9600);//设置波特率和读写方向
    port1->setDataBits(QSerialPort::Data8);		//数据位为8位
    port1->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    port1->setParity(QSerialPort::NoParity);	//无校验位
    port1->setStopBits(QSerialPort::OneStop); //一位停止位
    //port1->waitForReadyRead(true);
}
