#ifndef SAVETHREAD_H
#define SAVETHREAD_H
#include <QThread>

class SaveThread:public QThread
{
    Q_OBJECT
public:
    explicit SaveThread(QObject *parent=0);
    bool SaveData(QString string);
};

#endif // SAVETHREAD_H
