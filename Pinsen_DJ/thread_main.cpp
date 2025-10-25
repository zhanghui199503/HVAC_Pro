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

thread_main::thread_main(QObject *parent) : QThread(parent)
{

}

thread_main::~thread_main()
{
    threadPause();//暂停线程
}

void thread_main::run()
{
    m_buttonState=true;

    while(m_buttonState)
    {


        if(!m_buttonState)
            break;

        QMutexLocker locker(&m_mutex); // 自动加锁/解锁
        //m_mutex.lock();


        //this->msleep(1);

        if(st)
        {
            int testTime = R_Rfid_timer.nsecsElapsed();
//            qDebug()<<QString("thread_main——线程，时间：%1ns").arg(testTime);
            emit addLog("主流程",QString("thread_main——线程，时间：%1ns").arg(testTime));
            st = false;
        }

        //m_mutex.unlock();



//        qDebug()<<QString("thread_main——线程，时间：%1").arg(1);
        this->msleep(1);
        //this->sleep(1);
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


