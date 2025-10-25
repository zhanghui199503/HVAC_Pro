#include "pop_ups_ng.h"
#include "ui_pop_ups_ng.h"

Pop_ups_NG *Pop_NG;

Pop_ups_NG::Pop_ups_NG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pop_ups_NG)
{
    ui->setupUi(this);
}

Pop_ups_NG::~Pop_ups_NG()
{
    delete ui;
}

void Pop_ups_NG::on_NG_Continued_clicked()
{
    emit Sign_Set_NG("M",191,1);
    emit Sign_Set_NG("M",191,0);
    qDebug()<<"点击NG继续按钮";
    this->hide();
}


void Pop_ups_NG::on_NG_Stop_clicked()
{
    emit Sign_Set_NG("M",192,1);
//    emit Sign_Set_NG("M",192,0);
    qDebug()<<"点击NG暂停按钮";
    this->hide();
}

