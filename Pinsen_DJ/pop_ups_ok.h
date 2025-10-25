#ifndef POP_UPS_OK_H
#define POP_UPS_OK_H

#include <QWidget>
#include "Header_File.h"

namespace Ui {
class Pop_ups_OK;
}

class Pop_ups_OK : public QWidget
{
    Q_OBJECT

public:
    explicit Pop_ups_OK(QWidget *parent = nullptr);
    ~Pop_ups_OK();
    Ui::Pop_ups_OK *ui;
public slots:

private slots:
    void on_Confirm_OK_clicked();

private:


signals:
void Sign_Set_OK(QString unit, int address,int value);//发送OK
};

extern Pop_ups_OK *Pop_OK;
#endif // POP_UPS_OK_H
