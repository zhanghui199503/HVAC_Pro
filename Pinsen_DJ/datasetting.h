#ifndef DATASETTING_H
#define DATASETTING_H

#include <QWidget>
#include "Header_File.h"



//LIN电机设置界面
#include "lin_dataset.h"
#include "ui_lin_dataset.h"

//电机设置界面
#include "motor_dataset.h"
#include "ui_motor_dataset.h"

enum Motor{
    None,
    PT1,
    PT2,
    PT3,
    PT4,
    PT5,
    PT6,
    PT7,
    PT8,
    PT9,
    PT10,
    PT11,
    PT12,

    LIN1,
    Blower,
    RES1,
    RES2,
    RES3,
    RES4,
    RES5,
    RES6,
    RES7,
    RES8,
    RES9,
    RES10,
    RES11,
    RES12,
    RES13,
    RES14,
    RES15
};


class SerialConfigWidget;

namespace Ui {
class DataSetting;
}

class DataSetting : public QWidget
{
    Q_OBJECT

public:
    explicit DataSetting(QWidget *parent = nullptr);
    ~DataSetting();
    Ui::DataSetting *ui;
//    LIN_Dataset
     QList<LIN_Dataset *> LIN_Main;
     QList<Motor_Dataset *> Motor_Main;

     QList<QComboBox*> list_CBB;

     int Blower_Enable_flag = 0;//使能 1 不使能0
     int Blower_Mode_flag = 0;//1电压 2PWM 3LIN
     int Blower_LINMoode_flag = 0;//0电压 1PWM 2电阻 3LIN
     int Blower_RPMcontrast_flag =0;//转速比对 使能1 0使能
     int Expansionvalves_Enable_flag = 0;//电子膨胀阀 使能 1 不使能0
     int Speed_Cylinder1Enable_flag=0,Speed_Cylinder2Enable_flag=0,Speed_Cylinder3Enable_flag=0,Speed_Cylinder4Enable_flag=0,Speed_Cylinder5Enable_flag=0,Speed_Cylinder6Enable_flag=0,Speed_Cylinder7Enable_flag=0,Speed_Cylinder8Enable_flag=0,Speed_Cylinder9Enable_flag=0,Speed_Cylinder10Enable_flag=0;
     int SpeedEnable_flag=0,Speed1Enable_flag=0,Speed2Enable_flag=0,Speed3Enable_flag=0,Speed4Enable_flag=0,Speed5Enable_flag=0,Speed6Enable_flag=0,Speed7Enable_flag=0,Speed8Enable_flag=0,Speed9Enable_flag=0,Speed10Enable_flag=0,Speed11Enable_flag=0,Speed12Enable_flag=0;
     int SpeedMode1Enable_flag=0,SpeedMode2Enable_flag=0,SpeedMode3Enable_flag=0,SpeedMode4Enable_flag=0,SpeedMode5Enable_flag=0,SpeedMode6Enable_flag=0,SpeedMode7Enable_flag=0,SpeedMode8Enable_flag=0;
     int ResEnable_flag=0,Res1Enable_flag=0,Res2Enable_flag=0,Res3Enable_flag=0,Res4Enable_flag=0,Res5Enable_flag=0,Res6Enable_flag=0,Res7Enable_flag=0,Res8Enable_flag=0,Res9Enable_flag=0,Res10Enable_flag=0,Res11Enable_flag=0,Res12Enable_flag=0,Res13Enable_flag=0,ResSurroundingsEnable_flag =0;
     int Arrive_AutoCheck_Enable_flag =0;//到位自动检测 使能 1 不使能0
     int Automatic_mating_Enable_flag =0;// 自动对插使能 1 不使能0
     int LIN_WriteID_Enable_flag =0;// LIN 电机刷写使能 1 不使能0
     int Speed_contrast_Enable_flag = 0;// 对比检测 使能 1 不使能0
     int PM25_Enable_flag = 0;// PM2.5 使能 1 不使能0
     int PM25_Ver_Judge_flag = 0;// PM2.5 使能 1 不使能0
     int AQS_Enable_flag = 0;// AQS 使能 1 不使能0
     int AQS_Ver_Judge_flag = 0;// AQS 使能 1 不使能0
     int PTC_Enable_flag = 0;// AQS 使能 1 不使能0

     int Noises_Enable_flag = 0,FLZ_Enable_flag = 0,FLZ_A_Enable_flag = 0;// 噪音检测 使能 1 不使能0
     int X_vibration_Enable_flag = 0,Y_vibration_Enable_flag = 0,Z_vibration_Enable_flag = 0,vibration_Enable_flag = 0;//X轴，Y轴，Z轴，单轴

      int Read_Write_Mode ;//读写模式标志位 读0 写1

      QMap<uchar, uchar> MotorBoard;
      QMap<uchar, QMap<Motor, uchar>> map_BoardPos;

      QPair<uchar, uchar> getMotorPosition(const QString& motorName);

private:

public slots:
    void Main_Init();//界面初始化
//    void Update_show();//界面刷新
    void closeEvent(QCloseEvent *e);//界面关闭事件
    void functChanged();//测试

    void slot_SaveChangeData(QString);

    void Read_inifile();

    void UI_init();

    void SaveLimitData();

    void sendDataToSerial(int portIndex, const QByteArray &data);
private slots:
    void on_NextPage_clicked();

    void on_BackPage_clicked();

    void on_SaveData_clicked();

    void on_pushButton_clicked();

    void on_Set_Blower_V_clicked();

    void on_Set_Blower_PWM_clicked();

    void on_Set_Blower_LIN_clicked();

    void on_Set_Blower_Enable_clicked();

    void on_Set_Blower_RPMcontrast_clicked();

    void on_Expansionvalves_Enable_clicked();

    void on_Res_Enable_clicked();

    void on_Res1_Enable_clicked();

    void on_Res2_Enable_clicked();

    void on_Res3_Enable_clicked();

    void on_Res4_Enable_clicked();

    void on_Res5_Enable_clicked();

    void on_Res6_Enable_clicked();

    void on_Res7_Enable_clicked();

    void on_Res8_Enable_clicked();

    void on_Res9_Enable_clicked();

    void on_Res10_Enable_clicked();

    void on_Speed_contrast_Enable_clicked();

    void on_Noises_Enable_clicked();

    void on_FLZ_Enable_clicked();

    void on_SetMain_WriteMode_clicked();

    void on_PM25_Enable_clicked();

    void on_AQS_Enable_clicked();

    void on_FLZ_A_Enable_clicked();

    void on_SetMain_ReadMode_clicked();

    void on_DataSeting_PD_currentTextChanged(const QString &arg1);

    void on_X_vibration_Enable_clicked();

    void on_Y_vibration_Enable_clicked();

    void on_Z_vibration_Enable_clicked();

    void on_Speed_Cylinder1_Enable_clicked();

    void on_Speed_Cylinder2_Enable_clicked();

    void on_Speed_Cylinder3_Enable_clicked();

    void on_Speed_Cylinder4_Enable_clicked();

    void on_Speed_Cylinder5_Enable_clicked();

    void on_Speed_Cylinder6_Enable_clicked();

    void on_Speed_Cylinder7_Enable_clicked();

    void on_Speed_Cylinder8_Enable_clicked();


    void on_Speed_Enable_clicked();

    void on_Speed1_Enable_clicked();
    void on_Speed2_Enable_clicked();
    void on_Speed3_Enable_clicked();
    void on_Speed4_Enable_clicked();
    void on_Speed5_Enable_clicked();
    void on_Speed6_Enable_clicked();
    void on_Speed7_Enable_clicked();
    void on_Speed8_Enable_clicked();


    void on_Speed_Mode1_Enable_clicked();
    void on_Speed_Mode2_Enable_clicked();
    void on_Speed_Mode3_Enable_clicked();
    void on_Speed_Mode4_Enable_clicked();
    void on_Speed_Mode5_Enable_clicked();
    void on_Speed_Mode6_Enable_clicked();
    void on_Speed_Mode7_Enable_clicked();
    void on_Speed_Mode8_Enable_clicked();

    void on_PTC_Enable_clicked();

    void on_PTC_Btl_currentIndexChanged(int index);

    void on_PTC_Lb_currentIndexChanged(int index);

    void on_ResSurroundings_Enable_clicked();

    void on_LIN_WriteID_Enable_clicked();

    void on_PM25_Ver_Judge_clicked();

    void on_AQS_Ver_Judge_clicked();

    void on_ComboardNum_textChanged(const QString &arg1);

    void on_Serial_Num_currentTextChanged(const QString &arg1);

    void on_Save1LinMotor_clicked();

    void on_Save2LinMotor_clicked();

    void on_Save1PTMotor_clicked();

    void on_Save2PTMotor_clicked();

    void on_SaveBlowerData_clicked();

    void on_SaveResData_clicked();

    void on_SaveSequenceData_clicked();

    void on_Res11_Enable_clicked();

    void on_Res12_Enable_clicked();

    void on_Res13_Enable_clicked();

    void on_Start_Connect_clicked();

    void on_Start_Connect_2_clicked();

    void on_Start_Connect_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_SaveDataSql_clicked();

    void on_Save_configuration_clicked();

    void on_Test1_clicked();

signals:
    void Sign_Current_interface_flag(int index);//当前界面标志位 频道界面：2
    void Sign_Set_PLCdata(QString unit, int address,int value);//发送设置
    void Sign_Set_PLCWriteMode();//发送设置写模式
    void Sign_Set_PLCReadMode();//发送设置读模式
    void Sign_Set_Mode(int index);//发送设置模式到设置界面
    void Sign_Set_PLCdataPoint(QString unit, int address,int value);//发送设置

    // 当用户点击开始连接按钮时发出的信号，包含所有串口参数
    void connectRequested(const QString &portName, qint32 baudRate,
                         QSerialPort::DataBits dataBits,
                         QSerialPort::Parity parity,
                         QSerialPort::StopBits stopBits);

};
extern DataSetting *Data_Set;

#endif // DATASETTING_H
