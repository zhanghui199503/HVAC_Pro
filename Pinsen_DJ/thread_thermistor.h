#ifndef THREAD_THERMISTOR_H
#define THREAD_THERMISTOR_H

#include "mainwindow.h"
#include "motor_types.h"
#include <QObject>
#include <QVector>
#include <QDebug>
#include <cmath>
#include <QMutex>


#define M_PT        1
#define M_STEP      2
#define M_LIN       3
#define R_TEM       4
#define BLOWER      5

#define TherNumber 5
#define Borad_NUm 3

//struct ToralThermistor_Setting_basis
//{
//    int m_Borad = 0;//版号
//    int DelayTime = 0;//延时时间
//    int RunTime = 0;//检测时间
//    bool Compare_Enable = false;//对比使能
//    double temperature_Err = 0.0;//温度误差
//};

//struct Thermistor_Setting_basis
//{
//    bool Environment = false;//环境电阻
//    bool Temperature_Enable = false;//温敏电阻使能
//    double RC = 0.0;    //温度
//    double Beta = 0.0;  //B值
//    double R25 = 0.0;   //温度下的阻值
//    double Temperature_upper = 0.0;//温度上限
//    double Temperature_lower = 0.0;//温度下限
//};



//要返回的温敏状态 （公有）
//struct Thermistor_Status_basis
//{
//    double m_Temperature[Borad_NUm][TherNumber];//温度

//    int m_SingleStatus[Borad_NUm][TherNumber];//温敏电阻 状态 0：无状态 1：运行
//    int m_SingleResult[Borad_NUm][TherNumber];//温敏电阻 结果 0： 1：OK 2:NG

//    int m_TotalStatus = 0;//总状态 状态：停止为0，运行为1
//    int m_TotalResult = 0;//结果：默认是0，OK为1，NG为错误代码
//};



struct MY_Anion_Status_basis
{
    int Error_Num = 0;
    QString ReadData[8] = {""};//读取的
};


//共有
struct Anion_Status_basis
{
    int m_SingleStatus = 0;
    int m_TotalStatus = 0;//总状态 状态：停止为0，运行为1
    int m_TotalResult = 0;//结果：默认是0，OK为1，NG为错误代码
    QString ReturnData[8] = {""};
};



struct Thermistor_Status_basis
{
    double m_Temperature[Borad_NUm * TherNumber] = {0};//温度

    int m_SingleStatus[Borad_NUm * TherNumber] = {0};//温敏电阻 状态 0：无状态 1：运行 2:OK 3:NG
    int m_SingleResult[Borad_NUm * TherNumber] = {0};//温敏电阻 结果 0： 1：OK 2:NG

    int m_TotalStatus = 0;//总状态 状态：停止为0，运行为1
    int m_TotalResult = 0;//结果：默认是0，OK为1，NG为错误代码
};

//私有温敏状态
struct MY_Thermistor_Status_basis
{
    int status = 0;//0:未检测 1：检测结果
    int value = 0;
    double temperature;//温度
};

class thread_Thermistor: public QThread
{
    Q_OBJECT
public:
    //线程状态
    bool threadState;

    static thread_Thermistor* getInstance();
protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start（）间接调用
    void run();
private:
    static QMutex m_instanceMutex;      // 单例创建的互斥锁

    int SendAnionDataOK = 0;
    int AnionProcessSteps = 0;//负离子线程步骤
    Anion_etting_basis Anion_SetData;//负离子参数
    MY_Anion_Status_basis MY_Anion_Data;
    Anion_Status_basis Anion_Data;
    int SendDataOK = 0;
    //流程-------------------------------------------------
    int ProcessSteps = 0;
    int ProcessStepsTime = 0;//线程超时
    int ContrlOrWait = 0;//发送控制
    int Enable_Enable = 0;//使能数量

    double Environment_temperature = 0.0;//环境温度

    bool Borad_Enable[Borad_NUm] = {false};//板子使能通讯

    int RunTime = 0;//运行检测时间

    QByteArray Thermistor_SendContrl(bool _enable);

    QList<ToralThermistor_Setting_basis> ToralThermistor_SetData;//每块板的参数
    QList<QList<Thermistor_Setting_basis>> Thermistor_SetData;//温敏电阻参数

    QList<QList<MY_Thermistor_Status_basis>> MY_Thermistor_Data;//私有数据处理

    Thermistor_Status_basis Thermistor_Data;
//    Thermistor_Status_basis1 Thermistor_Data1;

    bool validateBetaParameters(double beta, double r25);//判断
    //B值计算法  resistance：当前阻值  beta:Bate值  r25 :T℃时阻值 T:温度
    double betaMethod(int resistance, double beta, double r25, double T);//

    int my_portIndex = 1;
    bool init_readFixed[Borad_NUm] = {false};
    bool readFixed_en[Borad_NUm] = {false};

    void sendDataToSerial(int portIndex, const QByteArray &data);
    void addFixedToSerial(int portIndex, const QByteArray &data,bool *_en);

private slots:
    //温敏----------------------------------------------------------------
    void ThermistorInit();//参数初始化
    int SendThermistorStop(int _Number);//温敏电阻停止
    int SendThermistorOPEN(bool OPEN, int _Number);//打开温敏电阻
    int SendThermistorRun(int _Number, QByteArray buff_send_data1);//温敏电阻运行
    void ReadThermistorData(int _Number);//读取温敏数据
    //负离子-----------------------------------------------------------------
    int SendAnionSendData();//发送负离子发送数据
    int SendAnionReadData();//发送负离子读取数据

public slots:
    //温敏---------------------------------------------------------------------------------------------------
    void resetStatus();//复位结果
    void ProcessStop();
    void SetToralThermistorBorad_Setting(QList<ToralThermistor_Setting_basis> _set);//设置温敏板数据
    void SetThermistorFP_Setting(QList<QList<Thermistor_Setting_basis>> _set);//温敏参数设置
    Thermistor_Status_basis reLinRealTimeData();//读取温敏实时数据
    void DataProcessing(QByteArray _reData);//数据处理
    int getProcessStatus();//获取整体的状态
    int getProcessResult();//获取整体结果
    void restProcessResultAndStatus();//复位整体的结果和状态
    //负离子------------------------------------------------------------------------------------------------
    void resetAnionStatus();//复位结果
    void SetAnionFP_Setting(Anion_etting_basis _set);//负离子参数设置
    void AnionDataProcessing(QByteArray _reData);//数据处理

    Anion_Status_basis reAnionRealTimeData();//返回数据
    int getAnionProcessStatus();//获取整体的状态
    int getAnionProcessResult();//获取整体结果
    void restAnionProcessResultAndStatus();//复位整体的结果和状态
signals:
};

extern thread_Thermistor* Nthread_Thermistor;
#endif // THREAD_THERMISTOR_H
