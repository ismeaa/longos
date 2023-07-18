#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QSerialPort>
#include<Qstring.h>
#include<QTcpServer>
#include<QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
        QSerialPort *serialPort;
    QTcpServer *tcpServer;
        QTcpSocket *tcpSocket;



private slots:
     void on_open_clicked();


     void on_clear_clicked();

     void serialportReadyRead_slot();



     void on_send_clicked();

     void readyread_Slot();

 private:
    Ui::Widget *ui;


};
#endif // WIDGET_H
