#include "motor_dataset.h"
#include "ui_motor_dataset.h"
#include "editablelabel.h"
#include <QtDebug>
#include <QDate>
#include <QDir>
#include <QFile>
QStringList Spinbox_Name = {"Set_Motor_Delay_1","Set_Motor_Delay_2","Set_Motor_Delay_3","Set_Motor_Delay_4","Set_Motor_Delay_5",
                            "Set_Motor_Delay_6","Set_Motor_Delay_7","Set_Motor_Delay_8",
                            "Set_Motor_Steps_1","Set_Motor_Steps_2","Set_Motor_Steps_3","Set_Motor_Steps_4","Set_Motor_Steps_5",
                            "Set_Motor_Steps_6","Set_Motor_Steps_7","Set_Motor_Steps_8",
                            "Set_PtMotor_Max_POS_1","Set_PtMotor_Max_POS_2","Set_PtMotor_Max_POS_3","Set_PtMotor_Max_POS_4",
                            "Set_PtMotor_Max_POS_5","Set_PtMotor_Max_POS_6","Set_PtMotor_Max_POS_7","Set_PtMotor_Max_POS_8",
                            "Set_PtMotor_Min_POS_1","Set_PtMotor_Min_POS_2","Set_PtMotor_Min_POS_3","Set_PtMotor_Min_POS_4",
                            "Set_PtMotor_Min_POS_5","Set_PtMotor_Min_POS_6","Set_PtMotor_Min_POS_7","Set_PtMotor_Min_POS_8",
                            "Set_BjMotor_Max_POS_1","Set_BjMotor_Max_POS_2","Set_BjMotor_Max_POS_3","Set_BjMotor_Max_POS_4",
                            "Set_BjMotor_Max_POS_5","Set_BjMotor_Max_POS_6","Set_BjMotor_Max_POS_7","Set_BjMotor_Max_POS_8",
                            "Set_BjMotor_Min_POS_7","Set_BjMotor_Min_POS_8",
                            "Set_Motor_Run_Max_A","Set_Motor_Run_Min_A", "Set_Motor_Stuck_A","Set_Motor_Delay_alarm", "Set_Motor_Start_Delay",
                            "Set_Motor_Run_MaxTime", "Set_Motor_Limit_1_F", "Set_Motor_Limit_2_F", "Set_BJMotor_HZ", "Set_Line2Motor_RunTime"
                           };
QStringList button_Name = {"Set_Motor_Enable",
                           "Set_Motor_PT","Set_Motor_BJ","Set_PT_5Line","Set_PT_2Line","Set_CW5_0","Set_CW0_5","Set_Line2_Stuck","Set_Line2_Stop",
                           "Set_Motor_24V","Set_Motor_12V"};
Motor_Dataset::Motor_Dataset(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Motor_Dataset)
{
    ui->setupUi(this);
    Main_Init();
}

Motor_Dataset::~Motor_Dataset()
{
    delete ui;
}

void Motor_Dataset::Main_Init()
{
//    QList<QDoubleSpinBox *> Motor_DoubleSpinbox;
//    Motor_DoubleSpinbox.append(ui->Set_Motor_Delay_1);Motor_DoubleSpinbox.append(ui->Set_Motor_Delay_2);Motor_DoubleSpinbox.append(ui->Set_Motor_Delay_3);
//    Motor_DoubleSpinbox.append(ui->Set_Motor_Delay_4);Motor_DoubleSpinbox.append(ui->Set_Motor_Delay_5);;Motor_DoubleSpinbox.append(ui->Set_Motor_Delay_6);
//    Motor_DoubleSpinbox.append(ui->Set_Motor_Delay_7);
//    Motor_DoubleSpinbox.append(ui->Set_Motor_Steps_1);Motor_DoubleSpinbox.append(ui->Set_Motor_Steps_2);Motor_DoubleSpinbox.append(ui->Set_Motor_Steps_3);
//    Motor_DoubleSpinbox.append(ui->Set_Motor_Steps_4);Motor_DoubleSpinbox.append(ui->Set_Motor_Steps_5);Motor_DoubleSpinbox.append(ui->Set_Motor_Steps_6);
//    Motor_DoubleSpinbox.append(ui->Set_Motor_Steps_7);Motor_DoubleSpinbox.append(ui->Set_Motor_Steps_8);
//    Motor_DoubleSpinbox.append(ui->Set_PtMotor_Max_POS_1);Motor_DoubleSpinbox.append(ui->Set_PtMotor_Min_POS_1);
//    Motor_DoubleSpinbox.append(ui->Set_PtMotor_Max_POS_2);Motor_DoubleSpinbox.append(ui->Set_PtMotor_Min_POS_2);
//    Motor_DoubleSpinbox.append(ui->Set_PtMotor_Max_POS_3);Motor_DoubleSpinbox.append(ui->Set_PtMotor_Min_POS_3);
//    Motor_DoubleSpinbox.append(ui->Set_PtMotor_Max_POS_4);Motor_DoubleSpinbox.append(ui->Set_PtMotor_Min_POS_4);
//    Motor_DoubleSpinbox.append(ui->Set_PtMotor_Max_POS_5);Motor_DoubleSpinbox.append(ui->Set_PtMotor_Min_POS_5);
//    Motor_DoubleSpinbox.append(ui->Set_PtMotor_Max_POS_6);Motor_DoubleSpinbox.append(ui->Set_PtMotor_Min_POS_6);
//    Motor_DoubleSpinbox.append(ui->Set_PtMotor_Max_POS_7);Motor_DoubleSpinbox.append(ui->Set_PtMotor_Min_POS_7);
//    Motor_DoubleSpinbox.append(ui->Set_PtMotor_Max_POS_8);Motor_DoubleSpinbox.append(ui->Set_PtMotor_Min_POS_8);
//    Motor_DoubleSpinbox.append(ui->Set_BjMotor_Max_POS_1);Motor_DoubleSpinbox.append(ui->Set_BjMotor_Max_POS_2);
//    Motor_DoubleSpinbox.append(ui->Set_BjMotor_Max_POS_3);Motor_DoubleSpinbox.append(ui->Set_BjMotor_Max_POS_4);
//    Motor_DoubleSpinbox.append(ui->Set_BjMotor_Max_POS_5);Motor_DoubleSpinbox.append(ui->Set_BjMotor_Max_POS_6);
//    Motor_DoubleSpinbox.append(ui->Set_BjMotor_Max_POS_7);Motor_DoubleSpinbox.append(ui->Set_BjMotor_Max_POS_8);
//    Motor_DoubleSpinbox.append(ui->Set_BjMotor_Min_POS_7);Motor_DoubleSpinbox.append(ui->Set_BjMotor_Min_POS_8);
//    Motor_DoubleSpinbox.append(ui->Set_Motor_Run_Max_A);Motor_DoubleSpinbox.append(ui->Set_Motor_Run_Min_A);Motor_DoubleSpinbox.append(ui->Set_Motor_Stuck_A);
//    Motor_DoubleSpinbox.append(ui->Set_Motor_Start_Delay);Motor_DoubleSpinbox.append(ui->Set_Motor_Delay_alarm);Motor_DoubleSpinbox.append(ui->Set_Motor_Run_MaxTime);
//    Motor_DoubleSpinbox.append(ui->Set_Motor_Limit_1_F);Motor_DoubleSpinbox.append(ui->Set_Motor_Limit_2_F);Motor_DoubleSpinbox.append(ui->Set_Line2Motor_RunTime);

//    for (int i =0;i<Motor_DoubleSpinbox.count() ;i++ )
//    {
//        connect(Motor_DoubleSpinbox.at(i),SIGNAL(valueChanged(QString)),this, SLOT(slot_DoubleSpinBox_textChange(QString)));
//    }
}

void Motor_Dataset::slot_SaveChangeData(QString index)
{
    QString Path = QApplication::applicationDirPath() + "\\Changdata\\" + QDate::currentDate().toString("yyyy_MM") + "//";
    QDir curDir(Path);
    if(!curDir.exists(Path)){//如果路径不存在则创建
        curDir.mkpath(Path);
    }

//    QString contextInfo = QString("[%1: %2]").arg(QString(context.file)).arg(context.line);//代码所在文件及行数
    QString contextTime = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");//当前时间

    QString mess = QString("%1:%2").arg(contextTime).arg(index);//一行日志信息
    QFile contextFile(Path + QDate::currentDate().toString("yyyy_MM_dd") +".log");
    contextFile.open(QIODevice::WriteOnly | QIODevice::Append);//以只写或追加方式打开文件
    QTextStream contextStream(&contextFile);//定义文件流
    contextStream << mess << "\r\n";//将文件流写入文件
    contextFile.flush();
    contextFile.close();
//    mutex.unlock();//释放互斥量
}

void Motor_Dataset::slot_NowMode1(int index)
{
    Read_Write_Mode1 = index;
}

void Motor_Dataset::on_Set_Motor_Enable_clicked()//设置电机使能
{
    if(Read_Write_Mode1)
    {
        if(Motor_Enable_flag == 0)
        {
            Motor_Enable_flag = 1;

            ui->Set_Motor_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("电机M"+QString::number(Motor+1)+"使能改为1");
        }
        else
        {
            Motor_Enable_flag = 0;
            ui->Set_Motor_Enable->setStyleSheet("");
            slot_SaveChangeData("电机M"+QString::number(Motor+1)+"使能改为0");
        }
    }
}

void Motor_Dataset::on_Set_Motor_PT_clicked()//设置电机为PT电机
{
    if(Read_Write_Mode1)
    {
        Motor_Mode_flag = 0;
        ui->Set_Motor_PT->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Set_Motor_BJ->setStyleSheet("");
        ui->BJ_POS_Data->hide();
        ui->PT_POS_Data->show();
        slot_SaveChangeData("电机M"+QString::number(Motor+1)+"类型改为伺服电机");
    }
}

void Motor_Dataset::on_Set_Motor_BJ_clicked()//设置电机为步进电机
{
    if(Read_Write_Mode1)
    {
        Motor_Mode_flag = 2;
        ui->Set_Motor_BJ->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Set_Motor_PT->setStyleSheet("");
        ui->BJ_POS_Data->show();
        ui->PT_POS_Data->hide();
        slot_SaveChangeData("电机M"+QString::number(Motor+1)+"类型改为步进电机");
    }
}

void Motor_Dataset::on_Set_PT_5Line_clicked()//设置电机为5线型
{
    if(Read_Write_Mode1)
    {
        Motor_PT_Mode_flag = 1;
        ui->Set_PT_5Line->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Set_PT_2Line->setStyleSheet("");
        slot_SaveChangeData("电机M"+QString::number(Motor+1)+"改为5线电机");
    }
}

void Motor_Dataset::on_Set_PT_2Line_clicked()//设置电机为2线型
{
    if(Read_Write_Mode1)
    {
        Motor_PT_Mode_flag = 2;
        ui->Set_PT_2Line->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Set_PT_5Line->setStyleSheet("");
        slot_SaveChangeData("电机M"+QString::number(Motor+1)+"改为2线电机");
    }
}

void Motor_Dataset::on_Set_CW5_0_clicked()//设置电机旋转方向5~0V
{
    if(Read_Write_Mode1)
    {
        Motor_PT_Direction_flag = 1;
        ui->Set_CW5_0->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Set_CW0_5->setStyleSheet("");
        slot_SaveChangeData("电机M"+QString::number(Motor+1)+"旋转方向改为5~0V");
    }
}


void Motor_Dataset::on_Set_CW0_5_clicked()//设置电机旋转方向0~5V
{
    if(Read_Write_Mode1)
    {
        Motor_PT_Direction_flag = 2;
        ui->Set_CW0_5->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Set_CW5_0->setStyleSheet("");
        slot_SaveChangeData("电机M"+QString::number(Motor+1)+"旋转方向改为0~5V");
    }
}

void Motor_Dataset::on_Set_Line2_Stuck_clicked()//设置2线电机为堵转型
{
    if(Read_Write_Mode1)
    {
        Motor_PT_Line2_flag = 1;
        ui->Set_Line2_Stuck->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Set_Line2_Stop->setStyleSheet("");
        slot_SaveChangeData("电机M"+QString::number(Motor+1)+"改为2线堵转型电机");
    }
}

void Motor_Dataset::on_Set_Line2_Stop_clicked()//设置2线电机为停止型
{
    if(Read_Write_Mode1)
    {
        Motor_PT_Line2_flag = 2;
        ui->Set_Line2_Stop->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Set_Line2_Stuck->setStyleSheet("");
        slot_SaveChangeData("电机M"+QString::number(Motor+1)+"改为2线停止型电机");
    }
}
