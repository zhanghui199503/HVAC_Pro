#ifndef THREAD_LINMOTOR_H
#define THREAD_LINMOTOR_H

#include "lin_headres.h"
#include "motor_types.h"
#include <QObject>
#include <QVector>
#include <QDebug>

#define LINMotor_Count 12

class thread_linmotor : public QThread
{
    Q_OBJECT
public:
    //线程状态
    bool threadState;

    static thread_linmotor* getInstance();
protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start（）间接调用
    void run();
private:
     static QMutex m_instanceMutex;      // 单例创建的互斥锁

    int SendDataOK = 0;

    //流程
    int ProcessSteps;

    //临时电机数量
    int MotorNumber = 0;

    //起始电机号
    int MotorStartNumber;

    //结束电机号
    int MotorEndNunber;

    //电机数量
    int MotorToralNumber;

    //当前目标步数
    int Now_targetStep[LINMotor_Count];

    //当前步数误差
    int Now_stepError[LINMotor_Count];

    //当前设置步数
    int Now_setStep[LINMotor_Count];

    //lin电机实时数据
    QList<LINMotor_basis> LINMotor_Data;

    //lin电机总设置
    LINMotorTotal_basis LINMotor_TotalSet;

    //lin电机设置参数
    QList<MY_LINMotorFP_Setting_basis> LINMotorFP_SetData;

    //步骤参数
    QList<QList<MY_LINMotorIP_Setting_basis>> LINMotor_SetData;

    //运行状态（0：待机 1：运行中 2：堵转 3：到位）
    int RunningState[LINMotor_Count];

    // 运行结果（0：无结果 1：ok 2：ng）
    int RunningResult[LINMotor_Count];

    //临时标志位
    int TemporaryFlage[LINMotor_Count];

    //电机运行步骤
    uchar Motor_run_step[LINMotor_Count];

    int run_number = 0;
    int run_number1 = 0;

    bool ProcessEN[LINMotor_Count];

    int Total_Status = 0;
    int Total_Result = 0;

    int my_portIndex = 1;
    int ProcessStepsTime = 0;//线程超时

    bool init_readFixed = false;
    bool readFixed_en = false;

    void sendDataToSerial(int portIndex, const QByteArray &data);
    void addFixedToSerial(int portIndex, const QByteArray &data,bool *_en);
private slots:
    //电机初始化
    int InitRun(int _Motot_N);

    //编址完成
    int Addressing_OK();

    //电机状态
    int MotorRunStatus(int _Motor_N);

    //电机运行结果
    int MotorRunResult(int _Motor_N);

    //电机数量判断
    int MotorNumberJudge();

    //电机状态创建
    void MotorInitStatus();

    //总电机初始化运行
    int MotorTotalInitRun();

    //单个电机初始化运行
    int MotorSingleInitRun(int _Motor_N);

    //电机参数读取
    void ReadMotorState();

    //电机版本信息读取
    int ReadMotorVersion(int _Motor_N);

    //控制单个电机停止
    int sendMotorStopProtocol(int _Motor_N);
public slots:
    //电机总参数设置
    void SetMotor_TotalSetting(LINMotorTotal_basis _set);


    void ProcessStop();//线程复位

    //全部电机停止运行
    void AllStop();

    //步骤参数设置
    void SetLINMotor_ProcessSet(QList<QList<MY_LINMotorIP_Setting_basis>> _set);

    //电机基本参数设置 true:配置成功 开始编址 false:
    bool SetMotorFP_Setting(QList<MY_LINMotorFP_Setting_basis> _set);

//     int run_funtion(int _Motor_N,QList<QList<MY_LINMotorIP_Setting_basis>> _set);

     //保存电机控制指令
     QByteArray SaveRunProtocol(int _Cintrl, int _Step, int _other);

    //通讯协议：运行指令
    int sendRunProtocol(QByteArray buff_send_data1, int Contrl);

    //通讯协议：电机初始化
    int sendMotorInitRunProtocol();

    //通讯协议：电机参数
    int sendMotorParameter(int _Motor_N);

    //通讯协议：编址指令
    int sendMotorAddressingProtocol();

//    QString Str_motorName[LINMotor_Count] = {"Lin1","Lin2","Lin3","Lin4","Lin5","Lin6","Lin7","Lin8","Lin9","Lin10","Lin11","Lin12"};

    void resetStatus();//复位结果状态

    void DataProcessing(QByteArray _reData, int _MotorID);//数据的处理

    LINMotorTotal_basis reBasicParameters();//读取参数

    QList<LINMotor_Return> reLinRealTimeData();//读取电机实时数据

    int getProcessStatus();//获取整体的状态
    int getProcessResult();//获取整体结果

    void restProcessResultAndStatus();//复位整体的结果和状态

    //Process启动停止
    void MotorRunProcess(int _Motor_N, bool _Enable);
//---------------------------------------------------------------------------------------------------------------------------------------------------
    //手动模式控制电机初始化
    void Manual_Init(int _MotorID, int _SetStep);

    //手动模式控制电机运行到目标步数
    void Manual_Run(int _MotorID, int _TargetStep);

    //手动模式走左极限 left limit
    void Manual_LeftLimitRun(int _MotorID);

    //手动模式走右极限 Right limit
    void Manual_RightLimitRun(int _MotorID);

signals:
    void MotorParameterSend_emit(int number);//电机参数发送信号
    void addressing_emit();                  //电机编址信号
    void MotorActuation_emit(int _MotorID, int _MotorContrl);              //电机作动信号
};

extern thread_linmotor* Nthread_linmotor;

#endif // THREAD_LINMOTOR_H
