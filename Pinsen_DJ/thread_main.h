#ifndef THREAD_MAIN_H
#define THREAD_MAIN_H

#include "Header_File.h"
#include <QObject>

#include "mainwindow.h"

#include "thread_ptmotor.h"

#include "FormLogShow.h"


struct ProcessParams_basis
{
    bool PT_motor = false;
    bool Lin_motor = false;

    bool Blower = false;

    bool Thermistor = false;
};


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

    bool isResultOk = true;//单步结果标志
    bool ngStopFlag = true;
protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start（）间接调用
    void run();

signals:
    void isDone();

    void addLog(const QString &level, const QString &content);

public slots:

    void test();


private:
    static QMutex m_instanceMutex;      // 单例创建的互斥锁
    bool m_buttonState; //if pause m_buttonState=false;else m_buttonState=true;
    QMutex m_mutex;//互斥量

    thread_ptmotor * thread_mainptmotor;
    //thread_ptmotor* thread_ptmotor::thread_mainptmotor = nullptr;



    bool MainRun_State = false;//启动信号
    bool Main_Stop = true;//停止信号
    int Main_Step;//执行步骤
     //总结果
    //每步执行状态

    //运行步骤
    int Main_Funtion_step = 0;
    int Main_Funtion(int _step);

    //运行顺序
    QStringList m_stepOrderList;





};

extern thread_main * Nthread_main;

#endif // THREAD_MAIN_H
