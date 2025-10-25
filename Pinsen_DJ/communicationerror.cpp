#include "communicationerror.h"
#include "ui_communicationerror.h"


Communicationerror *Heart_error;

Communicationerror::Communicationerror(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Communicationerror)
{
    ui->setupUi(this);
}

Communicationerror::~Communicationerror()
{
    delete ui;
}
