#include <QtGui/QApplication>
#include "mainwindow.h"
#include "setdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetDialog dlg;
    dlg.setModal(true);
    dlg.exec();

    MainWindow w(dlg.GetMeetingID(), dlg.GetPort());
    w.show();
    
    return a.exec();
}
