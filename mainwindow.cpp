#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QtGui>
#include <QtCore>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_serialport=new QSerialPort(this);
    m_settingDialog=new SettingDialog(this);
    m_savingThread=new SaveThread(this);
    //update port name list
    getValidPortName();
    initSettings();
    connect(m_serialport,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(m_settingDialog,SIGNAL(sendSettings(yuxiang::SerialPortInfo)),this,SLOT(updateSerialportInfo(yuxiang::SerialPortInfo)));
}

QVector<QString> MainWindow::getValidPortName()
{
    QVector<QString> portNamesList;
    const auto infos = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo info, infos) {
        portNamesList.append(info.portName());
    }
    m_settingDialog->updatePortName(portNamesList);
    return portNamesList;
}

void MainWindow::updateSerialportInfo(yuxiang::SerialPortInfo portInfo)
{
    m_serialportInfo.baudrate=portInfo.baudrate;
    m_serialportInfo.name=portInfo.name;
    m_serialportInfo.databits=portInfo.databits;
    m_serialportInfo.flowcontrol=portInfo.flowcontrol;
    m_serialportInfo.parity=portInfo.parity;
    m_serialportInfo.stopbits=portInfo.stopbits;
}

void MainWindow::on_actionSettings_triggered()
{
    m_settingDialog->show();
    m_settingDialog->initSettings();
}

MainWindow::~MainWindow()
{
    delete m_serialport;
    delete m_settingDialog;
    delete m_savingThread;
}

void MainWindow::initSettings()
{
    QSettings serialPortSettings("GEOSAT","BATHYSAT");
    if (serialPortSettings.value("name")!="")
    {
        m_serialportInfo.baudrate=static_cast<QSerialPort::BaudRate>(serialPortSettings.value("baudrate").toInt());
        m_serialportInfo.name=serialPortSettings.value("name").toString();
        m_serialportInfo.databits=static_cast<QSerialPort::DataBits>(serialPortSettings.value("databits").toInt());

        if(serialPortSettings.value("flowcontrol").toInt()==0)
            m_serialportInfo.flowcontrol=QSerialPort::NoFlowControl;
        else if(serialPortSettings.value("flowcontrol").toInt()==1)
            m_serialportInfo.flowcontrol=QSerialPort::HardwareControl;
        else if (serialPortSettings.value("flowcontrol").toInt()==2)
            m_serialportInfo.flowcontrol=QSerialPort::SoftwareControl;
        int parityIndex=serialPortSettings.value("parity").toInt();
        if(parityIndex>0)
        {
            parityIndex=parityIndex+1;
        }
        m_serialportInfo.parity=static_cast<QSerialPort::Parity>(parityIndex);

        int stopBitsIndex=serialPortSettings.value("stopbits").toInt();
        if(stopBitsIndex==0)
            stopBitsIndex=1;
        else if (stopBitsIndex==1)
            stopBitsIndex=3;

        m_serialportInfo.stopbits=static_cast<QSerialPort::StopBits>(stopBitsIndex);
    }
}

void MainWindow::on_actionConnect_triggered()
{
    m_serialport->setPortName(m_serialportInfo.name);
    m_serialport->setBaudRate(m_serialportInfo.baudrate);
    m_serialport->setDataBits(m_serialportInfo.databits);
    m_serialport->setFlowControl(m_serialportInfo.flowcontrol);
    m_serialport->setParity(m_serialportInfo.parity);
    m_serialport->setStopBits(m_serialportInfo.stopbits);
    if(m_serialport->open(QIODevice::ReadWrite))
    {
        ui->actionDisconnect->setEnabled(true);
        ui->actionConnect->setEnabled(false);
        ui->actionSettings->setEnabled(false);
        ui->actionSave->setEnabled(false);
        ui->textEdit_new->setEnabled(false);
    }
    m_currentTime="";
}

void MainWindow::readData()
{
    QString currentTime=QDateTime::currentDateTime().toString("hh:mm:ss,yyyy-MM-dd");
    if (m_currentTime!=currentTime)
    {
        if(m_currentTime!="")
        {
            m_savingThread->SaveData("<DateTime/>");
            ui->textEdit->append("<DateTime/>\n");
        }
        m_currentTime=currentTime;
        m_savingThread->SaveData("<DateTime "+currentTime +">");
        ui->textEdit->append("<DateTime "+currentTime +">");
    }
    const QByteArray data=m_serialport->readAll();

    m_savingThread->SaveData(QString(data));

    ui->textEdit->append(QString(data));
}

void MainWindow::on_actionDisconnect_triggered()
{
    ui->actionConnect->setChecked(false);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionSettings->setEnabled(true);
    ui->textEdit_new->setEnabled(true);
    m_serialport->close();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName=QFileDialog::getSaveFileName(this,tr("Save the log file"),"","text file(*.txt);;All files(*.*)");
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream in(&file);
        in<<ui->textEdit_new->toPlainText();
    }
}

void MainWindow::on_pushButton_depth_clicked()
{
    QString text=ui->textEdit->toPlainText();
    QStringList stringList1=text.split("<DateTime/>");
    foreach (QString string, stringList1) {

        QStringList stringList2=string.split(",");
        if(stringList2.size()>0)
        {

            int index=stringList2.indexOf("M");
            if(index>1)
            {
                QString depth=(stringList2.at(index-1));
                QString result=string.mid(0,32)+"\n Depth:"+depth;
                ui->textEdit_new->append(result);
            }
        }


    }


}
