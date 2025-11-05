#ifndef thread_CommTask_H
#define thread_CommTask_H

//#include "Header_File.h"
#include <QObject>
#include <QSemaphore>
#include <QQueue>
#include <QSerialPort>
//#include "thread_main.h"
//#include "thread_ptmotor.h"
#include "mainwindow.h"


//// 定义任务结果结构体，用于传递执行状态
//struct TaskResult {
//    bool completed;  // 任务是否完成
//    QByteArray result;  // 任务执行结果
//    bool success;    // 任务是否成功执行

//    TaskResult() : completed(false), success(false) {}
//};

// 任务结构体
struct Task {
    QByteArray data;
//    int priority;  // 数值越小优先级越高
    bool isFixed;  // 是否为固定任务

    bool *en;//固定任务使能

    int SendId;//站号

    int taskId;// 可以添加任务ID用于唯一标识

    //TaskResult* resultPtr /*= nullptr*/;  // 指向发送线程的结果存储地址
    QString ComNum;  // 串口
//    bool operator<(const Task& other) const {
//        return priority < other.priority; // 数值越小，优先级越高
//    }
};


//extern TaskResult resultgogo1;
//extern TaskResult resultgogo2;
//extern TaskResult resultgogo3;


class thread_CommTask : public QThread
{
    Q_OBJECT
public:
    explicit thread_CommTask(QObject *parent = 0);
    ~thread_CommTask();
    void threadPause();
    void threadResume();

    bool st = false;

    QElapsedTimer  R_Rfid_timer;

    void addNormalTask(const QByteArray data);
//    void addNormalTask(QString PTName,const QByteArray data);
    void addFixedTask(const QByteArray& data,bool* _send_en);
    void addFixedTask(QString PTName,const QByteArray& data,bool* _send_en) ;
    void clearFixedTask( );
    //QList<Task> m_taskQueue;  // 使用列表便于按优先级排序
    // 定义任务队列（成员变量）
    QQueue<Task> m_taskQueue;  // 主任务队列
    QQueue<Task> m_fixedTasks; // 固定任务队列（用于循环）

    void stop();

    int task_funtion();

    bool Send_finish;//发送后接收标志
    QElapsedTimer Send_Elaps;//发送后等待完成时间

    int Swtich_isFixed = 0;//切换发送 0：执行正常任务 1：执行固定任务
    int isFixed_Step = 0;//固定发送流程步骤

    int m_nextTaskId = 1;//用于生成唯一任务ID
    int Error_Count = 0;//执行失败次数
    int fixedError_Count = 0;//固定任务执行失败次数
    Task Error_tast;
    Task fixedError_tast;

    int my_portIndex;

public slots:
    void sendDataToSerial(int portIndex, const QByteArray &data);

protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start（）间接调用
    void run();

signals:
    void isDone();

    void addLog(const QString &level, const QString &content);

    void SendData_Board1(const QByteArray data);
    void SendData_Board2(const QByteArray data);
    void SendData_Board3(const QByteArray data);
public slots:

    void test();


private:
    bool m_buttonState; //if pause m_buttonState=false;else m_buttonState=true;
    QMutex m_mutex;//互斥量

    QSemaphore m_semaphore;
};

extern thread_CommTask * Nthread_CommTask[3];

#endif // thread_CommTask_H
