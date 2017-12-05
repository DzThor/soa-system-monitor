#include "sensoresthread.h"

SensoresThread::SensoresThread(QVector<QString>& vector_, QMutex& mutex_) :
    vector(&vector_),
    mutex(&mutex_){

}

void SensoresThread::run()
{
    while(1){
    QDir* dir = new QDir("/sys/class/hwmon/");
    dir->setFilter(QDir::Dirs);
    dir->setSorting(QDir::Size | QDir::Reversed);

    if(!dir->isReadable()){
        return;
    }else{
        QFileInfoList list = dir->entryInfoList();
        for (int i=0; i<list.size();i++){

            QDir tmp_dir(list[i].absoluteFilePath());
            tmp_dir.setFilter(QDir::Files);

            QStringList filters;
            filters << "temp*" << "fan*";
            tmp_dir.setNameFilters(filters);

            QFile tmp_name(list[i].absoluteFilePath().append("/name"));
            QString st_name;
            if(tmp_name.open(QIODevice::ReadOnly)){
                st_name=tmp_name.readLine();
                st_name.chop(1);
                st_name.append(":");
            }
                QFileInfoList tmp_list = tmp_dir.entryInfoList();
            foreach (QFileInfo file_info, tmp_list){

                QString fileName = file_info.absoluteFilePath();
                QFile file(fileName);
                QString tmp;
                tmp.append(st_name);
                tmp.append(file_info.baseName());
                tmp.append("\t");
                    if (file.open(QIODevice::ReadOnly)) {

                        mutex->lock();
                        tmp.append(file.readLine());
                        tmp.append("\n");
                        //st_name.append(tmp);
                        vector->push_back(tmp/*st_name*/);
                        mutex->unlock();
                        //ui->tabWidget->setTabText(3, in.readAll()); Enviar al hilo principal?
                        file.close();
                    }
            }
        }
    }
    emit Empty();
    this->sleep(1);}
}
