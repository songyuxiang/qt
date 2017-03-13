#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QtSerialPort/QSerialPort>
namespace Ui {
class MainWindow;
}
namespace yuxiang {
struct SerialPortInfo
{
    QString name;
    QSerialPort::BaudRate baudrate;
    QSerialPort::DataBits databits=QSerialPort::Data8;
    QSerialPort::FlowControl flowcontrol=QSerialPort::NoFlowControl;
    QSerialPort::Parity parity=QSerialPort::NoParity;
    QSerialPort::StopBits stopbits;
};
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    yuxiang::SerialPortInfo testSerialPort(QString portname);
    ~MainWindow();

private slots:
    void on_actionAutoConfigre_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
