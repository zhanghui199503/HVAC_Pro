#include "blower_dataset.h"
#include "ui_blower_dataset.h"
Blower_DataSet *Blower_Set;
Blower_DataSet::Blower_DataSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Blower_DataSet)
{
    ui->setupUi(this);
}

Blower_DataSet::~Blower_DataSet()
{
    delete ui;
}
