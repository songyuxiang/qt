#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QtSerialPort/QSerialPort>
#include "settingdialog.h"
#include <datastructure.h>
#include "savethread.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QVector<QString> getValidPortName();

    ~MainWindow();
private:
    void initSettings();
private slots:
    void on_actionSettings_triggered();
    void updateSerialportInfo(yuxiang::SerialPortInfo portInfo);
    void on_actionConnect_triggered();
    void readData();
    void on_actionDisconnect_triggered();

    void on_actionSave_triggered();

    void on_pushButton_depth_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_serialport=NULL;
    SettingDialog *m_settingDialog=NULL;
    yuxiang::SerialPortInfo m_serialportInfo;
    SaveThread *m_savingThread=NULL;
    QString m_currentTime="";
};

#endif // MAINWINDOW_H
