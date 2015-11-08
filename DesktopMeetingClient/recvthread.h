#ifndef RECVTHREAD_H
#define RECVTHREAD_H

#include <QThread>
class MainWindow;
class RecvThread : public QThread
{
public:
    RecvThread(QWidget* pWnd);
protected:
    void run();
private:
    MainWindow* pMain;
    QByteArray array;
};

#endif // RECVTHREAD_H
