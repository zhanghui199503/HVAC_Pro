#include "manualui.h"
#include "ui_manualui.h"


Manualui *Manualui_Main;
Manualui::Manualui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manualui)
{
    ui->setupUi(this);
    ManualInit();
}

Manualui::~Manualui()
{
    delete ui;
}

void Manualui::ManualInit()
{
    for(int i = 1;i<31;i++)
    {
        ui->Manual_PDbox->addItems({QString::number(i)});//频道
    }
    this->setWindowTitle("手动界面");
}

void Manualui::Update_show()
{
    ui->Manual_LIN1_1->setStyleSheet(Button_background_color(GetManualValue[0]));
    ui->Manual_LIN1_2->setStyleSheet(Button_background_color(GetManualValue[1]));
    ui->Manual_LIN1_3->setStyleSheet(Button_background_color(GetManualValue[2]));
    ui->Manual_LIN1_4->setStyleSheet(Button_background_color(GetManualValue[3]));
    ui->Manual_LIN1_5->setStyleSheet(Button_background_color(GetManualValue[4]));
    ui->Manual_LIN1_6->setStyleSheet(Button_background_color(GetManualValue[5]));
    ui->Manual_LIN1_7->setStyleSheet(Button_background_color(GetManualValue[6]));
    ui->Manual_LIN1_8->setStyleSheet(Button_background_color(GetManualValue[7]));
    ui->Manual_LIN1_9->setStyleSheet(Button_background_color(GetManualValue[8]));
    ui->Manual_LIN1_10->setStyleSheet(Button_background_color(GetManualValue[9]));
    ui->Manual_LIN1_11->setStyleSheet(Button_background_color(GetManualValue[10]));
    ui->Manual_LIN1_12->setStyleSheet(Button_background_color(GetManualValue[11]));
    ui->Manual_LIN1_13->setStyleSheet(Button_background_color(GetManualValue[12]));
    ui->Manual_LIN1_14->setStyleSheet(Button_background_color(GetManualValue[13]));
    ui->Manual_LIN1_15->setStyleSheet(Button_background_color(GetManualValue[14]));

    ui->Manual_LIN1_1_Now_Value->setValue(GetManualValue[15]);//LIN1-1实时经过步数
    ui->Manual_LIN1_2_Now_Value->setValue(GetManualValue[16]);//LIN1-2实时经过步数
    ui->Manual_LIN1_3_Now_Value->setValue(GetManualValue[17]);//LIN1-3实时经过步数
    ui->Manual_LIN1_4_Now_Value->setValue(GetManualValue[18]);//LIN1-4实时经过步数
    ui->Manual_LIN1_5_Now_Value->setValue(GetManualValue[19]);//LIN1-5实时经过步数
    ui->Manual_LIN1_6_Now_Value->setValue(GetManualValue[20]);//LIN1-6实时经过步数
    ui->Manual_LIN1_7_Now_Value->setValue(GetManualValue[21]);//LIN1-7实时经过步数
    ui->Manual_LIN1_8_Now_Value->setValue(GetManualValue[22]);//LIN1-8实时经过步数
    ui->Manual_LIN1_9_Now_Value->setValue(GetManualValue[23]);//LIN1-9实时经过步数
    ui->Manual_LIN1_10_Now_Value->setValue(GetManualValue[24]);//LIN1-10实时经过步数
    ui->Manual_LIN1_11_Now_Value->setValue(GetManualValue[25]);//LIN1-11实时经过步数
    ui->Manual_LIN1_12_Now_Value->setValue(GetManualValue[26]);//LIN1-12实时经过步数
    ui->Manual_LIN1_13_Now_Value->setValue(GetManualValue[27]);//LIN1-13实时经过步数
    ui->Manual_LIN1_14_Now_Value->setValue(GetManualValue[28]);//LIN1-14实时经过步数
    ui->Manual_LIN1_15_Now_Value->setValue(GetManualValue[29]);//LIN1-15实时经过步数
    
    ui->Manual_LIN1_1_NAD->setText(QString("%1").arg(GetManualValue[30], 0, 16).toUpper());
    ui->Manual_LIN1_1_Controlid->setText(QString("%1").arg(GetManualValue[31], 0, 16).toUpper());
    ui->Manual_LIN1_1_Stateid->setText(QString("%1").arg(GetManualValue[32], 0, 16).toUpper());

    ui->Manual_LIN1_2_NAD->setText(QString("%1").arg(GetManualValue[33], 0, 16).toUpper());
    ui->Manual_LIN1_2_Controlid->setText(QString("%1").arg(GetManualValue[34], 0, 16).toUpper());
    ui->Manual_LIN1_2_Stateid->setText(QString("%1").arg(GetManualValue[35], 0, 16).toUpper());

    ui->Manual_LIN1_3_NAD->setText(QString("%1").arg(GetManualValue[36], 0, 16).toUpper());
    ui->Manual_LIN1_3_Controlid->setText(QString("%1").arg(GetManualValue[37], 0, 16).toUpper());
    ui->Manual_LIN1_3_Stateid->setText(QString("%1").arg(GetManualValue[38], 0, 16).toUpper());

    ui->Manual_LIN1_4_NAD->setText(QString("%1").arg(GetManualValue[39], 0, 16).toUpper());
    ui->Manual_LIN1_4_Controlid->setText(QString("%1").arg(GetManualValue[40], 0, 16).toUpper());
    ui->Manual_LIN1_4_Stateid->setText(QString("%1").arg(GetManualValue[41], 0, 16).toUpper());

    ui->Manual_LIN1_5_NAD->setText(QString("%1").arg(GetManualValue[42], 0, 16).toUpper());
    ui->Manual_LIN1_5_Controlid->setText(QString("%1").arg(GetManualValue[43], 0, 16).toUpper());
    ui->Manual_LIN1_5_Stateid->setText(QString("%1").arg(GetManualValue[44], 0, 16).toUpper());

    ui->Manual_LIN1_6_NAD->setText(QString("%1").arg(GetManualValue[45], 0, 16).toUpper());
    ui->Manual_LIN1_6_Controlid->setText(QString("%1").arg(GetManualValue[46], 0, 16).toUpper());
    ui->Manual_LIN1_6_Stateid ->setText(QString("%1").arg(GetManualValue[47], 0, 16).toUpper());

    ui->Manual_LIN1_7_NAD->setText(QString("%1").arg(GetManualValue[48], 0, 16).toUpper());
    ui->Manual_LIN1_7_Controlid->setText(QString("%1").arg(GetManualValue[49], 0, 16).toUpper());
    ui->Manual_LIN1_7_Stateid->setText(QString("%1").arg(GetManualValue[50], 0, 16).toUpper());

    ui->Manual_LIN1_8_NAD->setText(QString("%1").arg(GetManualValue[51], 0, 16).toUpper());
    ui->Manual_LIN1_8_Controlid->setText(QString("%1").arg(GetManualValue[52], 0, 16).toUpper());
    ui->Manual_LIN1_8_Stateid->setText(QString("%1").arg(GetManualValue[53], 0, 16).toUpper());

    ui->Manual_LIN1_9_NAD->setText(QString("%1").arg(GetManualValue[54], 0, 16).toUpper());
    ui->Manual_LIN1_9_Controlid->setText(QString("%1").arg(GetManualValue[55], 0, 16).toUpper());
    ui->Manual_LIN1_9_Stateid->setText(QString("%1").arg(GetManualValue[56], 0, 16).toUpper());

    ui->Manual_LIN1_10_NAD->setText(QString("%1").arg(GetManualValue[57], 0, 16).toUpper());
    ui->Manual_LIN1_10_Controlid->setText(QString("%1").arg(GetManualValue[58], 0, 16).toUpper());
    ui->Manual_LIN1_10_Stateid->setText(QString("%1").arg(GetManualValue[59], 0, 16).toUpper());

    ui->Manual_LIN1_11_NAD->setText(QString("%1").arg(GetManualValue[60], 0, 16).toUpper());
    ui->Manual_LIN1_11_Controlid->setText(QString("%1").arg(GetManualValue[61], 0, 16).toUpper());
    ui->Manual_LIN1_11_Stateid->setText(QString("%1").arg(GetManualValue[62], 0, 16).toUpper());

    ui->Manual_LIN1_12_NAD->setText(QString("%1").arg(GetManualValue[63], 0, 16).toUpper());
    ui->Manual_LIN1_12_Controlid->setText(QString("%1").arg(GetManualValue[64], 0, 16).toUpper());
    ui->Manual_LIN1_12_Stateid->setText(QString("%1").arg(GetManualValue[65], 0, 16).toUpper());

    ui->Manual_LIN1_13_NAD->setText(QString("%1").arg(GetManualValue[66], 0, 16).toUpper());
    ui->Manual_LIN1_13_Controlid->setText(QString("%1").arg(GetManualValue[67], 0, 16).toUpper());
    ui->Manual_LIN1_13_Stateid->setText(QString("%1").arg(GetManualValue[68], 0, 16).toUpper());

    ui->Manual_LIN1_14_NAD->setText(QString("%1").arg(GetManualValue[69], 0, 16).toUpper());
    ui->Manual_LIN1_14_Controlid->setText(QString("%1").arg(GetManualValue[70], 0, 16).toUpper());
    ui->Manual_LIN1_14_Stateid->setText(QString("%1").arg(GetManualValue[71], 0, 16).toUpper());

    ui->Manual_LIN1_15_NAD->setText(QString("%1").arg(GetManualValue[72], 0, 16).toUpper());
    ui->Manual_LIN1_15_Controlid->setText(QString("%1").arg(GetManualValue[73], 0, 16).toUpper());
    ui->Manual_LIN1_15_Stateid->setText(QString("%1").arg(GetManualValue[74], 0, 16).toUpper());
    

    
    ui->Manual_Tem1->setStyleSheet(Button_background_color(GetManualValue[250]));
    ui->Manual_Tem2->setStyleSheet(Button_background_color(GetManualValue[251]));
    ui->Manual_Tem3->setStyleSheet(Button_background_color(GetManualValue[252]));
    ui->Manual_Tem4->setStyleSheet(Button_background_color(GetManualValue[253]));
    ui->Manual_Tem5->setStyleSheet(Button_background_color(GetManualValue[254]));
    ui->Manual_Tem6->setStyleSheet(Button_background_color(GetManualValue[255]));
    ui->Manual_Tem7->setStyleSheet(Button_background_color(GetManualValue[256]));
    ui->Manual_Tem8->setStyleSheet(Button_background_color(GetManualValue[257]));
    ui->Manual_Tem9->setStyleSheet(Button_background_color(GetManualValue[258]));
    ui->Manual_Tem10->setStyleSheet(Button_background_color(GetManualValue[259]));
    
    ui->Manual_Tem1_Now->setValue(QString::number(GetManualValue[260]/10.0,'f',1).toFloat());
    ui->Manual_Tem2_Now->setValue(QString::number(GetManualValue[261]/10.0,'f',1).toFloat());
    ui->Manual_Tem3_Now->setValue(QString::number(GetManualValue[262]/10.0,'f',1).toFloat());
    ui->Manual_Tem4_Now->setValue(QString::number(GetManualValue[263]/10.0,'f',1).toFloat());
    ui->Manual_Tem5_Now->setValue(QString::number(GetManualValue[264]/10.0,'f',1).toFloat());
    ui->Manual_Tem6_Now->setValue(QString::number(GetManualValue[265]/10.0,'f',1).toFloat());
    ui->Manual_Tem7_Now->setValue(QString::number(GetManualValue[266]/10.0,'f',1).toFloat());
    ui->Manual_Tem8_Now->setValue(QString::number(GetManualValue[267]/10.0,'f',1).toFloat());
    ui->Manual_Tem9_Now->setValue(QString::number(GetManualValue[268]/10.0,'f',1).toFloat());
    ui->Manual_Tem10_Now->setValue(QString::number(GetManualValue[269]/10.0,'f',1).toFloat());

    ui->Manual_NowTem->setValue(QString::number(GetManualValue[270]/1000.0,'f',3).toFloat());
    ui->Manual_Error->setValue(QString::number(GetManualValue[271]/1000.0,'f',3).toFloat());

    ui->Manual_Blower_POS1_A->setValue(QString::number(AutoDataValue[272]/100.0,'f',1).toFloat());//鼓风机1档电流值
    ui->Manual_Blower_POS2_A->setValue(QString::number(AutoDataValue[273]/100.0,'f',1).toFloat());//鼓风机2档电流值
    ui->Manual_Blower_POS3_A->setValue(QString::number(AutoDataValue[274]/100.0,'f',1).toFloat());//鼓风机3档电流值
    ui->Manual_Blower_POS4_A->setValue(QString::number(AutoDataValue[275]/100.0,'f',1).toFloat());//鼓风机4档电流值
    ui->Manual_Blower_POS5_A->setValue(QString::number(AutoDataValue[276]/100.0,'f',1).toFloat());//鼓风机5档电流值
    ui->Manual_Blower_POS6_A->setValue(QString::number(AutoDataValue[277]/100.0,'f',1).toFloat());//鼓风机6档电流值
    ui->Manual_Blower_POS7_A->setValue(QString::number(AutoDataValue[278]/100.0,'f',1).toFloat());//鼓风机7档电流值
    ui->Manual_Blower_POS8_A->setValue(QString::number(AutoDataValue[279]/100.0,'f',1).toFloat());//鼓风机8档电流值
    ui->Manual_Blower_POS9_A->setValue(QString::number(AutoDataValue[280]/100.0,'f',1).toFloat());//鼓风机8档电流值


    ui->Manual_Blower_POS1_V->setValue(QString::number(AutoDataValue[281]/100.0,'f',1).toFloat());//鼓风机1档电流值
    ui->Manual_Blower_POS2_V->setValue(QString::number(AutoDataValue[282]/100.0,'f',1).toFloat());//鼓风机2档电流值
    ui->Manual_Blower_POS3_V->setValue(QString::number(AutoDataValue[283]/100.0,'f',1).toFloat());//鼓风机3档电流值
    ui->Manual_Blower_POS4_V->setValue(QString::number(AutoDataValue[284]/100.0,'f',1).toFloat());//鼓风机4档电流值
    ui->Manual_Blower_POS5_V->setValue(QString::number(AutoDataValue[285]/100.0,'f',1).toFloat());//鼓风机5档电流值
    ui->Manual_Blower_POS6_V->setValue(QString::number(AutoDataValue[286]/100.0,'f',1).toFloat());//鼓风机6档电流值
    ui->Manual_Blower_POS7_V->setValue(QString::number(AutoDataValue[287]/100.0,'f',1).toFloat());//鼓风机7档电流值
    ui->Manual_Blower_POS8_V->setValue(QString::number(AutoDataValue[288]/100.0,'f',1).toFloat());//鼓风机8档电流值
    ui->Manual_Blower_POS9_V->setValue(QString::number(AutoDataValue[289]/100.0,'f',1).toFloat());//鼓风机8档电流值

    ui->Manual_Blower_POS1->setStyleSheet(Button_background_color(GetManualValue[290]));
    ui->Manual_Blower_POS2->setStyleSheet(Button_background_color(GetManualValue[291]));
    ui->Manual_Blower_POS3->setStyleSheet(Button_background_color(GetManualValue[292]));
    ui->Manual_Blower_POS4->setStyleSheet(Button_background_color(GetManualValue[293]));
    ui->Manual_Blower_POS5->setStyleSheet(Button_background_color(GetManualValue[294]));
    ui->Manual_Blower_POS6->setStyleSheet(Button_background_color(GetManualValue[295]));
    ui->Manual_Blower_POS7->setStyleSheet(Button_background_color(GetManualValue[296]));
    ui->Manual_Blower_POS8->setStyleSheet(Button_background_color(GetManualValue[297]));
    ui->Manual_Blower_POS9->setStyleSheet(Button_background_color(GetManualValue[298]));

    ui->Manual_PDbox->setCurrentIndex(GetManualValue[298]-1);

}


void Manualui::on_Manual_ReadTem_clicked()
{
    emit Sign_Set_PLCdata("M", 50,1);
}


//void Manualui::on_Manual_Motor_M1_CW_clicked()
//{
//    if(M1_CW == 0)
//    {
//        M1_CW = 1;
//        emit Sign_Set_PLCdata("Y", 96,1);
//    }
//    else
//    {
//        M1_CW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }

//}
//void Manualui::on_Manual_Motor_M1_CCW_clicked()
//{


//    if(M1_CCW == 0)
//    {
//        M1_CCW = 1;
//        emit Sign_Set_PLCdata("Y", 96,2);
//    }
//    else
//    {
//        M1_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }
//}
//void Manualui::on_Manual_Motor_M2_CW_clicked()
//{
//    if(M2_CW == 0)
//    {
//        M2_CW = 1;
//        emit Sign_Set_PLCdata("Y", 96,4);
//    }
//    else
//    {
//        M2_CW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }

//}
//void Manualui::on_Manual_Motor_M2_CCW_clicked()
//{
//    if(M2_CCW == 0)
//    {
//        M2_CCW = 1;
//        emit Sign_Set_PLCdata("Y", 96,8);
//    }
//    else
//    {
//        M2_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }
//}
//void Manualui::on_Manual_Motor_M3_CW_clicked()
//{
//    if(M3_CW == 0)
//    {
//        M3_CW = 1;
//       emit Sign_Set_PLCdata("Y", 96,16);
//    }
//    else
//    {
//        M3_CW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }

//}
//void Manualui::on_Manual_Motor_M3_CCW_clicked()
//{
//    if(M3_CCW == 0)
//    {
//        M3_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 96,32);
//    }
//    else
//    {
//        M3_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }
////    emit Sign_Set_PLCdata("Y", 96,32);
//}
//void Manualui::on_Manual_Motor_M4_CW_clicked()
//{
//    if(M4_CW == 0)
//    {
//        M4_CW = 1;
//       emit Sign_Set_PLCdata("Y", 96,64);
//    }
//    else
//    {
//        M4_CW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }
////    emit Sign_Set_PLCdata("Y", 96,64);
//}
//void Manualui::on_Manual_Motor_M4_CCW_clicked()
//{
//    if(M4_CCW == 0)
//    {
//        M4_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 96,128);
//    }
//    else
//    {
//        M4_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }
////    emit Sign_Set_PLCdata("Y", 96,128);
//}
//void Manualui::on_Manual_Motor_M5_CW_clicked()
//{
////    emit Sign_Set_PLCdata("Y", 96,256);
//    if(M5_CW == 0)
//    {
//        M5_CW = 1;
//       emit Sign_Set_PLCdata("Y", 96,256);
//    }
//    else
//    {
//        M5_CW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }
//}
//void Manualui::on_Manual_Motor_M5_CCW_clicked()
//{
//    if(M5_CCW == 0)
//    {
//        M5_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 96,512);
//    }
//    else
//    {
//        M5_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }
////    emit Sign_Set_PLCdata("Y", 96,512);
//}
//void Manualui::on_Manual_Motor_M6_CW_clicked()
//{
//    if(M6_CW == 0)
//    {
//        M6_CW = 1;
//       emit Sign_Set_PLCdata("Y", 96,1024);
//    }
//    else
//    {
//        M6_CW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }
////    emit Sign_Set_PLCdata("Y", 96,1024);
//}
//void Manualui::on_Manual_Motor_M6_CCW_clicked()
//{
//    if(M6_CCW == 0)
//    {
//        M6_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 96,2048);
//    }
//    else
//    {
//        M6_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 96,0);
//    }
////    emit Sign_Set_PLCdata("Y", 96,2048);
//}

//void Manualui::on_Manual_Motor_M7_CW_clicked()
//{
//    if(M7_CW == 0)
//    {
//        M7_CW = 1;
//       emit Sign_Set_PLCdata("Y", 320,1);
//    }
//    else
//    {
//        M7_CW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,1);
//}
//void Manualui::on_Manual_Motor_M7_CCW_clicked()
//{
//    if(M7_CCW == 0)
//    {
//        M7_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 320,2);
//    }
//    else
//    {
//        M7_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,2);
//}
//void Manualui::on_Manual_Motor_M8_CW_clicked()
//{
//    if(M8_CW == 0)
//    {
//        M8_CW = 1;
//       emit Sign_Set_PLCdata("Y", 320,4);
//    }
//    else
//    {
//        M8_CW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,4);
//}
//void Manualui::on_Manual_Motor_M8_CCW_clicked()
//{
//    if(M8_CCW == 0)
//    {
//        M8_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 320,8);
//    }
//    else
//    {
//        M8_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,8);
//}
//void Manualui::on_Manual_Motor_M9_CW_clicked()
//{
//    if(M9_CW == 0)
//    {
//        M9_CW = 1;
//       emit Sign_Set_PLCdata("Y",320,16);
//    }
//    else
//    {
//        M9_CW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,16);
//}
//void Manualui::on_Manual_Motor_M9_CCW_clicked()
//{
//    if(M9_CCW == 0)
//    {
//        M9_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 320,32);
//    }
//    else
//    {
//        M9_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,32);
//}
//void Manualui::on_Manual_Motor_M10_CW_clicked()
//{
//    if(M10_CW == 0)
//    {
//        M10_CW = 1;
//       emit Sign_Set_PLCdata("Y", 320,64);
//    }
//    else
//    {
//        M10_CW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,64);
//}
//void Manualui::on_Manual_Motor_M10_CCW_clicked()
//{
////    emit Sign_Set_PLCdata("Y", 320,128);
//    if(M10_CCW == 0)
//    {
//        M10_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 320,128);
//    }
//    else
//    {
//        M10_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
//}
//void Manualui::on_Manual_Motor_M11_CW_clicked()
//{
//    if(M11_CW == 0)
//    {
//        M11_CW = 1;
//       emit Sign_Set_PLCdata("Y", 320,256);
//    }
//    else
//    {
//        M11_CW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,256);
//}
//void Manualui::on_Manual_Motor_M11_CCW_clicked()
//{
//    if(M11_CCW == 0)
//    {
//        M11_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 320,512);
//    }
//    else
//    {
//        M11_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,512);
//}
//void Manualui::on_Manual_Motor_M12_CW_clicked()
//{
//    if(M12_CW == 0)
//    {
//        M12_CW = 1;
//       emit Sign_Set_PLCdata("Y", 320,1024);
//    }
//    else
//    {
//        M12_CW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,1024);
//}
//void Manualui::on_Manual_Motor_M12_CCW_clicked()
//{
//    if(M12_CCW == 0)
//    {
//        M12_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 320,2048);
//    }
//    else
//    {
//        M12_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,2048);
//}
//void Manualui::on_Manual_Motor_M13_CW_clicked()
//{
//    if(M13_CW == 0)
//    {
//        M13_CW = 1;
//       emit Sign_Set_PLCdata("Y", 320,4096);
//    }
//    else
//    {
//        M13_CW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,4096);
//}
//void Manualui::on_Manual_Motor_M13_CCW_clicked()
//{
////    emit Sign_Set_PLCdata("Y", 320,8192);
//    if(M13_CCW == 0)
//    {
//        M13_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 320,8192);
//    }
//    else
//    {
//        M13_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
//}
//void Manualui::on_Manual_Motor_M14_CW_clicked()
//{
////    emit Sign_Set_PLCdata("Y", 320,16384);
//    if(M14_CW == 0)
//    {
//        M14_CW = 1;
//       emit Sign_Set_PLCdata("Y", 320,16384);
//    }
//    else
//    {
//        M14_CW = 0;
//        emit Sign_Set_PLCdata("Y",320,0);
//    }
//}
//void Manualui::on_Manual_Motor_M14_CCW_clicked()
//{
//    if(M14_CCW == 0)
//    {
//        M14_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 320,32768);
//    }
//    else
//    {
//        M14_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 320,0);
//    }
////    emit Sign_Set_PLCdata("Y", 320,32768);
//}
//void Manualui::on_Manual_Motor_M15_CW_clicked()
//{
////    emit Sign_Set_PLCdata("Y", 336,1);
//    if(M15_CW == 0)
//    {
//        M15_CW = 1;
//       emit Sign_Set_PLCdata("Y", 336,1);
//    }
//    else
//    {
//        M15_CW = 0;
//        emit Sign_Set_PLCdata("Y", 336,0);
//    }
//}
//void Manualui::on_Manual_Motor_M15_CCW_clicked()
//{
////    emit Sign_Set_PLCdata("Y", 336,2);
//    if(M15_CCW == 0)
//    {
//        M15_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 336,2);
//    }
//    else
//    {
//        M15_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 336,0);
//    }
//}
//void Manualui::on_Manual_Motor_M16_CW_clicked()
//{
////    emit Sign_Set_PLCdata("Y", 336,4);
//    if(M16_CW == 0)
//    {
//        M16_CW = 1;
//       emit Sign_Set_PLCdata("Y",336,4);
//    }
//    else
//    {
//        M16_CW = 0;
//        emit Sign_Set_PLCdata("Y", 336,0);
//    }
//}
//void Manualui::on_Manual_Motor_M16_CCW_clicked()
//{
////    emit Sign_Set_PLCdata("Y", 336,8);
//    if(M16_CCW == 0)
//    {
//        M16_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 336,8);
//    }
//    else
//    {
//        M16_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 336,0);
//    }
//}
//void Manualui::on_Manual_Motor_M17_CW_clicked()
//{
//    if(M17_CW == 0)
//    {
//        M17_CW = 1;
//        ui->textEdit->append("M17开始正转");
//       emit Sign_Set_PLCdata("Y", 336,16);
//    }
//    else
//    {
//        M17_CW = 0;
//        emit Sign_Set_PLCdata("Y", 336,0);
//    }
////    emit Sign_Set_PLCdata("Y", 336,16);
//}
//void Manualui::on_Manual_Motor_M17_CCW_clicked()
//{
////    emit Sign_Set_PLCdata("Y", 336,32);
//    if(M17_CCW == 0)
//    {
//        M17_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 336,32);
//    }
//    else
//    {
//        M17_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 336,0);
//    }
//}
//void Manualui::on_Manual_Motor_M18_CW_clicked()
//{
////    emit Sign_Set_PLCdata("Y", 336,64);
//    if(M18_CW == 0)
//    {
//        M18_CW = 1;
//       emit Sign_Set_PLCdata("Y", 336,64);
//    }
//    else
//    {
//        M18_CW = 0;
//        emit Sign_Set_PLCdata("Y", 336,0);
//    }
//}
//void Manualui::on_Manual_Motor_M18_CCW_clicked()
//{
////    emit Sign_Set_PLCdata("Y", 336,128);
//    if(M18_CCW == 0)
//    {
//        M18_CCW = 1;
//       emit Sign_Set_PLCdata("Y", 336,128);
//    }
//    else
//    {
//        M18_CCW = 0;
//        emit Sign_Set_PLCdata("Y", 336,0);
//    }
//}

QString Manualui::Button_background_color(int result)
{
    QString result_color = "";
    if(result == 0)
    {
        result_color = "";
    }
    else if(result == 1)
    {
        result_color = "background-color:  rgb(0, 150, 0);";
    }
    else if(result == 2)
    {
        result_color = "background-color:  rgb(250, 250, 0);";
    }
    else if(result == 3)
    {
        result_color = "background-color:  rgb(255, 40, 0);";
    }
    return result_color;
}


void Manualui::on_Manual_LIN1_1_clicked()
{

    emit Sign_Set_PLCdata("D", 17370,ui->Manual_LIN1_1_Value->value());
    emit Sign_Set_PLCdata("M", 3200,1);
}

void Manualui::on_Manual_LIN1_2_clicked()
{
    emit Sign_Set_PLCdata("D", 17371,ui->Manual_LIN1_2_Value->value());
    emit Sign_Set_PLCdata("M", 3208,1);
}

void Manualui::on_Manual_LIN1_3_clicked()
{
    emit Sign_Set_PLCdata("D", 17372,ui->Manual_LIN1_3_Value->value());
    emit Sign_Set_PLCdata("M", 3216,1);
}

void Manualui::on_Manual_LIN1_4_clicked()
{
    emit Sign_Set_PLCdata("D", 17373,ui->Manual_LIN1_4_Value->value());
    emit Sign_Set_PLCdata("M", 3224,1);
}

void Manualui::on_Manual_LIN1_5_clicked()
{
    emit Sign_Set_PLCdata("D", 17374,ui->Manual_LIN1_5_Value->value());
    emit Sign_Set_PLCdata("M", 3620,1);
}

void Manualui::on_Manual_LIN1_6_clicked()
{
    emit Sign_Set_PLCdata("D", 17375,ui->Manual_LIN1_6_Value->value());
    emit Sign_Set_PLCdata("M", 3700,1);
}

void Manualui::on_Manual_LIN1_7_clicked()
{
    emit Sign_Set_PLCdata("D", 17376,ui->Manual_LIN1_7_Value->value());
    emit Sign_Set_PLCdata("M", 3708,1);
}

void Manualui::on_Manual_LIN1_8_clicked()
{
    emit Sign_Set_PLCdata("D", 17377,ui->Manual_LIN1_8_Value->value());
    emit Sign_Set_PLCdata("M", 3716,1);
}

void Manualui::on_Manual_LIN1_9_clicked()
{
    emit Sign_Set_PLCdata("D", 17378,ui->Manual_LIN1_9_Value->value());
    emit Sign_Set_PLCdata("M", 3724,1);
}

void Manualui::on_Manual_LIN1_10_clicked()
{
    emit Sign_Set_PLCdata("D", 17379,ui->Manual_LIN1_10_Value->value());
    emit Sign_Set_PLCdata("M", 3650,1);
}

void Manualui::on_Manual_LIN1_11_clicked()
{
    emit Sign_Set_PLCdata("D", 17380,ui->Manual_LIN1_11_Value->value());
//    emit Sign_Set_PLCdata("M", 3650,1);
}
void Manualui::on_Manual_LIN1_12_clicked()
{
    emit Sign_Set_PLCdata("D", 17381,ui->Manual_LIN1_12_Value->value());
//    emit Sign_Set_PLCdata("M", 3650,1);
}
void Manualui::on_Manual_LIN1_13_clicked()
{
    emit Sign_Set_PLCdata("D", 17382,ui->Manual_LIN1_13_Value->value());
//    emit Sign_Set_PLCdata("M", 3650,1);
}
void Manualui::on_Manual_LIN1_14_clicked()
{
    emit Sign_Set_PLCdata("D", 17383,ui->Manual_LIN1_14_Value->value());
//    emit Sign_Set_PLCdata("M", 3650,1);
}
void Manualui::on_Manual_LIN1_15_clicked()
{
    emit Sign_Set_PLCdata("D", 17384,ui->Manual_LIN1_15_Value->value());
//    emit Sign_Set_PLCdata("M", 3650,1);
}


void Manualui::on_Manual_Lin_Back_clicked()
{
    emit Sign_Set_PLCdata("M", 3150,1);
    emit Sign_Set_PLCdata("M", 1150,1);
}




void Manualui::on_Manual_Blower_POS1_clicked()
{
     emit Sign_Set_PLCdata("M", 111,1);
}
void Manualui::on_Manual_Blower_POS2_clicked()
{
    emit Sign_Set_PLCdata("M", 112,1);
}
void Manualui::on_Manual_Blower_POS3_clicked()
{
    emit Sign_Set_PLCdata("M", 113,1);
}
void Manualui::on_Manual_Blower_POS4_clicked()
{
    emit Sign_Set_PLCdata("M", 114,1);
}
void Manualui::on_Manual_Blower_POS5_clicked()
{
    emit Sign_Set_PLCdata("M", 115,1);
}
void Manualui::on_Manual_Blower_POS6_clicked()
{
    emit Sign_Set_PLCdata("M", 116,1);
}
void Manualui::on_Manual_Blower_POS7_clicked()
{
    emit Sign_Set_PLCdata("M", 117,1);
}
void Manualui::on_Manual_Blower_POS8_clicked()
{
    emit Sign_Set_PLCdata("M", 118,1);
}
void Manualui::on_Manual_Blower_POS9_clicked()
{
    emit Sign_Set_PLCdata("M", 119,1);
}

void Manualui::closeEvent(QCloseEvent *e)
{
    emit Sign_Current_interface_flag(1);
    e->accept();
}

void Manualui::on_Motor_M1_CW_clicked()
{

}

