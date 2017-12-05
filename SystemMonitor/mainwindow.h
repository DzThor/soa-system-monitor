#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sensoresthread.h"
#include "hwdcheck.h"
#include "usercheck.h"
#include "netcheck.h"
#include <QVector>
#include <QMutex>
#include <QString>
#include <QRunnable>
#include <QThreadPool>
#include <QTreeWidget>
#include <QStringList>
#include <QTableWidgetItem>
#include <QDir>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Mostrar(void);
    QVector<QString> Proceso(QFileInfo proceso);
    void procThread();

private:
    Ui::MainWindow *ui;
    SensoresThread* er_thread;
    QMutex er_mutex;
    QVector<QString> er_vector;
    QTreeWidget* tabla;
    hwdcheck hardware;
    QThread hwdThread;
    QTimer temporizador;
    usercheck user;
    QThread userThread;
    netcheck net;
    QThread netThread;


signals:
    void starthwd();
    void startuser();
    void startnet();

public slots:
    void Sethwd(QString output);
    void Setuser(QString output);
    void Setnet(QString output);
};

#endif // MAINWINDOW_H
