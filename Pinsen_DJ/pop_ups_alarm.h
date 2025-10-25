#ifndef POP_UPS_ALARM_H
#define POP_UPS_ALARM_H

#include <QWidget>
#include "Header_File.h"

namespace Ui {
class Pop_ups_Alarm;
}

class Pop_ups_Alarm : public QWidget
{
    Q_OBJECT

public:
    explicit Pop_ups_Alarm(QWidget *parent = nullptr);
    ~Pop_ups_Alarm();
    Ui::Pop_ups_Alarm *ui;
private:

};
extern Pop_ups_Alarm *Pop_Alarm;
#endif // POP_UPS_ALARM_H
