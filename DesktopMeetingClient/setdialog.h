#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>

namespace Ui {
class SetDialog;
}

class SetDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SetDialog(QWidget *parent = 0);
    ~SetDialog();
    
private:
    Ui::SetDialog *ui;
    int meetingID;
    short port;

public:
    int GetMeetingID();
    short GetPort();
private slots:
    void on_btnStart_clicked();
};

#endif // SETDIALOG_H
