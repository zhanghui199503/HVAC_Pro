/**
 * @file thread_CommTask.cpp
 * @brief 主流程控制线程模块
 * @details 该模块实现：
 *          1. 控制整个线程的流程
 *          2. 设备状态监控与数据采集
 *          3. 设备参数配置与控制
 *          4. 异常处理与报警
 * @author 开发团队
 * @date 2025-07-15
 * @version 2.1.0
 * @see thread_CommTask.h 设备接口定义
 * @see  配置文件格式
*/

//#include "Header_File.h"
#include "thread_CommTask.h"
#include "serialportworker.h"
thread_CommTask * Nthread_CommTask;

TaskResult resultgogo;

thread_CommTask::thread_CommTask(QObject *parent) : QThread(parent)
{

}

thread_CommTask::~thread_CommTask()
{
    threadPause();//暂停线程
}

void thread_CommTask::run()
{
    m_buttonState = true;

    while(m_buttonState)
    {
        //m_semaphore.acquire(); // 等待任务
        if(!m_buttonState)
            break;
        int res = task_funtion();//执行任务
        if(res == 0){
            this->msleep(1);
        }
    }
}

int thread_CommTask::task_funtion(){
    Task task;

    uchar byteValue;
    //emit addLog("消费线程",QString("开始"));
    if(Swtich_isFixed == 0){//执行普通任务
        if (m_taskQueue.isEmpty() && Error_Count == 0){
            //emit addLog("消费线程",QString("任务为空"));
            Swtich_isFixed = 1;
            return 0;
        }
        else{//前面有错误次数，代表未成功执行或者未正常返回数据，不读取任务，重新执行原来的任务
            if(Error_Count == 0){
                task = m_taskQueue.takeFirst();//从队列的开头移除并返回元素
                //task = m_taskQueue.head();//获取队列的头元素，但不移除它
            }
            else if(Error_Count > 0)
            {
                task = Error_tast;
            }
            int index = 0; // 要提取的字节索引 // 转换为两位十六进制字符串（带前导零）
            if (index >= 0 && index < task.data.size()){
                byteValue = static_cast<uchar>(task.data.at(index));// 提取指定位置的字节（转换为无符号数避免符号问题）
            }

            QString hexString = QString("%1").arg(byteValue, 2, 16, QChar('0')).toUpper();
            emit addLog("消费线程",QString("读取普通任务:%1").arg(byteValue));
            //            emit SendData(task.data);

            if(task.ComNum=="")
            {

            }else if(task.ComNum=="")
            {

            }else if(task.ComNum=="")
            {

            }
            //            emit SendData(task.data);
            sendDataToSerial(0, task.data);
        }
        Swtich_isFixed = 1;
    }
    else if(Swtich_isFixed == 1){//执行固定任务
        Swtich_isFixed = 0;
        //emit addLog("消费线程",QString("读取固定任务"));
        if(!m_fixedTasks.isEmpty()){
            if(fixedError_Count == 0){
                isFixed_Step = (isFixed_Step + 1) % m_fixedTasks.size();// 移动到下一个元素（循环）
                task = m_fixedTasks.at(isFixed_Step);// 获取当前元素（不删除）
            }
            else{
                task = m_fixedTasks.at(isFixed_Step);// 获取当前元素（不删除）
            }
            int index = 0; // 要提取的字节索引
            if (index >= 0 && index < task.data.size()){
                byteValue = static_cast<uchar>(task.data.at(index));//提取指定位置的字节（转换为无符号数避免符号问题）
            }

            QString hexString = QString("%1").arg(byteValue, 2, 16, QChar('0')).toUpper();
            emit addLog("消费线程",QString("读取固定任务:%1").arg(byteValue));
//            if(task.ComNum=="")
//            {

//            }else if(task.ComNum=="")
//            {

//            }else if(task.ComNum=="")
//            {

//            }
            sendDataToSerial(0, task.data);
            //            emit SendData(task.data);
        }
        else{
            //emit addLog("消费线程",QString("读取固定任务为空"));
            return 0;
        }
    }
    Send_finish = false;//复位接收变量
    Send_Elaps.start();//开始计时
    double testTime;
    while(!Send_finish){
        testTime = (double)Send_Elaps.nsecsElapsed() / (double)1000000 / (double)1000; //s
        if(testTime > 0.2){//S  大于该描数还未接收为接收失败
            Send_finish = true;
            if(Swtich_isFixed == 1){
//                qDebug()<<"gogo1";
                //普通任务(由于执行完成后切换，所以和上面是相反的)
                emit addLog("消费线程",QString("普通任务读取接收失败，时间：%1s").arg(testTime));
                Error_Count++;
                if(Error_Count >= 3){//大于3次报错并删除任务
                    Error_Count = 0;
                    task.resultPtr->completed = true;
                    task.resultPtr->success = false;
                }
                else{
                    Error_tast = task;
                }
            }
            else if(Swtich_isFixed == 0){//固定任务
                emit addLog("消费线程",QString("固定任务读取接收失败，时间：%1s").arg(testTime));
                fixedError_Count++;
                if(fixedError_Count >= 2){//固定任务失败
                    fixedError_Count = 0;
                    task.resultPtr->completed = true;
                    task.resultPtr->success = false;
                    //跳过任务
                }
            }
            return 2;
        }
    }

    task.resultPtr->completed = true;
    task.resultPtr->success = true;
    //task.resultPtr->result = result.result;

    //        //QMutexLocker locker(&m_mutex); // 自动加锁/解锁
    //        m_mutex.lock();

    //        //this->msleep(1);

    //        if(st)
    //        {
    //            int testTime = R_Rfid_timer.nsecsElapsed();
    //            qDebug()<<QString("thread_CommTask——线程，时间：%1ns").arg(testTime);
    //            emit addLog("消费线程",QString("thread_CommTask——线程，时间：%1ns").arg(testTime));
    //            st = false;
    //        }

    //        m_mutex.unlock();
    //        //this->msleep(1);
    return 1;
}

void thread_CommTask::test()
{
    st = true;
}

void thread_CommTask::threadPause()//暂停线程
{
    qDebug()<<QString("pause :%1").arg(m_buttonState);
    this->m_mutex.lock();
    this->m_buttonState=false;
    qDebug()<<QString("pause");
}

void thread_CommTask::threadResume()//继续线程
{
    qDebug()<<QString("resume :%1").arg(m_buttonState);
    this->m_mutex.unlock();
    this->m_buttonState=true;
    qDebug()<<QString("resume");
}

//void thread_CommTask::enqueueTask(const Task& task) {
//    QMutexLocker locker(&m_mutex);
//    // 按优先级插入任务
////    for (auto it = m_taskQueue.begin(); it != m_taskQueue.end(); ++it) {
////        if (task < *it) {
////            m_taskQueue.insert(it, task);
////            m_semaphore.release();
////            return;
////        }
////    }


//    m_taskQueue.enqueue(task);     // 直接入队，无需排序

////    m_taskQueue.append(task);
//    m_semaphore.release();
//}

// 添加普通任务
void thread_CommTask::addNormalTask(const QByteArray data,TaskResult* resultPtr) {
    Q_ASSERT(resultPtr != nullptr);  // 确保结果指针有效

    Task task;
    task.data = data;
    task.isFixed = false;
    //m_nextTaskId++;// 分配唯一ID
    task.resultPtr = resultPtr;  // 保存结果指针

    // 初始化结果为未完成
    resultPtr->completed = false;
    resultPtr->success = false;
    resultPtr->result.clear();


    QMutexLocker locker(&m_mutex); // 多线程安全
    m_taskQueue.enqueue(task);     // 入队
    qDebug()<<"11"<<task.data;
    m_semaphore.release();         // 通知线程有新任务
}

void thread_CommTask::addNormalTask(QString PTName,const QByteArray data,TaskResult* resultPtr) {
    Q_ASSERT(resultPtr != nullptr);  // 确保结果指针有效

    Task task;
    task.data = data;
    task.isFixed = false;
    //m_nextTaskId++;// 分配唯一ID
    task.resultPtr = resultPtr;  // 保存结果指针
    task.ComNum = PTName;
    // 初始化结果为未完成
    resultPtr->completed = false;
    resultPtr->success = false;
    resultPtr->result.clear();
    QMutexLocker locker(&m_mutex); // 多线程安全
    m_taskQueue.enqueue(task);     // 入队
    qDebug()<<"11"<<task.data;
    m_semaphore.release();         // 通知线程有新任务
}

// 添加固定任务
void thread_CommTask::addFixedTask(const QByteArray& data,TaskResult* resultPtr) {
    Q_ASSERT(resultPtr != nullptr);  // 确保结果指针有效

    Task task;
    task.data = data;
    task.isFixed = true;
    task.resultPtr = resultPtr;  // 保存结果指针

    // 初始化结果为未完成
    resultPtr->completed = false;
    resultPtr->success = false;
    resultPtr->result.clear();

    QMutexLocker locker(&m_mutex); // 多线程安全
    m_fixedTasks.enqueue(task);    // 入队
    m_semaphore.release();         // 通知线程有新任务
}

// 添加固定任务
void thread_CommTask::addFixedTask(QString PTName,const QByteArray& data,TaskResult* resultPtr) {
    Q_ASSERT(resultPtr != nullptr);  // 确保结果指针有效

    Task task;
    task.data = data;
    task.isFixed = true;
    task.resultPtr = resultPtr;  // 保存结果指针
    task.ComNum = PTName;
    // 初始化结果为未完成
    resultPtr->completed = false;
    resultPtr->success = false;
    resultPtr->result.clear();

    QMutexLocker locker(&m_mutex); // 多线程安全
    m_fixedTasks.enqueue(task);    // 入队
    m_semaphore.release();         // 通知线程有新任务
}

void thread_CommTask::clearFixedTask( ) {

    QMutexLocker locker(&m_mutex); // 多线程安全
    m_fixedTasks.clear();
    m_semaphore.release();         // 通知线程有新任务
}

void thread_CommTask::stop() {
    m_buttonState = false;
    m_semaphore.release(); // 释放信号量以唤醒可能正在等待的线程
}

void thread_CommTask::sendDataToSerial(int portIndex, const QByteArray &data)
{
//    qDebug()<<"当前索引"<<portIndex;
//    qDebug()<<"进入到开始发送数据接口函数"<<MainWindow::mutualui-> m_workers.contains(portIndex)<< MainWindow::mutualui-> m_serialOpened.value(portIndex, false);
    // 检查端口索引是否存在且已打开
    if (MainWindow::mutualui-> m_workers.contains(portIndex) && MainWindow::mutualui-> m_serialOpened.value(portIndex, false)) {
//        qDebug()<<"进入到开始发送数据接口函数1";
        SerialPortWorker *worker = MainWindow::mutualui-> m_workers.value(portIndex);
        if (worker) {
//          qDebug()<<"进入到开始发送数据接口函数2";
            // 使用Qt::QueuedConnection确保线程安全
            QMetaObject::invokeMethod(worker, "writeData",Qt::QueuedConnection,Q_ARG(QByteArray, data));
        }
    } else {
        qDebug() << "Serial port" << portIndex << "is not available or not opened";
    }
}

