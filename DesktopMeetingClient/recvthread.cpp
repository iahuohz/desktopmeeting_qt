#include "common.h"
#include "recvthread.h"
#include "mainwindow.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <QMessageBox>

RecvThread::RecvThread(QWidget* parent)
{
    pMain = (MainWindow*)parent;
}

void RecvThread::run()
{
    int nRecv = 0;
    char buf[MAX_SEND_SIZE];
    while(true)
    {
        nRecv = recvfrom(pMain->recvSocket,buf, MAX_SEND_SIZE, 0, NULL, NULL);
        if (nRecv <= 0)
        {
            break;
        }
        if(strncmp(buf, START_CODE, START_CODE_LENGTH) == 0) // 检查是否为帧头
        {
            array.clear();
            continue;
        }
        if(strncmp(buf, END_CODE, END_CODE_LENGTH) == 0)    // 检查是否为帧尾
        {
            pMain->updateView(array);
            continue;
        }
        array.append(buf, nRecv);                           // 如果是数据帧，直接写入内存
    }
}
