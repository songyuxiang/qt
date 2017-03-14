#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include <QSerialPort>

namespace yuxiang {
struct SerialPortInfo
{
    QString name;
    QSerialPort::BaudRate baudrate=QSerialPort::Baud115200;
    QSerialPort::DataBits databits=QSerialPort::Data8;
    QSerialPort::FlowControl flowcontrol=QSerialPort::NoFlowControl;
    QSerialPort::Parity parity=QSerialPort::NoParity;
    QSerialPort::StopBits stopbits=QSerialPort::TwoStop;
};
}

#endif // DATASTRUCTURE_H
