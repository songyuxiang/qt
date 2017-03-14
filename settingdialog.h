#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "datastructure.h"
namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    void updatePortName(QVector<QString> portnameList);
    void initSettings();
    ~SettingDialog();
private slots:
    void updateSettings();
signals:
    void sendSettings(yuxiang::SerialPortInfo);
private:
    Ui::SettingDialog *ui;
    yuxiang::SerialPortInfo serialInfo;
};

#endif // SETTINGDIALOG_H
