#include "pop_ups_alarm.h"
#include "ui_pop_ups_alarm.h"

Pop_ups_Alarm *Pop_Alarm;

Pop_ups_Alarm::Pop_ups_Alarm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pop_ups_Alarm)
{
    ui->setupUi(this);
}

Pop_ups_Alarm::~Pop_ups_Alarm()
{
    delete ui;
}
