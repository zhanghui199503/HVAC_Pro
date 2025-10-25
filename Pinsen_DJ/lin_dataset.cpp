#include "lin_dataset.h"
#include "ui_lin_dataset.h"
#include "editablelabel.h"
#include <QDebug>
#include <QDoubleSpinBox>
#include <QDate>
#include <QDir>
#include <QFile>
QStringList Control_Name = {"Set_LIN_Time1","Set_LIN_Time2","Set_LIN_Time3","Set_LIN_Time4","Set_LIN_Time5","Set_LIN_Time6",
                            "Set_LIN_Time7",
                            "Set_LIN_Step1","Set_LIN_Step2","Set_LIN_Step3","Set_LIN_Step4","Set_LIN_Step5","Set_LIN_Step6",
                            "Set_LIN_Step7","Set_LIN_Step8",
                            "Set_LIN_Value1","Set_LIN_Value2","Set_LIN_Value3","Set_LIN_Value4","Set_LIN_Value5",
                            "Set_LIN_Value6","Set_LIN_Value7","Set_LIN_error","Set_LIN_MaxRunTime","Set_LIN_ExtremePOS"};
QStringList ID_Name = {"Set_LIN_NAD","Set_LIN_Controlid","Set_LIN_Stateid"};
QStringList Enable_Name = {"Set_LIN_Enable","Set_LIN_ErrorEnable"};
LIN_Dataset::LIN_Dataset(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LIN_Dataset)
{
    ui->setupUi(this);
    Main_Init();//界面初始化
}

void LIN_Dataset::Main_Init()
{

 }

void LIN_Dataset::slot_NowMode(int index)
{
    Read_Write_Mode = index;
}

void LIN_Dataset::slot_SaveChangeData(QString index)
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

LIN_Dataset::~LIN_Dataset()
{
    delete ui;
}

void LIN_Dataset::on_Set_LIN_Enable_clicked()
{
    //    slot_SaveChangeData("后进";
    if(Read_Write_Mode)
    {
        if(LIN<15)
        {
            if(LIN_Enable_flag == 1)
            {
                LIN_Enable_flag = 0;
                ui->Set_LIN_Enable->setStyleSheet("");
                slot_SaveChangeData("进入修改LIN1-"+QString::number(LIN+1)+"使能，PLC地址:"+QString::number(600865+LIN)+"使能：关");
            }
            else
            {
                LIN_Enable_flag = 1;
                ui->Set_LIN_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
                slot_SaveChangeData("进入修改LIN1-"+QString::number(LIN+1)+"使能，PLC地址:"+QString::number(600865+LIN)+"使能：开");

            }
        }

    }
}


void LIN_Dataset::on_Set_LIN_ErrorEnable_clicked()
{
    if(Read_Write_Mode)
    {
        if(LIN<15)
        {
            if(LIN_ErrorEnable == 0)
            {
                LIN_ErrorEnable = 1;
                ui->Set_LIN_ErrorEnable->setStyleSheet("background-color: rgb(0, 200, 0);");
                slot_SaveChangeData("进入修改LIN1-"+QString::number(LIN+1)+"误差使能，PLC地址:"+QString::number(600880+LIN)+"使能：开");
            }
            else
            {
                LIN_ErrorEnable = 0;
                ui->Set_LIN_ErrorEnable->setStyleSheet("");
                slot_SaveChangeData("进入修改LIN1-"+QString::number(LIN+1)+"使能，PLC地址:"+QString::number(600880+LIN)+"使能：关");
            }
        }
    }
}


void LIN_Dataset::on_Set_LIN_InitEnable_clicked()
{
    if(Read_Write_Mode)
    {
        if(LIN<15)
        {
            if(LIN_InitEnable_flag == 1)
            {
                LIN_InitEnable_flag = 0;
                ui->Set_LIN_InitEnable->setStyleSheet("");
                slot_SaveChangeData("进入修改LIN1-"+QString::number(LIN+1)+"使能，PLC地址:"+QString::number(600865+LIN)+"使能：关");
            }
            else
            {
                LIN_InitEnable_flag = 1;
                ui->Set_LIN_InitEnable->setStyleSheet("background-color: rgb(0, 200, 0);");
                slot_SaveChangeData("进入修改LIN1-"+QString::number(LIN+1)+"使能，PLC地址:"+QString::number(600865+LIN)+"使能：开");

            }
        }

    }
}


void LIN_Dataset::on_Set_LIN_Direction_currentIndexChanged(int index)
{
    if(LIN<15)
    {
        LIN_Direction_flag =index;
    }
}



void LIN_Dataset::on_Set_LIN_InitDirection_currentIndexChanged(int index)
{
    if(LIN<15)
    {
        LIN_InitDirection_flag =index;
    }
}

