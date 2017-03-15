#include "savethread.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QFile>
#include <QTextStream>
SaveThread::SaveThread(QObject *parent):QThread(parent)
{

}
bool SaveThread::SaveData(QString string)
{
    QMutex mutex;
    mutex.lock();
    QFile file("saving.log");
    if(file.open(QIODevice::Append| QIODevice::Text))
    {
        QTextStream out(&file);
        out<<string<<"\n";
        file.flush();
        file.close();
        mutex.unlock();
        return true;
    }
    mutex.unlock();
    return false;
}
