#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "common.h"
#include <unistd.h>
#include <QTimer>
#include <QDesktopWidget>
#include <QBuffer>
#include <QPainter>

#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xfixes.h>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(sendDesktop()));
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::on_btnStart_clicked()
{
    interval = ui->txtFrequency->text().toInt();
    imageQuality = (ui->cmbQuality->currentIndex())*25;
    meetingID = ui->cmbGroup->currentIndex();
    port = ui->txtPort->text().toShort();

    this->initNetwork();
    timer->setInterval(interval);
    timer->start();

    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
}

void MainWindow::on_btnStop_clicked()
{
    timer->stop();
    this->uninitNetwork();

    ui->btnStop->setEnabled(false);
    ui->btnStart->setEnabled(true);
}

void MainWindow::sendDesktop()
{
    QDesktopWidget* pDesktop = QApplication::desktop();
    QPixmap pixmap = QPixmap::grabWindow(pDesktop->winId(),
        0, 0, pDesktop->width(), pDesktop->height());

    // 捕捉鼠标
    QPoint mousePos = QCursor::pos();
    XFixesCursorImage *xfcursorImage = XFixesGetCursorImage(QX11Info::display());
    QImage mouseCursor((uchar*)xfcursorImage->pixels,
                       xfcursorImage->width, xfcursorImage->height,
                       QImage::Format_ARGB32_Premultiplied);
    mousePos -= QPoint(xfcursorImage->xhot, xfcursorImage->yhot);

    QImage screenshot = pixmap.toImage();
    QPainter p;
    p.begin(&screenshot);
    p.drawImage(mousePos, mouseCursor);
    p.end();

    QBuffer buf;
    screenshot.save(&buf, "JPG", imageQuality);
    buf.open(QIODevice::ReadOnly);
    uchar* pData = (uchar*)buf.buffer().data();
    int len = buf.bytesAvailable();

    int times = len / MAX_SEND_SIZE;
    int nSend = 0;
    nSend = sendto(sendSocket, START_CODE, START_CODE_LENGTH,
                    0, (sockaddr*)&addr, sizeof(addr));

    uchar* t = pData;
    for(int i=0;i<times;i++)
    {
        nSend = sendto(sendSocket, t, MAX_SEND_SIZE,
                       0, (sockaddr*)&addr, sizeof(addr));
        t += nSend;
    }
    int remains = len % MAX_SEND_SIZE;
    if (remains != 0)
    {
        nSend = sendto(sendSocket, t, remains,
                       0, (sockaddr*)&addr, sizeof(addr));
    }
    buf.close();
    nSend = sendto(sendSocket, END_CODE, END_CODE_LENGTH,
                   0, (sockaddr*)&addr, sizeof(addr));
}

void MainWindow::initNetwork()
{
    sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // 设置组播地址
    ip_mreq mcast;
    mcast.imr_interface.s_addr = INADDR_ANY;
    mcast.imr_multiaddr.s_addr = inet_addr(MULTICASTADDRESS[meetingID]);
    int n = setsockopt(sendSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                       (char*)&mcast, sizeof(mcast));
    // 设置组播TTL
    int optval = 8;
    n = setsockopt(sendSocket, IPPROTO_IP, IP_MULTICAST_TTL,
                   (char*)&optval, sizeof(int));
    // 设置是否发送给自己
    int loop = 1;
    n = setsockopt(sendSocket, IPPROTO_IP, IP_MULTICAST_LOOP,
                   (char*)&loop, sizeof(int));
    // 设置组播信息发送的目的地
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(MULTICASTADDRESS[meetingID]);
    addr.sin_port = htons(port);
}

void MainWindow::uninitNetwork()
{
    ::close(sendSocket);
}
