#include "aboutsoftware.h"
#include "ui_aboutsoftware.h"
AboutSoftware *Aboutware;
AboutSoftware::AboutSoftware(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutSoftware)
{
    ui->setupUi(this);
    ui->textEdit->setFrameShape(QFrame::NoFrame);
    this->setWindowTitle("关于软件");
}

AboutSoftware::~AboutSoftware()
{
    delete ui;
}
