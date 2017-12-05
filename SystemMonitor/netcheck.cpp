#include "netcheck.h"

netcheck::netcheck(QObject *parent) : QObject(parent)
{

}

void netcheck::check_net(){

    QProcess *myProcess = new QProcess(this);

    myProcess->start("/bin/netstat -s");

    QString output;

    while(myProcess->waitForReadyRead()){
        output.append(myProcess->readAll());
    }

    QRegExp rx("(IpExt:\n(\s*([A-Z]|[a-z]|[0-9])*:\s[0-9]+\n)*)|(UdpLite:\n)|"
               "(IcmpMsg:\n(\s*([A-Z]|[a-z]|[0-9])*:\s[0-9]+\n)*)|(TcpExt:\n(\s*.*)*)");

    output.remove(rx);

    emit ready2Read(output);
}


