#ifndef POP_UPS_NG_H
#define POP_UPS_NG_H

#include <QWidget>
#include "Header_File.h"

namespace Ui {
class Pop_ups_NG;
}

class Pop_ups_NG : public QWidget
{
    Q_OBJECT

public:
    explicit Pop_ups_NG(QWidget *parent = nullptr);
    ~Pop_ups_NG();
     Ui::Pop_ups_NG *ui;
private:


signals:
void Sign_Set_NG(QString unit, int address,int value);//发送NG
private slots:
void on_NG_Continued_clicked();
void on_NG_Stop_clicked();
};
extern Pop_ups_NG *Pop_NG;
#endif // POP_UPS_NG_H
