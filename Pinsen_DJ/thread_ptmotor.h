#ifndef THREAD_PTMOTOR_H
#define THREAD_PTMOTOR_H


#include <QObject>
#include <QList>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QSettings>
#include <QApplication>
#include <QTextCodec>


#include "motor_types.h"  // 包含独立的类型定义
#include "thread_CommTask.h"


#define PtMotor_Count 12

class thread_ptmotor : public QObject
{
    Q_OBJECT

public:
    explicit thread_ptmotor(QObject *parent = nullptr);
    ~thread_ptmotor();

    QTimer *DelayTimer;

    static thread_ptmotor* getInstance();


    //读取参数
    float Volt;//实时电压
    int Current;//实时电流
    int m_state;// 状态（可表示电机的运行状态，如0-停止、1-运行、2-故障等）
    float m_runningTimeSec;// 运行时间（秒）
    bool m_runningDirection;//运行方向
    //写参数
    QString m_name;//电机名称
    int m_motorType;// 电机类型 (1:5线 2:2线堵转 3:2线停止)
    bool m_motorEnabled;// 电机使能状态
    bool m_motorDirection;// 电机方向 (true:正转 false:反转)
    int m_timeoutS;// 超时时间(秒)
    double m_voltageDeviation;// 电压偏差值(伏特)
    int m_stallCurrent;// 堵转电流(毫安)
    int m_currentUpperLimit;// 电流上限(毫安)
    int m_currentLowerLimit;// 电流下限(毫安)
    int m_startDelayMs;// 启动延时时间(毫秒)
    int m_alarmDelayMs;// 报警延时时间(毫秒)
    int m_voltageAvgCount;// 电压平均次数
    int m_currentAvgCount;// 电流平均次数
    int m_motornum; //电机号


    //    uchar controlType;//控制类型 1：位置 2：极限
    double m_targetVoltageUpper;// 目标电压上限(伏特)
    double m_targetVoltageLower;// 目标电压下限(伏特)
    int m_stopTime;// 停止时间
    // 线程状态
    bool threadState;


    // 设置数据
    void setPTMotorSettings(QList<PTMotorFP_Setting_basis> settings);
    void setPTMotorSettings1(QList<PTMotorFP_Setting_basis1> settings1);





    int Received_Success =1;//接收成功标志位
    bool All_Ptmotors_Success =false;//所有电机参数设置成功

    int Motor_state[PtMotor_Count] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};    //状态值
    uchar v_posIndex[12] = {0};    //状态值

//    uchar PtMotorOver[12][1] = {{0}};


    int POS_Over[PtMotor_Count][8]={{0}};//记录POS
    int Pt[PtMotor_Count] = {0};
    int Receive_Flag[PtMotor_Count] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int motor_ProcessStep[PtMotor_Count] = {0};  // 每个电机的处理步骤
    int motor_nowprocess[PtMotor_Count] = {0};   // 每个电机的当前处理POS
    bool motor_Enabled[PtMotor_Count] = {false}; // 电机使能状态
    int ProcessSteps = 0;
    bool ProcessStart_flag = true;

    bool my_Recevie_flag[PtMotor_Count] = {false};

public slots:
    void doWork();//线程工作函数
    void Receive_DataProcessing(QByteArray Data,int index);//接收数据处理
    void SendPtMotorFixedParameter(QString PTName,int PT_ID,int Broad_type,int Motor_Num,int StartDelay,int AlarmDelay,int V_AverageCount,int A_AverageCount,int RunDirection);//发送电机固定参数
    void SendPtMotorOperation(QString PTName,int PT_ID,int Broad_type,int Motor_Num,int PositionVoltage_UpperLimit,int PositionVoltage_LowerLimit,int PositionCurrent_UpperLimit,int PositionCurrent_LowerLimit,int TimeOut);//发送电机运行到POS
    void SendPtMotorDetectionOpening(QString PTName,int PT_ID,int Broad_type,int Motor_Num,int Direction,int PositionVoltage_UpperLimit,int PositionVoltage_LowerLimit,int LockedCurrent,int PositionCurrent_LowerLimit,int TimeOut);//发送电机检测开度
    void SendPtMotorStop(QString PTName,int PT_ID,int Broad_type,int Motor_Num);//发送电机停止
    void ReadPtMotorStatus(QString PTName,int PT_ID,int Broad_type,int Motor_Num);//读取电机状态
    void SendPtMotorRun(QString PTName, int PT_ID, int Broad_type, int Motor_Num,int Direction,int RunTime);//发送电机运行
    void ReceiveRunMotor(QString PTName);//接受运行电机
    void StartDelayTime(int DelayTimer);

    void DetermineCurrentMotor(QString ID,QString ID_Num);//确定当前电机


    void MotorParameterInit();//电机参数初始化


    bool SendDetectionOpeningCommand(int motorIndex);//发送检测开启命令
    bool SendRunPOSCommand(int motorIndex);//发送运行POS命令
    bool CheckMotorCompletion(int motorIndex);//检查电机完成情况
    bool ProcessDelayAndNext(int motorIndex);//处理延迟与下一步


    void sendDataToSerial(int portIndex, const QByteArray &data);//发送数据到串口


    void InitPtData();//初始化电机数据

    void testRunData();

    QList<PTMotorFP_Status_basis> reLinRealTimeData();



    void addFixedToSerial(int portIndex, const QByteArray &data,bool *_en);
    void Start_ReadState(int _pt_num);
    void Stop_ReadState(int _pt_num);

    int getProcessStatus();//获取整体状态
    int getProcessResult();//获取整体结果
    void ResetProcessStatusAndResult();
    void ResetDisplayData();

    void ProcessStop();//步骤停止

signals:
    // 可以添加需要的信号
    void workFinished();
    void errorOccurred(const QString &error);

    void SendData(QString Name,QByteArray data);

    void SendMotortatus(QString Modeltype,int ID,int MotorNum,int CurrentV,int CurrentA,int CurrentPos,int CurrentState);
    void SendData1(QByteArray data);
protected:


private:
    static QMutex m_instanceMutex;      // 单例创建的互斥锁

    bool init_readFixed[PtMotor_Count] = {false};
    bool readFixed_en[PtMotor_Count] = {false};

    // 可以添加其他私有成员
    QList<PTMotorFP_Setting_basis> m_ptMotorSettings;
    QList<PTMotorFP_Setting_basis1> m_ptMotorSettings1;
    QList<PTMotorFP_Status_basis> m_ptMotorStatus;


    bool UpData_ShowValue[PtMotor_Count][8] = {{true}};

    double delayTime[PtMotor_Count] = {0};

    QElapsedTimer Deley_Elaps[PtMotor_Count];//发送后等待完成时间

    int ProcessStatus = 0;
    int ProcessResult = 0;

};
extern thread_ptmotor* Nthread_ptmotor;
#endif // THREAD_PTMOTOR_H
