 #include "mainwindow.h"
#include "thread_main.h"
#include "thread_CommTask.h"

#include "FormLogShow.h"

#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QObject>


#include <QElapsedTimer>

#ifndef HEADERS1_H
#define HEADERS1_H


class LINMotorTotal_basis
{
public:
    bool Addressing_Enable = 0;//编址使能
    int m_motortargetStepError = 0;//目标步数误差

    int m_motorStartMotor = 0;//起始电机号
    int m_motorTotoalNumber = 0;//作动电机数
    uint SoftwareVersion = 0;//软件版本
    uint HardwareVersion = 0;//硬件版本
    uint BoardType = 0;      //板子类型

    bool Manual_Automatic = false;//手自动
};


struct LINMotor_Return//公有
{
    //电机版本号
    char m_motorSWID = 0;
    char m_motorHWID = 0;
    char m_motorVariantID = 0;
    char m_motorJEID = 0;
    char16_t m_motorSupID = 0;
    char16_t m_motorFunID = 0;

    int m_ProcessStatus[8] = {0};//挡位状态 //0:无状态 1：运行 2：OK 3：NG
    int m_ProcessStep[8] = {0};//步数
    bool show_flag[8] = {0};

    int m_TotalStatus = 0;//总状态 状态：停止为0，运行为1
    int m_TotalResult = 0;//结果：默认是0，OK为1，NG为错误代码
    int CurrentStep = 0;//电机实时步数
};



struct LINMotor_basis//私有读取
{
    //状态
    int m_state = 0;

    int m_AddressingState = 0;//编址状态 0：未编址 1：编址完成 2：编址失败 3：编址中
    int m_InitState = 0;//初始化状态     0：未初始化 1：初始化完成 2：初始化失败 3：初始化中

    //电机错误代码
    int ErrorCode = 0;

    //电压错误 1：欠压 2：过压
    int VoltageError = 0;

    //电气错误 1：有故障 2:永久故障
    int ElectrError = 0;

    //过温
    bool TempError = 0;

    //断线错误
    bool DisconnectError = 0;

    //响应错误
    bool PresentError = 0;

    //超时
    bool RunTimeOut = 0;

};

//通用参数，每个电机独立，与步骤无关
class MY_LINMotorFP_Setting_basis
{
public:
    //电机初始化使能
    bool m_motorInitRunEnabled;//初始化使能

    int m_motorInitRunDir;//初始化运行的方向 0：无 1：大端 2：小端
    //电机初始化设置步数
    int m_motorInitRunSetStep;

    // 电机使能状态
    bool m_motorEnabled;//电机使能

    //电机NAD
    int m_motorNAD;

    //电机控制ID
    int m_motorContrlID;

    //电机状态ID
    int m_motorStatusID;

    //电机运行速度
    int m_motorSpeed;

    // 电机方向 (true:正转 false:反转)
    bool m_motorDirection;

    //堵转使能更改
    bool m_motorLockedrotorChange;

    //励磁使能
    bool m_motorExcitation;

    //应急使能
    bool m_motorEmren;

    //应急方向
    bool m_motorEmrDir;

    //运行时间
    uint m_motorRunTime;

    //步数误差
    int m_motorStepError;
};

//控制类型
#define POSITION_CONTROL 1
#define LIMIT_CONTROL 2
class MY_LINMotorIP_Setting_basis//设置参数
{
public:
    int process;

//    //控制类型 1：位置 2：左极限 3：右极限 4：初始化 5：设置步数  6：停止 0：无
//    uchar controlType;

    //目标步数
    int m_motortargetStep;

    //设置步数
    int m_motorSetStep;

    // 停止时间
    int m_stopTime;
};

#endif // LIN_HEADRES_H
