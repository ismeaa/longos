#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //先定义一个QStringList

    QStringList serialNamePort;
    serialPort = new QSerialPort();
    tcpServer = new QTcpServer(this);
    tcpSocket = new QTcpSocket(this);




    connect(serialPort,SIGNAL(readyRead()),this,SLOT(serialportReadyRead_slot()));//链接发送和接受

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        serialNamePort << info.portName();
        //QSerialPortInfo是串口的信息类，是存放串口信息的。
        //QSerialPortInfo::availablePorts是自动搜索当前的可用串口，其返回值是一个数组，数组的元素是QSerialPortInfo类型的
        //然后将返回值加到了QStringList这个二维数组里面。
    }
    ui->chuan_kou_hao->addItems(serialNamePort);
    //将代码实现的功能显示在ui界面里面，这就是为啥刚才改名字。

}
//通过这段代码就可以把当前搜索的可用的串口在ui界面显示出来

Widget::~Widget()
{
    delete ui;
}

void Widget::serialportReadyRead_slot(){

    QString buf;
    buf = QString(serialPort->readAll());
    ui->recv->appendPlainText(buf);

}

void Widget::readyread_Slot(){
    QString buf;
    buf = tcpSocket->readAll();
    ui->recv->appendPlainText(buf);

}


void Widget::on_open_clicked()
{
    //先来定义一些变量：波特率、数据位、停止位、校验位
    QSerialPort::BaudRate bauRate; //波特率
    QSerialPort::DataBits dataBits; //数据位
    QSerialPort::StopBits stopBits; //停止位


    //定义完变量之后，要给变量进行赋值
    //对波特率进行判断（对变量逐一进行判断）
    if(ui->bo_te_lv->currentText()== "4800"){
        bauRate = QSerialPort::Baud4800;
        //如果ui界面的波特率控件参数选择的是4800，那么对应在QSerialPort里面的波特率就是4800
    }
    else if(ui->bo_te_lv->currentText()== "9600"){
        bauRate = QSerialPort::Baud9600;
    }
    else if(ui->bo_te_lv->currentText()== "115200"){
        bauRate = QSerialPort::Baud115200;
    }

    //对数据位进行判断
    if (ui->shu_ju_wei->currentText() == "5") {
        dataBits = QSerialPort::Data5;
    }else if(ui->shu_ju_wei->currentText() == "6") {
        dataBits = QSerialPort::Data6;
    }else if(ui->shu_ju_wei->currentText() == "7") {
        dataBits = QSerialPort::Data7;
    }else if(ui->shu_ju_wei->currentText() == "8") {
        dataBits = QSerialPort::Data8;
    }

    //设置停止位
    if (ui->ting_zhi_wei->currentText() == "1" ) {
        stopBits = QSerialPort::OneStop;
    }  else if(ui->ting_zhi_wei->currentText() == "2" ) {
        stopBits = QSerialPort::TwoStop;
    }else if(ui->ting_zhi_wei->currentText() == "1.5"){
        stopBits = QSerialPort::OneAndHalfStop;
    }

    //设置校验位



    //填充串口对象的属性值
    //要先选中串口，对应的端口是ui界面里面的serialCb
    serialPort->setPortName(ui->chuan_kou_hao->currentText());

    //设置波特率、数据位等
    serialPort->setBaudRate(bauRate);
    serialPort->setDataBits(dataBits);
    serialPort->setStopBits(stopBits);


    //设置好属性后打开串口，打开串口之前要先判断一下串口有没有打开成功
    if(serialPort->open(QIODevice::ReadWrite) == true){
        //ReadWrite设置的是可读可写的属性
        QMessageBox::information(this,"提示","成功");
    }else{QMessageBox::critical(this,"提示","失败");
    }
}



void Widget::on_clear_clicked()
{
    ui->recv->clear();
}


void Widget::on_send_clicked()
{
    tcpSocket->write(ui->send->text().toLocal8Bit().data());
}

