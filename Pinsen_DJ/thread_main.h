#ifndef THREAD_MAIN_H
#define THREAD_MAIN_H

#include "Header_File.h"
#include <QObject>

#include "mainwindow.h"

#include "thread_ptmotor.h"

#include "FormLogShow.h"

#include "thread_CommTask.h"
#include "ModbusRtu/mModbusRtu.h"

#define RES_RUN     0
#define RES_OK      1
#define RES_NG      2
#define RES_STOP      3

struct ProcessParams_basis
{
    bool PT_motor = false;
    bool Lin_motor = false;
    bool Blower = false;
    bool Thermistor = false;
    bool Anion = false;
    bool AQS = false;
    bool PM25 = false;
    bool Ptc = false;
    bool Uvc = false;
};

typedef enum {
    START = 0,     //启动
    RESET,          //复位
    MANUAL,   //手自动
    OK_JUDGE,        //OK确认
    STOP,    //急停
}KeyboxNum;


class thread_main : public QThread
{
    Q_OBJECT
public:
    explicit thread_main(QObject *parent = 0);
    ~thread_main();
    void threadPause();
    void threadResume();
    static thread_main* getInstance();

    bool st = false;

    QElapsedTimer R_Rfid_timer;

    ProcessParams_basis ProcessParams_finish;
    bool stepResult[20] = {false};

    bool FinishResultOk = true;//结果标志
    bool isResultOk = true;//单步结果标志
    bool ngStopFlag = true;

    void run_start();
    void run_stop();

    bool stopFunctionflag = false;
    void stopFunction();

    bool read_state();

    QStringList m_stepOrderList;

    bool KeyBoxStop_flag = false;
protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start（）间接调用
    void run();

signals:
    void isDone();

    void addLog(const QString &level, const QString &content);

    void Sign_ShowUI_Step(int _num);
    void Sign_ShowUI_Results(int _num);

    void Sign_Run_Start();
    void Sign_Run_Reset();
    void Sign_Run_Stop();

public slots:

    void test();


    void setFinishResult(uchar _res);
    void sendProtocol_AllStop();
private:
    static QMutex m_instanceMutex;      // 单例创建的互斥锁
    bool m_buttonState; //if pause m_buttonState=false;else m_buttonState=true;
    QMutex m_mutex;//互斥量

    QElapsedTimer Deley_Elaps;//发送后等待完成时间

    //thread_ptmotor * thread_mainptmotor;
    //thread_ptmotor* thread_ptmotor::thread_mainptmotor = nullptr;



    bool MainRun_State = false;//启动信号
    bool Main_Stop = true;//停止信号
    int Main_Step;//执行步骤
     //总结果
    //每步执行状态

    //运行步骤
    int Main_step = 0;
    int Main_Funtion_step = 0;
    int Main_Funtion(int _step);

    //运行顺序

    bool Light_open = false;
    QElapsedTimer LightDeley_Elaps;//发送后等待完成时间

    ProcessParams_basis ProcessParams_state;


    int m_ModbusRtu_delayTime = 0;
    QElapsedTimer KeyBox_timer[5];
    bool m_buttonPressed[5] = {false};       // 按钮最终按下状态（去抖后）
    bool m_lastRawState[5] = {false,false,false,false,true};        // 上一次原始输入状态
    bool isR_Res_timerStarted[5] = {false};  // 计时器是否已启动
    bool R_Res_timer_funFlag[5] = {false};   // 按下去抖完成标志

    void KeyBox_judge();
    void KeyboxFuntion(int _num,bool _state);


};

extern thread_main * Nthread_main;

#endif // THREAD_MAIN_H
