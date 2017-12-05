
#ifndef HWDCHECK_H
#define HWDCHECK_H
#include <QProcess>


class hwdcheck : public QObject
{
    Q_OBJECT
public:
    explicit hwdcheck(QObject *parent = 0);

signals:

    void ready2Read(QString output);
public slots:
    void check_hwd(void);
};

#endif // HWDCHECK_H
