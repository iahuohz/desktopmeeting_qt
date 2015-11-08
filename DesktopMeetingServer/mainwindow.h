#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_btnStart_clicked();
    void on_btnStop_clicked();
    void sendDesktop();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    int sendSocket;
    sockaddr_in addr;
    int interval;           // 计时器时间间隔
    int imageQuality;       // 图像质量
    int meetingID;          // 会议组编号
    short port;             // 组播端口
private:
    void initNetwork();
    void uninitNetwork();
};

#endif // MAINWINDOW_H
