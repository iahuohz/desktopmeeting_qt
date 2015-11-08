#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    friend class RecvThread;
public:
    explicit MainWindow(int meetingID, short port, QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    int meetingID;
    short port;
    QThread* recvThread;
    int recvSocket;
    QImage* pic;

private:
    void initNetwork();
    void deinitNetwork();
    void closeEvent(QCloseEvent *event);
    void paintEvent(QPaintEvent *pe);
    void updateView(const QByteArray& array);
};

#endif // MAINWINDOW_H
