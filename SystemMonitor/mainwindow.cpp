#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    tabla = new QTreeWidget();
//    tabla->setParent(ui->tab_procesos);
//    tabla->setColumnCount(4);
//    QStringList Header;
//    Header<<"PID"<<"Cmdline"<<"Name"<<"Threads";
//    tabla->setHeaderLabels(Header);
//    tabla->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(&temporizador, &QTimer::timeout, this, &MainWindow::procThread);
    temporizador.setInterval(5000);
    temporizador.start();



    /*QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 10; ++i)
        items.append(new QTreeWidgetItem(tabla));

    for(int i = 0; i<tabla->columnCount(); i++){
            items[i]->setText(0,"Hola");
            items[i]->setText(1,"Que");
            items[i]->setText(2,"Tal");
            items[i]->setText(3,"Pene");
    }*/
    QObject::connect(this,&MainWindow::starthwd,&hardware,&hwdcheck::check_hwd);
    QObject::connect(&hardware, &hwdcheck::ready2Read, this, &MainWindow::Sethwd);
    hardware.moveToThread(&hwdThread);
    hwdThread.start();
    emit starthwd();

    QObject::connect(this,&MainWindow::startuser,&user,&usercheck::check_user);
    QObject::connect(&user, &usercheck::ready2Read, this, &MainWindow::Setuser);
    user.moveToThread(&userThread);
    userThread.start();
    emit startuser();

    QObject::connect(this,&MainWindow::startnet,&net,&netcheck::check_net);
    QObject::connect(&net, &netcheck::ready2Read, this, &MainWindow::Setnet);
    net.moveToThread(&userThread);
    netThread.start();
    emit startnet();

    er_thread = new SensoresThread(er_vector,er_mutex);
    QObject::connect(er_thread,&SensoresThread::Empty,this,&MainWindow::Mostrar);
    er_thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Mostrar()
{
    QString datos_sensores;
    er_mutex.lock();
    for(int i=0; i<er_vector.size();i++){
        datos_sensores.append(er_vector[i]);
    }
    er_mutex.unlock();
    ui->label_sensores->setText(datos_sensores);
    er_vector.clear();
}

//void MainWindow::RecorreProcesos()
//{
//    //QList<QTreeWidgetItem*> contenidos;

//       //contenidos.append(new QTreeWidgetItem(tabla));
//}

QVector<QString> MainWindow::Proceso(QFileInfo proceso){
    QVector<QString> vector;
    QString tmpPid = /*list[i]*/proceso.fileName();//PID
    //contenidos[i]->setText(0,tmpPid);
    //objeto->setText(0,tmpPid);
    vector.push_back(tmpPid);
    //QDir tmp_dir(list[i].absoluteFilePath());
    QDir tmp_dir(proceso.absoluteFilePath());
    tmp_dir.setFilter(QDir::Files);
    QStringList filters;
    filters << "cmdline" << "status";
    tmp_dir.setNameFilters(filters);
    tmp_dir.setSorting(QDir::Name);

    QFileInfoList tmp_list = tmp_dir.entryInfoList();

    foreach (QFileInfo file_info, tmp_list){ //Dos ficheros, status y cmdline

    if(file_info.baseName()=="cmdline"){

        QString fileName = file_info.absoluteFilePath();
        QFile file(fileName);
        QString tmpCmdLine;
            if (file.open(QIODevice::ReadOnly)) {
                tmpCmdLine.append(file.readLine()); //cmdline
                vector.push_back(tmpCmdLine);
                //contenidos[i]->setText(1,tmpCmdLine);
                //objeto->setText(1,tmpCmdLine);
                tmpCmdLine.chop(1);
                file.close();
            }
     }else {

        QString fileName = file_info.absoluteFilePath();
        QFile file(fileName);
        QString tmpThreads;
        QString tmpName;

            if (file.open(QIODevice::ReadOnly)) {
                bool salir = false;

                tmpName.append(file.readLine()); //name
                tmpName.remove(0, tmpName.indexOf("\t"));
                tmpName.remove(QRegExp("[\\n\\t\\r]"));
                vector.push_back(tmpName);
                tmpName.chop(1);

                while(!salir){
                    tmpThreads=file.readLine();
                    if(tmpThreads.startsWith("Threads:")){ //threads
                        salir=true;
                        tmpThreads.chop(1);
                        tmpThreads.remove(0, tmpThreads.indexOf("\t"));
                        tmpThreads.remove(QRegExp("[\\n\\t\\r]"));

                        vector.push_back(tmpThreads);
                    }

            }
                file.close();
     }
    }
    }
    return(vector);
}

void MainWindow::procThread()
{
    ui->treeWidget->clear();
    QDir* dir = new QDir("/proc/");
    dir->setFilter(QDir::Dirs);
    QStringList filtro;
    filtro << "[1-9]*";
    dir->setNameFilters(filtro);
    dir->setSorting(QDir::Size | QDir::Reversed);
    QList<QTreeWidgetItem *> items;


    if(dir->isReadable()){
        QFileInfoList list = dir->entryInfoList();

       for (int i=0; i<list.size();i++){
            QFuture<QVector<QString>> futuro = QtConcurrent::run(this, &MainWindow::Proceso, list[i]);
            QFutureWatcher<QVector<QString>> *w = new QFutureWatcher<QVector<QString>>();
            QObject::connect(w,&QFutureWatcher<QVector<QString>>::finished,this, [=]{
                QTreeWidgetItem* ejemplo =new QTreeWidgetItem(ui->treeWidget);

                QVector<QString> tmpVector = futuro.result();
                ejemplo->setText(0,tmpVector[0]);
                ejemplo->setText(1,tmpVector[1]);
                ejemplo->setText(2,tmpVector[2]);
                ejemplo->setText(3,tmpVector[3]);

                ui->treeWidget->sortItems(0,Qt::AscendingOrder);
       });
            w->setFuture(futuro);
    }
    }
}

void MainWindow::Sethwd(QString output){
    ui->label_hwd->setText(output);
}

void MainWindow::Setuser(QString output){
    ui->label_user->setText(output);
}

void MainWindow::Setnet(QString output){
    ui->label_net->setText(output);
}
