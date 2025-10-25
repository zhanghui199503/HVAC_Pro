#include "MFormMotor.h"
#include "ui_MFormMotor.h"

MFormMotor::MFormMotor(QWidget *parent,
                       QString title_name,
                       const uchar motor_name,
                       const uchar motor_index,
                       const uchar small_Board_MotorID,
                       const uchar big_Board_MotorID) :
    QGroupBox(parent),
    _titleName(title_name),
    _v_motorName(motor_name),
    _v_motorIndex(motor_index),
    _v_smallBoardMotorID(small_Board_MotorID),
    _v_bigBoardMotorID(big_Board_MotorID),
    ui(new Ui::MFormMotor)
{
    ui->setupUi(this);
    Init_OBJS();

    setTitle(_titleName);

    if(motor_name == EM::PT){
        ui->Frame_PT->setVisible(true);
        ui->Frame_LIN->setVisible(false);
    }else if(motor_name == EM::LIN){

        ui->Frame_PT->setVisible(false);
        ui->Frame_LIN->setVisible(true);
    }
}

MFormMotor::~MFormMotor()
{
    delete ui;
}

void MFormMotor::Init_OBJS()
{
    list_BTN_POS << ui->BTN_POS_1 << ui->BTN_POS_2 << ui->BTN_POS_3 << ui->BTN_POS_4
                 << ui->BTN_POS_5 << ui->BTN_POS_6 << ui->BTN_POS_7 << ui->BTN_POS_8;
}

void MFormMotor::load_FileINI(const QString& path_name, const QString channel)
{
    QSettings *INI_File = new QSettings(path_name, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    INI_File->beginGroup(channel);

    ui->BTN_Motor_Name->setText((INI_File->value(tr("Motor_%1_Name").arg(_v_motorIndex), "电机模式").toString()));

    QString list_default = "POS1,POS2,POS3,POS4,POS5,POS6,POS7,POS8";
    QStringList list = INI_File->value(tr("Motor_%1_POS_Name").arg(_v_motorIndex), list_default).toString().split(',');

    QStringList list_max_value = INI_File->value(tr("Motor_%1_Max_Value").arg(_v_motorIndex), list_default).toString().split(',');
    QStringList list_min_value = INI_File->value(tr("Motor_%1_Min_Value").arg(_v_motorIndex), list_default).toString().split(',');

    for(int i=0; i<8; ++i){
        list_BTN_POS.at(i)->setText(list.at(i));
        v_maxValue[i] = list_max_value.at(i).toFloat();
        v_minValue[i] = list_min_value.at(i).toFloat();
    }
    INI_File->endGroup();
    INI_File->destroyed();
}
/**
 * @brief MFormMotor::slot_clearLED 清除界面颜色
 */
void MFormMotor::slot_clearLED()
{
    ui->BTN_Motor_Name->setStyleSheet("");
    foreach(QPushButton *btn, list_BTN_POS){
        btn->setStyleSheet("");
    }
}
/**
 * @brief MFormMotor::slot_SendMotorStatus 接收电机信息
 * @param Modeltype
 * @param ID
 * @param MotorNum
 * @param CurrentV
 * @param CurrentA
 * @param CurrentPos
 * @param CurrentState
 */
void MFormMotor::slot_SendMotorStatus(QString Modeltype, int ID,int MotorNum,int CurrentV,int CurrentA, int CurrentPos, int CurrentState)
{
    if(_v_bigBoardMotorID == ID && _v_smallBoardMotorID == MotorNum){

        ui->LE_VlotValue->setValue(CurrentV);
        ui->LE_CurrentValue->setValue(CurrentA);


        if(CurrentPos == 9){

            slot_setled(true, 0, CurrentState);

        }else if(CurrentPos > 0 && CurrentPos < 8){

            slot_setled(false, CurrentPos-1, CurrentState);
        }

        if(CurrentPos == 7){

            ui->LE_Motor_Limit_1->setValue(CurrentV);
            ui->LE_Bocking_Curr_1->setValue(CurrentA);

        }else if(CurrentPos == 8){

            ui->LE_Motor_Limit_2->setValue(CurrentV);
            ui->LE_Bocking_Curr_2->setValue(CurrentA);
        }

    }
}
/**
 * @brief MFormMotor::slot_setled
 * @param pos_index
 * @param state
 */
void MFormMotor::slot_setled(bool b_motorClass, const uchar pos_index, const uchar state)
{
    if(b_motorClass){
        if(state == 0x00){

            ui->BTN_Motor_Name->setStyleSheet("background-color: green;");

        }else if(state == 0x01 || state == 0x02){

            ui->BTN_Motor_Name->setStyleSheet("background-color: Yellow;");

        }else if(state == 0x11 || state == 0x12 || state == 0x13 || state == 0x14 || state == 0x15){

            ui->BTN_Motor_Name->setStyleSheet("background-color: red;");

        }else{

            ui->BTN_Motor_Name->setStyleSheet("");
        }
    }else{
        if(state == 0x00){

            list_BTN_POS.at(pos_index)->setStyleSheet("background-color: green;");

        }else if(state == 0x01 || state == 0x02){

            list_BTN_POS.at(pos_index)->setStyleSheet("background-color: Yellow;");

        }else if(state == 0x11 || state == 0x12 || state == 0x13 || state == 0x14 || state == 0x15){

            list_BTN_POS.at(pos_index)->setStyleSheet("background-color: red;");

        }else{

            list_BTN_POS.at(pos_index)->setStyleSheet("");
        }
    }

}
