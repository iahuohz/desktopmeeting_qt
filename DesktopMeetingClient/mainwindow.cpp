#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recvthread.h"
#include "common.h"
#include <unistd.h>
#include <QThread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <QPaintEvent>
#include <QPainter>

MainWindow::MainWindow(int meetingID, short port, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->lblPic);

    this->meetingID = meetingID;
    this->port = port;
    initNetwork();

    pic = NULL;

    recvThread = new RecvThread(this);
    recvThread->start();
}

MainWindow::~MainWindow()
{
    delete recvThread;
    delete ui;
}

void MainWindow::initNetwork()
{
    recvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    bind(recvSocket, (sockaddr*)&addr, sizeof(addr));

    // 设置组播地址
    ip_mreq mcast;
    mcast.imr_interface.s_addr = INADDR_ANY;
    mcast.imr_multiaddr.s_addr = inet_addr(MULTICASTADDRESS[meetingID]);
    int n = setsockopt(recvSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                       (char*)&mcast, sizeof(mcast));
    // 设置组播TTL
    int optval = 8;
    n = setsockopt(recvSocket, IPPROTO_IP, IP_MULTICAST_TTL,
                   (char*)&optval, sizeof(int));
    // 设置是否发送给自己
    int loop = 1;
    n = setsockopt(recvSocket, IPPROTO_IP, IP_MULTICAST_LOOP,
                   (char*)&loop, sizeof(int));
}

void MainWindow::deinitNetwork()
{
    ::close(recvSocket);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    deinitNetwork();
    recvThread->quit();
}

void MainWindow::paintEvent(QPaintEvent *pe)
{
    //ui->lblPic->setPixmap(*pic);
    if (pic != NULL)
    {
        QPainter paint(this);
        QImage p = pic->scaled(ui->lblPic->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        paint.drawImage(0, 0, p);
        delete pic;
        pic = NULL;
    }
}

void MainWindow::updateView(const QByteArray& array)
{
    pic = new QImage();
    bool ret = pic->loadFromData(array, "JPG");
    this->update();
}
