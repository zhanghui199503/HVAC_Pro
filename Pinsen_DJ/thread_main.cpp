/**
 * @file thread_main.cpp
 * @brief 主流程控制线程模块
 * @details 该模块实现：
 *          1. 控制整个线程的流程
 *          2. 设备状态监控与数据采集
 *          3. 设备参数配置与控制
 *          4. 异常处理与报警
 * @author 开发团队
 * @date 2025-07-15
 * @version 2.1.0
 * @see thread_main.h 设备接口定义
 * @see  配置文件格式
*/

#include "thread_main.h"
thread_main * Nthread_main;

QMutex thread_main::m_instanceMutex; // 关键：类外定义，分配内存

thread_main::thread_main(QObject *parent) : QThread(parent)
{
    NFormLogShow = FormLogShow::getInstance();

    thread_mainptmotor = thread_ptmotor::getInstance();

}

thread_main::~thread_main()
{
    threadPause();//暂停线程
}

// 获取单例实例（线程安全的创建方式）
thread_main* thread_main::getInstance()
{
    // 双重检查锁定（提高效率，避免每次获取实例都加锁）
    if (!Nthread_CommTask) {
        QMutexLocker locker(&m_instanceMutex);  // 加锁确保线程安全
        if (!Nthread_CommTask) {
            Nthread_CommTask = new thread_CommTask();
        }
    }
    return Nthread_main;
}


void thread_main::run()
{
    m_buttonState=true;

    while(m_buttonState)
    {


        if(!m_buttonState)
            break;

        //停止运行 保证每个线程都已经停止了
        if(Main_Stop){
            this->msleep(200);
            NFormLogShow->addLog("主线程","线程停止中");
            continue;
        }

        //NFormLogShow->addLog("主线程","线程启动中");


        QMutexLocker locker(&m_mutex); // 自动加锁/解锁




        this->msleep(10);
    }
}

int thread_main::Main_Funtion(int _step)
{
    if(Main_Funtion_step == 0){
        //初始化参数
        isResultOk = true;//单步结果标志
        Main_Funtion_step = 1;
    }else if(Main_Funtion_step == 1){

        QList<PTMotorFP_Setting_basis1> ptmotor_setting;
        ProcessParams_basis ProcessParams_state;

        //============================================================================PT电机
        //判断电机顺序
        for(int i = 0;i < 12;i++){
            if(m_stepOrderList[i] == QString::number(_step + 1)){//1-12是PT电机如果是该步骤，则赋值
                PTmotorSettingsList1[i].en = false;
                ProcessParams_state.PT_motor = true;
            }else{
                PTmotorSettingsList1[i].en = false;
            }
        }
        //读取参数
        if(ProcessParams_state.PT_motor){//PT电机赋值
            thread_mainptmotor->setPTMotorSettings1(PTmotorSettingsList1);
        }
        //=================================================================================

        //======================================================================LIN电机
        if(m_stepOrderList[12] == QString::number(_step + 1)){//13是LIN电机如果是该步骤，则赋值
            ProcessParams_state.Lin_motor = true;
        }
        else{
            ProcessParams_state.Lin_motor = false;
        }
        //======================================================================

        //======================================================================Blower鼓风机
        if(m_stepOrderList[13] == QString::number(_step + 1)){
            ProcessParams_state.Blower = true;
        }else{
            ProcessParams_state.Blower = false;
        }
        //======================================================================

        //======================================================================温敏电阻
        if(m_stepOrderList[14] == QString::number(_step + 1)){
            ProcessParams_state.Thermistor = true;
        }else{
            ProcessParams_state.Thermistor = false;
        }
        //======================================================================

        Main_Funtion_step = 2;
    }else if(Main_Funtion_step == 2){
        int f_finish = 0; //临时存放状态
        int f_res = 0; //临时存放结果
        int stepResult_i = 0;//存储结果下标
        //pt电机读取状态
        if(f_finish == 0 && !stepResult[stepResult_i]){
            //读取结果
            if(f_res == 0){
                //未运行，直接跳过
            }else if(f_res == 1){
                //ok
            }else if(f_res > 1){
                //ng
                isResultOk = false;//单步结果标志
            }
            stepResult[stepResult_i] = true;
        }

        stepResult_i++;
        //lin电机读取状态
        if(f_finish == 0 && !stepResult[stepResult_i]){
            //读取结果
            if(f_res == 0){
                //未运行，直接跳过
            }else if(f_res == 1){
                //ok
            }else if(f_res > 1){
                //ng
                isResultOk = false;//单步结果标志
            }
            stepResult[stepResult_i] = true;
        }

        stepResult_i++;
        //鼓风机电机读取状态
        if(f_finish == 0 && !stepResult[stepResult_i]){
            //读取结果
            if(f_res == 0){
                //未运行，直接跳过
            }else if(f_res == 1){
                //ok
            }else if(f_res > 1){
                //ng
                isResultOk = false;//单步结果标志
            }
            stepResult[stepResult_i] = true;
        }

        stepResult_i++;
        //温敏电阻读取状态
        if(f_finish == 0 && !stepResult[stepResult_i]){
            //读取结果
            if(f_res == 0){//未运行，直接跳过
            }else if(f_res == 1){//ok
            }else if(f_res > 1){//ng
                isResultOk = false;//单步结果标志
            }
            stepResult[stepResult_i] = true;
        }

        if(!isResultOk){//判断停止还是继续运行
            if(ngStopFlag){//NG停止运行
                //发送停止指令

                //返回结果
            }
        }

        //全部完成
        for(int i = 0;i <= stepResult_i;i++){
            if(!stepResult[stepResult_i]){
                break;
            }
        }
    }else if(Main_Funtion_step == 3){
        //使能判断

        //
    }
}

void thread_main::test()
{
    st = true;
}

void thread_main::threadPause()//暂停线程
{
    qDebug()<<QString("pause :%1").arg(m_buttonState);
    this->m_mutex.lock();
    this->m_buttonState=false;
    qDebug()<<QString("pause");
}

void thread_main::threadResume()//继续线程
{
    qDebug()<<QString("resume :%1").arg(m_buttonState);
    this->m_mutex.unlock();
    this->m_buttonState=true;
    qDebug()<<QString("resume");
}



