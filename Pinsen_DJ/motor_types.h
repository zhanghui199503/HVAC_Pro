#ifndef MOTOR_TYPES_H
#define MOTOR_TYPES_H

#include <QString>
#include <QList>


#define M_PT        1
#define M_STEP      2
#define M_LIN       3
#define R_TEM       4
#define BLOWER      5


struct PTMotorFP_Setting_basis
{
    bool b_Received = true;
    QString m_COM;                    //串口号
    int m_Borad = 0;                   //板号
    int m_id = 0;                    //id号
    bool m_motorEnabled = false;        // 电机使能状态 (Motor_X_Enable)
    int m_motorNumber = 0;          // 电机号 (1-2)
    QString m_name;              // 电机名称
    int m_PTmotorMode = 0;           //PT类型区分5线和2线
    int m_motorType = 0;             // 电机类型 (根据 PT_Mode_flag 和 PT_Line2_flag 判断)
    int m_motorDirection = 0;        // 电机方向 (Motor_X_PT_Direction_flag)
    int m_towmotortype = 0;          // 两线类型
    int m_currentUpperLimit = 0;     // 电流上限(毫安)
    int m_currentLowerLimit = 0;    // 电流下限(毫安)
    int m_stallCurrent = 0;          // 堵转电流(毫安)
    int m_startDelayMs = 0;          // 启动延时时间(毫秒)
    int m_alarmDelayMs = 0;          // 报警延时时间(毫秒)
    int m_timeoutMs = 0;             // 超时时间(秒) (Motor_X_Run_MaxTime)
    double m_line2MotorRunTime = 0;  // 2线电机运行时间
    int m_voltageAvgCount = 0;      // 默认电压平均次数
    int m_currentAvgCount = 0;       // 默认电流平均次数
};

struct PTMotorFP_Setting_basis1
{
    bool en = false;//使能
    QString m_PTName = "";            //PT名字
    QString m_POS = "";                //POS顺序
    QString m_MaxValue = "";           //上限
    QString m_MinValue = "";          //下限
    QString m_Time = "";               //跳转
};

struct PTMotor_Current_Status
{
    float positionVoltageV = 0;//位置电压
    int presentCurrentmA = 0;//当前电流mA
    float runningTimeS = 0;//运行时间（s）
    char status = -1;//状态
};

struct PTMotorFP_Status_basis
{
    double Current_V = 0;//实时电压
    double Current_A = 0;//实时电流
    int m_TotalStatus= 0;//总状态 状态：停止为0，运行为1
    int m_TotalResult= 0;//结果：默认是0，OK为1，NG为错误代码
    int POSStatus[8] = {0};//档位状态 0：未运行 1：RUN 2：OK 3：NG
    double V_UpperLimit[8] = {0};//电压上限
    double V_LowerLimit[8] = {0};//电压下限
    double POS_V[8] = {0};//电压
    double POS_A[8] = {0};//电流
    bool show_flag[8] = {0};//显示完成状态,功能模块在启动时复位，这个POS显现完成后主流程置为true

    uchar m_type[8] = {0}; //0:pos 1:左极限 2：右极限
};


// 其他结构体定义...
struct LINMotorFP_Setting_basis
{
    int m_id=0;                    //id号


    bool m_motorEnabled=false;          //电机使能状态
    bool m_motorerrEnabled=false;       //步数误差使能状态
    bool m_motorInitEnabled=false;       //初始化使能
    QString m_name="";                //电机名称
    int m_motorRunSpeed=0;           //电机运行速度
    int m_motorMaxtimer=0;           //电机运行最大时间
    bool m_motorInitDirection;   //电机初始化方向
    int m_motorStepErrValue=0;       //步数误差值
    QString m_motorNAD="";            //电机NAD
    QString m_motorControlid="";      //电机控制ID
    QString m_motorStateid="";       //电机状态ID
    int m_motorOther=0;             //电机旋转方向，应急运行位置,应急运行释放
    int m_motorInitValue=0;         //初始化使能位置
};

struct LINMotorFP_Setting_basis1
{
    QString m_LINName="";             //LIN名字
    QString m_POS="";                //POS顺序
    QString m_Value="";               //值
    QString m_Time="";               //跳转
};

struct Blower_Setting_basis
{
    int m_Blowerid = 0;                //id号
    bool m_BlowerEnabled = false;          //鼓风机使能状态
    int m_BlowerMode = 0;              //鼓风机类型
    QString m_BlowerStartDelay;     //鼓风机名称
    double m_BlowerPowervoltageUP = 0;    //鼓风机电源电压上限
    double m_BlowerPowervoltageDown = 0;  //鼓风机电源电压下限
    QString m_BlowerRate;          //鼓风机频率
    QString m_LINBlowerControlid;  //控制ID
    QString m_LINBlowerStateid;    //状态ID
    QString m_LINBlowerSendid;     //发送ID
    QString m_LINBlowerReadid;     //读取ID
    bool m_LINBlowerSpeed_Compare = false;  //转速比对使能
    double m_LINBlowerErrorValue = 0;     //转速比对误差值
    bool m_X_vibration_Enable = false;          //X轴震动使能状态
    bool m_Y_vibration_Enable = false;          //Y轴震动使能状态
    bool m_Z_vibration_Enable = false;          //Z轴震动使能状态
    bool m_Noises_Enable = false;          //噪音使能状态
    double m_vibration_StartDelay=0; //启动延时
    double m_vibration_DelayAlarm=0; //震动报警延时
    double m_Noises_StartDelay=0; //噪音启动延时
    double m_Noises_DelayAlarm=0; //噪音震动报警延时
};

struct Blower_Setting_basis1
{
    QString m_POS;   //POS顺序
    QString m_Type;  //类型
    QString m_Value; //端电压，占空比，转速
    QString m_Time;  //运行时间
    QString m_BlowerMaxValue;  //上限
    QString m_BlowerMinValue;  //下限
    QString m_X_vibrationrMaxValue;  //上限
    QString m_X_vibrationrMinValue;  //下限
    QString m_Y_vibrationMaxValue;  //上限
    QString m_Y_vibrationMinValue;  //下限
    QString m_Z_vibrationMaxValue;  //上限
    QString m_Z_vibrationMinValue;  //下限
    QString m_NoisesMaxValue;  //上限
    QString m_NoisesMinValue;  //下限
};

struct ToralThermistor_Setting_basis
{
    int m_Borad = 0;//版号
    int RunTime = 0;//检测时间(100ms 单位)
    int DelayTime = 0.0;//启动延时时间
    bool Compare_Enable = false;//对比检测使能
    double temperature_Err = 0.0;//温度误差
};

struct Thermistor_Setting_basis
{
    bool Environment = false;//环境电阻使能
    bool Temperature_Enable = false;//温敏电阻使能
    double RC = 0.0;    //温度
    double Beta = 0.0;  //B值 材料常数
    double R25 = 0.0;   //温度下的阻值
    double Temperature_upper = 0.0;//温度上限
    double Temperature_lower = 0.0;//温度下限
};

//负离子设置
struct Anion_etting_basis
{
    int m_Borad = 0;//板号
    int CtrID = 0;
    int StatusID = 0;
    QString SendData[8] = {""};//发送的数据
    QString Compare[8] = {""};//对比报文
    bool CompareEnable[8] = {false};//对比使能
};

#endif // MOTOR_TYPES_H
