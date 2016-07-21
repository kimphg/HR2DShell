#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdesktopwidget.h>
#include <QProcess>
#include <QTimer>
#include <QUdpSocket>
#include <QThread>

class Sleeper : public QThread
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QProcess *jupiter;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void StartJupiter();
    void StopJupiter();

private:
    Ui::MainWindow *ui;
private slots:
    void watchDogTimerTick();
    void processUdp();
};

#endif // MAINWINDOW_H
