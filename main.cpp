#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
bool checkLicense(QString companyName,QString version){
    QSettings settings(companyName,version);
//    QFile file("license.sat");
//    if (file.open(QIODevice::ReadWrite))
//    {
//        QTextStream out(&file);
//        QString data=out.readAll();
//        if (data=="30")
//        {
//            settings.setValue("00000000",10);
//        }
//        out<<"";
//        file.flush();
//        file.close();
//    }


    if (settings.value("00000000").toString()=="11111111")
    {
        return true;
    }

    else if(settings.value("00000000").toInt()>0)
    {
        int x=settings.value("00000000").toInt()-1;
        settings.setValue("00000000",x);
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"test";
    if (checkLicense("GEOSAT","BATHYSAT1.0"))
    {

        MainWindow w;
        w.show();
        return a.exec();
    }
    return 0;
}
