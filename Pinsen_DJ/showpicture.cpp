#include "showpicture.h"
#include "ui_showpicture.h"
showpicture *showLogo;
showpicture::showpicture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showpicture)
{
    ui->setupUi(this);
    this->setWindowTitle("联系我们");
    ui->label_2->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_3->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_4->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_5->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_6->setAttribute(Qt::WA_TranslucentBackground);
}

showpicture::~showpicture()
{
    delete ui;
}
