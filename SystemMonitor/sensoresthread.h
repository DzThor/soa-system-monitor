#ifndef SENSORESTHREAD_H
#define SENSORESTHREAD_H

#include <QThread>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QVector>
#include <QMutex>


class SensoresThread : public QThread
{
    Q_OBJECT

    protected:
        void run();

    private:
        QVector<QString>* vector;
        QMutex* mutex;
    public:
        SensoresThread(QVector<QString>& vector_, QMutex& mutex_);

    signals:
        bool Empty(void);
};

#endif // SENSORESTHREAD_H
