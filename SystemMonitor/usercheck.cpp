#include "usercheck.h"

usercheck::usercheck(QObject *parent) : QObject(parent)
{

}

void usercheck::check_user(){

    QProcess *myProcess = new QProcess(this);

    myProcess->start("/usr/bin/w --short");
    QString output;

    while(myProcess->waitForReadyRead()){
        output.append(myProcess->readAll());
    }
    emit ready2Read(output);
}
