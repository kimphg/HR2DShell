#include "mainwindow.h"
#include "ui_mainwindow.h"
QTimer *watchdogTimer = new QTimer();
QUdpSocket udpSocket;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRect rec = QApplication::desktop()->screenGeometry(0);
    setFixedSize(rec.width(),rec.height());
    this->showFullScreen();
    udpSocket.bind(8089);
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processUdp()));
    jupiter = new QProcess;
    StartJupiter();
    connect(watchdogTimer, SIGNAL(timeout()), this, SLOT(watchDogTimerTick()));
    watchdogTimer->start(5000);
}
bool running = false;
void MainWindow::StartJupiter()
{
    jupiter->start("\"H:\\release version\\RadarSimulator.exe\"");
    running = true;
}
void MainWindow::StopJupiter()
{
    jupiter->kill();
    running = false;
}
char buff[100];

void MainWindow::watchDogTimerTick()
{
    if(running)
    {
        StopJupiter();
        watchdogTimer->start(100);
    }
    else
    {
        StartJupiter();
        watchdogTimer->start(5000);
    }

}
void MainWindow::processUdp()
{
    while (udpSocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
        watchdogTimer->start(5000);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
