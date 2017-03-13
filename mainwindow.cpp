#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

yuxiang::SerialPortInfo MainWindow::testSerialPort(QString portname)
{
    QSerialPort serialport;
    yuxiang::SerialPortInfo serialInfo;
    serialport.setPortName(portname);
    serialport.setBaudRate(QSerialPort::Baud115200);
    serialport.setDataBits(QSerialPort::Data8);
    serialport.setParity(QSerialPort::NoParity);
    serialport.setStopBits(QSerialPort::TwoStop);
    serialport.setFlowControl(QSerialPort::NoFlowControl);
    if (serialport.open(QIODevice::ReadWrite))
    {
        const QByteArray data=serialport.readAll();
        if (QString(data)=="")
        {
            qDebug()<<portname<<"not available";
        }
        else
        {
            qDebug()<<portname<<"available";
        }
    }
    return serialInfo;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAutoConfigre_triggered()
{
    const auto infos = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo info, infos) {
        yuxiang::SerialPortInfo serialPortInfo;
        QString name=info.portName();
        serialPortInfo=testSerialPort(name);
    }

}
