#ifndef NETCHECK_H
#define NETCHECK_H

#include <QProcess>

class netcheck : public QObject
{
    Q_OBJECT
public:
    explicit netcheck(QObject *parent = 0);

signals:

    void ready2Read(QString output);
public slots:
    void check_net(void);
};

#endif // NETCHECK_H
