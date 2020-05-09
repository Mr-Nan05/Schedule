#include "remind_time_set.h"
#include "ui_remind_time_set.h"
//#include "ui_remind.h"

Remind::Remind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Remind)
{
    ui->setupUi(this);
}

Remind::~Remind()
{
    delete ui;
}

void Remind::on_buttonBox_accepted()
{
    aRemindTime = ui->timeEdit->time();
    //aReminder = ui->timeEdit->text();
}
