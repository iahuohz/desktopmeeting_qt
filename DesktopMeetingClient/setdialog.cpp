#include "setdialog.h"
#include "ui_setdialog.h"

SetDialog::SetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDialog)
{
    ui->setupUi(this);
}

SetDialog::~SetDialog()
{
    delete ui;
}

int SetDialog::GetMeetingID()
{
    return meetingID;
}

short SetDialog::GetPort()
{
    return port;
}

void SetDialog::on_btnStart_clicked()
{
    meetingID = ui->cmbGroup->currentIndex();
    port = ui->txtPort->text().toShort();
    this->setResult(1);
    this->close();
}
