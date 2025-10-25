#include "pop_ups_ok.h"
#include "ui_pop_ups_ok.h"

Pop_ups_OK *Pop_OK;

Pop_ups_OK::Pop_ups_OK(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pop_ups_OK)
{
    ui->setupUi(this);
}

Pop_ups_OK::~Pop_ups_OK()
{
    delete ui;
}

void Pop_ups_OK::on_Confirm_OK_clicked()
{
    emit Sign_Set_OK("M",1025,1);
    emit Sign_Set_OK("M",1025,0);
    qDebug()<<"点击检测OK完成按钮";
    this->hide();
}

