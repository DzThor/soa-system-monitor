#ifndef USERCHECK_H
#define USERCHECK_H


#include <QProcess>

class usercheck : public QObject
{
    Q_OBJECT
public:
    explicit usercheck(QObject *parent = 0);

signals:

    void ready2Read(QString output);
public slots:
    void check_user(void);
};

#endif // USERCHECK_H
