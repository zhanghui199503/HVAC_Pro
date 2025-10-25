#ifndef MANUALUI_H
#define MANUALUI_H

#include <QWidget>
#include "Header_File.h"

namespace Ui {
class Manualui;
}

class Manualui : public QWidget
{
    Q_OBJECT

public:
    explicit Manualui(QWidget *parent = nullptr);
    ~Manualui();
    Ui::Manualui *ui;
    int M1_CW = 0,M2_CW = 0,M3_CW = 0,M4_CW = 0,M5_CW = 0,M6_CW = 0,M7_CW = 0,M8_CW = 0,M9_CW = 0,M10_CW = 0,M11_CW = 0,M12_CW = 0,M13_CW = 0,M14_CW = 0,M15_CW = 0,M16_CW = 0,M17_CW = 0,M18_CW = 0;
    int M1_CCW = 0,M2_CCW = 0,M3_CCW = 0,M4_CCW = 0,M5_CCW = 0,M6_CCW = 0,M7_CCW = 0,M8_CCW = 0,M9_CCW = 0,M10_CCW = 0,M11_CCW = 0,M12_CCW = 0,M13_CCW = 0,M14_CCW = 0,M15_CCW = 0,M16_CCW = 0,M17_CCW = 0,M18_CCW = 0;


public slots:
    void  Update_show();//界面刷新
    QString Button_background_color(int result);
    void closeEvent(QCloseEvent *e);
    void ManualInit();//手动界面初始化
private slots:
    void on_Manual_ReadTem_clicked();

//    void on_Manual_Motor_M1_CW_clicked();
//    void on_Manual_Motor_M2_CW_clicked();
//    void on_Manual_Motor_M3_CW_clicked();
//    void on_Manual_Motor_M4_CW_clicked();
//    void on_Manual_Motor_M5_CW_clicked();
//    void on_Manual_Motor_M6_CW_clicked();
//    void on_Manual_Motor_M7_CW_clicked();
//    void on_Manual_Motor_M8_CW_clicked();
//    void on_Manual_Motor_M9_CW_clicked();
//    void on_Manual_Motor_M10_CW_clicked();
//    void on_Manual_Motor_M11_CW_clicked();
//    void on_Manual_Motor_M12_CW_clicked();
//    void on_Manual_Motor_M13_CW_clicked();
//    void on_Manual_Motor_M14_CW_clicked();
//    void on_Manual_Motor_M15_CW_clicked();
//    void on_Manual_Motor_M16_CW_clicked();
//    void on_Manual_Motor_M17_CW_clicked();
//    void on_Manual_Motor_M18_CW_clicked();

//    void on_Manual_Motor_M1_CCW_clicked();
//    void on_Manual_Motor_M2_CCW_clicked();
//    void on_Manual_Motor_M3_CCW_clicked();
//    void on_Manual_Motor_M4_CCW_clicked();
//    void on_Manual_Motor_M5_CCW_clicked();
//    void on_Manual_Motor_M6_CCW_clicked();
//    void on_Manual_Motor_M7_CCW_clicked();
//    void on_Manual_Motor_M8_CCW_clicked();
//    void on_Manual_Motor_M9_CCW_clicked();
//    void on_Manual_Motor_M10_CCW_clicked();
//    void on_Manual_Motor_M11_CCW_clicked();
//    void on_Manual_Motor_M12_CCW_clicked();
//    void on_Manual_Motor_M13_CCW_clicked();
//    void on_Manual_Motor_M14_CCW_clicked();
//    void on_Manual_Motor_M15_CCW_clicked();
//    void on_Manual_Motor_M16_CCW_clicked();
//    void on_Manual_Motor_M17_CCW_clicked();
//    void on_Manual_Motor_M18_CCW_clicked();


    void on_Manual_LIN1_1_clicked();

    void on_Manual_LIN1_2_clicked();
    void on_Manual_LIN1_3_clicked();
    void on_Manual_LIN1_4_clicked();
    void on_Manual_LIN1_5_clicked();
    void on_Manual_LIN1_6_clicked();
    void on_Manual_LIN1_7_clicked();
    void on_Manual_LIN1_8_clicked();
    void on_Manual_LIN1_9_clicked();
    void on_Manual_LIN1_10_clicked();
    void on_Manual_LIN1_11_clicked();
    void on_Manual_LIN1_12_clicked();
    void on_Manual_LIN1_13_clicked();
    void on_Manual_LIN1_14_clicked();
    void on_Manual_LIN1_15_clicked();

    void on_Manual_Lin_Back_clicked();



    void on_Manual_Blower_POS1_clicked();
    void on_Manual_Blower_POS2_clicked();
    void on_Manual_Blower_POS3_clicked();
    void on_Manual_Blower_POS4_clicked();
    void on_Manual_Blower_POS5_clicked();
    void on_Manual_Blower_POS6_clicked();
    void on_Manual_Blower_POS7_clicked();
    void on_Manual_Blower_POS8_clicked();
    void on_Manual_Blower_POS9_clicked();

    void on_Motor_M1_CW_clicked();

private:

signals:
    void Sign_Set_PLCdata(QString unit, int address,int value);//发送设置
    void Sign_Current_interface_flag(int index);//当前界面标志位 手动界面：1
};

extern Manualui *Manualui_Main;
#endif // MANUALUI_H
