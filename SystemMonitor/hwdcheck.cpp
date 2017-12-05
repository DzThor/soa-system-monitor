#include "hwdcheck.h"

hwdcheck::hwdcheck(QObject *parent) : QObject(parent)
{

}

void hwdcheck::check_hwd(){

    QProcess *myProcess = new QProcess(this);

    myProcess->start("/usr/bin/lshw");
    QString output;

    while(myProcess->waitForReadyRead()){
        output.append(myProcess->readAll());
    }

    emit ready2Read(output);
}

