#ifndef MOTOR_DATASET_H
#define MOTOR_DATASET_H
//#include "Header_File.h"
#include <QWidget>
//#include <datasetting.h>
//#include "mainwindow.h"
namespace Ui {
class Motor_Dataset;
}

class Motor_Dataset : public QWidget
{
    Q_OBJECT

public:
    explicit Motor_Dataset(QWidget *parent = nullptr);
    ~Motor_Dataset();
    Ui::Motor_Dataset *ui;
    int Motor_Enable_flag = 0;//使能 1 不使能0
    int Motor_RunAsynchronously_flag = 0;//异步运行使能1 不使能0
    int Motor_Mode_flag = 0;//电机类型 1：PT 2：步进
    int Motor_PT_Mode_flag = 0;//PT电机类型 1：5线电机 2:2线电机
    int Motor_PT_Direction_flag = 0;//PT电机方向 1：5到0V 2:0到5V
    int Motor_PT_Line2_flag = 0;//2线PT电机类型 1：堵转 2:停止
    int Motor_V_flag = 0;//电机电压 1:24V 2:12V
    int Motor = 0;//电机标志位
    int Read_Write_Mode1 = 0;//判断当前模式 0读取模式 1写入模式
public slots:
    void Main_Init();//界面初始化
    void slot_SaveChangeData(QString);//保存改变值
    void slot_NowMode1(int index);//判断当前模式 0读取模式 1写入模式

private slots:
    void on_Set_Motor_Enable_clicked();

//    void on_Set_Motor_RunAsynchronously_clicked();

    void on_Set_Motor_PT_clicked();

    void on_Set_Motor_BJ_clicked();

    void on_Set_PT_2Line_clicked();

    void on_Set_PT_5Line_clicked();

    void on_Set_CW5_0_clicked();

    void on_Set_CW0_5_clicked();

    void on_Set_Line2_Stuck_clicked();

    void on_Set_Line2_Stop_clicked();




private:

signals:
    void Sign_Set_PLCMotorData(QString unit, int address,int value);//发送设置
};

#endif // MOTOR_DATASET_H
