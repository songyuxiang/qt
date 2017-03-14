#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QDebug>
#include <QSettings>
SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    connect(this,SIGNAL(accepted()),this,SLOT(updateSettings()));
}

void SettingDialog::updatePortName(QVector<QString> portnameList)
{
    foreach (QString name, portnameList) {
        ui->comboBox_portname_3->addItem(name);
    }
}

void SettingDialog::initSettings()
{
    QSettings serialPortSettings("GEOSAT","BATHYSAT");
    if (serialPortSettings.value("name").toString()!="")
    {
        serialInfo.baudrate=static_cast<QSerialPort::BaudRate>(serialPortSettings.value("baudrate").toInt());
        ui->comboBox_bautrate_3->setCurrentText(serialPortSettings.value("baudrate").toString());
        serialInfo.name=serialPortSettings.value("name").toString();
        ui->comboBox_portname_3->setCurrentText(serialPortSettings.value("name").toString());
        serialInfo.databits=static_cast<QSerialPort::DataBits>(serialPortSettings.value("databits").toInt());
        ui->comboBox_databits_3->setCurrentText(serialPortSettings.value("databits").toString());
        if(serialPortSettings.value("flowcontrol").toInt()==0)
            serialInfo.flowcontrol=QSerialPort::NoFlowControl;
        else if(serialPortSettings.value("flowcontrol").toInt()==1)
            serialInfo.flowcontrol=QSerialPort::HardwareControl;
        else if (serialPortSettings.value("flowcontrol").toInt()==2)
            serialInfo.flowcontrol=QSerialPort::SoftwareControl;

        ui->comboBox_flowcontrol_3->setCurrentIndex(serialPortSettings.value("flowcontrol").toInt());

        int parityIndex=serialPortSettings.value("parity").toInt();
        if(parityIndex>0)
        {
            parityIndex=parityIndex+1;
        }
        ui->comboBox_parity_3->setCurrentIndex(serialPortSettings.value("parity").toInt());
        serialInfo.parity=static_cast<QSerialPort::Parity>(parityIndex);

        int stopBitsIndex=serialPortSettings.value("stopbits").toInt();
        if(stopBitsIndex==0)
            stopBitsIndex=1;
        else if (stopBitsIndex==1)
            stopBitsIndex=3;
        ui->comboBox_stopbits_3->setCurrentIndex(serialPortSettings.value("stopbits").toInt());
        serialInfo.stopbits=static_cast<QSerialPort::StopBits>(stopBitsIndex);
        emit sendSettings(serialInfo);
    }
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::updateSettings()
{
    serialInfo.baudrate=static_cast<QSerialPort::BaudRate>(ui->comboBox_bautrate_3->currentText().toInt());
    serialInfo.name=ui->comboBox_portname_3->currentText();
    serialInfo.databits=static_cast<QSerialPort::DataBits>(ui->comboBox_databits_3->currentText().toInt());

    if(ui->comboBox_flowcontrol_3->currentIndex()==0)
        serialInfo.flowcontrol=QSerialPort::NoFlowControl;
    else if(ui->comboBox_flowcontrol_3->currentIndex()==1)
        serialInfo.flowcontrol=QSerialPort::HardwareControl;
    else if (ui->comboBox_flowcontrol_3->currentIndex()==2)
        serialInfo.flowcontrol=QSerialPort::SoftwareControl;
    int parityIndex=ui->comboBox_parity_3->currentIndex();
    if(parityIndex>0)
    {
        parityIndex=parityIndex+1;
    }
    serialInfo.parity=static_cast<QSerialPort::Parity>(parityIndex);

    int stopBitsIndex=ui->comboBox_stopbits_3->currentIndex();
    if(stopBitsIndex==0)
        stopBitsIndex=1;
    else if (stopBitsIndex==1)
        stopBitsIndex=3;

    serialInfo.stopbits=static_cast<QSerialPort::StopBits>(stopBitsIndex);
    emit sendSettings(serialInfo);

    QSettings serialPortSettings("GEOSAT","BATHYSAT");
    serialPortSettings.setValue("baudrate",ui->comboBox_bautrate_3->currentText().toInt());
    serialPortSettings.setValue("name",ui->comboBox_portname_3->currentText());
    serialPortSettings.setValue("databits",ui->comboBox_databits_3->currentText().toInt());
    serialPortSettings.setValue("flowcontrol",ui->comboBox_flowcontrol_3->currentIndex());
    serialPortSettings.setValue("parity",ui->comboBox_parity_3->currentIndex());
    serialPortSettings.setValue("stopbits",ui->comboBox_stopbits_3->currentIndex());
}
