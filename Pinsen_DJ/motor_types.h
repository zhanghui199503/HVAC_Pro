#ifndef MOTOR_TYPES_H
#define MOTOR_TYPES_H

#include <QString>
#include <QList>

struct PTMotorFP_Setting_basis
{
    bool b_Received = true;
    QString m_COM;                    //串口号
    int m_Borad;                    //板号
    int m_id;                    //id号
    bool m_motorEnabled;         // 电机使能状态 (Motor_X_Enable)
    int m_motorNumber;           // 电机号 (1-2)
    QString m_name;              // 电机名称
    int m_PTmotorMode;           //PT类型区分5线和2线
    int m_motorType;             // 电机类型 (根据 PT_Mode_flag 和 PT_Line2_flag 判断)
    int m_motorDirection;        // 电机方向 (Motor_X_PT_Direction_flag)
    int m_towmotortype;          // 两线类型
    int m_currentUpperLimit;     // 电流上限(毫安)
    int m_currentLowerLimit;     // 电流下限(毫安)
    int m_stallCurrent;          // 堵转电流(毫安)
    int m_startDelayMs;          // 启动延时时间(毫秒)
    int m_alarmDelayMs;          // 报警延时时间(毫秒)
    int m_timeoutMs;             // 超时时间(秒) (Motor_X_Run_MaxTime)
    double m_line2MotorRunTime;  // 2线电机运行时间
    int m_voltageAvgCount;       // 默认电压平均次数
    int m_currentAvgCount;       // 默认电流平均次数
};

struct PTMotorFP_Setting_basis1
{
    QString m_PTName;            //PT名字
    QString m_POS;               //POS顺序
    QString m_MaxValue;          //上限
    QString m_MinValue;          //下限
    QString m_Time;              //跳转
};

struct PTMotor_Current_Status
{
    float positionVoltageV = 0;//位置电压
    int presentCurrentmA = 0;//当前电流mA
    float runningTimeS = 0;//运行时间（s）
    char status = -1;//状态
};

// 其他结构体定义...
struct LINMotorFP_Setting_basis
{
    int m_id;                    //id号
    bool m_motorEnabled;         //电机使能状态
    bool m_motorerrEnabled;      //步数误差使能状态
    bool m_motorInitEnabled;     //初始化使能
    QString m_name;              //电机名称
    int m_motorRunSpeed;         //电机运行速度
    int m_motorMaxtimer;         //电机运行最大时间
    bool m_motorInitDirection;   //电机初始化方向
    int m_motorStepErrValue;     //步数误差值
    QString m_motorNAD;          //电机NAD
    QString m_motorControlid;    //电机控制ID
    QString m_motorStateid;      //电机状态ID
    int m_motorOther;            //电机旋转方向，应急运行位置,应急运行释放
    int m_motorInitValue;        //初始化使能位置
};

struct LINMotorFP_Setting_basis1
{
    QString m_LINName;           //LIN名字
    QString m_POS;               //POS顺序
    QString m_Value;             //值
    QString m_Time;              //跳转
};

struct Blower_Setting_basis
{
    int m_Blowerid;                //id号
    bool m_BlowerEnabled;          //鼓风机使能状态
    int m_BlowerMode;              //鼓风机类型
    QString m_BlowerStartDelay;     //鼓风机名称
    int m_BlowerPowervoltageUP;    //鼓风机电源电压上限
    int m_BlowerPowervoltageDown;  //鼓风机电源电压下限
    QString m_BlowerRate;          //鼓风机频率
    QString m_LINBlowerControlid;  //控制ID
    QString m_LINBlowerStateid;    //状态ID
    QString m_LINBlowerSendid;     //发送ID
    QString m_LINBlowerReadid;     //读取ID
    bool m_LINBlowerSpeed_Compare;  //转速比对使能
    int m_LINBlowerErrorValue;     //转速比对误差值
    bool m_X_vibration_Enable;          //X轴震动使能状态
    bool m_Y_vibration_Enable;          //Y轴震动使能状态
    bool m_Z_vibration_Enable;          //Z轴震动使能状态
    bool m_Noises_Enable;          //噪音使能状态
    double m_vibration_StartDelay; //启动延时
    double m_vibration_DelayAlarm; //震动报警延时
    double m_Noises_StartDelay; //噪音启动延时
    double m_Noises_DelayAlarm; //噪音震动报警延时
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

struct Res_Setting_basis
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
#endif // MOTOR_TYPES_H
