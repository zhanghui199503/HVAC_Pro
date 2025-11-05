#include "datasetting.h"
#include "ui_datasetting.h"
//#include "qglobal.h"
DataSetting *Data_Set;
//int Read_Write_Mode = 0;
QList<QScrollArea *> LIN_container;
QList<QScrollArea *> Motor_container;

//---------------------震动----------------------
QList<EditableLabel*> vibrationNameWidgets;//振动POS名字
QList<QDoubleSpinBox*> xVibrationMaxWidgets;//X轴上限
QList<QDoubleSpinBox*> xVibrationMinWidgets;//X轴下限
QList<QDoubleSpinBox*> yVibrationMaxWidgets;//Y轴上限
QList<QDoubleSpinBox*> yVibrationMinWidgets;//Y轴下限
QList<QDoubleSpinBox*> zVibrationMaxWidgets;//Z轴上限
QList<QDoubleSpinBox*> zVibrationMinWidgets;//Z轴下限
QList<QDoubleSpinBox*> noisesMaxWidgets;//噪音上限
QList<QDoubleSpinBox*> noisesMinWidgets;//噪音下限

//---------------------鼓风机----------------------
QList<QDoubleSpinBox*> Blower_StepsWidgets;//鼓风机运行顺序

QList<EditableLabel*> VBlowerPosNameWidgets;//端电压鼓风机POS名称
QList<QDoubleSpinBox*> VBlowerVWidgets;//端电压鼓风机端电压
QList<QDoubleSpinBox*> VBlowerTimeWidgets;//端电压鼓风机运行时间
QList<QDoubleSpinBox*> VBlowerMaxAWidgets;//端电压鼓风机电流上限
QList<QDoubleSpinBox*> VBlowerMinAWidgets;//端电压鼓风机电流下限

QList<EditableLabel*> PWMBlowerPosNameWidgets;//PWM鼓风机POS名称
QList<QDoubleSpinBox*> PWMBlowerPWMWidgets;//PWM鼓风机端电压
QList<QDoubleSpinBox*> PWMBlowerTimeWidgets;//PWM鼓风机运行时间
QList<QDoubleSpinBox*> PWMBlowerMaxAWidgets;//PWM鼓风机电流上限
QList<QDoubleSpinBox*> PWMBlowerMinAWidgets;//PWM鼓风机电流下限

QList<EditableLabel*> LINBlowerPosNameWidgets;//LIN鼓风机POS名称
QList<QDoubleSpinBox*> LINBlowerLINWidgets;//LIN鼓风机端电压
QList<QDoubleSpinBox*> LINBlowerTimeWidgets;//LIN鼓风机运行时间
QList<QDoubleSpinBox*> LINBlowerMaxAWidgets;//LIN鼓风机电流上限
QList<QDoubleSpinBox*> LINBlowerMinAWidgets;//LIN鼓风机电流下限

//---------------------电子膨胀阀----------------------

QList<EditableLabel*> ExpansionPosNameWidgets;//电子膨胀阀POS名称
QList<QDoubleSpinBox*> ExpansionStepWidgets;//电子膨胀阀运行顺序
QList<QDoubleSpinBox*> ExpansionTimeWidgets;//电子膨胀阀跳转时间
QList<QDoubleSpinBox*> ExpansionValueWidgets;//电子膨胀阀步数

//---------------------电阻----------------------
QList<int> Res_EnableWidgets;//电阻使能
QList<QPushButton*> Res_EnableButtonWidgets;//电阻按钮
QList<QLineEdit*> ResNameWidgets;//电阻名称
QList<QDoubleSpinBox*> ResValueWidgets;//电阻阻值
QList<QDoubleSpinBox*> ResTempWidgets;//电阻XX温度下
QList<QDoubleSpinBox*> ResMaterialConstantWidgets;//电阻材料常数
QList<QDoubleSpinBox*> ResMaxValueWidgets;//电阻温度上限
QList<QDoubleSpinBox*> ResMinValueWidgets;//电阻温度下限

//---------------------风速----------------------
QList<int> Speed_EnableWidgets;//风速使能
QList<QPushButton*> Speed_EnableButtonWidgets;//风速按钮
QList<QLineEdit*> SpeedNameWidgets;//风速名称
QList<QDoubleSpinBox*> SpeedMode1MaxMinValueWidgets;//风速1档上下限
QList<QDoubleSpinBox*> SpeedMode2MaxMinValueWidgets;//风速2档上下限
QList<QDoubleSpinBox*> SpeedMode3MaxMinValueWidgets;//风速3档上下限
QList<QDoubleSpinBox*> SpeedMode4MaxMinValueWidgets;//风速4档上下限
QList<QDoubleSpinBox*> SpeedMode5MaxMinValueWidgets;//风速5档上下限
QList<QDoubleSpinBox*> SpeedMode6MaxMinValueWidgets;//风速6档上下限
QList<QDoubleSpinBox*> SpeedMode7MaxMinValueWidgets;//风速7档上下限
QList<QDoubleSpinBox*> SpeedMode8MaxMinValueWidgets;//风速8档上下限


//---------------------检测顺序----------------------

QList<QDoubleSpinBox*> EquenceWidgets;//检测顺序

QVector<QString> sqlData = {"序号","频道号","修改日期"};


QVector<QString> sqldataLINLimitData = {"LIN1_1POS1上下限","LIN1_1POS2上下限","LIN1_1POS3上下限","LIN1_1POS4上下限","LIN1_1POS5上下限","LIN1_1POS6上下限","LIN1_1POS7上下限","LIN1_1POS8上下限",
                                        "LIN1_2POS1上下限","LIN1_2POS2上下限","LIN1_2POS3上下限","LIN1_2POS4上下限","LIN1_2POS5上下限","LIN1_2POS6上下限","LIN1_2POS7上下限","LIN1_2POS8上下限",
                                        "LIN1_3POS1上下限","LIN1_3POS2上下限","LIN1_3POS3上下限","LIN1_3POS4上下限","LIN1_3POS5上下限","LIN1_3POS6上下限","LIN1_3POS7上下限","LIN1_3POS8上下限",
                                        "LIN1_4POS1上下限","LIN1_4POS2上下限","LIN1_4POS3上下限","LIN1_4POS4上下限","LIN1_4POS5上下限","LIN1_4POS6上下限","LIN1_4POS7上下限","LIN1_4POS8上下限",
                                        "LIN1_5POS1上下限","LIN1_5POS2上下限","LIN1_5POS3上下限","LIN1_5POS4上下限","LIN1_5POS5上下限","LIN1_5POS6上下限","LIN1_5POS7上下限","LIN1_5POS8上下限",
                                        "LIN1_6POS1上下限","LIN1_6POS2上下限","LIN1_6POS3上下限","LIN1_6POS4上下限","LIN1_6POS5上下限","LIN1_6POS6上下限","LIN1_6POS7上下限","LIN1_6POS8上下限",
                                        "LIN1_7POS1上下限","LIN1_7POS2上下限","LIN1_7POS3上下限","LIN1_7POS4上下限","LIN1_7POS5上下限","LIN1_7POS6上下限","LIN1_7POS7上下限","LIN1_7POS8上下限",
                                        "LIN1_8POS1上下限","LIN1_8POS2上下限","LIN1_8POS3上下限","LIN1_8POS4上下限","LIN1_8POS5上下限","LIN1_8POS6上下限","LIN1_8POS7上下限","LIN1_8POS8上下限",
                                        "LIN1_9POS1上下限","LIN1_9POS2上下限","LIN1_9POS3上下限","LIN1_9POS4上下限","LIN1_9POS5上下限","LIN1_9POS6上下限","LIN1_9POS7上下限","LIN1_9POS8上下限",
                                        "LIN1_10POS1上下限","LIN1_10POS2上下限","LIN1_10POS3上下限","LIN1_10POS4上下限","LIN1_10POS5上下限","LIN1_10POS6上下限","LIN1_10POS7上下限","LIN1_10POS8上下限",
                                        "LIN1_11POS1上下限","LIN1_11POS2上下限","LIN1_11POS3上下限","LIN1_11POS4上下限","LIN1_11POS5上下限","LIN1_11POS6上下限","LIN1_11POS7上下限","LIN1_11POS8上下限",
                                        "LIN1_12POS1上下限","LIN1_12POS2上下限","LIN1_12POS3上下限","LIN1_12POS4上下限","LIN1_12POS5上下限","LIN1_12POS6上下限","LIN1_12POS7上下限","LIN1_12POS8上下限"
                                       };
QVector<QString> sqldataPTLimitData = {"PT1POS1上下限","PT1POS2上下限","PT1POS3上下限","PT1POS4上下限","PT1POS5上下限","PT1POS6上下限","PT1POS7上下限","PT1POS8上下限",
                                       "PT2POS1上下限","PT2POS2上下限","PT2POS3上下限","PT2POS4上下限","PT2POS5上下限","PT2POS6上下限","PT2POS7上下限","PT2POS8上下限",
                                       "PT3POS1上下限","PT3POS2上下限","PT3POS3上下限","PT3POS4上下限","PT3POS5上下限","PT3POS6上下限","PT3POS7上下限","PT3POS8上下限",
                                       "PT4POS1上下限","PT4POS2上下限","PT4POS3上下限","PT4POS4上下限","PT4POS5上下限","PT4POS6上下限","PT4POS7上下限","PT4POS8上下限",
                                       "PT5POS1上下限","PT5POS2上下限","PT5POS3上下限","PT5POS4上下限","PT5POS5上下限","PT5POS6上下限","PT5POS7上下限","PT5POS8上下限",
                                       "PT6POS1上下限","PT6POS2上下限","PT6POS3上下限","PT6POS4上下限","PT6POS5上下限","PT6POS6上下限","PT6POS7上下限","PT6POS8上下限",
                                       "PT7POS1上下限","PT7POS2上下限","PT7POS3上下限","PT7POS4上下限","PT7POS5上下限","PT7POS6上下限","PT7POS7上下限","PT7POS8上下限",
                                       "PT8POS1上下限","PT8POS2上下限","PT8POS3上下限","PT8POS4上下限","PT8POS5上下限","PT8POS6上下限","PT8POS7上下限","PT8POS8上下限",
                                       "PT9POS1上下限","PT9POS2上下限","PT9POS3上下限","PT9POS4上下限","PT9POS5上下限","PT9POS6上下限","PT9POS7上下限","PT9POS8上下限",
                                       "PT10POS1上下限","PT10POS2上下限","PT10POS3上下限","PT10POS4上下限","PT10POS5上下限","PT10POS6上下限","PT10POS7上下限","PT10POS8上下限",
                                       "PT11POS1上下限","PT11POS2上下限","PT11POS3上下限","PT11POS4上下限","PT11POS5上下限","PT11POS6上下限","PT11POS7上下限","PT11POS8上下限",
                                       "PT12POS1上下限","PT12POS2上下限","PT12POS3上下限","PT12POS4上下限","PT12POS5上下限","PT12POS6上下限","PT12POS7上下限","PT12POS8上下限"
                                      };
QVector<QString> sqldataBlowerLimitData = {"BlowerPOS1上下限","BlowerPOS2上下限","BlowerPOS3上下限","BlowerPOS4上下限","BlowerPOS5上下限","BlowerPOS6上下限","BlowerPOS7上下限","BlowerPOS8上下限","BlowerPOS9上下限",
                                           "X_vibrationPOS1上下限","X_vibrationPOS2上下限","X_vibrationPOS3上下限","X_vibrationPOS4上下限","X_vibrationPOS5上下限","X_vibrationPOS6上下限","X_vibrationPOS7上下限","X_vibrationPOS8上下限","X_vibrationPOS9上下限",
                                           "Y_vibrationPOS1上下限","Y_vibrationPOS2上下限","Y_vibrationPOS3上下限","Y_vibrationPOS4上下限","Y_vibrationPOS5上下限","Y_vibrationPOS6上下限","Y_vibrationPOS7上下限","Y_vibrationPOS8上下限","Y_vibrationPOS9上下限",
                                           "Z_vibrationPOS1上下限","Z_vibrationPOS2上下限","Z_vibrationPOS3上下限","Z_vibrationPOS4上下限","Z_vibrationPOS5上下限","Z_vibrationPOS6上下限","Z_vibrationPOS7上下限","Z_vibrationPOS8上下限","Z_vibrationPOS9上下限",
                                           "NoisesPOS1上下限","NoisesPOS2上下限","NoisesPOS3上下限","NoisesPOS4上下限","NoisesPOS5上下限","NoisesPOS6上下限","NoisesPOS7上下限","NoisesPOS8上下限","NoisesPOS9上下限",
                                           "Res1上下限","Res2上下限","Res3上下限","Res4上下限","Res5上下限","Res6上下限","Res7上下限","Res8上下限","Res9上下限","Res10上下限","Res11上下限","Res12上下限"
                                          };



//QStringList Equence_Name
DataSetting::DataSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataSetting)
{
    ui->setupUi(this);
    Main_Init();
    UI_init();
    ui->SetMain_WriteMode->click();
    Read_inifile();
    qputenv("QT_SCALE_FACTOR", "0.5");  // 设置全局缩放因子为1.5倍
}

void DataSetting::functChanged()
{
    qDebug() << sender();
    qDebug() << "this is a signal!!!";
}



void DataSetting::Main_Init()//界面初始化
{
    list_CBB<<ui->CBB_posBoard_1<<ui->CBB_posBoard_2<<ui->CBB_posBoard_3<<ui->CBB_posBoard_4
           <<ui->CBB_posBoard_5<<ui->CBB_posBoard_6<<ui->CBB_posBoard_7<<ui->CBB_posBoard_8
          <<ui->CBB_posBoard_9<<ui->CBB_posBoard_10<<ui->CBB_posBoard_11<<ui->CBB_posBoard_12
         <<ui->CBB_posBoard_13<<ui->CBB_posBoard_14<<ui->CBB_posBoard_15<<ui->CBB_posBoard_16
        <<ui->CBB_posBoard_17<<ui->CBB_posBoard_18<<ui->CBB_posBoard_19<<ui->CBB_posBoard_20
       <<ui->CBB_posBoard_21<<ui->CBB_posBoard_22<<ui->CBB_posBoard_23<<ui->CBB_posBoard_24;


    LIN_container.append(ui->scrollArea);LIN_container.append(ui->scrollArea_2);LIN_container.append(ui->scrollArea_3);LIN_container.append(ui->scrollArea_4);
    LIN_container.append(ui->scrollArea_5);LIN_container.append(ui->scrollArea_6);LIN_container.append(ui->scrollArea_7);LIN_container.append(ui->scrollArea_8);
    LIN_container.append(ui->scrollArea_9);LIN_container.append(ui->scrollArea_10);LIN_container.append(ui->scrollArea_11);LIN_container.append(ui->scrollArea_12);
    for (int i =0;i<12 ;i++ )
    {
        LIN_Dataset *lin1 = new LIN_Dataset();
        connect(this, &DataSetting::Sign_Set_Mode, lin1 , &LIN_Dataset::slot_NowMode);
        LIN_Main.append(lin1);
        LIN_Main.at(i)->LIN = i;
        QVBoxLayout *layout = new QVBoxLayout();
        layout->setMargin(0);
        layout->addWidget(lin1);
        LIN_container.at(i)->setFrameShape(QFrame::NoFrame);
        LIN_container.at(i)->setLayout(layout);
        LIN_Main.at(i)->ui->LIN->setTitle("LIN1."+QString::number(i+1));

    }
    Motor_container.append(ui->scrollArea_31);Motor_container.append(ui->scrollArea_32);Motor_container.append(ui->scrollArea_33);Motor_container.append(ui->scrollArea_34);
    Motor_container.append(ui->scrollArea_35);Motor_container.append(ui->scrollArea_36);Motor_container.append(ui->scrollArea_37);Motor_container.append(ui->scrollArea_38);
    Motor_container.append(ui->scrollArea_39);Motor_container.append(ui->scrollArea_40);Motor_container.append(ui->scrollArea_41);Motor_container.append(ui->scrollArea_42);

    for (int i =0;i<12 ;i++ )
    {
        Motor_Dataset *Motor1 = new Motor_Dataset();
        connect(this, &DataSetting::Sign_Set_Mode, Motor1 , &Motor_Dataset::slot_NowMode1);
        Motor_Main.append(Motor1);
        Motor_Main.at(i)->Motor = i;
        QVBoxLayout *layout = new QVBoxLayout();
        layout->setMargin(0);
        layout->addWidget(Motor1);
        Motor_container.at(i)->setFrameShape(QFrame::NoFrame);
        Motor_container.at(i)->setLayout(layout);
        Motor_Main.at(i)->ui->Motor->setTitle("伺服电机"+QString::number(i+1));
    }
    for(int i = 1;i<31;i++)
    {
        ui->DataSeting_PD->addItems({QString::number(i)});//频道
    }
    //获取当前计算机所有串口设备
    QList<QSerialPortInfo> coms = QSerialPortInfo::availablePorts();
    QStringList list_ports;
    for(int i=0; i<coms.size(); i++){
        list_ports.append(coms[i].portName());
    }
    ui->Serial_Number->addItems(list_ports);
    ui->Serial_Number2->addItems(list_ports);
    ui->Serial_Number3->addItems(list_ports);
    ui->Serial_Num->addItem("485扩展");
    ui->Serial_Num->addItems(list_ports);
    ui->Serial_Num_2->addItems(list_ports);
    ui->Serial_Num_3->addItems(list_ports);
    for (int i=1;i<10 ;i++ ) {
        ui->BoardNum->addItem(QString::number(i));
        ui->BoardNum_2->addItem(QString::number(i));
        ui->BoardNum_3->addItem(QString::number(i));
        ui->StationNum->addItem(QString::number(i));
    }


}

void DataSetting::slot_SaveChangeData(QString index)
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

void DataSetting::on_Set_Blower_Enable_clicked()//鼓风机使能
{
    if(Read_Write_Mode == 1)
    {
        if(Blower_Enable_flag == 1)
        {
            Blower_Enable_flag = 0;
            ui->Set_Blower_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改鼓风机使能，PLC地址:602045,修改值:"+QString::number(0));
        }
        else
        {
            Blower_Enable_flag = 1;
            ui->Set_Blower_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改鼓风机使能，PLC地址:602045,修改值:"+QString::number(1));
        }
    }

}

void DataSetting::on_Set_Blower_V_clicked()//电压型鼓风机
{
    if(Read_Write_Mode == 1)
    {
        Blower_Mode_flag = 1;
        ui->Set_Blower_V->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Blower_mode->setCurrentIndex(0);
        ui->Set_Blower_PWM->setStyleSheet("");
        ui->Set_Blower_LIN->setStyleSheet("");
    }

}

void DataSetting::on_Set_Blower_PWM_clicked()//PWM型鼓风机
{
    if(Read_Write_Mode == 1)
    {
        Blower_Mode_flag = 2;
        ui->Set_Blower_PWM->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Blower_mode->setCurrentIndex(1);
        ui->Set_Blower_V->setStyleSheet("");
        ui->Set_Blower_LIN->setStyleSheet("");
    }

}

void DataSetting::on_Set_Blower_LIN_clicked()//LIN型鼓风机
{
    if(Read_Write_Mode == 1)
    {
        Blower_Mode_flag = 3;
        ui->Set_Blower_LIN->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Blower_mode->setCurrentIndex(2);
        ui->Set_Blower_V->setStyleSheet("");
        ui->Set_Blower_PWM->setStyleSheet("");
    }
}

void DataSetting::on_Set_Blower_RPMcontrast_clicked()//LIN鼓风机转速比对
{
    if(Read_Write_Mode == 1)
    {
        if(Blower_RPMcontrast_flag == 1)
        {
            Blower_RPMcontrast_flag = 0;
            ui->Set_Blower_RPMcontrast->setStyleSheet("");
            ui->Set_Blower_RPMcontrast->setText("OFF");
        }
        else
        {
            Blower_RPMcontrast_flag = 1;
            ui->Set_Blower_RPMcontrast->setStyleSheet("background-color: rgb(0, 200, 0);");
            ui->Set_Blower_RPMcontrast->setText("ON");
        }
    }

}

void DataSetting::on_X_vibration_Enable_clicked()//振动X轴使能
{
    if(Read_Write_Mode == 1)
    {
        if(X_vibration_Enable_flag == 1)
        {
            X_vibration_Enable_flag = 0;
            ui->X_vibration_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改振动X轴使能，PLC地址:602114,使能：关");
        }
        else
        {
            X_vibration_Enable_flag = 1;
            ui->X_vibration_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改振动X轴使能，PLC地址:602114,使能：开");
        }
    }
}

void DataSetting::on_Y_vibration_Enable_clicked()//振动Y轴使能
{
    if(Read_Write_Mode == 1)
    {
        if(Y_vibration_Enable_flag == 1)
        {
            Y_vibration_Enable_flag = 0;
            ui->Y_vibration_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改振动Y轴使能，PLC地址:602115,使能：关");
        }
        else
        {
            Y_vibration_Enable_flag = 1;
            ui->Y_vibration_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改振动Y轴使能，PLC地址:602115,使能：开");
        }
    }
}

void DataSetting::on_Z_vibration_Enable_clicked()//振动Z轴使能
{
    if(Read_Write_Mode == 1)
    {
        if(Z_vibration_Enable_flag == 1)
        {
            Z_vibration_Enable_flag = 0;
            ui->Z_vibration_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改振动Z轴使能，PLC地址:602116,使能：关");
        }
        else
        {
            Z_vibration_Enable_flag = 1;
            ui->Z_vibration_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改振动Z轴使能，PLC地址:602116,使能：开");
        }
    }
}

//---------------------------------------风速---------------------------------------------

void DataSetting::on_Speed_contrast_Enable_clicked()//风速对比检测使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_contrast_Enable_flag==0)
        {
            Speed_contrast_Enable_flag =1;
            slot_SaveChangeData("进入修改风速对比检测使能，PLC地址:602677,使能：开");
        }
        else
        {
            Speed_contrast_Enable_flag =0;
            slot_SaveChangeData("进入修改风速对比检测使能，PLC地址:602677,使能：关");
        }
    }
}

void DataSetting::on_Speed_Cylinder1_Enable_clicked()//风速气缸1使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_Cylinder1Enable_flag == 1)
        {
            Speed_Cylinder1Enable_flag = 0;
            ui->Speed_Cylinder1_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速气缸1使能，PLC地址:602397,使能：关");
        }
        else
        {
            Speed_Cylinder1Enable_flag = 1;
            ui->Speed_Cylinder1_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");

            slot_SaveChangeData("进入修改风速气缸1使能，PLC地址:602397,使能：开");
        }
    }
}

void DataSetting::on_Speed_Cylinder2_Enable_clicked()//风速气缸2使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_Cylinder2Enable_flag == 1)
        {
            Speed_Cylinder2Enable_flag = 0;

            ui->Speed_Cylinder2_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速气缸2使能，PLC地址:602398,使能：关");
        }
        else
        {
            Speed_Cylinder2Enable_flag = 1;
            ui->Speed_Cylinder2_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速气缸2使能，PLC地址:602398,使能：开");
        }
    }
}

void DataSetting::on_Speed_Cylinder3_Enable_clicked()//风速气缸3使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_Cylinder3Enable_flag == 1)
        {
            Speed_Cylinder3Enable_flag = 0;
            ui->Speed_Cylinder3_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速气缸3使能，PLC地址:602399,使能：关");
        }
        else
        {
            Speed_Cylinder3Enable_flag = 1;
            ui->Speed_Cylinder3_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速气缸3使能，PLC地址:602399,使能：开");
        }
    }
}

void DataSetting::on_Speed_Cylinder4_Enable_clicked()//风速气缸4使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_Cylinder4Enable_flag == 1)
        {
            Speed_Cylinder4Enable_flag = 0;
            ui->Speed_Cylinder4_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速气缸4使能，PLC地址:602400,使能：关");
        }
        else
        {
            Speed_Cylinder4Enable_flag = 1;
            ui->Speed_Cylinder4_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速气缸4使能，PLC地址:602400,使能：开");
        }
    }
}

void DataSetting::on_Speed_Cylinder5_Enable_clicked()//风速气缸5使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_Cylinder5Enable_flag == 1)
        {
            Speed_Cylinder5Enable_flag = 0;
            ui->Speed_Cylinder5_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速气缸5使能，PLC地址:602401,使能：关");
        }
        else
        {
            Speed_Cylinder5Enable_flag = 1;
            ui->Speed_Cylinder5_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速气缸5使能，PLC地址:602401,使能：开");
        }
    }
}

void DataSetting::on_Speed_Cylinder6_Enable_clicked()//风速气缸6使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_Cylinder1Enable_flag == 1)
        {
            Speed_Cylinder6Enable_flag = 0;
            ui->Speed_Cylinder6_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速气缸6使能，PLC地址:602402,使能：关");
        }
        else
        {
            Speed_Cylinder6Enable_flag = 1;
            ui->Speed_Cylinder6_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速气缸6使能，PLC地址:602402,使能：开");
        }
    }
}

void DataSetting::on_Speed_Cylinder7_Enable_clicked()//风速气缸7使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_Cylinder7Enable_flag == 1)
        {
            Speed_Cylinder7Enable_flag = 0;
            ui->Speed_Cylinder7_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速气缸7使能，PLC地址:602403,使能：关");
        }
        else
        {
            Speed_Cylinder7Enable_flag = 1;
            ui->Speed_Cylinder7_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速气缸7使能，PLC地址:602403,使能：开");
        }
    }
}

void DataSetting::on_Speed_Cylinder8_Enable_clicked()//风速气缸8使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_Cylinder8Enable_flag == 1)
        {
            Speed_Cylinder8Enable_flag = 0;
            ui->Speed_Cylinder8_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速气缸8使能，PLC地址:602404,使能：关");
        }
        else
        {
            Speed_Cylinder8Enable_flag = 1;
            ui->Speed_Cylinder8_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速气缸8使能，PLC地址:602404,使能：开");
        }
    }
}



void DataSetting::on_Speed_Enable_clicked()//风速总使能
{
    if(Read_Write_Mode == 1)
    {
        if(SpeedEnable_flag == 1)
        {
            SpeedEnable_flag = 0;
            ui->Speed_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速总使能，PLC地址:602408,使能：关");
        }
        else
        {
            SpeedEnable_flag = 1;
            ui->Speed_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速总使能，PLC地址:602408,使能：开");
        }
    }
}

void DataSetting::on_Speed1_Enable_clicked()//风速1使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_EnableWidgets[0]==1)
        {
            Speed_EnableWidgets[0] = 0;
            ui->Speed1_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速1使能，PLC地址:602409,使能：关");

        }
        else
        {
            Speed_EnableWidgets[0] = 1;
            ui->Speed1_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速1使能，PLC地址:602409,使能：开");
        }
    }
}

void DataSetting::on_Speed2_Enable_clicked()//风速2使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_EnableWidgets[1] == 1)
        {
            Speed_EnableWidgets[1] = 0;
            ui->Speed2_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速2使能，PLC地址:602410,使能：关");
        }
        else
        {
            Speed_EnableWidgets[1] = 1;
            ui->Speed2_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速2使能，PLC地址:602410,使能：开");
        }
    }
}

void DataSetting::on_Speed3_Enable_clicked()//风速3使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_EnableWidgets[2] == 1)
        {
            Speed_EnableWidgets[2] = 0;
            ui->Speed3_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速3使能，PLC地址:602411,使能：关");
        }
        else
        {
            Speed_EnableWidgets[2] = 1;
            ui->Speed3_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速3使能，PLC地址:602411,使能：开");
        }
    }
}

void DataSetting::on_Speed4_Enable_clicked()//风速4使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_EnableWidgets[3] == 1)
        {
            Speed_EnableWidgets[3] = 0;
            ui->Speed4_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速4使能，PLC地址:602412,使能：关");
            ;
        }
        else
        {
            Speed_EnableWidgets[3] = 1;
            ui->Speed4_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速4使能，PLC地址:602412,使能：开");

        }
    }
}

void DataSetting::on_Speed5_Enable_clicked()//风速5使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_EnableWidgets[4] == 1)
        {
            Speed_EnableWidgets[4] = 0;
            ui->Speed5_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速5使能，PLC地址:602413,使能：关");

        }
        else
        {
            Speed_EnableWidgets[4] = 1;
            ui->Speed5_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速5使能，PLC地址:602413,使能：开");

        }
    }
}

void DataSetting::on_Speed6_Enable_clicked()//风速6使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_EnableWidgets[5] == 1)
        {
            Speed_EnableWidgets[5] = 0;
            ui->Speed6_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速6使能，PLC地址:602414,使能：关");

        }
        else
        {
            Speed_EnableWidgets[5] = 1;
            ui->Speed6_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速6使能，PLC地址:602414,使能：开");
        }
    }
}

void DataSetting::on_Speed7_Enable_clicked()//风速7使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_EnableWidgets[6] == 1)
        {
            Speed_EnableWidgets[6] = 0;
            ui->Speed7_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速7使能，PLC地址:602415,使能：关");
        }
        else
        {
            Speed_EnableWidgets[6] = 1;
            ui->Speed7_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速7使能，PLC地址:602415,使能：开");
        }
    }
}

void DataSetting::on_Speed8_Enable_clicked()//风速8使能
{
    if(Read_Write_Mode == 1)
    {
        if(Speed_EnableWidgets[7] == 1)
        {
            Speed_EnableWidgets[7] = 0;
            ui->Speed8_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速8使能，PLC地址:602416,使能：关");
        }
        else
        {
            Speed_EnableWidgets[7] = 1;
            ui->Speed8_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速8使能，PLC地址:602416,使能：开");
        }
    }
}



void DataSetting::on_Speed_Mode1_Enable_clicked()//风速模式1使能
{
    if(Read_Write_Mode == 1)
    {
        if(SpeedMode1Enable_flag == 1)
        {
            SpeedMode1Enable_flag = 0;
            ui->Speed_Mode1_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速模式1使能，PLC地址:602423,使能：关");

        }
        else
        {
            SpeedMode1Enable_flag = 1;
            ui->Speed_Mode1_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速模式1使能，PLC地址:602423,使能：开");
        }
    }
}

void DataSetting::on_Speed_Mode2_Enable_clicked()//风速模式2使能
{
    if(Read_Write_Mode == 1)
    {
        if(SpeedMode2Enable_flag == 1)
        {
            SpeedMode2Enable_flag = 0;
            ui->Speed_Mode2_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速模式2使能，PLC地址:602424,使能：关");
        }
        else
        {
            SpeedMode2Enable_flag = 1;
            ui->Speed_Mode2_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速模式2使能，PLC地址:602424,使能：开");
        }
    }
}

void DataSetting::on_Speed_Mode3_Enable_clicked()//风速模式3使能
{
    if(Read_Write_Mode == 1)
    {
        if(SpeedMode3Enable_flag == 1)
        {
            SpeedMode3Enable_flag = 0;
            ui->Speed_Mode3_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速模式3使能，PLC地址:602425,使能：关");
        }
        else
        {
            SpeedMode3Enable_flag = 1;
            ui->Speed_Mode3_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速模式3使能，PLC地址:602425,使能：开");
        }
    }
}

void DataSetting::on_Speed_Mode4_Enable_clicked()//风速模式4使能
{
    if(Read_Write_Mode == 1)
    {
        if(SpeedMode1Enable_flag == 1)
        {
            SpeedMode4Enable_flag = 0;
            ui->Speed_Mode4_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速模式4使能，PLC地址:602426,使能：关");
        }
        else
        {
            SpeedMode4Enable_flag = 1;
            ui->Speed_Mode4_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速模式4使能，PLC地址:602426,使能：开");
        }
    }
}

void DataSetting::on_Speed_Mode5_Enable_clicked()//风速模式5使能
{
    if(Read_Write_Mode == 1)
    {
        if(SpeedMode5Enable_flag == 1)
        {
            SpeedMode5Enable_flag = 0;
            ui->Speed_Mode5_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速模式5使能，PLC地址:602427,使能：关");
        }
        else
        {
            SpeedMode5Enable_flag = 1;
            ui->Speed_Mode5_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速模式5使能，PLC地址:602427,使能：开");
        }
    }
}

void DataSetting::on_Speed_Mode6_Enable_clicked()//风速模式6使能
{
    if(Read_Write_Mode == 1)
    {
        if(SpeedMode6Enable_flag == 1)
        {
            SpeedMode6Enable_flag = 0;
            ui->Speed_Mode6_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速模式6使能，PLC地址:602428,使能：关");
        }
        else
        {
            SpeedMode6Enable_flag = 1;
            ui->Speed_Mode6_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速模式6使能，PLC地址:602428,使能：开");
        }
    }
}

void DataSetting::on_Speed_Mode7_Enable_clicked()//风速模式7使能
{
    if(Read_Write_Mode == 1)
    {
        if(SpeedMode7Enable_flag == 1)
        {
            SpeedMode7Enable_flag = 0;
            ui->Speed_Mode7_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速模式7使能，PLC地址:602429,使能：关");
        }
        else
        {
            SpeedMode7Enable_flag = 1;
            ui->Speed_Mode7_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速模式7使能，PLC地址:602429,使能：开");
        }
    }
}

void DataSetting::on_Speed_Mode8_Enable_clicked()//风速模式8使能
{
    if(Read_Write_Mode == 1)
    {
        if(SpeedMode8Enable_flag == 1)
        {
            SpeedMode8Enable_flag = 0;
            ui->Speed_Mode8_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改风速模式8使能，PLC地址:602429,使能：关");
        }
        else
        {
            SpeedMode8Enable_flag = 1;
            ui->Speed_Mode8_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改风速模式8使能，PLC地址:602429,使能：开");
        }
    }
}

void DataSetting::on_Expansionvalves_Enable_clicked()//电子膨胀阀使能
{
    if(Read_Write_Mode == 1)
    {
        if(Expansionvalves_Enable_flag == 1)
        {
            Expansionvalves_Enable_flag = 0;
            ui->Expansionvalves_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改电子膨胀阀使能，PLC地址:602194,使能：关");
        }
        else
        {
            Expansionvalves_Enable_flag = 1;
            ui->Expansionvalves_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改电子膨胀阀使能，PLC地址:602194,使能：开");
        }
    }
}
//-------------------------------------PTC---------------------------------------------

void DataSetting::on_PTC_Enable_clicked()//PTC使能
{
    if(Read_Write_Mode == 1)
    {
        if(PTC_Enable_flag == 1)
        {
            PTC_Enable_flag = 0;
            ui->PTC_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改PTC使能，PLC地址:602233,使能：关");
        }
        else
        {
            PTC_Enable_flag = 1;
            ui->PTC_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改PTC使能，PLC地址:602233,使能：开");
        }
    }
}

void DataSetting::on_PTC_Btl_currentIndexChanged(int index)//PTC波特率
{
    if(Read_Write_Mode == 1)
    {
        slot_SaveChangeData("进入修改PTC波特率，PLC地址:602227,值："+QString::number(index));
    }
}

void DataSetting::on_PTC_Lb_currentIndexChanged(int index)//PTC滤波
{
    if(Read_Write_Mode == 1)
    {
        slot_SaveChangeData("进入修改PTC滤波模式，PLC地址:602228,值："+QString::number(index));
    }
}

void DataSetting::on_PM25_Enable_clicked()//PM2.5检测使能
{
    if(Read_Write_Mode == 1)
    {
        if(PM25_Enable_flag==0)
        {
            PM25_Enable_flag =1;
            ui->PM25_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改PM2.5检测使能，PLC地址:602695,使能：开");
        }
        else
        {
            PM25_Enable_flag =0;
            ui->PM25_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改PM2.5检测使能，PLC地址:602695,使能：关");
        }
    }
}

void DataSetting::on_PM25_Ver_Judge_clicked()
{
    if(Read_Write_Mode == 1)
    {
        if(PM25_Ver_Judge_flag==0)
        {
            PM25_Ver_Judge_flag =1;
            ui->PM25_Ver_Judge->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改PM2.5版本判断使能，PLC地址:602822,使能：开");
        }
        else
        {
            PM25_Ver_Judge_flag =0;
            ui->PM25_Ver_Judge->setStyleSheet("");
            slot_SaveChangeData("进入修改PM2.5版本判断使能，PLC地址:602822,使能：关");
        }
    }
}

//-------------------------------------AQS---------------------------------------------

void DataSetting::on_AQS_Enable_clicked()//AQS使能
{
    if(Read_Write_Mode == 1)
    {
        if(AQS_Enable_flag==0)
        {
            AQS_Enable_flag =1;
            ui->AQS_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改AQS检测使能，PLC地址:602704,使能：开");
        }
        else
        {
            AQS_Enable_flag =0;
            ui->AQS_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改AQS检测使能，PLC地址:602704,使能：关");
        }
    }
}


void DataSetting::on_AQS_Ver_Judge_clicked()
{
    if(Read_Write_Mode == 1)
    {
        if(AQS_Ver_Judge_flag==0)
        {
            AQS_Ver_Judge_flag =1;
            ui->AQS_Ver_Judge->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改AQS版本判断使能，PLC地址:602823,使能：开");
        }
        else
        {
            AQS_Ver_Judge_flag =0;
            ui->AQS_Ver_Judge->setStyleSheet("");
            slot_SaveChangeData("进入修改AQS版本判断使能，PLC地址:602823,使能：关");

        }
    }
}



void DataSetting::on_FLZ_Enable_clicked()//负离子使能
{
    if(Read_Write_Mode == 1)
    {
        if(FLZ_Enable_flag==0)
        {
            FLZ_Enable_flag =1;
            ui->FLZ_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改负离子检测使能，PLC地址:602684,使能：开");
        }
        else
        {
            FLZ_Enable_flag =0;
            ui->FLZ_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改负离子检测使能，PLC地址:602684,使能：关");
        }
    }
}

void DataSetting::on_FLZ_A_Enable_clicked()//负离子电压使能
{
    if(Read_Write_Mode == 1)
    {
        if(FLZ_A_Enable_flag==0)
        {
            FLZ_A_Enable_flag =1;
            ui->FLZ_A_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改负离子电压使能，PLC地址:602685,使能：开");
        }
        else
        {
            FLZ_A_Enable_flag =0;
            ui->FLZ_A_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改负离子电压使能，PLC地址:602685,使能：关");
        }
    }
}




void DataSetting::on_Noises_Enable_clicked()//噪音使能
{
    if(Read_Write_Mode == 1)
    {
        if(Noises_Enable_flag==0)
        {
            Noises_Enable_flag =1;
            ui->Noises_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改噪音检测使能，PLC地址:602678,使能：开");
        }
        else
        {
            Noises_Enable_flag =0;
            ui->Noises_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改噪音检测使能，PLC地址:602678,使能：关");
        }
    }
}


void DataSetting::on_Res_Enable_clicked()//电阻总使能
{
    if(Read_Write_Mode == 1)
    {
        if(ResEnable_flag==0)
        {
            ResEnable_flag =1;
            ui->Res_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改电阻总检测使能，PLC地址:602235,使能：开");
        }
        else
        {
            ResEnable_flag =0;
            ui->Res_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改电阻总检测使能，PLC地址:602235,使能：关");
        }
    }
}
void DataSetting::on_ResSurroundings_Enable_clicked()//对比检测使能
{
    if(Read_Write_Mode == 1)
    {
        if(ResSurroundingsEnable_flag==0)
        {
            ResSurroundingsEnable_flag =1;
            ui->ResSurroundings_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改对比检测使能，PLC地址:602242,使能：开");
        }
        else
        {
            ResSurroundingsEnable_flag =0;
            ui->ResSurroundings_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改对比检测使能，PLC地址:602242,使能：关");
        }
    }
}
void DataSetting::on_Res1_Enable_clicked()//温敏1使能
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[0]==0)//Res1Enable_flag==0
        {

            Res_EnableWidgets[0]=1;//Res1Enable_flag =1;
            ui->Res1_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏1使能，PLC地址:602236,使能：开");
        }
        else
        {
            Res_EnableWidgets[0]=0;//Res1Enable_flag =0;
            ui->Res1_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏1使能，PLC地址:602236,使能：关");
        }
    }
}
void DataSetting::on_Res2_Enable_clicked()//温敏2使能
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[1]==0)//Res2Enable_flag==0
        {
            Res_EnableWidgets[1]=1;//Res2Enable_flag =1;
            ui->Res2_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏2使能，PLC地址:602237,使能：开");
        }
        else
        {
            Res_EnableWidgets[1]=0;//Res2Enable_flag =0;
            ui->Res2_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏2使能，PLC地址:602237,使能：关");

        }
    }
}
void DataSetting::on_Res3_Enable_clicked()//温敏3使能
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[2]==0)
        {
            Res_EnableWidgets[2] =1;
            ui->Res3_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏3使能，PLC地址:602238,使能：开");
        }
        else
        {
            Res_EnableWidgets[2] =0;
            ui->Res3_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏3使能，PLC地址:602238,使能：关");
        }
    }
}
void DataSetting::on_Res4_Enable_clicked()//温敏4使能
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[3]==0)
        {
            Res_EnableWidgets[3] =1;
            ui->Res4_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏4使能，PLC地址:602239,使能：开");
        }
        else
        {
            Res_EnableWidgets[3] =0;
            ui->Res4_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏4使能，PLC地址:602239,使能：关");
        }

    }
}
void DataSetting::on_Res5_Enable_clicked()//温敏5使能
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[4]==0)
        {
            Res_EnableWidgets[4] =1;
            ui->Res5_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏5使能，PLC地址:602240,使能：开");
        }
        else
        {
            Res_EnableWidgets[4] =0;
            ui->Res5_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏5使能，PLC地址:602240,使能：关");
        }
    }
}
void DataSetting::on_Res6_Enable_clicked()//温敏6使能
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[5]==0)
        {
            Res_EnableWidgets[5] =1;
            ui->Res6_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏6使能，PLC地址:602241,使能：开");
        }
        else
        {
            Res_EnableWidgets[5] =0;
            ui->Res6_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏6使能，PLC地址:602241,使能：关");
        }
    }
}
void DataSetting::on_Res7_Enable_clicked()//温敏7使能
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[6]==0)
        {
            Res_EnableWidgets[6] =1;
            ui->Res7_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏7使能，PLC地址:602242,使能：开");
        }
        else
        {
            Res_EnableWidgets[6] =0;
            ui->Res7_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏7使能，PLC地址:602242,使能：关");
        }
    }
}
void DataSetting::on_Res8_Enable_clicked()//温敏8使能
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[7]==0)
        {
            Res_EnableWidgets[7] =1;
            ui->Res8_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏8使能，PLC地址:602243,使能：开");
        }
        else
        {
            Res_EnableWidgets[7] =0;
            ui->Res8_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏8使能，PLC地址:602243,使能：关");
        }
    }
}
void DataSetting::on_Res9_Enable_clicked()//温敏9使能
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[8]==0)
        {
            Res_EnableWidgets[8] =1;
            ui->Res9_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏9使能，PLC地址:602244,使能：开");
        }
        else
        {
            Res_EnableWidgets[8] =0;
            ui->Res9_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏9使能，PLC地址:602244,使能：关");
        }
    }
}
void DataSetting::on_Res10_Enable_clicked()//温敏10使能
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[9]==0)
        {
            Res_EnableWidgets[9] =1;
            ui->Res10_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏10使能，PLC地址:602245,使能：开");
        }
        else
        {
            Res_EnableWidgets[9] =0;
            ui->Res10_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏10使能，PLC地址:602245,使能：关");
        }
    }
}


void DataSetting::on_Res11_Enable_clicked()
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[10]==0)
        {
            Res_EnableWidgets[10] =1;
            ui->Res11_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏10使能，PLC地址:602245,使能：开");
        }
        else
        {
            Res_EnableWidgets[10] =0;
            ui->Res11_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏10使能，PLC地址:602245,使能：关");
        }
    }
}


void DataSetting::on_Res12_Enable_clicked()
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[11]==0)
        {
            Res_EnableWidgets[11] =1;
            ui->Res12_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏10使能，PLC地址:602245,使能：开");
        }
        else
        {
            Res_EnableWidgets[11] =0;
            ui->Res12_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏10使能，PLC地址:602245,使能：关");
        }
    }
}


void DataSetting::on_Res13_Enable_clicked()//环境温敏
{
    if(Read_Write_Mode == 1)
    {
        if(Res_EnableWidgets[12]==0)
        {
            Res_EnableWidgets[12] =1;
            ui->Res13_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改温敏10使能，PLC地址:602245,使能：开");
        }
        else
        {
            Res_EnableWidgets[12] =0;
            ui->Res13_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改温敏10使能，PLC地址:602245,使能：关");
        }
    }
}


void DataSetting::on_LIN_WriteID_Enable_clicked()//LIN电机写ID功能
{
    if(Read_Write_Mode == 1)
    {
        if(LIN_WriteID_Enable_flag == 1)
        {
            LIN_WriteID_Enable_flag = 0;
            ui->LIN_WriteID_Enable->setStyleSheet("");
            slot_SaveChangeData("进入修改LIN电机写ID功能，PLC地址:602731,使能：关");
        }
        else
        {
            LIN_WriteID_Enable_flag = 1;
            ui->LIN_WriteID_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
            slot_SaveChangeData("进入修改LIN电机写ID功能，PLC地址:602731,使能：开");
        }
    }
}

DataSetting::~DataSetting()
{
    delete ui;
}



void DataSetting::on_NextPage_clicked()
{
    int index = ui->tabwidget->currentIndex();

    if(index<ui->tabwidget->count())
    {
        //    qDebug()<<"当前Tab数量"<<ui->tabWidget->count();
        ui->tabwidget->setCurrentIndex(index+1);
    }
}


void DataSetting::on_BackPage_clicked()
{
    int index = ui->tabwidget->currentIndex();
    if(index<ui->tabwidget->count())
    {
        //    qDebug()<<"当前Tab数量"<<ui->tabWidget->count();
        ui->tabwidget->setCurrentIndex(index-1);
    }
    qDebug()<<"当前Tab数量"<<ui->tabwidget->count();

}

void DataSetting::closeEvent(QCloseEvent *e)
{
    emit Sign_Current_interface_flag(2);

    e->accept();
}

void DataSetting::on_SaveData_clicked()
{
    auto temp = QMessageBox::information(this,"提示","是否保存参数",QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {

        QDateTime time = QDateTime::currentDateTime();
        slot_SaveChangeData("开始存储"+time.toString());
        QString PD = "PD"+ui->DataSeting_PD->currentText();
        //    //----------------------LIN电机------------------------------
        for (int i =1;i<13;i++ )
        {
            if(i<13)
            {
                if(LIN_Main.at(i-1)->LIN_Enable_flag == 1)
                {
                    ini_file().Set_Control(PD+"/LIN1_"+QString::number(i)+"_Enable",QString::number(1));
                }
                else
                {
                    ini_file().Set_Control(PD+"/LIN1_"+QString::number(i)+"_Enable",QString::number(0));
                }
                ini_file().Set_Control(PD+"/LIN1_"+QString::number(i)+"_Name",LIN_Main.at(i-1)->ui->Set_LIN_Name->text());
            }
        }
        //    //----------------------伺服电机------------------------------
        for(int i = 1;i<13;i++)
        {
            //电机使能 使能:1 不使能:0
            if(Motor_Main.at(i-1)->Motor_Enable_flag==1)
            {
                ini_file().Set_Control(PD+"/Motor"+QString::number(i)+"_Enable",QString::number(1));
            }
            else
            {
                ini_file().Set_Control(PD+"/Motor"+QString::number(i)+"_Enable",QString::number(0));
            }
            ini_file().Set_Control(PD+"/Motor"+QString::number(i)+"_Name",Motor_Main.at(i-1)->ui->Set_Motor_Name->text());
        }
        QList<QLineEdit *> Res_container;
        Res_container.append(ui->Res1_Name);Res_container.append(ui->Res2_Name);Res_container.append(ui->Res3_Name);Res_container.append(ui->Res4_Name);
        Res_container.append(ui->Res5_Name);Res_container.append(ui->Res6_Name);Res_container.append(ui->Res7_Name);Res_container.append(ui->Res8_Name);
        Res_container.append(ui->Res9_Name);Res_container.append(ui->Res10_Name);
        for(int i = 1;i<11;i++)
        {
            ini_file().Set_Control(PD+"/Res"+QString::number(i)+"_Name",Res_container.at(i-1)->text());
        }
        QList<QLineEdit *> Speed_container;
        Speed_container.append(ui->Speed1_Name);Speed_container.append(ui->Speed2_Name);Speed_container.append(ui->Speed3_Name);Speed_container.append(ui->Speed4_Name);
        Speed_container.append(ui->Speed5_Name);Speed_container.append(ui->Speed6_Name);Speed_container.append(ui->Speed7_Name);Speed_container.append(ui->Speed8_Name);

        for(int i = 1;i<9;i++)
        {
            ini_file().Set_Control(PD+"/Speed"+QString::number(i)+"_Name",Speed_container.at(i-1)->text());
        }
        slot_SaveChangeData("结束存储"+time.toString());
    }
    else
    {
    }
}

void DataSetting::on_pushButton_clicked()
{
    //400个数据7秒钟
    //    QString path = QApplication::applicationDirPath() + "/System/System.ini";
    //    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    //    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    //    QDateTime time = QDateTime::currentDateTime();
    //    qDebug()<<"开始存储"<<time;
    //    for(int i =0 ;i<400;i++)
    //    {
    //        QString str = "Motor"+QString::number(i);
    //        INI_File->setValue(str,QString::number(1));
    //        QThread::msleep(1);

    //    }
    //    time = QDateTime::currentDateTime();
    //    INI_File->destroyed();
    //        qDebug()<<"结束存储"<<time;


}

void DataSetting::on_SetMain_ReadMode_clicked()//读模式
{
    slot_SaveChangeData("进入频道配置点击读模式");
    ui->SetMain_ReadMode->setStyleSheet("background-color: rgb(0, 200, 0);");
    ui->SetMain_WriteMode->setStyleSheet("");
    emit Sign_Set_PLCReadMode();
    emit Sign_Set_Mode(0);
    ;

}

void DataSetting::on_SetMain_WriteMode_clicked()//写模式
{
    slot_SaveChangeData("进入频道配置点击写模式");

    ui->SetMain_ReadMode->setStyleSheet("");
    ui->SetMain_WriteMode->setStyleSheet("background-color: rgb(0, 200, 0);");
    Read_Write_Mode = 1;
    emit Sign_Set_PLCWriteMode();
    emit Sign_Set_Mode(1);
}

void DataSetting::on_DataSeting_PD_currentTextChanged(const QString &arg1)
{
    QString PD = "PD"+arg1;
    //    QList<QLineEdit *> LIN1_Name;
    //    for(int i =0;i<12;i++)
    //    {
    //        LIN1_Name.append(LIN_Main.at(i)->ui->Set_LIN_Name);
    //    }

    //    for (int i = 1;i<13 ; i++)
    //    {
    //        LIN1_Name.at(i-1)->setText(ini_file().Get_Control(PD+"/LIN1_"+QString::number(i)+"_Name"));
    //    }

    //    QList<QLineEdit *> Motor_Name;
    //    for(int i =0;i<12;i++)
    //    {
    //        Motor_Name.append(Motor_Main.at(i)->ui->Set_Motor_Name);
    //    }
    //    ui->Speed1_Name->setText(ini_file().Get_Control(PD+"/Speed1"+"_Name"));ui->Speed2_Name->setText(ini_file().Get_Control(PD+"/Speed2"+"_Name"));
    //    ui->Speed3_Name->setText(ini_file().Get_Control(PD+"/Speed3"+"_Name"));ui->Speed4_Name->setText(ini_file().Get_Control(PD+"/Speed4"+"_Name"));
    //    ui->Speed5_Name->setText(ini_file().Get_Control(PD+"/Speed5"+"_Name"));ui->Speed6_Name->setText(ini_file().Get_Control(PD+"/Speed6"+"_Name"));
    //    ui->Speed7_Name->setText(ini_file().Get_Control(PD+"/Speed7"+"_Name"));ui->Speed8_Name->setText(ini_file().Get_Control(PD+"/Speed8"+"_Name"));

    //    ui->Res1_Name->setText(ini_file().Get_Control(PD+"/Res1"+"_Name"));ui->Res2_Name->setText(ini_file().Get_Control(PD+"/Res2"+"_Name"));
    //    ui->Res3_Name->setText(ini_file().Get_Control(PD+"/Res3"+"_Name"));ui->Res4_Name->setText(ini_file().Get_Control(PD+"/Res4"+"_Name"));
    //    ui->Res5_Name->setText(ini_file().Get_Control(PD+"/Res5"+"_Name"));ui->Res6_Name->setText(ini_file().Get_Control(PD+"/Res6"+"_Name"));
    //    ui->Res7_Name->setText(ini_file().Get_Control(PD+"/Res7"+"_Name"));ui->Res8_Name->setText(ini_file().Get_Control(PD+"/Res8"+"_Name"));
    //    ui->Res9_Name->setText(ini_file().Get_Control(PD+"/Res9"+"_Name"));ui->Res10_Name->setText(ini_file().Get_Control(PD+"/Res10"+"_Name"));


    QString path = QApplication::applicationDirPath() + "/HVAC/PD_HVACMode.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    ui->HVAC_Mode->setText(INI_File->value(PD+"_HVAC_Name").toString());

    Read_inifile();
    INI_File->destroyed();
}


void DataSetting::on_ComboardNum_textChanged(const QString &arg1)
{
    if(arg1.toInt()>0&&arg1.toInt()<4)
    {
        if(arg1.toInt()==1)
        {
            ui->COM1->show();
            ui->COM2->hide();
            ui->COM3->hide();
        }
        else if(arg1.toInt()==2)
        {
            ui->COM1->show();
            ui->COM2->show();
            ui->COM3->hide();
        }
        else if(arg1.toInt()==3)
        {
            ui->COM1->show();
            ui->COM2->show();
            ui->COM3->show();
        }
    }
}

void DataSetting::on_Serial_Num_currentTextChanged(const QString &arg1)
{
    if(arg1=="485扩展")
    {
        ui->Position1->setText("位置9");
        ui->Position2->setText("位置10");
        ui->Position3->setText("位置11");
        ui->Position4->setText("位置12");
        ui->Position5->setText("位置13");
        ui->Position6->setText("位置14");
        ui->Position7->setText("位置15");
        ui->Position8->setText("位置16");
    }
    else
    {
        ui->Position1->setText("位置1");
        ui->Position2->setText("位置2");
        ui->Position3->setText("位置3");
        ui->Position4->setText("位置4");
        ui->Position5->setText("位置5");
        ui->Position6->setText("位置6");
        ui->Position7->setText("位置7");
        ui->Position8->setText("位置8");
    }
}




void DataSetting::on_Start_Connect_clicked()//开始链接
{
    // 获取所有参数
    QString portName = ui->Serial_Number->currentText();
    qint32 baudRate = ui->Baud_rate->value();
    // 发出连接请求信号
    emit connectRequested(portName, baudRate, QSerialPort::Data8, QSerialPort::NoParity, QSerialPort::OneStop);
}

void DataSetting::on_Start_Connect_2_clicked()
{
    QString portName = ui->Serial_Number2->currentText();
    qint32 baudRate = ui->Baud_rate_2->value();
    // 发出连接请求信号
    emit connectRequested(portName, baudRate, QSerialPort::Data8, QSerialPort::NoParity, QSerialPort::OneStop);
}


void DataSetting::on_Start_Connect_3_clicked()
{
    QString portName = ui->Serial_Number3->currentText();
    qint32 baudRate = ui->Baud_rate_3->value();
    // 发出连接请求信号
    emit connectRequested(portName, baudRate, QSerialPort::Data8, QSerialPort::NoParity, QSerialPort::OneStop);
}





//--------------------------------UI界面存数组----------------------------
void DataSetting::UI_init()
{


    //-----------------------------鼓风机------------------------------
    Blower_StepsWidgets = {
        ui->Blower_Steps_1,ui->Blower_Steps_2,ui->Blower_Steps_3,
        ui->Blower_Steps_4,ui->Blower_Steps_5,ui->Blower_Steps_6,
        ui->Blower_Steps_7,ui->Blower_Steps_8,ui->Blower_Steps_9
    };//鼓风机运行顺序

    VBlowerPosNameWidgets = {
        ui->Blower_Voltage_Name_POS_1,ui->Blower_Voltage_Name_POS_2,ui->Blower_Voltage_Name_POS_3,
        ui->Blower_Voltage_Name_POS_4,ui->Blower_Voltage_Name_POS_5,ui->Blower_Voltage_Name_POS_6,
        ui->Blower_Voltage_Name_POS_7,ui->Blower_Voltage_Name_POS_8,ui->Blower_Voltage_Name_POS_9
    };//端电压鼓风机POS名称

    VBlowerVWidgets = {
        ui->Blower_Voltage_V_POS_1,ui->Blower_Voltage_V_POS_2,ui->Blower_Voltage_V_POS_3,
        ui->Blower_Voltage_V_POS_4,ui->Blower_Voltage_V_POS_5,ui->Blower_Voltage_V_POS_6,
        ui->Blower_Voltage_V_POS_7,ui->Blower_Voltage_V_POS_8,ui->Blower_Voltage_V_POS_9
    };//端电压鼓风机端电压

    VBlowerTimeWidgets= {
        ui->Blower_Voltage_Time_POS_1,ui->Blower_Voltage_Time_POS_2,ui->Blower_Voltage_Time_POS_3,
        ui->Blower_Voltage_Time_POS_4,ui->Blower_Voltage_Time_POS_5,ui->Blower_Voltage_Time_POS_6,
        ui->Blower_Voltage_Time_POS_7,ui->Blower_Voltage_Time_POS_8,ui->Blower_Voltage_Time_POS_9,
    };//端电压鼓风机检测时间

    VBlowerMaxAWidgets = {
        ui->Blower_Voltage_Max_POS_1,ui->Blower_Voltage_Max_POS_2,ui->Blower_Voltage_Max_POS_3,
        ui->Blower_Voltage_Max_POS_4,ui->Blower_Voltage_Max_POS_5,ui->Blower_Voltage_Max_POS_6,
        ui->Blower_Voltage_Max_POS_7,ui->Blower_Voltage_Max_POS_8,ui->Blower_Voltage_Max_POS_9
    };//端电压鼓风机电流上限

    VBlowerMinAWidgets = {
        ui->Blower_Voltage_Min_POS_1,ui->Blower_Voltage_Min_POS_2,ui->Blower_Voltage_Min_POS_3,
        ui->Blower_Voltage_Min_POS_4,ui->Blower_Voltage_Min_POS_5,ui->Blower_Voltage_Min_POS_6,
        ui->Blower_Voltage_Min_POS_7,ui->Blower_Voltage_Min_POS_8,ui->Blower_Voltage_Min_POS_9
    };//端电压鼓风机电流下限

    PWMBlowerPosNameWidgets = {
        ui->Blower_PWM_Name_POS_1,ui->Blower_PWM_Name_POS_2,ui->Blower_PWM_Name_POS_3,
        ui->Blower_PWM_Name_POS_4,ui->Blower_PWM_Name_POS_5,ui->Blower_PWM_Name_POS_6,
        ui->Blower_PWM_Name_POS_7,ui->Blower_PWM_Name_POS_8,ui->Blower_PWM_Name_POS_9
    };//PWM鼓风机POS名称

    PWMBlowerPWMWidgets = {
        ui->Blower_PWM_PWM_POS_1,ui->Blower_PWM_PWM_POS_2,ui->Blower_PWM_PWM_POS_3,
        ui->Blower_PWM_PWM_POS_4,ui->Blower_PWM_PWM_POS_5,ui->Blower_PWM_PWM_POS_6,
        ui->Blower_PWM_PWM_POS_7,ui->Blower_PWM_PWM_POS_8,ui->Blower_PWM_PWM_POS_9
    };//PWM鼓风机占空比

    PWMBlowerTimeWidgets= {
        ui->Blower_PWM_Time_POS_1,ui->Blower_PWM_Time_POS_2,ui->Blower_PWM_Time_POS_3,
        ui->Blower_PWM_Time_POS_4,ui->Blower_PWM_Time_POS_5,ui->Blower_PWM_Time_POS_6,
        ui->Blower_PWM_Time_POS_7,ui->Blower_PWM_Time_POS_8,ui->Blower_PWM_Time_POS_9,
    };//PWM鼓风机检测时间

    PWMBlowerMaxAWidgets = {
        ui->Blower_PWM_Max_POS_1,ui->Blower_PWM_Max_POS_2,ui->Blower_PWM_Max_POS_3,
        ui->Blower_PWM_Max_POS_4,ui->Blower_PWM_Max_POS_5,ui->Blower_PWM_Max_POS_6,
        ui->Blower_PWM_Max_POS_7,ui->Blower_PWM_Max_POS_8,ui->Blower_PWM_Max_POS_9
    };//PWM鼓风机电流上限

    PWMBlowerMinAWidgets = {
        ui->Blower_PWM_Min_POS_1,ui->Blower_PWM_Min_POS_2,ui->Blower_PWM_Min_POS_3,
        ui->Blower_PWM_Min_POS_4,ui->Blower_PWM_Min_POS_5,ui->Blower_PWM_Min_POS_6,
        ui->Blower_PWM_Min_POS_7,ui->Blower_PWM_Min_POS_8,ui->Blower_PWM_Min_POS_9
    };//PWM鼓风机电流下限

    LINBlowerPosNameWidgets = {
        ui->Blower_LIN_Name_POS_1,ui->Blower_LIN_Name_POS_2,ui->Blower_LIN_Name_POS_3,
        ui->Blower_LIN_Name_POS_4,ui->Blower_LIN_Name_POS_5,ui->Blower_LIN_Name_POS_6,
        ui->Blower_LIN_Name_POS_7,ui->Blower_LIN_Name_POS_8,ui->Blower_LIN_Name_POS_9
    };//LIN鼓风机POS名称

    LINBlowerLINWidgets = {
        ui->Blower_LIN_RPM_POS_1,ui->Blower_LIN_RPM_POS_2,ui->Blower_LIN_RPM_POS_3,
        ui->Blower_LIN_RPM_POS_4,ui->Blower_LIN_RPM_POS_5,ui->Blower_LIN_RPM_POS_6,
        ui->Blower_LIN_RPM_POS_7,ui->Blower_LIN_RPM_POS_8,ui->Blower_LIN_RPM_POS_9
    };//LIN鼓风机占空比

    LINBlowerTimeWidgets= {
        ui->Blower_LIN_Time_POS_1,ui->Blower_LIN_Time_POS_2,ui->Blower_LIN_Time_POS_3,
        ui->Blower_LIN_Time_POS_4,ui->Blower_LIN_Time_POS_5,ui->Blower_LIN_Time_POS_6,
        ui->Blower_LIN_Time_POS_7,ui->Blower_LIN_Time_POS_8,ui->Blower_LIN_Time_POS_9,
    };//LIN鼓风机检测时间

    LINBlowerMaxAWidgets = {
        ui->Blower_LIN_Max_POS_1,ui->Blower_LIN_Max_POS_2,ui->Blower_LIN_Max_POS_3,
        ui->Blower_LIN_Max_POS_4,ui->Blower_LIN_Max_POS_5,ui->Blower_LIN_Max_POS_6,
        ui->Blower_LIN_Max_POS_7,ui->Blower_LIN_Max_POS_8,ui->Blower_LIN_Max_POS_9
    };//LIN鼓风机电流上限

    LINBlowerMinAWidgets = {
        ui->Blower_LIN_Min_POS_1,ui->Blower_LIN_Min_POS_2,ui->Blower_LIN_Min_POS_3,
        ui->Blower_LIN_Min_POS_4,ui->Blower_LIN_Min_POS_5,ui->Blower_LIN_Min_POS_6,
        ui->Blower_LIN_Min_POS_7,ui->Blower_LIN_Min_POS_8,ui->Blower_LIN_Min_POS_9
    };//LIN鼓风机电流下限

    //-----------------------------震动,噪音---------------------------------------
    // 震动位置名称
    vibrationNameWidgets = {
        ui->Vibration_NamePOS1, ui->Vibration_NamePOS2, ui->Vibration_NamePOS3,
        ui->Vibration_NamePOS4, ui->Vibration_NamePOS5, ui->Vibration_NamePOS6,
        ui->Vibration_NamePOS7, ui->Vibration_NamePOS8, ui->Vibration_NamePOS9
    };
    // X轴震动上限
    xVibrationMaxWidgets = {
        ui->X_vibration_Max_value_POS1, ui->X_vibration_Max_value_POS2, ui->X_vibration_Max_value_POS3,
        ui->X_vibration_Max_value_POS4, ui->X_vibration_Max_value_POS5, ui->X_vibration_Max_value_POS6,
        ui->X_vibration_Max_value_POS7, ui->X_vibration_Max_value_POS8, ui->X_vibration_Max_value_POS9
    };
    // X轴震动下限
    xVibrationMinWidgets = {
        ui->X_vibration_Min_value_POS1, ui->X_vibration_Min_value_POS2, ui->X_vibration_Min_value_POS3,
        ui->X_vibration_Min_value_POS4, ui->X_vibration_Min_value_POS5, ui->X_vibration_Min_value_POS6,
        ui->X_vibration_Min_value_POS7, ui->X_vibration_Min_value_POS8, ui->X_vibration_Min_value_POS9
    };
    // Y轴震动上限
    yVibrationMaxWidgets = {
        ui->Y_vibration_Max_value_POS1, ui->Y_vibration_Max_value_POS2, ui->Y_vibration_Max_value_POS3,
        ui->Y_vibration_Max_value_POS4, ui->Y_vibration_Max_value_POS5, ui->Y_vibration_Max_value_POS6,
        ui->Y_vibration_Max_value_POS7, ui->Y_vibration_Max_value_POS8, ui->Y_vibration_Max_value_POS9
    };
    // Y轴震动下限
    yVibrationMinWidgets = {
        ui->Y_vibration_Min_value_POS1, ui->Y_vibration_Min_value_POS2, ui->Y_vibration_Min_value_POS3,
        ui->Y_vibration_Min_value_POS4, ui->Y_vibration_Min_value_POS5, ui->Y_vibration_Min_value_POS6,
        ui->Y_vibration_Min_value_POS7, ui->Y_vibration_Min_value_POS8, ui->Y_vibration_Min_value_POS9
    };
    // Z轴震动上限
    zVibrationMaxWidgets = {
        ui->Z_vibration_Max_value_POS1, ui->Z_vibration_Max_value_POS2, ui->Z_vibration_Max_value_POS3,
        ui->Z_vibration_Max_value_POS4, ui->Z_vibration_Max_value_POS5, ui->Z_vibration_Max_value_POS6,
        ui->Z_vibration_Max_value_POS7, ui->Z_vibration_Max_value_POS8, ui->Z_vibration_Max_value_POS9
    };
    // Z轴震动下限
    zVibrationMinWidgets = {
        ui->Z_vibration_Min_value_POS1, ui->Z_vibration_Min_value_POS2, ui->Z_vibration_Min_value_POS3,
        ui->Z_vibration_Min_value_POS4, ui->Z_vibration_Min_value_POS5, ui->Z_vibration_Min_value_POS6,
        ui->Z_vibration_Min_value_POS7, ui->Z_vibration_Min_value_POS8, ui->Z_vibration_Min_value_POS9
    };
    // 噪音上限
    noisesMaxWidgets = {
        ui->Noises_Max_value_POS1, ui->Noises_Max_value_POS2, ui->Noises_Max_value_POS3,
        ui->Noises_Max_value_POS4, ui->Noises_Max_value_POS5, ui->Noises_Max_value_POS6,
        ui->Noises_Max_value_POS7, ui->Noises_Max_value_POS8, ui->Noises_Max_value_POS9
    };
    // 噪音下限
    noisesMinWidgets = {
        ui->Noises_Min_value_POS1, ui->Noises_Min_value_POS2, ui->Noises_Min_value_POS3,
        ui->Noises_Min_value_POS4, ui->Noises_Min_value_POS5, ui->Noises_Min_value_POS6,
        ui->Noises_Min_value_POS7, ui->Noises_Min_value_POS8, ui->Noises_Min_value_POS9
    };

    //-----------------------------电子膨胀阀---------------------------------------
    ExpansionPosNameWidgets = {
        ui->Expansionvalves_POS1, ui->Expansionvalves_POS2, ui->Expansionvalves_POS3,
        ui->Expansionvalves_POS4, ui->Expansionvalves_POS5, ui->Expansionvalves_POS6,
        ui->Expansionvalves_POS7
    };
    ExpansionStepWidgets = {
        ui->Expansionvalves_Step1,ui->Expansionvalves_Step2,ui->Expansionvalves_Step3,
        ui->Expansionvalves_Step4,ui->Expansionvalves_Step5,ui->Expansionvalves_Step6,
        ui->Expansionvalves_Step7,ui->Expansionvalves_Step8
    };
    ExpansionTimeWidgets = {
        ui->Expansionvalves_Time1,ui->Expansionvalves_Time2,ui->Expansionvalves_Time3,
        ui->Expansionvalves_Time4,ui->Expansionvalves_Time5,ui->Expansionvalves_Time6,
        ui->Expansionvalves_Time7
    };
    ExpansionValueWidgets = {
        ui->Expansionvalves_Value1,ui->Expansionvalves_Value2,ui->Expansionvalves_Value3,
        ui->Expansionvalves_Value4,ui->Expansionvalves_Value5,ui->Expansionvalves_Value6,
        ui->Expansionvalves_Value7
    };

    //---------------------电阻----------------------
    Res_EnableWidgets = {

        Res1Enable_flag,Res2Enable_flag,Res3Enable_flag,Res4Enable_flag,Res5Enable_flag,Res6Enable_flag,
        Res7Enable_flag,Res8Enable_flag,Res9Enable_flag,Res10Enable_flag,Res11Enable_flag,Res12Enable_flag,
        Res13Enable_flag

    };

    Res_EnableButtonWidgets = {
        ui->Res1_Enable,ui->Res2_Enable,ui->Res3_Enable,ui->Res4_Enable,ui->Res5_Enable,ui->Res6_Enable,
        ui->Res7_Enable,ui->Res8_Enable,ui->Res9_Enable,ui->Res10_Enable,ui->Res11_Enable,ui->Res12_Enable,
        ui->Res13_Enable
    };


    ResNameWidgets = {
        ui->Res1_Name,ui->Res2_Name,ui->Res3_Name,ui->Res4_Name,ui->Res5_Name,ui->Res6_Name,
        ui->Res7_Name,ui->Res8_Name,ui->Res9_Name,ui->Res10_Name,ui->Res11_Name,ui->Res12_Name,
        ui->Res13_Name
    };
    ResTempWidgets = {
        ui->Res1_1,ui->Res2_1,ui->Res3_1,ui->Res4_1,ui->Res5_1,ui->Res6_1,
        ui->Res7_1,ui->Res8_1,ui->Res9_1,ui->Res10_1,ui->Res11_1,ui->Res12_1,ui->Res13_1
    };

    ResValueWidgets = {
        ui->Res1_2,ui->Res2_2,ui->Res3_2,ui->Res4_2,ui->Res5_2,ui->Res6_2,
        ui->Res7_2,ui->Res8_2,ui->Res9_2,ui->Res10_2,ui->Res11_2,ui->Res12_2,ui->Res13_2
    };

    ResMaterialConstantWidgets = {
        ui->Res1_3,ui->Res2_3,ui->Res3_3,ui->Res4_3,ui->Res5_3,ui->Res6_3,
        ui->Res7_3,ui->Res8_3,ui->Res9_3,ui->Res10_3,ui->Res11_3,ui->Res12_3,ui->Res13_3
    };

    ResMaxValueWidgets = {
        ui->Res1_Max_value,ui->Res2_Max_value,ui->Res3_Max_value,ui->Res4_Max_value,ui->Res5_Max_value,ui->Res6_Max_value,
        ui->Res7_Max_value,ui->Res8_Max_value,ui->Res9_Max_value,ui->Res10_Max_value,ui->Res11_Max_value,ui->Res12_Max_value
    };

    ResMinValueWidgets = {
        ui->Res1_Min_value,ui->Res2_Min_value,ui->Res3_Min_value,ui->Res4_Min_value,ui->Res5_Min_value,ui->Res6_Min_value,
        ui->Res7_Min_value,ui->Res8_Min_value,ui->Res9_Min_value,ui->Res10_Min_value,ui->Res11_Min_value,ui->Res12_Min_value
    };

    //---------------------风速----------------------

    Speed_EnableWidgets = {
        Speed1Enable_flag,Speed2Enable_flag,Speed3Enable_flag,Speed4Enable_flag,
        Speed5Enable_flag,Speed6Enable_flag,Speed7Enable_flag,Speed8Enable_flag
    };//风速使能

    Speed_EnableButtonWidgets = {
        ui->Speed1_Enable,ui->Speed2_Enable,ui->Speed3_Enable,ui->Speed4_Enable,
        ui->Speed5_Enable,ui->Speed6_Enable,ui->Speed7_Enable,ui->Speed8_Enable
    };

    SpeedNameWidgets = {
        ui->Speed1_Name,ui->Speed2_Name,ui->Speed3_Name,ui->Speed4_Name,
        ui->Speed5_Name,ui->Speed6_Name,ui->Speed7_Name,ui->Speed8_Name
    };//风速名称
    SpeedMode1MaxMinValueWidgets = {
        ui->Speed1_Mode1_Max_Value,ui->Speed1_Mode1_Min_Value,ui->Speed2_Mode1_Max_Value,ui->Speed2_Mode1_Min_Value,
        ui->Speed3_Mode1_Max_Value,ui->Speed3_Mode1_Min_Value,ui->Speed4_Mode1_Max_Value,ui->Speed4_Mode1_Min_Value,
        ui->Speed5_Mode1_Max_Value,ui->Speed5_Mode1_Min_Value,ui->Speed6_Mode1_Max_Value,ui->Speed6_Mode1_Min_Value,
        ui->Speed7_Mode1_Max_Value,ui->Speed7_Mode1_Min_Value,ui->Speed8_Mode1_Max_Value,ui->Speed8_Mode1_Min_Value
    };//风速1档上下限
    SpeedMode2MaxMinValueWidgets = {
        ui->Speed1_Mode2_Max_Value,ui->Speed1_Mode2_Min_Value,ui->Speed2_Mode2_Max_Value,ui->Speed2_Mode2_Min_Value,
        ui->Speed3_Mode2_Max_Value,ui->Speed3_Mode2_Min_Value,ui->Speed4_Mode2_Max_Value,ui->Speed4_Mode2_Min_Value,
        ui->Speed5_Mode2_Max_Value,ui->Speed5_Mode2_Min_Value,ui->Speed6_Mode2_Max_Value,ui->Speed6_Mode2_Min_Value,
        ui->Speed7_Mode2_Max_Value,ui->Speed7_Mode2_Min_Value,ui->Speed8_Mode2_Max_Value,ui->Speed8_Mode2_Min_Value
    };//风速2档上下限
    SpeedMode3MaxMinValueWidgets = {
        ui->Speed1_Mode3_Max_Value,ui->Speed1_Mode3_Min_Value,ui->Speed2_Mode3_Max_Value,ui->Speed2_Mode3_Min_Value,
        ui->Speed3_Mode3_Max_Value,ui->Speed3_Mode3_Min_Value,ui->Speed4_Mode3_Max_Value,ui->Speed4_Mode3_Min_Value,
        ui->Speed5_Mode3_Max_Value,ui->Speed5_Mode3_Min_Value,ui->Speed6_Mode3_Max_Value,ui->Speed6_Mode3_Min_Value,
        ui->Speed7_Mode3_Max_Value,ui->Speed7_Mode3_Min_Value,ui->Speed8_Mode3_Max_Value,ui->Speed8_Mode3_Min_Value
    };//风速3档上下限
    SpeedMode4MaxMinValueWidgets = {
        ui->Speed1_Mode4_Max_Value,ui->Speed1_Mode4_Min_Value,ui->Speed2_Mode4_Max_Value,ui->Speed2_Mode4_Min_Value,
        ui->Speed3_Mode4_Max_Value,ui->Speed3_Mode4_Min_Value,ui->Speed4_Mode4_Max_Value,ui->Speed4_Mode4_Min_Value,
        ui->Speed5_Mode4_Max_Value,ui->Speed5_Mode4_Min_Value,ui->Speed6_Mode4_Max_Value,ui->Speed6_Mode4_Min_Value,
        ui->Speed7_Mode4_Max_Value,ui->Speed7_Mode4_Min_Value,ui->Speed8_Mode4_Max_Value,ui->Speed8_Mode4_Min_Value
    };//风速4档上下限
    SpeedMode5MaxMinValueWidgets = {
        ui->Speed1_Mode5_Max_Value,ui->Speed1_Mode5_Min_Value,ui->Speed2_Mode5_Max_Value,ui->Speed2_Mode5_Min_Value,
        ui->Speed3_Mode5_Max_Value,ui->Speed3_Mode5_Min_Value,ui->Speed4_Mode5_Max_Value,ui->Speed4_Mode5_Min_Value,
        ui->Speed5_Mode5_Max_Value,ui->Speed5_Mode5_Min_Value,ui->Speed6_Mode5_Max_Value,ui->Speed6_Mode5_Min_Value,
        ui->Speed7_Mode5_Max_Value,ui->Speed7_Mode5_Min_Value,ui->Speed8_Mode5_Max_Value,ui->Speed8_Mode5_Min_Value
    };//风速5档上下限
    SpeedMode6MaxMinValueWidgets = {
        ui->Speed1_Mode6_Max_Value,ui->Speed1_Mode6_Min_Value,ui->Speed2_Mode6_Max_Value,ui->Speed2_Mode6_Min_Value,
        ui->Speed3_Mode6_Max_Value,ui->Speed3_Mode6_Min_Value,ui->Speed4_Mode6_Max_Value,ui->Speed4_Mode6_Min_Value,
        ui->Speed5_Mode6_Max_Value,ui->Speed5_Mode6_Min_Value,ui->Speed6_Mode6_Max_Value,ui->Speed6_Mode6_Min_Value,
        ui->Speed7_Mode6_Max_Value,ui->Speed7_Mode6_Min_Value,ui->Speed8_Mode6_Max_Value,ui->Speed8_Mode6_Min_Value
    };//风速6档上下限
    SpeedMode7MaxMinValueWidgets = {
        ui->Speed1_Mode7_Max_Value,ui->Speed1_Mode7_Min_Value,ui->Speed2_Mode7_Max_Value,ui->Speed2_Mode7_Min_Value,
        ui->Speed3_Mode7_Max_Value,ui->Speed3_Mode7_Min_Value,ui->Speed4_Mode7_Max_Value,ui->Speed4_Mode7_Min_Value,
        ui->Speed5_Mode7_Max_Value,ui->Speed5_Mode7_Min_Value,ui->Speed6_Mode7_Max_Value,ui->Speed6_Mode7_Min_Value,
        ui->Speed7_Mode7_Max_Value,ui->Speed7_Mode7_Min_Value,ui->Speed8_Mode7_Max_Value,ui->Speed8_Mode7_Min_Value
    };//风速7档上下限
    SpeedMode8MaxMinValueWidgets = {
        ui->Speed1_Mode8_Max_Value,ui->Speed1_Mode8_Min_Value,ui->Speed2_Mode8_Max_Value,ui->Speed2_Mode8_Min_Value,
        ui->Speed3_Mode8_Max_Value,ui->Speed3_Mode8_Min_Value,ui->Speed4_Mode8_Max_Value,ui->Speed4_Mode8_Min_Value,
        ui->Speed5_Mode8_Max_Value,ui->Speed5_Mode8_Min_Value,ui->Speed6_Mode8_Max_Value,ui->Speed6_Mode8_Min_Value,
        ui->Speed7_Mode8_Max_Value,ui->Speed7_Mode8_Min_Value,ui->Speed8_Mode8_Max_Value,ui->Speed8_Mode8_Min_Value
    };//风速8档上下限
    //---------------------检测顺序----------------------
    EquenceWidgets = {
        ui->M1_Equence,ui->M2_Equence,ui->M3_Equence,ui->M4_Equence,ui->M5_Equence,ui->M6_Equence,ui->M7_Equence,ui->M8_Equence,
        ui->M9_Equence,ui->M10_Equence,ui->M11_Equence,ui->M12_Equence,ui->LIN1_Equence,ui->Blower_Equence,ui->Res_Equence,ui->FLZ_Equence,
        ui->AQS_Equence,ui->PM25_Equence,ui->PTC_Equence
    };

}

void DataSetting::SaveLimitData()
{
    QMap<QString,QString> m_map; //定义一个QMap对象
    m_map.insert("序号", sqlData[0]); //向map里添加一对“键-值”
    m_map.insert("频道号", sqlData[1]); //向map里添加一对“键-值”
    m_map.insert("日期", sqlData[2]); //向map里添加一对“键-值”

    m_map.insert("LIN1_1POS1上下限", sqldataLINLimitData[0]); //向map里添加一对“键_值”
    m_map.insert("LIN1_1POS2上下限", sqldataLINLimitData[1]); //向map里添加一对“键_值”
    m_map.insert("LIN1_1POS3上下限", sqldataLINLimitData[2]); //向map里添加一对“键_值”
    m_map.insert("LIN1_1POS4上下限", sqldataLINLimitData[3]); //向map里添加一对“键_值”
    m_map.insert("LIN1_1POS5上下限", sqldataLINLimitData[4]); //向map里添加一对“键_值”
    m_map.insert("LIN1_1POS6上下限", sqldataLINLimitData[5]); //向map里添加一对“键_值”
    m_map.insert("LIN1_1POS7上下限", sqldataLINLimitData[6]); //向map里添加一对“键_值”
    m_map.insert("LIN1_1POS8上下限", sqldataLINLimitData[7]); //向map里添加一对“键_值”

    m_map.insert("LIN1_2POS1上下限", sqldataLINLimitData[8]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2POS2上下限", sqldataLINLimitData[9]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2POS3上下限", sqldataLINLimitData[10]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2POS4上下限", sqldataLINLimitData[11]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2POS5上下限", sqldataLINLimitData[12]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2POS6上下限", sqldataLINLimitData[13]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2POS7上下限", sqldataLINLimitData[14]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2POS8上下限", sqldataLINLimitData[15]); //向map里添加一对“键_值”

    m_map.insert("LIN1_3POS1上下限", sqldataLINLimitData[16]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3POS2上下限", sqldataLINLimitData[17]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3POS3上下限", sqldataLINLimitData[18]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3POS4上下限", sqldataLINLimitData[19]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3POS5上下限", sqldataLINLimitData[20]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3POS6上下限", sqldataLINLimitData[21]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3POS7上下限", sqldataLINLimitData[22]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3POS8上下限", sqldataLINLimitData[23]); //向map里添加一对“键_值”

    m_map.insert("LIN1_4POS1上下限", sqldataLINLimitData[24]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4POS2上下限", sqldataLINLimitData[25]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4POS3上下限", sqldataLINLimitData[26]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4POS4上下限", sqldataLINLimitData[27]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4POS5上下限", sqldataLINLimitData[28]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4POS6上下限", sqldataLINLimitData[29]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4POS7上下限", sqldataLINLimitData[30]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4POS8上下限", sqldataLINLimitData[31]); //向map里添加一对“键_值”

    m_map.insert("LIN1_5POS1上下限", sqldataLINLimitData[32]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5POS2上下限", sqldataLINLimitData[33]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5POS3上下限", sqldataLINLimitData[34]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5POS4上下限", sqldataLINLimitData[35]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5POS5上下限", sqldataLINLimitData[36]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5POS6上下限", sqldataLINLimitData[37]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5POS7上下限", sqldataLINLimitData[38]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5POS8上下限", sqldataLINLimitData[39]); //向map里添加一对“键_值”

    m_map.insert("LIN1_6POS1上下限", sqldataLINLimitData[40]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6POS2上下限", sqldataLINLimitData[41]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6POS3上下限", sqldataLINLimitData[42]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6POS4上下限", sqldataLINLimitData[43]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6POS5上下限", sqldataLINLimitData[44]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6POS6上下限", sqldataLINLimitData[45]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6POS7上下限", sqldataLINLimitData[46]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6POS8上下限", sqldataLINLimitData[47]); //向map里添加一对“键_值”

    m_map.insert("LIN1_7POS1上下限", sqldataLINLimitData[48]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7POS2上下限", sqldataLINLimitData[49]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7POS3上下限", sqldataLINLimitData[50]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7POS4上下限", sqldataLINLimitData[51]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7POS5上下限", sqldataLINLimitData[52]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7POS6上下限", sqldataLINLimitData[53]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7POS7上下限", sqldataLINLimitData[54]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7POS8上下限", sqldataLINLimitData[55]); //向map里添加一对“键_值”

    m_map.insert("LIN1_8POS1上下限", sqldataLINLimitData[56]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8POS2上下限", sqldataLINLimitData[57]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8POS3上下限", sqldataLINLimitData[58]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8POS4上下限", sqldataLINLimitData[59]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8POS5上下限", sqldataLINLimitData[60]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8POS6上下限", sqldataLINLimitData[61]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8POS7上下限", sqldataLINLimitData[62]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8POS8上下限", sqldataLINLimitData[63]); //向map里添加一对“键_值”

    m_map.insert("LIN1_9POS1上下限", sqldataLINLimitData[64]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9POS2上下限", sqldataLINLimitData[65]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9POS3上下限", sqldataLINLimitData[66]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9POS4上下限", sqldataLINLimitData[67]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9POS5上下限", sqldataLINLimitData[68]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9POS6上下限", sqldataLINLimitData[69]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9POS7上下限", sqldataLINLimitData[70]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9POS8上下限", sqldataLINLimitData[71]); //向map里添加一对“键_值”

    m_map.insert("LIN1_10POS1上下限", sqldataLINLimitData[72]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10POS2上下限", sqldataLINLimitData[73]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10POS3上下限", sqldataLINLimitData[74]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10POS4上下限", sqldataLINLimitData[75]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10POS5上下限", sqldataLINLimitData[76]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10POS6上下限", sqldataLINLimitData[77]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10POS7上下限", sqldataLINLimitData[78]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10POS8上下限", sqldataLINLimitData[79]); //向map里添加一对“键_值”

    m_map.insert("LIN1_11POS1上下限", sqldataLINLimitData[80]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11POS2上下限", sqldataLINLimitData[81]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11POS3上下限", sqldataLINLimitData[82]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11POS4上下限", sqldataLINLimitData[83]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11POS5上下限", sqldataLINLimitData[84]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11POS6上下限", sqldataLINLimitData[85]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11POS7上下限", sqldataLINLimitData[86]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11POS8上下限", sqldataLINLimitData[87]); //向map里添加一对“键_值”

    m_map.insert("LIN1_12POS1上下限", sqldataLINLimitData[88]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12POS2上下限", sqldataLINLimitData[89]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12POS3上下限", sqldataLINLimitData[90]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12POS4上下限", sqldataLINLimitData[91]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12POS5上下限", sqldataLINLimitData[92]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12POS6上下限", sqldataLINLimitData[93]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12POS7上下限", sqldataLINLimitData[94]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12POS8上下限", sqldataLINLimitData[95]); //向map里添加一对“键_值”

    m_map.insert("PT1POS1上下限", sqldataPTLimitData[0]); //向map里添加一对“键_值”
    m_map.insert("PT1POS2上下限", sqldataPTLimitData[1]); //向map里添加一对“键_值”
    m_map.insert("PT1POS3上下限", sqldataPTLimitData[2]); //向map里添加一对“键_值”
    m_map.insert("PT1POS4上下限", sqldataPTLimitData[3]); //向map里添加一对“键_值”
    m_map.insert("PT1POS5上下限", sqldataPTLimitData[4]); //向map里添加一对“键_值”
    m_map.insert("PT1POS6上下限", sqldataPTLimitData[5]); //向map里添加一对“键_值”
    m_map.insert("PT1POS7上下限", sqldataPTLimitData[6]); //向map里添加一对“键_值”
    m_map.insert("PT1POS8上下限", sqldataPTLimitData[7]); //向map里添加一对“键_值”

    m_map.insert("PT2POS1上下限", sqldataPTLimitData[8]); //向map里添加一对“键_值”
    m_map.insert("PT2POS2上下限", sqldataPTLimitData[9]); //向map里添加一对“键_值”
    m_map.insert("PT2POS3上下限", sqldataPTLimitData[10]); //向map里添加一对“键_值”
    m_map.insert("PT2POS4上下限", sqldataPTLimitData[11]); //向map里添加一对“键_值”
    m_map.insert("PT2POS5上下限", sqldataPTLimitData[12]); //向map里添加一对“键_值”
    m_map.insert("PT2POS6上下限", sqldataPTLimitData[13]); //向map里添加一对“键_值”
    m_map.insert("PT2POS7上下限", sqldataPTLimitData[14]); //向map里添加一对“键_值”
    m_map.insert("PT2POS8上下限", sqldataPTLimitData[15]); //向map里添加一对“键_值”

    m_map.insert("PT3POS1上下限", sqldataPTLimitData[16]); //向map里添加一对“键_值”
    m_map.insert("PT3POS2上下限", sqldataPTLimitData[17]); //向map里添加一对“键_值”
    m_map.insert("PT3POS3上下限", sqldataPTLimitData[18]); //向map里添加一对“键_值”
    m_map.insert("PT3POS4上下限", sqldataPTLimitData[19]); //向map里添加一对“键_值”
    m_map.insert("PT3POS5上下限", sqldataPTLimitData[20]); //向map里添加一对“键_值”
    m_map.insert("PT3POS6上下限", sqldataPTLimitData[21]); //向map里添加一对“键_值”
    m_map.insert("PT3POS7上下限", sqldataPTLimitData[22]); //向map里添加一对“键_值”
    m_map.insert("PT3POS8上下限", sqldataPTLimitData[23]); //向map里添加一对“键_值”

    m_map.insert("PT4POS1上下限", sqldataPTLimitData[24]); //向map里添加一对“键_值”
    m_map.insert("PT4POS2上下限", sqldataPTLimitData[25]); //向map里添加一对“键_值”
    m_map.insert("PT4POS3上下限", sqldataPTLimitData[26]); //向map里添加一对“键_值”
    m_map.insert("PT4POS4上下限", sqldataPTLimitData[27]); //向map里添加一对“键_值”
    m_map.insert("PT4POS5上下限", sqldataPTLimitData[28]); //向map里添加一对“键_值”
    m_map.insert("PT4POS6上下限", sqldataPTLimitData[29]); //向map里添加一对“键_值”
    m_map.insert("PT4POS7上下限", sqldataPTLimitData[30]); //向map里添加一对“键_值”
    m_map.insert("PT4POS8上下限", sqldataPTLimitData[31]); //向map里添加一对“键_值”

    m_map.insert("PT5POS1上下限", sqldataPTLimitData[32]); //向map里添加一对“键_值”
    m_map.insert("PT5POS2上下限", sqldataPTLimitData[33]); //向map里添加一对“键_值”
    m_map.insert("PT5POS3上下限", sqldataPTLimitData[34]); //向map里添加一对“键_值”
    m_map.insert("PT5POS4上下限", sqldataPTLimitData[35]); //向map里添加一对“键_值”
    m_map.insert("PT5POS5上下限", sqldataPTLimitData[36]); //向map里添加一对“键_值”
    m_map.insert("PT5POS6上下限", sqldataPTLimitData[37]); //向map里添加一对“键_值”
    m_map.insert("PT5POS7上下限", sqldataPTLimitData[38]); //向map里添加一对“键_值”
    m_map.insert("PT5POS8上下限", sqldataPTLimitData[39]); //向map里添加一对“键_值”

    m_map.insert("PT6POS1上下限", sqldataPTLimitData[40]); //向map里添加一对“键_值”
    m_map.insert("PT6POS2上下限", sqldataPTLimitData[41]); //向map里添加一对“键_值”
    m_map.insert("PT6POS3上下限", sqldataPTLimitData[42]); //向map里添加一对“键_值”
    m_map.insert("PT6POS4上下限", sqldataPTLimitData[43]); //向map里添加一对“键_值”
    m_map.insert("PT6POS5上下限", sqldataPTLimitData[44]); //向map里添加一对“键_值”
    m_map.insert("PT6POS6上下限", sqldataPTLimitData[45]); //向map里添加一对“键_值”
    m_map.insert("PT6POS7上下限", sqldataPTLimitData[46]); //向map里添加一对“键_值”
    m_map.insert("PT6POS8上下限", sqldataPTLimitData[47]); //向map里添加一对“键_值”

    m_map.insert("PT7POS1上下限", sqldataPTLimitData[48]); //向map里添加一对“键_值”
    m_map.insert("PT7POS2上下限", sqldataPTLimitData[49]); //向map里添加一对“键_值”
    m_map.insert("PT7POS3上下限", sqldataPTLimitData[50]); //向map里添加一对“键_值”
    m_map.insert("PT7POS4上下限", sqldataPTLimitData[51]); //向map里添加一对“键_值”
    m_map.insert("PT7POS5上下限", sqldataPTLimitData[52]); //向map里添加一对“键_值”
    m_map.insert("PT7POS6上下限", sqldataPTLimitData[53]); //向map里添加一对“键_值”
    m_map.insert("PT7POS7上下限", sqldataPTLimitData[54]); //向map里添加一对“键_值”
    m_map.insert("PT7POS8上下限", sqldataPTLimitData[55]); //向map里添加一对“键_值”

    m_map.insert("PT8POS1上下限", sqldataPTLimitData[56]); //向map里添加一对“键_值”
    m_map.insert("PT8POS2上下限", sqldataPTLimitData[57]); //向map里添加一对“键_值”
    m_map.insert("PT8POS3上下限", sqldataPTLimitData[58]); //向map里添加一对“键_值”
    m_map.insert("PT8POS4上下限", sqldataPTLimitData[59]); //向map里添加一对“键_值”
    m_map.insert("PT8POS5上下限", sqldataPTLimitData[60]); //向map里添加一对“键_值”
    m_map.insert("PT8POS6上下限", sqldataPTLimitData[61]); //向map里添加一对“键_值”
    m_map.insert("PT8POS7上下限", sqldataPTLimitData[62]); //向map里添加一对“键_值”
    m_map.insert("PT8POS8上下限", sqldataPTLimitData[63]); //向map里添加一对“键_值”

    m_map.insert("PT9POS1上下限", sqldataPTLimitData[64]); //向map里添加一对“键_值”
    m_map.insert("PT9POS2上下限", sqldataPTLimitData[65]); //向map里添加一对“键_值”
    m_map.insert("PT9POS3上下限", sqldataPTLimitData[66]); //向map里添加一对“键_值”
    m_map.insert("PT9POS4上下限", sqldataPTLimitData[67]); //向map里添加一对“键_值”
    m_map.insert("PT9POS5上下限", sqldataPTLimitData[68]); //向map里添加一对“键_值”
    m_map.insert("PT9POS6上下限", sqldataPTLimitData[69]); //向map里添加一对“键_值”
    m_map.insert("PT9POS7上下限", sqldataPTLimitData[70]); //向map里添加一对“键_值”
    m_map.insert("PT9POS8上下限", sqldataPTLimitData[71]); //向map里添加一对“键_值”

    m_map.insert("PT10POS1上下限", sqldataPTLimitData[72]); //向map里添加一对“键_值”
    m_map.insert("PT10POS2上下限", sqldataPTLimitData[73]); //向map里添加一对“键_值”
    m_map.insert("PT10POS3上下限", sqldataPTLimitData[74]); //向map里添加一对“键_值”
    m_map.insert("PT10POS4上下限", sqldataPTLimitData[75]); //向map里添加一对“键_值”
    m_map.insert("PT10POS5上下限", sqldataPTLimitData[76]); //向map里添加一对“键_值”
    m_map.insert("PT10POS6上下限", sqldataPTLimitData[77]); //向map里添加一对“键_值”
    m_map.insert("PT10POS7上下限", sqldataPTLimitData[78]); //向map里添加一对“键_值”
    m_map.insert("PT10POS8上下限", sqldataPTLimitData[79]); //向map里添加一对“键_值”

    m_map.insert("PT11POS1上下限", sqldataPTLimitData[80]); //向map里添加一对“键_值”
    m_map.insert("PT11POS2上下限", sqldataPTLimitData[81]); //向map里添加一对“键_值”
    m_map.insert("PT11POS3上下限", sqldataPTLimitData[82]); //向map里添加一对“键_值”
    m_map.insert("PT11POS4上下限", sqldataPTLimitData[83]); //向map里添加一对“键_值”
    m_map.insert("PT11POS5上下限", sqldataPTLimitData[84]); //向map里添加一对“键_值”
    m_map.insert("PT11POS6上下限", sqldataPTLimitData[85]); //向map里添加一对“键_值”
    m_map.insert("PT11POS7上下限", sqldataPTLimitData[86]); //向map里添加一对“键_值”
    m_map.insert("PT11POS8上下限", sqldataPTLimitData[87]); //向map里添加一对“键_值”

    m_map.insert("PT12POS1上下限", sqldataPTLimitData[88]); //向map里添加一对“键_值”
    m_map.insert("PT12POS2上下限", sqldataPTLimitData[89]); //向map里添加一对“键_值”
    m_map.insert("PT12POS3上下限", sqldataPTLimitData[90]); //向map里添加一对“键_值”
    m_map.insert("PT12POS4上下限", sqldataPTLimitData[91]); //向map里添加一对“键_值”
    m_map.insert("PT12POS5上下限", sqldataPTLimitData[92]); //向map里添加一对“键_值”
    m_map.insert("PT12POS6上下限", sqldataPTLimitData[93]); //向map里添加一对“键_值”
    m_map.insert("PT12POS7上下限", sqldataPTLimitData[94]); //向map里添加一对“键_值”
    m_map.insert("PT12POS8上下限", sqldataPTLimitData[95]); //向map里添加一对“键_值”

    m_map.insert("BlowerPOS1上下限", sqldataBlowerLimitData[0]); //向map里添加一对“键_值”
    m_map.insert("BlowerPOS2上下限", sqldataBlowerLimitData[1]); //向map里添加一对“键_值”
    m_map.insert("BlowerPOS3上下限", sqldataBlowerLimitData[2]); //向map里添加一对“键_值”
    m_map.insert("BlowerPOS4上下限", sqldataBlowerLimitData[3]); //向map里添加一对“键_值”
    m_map.insert("BlowerPOS5上下限", sqldataBlowerLimitData[4]); //向map里添加一对“键_值”
    m_map.insert("BlowerPOS6上下限", sqldataBlowerLimitData[5]); //向map里添加一对“键_值”
    m_map.insert("BlowerPOS7上下限", sqldataBlowerLimitData[6]); //向map里添加一对“键_值”
    m_map.insert("BlowerPOS8上下限", sqldataBlowerLimitData[7]); //向map里添加一对“键_值”

    m_map.insert("X_vibrationPOS1上下限", sqldataBlowerLimitData[8]); //向map里添加一对“键_值”
    m_map.insert("X_vibrationPOS2上下限", sqldataBlowerLimitData[9]); //向map里添加一对“键_值”
    m_map.insert("X_vibrationPOS3上下限", sqldataBlowerLimitData[10]); //向map里添加一对“键_值”
    m_map.insert("X_vibrationPOS4上下限", sqldataBlowerLimitData[11]); //向map里添加一对“键_值”
    m_map.insert("X_vibrationPOS5上下限", sqldataBlowerLimitData[12]); //向map里添加一对“键_值”
    m_map.insert("X_vibrationPOS6上下限", sqldataBlowerLimitData[13]); //向map里添加一对“键_值”
    m_map.insert("X_vibrationPOS7上下限", sqldataBlowerLimitData[14]); //向map里添加一对“键_值”
    m_map.insert("X_vibrationPOS8上下限", sqldataBlowerLimitData[15]); //向map里添加一对“键_值”

    m_map.insert("Y_vibrationPOS1上下限", sqldataBlowerLimitData[16]); //向map里添加一对“键_值”
    m_map.insert("Y_vibrationPOS2上下限", sqldataBlowerLimitData[17]); //向map里添加一对“键_值”
    m_map.insert("Y_vibrationPOS3上下限", sqldataBlowerLimitData[18]); //向map里添加一对“键_值”
    m_map.insert("Y_vibrationPOS4上下限", sqldataBlowerLimitData[19]); //向map里添加一对“键_值”
    m_map.insert("Y_vibrationPOS5上下限", sqldataBlowerLimitData[20]); //向map里添加一对“键_值”
    m_map.insert("Y_vibrationPOS6上下限", sqldataBlowerLimitData[21]); //向map里添加一对“键_值”
    m_map.insert("Y_vibrationPOS7上下限", sqldataBlowerLimitData[22]); //向map里添加一对“键_值”
    m_map.insert("Y_vibrationPOS8上下限", sqldataBlowerLimitData[23]); //向map里添加一对“键_值”

    m_map.insert("Z_vibrationPOS1上下限", sqldataBlowerLimitData[24]); //向map里添加一对“键_值”
    m_map.insert("Z_vibrationPOS2上下限", sqldataBlowerLimitData[25]); //向map里添加一对“键_值”
    m_map.insert("Z_vibrationPOS3上下限", sqldataBlowerLimitData[26]); //向map里添加一对“键_值”
    m_map.insert("Z_vibrationPOS4上下限", sqldataBlowerLimitData[27]); //向map里添加一对“键_值”
    m_map.insert("Z_vibrationPOS5上下限", sqldataBlowerLimitData[28]); //向map里添加一对“键_值”
    m_map.insert("Z_vibrationPOS6上下限", sqldataBlowerLimitData[29]); //向map里添加一对“键_值”
    m_map.insert("Z_vibrationPOS7上下限", sqldataBlowerLimitData[30]); //向map里添加一对“键_值”
    m_map.insert("Z_vibrationPOS8上下限", sqldataBlowerLimitData[31]); //向map里添加一对“键_值”

    m_map.insert("NoisesPOS1上下限", sqldataBlowerLimitData[32]); //向map里添加一对“键_值”
    m_map.insert("NoisesPOS2上下限", sqldataBlowerLimitData[33]); //向map里添加一对“键_值”
    m_map.insert("NoisesPOS3上下限", sqldataBlowerLimitData[34]); //向map里添加一对“键_值”
    m_map.insert("NoisesPOS4上下限", sqldataBlowerLimitData[35]); //向map里添加一对“键_值”
    m_map.insert("NoisesPOS5上下限", sqldataBlowerLimitData[36]); //向map里添加一对“键_值”
    m_map.insert("NoisesPOS6上下限", sqldataBlowerLimitData[37]); //向map里添加一对“键_值”
    m_map.insert("NoisesPOS7上下限", sqldataBlowerLimitData[38]); //向map里添加一对“键_值”
    m_map.insert("NoisesPOS8上下限", sqldataBlowerLimitData[39]); //向map里添加一对“键_值”

    m_map.insert("ResPOS1上下限", sqldataBlowerLimitData[40]); //向map里添加一对“键_值”
    m_map.insert("ResPOS2上下限", sqldataBlowerLimitData[41]); //向map里添加一对“键_值”
    m_map.insert("ResPOS3上下限", sqldataBlowerLimitData[42]); //向map里添加一对“键_值”
    m_map.insert("ResPOS4上下限", sqldataBlowerLimitData[43]); //向map里添加一对“键_值”
    m_map.insert("ResPOS5上下限", sqldataBlowerLimitData[44]); //向map里添加一对“键_值”
    m_map.insert("ResPOS6上下限", sqldataBlowerLimitData[45]); //向map里添加一对“键_值”
    m_map.insert("ResPOS7上下限", sqldataBlowerLimitData[46]); //向map里添加一对“键_值”
    m_map.insert("ResPOS8上下限", sqldataBlowerLimitData[47]); //向map里添加一对“键_值”

    QMap<QString,QString>::iterator it; //遍历map
    QString data1,data2;
    data1 = "";
    data2 = "";
    for ( it = m_map.begin(); it != m_map.end(); ++it )
    {
        if(data1 == "")
        {
            data1 = it.key();
        }
        else
        {
            data1 += "," + it.key();
        }

        if(data2 == "")
        {
            data2 = "'" + it.value() + "'";
        }
        else
        {
            data2 += ",'" + it.value() + "'";
        }

    }
    data2 = data2.replace("'NULL'","NULL");

    QString str = QString("insert into jianghuai_songz.datas_linecode_d(%1) values(%2)").arg(data1).arg(data2);

    //    Slots_MySql_exec(str);//发送到主控数据库追溯
}


//---------------------------------读取数据-------------------------------------
void DataSetting::Read_inifile()
{
    Read_Write_Mode = 1;
    qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    //----------------------------LIN_Motor ini-----------------------------
    QString Linpath = QApplication::applicationDirPath() + "/HVAC/HVAC_LIN_Data.ini";
    QSettings *LinINI_File = new QSettings(Linpath, QSettings::IniFormat);
    LinINI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    QString PD = "PD"+ui->DataSeting_PD->currentText();
    qDebug()<<"切换为频道"+PD;
    for (int i =1;i<13;i++ )
    {
        if(i<13)
        {
            //--------------------------------------LIN电机-------------------------------------------
            //            qDebug()<<PD+"/LIN1_"+QString::number(i)+"_Enable"<<LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_Enable").toInt();

            if(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_Enable").toInt()== 1)//记录使能
            {
                LIN_Main.at(i-1)->ui->Set_LIN_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
                LIN_Main.at(i-1)->LIN_Enable_flag=1;
            }
            else
            {

                LIN_Main.at(i-1)->ui->Set_LIN_Enable->setStyleSheet("");
                LIN_Main.at(i-1)->LIN_Enable_flag=0;
            }
            if(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_ErrorEnable").toInt() == 1)//记录误差使能
            {
                LIN_Main.at(i-1)->ui->Set_LIN_ErrorEnable->setStyleSheet("background-color: rgb(0, 200, 0);");
                LIN_Main.at(i-1)->LIN_ErrorEnable=1;
            }
            else
            {
                LIN_Main.at(i-1)->ui->Set_LIN_ErrorEnable->setStyleSheet("");
                LIN_Main.at(i-1)->LIN_ErrorEnable=0;
            }
            if(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_InitEnable").toInt() == 1)//记录初始化使能
            {
                LIN_Main.at(i-1)->ui->Set_LIN_ErrorEnable->setStyleSheet("background-color: rgb(0, 200, 0);");
                LIN_Main.at(i-1)->LIN_InitEnable_flag=1;
            }
            else
            {
                LIN_Main.at(i-1)->ui->Set_LIN_ErrorEnable->setStyleSheet("");
                LIN_Main.at(i-1)->LIN_InitEnable_flag=0;
            }

            LIN_Main.at(i-1)->ui->Set_LIN_Name->setText(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_Name").toString());
            LIN_Main.at(i-1)->ui->Set_LIN_RunSpeed->setValue(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_RunSpeed").toDouble());
            LIN_Main.at(i-1)->ui->Set_LIN_MaxRunTime->setValue(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_MaxRunTime").toDouble());
            LIN_Main.at(i-1)->ui->Set_LIN_InitDirection->setCurrentIndex(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_InitDirection").toInt());
            LIN_Main.at(i-1)->ui->Set_LIN_error->setValue(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_errorValue").toDouble());
            LIN_Main.at(i-1)->ui->Set_LIN_NAD->setText(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_NAD").toString());
            LIN_Main.at(i-1)->ui->Set_LIN_Controlid->setText(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_Controlid").toString());
            LIN_Main.at(i-1)->ui->Set_LIN_Stateid->setText(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_Stateid").toString());
            LIN_Main.at(i-1)->ui->Set_LIN_Direction->setCurrentIndex(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_Direction").toInt());
            LIN_Main.at(i-1)->ui->Set_LIN_InitValue->setValue(LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_InitValue").toInt());
            
            QString TimeString = LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_Time").toString();
            if (!TimeString.isEmpty())
            {
                QStringList TimeList = TimeString.split(',');// 将字符串按逗号分割成列表
                LIN_Main.at(i-1)->ui->Set_LIN_Time1->setValue(TimeList[0].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Time2->setValue(TimeList[1].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Time3->setValue(TimeList[2].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Time4->setValue(TimeList[3].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Time5->setValue(TimeList[4].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Time6->setValue(TimeList[5].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Time7->setValue(TimeList[6].toDouble());
            }
            else
            {
                LIN_Main.at(i-1)->ui->Set_LIN_Time1->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Time2->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Time3->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Time4->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Time5->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Time6->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Time7->setValue(0);
            }

            QString StepString = LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_Step").toString();
            if(!StepString.isEmpty())
            {
                QStringList StepList= StepString.split(',');
                LIN_Main.at(i-1)->ui->Set_LIN_Step1->setValue(StepList[0].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Step2->setValue(StepList[1].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Step3->setValue(StepList[2].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Step4->setValue(StepList[3].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Step5->setValue(StepList[4].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Step6->setValue(StepList[5].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Step7->setValue(StepList[6].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Step8->setValue(StepList[7].toDouble());
            }
            else
            {
                LIN_Main.at(i-1)->ui->Set_LIN_Step1->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Step2->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Step3->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Step4->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Step5->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Step6->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Step7->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Step8->setValue(0);
            }

            QString NameString = LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_POS_Name").toString();
            if(!NameString.isEmpty())
            {
                QStringList NameList= NameString.split(',');
                LIN_Main.at(i-1)->ui->LinMotor_POS1_Name->setText(NameList[0]);
                LIN_Main.at(i-1)->ui->LinMotor_POS2_Name->setText(NameList[1]);
                LIN_Main.at(i-1)->ui->LinMotor_POS3_Name->setText(NameList[2]);
                LIN_Main.at(i-1)->ui->LinMotor_POS4_Name->setText(NameList[3]);
                LIN_Main.at(i-1)->ui->LinMotor_POS5_Name->setText(NameList[4]);
                LIN_Main.at(i-1)->ui->LinMotor_POS6_Name->setText(NameList[5]);
                LIN_Main.at(i-1)->ui->LinMotor_POS7_Name->setText(NameList[6]);
                LIN_Main.at(i-1)->ui->LinMotor_POS8_Name->setText(NameList[7]);
            }
            else
            {
                LIN_Main.at(i-1)->ui->LinMotor_POS1_Name->setText("1");
                LIN_Main.at(i-1)->ui->LinMotor_POS2_Name->setText("2");
                LIN_Main.at(i-1)->ui->LinMotor_POS3_Name->setText("3");
                LIN_Main.at(i-1)->ui->LinMotor_POS4_Name->setText("4");
                LIN_Main.at(i-1)->ui->LinMotor_POS5_Name->setText("5");
                LIN_Main.at(i-1)->ui->LinMotor_POS6_Name->setText("6");
                LIN_Main.at(i-1)->ui->LinMotor_POS7_Name->setText("7");
                LIN_Main.at(i-1)->ui->LinMotor_POS8_Name->setText("8");
            }

            QString ValueString = LinINI_File->value(PD+"/LIN1_"+QString::number(i)+"_POS_Value").toString();
            if(!ValueString.isEmpty())
            {
                QStringList ValueList = ValueString.split(',');
                LIN_Main.at(i-1)->ui->Set_LIN_Value1->setValue(ValueList[0].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Value2->setValue(ValueList[1].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Value3->setValue(ValueList[2].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Value4->setValue(ValueList[3].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Value5->setValue(ValueList[4].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Value6->setValue(ValueList[5].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Value7->setValue(ValueList[6].toDouble());
                LIN_Main.at(i-1)->ui->Set_LIN_Value8->setValue(ValueList[7].toDouble());
            }
            else
            {
                LIN_Main.at(i-1)->ui->Set_LIN_Value1->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Value2->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Value3->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Value4->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Value5->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Value6->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Value7->setValue(0);
                LIN_Main.at(i-1)->ui->Set_LIN_Value8->setValue(0);
            }
        }
    }
    //----------------------------PT_Motor ini-----------------------------
    QString Ptpath = QApplication::applicationDirPath() + "/HVAC/HVAC_PT_Data.ini";
    QSettings *PtINI_File = new QSettings(Ptpath, QSettings::IniFormat);
    PtINI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    for (int i =1;i<13;i++ )
    {
        if(i<13)
        {
            //--------------------------------------PT电机-------------------------------------------
            if(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Enable").toInt()== 1)//判断电机使能
            {
                //                Motor_Main.at(i-1)->ui->Set_Motor_Enable->click();

                Motor_Main.at(i-1)->ui->Set_Motor_Enable->setStyleSheet(" background-color: rgb(0, 200, 0);");
                Motor_Main.at(i-1)->Motor_Enable_flag=1;
            }
            else
            {
                Motor_Main.at(i-1)->ui->Set_Motor_Enable->setStyleSheet("");
                Motor_Main.at(i-1)->Motor_Enable_flag=0;
            }

            if(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_PT_Mode_flag").toInt()== 1)//记录电机五线-两线
            {
                //                Motor_Main.at(i-1)->ui->Set_PT_5Line->click();
                Motor_Main.at(i-1)->Motor_PT_Mode_flag = 1;
                Motor_Main.at(i-1)->ui->Set_PT_2Line->setStyleSheet("");
                Motor_Main.at(i-1)->ui->Set_PT_5Line->setStyleSheet("background-color: rgb(0, 200, 0);");
            }
            else if(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_PT_Mode_flag").toInt()== 2)
            {
                //                Motor_Main.at(i-1)->ui->Set_PT_2Line->click();
                Motor_Main.at(i-1)->Motor_PT_Mode_flag = 2;
                Motor_Main.at(i-1)->ui->Set_PT_2Line->setStyleSheet("background-color: rgb(0, 200, 0);");
                Motor_Main.at(i-1)->ui->Set_PT_5Line->setStyleSheet("");
            }
            else
            {
                Motor_Main.at(i-1)->Motor_PT_Mode_flag = 0;
                Motor_Main.at(i-1)->ui->Set_PT_2Line->setStyleSheet("");
                Motor_Main.at(i-1)->ui->Set_PT_5Line->setStyleSheet("");
            }

            if(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_PT_Direction_flag").toInt()== 1)//记录电机运行方向
            {
                //                Motor_Main.at(i-1)->ui->Set_CW5_0->click();
                Motor_Main.at(i-1)->Motor_PT_Direction_flag = 1;
                Motor_Main.at(i-1)->ui->Set_CW0_5->setStyleSheet("");
                Motor_Main.at(i-1)->ui->Set_CW5_0->setStyleSheet("background-color: rgb(0, 200, 0);");
            }
            else if(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_PT_Direction_flag").toInt()== 2)//记录电机运行方向
            {
                //                Motor_Main.at(i-1)->ui->Set_CW0_5->click();
                Motor_Main.at(i-1)->Motor_PT_Direction_flag = 2;
                Motor_Main.at(i-1)->ui->Set_CW0_5->setStyleSheet("background-color: rgb(0, 200, 0);");
                Motor_Main.at(i-1)->ui->Set_CW5_0->setStyleSheet("");
            }
            else
            {
                Motor_Main.at(i-1)->Motor_PT_Direction_flag = 0;
                Motor_Main.at(i-1)->ui->Set_CW0_5->setStyleSheet("");
                Motor_Main.at(i-1)->ui->Set_CW5_0->setStyleSheet("");
            }

            if(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_PT_Line2_flag").toInt()== 1)//记录两线电机堵转/停止
            {
                //                Motor_Main.at(i-1)->ui->Set_Line2_Stuck->click();
                Motor_Main.at(i-1)->Motor_PT_Line2_flag = 1;
                Motor_Main.at(i-1)->ui->Set_Line2_Stop->setStyleSheet("");
                Motor_Main.at(i-1)->ui->Set_Line2_Stuck->setStyleSheet("background-color: rgb(0, 200, 0);");
            }
            else if(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_PT_Line2_flag").toInt()== 2)//记录两线电机堵转/停止
            {
                //                Motor_Main.at(i-1)->ui->Set_Line2_Stop->click();
                Motor_Main.at(i-1)->Motor_PT_Line2_flag = 2;
                Motor_Main.at(i-1)->ui->Set_Line2_Stop->setStyleSheet("background-color: rgb(0, 200, 0);");
                Motor_Main.at(i-1)->ui->Set_Line2_Stuck->setStyleSheet("");
            }
            else
            {
                Motor_Main.at(i-1)->Motor_PT_Line2_flag = 0;
                Motor_Main.at(i-1)->ui->Set_Line2_Stop->setStyleSheet("");
                Motor_Main.at(i-1)->ui->Set_Line2_Stuck->setStyleSheet("");
            }

            Motor_Main.at(i-1)->ui->Set_Motor_Name->setText(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Name").toString());

            QString PTDelayString = PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Delay").toString();
            if (!PTDelayString.isEmpty())
            {
                QStringList DelayList = PTDelayString.split(',');// 将字符串按逗号分割成列表
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_1->setValue(DelayList[0].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_2->setValue(DelayList[1].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_3->setValue(DelayList[2].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_4->setValue(DelayList[3].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_5->setValue(DelayList[4].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_6->setValue(DelayList[5].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_7->setValue(DelayList[6].toDouble());
            }
            else
            {
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_1->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_2->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_3->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_4->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_5->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_6->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Delay_7->setValue(0);
                //                qWarning() << "未在INI文件中找到LIN_Time/Values键或其值为空。";
            }

            QString PTStepString = PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Step").toString();;//记录顺序
            if (!PTStepString.isEmpty())
            {
                QStringList PTStepList = PTStepString.split(',');// 将字符串按逗号分割成列表
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_1->setValue(PTStepList[0].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_2->setValue(PTStepList[1].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_3->setValue(PTStepList[2].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_4->setValue(PTStepList[3].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_5->setValue(PTStepList[4].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_6->setValue(PTStepList[5].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_7->setValue(PTStepList[6].toDouble());
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_8->setValue(PTStepList[7].toDouble());
            }
            else
            {
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_1->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_2->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_3->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_4->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_5->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_6->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_7->setValue(0);
                Motor_Main.at(i-1)->ui->Set_Motor_Steps_8->setValue(0);
            }

            QString PTPosNameString = PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_POS_Name").toString();;//记录POS名字
            if (!PTPosNameString.isEmpty())
            {
                QStringList PTPosNameList = PTPosNameString.split(',');// 将字符串按逗号分割成列表
                Motor_Main.at(i-1)->ui->Motor_POS1_Text->setText(PTPosNameList[0]);
                Motor_Main.at(i-1)->ui->Motor_POS2_Text->setText(PTPosNameList[1]);
                Motor_Main.at(i-1)->ui->Motor_POS3_Text->setText(PTPosNameList[2]);
                Motor_Main.at(i-1)->ui->Motor_POS4_Text->setText(PTPosNameList[3]);
                Motor_Main.at(i-1)->ui->Motor_POS5_Text->setText(PTPosNameList[4]);
                Motor_Main.at(i-1)->ui->Motor_POS6_Text->setText(PTPosNameList[5]);
                Motor_Main.at(i-1)->ui->Motor_POS7_Text->setText(PTPosNameList[6]);
                Motor_Main.at(i-1)->ui->Motor_POS8_Text->setText(PTPosNameList[7]);
            }
            else
            {
                Motor_Main.at(i-1)->ui->Motor_POS1_Text->setText("1");
                Motor_Main.at(i-1)->ui->Motor_POS2_Text->setText("2");
                Motor_Main.at(i-1)->ui->Motor_POS3_Text->setText("3");
                Motor_Main.at(i-1)->ui->Motor_POS4_Text->setText("4");
                Motor_Main.at(i-1)->ui->Motor_POS5_Text->setText("5");
                Motor_Main.at(i-1)->ui->Motor_POS6_Text->setText("6");
                Motor_Main.at(i-1)->ui->Motor_POS7_Text->setText("7");
                Motor_Main.at(i-1)->ui->Motor_POS8_Text->setText("8");
            }

            QString PTMaxValueString = PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Max_Value").toString();;//记录POS上限
            if (!PTMaxValueString.isEmpty())
            {
                QStringList PTMaxValueList = PTMaxValueString.split(',');// 将字符串按逗号分割成列表
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_1->setValue(PTMaxValueList[0].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_2->setValue(PTMaxValueList[1].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_3->setValue(PTMaxValueList[2].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_4->setValue(PTMaxValueList[3].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_5->setValue(PTMaxValueList[4].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_6->setValue(PTMaxValueList[5].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_7->setValue(PTMaxValueList[6].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_8->setValue(PTMaxValueList[7].toDouble());
            }
            else
            {
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_1->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_2->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_3->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_4->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_5->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_6->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_7->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_8->setValue(0);
            }

            QString PTMinValueString = PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Min_Value").toString();;//记录POS下限
            if (!PTMinValueString.isEmpty())
            {
                QStringList PTMinValueList = PTMinValueString.split(',');// 将字符串按逗号分割成列表
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_1->setValue(PTMinValueList[0].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_2->setValue(PTMinValueList[1].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_3->setValue(PTMinValueList[2].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_4->setValue(PTMinValueList[3].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_5->setValue(PTMinValueList[4].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_6->setValue(PTMinValueList[5].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_7->setValue(PTMinValueList[6].toDouble());
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_8->setValue(PTMinValueList[7].toDouble());
            }
            else
            {
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_1->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_2->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_3->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_4->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_5->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_6->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_7->setValue(0);
                Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_8->setValue(0);
            }

            Motor_Main.at(i-1)->ui->Set_Motor_Num->setValue(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_MotorNum").toDouble());
            Motor_Main.at(i-1)->ui->Set_Motor_Run_Max_A->setValue(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Run_Max_A").toDouble());
            Motor_Main.at(i-1)->ui->Set_Motor_Run_Min_A->setValue(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Run_Min_A").toDouble());
            Motor_Main.at(i-1)->ui->Set_Motor_Stuck_A->setValue(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Stuck_A").toDouble());
            Motor_Main.at(i-1)->ui->Set_Motor_Start_Delay->setValue(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Start_Delay").toDouble());
            Motor_Main.at(i-1)->ui->Set_Motor_Delay_alarm->setValue(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Delay_alarm").toDouble());
            Motor_Main.at(i-1)->ui->Set_Motor_Run_MaxTime->setValue(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Run_MaxTime").toDouble());
            Motor_Main.at(i-1)->ui->Set_MotorVoltageAvgCount->setValue(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_voltageAvgCount").toDouble());//电压平均次数
            Motor_Main.at(i-1)->ui->Set_MotorCurrentAvgCount->setValue(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_currentAvgCount").toDouble());//电流平均次数
            Motor_Main.at(i-1)->ui->Set_Line2Motor_RunTime->setValue(PtINI_File->value(PD+"/Motor_"+QString::number(i)+"_Line2Motor_RunTime").toDouble());
        }
    }
    PtINI_File->destroyed();
    //----------------------------鼓风机 ini-----------------------------
    QString Blowerpath = QApplication::applicationDirPath() + "/HVAC/HVAC_Blower_Data.ini";
    QSettings *BlowerINI_File = new QSettings(Blowerpath, QSettings::IniFormat);
    BlowerINI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    if(BlowerINI_File->value(PD+"/Blower_Enable").toInt()== 1)//鼓风机使能
    {
        //        ui->Set_Blower_Enable->click();
        Blower_Enable_flag = 1;
        ui->Set_Blower_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        Blower_Enable_flag = 0;
        ui->Set_Blower_Enable->setStyleSheet("");
    }

    if(BlowerINI_File->value(PD+"/Blower_Mode").toInt()== 1)//记录鼓风机类型 0电压 1PWM 2电阻 3LIN
    {
        //        ui->Set_Blower_V->click();

        Blower_Mode_flag = 1;
        ui->Set_Blower_V->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Set_Blower_PWM->setStyleSheet("");
        ui->Set_Blower_LIN->setStyleSheet("");
    }
    else if(BlowerINI_File->value(PD+"/Blower_Mode").toInt()== 2)
    {
        //        ui->Set_Blower_PWM->click();
        Blower_Mode_flag = 2;
        ui->Set_Blower_V->setStyleSheet("");
        ui->Set_Blower_PWM->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Set_Blower_LIN->setStyleSheet("");
    }
    else if(BlowerINI_File->value(PD+"/Blower_Mode").toInt()== 3)
    {
        //        ui->Set_Blower_LIN->click();
        Blower_Mode_flag = 3;
        ui->Set_Blower_V->setStyleSheet("");
        ui->Set_Blower_PWM->setStyleSheet("");
        ui->Set_Blower_LIN->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        Blower_Mode_flag = 0;
        ui->Set_Blower_V->setStyleSheet("");
        ui->Set_Blower_PWM->setStyleSheet("");
        ui->Set_Blower_LIN->setStyleSheet("");
    }

    ui->Blower_Start_Delay->setValue(BlowerINI_File->value(PD+"/Blower_Start_Delay").toDouble());//记录鼓风机启动延时
    ui->Blower_V_Max->setValue(BlowerINI_File->value(PD+"/Blower_V_Max").toDouble());//记录鼓风机电源电压上限
    ui->Blower_V_Min->setValue(BlowerINI_File->value(PD+"/Blower_V_Min").toDouble());//记录鼓风机电源电压下限
    ui->Blower_PWM_HZ->setValue(BlowerINI_File->value(PD+"/Blower_PWM_HZ").toDouble());//记录鼓风机频率

    QString BlowerStepString = BlowerINI_File->value(PD+"/Blower_Step").toString();
    if(!BlowerStepString.isEmpty())
    {
        QStringList BlowerStepList = BlowerStepString.split(',');
        for(int i=0;i<Blower_StepsWidgets.count();i++)
        {
            Blower_StepsWidgets[i]->setValue(BlowerStepList[i].toDouble());
        }
    }

    //-------------------端电压型鼓风机--------------------
    QString VBlowerPosNameString = BlowerINI_File->value(PD+"/VoltageBlower_PosName").toString();
    if(!VBlowerPosNameString.isEmpty())
    {
        QStringList VBlowerPosNameList = VBlowerPosNameString.split(',');
        for(int i=0;i<VBlowerPosNameWidgets.count();i++)
        {
            VBlowerPosNameWidgets[i]->setText(VBlowerPosNameList[i]);
        }
    }
    else
    {

        VBlowerPosNameWidgets[0]->setText("1档");
        VBlowerPosNameWidgets[1]->setText("2档");
        VBlowerPosNameWidgets[2]->setText("3档");
        VBlowerPosNameWidgets[3]->setText("4档");
        VBlowerPosNameWidgets[4]->setText("5档");
        VBlowerPosNameWidgets[5]->setText("6档");
        VBlowerPosNameWidgets[6]->setText("7档");
        VBlowerPosNameWidgets[7]->setText("8档");
        VBlowerPosNameWidgets[8]->setText("9档");

    }

    QString VBlowerVString = BlowerINI_File->value(PD+"/VoltageBlower_Voltage").toString();
    if(!VBlowerVString.isEmpty())
    {
        QStringList VBlowerVList = VBlowerVString.split(',');
        for(int i=0;i<VBlowerVWidgets.count();i++)
        {
            VBlowerVWidgets[i]->setValue(VBlowerVList[i].toDouble());
        }
    }

    QString VBlowerTimeString = BlowerINI_File->value(PD+"/VoltageBlower_Time").toString();
    if(!VBlowerTimeString.isEmpty())
    {
        QStringList VBlowerTimeList = VBlowerTimeString.split(',');
        for(int i=0;i<VBlowerTimeWidgets.count();i++)
        {
            VBlowerTimeWidgets[i]->setValue(VBlowerTimeList[i].toDouble());
        }
    }

    QString VBlowerMaxAString = BlowerINI_File->value(PD+"/VoltageBlower_MaxA").toString();
    if(!VBlowerMaxAString.isEmpty())
    {
        QStringList VBlowerMaxAList = VBlowerMaxAString.split(',');
        for(int i=0;i<VBlowerMaxAWidgets.count();i++)
        {
            VBlowerMaxAWidgets[i]->setValue(VBlowerMaxAList[i].toDouble());
        }
    }

    QString VBlowerMinAString = BlowerINI_File->value(PD+"/VoltageBlower_MinA").toString();
    if(!VBlowerMinAString.isEmpty())
    {
        QStringList VBlowerMinAList = VBlowerMinAString.split(',');
        for(int i=0;i<VBlowerMinAWidgets.count();i++)
        {
            VBlowerMinAWidgets[i]->setValue(VBlowerMinAList[i].toDouble());
        }
    }

    //-------------------PWM型鼓风机--------------------
    QString PWMBlowerPosNameString = BlowerINI_File->value(PD+"/PWMBlower_PosName").toString();
    if(!PWMBlowerPosNameString.isEmpty())
    {
        QStringList PWMPosNameList = PWMBlowerPosNameString.split(',');
        for (int i = 0; i < PWMBlowerPosNameWidgets.count(); i++) {
            PWMBlowerPosNameWidgets[i]->setText(PWMPosNameList[i]);
        }
    }
    else
    {

        PWMBlowerPosNameWidgets[0]->setText("1档");
        PWMBlowerPosNameWidgets[1]->setText("2档");
        PWMBlowerPosNameWidgets[2]->setText("3档");
        PWMBlowerPosNameWidgets[3]->setText("4档");
        PWMBlowerPosNameWidgets[4]->setText("5档");
        PWMBlowerPosNameWidgets[5]->setText("6档");
        PWMBlowerPosNameWidgets[6]->setText("7档");
        PWMBlowerPosNameWidgets[7]->setText("8档");
        PWMBlowerPosNameWidgets[8]->setText("9档");

    }

    QString PWMBlowerPWMString = BlowerINI_File->value(PD+"/PWMBlower_PWM").toString();
    if(!PWMBlowerPWMString.isEmpty())
    {
        QStringList PWMPosNameList = PWMBlowerPWMString.split(',');
        for (int i = 0; i < PWMBlowerPWMWidgets.count(); i++) {
            PWMBlowerPWMWidgets[i]->setValue(PWMPosNameList[i].toDouble());
        }
    }

    QString PWMBlowerTimeString = BlowerINI_File->value(PD+"/PWMBlower_Time").toString();
    if(!PWMBlowerTimeString.isEmpty())
    {
        QStringList PWMBlowerTimeList = PWMBlowerTimeString.split(',');
        for (int i = 0; i < PWMBlowerTimeWidgets.count(); i++) {
            PWMBlowerTimeWidgets[i]->setValue(PWMBlowerTimeList[i].toDouble());
        }
    }

    QString PWMBlowerMaxAString = BlowerINI_File->value(PD+"/PWMBlower_MaxA").toString();
    if(!PWMBlowerMaxAString.isEmpty())
    {
        QStringList PWMBlowerMaxAList = PWMBlowerMaxAString.split(',');
        for (int i = 0; i < PWMBlowerMaxAWidgets.count(); i++) {
            PWMBlowerMaxAWidgets[i]->setValue(PWMBlowerMaxAList[i].toDouble());
        }
    }

    QString PWMBlowerMinAString = BlowerINI_File->value(PD+"/PWMBlower_MinA").toString();
    if(!PWMBlowerMinAString.isEmpty())
    {
        QStringList PWMBlowerMinAList = PWMBlowerMinAString.split(',');
        for (int i = 0; i < PWMBlowerMinAWidgets.count(); i++) {
            PWMBlowerMinAWidgets[i]->setValue(PWMBlowerMinAList[i].toDouble());
        }
    }

    //-------------------LIN型鼓风机--------------------
    QString LINBlowerPosNameString = BlowerINI_File->value(PD+"/LINBlower_PosName").toString();
    if(!LINBlowerPosNameString.isEmpty())
    {
        QStringList LINBlowerPosNameList = LINBlowerPosNameString.split(',');
        for (int i = 0; i < LINBlowerPosNameWidgets.count(); i++) {
            LINBlowerPosNameWidgets[i]->setText(LINBlowerPosNameList[i]);
        }
    }
    else
    {

        LINBlowerPosNameWidgets[0]->setText("1档");
        LINBlowerPosNameWidgets[1]->setText("2档");
        LINBlowerPosNameWidgets[2]->setText("3档");
        LINBlowerPosNameWidgets[3]->setText("4档");
        LINBlowerPosNameWidgets[4]->setText("5档");
        LINBlowerPosNameWidgets[5]->setText("6档");
        LINBlowerPosNameWidgets[6]->setText("7档");
        LINBlowerPosNameWidgets[7]->setText("8档");
        LINBlowerPosNameWidgets[8]->setText("9档");

    }


    QString LINBlowerLINString = BlowerINI_File->value(PD+"/LINBlower_LIN").toString();
    if(!LINBlowerLINString.isEmpty())
    {
        QStringList LINBlowerLINList = LINBlowerLINString.split(',');
        for (int i = 0; i < LINBlowerLINWidgets.count(); i++) {
            LINBlowerLINWidgets[i]->setValue(LINBlowerLINList[i].toDouble());
        }
    }

    QString LINBlowerTimeString = BlowerINI_File->value(PD+"/LINBlower_Time").toString();
    if(!LINBlowerTimeString.isEmpty())
    {
        QStringList LINBlowerTimeList = LINBlowerTimeString.split(',');
        for (int i = 0; i < LINBlowerTimeWidgets.count(); i++) {
            LINBlowerTimeWidgets[i]->setValue(LINBlowerTimeList[i].toDouble());
        }
    }

    QString LINBlowerMaxAString = BlowerINI_File->value(PD+"/LINBlower_MaxA").toString();
    if(!LINBlowerMaxAString.isEmpty())
    {
        QStringList LINBlowerMaxAList = LINBlowerMaxAString.split(',');
        for (int i = 0; i < LINBlowerMaxAWidgets.count(); i++) {
            LINBlowerMaxAWidgets[i]->setValue(LINBlowerMaxAList[i].toDouble());
        }
    }

    QString LINBlowerMinAString = BlowerINI_File->value(PD+"/LINBlower_MinA").toString();
    if(!LINBlowerMinAString.isEmpty())
    {
        QStringList LINBlowerMinAList = LINBlowerMinAString.split(',');
        for (int i = 0; i < LINBlowerMinAWidgets.count(); i++) {
            LINBlowerMinAWidgets[i]->setValue(LINBlowerMinAList[i].toDouble());
        }
    }

    ui->Blower_LIN_Controlid->setText(BlowerINI_File->value(PD+"/LINBlower_Controlid").toString());
    ui->Blower_LIN_Stateid->setText(BlowerINI_File->value(PD+"/LINBlower_Stateid").toString());
    ui->Blower_Send_ID->setText(BlowerINI_File->value(PD+"/LINBlower_Send_ID").toString());
    ui->Blower_Read_ID->setText(BlowerINI_File->value(PD+"/LINBlower_Read_ID").toString());
    if(BlowerINI_File->value(PD+"/LINBlower_RPMcontrastEnable").toInt() ==1 )
    {
        Blower_RPMcontrast_flag = 1;
        ui->Set_Blower_RPMcontrast->setStyleSheet("background-color: rgb(0, 200, 0);");
        ui->Set_Blower_RPMcontrast->setText("OFF");
    }
    else
    {
        Blower_RPMcontrast_flag = 0;
        ui->Set_Blower_RPMcontrast->setStyleSheet("");
        ui->Set_Blower_RPMcontrast->setText("ON");
    }
    ui->Blower_error->setValue(BlowerINI_File->value(PD+"/LINBlower_error").toDouble());


    //-------------------------------震动+噪音-----------------------------
    if(BlowerINI_File->value(PD+"/X_vibration_Enable").toInt() ==1)
    {
        X_vibration_Enable_flag = 1;
        ui->X_vibration_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        X_vibration_Enable_flag = 0;
        ui->X_vibration_Enable->setStyleSheet("");
    }
    if(BlowerINI_File->value(PD+"/Y_vibration_Enable").toInt() ==1)
    {
        Y_vibration_Enable_flag = 1;
        ui->Y_vibration_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        Y_vibration_Enable_flag = 0;
        ui->Y_vibration_Enable->setStyleSheet("");
    }
    if(BlowerINI_File->value(PD+"/Z_vibration_Enable").toInt() ==1)
    {
        Z_vibration_Enable_flag = 1;
        ui->Z_vibration_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        Z_vibration_Enable_flag = 0;
        ui->Z_vibration_Enable->setStyleSheet("");
    }
    if(BlowerINI_File->value(PD+"/Noises_Enable").toInt() ==1)
    {
        Noises_Enable_flag =1;
        ui->Noises_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        Noises_Enable_flag =0;
        ui->Noises_Enable->setStyleSheet("");
    }

    ui->vibration_Start_Delay->setValue(BlowerINI_File->value(PD+"/Vibration_Delay").toDouble());
    ui->vibration_CheckTime->setValue(BlowerINI_File->value(PD+"/Vibration_CheckTime").toDouble());
    ui->Noises_StartDelay->setValue(BlowerINI_File->value(PD+"/Noises_Delay").toDouble());
    ui->Noises_CheckTime->setValue(BlowerINI_File->value(PD+"/Noises_CheckTime").toDouble());

    QString VibrationPosString = BlowerINI_File->value(PD+"/Vibration_PosName").toString();
    if(!VibrationPosString.isEmpty())
    {
        QStringList VibrationPosList = VibrationPosString.split(',');
        for (int i = 0; i < vibrationNameWidgets.count(); i++) {
            vibrationNameWidgets[i]->setText(VibrationPosList[i]);
        }
    }
    else
    {

        vibrationNameWidgets[0]->setText("1档");
        vibrationNameWidgets[1]->setText("2档");
        vibrationNameWidgets[2]->setText("3档");
        vibrationNameWidgets[3]->setText("4档");
        vibrationNameWidgets[4]->setText("5档");
        vibrationNameWidgets[5]->setText("6档");
        vibrationNameWidgets[6]->setText("7档");
        vibrationNameWidgets[7]->setText("8档");
        vibrationNameWidgets[8]->setText("9档");

    }

    QString XVibrationMaxValueString = BlowerINI_File->value(PD+"/XVibration_MaxValue").toString();
    if(!XVibrationMaxValueString.isEmpty())
    {
        QStringList XVibrationMaxValueList = XVibrationMaxValueString.split(',');
        for (int i = 0; i < xVibrationMaxWidgets.count(); i++) {
            xVibrationMaxWidgets[i]->setValue(XVibrationMaxValueList[i].toDouble());
        }
    }

    QString XVibrationMinValueString = BlowerINI_File->value(PD+"/XVibration_MinValue").toString();
    if(!XVibrationMinValueString.isEmpty())
    {
        QStringList XVibrationMinValueList = XVibrationMinValueString.split(',');
        for (int i = 0; i < xVibrationMinWidgets.count(); i++) {
            xVibrationMinWidgets[i]->setValue(XVibrationMinValueList[i].toDouble());
        }
    }

    QString YVibrationMaxValueString = BlowerINI_File->value(PD+"/YVibration_MaxValue").toString();
    if(!YVibrationMaxValueString.isEmpty())
    {
        QStringList YVibrationMaxValueList = YVibrationMaxValueString.split(',');
        for (int i = 0; i < yVibrationMaxWidgets.count(); i++) {
            yVibrationMaxWidgets[i]->setValue(YVibrationMaxValueList[i].toDouble());
        }
    }

    QString YVibrationMinValueString = BlowerINI_File->value(PD+"/YVibration_MinValue").toString();
    if(!YVibrationMinValueString.isEmpty())
    {
        QStringList YVibrationMinValueList = YVibrationMinValueString.split(',');
        for (int i = 0; i < yVibrationMinWidgets.count(); i++) {
            yVibrationMinWidgets[i]->setValue(YVibrationMinValueList[i].toDouble());
        }
    }

    QString ZVibrationMaxValueString = BlowerINI_File->value(PD+"/ZVibration_MaxValue").toString();
    if(!ZVibrationMaxValueString.isEmpty())
    {
        QStringList ZVibrationMaxValueList = ZVibrationMaxValueString.split(',');
        for (int i = 0; i < zVibrationMaxWidgets.count(); i++) {
            zVibrationMaxWidgets[i]->setValue(ZVibrationMaxValueList[i].toDouble());
        }
    }

    QString ZVibrationMinValueString = BlowerINI_File->value(PD+"/ZVibration_MinValue").toString();
    if(!ZVibrationMinValueString.isEmpty())
    {
        QStringList ZVibrationMinValueList = ZVibrationMinValueString.split(',');
        for (int i = 0; i < zVibrationMinWidgets.count(); i++) {
            zVibrationMinWidgets[i]->setValue(ZVibrationMinValueList[i].toDouble());
        }
    }

    QString NoisesMaxValueString = BlowerINI_File->value(PD+"/Noises_MaxValue").toString();
    if(!NoisesMaxValueString.isEmpty())
    {
        QStringList NoisesMaxValueList = NoisesMaxValueString.split(',');
        for (int i = 0; i < noisesMaxWidgets.count(); i++) {
            noisesMaxWidgets[i]->setValue(NoisesMaxValueList[i].toDouble());
        }
    }

    QString NoisesMinValueString = BlowerINI_File->value(PD+"/Noises_MinValue").toString();
    if(!NoisesMinValueString.isEmpty())
    {
        QStringList NoisesMinValueList = NoisesMinValueString.split(',');
        for (int i = 0; i < noisesMinWidgets.count(); i++) {
            noisesMinWidgets[i]->setValue(NoisesMinValueList[i].toDouble());
        }
    }


    //-------------------------------电子膨胀阀-----------------------------

    if(BlowerINI_File->value(PD+"/Expansionvalves_Enable") ==1)
    {
        //        ui->Expansionvalves_Enable->click();
        Expansionvalves_Enable_flag = 1;
        ui->Expansionvalves_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        Expansionvalves_Enable_flag = 0;
        ui->Expansionvalves_Enable->setStyleSheet("");
    }

    ui->Expansionvalves_Controlid->setText(BlowerINI_File->value(PD+"/Expansionvalves_Controlid").toString());
    ui->Expansionvalves_Stateid->setText(BlowerINI_File->value(PD+"/Expansionvalves_Stateid").toString());
    ui->Expansionvalves_StartDelay->setValue(BlowerINI_File->value(PD+"/Expansionvalves_StartDelay").toDouble());
    ui->Expansionvalves_RunTimer->setValue(BlowerINI_File->value(PD+"/Expansionvalves_RunTimer").toDouble());

    QString ExpansionvalvesPosNameString = BlowerINI_File->value(PD+"/Expansionvalves_PosName").toString();
    if(!ExpansionvalvesPosNameString.isEmpty())
    {
        QStringList xpansionvalvesPosNameList = ExpansionvalvesPosNameString.split(',');
        for (int i = 0; i < ExpansionPosNameWidgets.count(); i++) {
            ExpansionPosNameWidgets[i]->setText(xpansionvalvesPosNameList[i]);
        }
    }
    else
    {

        ExpansionPosNameWidgets[0]->setText("1");
        ExpansionPosNameWidgets[1]->setText("2");
        ExpansionPosNameWidgets[2]->setText("3");
        ExpansionPosNameWidgets[3]->setText("4");
        ExpansionPosNameWidgets[4]->setText("5");
        ExpansionPosNameWidgets[5]->setText("6");
        ExpansionPosNameWidgets[6]->setText("7");


    }


    QString ExpansionvalvesStepString = BlowerINI_File->value(PD+"/Expansionvalves_Step").toString();
    if(!ExpansionvalvesStepString.isEmpty())
    {
        QStringList ExpansionvalvesStepList = ExpansionvalvesStepString.split(',');
        for (int i = 0; i < ExpansionStepWidgets.count(); i++) {
            ExpansionStepWidgets[i]->setValue(ExpansionvalvesStepList[i].toDouble());
        }
    }

    QString ExpansionvalvesTimeString = BlowerINI_File->value(PD+"/Expansionvalves_Time").toString();
    if(!ExpansionvalvesTimeString.isEmpty())
    {
        QStringList ExpansionvalvesTimeList = ExpansionvalvesTimeString.split(',');
        for (int i = 0; i < ExpansionTimeWidgets.count(); i++) {
            ExpansionTimeWidgets[i]->setValue(ExpansionvalvesTimeList[i].toDouble());
        }
    }

    QString ExpansionvalvesValueString = BlowerINI_File->value(PD+"/Expansionvalves_Value").toString();
    if(!ExpansionvalvesValueString.isEmpty())
    {
        QStringList ExpansionvalvesValueList = ExpansionvalvesValueString.split(',');
        for (int i = 0; i < ExpansionValueWidgets.count(); i++) {
            ExpansionValueWidgets[i]->setValue(ExpansionvalvesValueList[i].toDouble());
        }
    }

    //-------------------------------PTC-----------------------------
    if(BlowerINI_File->value(PD+"/PTC_Enable").toInt()==1)
    {
        //        ui->PTC_Enable->click();
        PTC_Enable_flag = 1;
        ui->PTC_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        PTC_Enable_flag = 0;
        ui->PTC_Enable->setStyleSheet("");
    }
    ui->PTC_Controlid->setText(BlowerINI_File->value(PD+"/PTC_Controlid").toString());
    ui->PTC_Stateid->setText(BlowerINI_File->value(PD+"/PTC_Stateid").toString());
    ui->PTC_Btl->setCurrentIndex(BlowerINI_File->value(PD+"/PTC_Stateid").toInt());
    ui->PTC_Lb->setCurrentIndex(BlowerINI_File->value(PD+"/PTC_Stateid").toInt());
    ui->PTC_Hardware->setText(BlowerINI_File->value(PD+"/PTC_Hardware").toString());
    ui->PTC_Software->setText(BlowerINI_File->value(PD+"/PTC_Software").toString());
    ui->PTC_CheckTime->setValue(BlowerINI_File->value(PD+"/PTC_Stateid").toDouble());
    ui->PTC_StartDelay->setValue(BlowerINI_File->value(PD+"/PTC_Stateid").toDouble());

    //------------------------------PM2.5--------------------------
    if(BlowerINI_File->value(PD+"/PM25_Enable").toInt()==1)
    {
        //        ui->PM25_Enable->click();
        PM25_Enable_flag =1;
        ui->PM25_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        PM25_Enable_flag =0;
        ui->PM25_Enable->setStyleSheet("");
    }
    if(BlowerINI_File->value(PD+"/PM25_Ver_Enable").toInt()==1)
    {
        //        ui->PM25_Ver_Judge->click();
        PM25_Ver_Judge_flag =1;
        ui->PM25_Ver_Judge->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        PM25_Ver_Judge_flag =0;
        ui->PM25_Ver_Judge->setStyleSheet("");
    }
    ui->PM25_In_Value->setValue(BlowerINI_File->value(PD+"/PM25_In_Value").toDouble());
    ui->PM25_In_MaxValue->setValue(BlowerINI_File->value(PD+"/PM25_In_MaxValue").toDouble());
    ui->PM25_In_MinValue->setValue(BlowerINI_File->value(PD+"/PM25_In_MinValue").toDouble());
    ui->PM25_Out_Value->setValue(BlowerINI_File->value(PD+"/PM25_Out_Value").toDouble());
    ui->PM25_Out_MaxValue->setValue(BlowerINI_File->value(PD+"/PM25_Out_MaxValue").toDouble());
    ui->PM25_Out_MinValue->setValue(BlowerINI_File->value(PD+"/PM25_Out_MinValue").toDouble());
    ui->PM25_errorValue->setValue(BlowerINI_File->value(PD+"/PM25_errorValue").toDouble());
    ui->PM25_Software1->setValue(BlowerINI_File->value(PD+"/PM25_Software1").toDouble());
    ui->PM25_Software2->setValue(BlowerINI_File->value(PD+"/PM25_Software2").toDouble());


    //------------------------------AQS--------------------------
    if(BlowerINI_File->value(PD+"/AQS_Enable").toInt()==1)
    {
        //        ui->AQS_Enable->click();
        AQS_Enable_flag =1;
        ui->AQS_Enable->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        AQS_Enable_flag =0;
        ui->AQS_Enable->setStyleSheet("");
    }
    if(BlowerINI_File->value(PD+"/AQS_Ver_Enable").toInt()==1)
    {
        //        ui->AQS_Ver_Judge->click();
        AQS_Ver_Judge_flag =1;
        ui->AQS_Ver_Judge->setStyleSheet("background-color: rgb(0, 200, 0);");
    }
    else
    {
        AQS_Ver_Judge_flag =0;
        ui->AQS_Ver_Judge->setStyleSheet("");
    }
    ui->AQS_Stateid->setText(BlowerINI_File->value(PD+"/AQS_Stateid").toString());
    ui->AQS_Airquality->setText(BlowerINI_File->value(PD+"/AQS_Airquality").toString());
    ui->AQS_Max_Value->setText(BlowerINI_File->value(PD+"/AQS_Max_Value").toString());
    ui->AQS_Min_Value->setText(BlowerINI_File->value(PD+"/AQS_Min_Value").toString());
    ui->AQS_Software->setValue(BlowerINI_File->value(PD+"/AQS_Software").toDouble());
    ui->AQS_Hardware->setValue(BlowerINI_File->value(PD+"/AQS_Hardware").toDouble());

    //----------------------------电阻 风速 ini-----------------------------
    //--------------------------温敏--------------------------
    QString ResSpeedpath = QApplication::applicationDirPath() + "/HVAC/HVAC_ResSpeed_Data.ini";
    QSettings *ResSpeedINI_File = new QSettings(ResSpeedpath, QSettings::IniFormat);
    ResSpeedINI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    ui->Res_StartDelay->setValue(ResSpeedINI_File->value(PD+"/Res_StartDelay").toDouble());//记录温敏启动延时
    ui->Res_CheckTime->setValue(ResSpeedINI_File->value(PD+"/Res_CheckTime").toDouble());//记录温敏检测时间
    ui->Res_Tem_error->setValue(ResSpeedINI_File->value(PD+"/Res_Tem_error").toDouble());//记录温敏环境误差

    QString Res_EnableString = ResSpeedINI_File->value(PD+"/Res_Enable").toString();//温敏使能
    if(!Res_EnableString.isEmpty())
    {
        QStringList Res_EnableList = Res_EnableString.split(',');
        qDebug()<<"--------------------------------"<<Res_EnableString<<Res_EnableButtonWidgets.count();
        for (int i = 0; i < Res_EnableButtonWidgets.count(); i++) {
            if(Res_EnableList.at(i).toInt())
            {
                //                Res_EnableButtonWidgets[i]->click();
                 qDebug()<<"--------------------------------"<<Res_EnableString;
                Res_EnableWidgets[i] = 1;
                Res_EnableButtonWidgets[i]->setStyleSheet("background-color: rgb(0, 200, 0);");
            }
            else
            {
                Res_EnableWidgets[i] = 0;
                Res_EnableButtonWidgets[i]->setStyleSheet("");
            }
        }
    }

    QString Res_PosNameString = ResSpeedINI_File->value(PD+"/Res_PosName").toString();//温敏名称
    if(!Res_PosNameString.isEmpty())
    {
        QStringList ResPosNameList = Res_PosNameString.split(',');
        for (int i = 0; i < ResNameWidgets.count(); i++) {
            ResNameWidgets[i]->setText(ResPosNameList[i]);
        }
    }

    QString ResTempString = ResSpeedINI_File->value(PD+"/Res_Temp").toString();//温敏XX温度下
    if(!ResTempString.isEmpty())
    {
        QStringList ResTempList = ResTempString.split(',');
        for (int i = 0; i < ResTempWidgets.count(); i++) {
            ResTempWidgets[i]->setValue(ResTempList[i].toDouble());
        }
    }

    QString ResValueString = ResSpeedINI_File->value(PD+"/Res_Value").toString();//温敏阻值
    if(!ResValueString.isEmpty())
    {
        QStringList ResValueList = ResValueString.split(',');
        for (int i = 0; i < ResValueWidgets.count(); i++) {
            ResValueWidgets[i]->setValue(ResValueList[i].toDouble());
        }
    }

    QString ResMaterialConstantString = ResSpeedINI_File->value(PD+"/Res_MaterialConstant").toString();//温敏材料常数
    if(!ResMaterialConstantString.isEmpty())
    {
        QStringList ResMaterialConstantList = ResMaterialConstantString.split(',');
        for (int i = 0; i < ResMaterialConstantWidgets.count(); i++) {
            ResMaterialConstantWidgets[i]->setValue(ResMaterialConstantList[i].toDouble());
        }
    }

    QString ResMaxValueString = ResSpeedINI_File->value(PD+"/Res_MaxValue").toString();//温敏上限
    if(!ResMaxValueString.isEmpty())
    {
        QStringList ResMaxValueList = ResMaxValueString.split(',');
        for (int i = 0; i < ResMaxValueWidgets.count(); i++) {
            ResMaxValueWidgets[i]->setValue(ResMaxValueList[i].toDouble());
        }
    }

    QString ResMinValueString = ResSpeedINI_File->value(PD+"/Res_MinValue").toString();//温敏下限
    if(!ResMinValueString.isEmpty())
    {
        QStringList ResMinValueList = ResMinValueString.split(',');
        for (int i = 0; i < ResMinValueWidgets.count(); i++) {
            ResMinValueWidgets[i]->setValue(ResMinValueList[i].toDouble());
        }
    }

    //--------------------------风速--------------------------
    ui->Speed_CheckTime->setValue(ResSpeedINI_File->value(PD+"/Speed_CheckTime").toDouble());

    QString Speed_EnableString = ResSpeedINI_File->value(PD+"/Speed_Enable").toString();//风速使能
    if(!Speed_EnableString.isEmpty())
    {
        QStringList Speed_EnableList = Speed_EnableString.split(',');
        for (int i = 0; i < Speed_EnableWidgets.count(); i++) {
            if(Speed_EnableWidgets[i]==1)
            {
                //                Speed_EnableButtonWidgets[i]->click();
                Speed_EnableWidgets[i] = 1;
                Speed_EnableButtonWidgets[i]->setStyleSheet("background-color: rgb(0, 200, 0);");
            }
            else
            {
                Speed_EnableWidgets[i] = 0;
                Speed_EnableButtonWidgets[i]->setStyleSheet("");
            }
        }
    }

    QString Speed_PosNameString = ResSpeedINI_File->value(PD+"/Speed_Name").toString();//风速名称
    if(!Speed_PosNameString.isEmpty())
    {
        QStringList Speed_PosNameList = Speed_PosNameString.split(',');
        for (int i = 0; i < SpeedNameWidgets.count(); i++) {
            SpeedNameWidgets[i]->setText(Speed_PosNameList[i]);
        }
    }

    QString SpeedMode1String = ResSpeedINI_File->value(PD+"/SpeedMode1MaxMinValue").toString();//风速1上下限
    if(!SpeedMode1String.isEmpty())
    {
        QStringList SpeedMode1List = SpeedMode1String.split(',');
        for (int i = 0; i < SpeedMode1MaxMinValueWidgets.count(); i++) {
            SpeedMode1MaxMinValueWidgets[i]->setValue(SpeedMode1List[i].toDouble());
        }
    }

    QString SpeedMode2String = ResSpeedINI_File->value(PD+"/SpeedMode2MaxMinValue").toString();//风速2上下限
    if(!SpeedMode2String.isEmpty())
    {
        QStringList SpeedMode2List = SpeedMode2String.split(',');
        for (int i = 0; i < SpeedMode2MaxMinValueWidgets.count(); i++) {
            SpeedMode2MaxMinValueWidgets[i]->setValue(SpeedMode2List[i].toDouble());
        }
    }

    QString SpeedMode3String = ResSpeedINI_File->value(PD+"/SpeedMode3MaxMinValue").toString();//风速3上下限
    if(!SpeedMode3String.isEmpty())
    {
        QStringList SpeedMode3List = SpeedMode3String.split(',');
        for (int i = 0; i < SpeedMode3MaxMinValueWidgets.count(); i++) {
            SpeedMode3MaxMinValueWidgets[i]->setValue(SpeedMode3List[i].toDouble());
        }
    }

    QString SpeedMode4String = ResSpeedINI_File->value(PD+"/SpeedMode4MaxMinValue").toString();//风速4上下限
    if(!SpeedMode4String.isEmpty())
    {
        QStringList SpeedMode4List = SpeedMode4String.split(',');
        for (int i = 0; i < SpeedMode4MaxMinValueWidgets.count(); i++) {
            SpeedMode4MaxMinValueWidgets[i]->setValue(SpeedMode4List[i].toDouble());
        }
    }

    QString SpeedMode5String = ResSpeedINI_File->value(PD+"/SpeedMode5MaxMinValue").toString();//风速5上下限
    if(!SpeedMode5String.isEmpty())
    {
        QStringList SpeedMode5List = SpeedMode5String.split(',');
        for (int i = 0; i < SpeedMode5MaxMinValueWidgets.count(); i++) {
            SpeedMode5MaxMinValueWidgets[i]->setValue(SpeedMode5List[i].toDouble());
        }
    }

    QString SpeedMode6String = ResSpeedINI_File->value(PD+"/SpeedMode6MaxMinValue").toString();//风速6上下限
    if(!SpeedMode6String.isEmpty())
    {
        QStringList SpeedMode6List = SpeedMode6String.split(',');
        for (int i = 0; i < SpeedMode6MaxMinValueWidgets.count(); i++) {
            SpeedMode6MaxMinValueWidgets[i]->setValue(SpeedMode6List[i].toDouble());
        }
    }

    QString SpeedMode7String = ResSpeedINI_File->value(PD+"/SpeedMode7MaxMinValue").toString();//风速7上下限
    if(!SpeedMode7String.isEmpty())
    {
        QStringList SpeedMode7List = SpeedMode7String.split(',');
        for (int i = 0; i < SpeedMode7MaxMinValueWidgets.count(); i++) {
            SpeedMode7MaxMinValueWidgets[i]->setValue(SpeedMode7List[i].toDouble());
        }
    }

    QString SpeedMode8String = ResSpeedINI_File->value(PD+"/SpeedMode8MaxMinValue").toString();//风速8上下限
    if(!SpeedMode8String.isEmpty())
    {
        QStringList SpeedMode8List = SpeedMode8String.split(',');
        for (int i = 0; i < SpeedMode8MaxMinValueWidgets.count(); i++) {
            SpeedMode8MaxMinValueWidgets[i]->setValue(SpeedMode8List[i].toDouble());
        }
    }
    //-----------------------------负离子-------------------------------
    ui->FLZ_CheckTime->setValue(ResSpeedINI_File->value(PD+"/FLZ_CheckTime").toDouble());
    ui->FLZ_StartDelay->setValue(ResSpeedINI_File->value(PD+"/FLZ_StartDelay").toDouble());
    ui->FLZ_Max_Value->setValue(ResSpeedINI_File->value(PD+"/FLZ_Max_Value").toDouble());
    ui->FLZ_Min_Value->setValue(ResSpeedINI_File->value(PD+"/FLZ_Min_Value").toDouble());


    //----------------------------检测顺序 ini-----------------------------
    QString Equencepath = QApplication::applicationDirPath() + "/HVAC/HVAC_Equence_Data.ini";
    QSettings *EquenceINI_File = new QSettings(Equencepath, QSettings::IniFormat);
    EquenceINI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    QString EquenceString = EquenceINI_File->value(PD+"/Equence").toString();
    if(!EquenceString.isEmpty())
    {
        QStringList EquenceList = EquenceString.split(',');
        for (int i = 0; i < EquenceWidgets.count(); i++) {
            EquenceWidgets[i]->setValue(EquenceList[i].toDouble());
        }
    }

    //--------------------------串口设置界面--------------------

    //    QString PD = "PD"+ui->DataSeting_PD->currentText();
    QString path = QApplication::applicationDirPath() + "/HVAC/SettingData.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));


    ui->Serial_Number->setCurrentText(INI_File->value("Serial_Number").toString());
       ui->Serial_Number2->setCurrentText(INI_File->value("Serial_Number2").toString());
       ui->Serial_Number3->setCurrentText(INI_File->value("Serial_Number3").toString());
       ui->Baud_rate->setValue(INI_File->value("Baud_rate").toDouble());
        ui->Baud_rate_2->setValue(INI_File->value("Baud_rate2").toDouble());
        ui->Baud_rate_3->setValue(INI_File->value("Baud_rate3").toDouble());



    ui->Serial_Num->setCurrentText(INI_File->value(QString::number(1)+"/serialNumber").toString());
    ui->BoardNum->setCurrentText(INI_File->value(QString::number(1)+"/boardNumber").toString());
    INI_File->beginGroup(ui->BoardNum->currentText());
    ui->CBB_posBoard_1->setCurrentText(INI_File->value("CBB_posBoard_1").toString());
    ui->CBB_posBoard_2->setCurrentText(INI_File->value("CBB_posBoard_2").toString());
    ui->CBB_posBoard_3->setCurrentText(INI_File->value("CBB_posBoard_3").toString());
    ui->CBB_posBoard_4->setCurrentText(INI_File->value("CBB_posBoard_4").toString());
    ui->CBB_posBoard_5->setCurrentText(INI_File->value("CBB_posBoard_5").toString());
    ui->CBB_posBoard_6->setCurrentText(INI_File->value("CBB_posBoard_6").toString());
    ui->CBB_posBoard_7->setCurrentText(INI_File->value("CBB_posBoard_7").toString());
    ui->CBB_posBoard_8->setCurrentText(INI_File->value("CBB_posBoard_8").toString());
    INI_File->endGroup();
    INI_File->destroyed();

    ui->Serial_Num_2->setCurrentText(INI_File->value(QString::number(2)+"/serialNumber").toString());
    ui->BoardNum_2->setCurrentText(INI_File->value(QString::number(2)+"/boardNumber").toString());
    INI_File->beginGroup(ui->BoardNum_2->currentText());
    ui->CBB_posBoard_9->setCurrentText(INI_File->value("CBB_posBoard_1").toString());
    ui->CBB_posBoard_10->setCurrentText(INI_File->value("CBB_posBoard_2").toString());
    ui->CBB_posBoard_11->setCurrentText(INI_File->value("CBB_posBoard_3").toString());
    ui->CBB_posBoard_12->setCurrentText(INI_File->value("CBB_posBoard_4").toString());
    ui->CBB_posBoard_13->setCurrentText(INI_File->value("CBB_posBoard_5").toString());
    ui->CBB_posBoard_14->setCurrentText(INI_File->value("CBB_posBoard_6").toString());
    ui->CBB_posBoard_15->setCurrentText(INI_File->value("CBB_posBoard_7").toString());
    ui->CBB_posBoard_16->setCurrentText(INI_File->value("CBB_posBoard_8").toString());
    INI_File->endGroup();
    INI_File->destroyed();

    ui->Serial_Num_3->setCurrentText(INI_File->value(QString::number(3)+"/serialNumber").toString());
    ui->BoardNum_3->setCurrentText(INI_File->value(QString::number(3)+"/boardNumber").toString());
    INI_File->beginGroup(ui->BoardNum_3->currentText());
    ui->CBB_posBoard_17->setCurrentText(INI_File->value("CBB_posBoard_1").toString());
    ui->CBB_posBoard_18->setCurrentText(INI_File->value("CBB_posBoard_2").toString());
    ui->CBB_posBoard_19->setCurrentText(INI_File->value("CBB_posBoard_3").toString());
    ui->CBB_posBoard_20->setCurrentText(INI_File->value("CBB_posBoard_4").toString());
    ui->CBB_posBoard_21->setCurrentText(INI_File->value("CBB_posBoard_5").toString());
    ui->CBB_posBoard_22->setCurrentText(INI_File->value("CBB_posBoard_6").toString());
    ui->CBB_posBoard_23->setCurrentText(INI_File->value("CBB_posBoard_7").toString());
    ui->CBB_posBoard_24->setCurrentText(INI_File->value("CBB_posBoard_8").toString());
    INI_File->endGroup();
    INI_File->destroyed();
    qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    MotorBoard.clear();
    map_BoardPos.clear();

    QVector<Motor> sss;
    sss.append(Motor::PT1);
    sss.append(Motor::PT2);
    sss.append(Motor::PT3);
    sss.append(Motor::PT4);
    sss.append(Motor::PT5);
    sss.append(Motor::PT6);
    sss.append(Motor::PT7);
    sss.append(Motor::PT8);
    sss.append(Motor::PT9);
    sss.append(Motor::PT10);
    sss.append(Motor::PT11);
    sss.append(Motor::PT12);

    QVector<Motor> aaa;
    aaa.append(Motor::RES1);
    aaa.append(Motor::RES2);
    aaa.append(Motor::RES3);
    aaa.append(Motor::RES4);
    aaa.append(Motor::RES5);
    aaa.append(Motor::RES6);
    aaa.append(Motor::RES7);
    aaa.append(Motor::RES8);
    aaa.append(Motor::RES9);
    aaa.append(Motor::RES10);
    aaa.append(Motor::RES11);
    aaa.append(Motor::RES12);
    aaa.append(Motor::RES13);
    aaa.append(Motor::RES14);
    aaa.append(Motor::RES15);
    uchar boardIndex = ui->BoardNum->currentIndex();
    uchar boardIndex1 = ui->BoardNum_2->currentIndex();
    uchar boardIndex2 = ui->BoardNum_3->currentIndex();

    QMap<Motor, uchar> pos;
    QMap<Motor, uchar> pos2;
    QMap<Motor, uchar> pos3;

    for(int i=0; i<24; ++i)
    {
        if("伺服电机板" == list_CBB.at(i)->currentText())
        {
            if(i<8)
            {
                if(sss.isEmpty())
                {
                    return;
                }
                Motor  kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);
                kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);
            }
            else if(i<16)
            {
                if(sss.isEmpty())
                {
                    return;
                }
                Motor kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);

                kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);
            }
            else if(i<24)
            {
                if(sss.isEmpty())
                {
                    return;
                }
                Motor kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

                kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);
            }


        }else if("温敏板" == list_CBB.at(i)->currentText()){
            if(i<8)
            {
                if(aaa.isEmpty())
                {
                    return;
                }
                Motor kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);
            }
            else if(i<16)
            {
                if(aaa.isEmpty())
                {
                    return;
                }
                Motor kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);
            }
            else if(i<24)
            {
                if(aaa.isEmpty())
                {
                    return;
                }
                Motor kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

            }



        }else if("LIN电机板" == list_CBB.at(i)->currentText()){
            if(i<8)
            {
                MotorBoard.insert(Motor::LIN1, boardIndex);
                pos.insert(Motor::LIN1, i);
            }
            else if(i<16)
            {
                MotorBoard.insert(Motor::LIN1, boardIndex1);
                pos2.insert(Motor::LIN1, i-8);
            }
            else if(i<24)
            {
                MotorBoard.insert(Motor::LIN1, boardIndex2);
                pos3.insert(Motor::LIN1, i-16);
            }


        }else if("鼓风机板" == list_CBB.at(i)->currentText()){
            if(i<8)
            {
                MotorBoard.insert(Motor::Blower, boardIndex);
                pos.insert(Motor::Blower, i);
            }
            else if(i<16)
            {
                MotorBoard.insert(Motor::Blower, boardIndex1);
                pos2.insert(Motor::Blower, i-8);
            }
            else if(i<24)
            {
                MotorBoard.insert(Motor::Blower, boardIndex2);
                pos3.insert(Motor::Blower, i-16);
            }


        }
    }
    map_BoardPos.insert(ui->BoardNum->currentIndex(), pos);
    map_BoardPos.insert(ui->BoardNum_2->currentIndex(), pos2);
    map_BoardPos.insert(ui->BoardNum_3->currentIndex(), pos3);

    qDebug()<<MotorBoard<<map_BoardPos;

}
//---------------------------------存储代码-------------------------------------
void DataSetting::on_Save1LinMotor_clicked()//保存Lin1~9电机参数
{

    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_LIN_Data.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    auto temp = QMessageBox::information(this,"提示","是否保存参数",QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        QDateTime time = QDateTime::currentDateTime();
        slot_SaveChangeData("开始存储"+time.toString());
        QString PD = "PD"+ui->DataSeting_PD->currentText();
        //    //----------------------LIN电机------------------------------
        for (int i =1;i<10;i++ )
        {
            if(i<10)
            {
                if(LIN_Main.at(i-1)->LIN_Enable_flag == 1)//记录使能
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Enable",QString::number(1));
                }
                else
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Enable",QString::number(0));
                }

                if(LIN_Main.at(i-1)->LIN_ErrorEnable == 1)//记录误差使能
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_ErrorEnable",QString::number(1));
                }
                else
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_ErrorEnable",QString::number(0));
                }

                if(LIN_Main.at(i-1)->LIN_InitEnable_flag == 1)//记录初始化使能
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_InitEnable",QString::number(1));
                }
                else
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_InitEnable",QString::number(0));
                }

                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Name",LIN_Main.at(i-1)->ui->Set_LIN_Name->text());//记录电机名称
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_RunSpeed",LIN_Main.at(i-1)->ui->Set_LIN_RunSpeed->text());//记录电机运行速度
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_MaxRunTime",LIN_Main.at(i-1)->ui->Set_LIN_MaxRunTime->text());//记录运行最大时间
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_InitDirection",LIN_Main.at(i-1)->LIN_InitDirection_flag);//记录初始化方向
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_errorValue",LIN_Main.at(i-1)->ui->Set_LIN_error->text());//记录误差值
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_NAD",LIN_Main.at(i-1)->ui->Set_LIN_NAD->text());//记录NAD
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Controlid",LIN_Main.at(i-1)->ui->Set_LIN_Controlid->text());//记录控制ID
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Stateid",LIN_Main.at(i-1)->ui->Set_LIN_Stateid->text());//记录状态ID
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Direction",LIN_Main.at(i-1)->LIN_Direction_flag);//记录旋转方向
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_InitValue",LIN_Main.at(i-1)->ui->Set_LIN_InitValue->value());//记录初始化值
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_LINName",QString::number(i));//记录电机原名
                QStringList TimeList;
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time1->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time2->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time3->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time4->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time5->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time6->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time7->value());
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Time",TimeList.join(','));//记录跳转时间
                QStringList StepList;
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step1->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step2->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step3->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step4->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step5->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step6->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step7->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step8->value());
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Step",StepList.join(','));//记录顺序
                QStringList NameList;
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS1_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS2_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS3_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS4_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS5_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS6_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS7_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS8_Name->text();
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_POS_Name",NameList.join(','));//记录POS名称
                QStringList ValueList;
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value1->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value2->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value3->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value4->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value5->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value6->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value7->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value8->text();
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_POS_Value",ValueList.join(','));//记录POS值
            }
        }
    }
    INI_File->destroyed();
    qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
}

void DataSetting::on_Save2LinMotor_clicked()//保存Lin10~12电机参数
{

    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_LIN_Data.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    auto temp = QMessageBox::information(this,"提示","是否保存参数",QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {

        QDateTime time = QDateTime::currentDateTime();
        slot_SaveChangeData("开始存储"+time.toString());
        QString PD = "PD"+ui->DataSeting_PD->currentText();
        //    //----------------------LIN电机------------------------------
        for (int i =10;i<13;i++ )
        {
            if(i<13)
            {
                if(LIN_Main.at(i-1)->LIN_Enable_flag == 1)//记录使能
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Enable",QString::number(1));
                }
                else
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Enable",QString::number(0));
                }

                if(LIN_Main.at(i-1)->LIN_ErrorEnable == 1)//记录误差使能
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_ErrorEnable",QString::number(1));
                }
                else
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_ErrorEnable",QString::number(0));
                }


                if(LIN_Main.at(i-1)->LIN_InitEnable_flag == 1)//记录初始化使能
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_InitEnable",QString::number(1));
                }
                else
                {
                    INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_InitEnable",QString::number(0));
                }

                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Name",LIN_Main.at(i-1)->ui->Set_LIN_Name->text());//记录电机名称
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_RunSpeed",LIN_Main.at(i-1)->ui->Set_LIN_RunSpeed->text());//记录电机运行速度
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_MaxRunTime",LIN_Main.at(i-1)->ui->Set_LIN_MaxRunTime->text());//记录运行最大时间
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_InitDirection",LIN_Main.at(i-1)->LIN_InitDirection_flag);//记录初始化方向
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_errorValue",LIN_Main.at(i-1)->ui->Set_LIN_error->text());//记录误差值
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_NAD",LIN_Main.at(i-1)->ui->Set_LIN_NAD->text());//记录NAD
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Controlid",LIN_Main.at(i-1)->ui->Set_LIN_Controlid->text());//记录控制ID
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Stateid",LIN_Main.at(i-1)->ui->Set_LIN_Stateid->text());//记录状态ID
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Direction",LIN_Main.at(i-1)->LIN_Direction_flag);//记录旋转方向
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_InitValue",LIN_Main.at(i-1)->ui->Set_LIN_InitValue->value());//记录初始化值
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_LINName",QString::number(i));//记录电机原名

                QStringList TimeList;
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time1->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time2->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time3->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time4->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time5->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time6->value());
                TimeList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Time7->value());
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Time",TimeList.join(','));//记录跳转时间
                QStringList StepList;
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step1->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step2->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step3->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step4->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step5->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step6->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step7->value());
                StepList << QString::number(LIN_Main.at(i-1)->ui->Set_LIN_Step8->value());
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_Step",StepList.join(','));//记录步数
                QStringList NameList;
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS1_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS2_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS3_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS4_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS5_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS6_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS7_Name->text();
                NameList << LIN_Main.at(i-1)->ui->LinMotor_POS8_Name->text();
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_POS_Name",NameList.join(','));//记录POS名称
                QStringList ValueList;
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value1->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value2->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value3->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value4->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value5->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value6->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value7->text();
                ValueList << LIN_Main.at(i-1)->ui->Set_LIN_Value8->text();
                INI_File->setValue(PD+"/LIN1_"+QString::number(i)+"_POS_Value",ValueList.join(','));//记录POS值
            }
        }
    }

    qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
}

void DataSetting::on_Save1PTMotor_clicked()//保存PT1~6电机参数
{
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_PT_Data.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    auto temp = QMessageBox::information(this,"提示","是否保存参数",QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        QDateTime time = QDateTime::currentDateTime();
        slot_SaveChangeData("开始存储"+time.toString());
        QString PD = "PD"+ui->DataSeting_PD->currentText();
        for (int i =1;i<7;i++ )
        {
            if(i<7)
            {
                if(Motor_Main.at(i-1)->Motor_Enable_flag == 1)//记录使能
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Enable",QString::number(1));
                }
                else
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Enable",QString::number(0));
                }

                if(Motor_Main.at(i-1)->Motor_PT_Mode_flag == 1)//PT类型：1五线 2两线
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Mode_flag",QString::number(1));
                }
                else
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Mode_flag",QString::number(2));
                }

                if(Motor_Main.at(i-1)->Motor_PT_Direction_flag == 1)//电机方向：1=5~0V  2=0~5V
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Direction_flag",QString::number(1));
                }
                else
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Direction_flag",QString::number(2));
                }

                if(Motor_Main.at(i-1)->Motor_PT_Line2_flag == 1)//两线类型：1=堵转 2=停止
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Line2_flag",QString::number(1));
                }
                else
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Line2_flag",QString::number(2));
                }

                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Name",Motor_Main.at(i-1)->ui->Set_Motor_Name->text());//记录电机名称
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PTName","PT"+QString::number(i));//记录电机原名

                QStringList TimeList;
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_1->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_2->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_3->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_4->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_5->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_6->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_7->value());
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Delay",TimeList.join(','));//记录跳转时间
                QStringList StepList;
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_1->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_2->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_3->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_4->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_5->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_6->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_7->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_8->value());
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Step",StepList.join(','));//记录顺序
                QStringList PosNameList;
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS1_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS2_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS3_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS4_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS5_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS6_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS7_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS8_Text->text();
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_POS_Name",PosNameList.join(','));//记录POS名称
                QStringList MaxValueList;
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_1->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_2->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_3->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_4->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_5->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_6->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_7->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_8->value());
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Max_Value",MaxValueList.join(','));//记录电压上限
                QStringList MinValueList;
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_1->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_2->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_3->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_4->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_5->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_6->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_7->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_8->value());
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Min_Value",MinValueList.join(','));//记录电压下限

                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_MotorNum",Motor_Main.at(i-1)->ui->Set_Motor_Num->value());//电机号
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Run_Max_A",Motor_Main.at(i-1)->ui->Set_Motor_Run_Max_A->value());//记录运行电流上限
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Run_Min_A",Motor_Main.at(i-1)->ui->Set_Motor_Run_Min_A->value());//记录运行电流下限
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Stuck_A",Motor_Main.at(i-1)->ui->Set_Motor_Stuck_A->value());//记录堵转电流
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Start_Delay",Motor_Main.at(i-1)->ui->Set_Motor_Start_Delay->value());//记录启动延时
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Delay_alarm",Motor_Main.at(i-1)->ui->Set_Motor_Delay_alarm->value());//记录延时报警
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Run_MaxTime",Motor_Main.at(i-1)->ui->Set_Motor_Run_MaxTime->value());//记录运行最大时间
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_voltageAvgCount",Motor_Main.at(i-1)->ui->Set_MotorVoltageAvgCount->value());//电压平均次数
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_currentAvgCount",Motor_Main.at(i-1)->ui->Set_MotorCurrentAvgCount->value());//电流平均次数
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Line2Motor_RunTime",Motor_Main.at(i-1)->ui->Set_Line2Motor_RunTime->value());//记录2线电机运行时间
            }
        }
    }
    qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
}

void DataSetting::on_Save2PTMotor_clicked()//保存PT7~12电机参数
{
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_PT_Data.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    auto temp = QMessageBox::information(this,"提示","是否保存参数",QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        QDateTime time = QDateTime::currentDateTime();
        slot_SaveChangeData("开始存储"+time.toString());
        QString PD = "PD"+ui->DataSeting_PD->currentText();
        for (int i =7;i<13;i++ )
        {
            if(i<13)
            {
                if(Motor_Main.at(i-1)->Motor_Enable_flag == 1)//记录使能
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Enable",QString::number(1));
                }
                else
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Enable",QString::number(0));
                }

                if(Motor_Main.at(i-1)->Motor_PT_Mode_flag == 1)//PT类型：1五线 2两线 0不使能
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Mode_flag",QString::number(1));
                }
                else if(Motor_Main.at(i-1)->Motor_PT_Mode_flag == 2)
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Mode_flag",QString::number(2));
                }
                else
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Mode_flag",QString::number(0));
                }

                if(Motor_Main.at(i-1)->Motor_PT_Direction_flag == 1)//电机方向：1=5~0V 2=0~5V 0不选
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Direction_flag",QString::number(1));
                }
                else if(Motor_Main.at(i-1)->Motor_PT_Direction_flag == 2)
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Direction_flag",QString::number(2));
                }
                else
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Direction_flag",QString::number(0));
                }

                if(Motor_Main.at(i-1)->Motor_PT_Line2_flag == 1)//两线类型：1=堵转 2=停止 0 = 不选
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Line2_flag",QString::number(1));
                }
                else if(Motor_Main.at(i-1)->Motor_PT_Line2_flag == 2)
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Line2_flag",QString::number(2));
                }
                else
                {
                    INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PT_Line2_flag",QString::number(0));
                }

                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Name",Motor_Main.at(i-1)->ui->Set_Motor_Name->text());//记录电机名称
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_PTName","PT"+QString::number(i));//记录电机原名

                QStringList TimeList;
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_1->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_2->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_3->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_4->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_5->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_6->value());
                TimeList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Delay_7->value());
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Delay",TimeList.join(','));//记录跳转时间
                QStringList StepList;
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_1->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_2->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_3->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_4->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_5->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_6->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_7->value());
                StepList << QString::number(Motor_Main.at(i-1)->ui->Set_Motor_Steps_8->value());
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Step",StepList.join(','));//记录顺序
                QStringList PosNameList;
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS1_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS2_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS3_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS4_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS5_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS6_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS7_Text->text();
                PosNameList << Motor_Main.at(i-1)->ui->Motor_POS8_Text->text();
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_POS_Name",PosNameList.join(','));//记录POS名称
                QStringList MaxValueList;
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_1->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_2->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_3->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_4->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_5->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_6->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_7->value());
                MaxValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Max_POS_8->value());
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Max_Value",MaxValueList.join(','));//记录电压上限
                QStringList MinValueList;
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_1->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_2->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_3->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_4->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_5->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_6->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_7->value());
                MinValueList << QString::number(Motor_Main.at(i-1)->ui->Set_PtMotor_Min_POS_8->value());
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Min_Value",MinValueList.join(','));//记录电压下限

                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_MotorNum",Motor_Main.at(i-1)->ui->Set_Motor_Num->value());//电机号
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Run_Max_A",Motor_Main.at(i-1)->ui->Set_Motor_Run_Max_A->value());//记录运行电流上限
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Run_Min_A",Motor_Main.at(i-1)->ui->Set_Motor_Run_Min_A->value());//记录运行电流下限
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Stuck_A",Motor_Main.at(i-1)->ui->Set_Motor_Stuck_A->value());//记录堵转电流
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Start_Delay",Motor_Main.at(i-1)->ui->Set_Motor_Start_Delay->value());//记录启动延时
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Delay_alarm",Motor_Main.at(i-1)->ui->Set_Motor_Delay_alarm->value());//记录延时报警
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Run_MaxTime",Motor_Main.at(i-1)->ui->Set_Motor_Run_MaxTime->value());//记录运行最大时间
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_voltageAvgCount",Motor_Main.at(i-1)->ui->Set_MotorVoltageAvgCount->value());//电压平均次数
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_currentAvgCount",Motor_Main.at(i-1)->ui->Set_MotorCurrentAvgCount->value());//电流平均次数
                INI_File->setValue(PD+"/Motor_"+QString::number(i)+"_Line2Motor_RunTime",Motor_Main.at(i-1)->ui->Set_Line2Motor_RunTime->value());//记录2线电机运行时间
            }
        }
    }
    qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

}

void DataSetting::on_SaveBlowerData_clicked()//保存鼓风机，震动，噪音，电子膨胀阀，PTC，PM2.5，AQS
{
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_Blower_Data.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    auto temp = QMessageBox::information(this,"提示","是否保存参数",QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        QDateTime time = QDateTime::currentDateTime();
        slot_SaveChangeData("开始存储"+time.toString());
        QString PD = "PD"+ui->DataSeting_PD->currentText();
        INI_File->setValue(PD+"/Blower_Enable",QString::number(Blower_Enable_flag));//记录鼓风机使能
        INI_File->setValue(PD+"/Blower_Mode",QString::number(Blower_Mode_flag));//记录鼓风机类型 0电压 1PWM 2电阻 3LIN
        INI_File->setValue(PD+"/Blower_Start_Delay",QString::number(ui->Blower_Start_Delay->value()));//记录鼓风机启动延时
        INI_File->setValue(PD+"/Blower_V_Max",QString::number(ui->Blower_V_Max->value()));//记录鼓风机电源电压上限
        INI_File->setValue(PD+"/Blower_V_Min",QString::number(ui->Blower_V_Min->value()));//记录鼓风机电源电压下限
        INI_File->setValue(PD+"/Blower_PWM_HZ",QString::number(ui->Blower_PWM_HZ->value()));//记录鼓风机频率
        QStringList StepList;
        for (int i = 0; i < Blower_StepsWidgets.count(); ++i) {
            StepList << Blower_StepsWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Blower_Step",StepList.join(','));//记录顺序
        //端电压型鼓风机
        QStringList VPosNameList;
        for (int i = 0; i < VBlowerPosNameWidgets.count(); ++i) {
            VPosNameList << VBlowerPosNameWidgets[i]->text();
        }
        INI_File->setValue(PD+"/VoltageBlower_PosName",VPosNameList.join(','));//记录POS名称
        QStringList VoltageList;
        for (int i = 0; i < VBlowerVWidgets.count(); ++i) {
            VoltageList << VBlowerVWidgets[i]->text();
        }
        INI_File->setValue(PD+"/VoltageBlower_Voltage",VoltageList.join(','));//记录端电压
        QStringList VTimeList;
        for (int i = 0; i < VBlowerTimeWidgets.count(); ++i) {
            VTimeList << VBlowerTimeWidgets[i]->text();
        }
        INI_File->setValue(PD+"/VoltageBlower_Time",VTimeList.join(','));//记录端电压时间
        QStringList VMaxAList;
        for (int i = 0; i < VBlowerMaxAWidgets.count(); ++i) {
            VMaxAList << VBlowerMaxAWidgets[i]->text();
        }
        INI_File->setValue(PD+"/VoltageBlower_MaxA",VMaxAList.join(','));//记录端电压电流上限
        QStringList VMinAList;
        for (int i = 0; i < VBlowerMinAWidgets.count(); ++i) {
            VMinAList << VBlowerMinAWidgets[i]->text();
        }
        INI_File->setValue(PD+"/VoltageBlower_MinA",VMinAList.join(','));//记录端电压电流下限
        //PWM型鼓风机

        QStringList PWMPosNameList;
        for (int i = 0; i < PWMBlowerPosNameWidgets.count(); ++i) {
            PWMPosNameList << PWMBlowerPosNameWidgets[i]->text();
        }
        INI_File->setValue(PD+"/PWMBlower_PosName",PWMPosNameList.join(','));//记录POS名称
        QStringList PWMList;
        for (int i = 0; i < PWMBlowerPWMWidgets.count(); ++i) {
            PWMList << PWMBlowerPWMWidgets[i]->text();
        }
        INI_File->setValue(PD+"/PWMBlower_PWM",PWMList.join(','));//记录PWM
        QStringList PWMTimeList;
        for (int i = 0; i < PWMBlowerTimeWidgets.count(); ++i) {
            PWMTimeList << PWMBlowerTimeWidgets[i]->text();
        }
        INI_File->setValue(PD+"/PWMBlower_Time",PWMTimeList.join(','));//记录端电压时间
        QStringList PWMMaxAList;
        for (int i = 0; i < PWMBlowerMaxAWidgets.count(); ++i) {
            PWMMaxAList << PWMBlowerMaxAWidgets[i]->text();
        }
        INI_File->setValue(PD+"/PWMBlower_MaxA",PWMMaxAList.join(','));//记录端电压电流上限
        QStringList PWMMinAList;
        for (int i = 0; i < PWMBlowerMinAWidgets.count(); ++i) {
            PWMMinAList << PWMBlowerMinAWidgets[i]->text();
        }
        INI_File->setValue(PD+"/PWMBlower_MinA",PWMMinAList.join(','));//记录端电压电流下限

        //LIN型鼓风机
        QStringList LINPosNameList;
        for (int i = 0; i < LINBlowerPosNameWidgets.count(); ++i) {
            LINPosNameList << LINBlowerPosNameWidgets[i]->text();
        }
        INI_File->setValue(PD+"/LINBlower_PosName",LINPosNameList.join(','));//记录POS名称
        QStringList LINList;
        for (int i = 0; i < LINBlowerLINWidgets.count(); ++i) {
            LINList << LINBlowerLINWidgets[i]->text();
        }
        INI_File->setValue(PD+"/LINBlower_LIN",LINList.join(','));//记录PWM
        QStringList LINTimeList;
        for (int i = 0; i < LINBlowerTimeWidgets.count(); ++i) {
            LINTimeList << LINBlowerTimeWidgets[i]->text();
        }
        INI_File->setValue(PD+"/LINBlower_Time",LINTimeList.join(','));//记录端电压时间
        QStringList LINMaxAList;
        for (int i = 0; i < LINBlowerMaxAWidgets.count(); ++i) {
            LINMaxAList << LINBlowerMaxAWidgets[i]->text();
        }
        INI_File->setValue(PD+"/LINBlower_MaxA",LINMaxAList.join(','));//记录LIN鼓风机电流上限
        QStringList LINMinAList;
        for (int i = 0; i < LINBlowerMinAWidgets.count(); ++i) {
            LINMinAList << LINBlowerMinAWidgets[i]->text();
        }
        INI_File->setValue(PD+"/LINBlower_MinA",LINMinAList.join(','));//记录LIN鼓风机电流下限

        INI_File->setValue(PD+"/LINBlower_Controlid",ui->Blower_LIN_Controlid->text());//记录鼓风机控制ID
        INI_File->setValue(PD+"/LINBlower_Stateid",ui->Blower_LIN_Stateid->text());//记录鼓风机状态ID
        INI_File->setValue(PD+"/LINBlower_Send_ID",ui->Blower_Send_ID->text());//记录鼓风机发送ID
        INI_File->setValue(PD+"/LINBlower_Read_ID",ui->Blower_Read_ID->text());//记录鼓风机读取ID
        INI_File->setValue(PD+"/LINBlower_RPMcontrastEnable",QString::number(Blower_RPMcontrast_flag));//记录鼓风机转速比对使能
        INI_File->setValue(PD+"/LINBlower_error",ui->Blower_error->value());//记录鼓风机转速误差

        //-------------------------------震动+噪音------------------------------
        INI_File->setValue(PD+"/X_vibration_Enable",X_vibration_Enable_flag);//记录X轴震动使能
        INI_File->setValue(PD+"/Y_vibration_Enable",Y_vibration_Enable_flag);//记录Y轴震动使能
        INI_File->setValue(PD+"/Z_vibration_Enable",Z_vibration_Enable_flag);//记录Z轴震动使能
        INI_File->setValue(PD+"/Noises_Enable",Noises_Enable_flag);//记录噪音使能

        INI_File->setValue(PD+"/Vibration_Delay",ui->vibration_Start_Delay->value());//记录震动启动延时
        INI_File->setValue(PD+"/Vibration_CheckTime",ui->vibration_CheckTime->text());//记录震动检测时间
        INI_File->setValue(PD+"/Noises_Delay",ui->Noises_StartDelay->text());//记录噪音启动延时
        INI_File->setValue(PD+"/Noises_CheckTime",ui->Noises_CheckTime->value());//记录噪音检测时间

        QStringList VibrationPosList;
        for (int i = 0; i < vibrationNameWidgets.count(); ++i) {
            VibrationPosList << vibrationNameWidgets[i]->text();
        }
        INI_File->setValue(PD + "/Vibration_PosName", VibrationPosList.join(','));//记录POS名字

        QStringList XVibrationMaxList;
        for (int i = 0; i < xVibrationMaxWidgets.count(); ++i) {
            XVibrationMaxList << xVibrationMaxWidgets[i]->text();
        }
        INI_File->setValue(PD+"/XVibration_MaxValue",XVibrationMaxList.join(','));//记录X轴震动上限
        QStringList XVibrationMinList;
        for (int i = 0; i < xVibrationMinWidgets.count(); ++i) {
            XVibrationMinList << xVibrationMinWidgets[i]->text();
        }
        INI_File->setValue(PD+"/XVibration_MinValue",XVibrationMinList.join(','));//记录X轴震动下限
        QStringList YVibrationMaxList;
        for (int i = 0; i < yVibrationMaxWidgets.count(); ++i) {
            YVibrationMaxList << yVibrationMaxWidgets[i]->text();
        }
        INI_File->setValue(PD+"/YVibration_MaxValue",YVibrationMaxList.join(','));//记录Y轴震动上限
        QStringList YVibrationMinList;
        for (int i = 0; i < yVibrationMinWidgets.count(); ++i) {
            YVibrationMinList << yVibrationMinWidgets[i]->text();
        }
        INI_File->setValue(PD+"/YVibration_MinValue",YVibrationMinList.join(','));//记录Y轴震动下限
        QStringList ZVibrationMaxList;
        for (int i = 0; i < zVibrationMaxWidgets.count(); ++i) {
            ZVibrationMaxList << zVibrationMaxWidgets[i]->text();
        }
        INI_File->setValue(PD+"/ZVibration_MaxValue",ZVibrationMaxList.join(','));//记录Z轴震动上限
        QStringList ZVibrationMinList;
        for (int i = 0; i < zVibrationMinWidgets.count(); ++i) {
            ZVibrationMinList << zVibrationMinWidgets[i]->text();
        }
        INI_File->setValue(PD+"/ZVibration_MinValue",ZVibrationMinList.join(','));//记录Z轴震动下限
        QStringList NoisesMaxList;
        for (int i = 0; i < 9; ++i) {
            NoisesMaxList << noisesMaxWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Noises_MaxValue",NoisesMaxList.join(','));//记录噪音上限
        QStringList NoisesMinList;
        for (int i = 0; i < noisesMinWidgets.count(); ++i) {
            NoisesMinList << noisesMinWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Noises_MinValue",NoisesMinList.join(','));//记录噪音下限


        //------------------------------电子膨胀阀--------------------------
        INI_File->setValue(PD+"/Expansionvalves_Enable",Expansionvalves_Enable_flag);//记录电子膨胀阀使能
        INI_File->setValue(PD+"/Expansionvalves_Controlid",ui->Expansionvalves_Controlid->text());//记录电子膨胀阀控制ID
        INI_File->setValue(PD+"/Expansionvalves_Stateid",ui->Expansionvalves_Stateid->text());//记录鼓风机发送ID
        INI_File->setValue(PD+"/Expansionvalves_StartDelay",ui->Expansionvalves_StartDelay->text());//记录鼓风机读取ID
        INI_File->setValue(PD+"/Expansionvalves_RunTimer",ui->Expansionvalves_RunTimer->text());//记录鼓风机转速比对使能
        QStringList ExpansionPosNameList;
        for (int i = 0; i < ExpansionPosNameWidgets.count(); ++i) {
            ExpansionPosNameList << ExpansionPosNameWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Expansionvalves_PosName",ExpansionPosNameList.join(','));//记录电子膨胀阀POS名称
        QStringList ExpansionStepList;
        for (int i = 0; i < ExpansionStepWidgets.count(); ++i) {
            ExpansionStepList << ExpansionStepWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Expansionvalves_Step",ExpansionStepList.join(','));//记录电子膨胀阀运行顺序
        QStringList ExpansionTimeList;
        for (int i = 0; i < ExpansionTimeWidgets.count(); ++i) {
            ExpansionTimeList << ExpansionTimeWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Expansionvalves_Time",ExpansionTimeList.join(','));//记录电子膨胀阀跳转时间
        QStringList ExpansionValueList;
        for (int i = 0; i < ExpansionValueWidgets.count(); ++i) {
            ExpansionValueList << ExpansionValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Expansionvalves_Value",ExpansionValueList.join(','));//记录电子膨胀阀值

        //------------------------------PTC--------------------------
        INI_File->setValue(PD+"/PTC_Enable",PTC_Enable_flag);//记录PTC使能
        INI_File->setValue(PD+"/PTC_Controlid",ui->PTC_Controlid->text());//记录PTC控制ID
        INI_File->setValue(PD+"/PTC_Stateid",ui->PTC_Stateid->text());//记录PTC状态ID
        INI_File->setValue(PD+"/PTC_Btl",ui->PTC_Btl->currentIndex());//记录PTC波特率
        INI_File->setValue(PD+"/PTC_Lb",ui->PTC_Lb->currentIndex());//记录鼓风机滤波模式
        INI_File->setValue(PD+"/PTC_Hardware",ui->PTC_Hardware->text());//记录PTC硬件版本
        INI_File->setValue(PD+"/PTC_Software",ui->PTC_Software->text());//记录PTC软件版本
        INI_File->setValue(PD+"/PTC_CheckTime",ui->PTC_CheckTime->text());//记录PTC检测时间
        INI_File->setValue(PD+"/PTC_StartDelay",ui->PTC_StartDelay->text());//记录PTC启动延时

        //------------------------------PM2.5--------------------------
        INI_File->setValue(PD+"/PM25_Enable",PM25_Enable_flag);//记录PM2.5使能
        INI_File->setValue(PD+"/PM25_Ver_Enable",PM25_Ver_Judge_flag);//记录PM2.5版本判断使能
        INI_File->setValue(PD+"/PM25_In_Value",ui->PM25_In_Value->value());//记录PM2.5车内浓度
        INI_File->setValue(PD+"/PM25_In_MaxValue",ui->PM25_In_MaxValue->value());//记录PM2.5车内浓度上限
        INI_File->setValue(PD+"/PM25_In_MinValue",ui->PM25_In_MinValue->value());//记录PM2.5车内浓度下限
        INI_File->setValue(PD+"/PM25_Out_Value",ui->PM25_Out_Value->value());//记录PM2.5车外浓度
        INI_File->setValue(PD+"/PM25_Out_MaxValue",ui->PM25_Out_MaxValue->value());//记录PM2.5车外浓度上限
        INI_File->setValue(PD+"/PM25_Out_MinValue",ui->PM25_Out_MinValue->value());//记录PM2.5车外浓度下限
        INI_File->setValue(PD+"/PM25_errorValue",ui->PM25_errorValue->value());//记录PM2.5浓度差异值
        INI_File->setValue(PD+"/PM25_Software1",ui->PM25_Software1->value());//记录PM2.5版本判断使能
        INI_File->setValue(PD+"/PM25_Software2",ui->PM25_Software2->value());//记录PM2.5版本判断使能

        //------------------------------AQS--------------------------
        INI_File->setValue(PD+"/AQS_Enable",AQS_Enable_flag);//记录AQS使能
        INI_File->setValue(PD+"/AQS_Ver_Enable",AQS_Ver_Judge_flag);//记录AQS版本判断使能
        INI_File->setValue(PD+"/AQS_Stateid",ui->AQS_Stateid->text());//记录AQS状态ID
        INI_File->setValue(PD+"/AQS_Airquality",ui->AQS_Airquality->text());//记录AQS空气质量状态
        INI_File->setValue(PD+"/AQS_Max_Value",ui->AQS_Max_Value->text());//记录AQS空气质量状态上限
        INI_File->setValue(PD+"/AQS_Min_Value",ui->AQS_Min_Value->text());//记录AQS空气质量状态下限
        INI_File->setValue(PD+"/AQS_Software",ui->AQS_Software->text());//记录AQS软件版本
        INI_File->setValue(PD+"/AQS_Hardware",ui->AQS_Hardware->text());//记录AQS硬件版本
        qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    }
}

void DataSetting::on_SaveResData_clicked()//保存温敏，风速，负离子
{
    //-----------------------------温敏--------------------------------
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_ResSpeed_Data.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    auto temp = QMessageBox::information(this,"提示","是否保存参数",QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        QDateTime time = QDateTime::currentDateTime();
        slot_SaveChangeData("开始存储"+time.toString());
        QString PD = "PD"+ui->DataSeting_PD->currentText();

        INI_File->setValue(PD+"/Res_StartDelay",QString::number(ui->Res_StartDelay->value()));//记录温敏启动延时
        INI_File->setValue(PD+"/Res_CheckTime",QString::number(ui->Res_CheckTime->value()));//记录温敏检测时间
        INI_File->setValue(PD+"/Res_Tem_error",QString::number(ui->Res_Tem_error->value()));//记录温敏环境误差

        QStringList Res_EnableList;
        for (int i = 0; i < Res_EnableWidgets.count(); ++i) {
            qDebug() << "温敏" << i << "值：" << Res_EnableWidgets[i];
            Res_EnableList <<QString::number(Res_EnableWidgets[i]);
        }
        INI_File->setValue(PD+"/Res_Enable",Res_EnableList.join(','));//记录温敏使能
        QStringList ResPosNameList;
        for (int i = 0; i < ResPosNameList.count(); ++i) {
            ResPosNameList <<ResNameWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Res_PosName",ResPosNameList.join(','));//记录温敏名称
        QStringList ResTempList;
        for (int i = 0; i < ResTempWidgets.count(); ++i) {
            ResTempList <<ResTempWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Res_Temp",ResTempList.join(','));//记录XX温度下
        QStringList ResValueList;
        for (int i = 0; i < ResValueWidgets.count(); ++i) {
            ResValueList <<ResValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Res_Value",ResValueList.join(','));//记录阻值
        QStringList ResMaterialConstantList;
        for (int i = 0; i < ResMaterialConstantWidgets.count(); ++i) {
            ResMaterialConstantList <<ResMaterialConstantWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Res_MaterialConstant",ResMaterialConstantList.join(','));//记录材料常数
        QStringList ResMaxValueList;
        for (int i = 0; i < ResMaxValueWidgets.count(); ++i) {
            ResMaxValueList <<ResMaxValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Res_MaxValue",ResMaxValueList.join(','));//记录上限
        QStringList ResMinValueList;
        for (int i = 0; i < ResMinValueWidgets.count(); ++i) {
            ResMinValueList <<ResMinValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Res_MinValue",ResMinValueList.join(','));//记录下限

        //-----------------------------风速--------------------------------

        INI_File->setValue(PD+"/Speed_CheckTime",QString::number(ui->Speed_CheckTime->value()));//记录风速检测时间
        QStringList Speed_EnableList;
        for (int i = 0; i < Speed_EnableWidgets.count(); ++i) {
            Speed_EnableList << QString::number( Speed_EnableWidgets[i]);
        }
        INI_File->setValue(PD+"/Speed_Enable",Speed_EnableList.join(','));//风速使能
        QStringList SpeedNameList;
        for (int i = 0; i < SpeedNameWidgets.count(); ++i) {
            SpeedNameList << SpeedNameWidgets[i]->text();
        }
        INI_File->setValue(PD+"/Speed_Name",SpeedNameList.join(','));//风速名称
        QStringList SpeedMode1List;
        for (int i = 0; i < SpeedMode1MaxMinValueWidgets.count(); ++i) {
            SpeedMode1List << SpeedMode1MaxMinValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/SpeedMode1MaxMinValue",SpeedMode1List.join(','));//风速模式1上下限
        QStringList SpeedMode2List;
        for (int i = 0; i < SpeedMode2MaxMinValueWidgets.count(); ++i) {
            SpeedMode2List << SpeedMode2MaxMinValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/SpeedMode2MaxMinValue",SpeedMode2List.join(','));//风速模式2上下限
        QStringList SpeedMode3List;
        for (int i = 0; i < SpeedMode3MaxMinValueWidgets.count(); ++i) {
            SpeedMode3List << SpeedMode3MaxMinValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/SpeedMode3MaxMinValue",SpeedMode3List.join(','));//风速模式3上下限
        QStringList SpeedMode4List;
        for (int i = 0; i < SpeedMode4MaxMinValueWidgets.count(); ++i) {
            SpeedMode4List << SpeedMode4MaxMinValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/SpeedMode4MaxMinValue",SpeedMode4List.join(','));//风速模式4上下限
        QStringList SpeedMode5List;
        for (int i = 0; i < SpeedMode5MaxMinValueWidgets.count(); ++i) {
            SpeedMode5List << SpeedMode5MaxMinValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/SpeedMode5MaxMinValue",SpeedMode5List.join(','));//风速模式5上下限
        QStringList SpeedMode6List;
        for (int i = 0; i < SpeedMode6MaxMinValueWidgets.count(); ++i) {
            SpeedMode6List << SpeedMode6MaxMinValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/SpeedMode6MaxMinValue",SpeedMode6List.join(','));//风速模式6上下限
        QStringList SpeedMode7List;
        for (int i = 0; i < SpeedMode7MaxMinValueWidgets.count(); ++i) {
            SpeedMode7List << SpeedMode7MaxMinValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/SpeedMode7MaxMinValue",SpeedMode7List.join(','));//风速模式7上下限
        QStringList SpeedMode8List;
        for (int i = 0; i < SpeedMode8MaxMinValueWidgets.count(); ++i) {
            SpeedMode8List << SpeedMode8MaxMinValueWidgets[i]->text();
        }
        INI_File->setValue(PD+"/SpeedMode8MaxMinValue",SpeedMode8List.join(','));//风速模式8上下限

        //-----------------------------负离子-------------------------------
        INI_File->setValue(PD+"/FLZ_CheckTime",QString::number(ui->FLZ_CheckTime->value()));//记录负离子检测时间
        INI_File->setValue(PD+"/FLZ_StartDelay",QString::number(ui->FLZ_StartDelay->value()));//记录负离子启动延时
        INI_File->setValue(PD+"/FLZ_Max_Value",QString::number(ui->FLZ_Max_Value->value()));//记录负离子检测上限
        INI_File->setValue(PD+"/FLZ_Min_Value",QString::number(ui->FLZ_Min_Value->value()));//记录负离子检测下限


    }
}

void DataSetting::on_SaveSequenceData_clicked()
{
    //-----------------------------检测顺序--------------------------------
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_Equence_Data.ini";
    QSettings *SetEquenceINI_File = new QSettings(path, QSettings::IniFormat);
    SetEquenceINI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    auto temp = QMessageBox::information(this,"提示","是否保存参数",QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        qDebug()<<QTime::currentTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        QDateTime time = QDateTime::currentDateTime();
        slot_SaveChangeData("开始存储"+time.toString());
        QString PD = "PD"+ui->DataSeting_PD->currentText();

        QStringList EquenceList;
        for (int i = 0; i < EquenceWidgets.count(); ++i) {
            EquenceList <<QString::number(EquenceWidgets[i]->value());
        }
        SetEquenceINI_File->setValue(PD+"/Equence",EquenceList.join(','));//记录顺序
    }
}


void DataSetting::on_pushButton_2_clicked()
{
    QByteArray data = "Hello Serial Port 0";
    //    mainWindow->sendDataToSerial(0, data);
    sendDataToSerial(0,"124");
}


void DataSetting::on_pushButton_3_clicked()
{
    sendDataToSerial(1,"124");
}

void DataSetting::sendDataToSerial(int portIndex, const QByteArray &data)
{
    // 检查端口索引是否存在且已打开
    if (MainWindow::mutualui-> m_workers.contains(portIndex) && MainWindow::mutualui-> m_serialOpened.value(portIndex, false)) {
        SerialPortWorker *worker = MainWindow::mutualui-> m_workers.value(portIndex);
        if (worker) {
            // 使用Qt::QueuedConnection确保线程安全
            QMetaObject::invokeMethod(worker, "writeData",Qt::QueuedConnection,Q_ARG(QByteArray, data));
        }
    } else {
        qDebug() << "Serial port" << portIndex << "is not available or not opened";
    }
}

void DataSetting::on_SaveDataSql_clicked()
{
    QString PD = "PD"+ui->DataSeting_PD->currentText();
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_LIN_Data.ini";
    QSettings *LinINI_File = new QSettings(path, QSettings::IniFormat);
    LinINI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    sqlData[1] = ui->DataSeting_PD->currentText();
    QDateTime time = QDateTime::currentDateTime();
    sqlData[2] = time.toString("hh:mm:ss.zzz");
    for (int i =1;i<13;i++ )
    {
        QString ValueString = LinINI_File->value(PD + "/LIN1_" + QString::number(i) + "_POS_Value").toString();
        QStringList ValueList = ValueString.split(',');
        int errorValue = LinINI_File->value(PD + "/LIN1_" + QString::number(i) + "_errorValue").toInt();
        int baseIndex = (i - 1) * 8; // 计算基础索引
        for (int j = 0; j < 8; j++) {
            double value = ValueList[j].toDouble();
            sqldataLINLimitData[baseIndex + j] = QString::number(value + errorValue) + "、" + QString::number(value - errorValue);
        }
    }
    path = QApplication::applicationDirPath() + "/HVAC/HVAC_PT_Data.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    for (int i =1;i<13;i++ )
    {
        QString PTMaxValue = INI_File->value(PD + "/Motor_" + QString::number(i) + "_Max_Value").toString();
        QString PTMinValue = INI_File->value(PD + "/Motor_" + QString::number(i) + "_Min_Value").toString();
        QStringList PTMaxValueList = PTMaxValue.split(',');
        QStringList PTMinValueList = PTMinValue.split(',');
        int baseIndex = (i - 1) * 8; // 计算基础索引
        for (int j = 0; j < 8; j++) {
            double Maxvalue = PTMaxValueList[j].toDouble();
            double Minvalue = PTMinValueList[j].toDouble();
            sqldataLINLimitData[baseIndex + j] = QString::number(Maxvalue) + "、" + QString::number(Minvalue);
        }
    }
    path = QApplication::applicationDirPath() + "/HVAC/HVAC_Blower_Data.ini";
    QSettings *BlowerINI_File = new QSettings(path, QSettings::IniFormat);
    BlowerINI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    QString BlowerMaxValue;
    QString BlowerMinValue;
    if(BlowerINI_File->value(PD+"/Blower_Mode").toInt()==1)//记录鼓风机类型 1电压 2PWM 3LIN
    {
        BlowerMaxValue = BlowerINI_File->value(PD+"/VoltageBlower_MaxA").toString();//记录端电压电流上限
        BlowerMinValue = BlowerINI_File->value(PD+"/VoltageBlower_MinA").toString();//记录端电压电流下限
    }
    else if (BlowerINI_File->value(PD+"/Blower_Mode").toInt()==2)
    {
        BlowerMaxValue = BlowerINI_File->value(PD+"/PWMBlower_MaxA").toString();//记录PWM电流上限
        BlowerMinValue = BlowerINI_File->value(PD+"/PWMBlower_MinA").toString();//记录PWM电流下限

    }
    else if (BlowerINI_File->value(PD+"/Blower_Mode").toInt()==3)
    {
        BlowerMaxValue = BlowerINI_File->value(PD+"/LINBlower_MaxA").toString();//记录LIN电流上限
        BlowerMinValue = BlowerINI_File->value(PD+"/LINBlower_MinA").toString();//记录LIN电流下限
    }
    QStringList BlowerMaxValueList = BlowerMaxValue.split(',');
    QStringList BlowerMinValueList = BlowerMinValue.split(',');
    for (int j = 0; j < 8; j++) {
        double Maxvalue = BlowerMaxValueList[j].toDouble();
        double Minvalue = BlowerMinValueList[j].toDouble();
        sqldataBlowerLimitData[j] = QString::number(Maxvalue) + "、" + QString::number(Minvalue);
    }

    QString X_vibrationMaxValue = BlowerINI_File->value(PD+"/XVibration_MaxValue").toString();
    QString X_vibrationMinValue = BlowerINI_File->value(PD+"/XVibration_MinValue").toString();
    QStringList X_vibrationMaxValueList = X_vibrationMaxValue.split(',');
    QStringList X_vibrationMinValueList = X_vibrationMinValue.split(',');
    for (int j = 8; j < 16; j++) {
        double Maxvalue = X_vibrationMaxValueList[j].toDouble();
        double Minvalue = X_vibrationMinValueList[j].toDouble();
        sqldataBlowerLimitData[j] = QString::number(Maxvalue) + "、" + QString::number(Minvalue);
    }

    QString Y_vibrationMaxValue = BlowerINI_File->value(PD+"/YVibration_MaxValue").toString();
    QString Y_vibrationMinValue = BlowerINI_File->value(PD+"/YVibration_MinValue").toString();
    QStringList Y_vibrationMaxValueList = Y_vibrationMaxValue.split(',');
    QStringList Y_vibrationMinValueList = Y_vibrationMinValue.split(',');
    for (int j = 16; j < 24; j++) {
        double Maxvalue = Y_vibrationMaxValueList[j].toDouble();
        double Minvalue = Y_vibrationMinValueList[j].toDouble();
        sqldataBlowerLimitData[j] = QString::number(Maxvalue) + "、" + QString::number(Minvalue);
    }

    QString Z_vibrationMaxValue = BlowerINI_File->value(PD+"/ZVibration_MaxValue").toString();
    QString Z_vibrationMinValue = BlowerINI_File->value(PD+"/ZVibration_MinValue").toString();
    QStringList Z_vibrationMaxValueList = Z_vibrationMaxValue.split(',');
    QStringList Z_vibrationMinValueList = Z_vibrationMinValue.split(',');
    for (int j = 24; j < 32; j++) {
        double Maxvalue = Z_vibrationMaxValueList[j].toDouble();
        double Minvalue = Z_vibrationMinValueList[j].toDouble();
        sqldataBlowerLimitData[j] = QString::number(Maxvalue) + "、" + QString::number(Minvalue);
    }

    QString Noises_MaxValue = BlowerINI_File->value(PD+"/Noises_MaxValue").toString();
    QString Noises_MinValue = BlowerINI_File->value(PD+"/Noises_MinValue").toString();
    QStringList Noises_MaxValueList = Noises_MaxValue.split(',');
    QStringList Noises_MinValueList = Noises_MinValue.split(',');
    for (int j = 32; j < 40; j++) {
        double Maxvalue = Noises_MaxValueList[j].toDouble();
        double Minvalue = Noises_MinValueList[j].toDouble();
        sqldataBlowerLimitData[j] = QString::number(Maxvalue) + "、" + QString::number(Minvalue);
    }

    path = QApplication::applicationDirPath() + "/HVAC/HVAC_ResSpeed_Data.ini";
    QSettings *ResINI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    QString Res_MaxValue = ResINI_File->value(PD+"/Res_MaxValue").toString();
    QString Res_MinValue = ResINI_File->value(PD+"/Res_MinValue").toString();
    QStringList Res_MaxValueList = Res_MaxValue.split(',');
    QStringList Res_MinValueList = Res_MinValue.split(',');
    for (int j = 40; j < 48; j++) {
        double Maxvalue = Noises_MaxValueList[j].toDouble();
        double Minvalue = Noises_MinValueList[j].toDouble();
        sqldataBlowerLimitData[j] = QString::number(Maxvalue) + "、" + QString::number(Minvalue);
    }
}


void DataSetting::on_Save_configuration_clicked()
{
    QString PD = "PD"+ui->DataSeting_PD->currentText();
    QString path = QApplication::applicationDirPath() + "/HVAC/SettingData.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    INI_File->setValue("Serial_Number", ui->Serial_Number->currentText());
    INI_File->setValue("Serial_Number2", ui->Serial_Number2->currentText());
    INI_File->setValue("Serial_Number3", ui->Serial_Number3->currentText());
    INI_File->setValue("Baud_rate", ui->Baud_rate->value());
    INI_File->setValue("Baud_rate2", ui->Baud_rate_2->value());
    INI_File->setValue("Baud_rate3", ui->Baud_rate_3->value());



    INI_File->beginGroup(ui->BoardNum->currentText());
    INI_File->setValue("serialNumber", ui->Serial_Num->currentText());
    INI_File->setValue("boardNumber", ui->BoardNum->currentText());
    INI_File->setValue("CBB_posBoard_1", ui->CBB_posBoard_1->currentText());
    INI_File->setValue("CBB_posBoard_2", ui->CBB_posBoard_2->currentText());
    INI_File->setValue("CBB_posBoard_3", ui->CBB_posBoard_3->currentText());
    INI_File->setValue("CBB_posBoard_4", ui->CBB_posBoard_4->currentText());
    INI_File->setValue("CBB_posBoard_5", ui->CBB_posBoard_5->currentText());
    INI_File->setValue("CBB_posBoard_6", ui->CBB_posBoard_6->currentText());
    INI_File->setValue("CBB_posBoard_7", ui->CBB_posBoard_7->currentText());
    INI_File->setValue("CBB_posBoard_8", ui->CBB_posBoard_8->currentText());
    INI_File->endGroup();
    INI_File->destroyed();

    INI_File->beginGroup(ui->BoardNum_2->currentText());
    INI_File->setValue("serialNumber", ui->Serial_Num_2->currentText());
    INI_File->setValue("boardNumber", ui->BoardNum_2->currentText());
    INI_File->setValue("CBB_posBoard_1", ui->CBB_posBoard_9->currentText());
    INI_File->setValue("CBB_posBoard_2", ui->CBB_posBoard_10->currentText());
    INI_File->setValue("CBB_posBoard_3", ui->CBB_posBoard_11->currentText());
    INI_File->setValue("CBB_posBoard_4", ui->CBB_posBoard_12->currentText());
    INI_File->setValue("CBB_posBoard_5", ui->CBB_posBoard_13->currentText());
    INI_File->setValue("CBB_posBoard_6", ui->CBB_posBoard_14->currentText());
    INI_File->setValue("CBB_posBoard_7", ui->CBB_posBoard_15->currentText());
    INI_File->setValue("CBB_posBoard_8", ui->CBB_posBoard_16->currentText());
    INI_File->endGroup();
    INI_File->destroyed();

    INI_File->beginGroup(ui->BoardNum_3->currentText());
    INI_File->setValue("serialNumber", ui->Serial_Num_3->currentText());
    INI_File->setValue("boardNumber", ui->BoardNum_3->currentText());
    INI_File->setValue("CBB_posBoard_1", ui->CBB_posBoard_17->currentText());
    INI_File->setValue("CBB_posBoard_2", ui->CBB_posBoard_18->currentText());
    INI_File->setValue("CBB_posBoard_3", ui->CBB_posBoard_19->currentText());
    INI_File->setValue("CBB_posBoard_4", ui->CBB_posBoard_20->currentText());
    INI_File->setValue("CBB_posBoard_5", ui->CBB_posBoard_21->currentText());
    INI_File->setValue("CBB_posBoard_6", ui->CBB_posBoard_22->currentText());
    INI_File->setValue("CBB_posBoard_7", ui->CBB_posBoard_23->currentText());
    INI_File->setValue("CBB_posBoard_8", ui->CBB_posBoard_24->currentText());
    INI_File->endGroup();
    INI_File->destroyed();




    MotorBoard.clear();
    map_BoardPos.clear();

    QVector<Motor> sss;
    sss.append(Motor::PT1);
    sss.append(Motor::PT2);
    sss.append(Motor::PT3);
    sss.append(Motor::PT4);
    sss.append(Motor::PT5);
    sss.append(Motor::PT6);
    sss.append(Motor::PT7);
    sss.append(Motor::PT8);
    sss.append(Motor::PT9);
    sss.append(Motor::PT10);
    sss.append(Motor::PT11);
    sss.append(Motor::PT12);

    QVector<Motor> aaa;
    aaa.append(Motor::RES1);
    aaa.append(Motor::RES2);
    aaa.append(Motor::RES3);
    aaa.append(Motor::RES4);
    aaa.append(Motor::RES5);
    aaa.append(Motor::RES6);
    aaa.append(Motor::RES7);
    aaa.append(Motor::RES8);
    aaa.append(Motor::RES9);
    aaa.append(Motor::RES10);
    aaa.append(Motor::RES11);
    aaa.append(Motor::RES12);
    aaa.append(Motor::RES13);
    aaa.append(Motor::RES14);
    aaa.append(Motor::RES15);

    uchar boardIndex = ui->BoardNum->currentIndex();
    uchar boardIndex1 = ui->BoardNum_2->currentIndex();
    uchar boardIndex2 = ui->BoardNum_3->currentIndex();

    QMap<Motor, uchar> pos;
    QMap<Motor, uchar> pos2;
    QMap<Motor, uchar> pos3;
    for(int i=0; i<24; ++i)
    {
        if("伺服电机板" == list_CBB.at(i)->currentText())
        {
            if(i<8)
            {
                Motor  kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);

                kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);
            }
            else if(i<16)
            {
                Motor kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);

                kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);
            }
            else if(i<24)
            {
                Motor kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

                kind = sss.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);
            }


        }else if("温敏板" == list_CBB.at(i)->currentText()){
            if(i<8)
            {
                Motor kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex);
                pos.insert(kind, i);
            }
            else if(i<16)
            {
                Motor kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex1);
                pos2.insert(kind, i-8);
            }
            else if(i<24)
            {
                Motor kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

                kind = aaa.takeFirst();
                MotorBoard.insert(kind, boardIndex2);
                pos3.insert(kind, i-16);

            }



        }else if("LIN电机板" == list_CBB.at(i)->currentText()){
            if(i<8)
            {
                MotorBoard.insert(Motor::LIN1, boardIndex);
                pos.insert(Motor::LIN1, i);
            }
            else if(i<16)
            {
                MotorBoard.insert(Motor::LIN1, boardIndex1);
                pos2.insert(Motor::LIN1, i-8);
            }
            else if(i<24)
            {
                MotorBoard.insert(Motor::LIN1, boardIndex2);
                pos3.insert(Motor::LIN1, i-16);
            }


        }else if("鼓风机板" == list_CBB.at(i)->currentText()){
            if(i<8)
            {
                MotorBoard.insert(Motor::Blower, boardIndex);
                pos.insert(Motor::Blower, i);
            }
            else if(i<16)
            {
                MotorBoard.insert(Motor::Blower, boardIndex1);
                pos2.insert(Motor::Blower, i-8);
            }
            else if(i<24)
            {
                MotorBoard.insert(Motor::Blower, boardIndex2);
                pos3.insert(Motor::Blower, i-16);
            }


        }
    }
    map_BoardPos.insert(ui->BoardNum->currentIndex(), pos);
    map_BoardPos.insert(ui->BoardNum_2->currentIndex(), pos2);
    map_BoardPos.insert(ui->BoardNum_3->currentIndex(), pos3);

    qDebug()<<MotorBoard<<map_BoardPos;


}

Motor stringToMotor(const QString& motorName) {
    // 创建字符串到枚举值的映射
    static QMap<QString, Motor> motorMap = {
        {"None", Motor::None},
        {"PT1", Motor::PT1},
        {"PT2", Motor::PT2},
        {"PT3", Motor::PT3},
        {"PT4", Motor::PT4},
        {"PT5", Motor::PT5},
        {"PT6", Motor::PT6},
        {"PT7", Motor::PT7},
        {"PT8", Motor::PT8},
        {"PT9", Motor::PT9},
        {"PT10", Motor::PT10},
        {"PT11", Motor::PT11},
        {"PT12", Motor::PT12},
        {"LIN1", Motor::LIN1},
        {"Blower", Motor::Blower},
        {"RES1", Motor::RES1},
        {"RES2", Motor::RES2},
        {"RES3", Motor::RES3},
        {"RES4", Motor::RES4},
        {"RES5", Motor::RES5},
        {"RES6", Motor::RES6},
        {"RES7", Motor::RES7},
        {"RES8", Motor::RES8},
        {"RES9", Motor::RES9},
        {"RES10", Motor::RES10},
        {"RES11", Motor::RES11},
        {"RES12", Motor::RES12},
        {"RES13", Motor::RES13},
        {"RES14", Motor::RES14},
        {"RES15", Motor::RES15}
    };

    // 查找对应的枚举值
    if (motorMap.contains(motorName)) {
        return motorMap.value(motorName);
    } else {
        return Motor::None; // 返回 None 表示无效的电机名称
    }
}

QPair<uchar, uchar> DataSetting::getMotorPosition(const QString& motorName) {
    // 将 QString 转换为 Motor 枚举类型
    Motor motorType = stringToMotor(motorName);

    // 检查转换是否成功
    if (motorType == Motor::None) {
        qDebug() << "无效的电机名称:" << motorName;
        return qMakePair(static_cast<uchar>(255), static_cast<uchar>(255));
    }

    // 检查 MotorBoard 中是否包含指定的电机类型
    if (MotorBoard.contains(motorType)) {
        uchar boardIndex = MotorBoard.value(motorType);

        // 通过板卡索引在 map_BoardPos 中找到对应的位置映射
        if (map_BoardPos.contains(boardIndex)) {
            QMap<Motor, uchar> posMap = map_BoardPos.value(boardIndex);

            if (posMap.contains(motorType)) {
                uchar position = posMap.value(motorType);
                // 返回板卡索引和位置
                return qMakePair(boardIndex, position);
            } else {
                qDebug() << "在板卡" << boardIndex << "中未找到" << motorName << "的位置";
            }
        } else {
            qDebug() << "未找到板卡索引" << boardIndex << "的位置映射";
        }
    } else {
        qDebug() << "未找到" << motorName << "的板卡信息";
    }

    // 如果未找到，返回一个无效值（例如 255, 255）
    return qMakePair(static_cast<uchar>(255), static_cast<uchar>(255));
}



void DataSetting::on_Test1_clicked()
{
    QPair<uchar, uchar> res1Pos = getMotorPosition(ui->lineEdit->text());
    ui->lineEdit_2->setText(QString::number(res1Pos.first));
    ui->lineEdit_3->setText(QString::number(res1Pos.second));
    if (res1Pos.first != 255) {
        qDebug() << ui->lineEdit->text()+"板卡板号:" << res1Pos.first << "ID:" << res1Pos.second;
    }
}

