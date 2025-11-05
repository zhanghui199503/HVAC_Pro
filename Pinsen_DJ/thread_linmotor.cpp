#include "thread_linmotor.h"

thread_linmotor* Nthread_linmotor = nullptr;

QMutex thread_linmotor::m_instanceMutex; // 关键：类外定义，分配内存

QList<LINMotor_Return> LinMotor_data;
//LINMotor_Return LinMotor_data[LINMotor_Count];

void thread_linmotor::resetStatus()
{
//    AllStop();
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    buff_send_data.append(0x02);
    buff_send_data.append(0xFF);

    buff_send_data.append(0x80);//功能码
    buff_send_data.append(0xFF);//板子类型

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符
    sendDataToSerial(my_portIndex, buff_send_data);

    ProcessSteps = 0;

    for(run_number = 0; run_number < LINMotor_Count; run_number++)
    {
        LinMotor_data[run_number].m_motorSWID = 0;
        LinMotor_data[run_number].m_motorHWID = 0;
        LinMotor_data[run_number].m_motorVariantID = 0;
        LinMotor_data[run_number].m_motorJEID = 0;
        LinMotor_data[run_number].m_motorSupID = 0;
        LinMotor_data[run_number].m_motorFunID = 0;

        memset(LinMotor_data[run_number].m_ProcessStatus,false,sizeof (LinMotor_data[run_number].m_ProcessStatus));
        memset(LinMotor_data[run_number].m_ProcessStep,false,sizeof (LinMotor_data[run_number].m_ProcessStep));

        LinMotor_data[run_number].m_TotalStatus = 0;
        LinMotor_data[run_number].m_TotalResult = 0;
        LinMotor_data[run_number].CurrentStep = 0;
    }

    memset(RunningState,0,sizeof (RunningState));
    memset(RunningResult,0,sizeof (RunningResult));
}

// 获取单例实例（线程安全的创建方式）
thread_linmotor* thread_linmotor::getInstance()
{
    // 双重检查锁定（提高效率，避免每次获取实例都加锁）
    if (!Nthread_linmotor) {
        QMutexLocker locker(&m_instanceMutex);  // 加锁确保线程安全
        if (!Nthread_linmotor) {
            Nthread_linmotor = new thread_linmotor();
        }
    }
    return Nthread_linmotor;
}


void thread_linmotor::run()
{
    int judgment = 0;
    int judgment1 = 0;
    int ContrlOrWait = 0;

    int InitMotorNumber = 0;
    int InitMotorOK = 0;
    bool TotalStatusChange = false;
    QByteArray motor_contrl[LINMotor_Count],motor_totalcontrl;
    int motor_ProcessStep[LINMotor_Count] = {0};
    int motor_nowprocess[LINMotor_Count] = {0};
//    int errornumber[LINMotor_Count] = {0};
    int timeout[LINMotor_Count] = {0};//⏲
    uint runtimeout[LINMotor_Count] = {0};//运行时间计数
    run_number = MotorStartNumber;
    threadState = true;

    MotorInitStatus();

    while(threadState)
    {
        if(ProcessSteps == 0)
        {
            judgment = 0;
            judgment1 = 0;
            ContrlOrWait = 0;
            InitMotorNumber = 0;
            InitMotorOK = 0;
            memset(motor_nowprocess,0,sizeof (motor_nowprocess));
            memset(motor_ProcessStep,0,sizeof (motor_ProcessStep));
            readFixed_en = false;
            TotalStatusChange = false;
            run_number = MotorStartNumber;
            ProcessStepsTime = 0;
        }
        else
        {
            if(ProcessStepsTime < 666)ProcessStepsTime++;
            if(ProcessSteps == 1)
            {
                Total_Status = 1;
                Total_Result = 1;
                run_number = MotorStartNumber;
                ProcessSteps = 2;
                qDebug()<<"执行步骤1"<<run_number;
            }
            else if(ProcessSteps == 2)//发送电机信息到单片机 编址模式
            {
                qDebug()<<run_number<<MotorStartNumber;
                if(sendMotorParameter(run_number))
                {
                    memset(LinMotor_data[run_number].show_flag,false,sizeof (LinMotor_data[run_number].show_flag));
                    if(!LINMotor_TotalSet.Manual_Automatic)LinMotor_data[run_number].m_TotalStatus = 1;
                    if(run_number >= MotorEndNunber)ProcessSteps = 3;
                    run_number++;
                }
            }
    //        else if(ProcessSteps == 2)//发送电机数据 不需要编址
    //        {
    //            if(LINMotorFP_SetData[i].m_motorEnabled)
    //            {
    //                if(!LINMotor_TotalSet.Manual_Automatic)LINMotor_Data[i].m_ToralProcessStatus = 1;
    //                if(sendMotorParameter(i))
    //                {
    //                    qDebug()<<i<<MotorEndNunber;
    //                    if(i >= MotorEndNunber)
    //                    {
    //                        i = MotorStartNumber;
    //                        ReadMotorState();//读取电机状态
    //                        ProcessSteps = 6;
    //                    }
    //                    i++;
    //                }
    //            }
    //            else i++;
    //        }
    //编址流程----------------------------------------------------------------------------
            else if(ProcessSteps == 3)//编址流程
            {
                TotalStatusChange = true;
                if(sendMotorAddressingProtocol())
                {
                    qDebug()<<"发送编址流程";
                    ReadMotorState();//读取电机状态
                    ProcessSteps = 5;
                }
            }
            else if(ProcessSteps == 5)//等待编址的完成
            {
                judgment = Addressing_OK();
                if(judgment == 2)
                {
                    qDebug()<<"进入判断读取版本号";
                    run_number = MotorStartNumber;
                    ProcessSteps = 6;
                }
                else if(judgment == 3)
                {
                    qDebug()<<"ID错误";
                    ProcessSteps = 10;
                }
            }
    //读取电机版本号----------------------------------------------------------------------
            else if(ProcessSteps == 6)
            {
                qDebug()<<LINMotorFP_SetData[run_number].m_motorEnabled<<LINMotor_Data[run_number].ErrorCode;
                if(LINMotorFP_SetData[run_number].m_motorEnabled && (LINMotor_Data[run_number].ErrorCode == 0))
                {
                    if(ReadMotorVersion(run_number))
                    {
                        if(run_number >= MotorEndNunber)
                        {
                            qDebug()<<"进入判断初始步骤";
                            run_number = MotorStartNumber;
                            ProcessSteps = 7;
                        }
                        run_number++;
                    }
                }
                else
                {
                    if(run_number >= MotorEndNunber)
                    {
                        qDebug()<<"进入判断初始步骤";
                        run_number = MotorStartNumber;
                        ProcessSteps = 7;
                    }
                    run_number++;
                }
            }
    //判断是否为自动且要初始化---------------------------------------------------------------------------
            else if(ProcessSteps == 7)
            {
                qDebug()<<"判读是否需要初始化";
                if(!LINMotor_TotalSet.Manual_Automatic)//自动模式
                {
                    for(run_number = MotorStartNumber; run_number <= MotorEndNunber; run_number++)
                    {
                        qDebug()<<QString("电机%1").arg(run_number)<<LINMotor_Data[run_number].ErrorCode;
                        if(LINMotor_Data[run_number].ErrorCode == 0)motor_nowprocess[run_number] = 1;
                        else
                        {
                            motor_nowprocess[run_number] = 0;
                            LinMotor_data[run_number].m_TotalStatus = 0;
                            LinMotor_data[run_number].m_TotalResult = (LINMotor_Data[run_number].ErrorCode << 1) & 0x1FE;//硬件错误
                        }
                        if(LINMotorFP_SetData[run_number].m_motorInitRunEnabled && LINMotor_Data[run_number].ErrorCode == 0)
                        {
                            judgment = 0;
                            ProcessSteps = 8;
                            TemporaryFlage[run_number] = 1;
                            InitMotorOK = 0;
                            InitMotorNumber = 0;
                            qDebug()<<"需要执行初始化";
                        }
                        qDebug()<<QString("电机%1步骤").arg(run_number)<<motor_nowprocess[run_number];
                    }
                    if(ProcessSteps == 7)
                    {
                        SendDataOK = 0;
                        ProcessSteps = 9;
                        qDebug()<<"不需要执行初始化";
                    }
                }
                else
                {
                    qDebug()<<"直接进入随便控制";
                    SendDataOK = 0;
                    ProcessSteps = 9;//手动模式
                }
            }
    //初始化------------------------------------------------------------------------------------------
            else if(ProcessSteps == 8)
            {
                for(run_number = 0; run_number < LINMotor_Count; run_number++)
                {
                    if(run_number >= MotorStartNumber && run_number <= MotorEndNunber && LINMotorFP_SetData[run_number].m_motorInitRunEnabled)
                    {
                        if(TemporaryFlage[run_number] == 0)
                        {
                            motor_contrl[run_number] = SaveRunProtocol(0, 0, 0);
                        }
                        else if(TemporaryFlage[run_number] == 1)//初始化
                        {
                            if(motor_ProcessStep[run_number] == 0)//发送数据
                            {
                                InitMotorNumber++;
                                qDebug()<<QString("电机%1初始化").arg(run_number);
                                motor_contrl[run_number] = SaveRunProtocol(4, LINMotorFP_SetData[run_number].m_motorInitRunSetStep, LINMotorFP_SetData[run_number].m_motorInitRunDir);
                                motor_ProcessStep[run_number] = 1;
                                ContrlOrWait |= (1<<run_number);
                                runtimeout[run_number] = 0;
                            }
                            else if(motor_ProcessStep[run_number] == 1)//等待
                            {
                                if(!ContrlOrWait)motor_ProcessStep[run_number] = 2;
                            }
                            else if(motor_ProcessStep[run_number] == 2)//判断
                            {
                                if(!LINMotor_TotalSet.Manual_Automatic)//自动运行中
                                {
                                    if(runtimeout[run_number] < LINMotorFP_SetData[run_number].m_motorRunTime)runtimeout[run_number]++;
                                    else
                                    {
                                        motor_ProcessStep[run_number] = 4;
                                    }
                                }
                                if(MotorSingleInitRun(run_number) == 1)
                                {
                                    InitMotorOK++;
                                    TemporaryFlage[run_number] = 0;
                                    runtimeout[run_number] = 0;
                                    motor_ProcessStep[run_number] = 0;
                                }
                                else if(MotorSingleInitRun(run_number) == 2)
                                {
                                    motor_ProcessStep[run_number] = 4;
                                }
                            }
                            else if(motor_ProcessStep[run_number] == 4)//错误步骤锁存
                            {
                                LinMotor_data[run_number].m_TotalResult = 17;
                                TemporaryFlage[run_number] = 3;
                                motor_ProcessStep[run_number] = 0;
                                LinMotor_data[run_number].m_TotalStatus = 0;
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    runtimeout[run_number] = 0;
                                    motor_nowprocess[run_number] = 0;
                                }
                            }
                        }
                        else if(TemporaryFlage[run_number] == 3)//停止
                        {
                            if(motor_ProcessStep[run_number] == 0)//发送数据
                            {
                                motor_contrl[run_number] = SaveRunProtocol(6, 0, 0);
                                motor_ProcessStep[run_number] = 1;
                                ContrlOrWait |= (1<<run_number);
                            }
                            else if(motor_ProcessStep[run_number] == 1)//等待
                            {
                                if(!ContrlOrWait)motor_ProcessStep[run_number] = 2;
                            }
                            else if(motor_ProcessStep[run_number] == 2)//判断
                            {
                                if(MotorRunStatus(run_number) == 0)
                                {
                                    InitMotorOK++;
                                    motor_ProcessStep[run_number] = 0;
                                    TemporaryFlage[run_number] = 0;
                                }
                            }
                        }
                    }
                    else motor_contrl[run_number] = SaveRunProtocol(0, 0, 0);
                }
                if(ContrlOrWait)
                {
                    motor_totalcontrl = motor_contrl[0] + motor_contrl[1] + motor_contrl[2] + motor_contrl[3] + motor_contrl[4] + motor_contrl[5]
                                      + motor_contrl[6] + motor_contrl[7] + motor_contrl[8] + motor_contrl[9] + motor_contrl[10] + motor_contrl[11];
                    int j = sendRunProtocol(motor_totalcontrl,ContrlOrWait);
                    if(j)//发送控制指令
                    {
                        ContrlOrWait &= j;
                    }
                }
                else//
                {
                    if(InitMotorNumber ==  InitMotorOK)ProcessSteps = 9;
                }
            }
    //作动--------------------------------------------------------------------------------------------
            else if(ProcessSteps == 9)//编址完成，随便作动
            {

                for(run_number = 0; run_number < LINMotor_Count; run_number++)
                {
                    if(run_number >= MotorStartNumber && run_number <= MotorEndNunber)
                    {
                        //qDebug()<<QString("刘LIN电机%1进入走挡位%2为POS%3").arg(run_number).arg(motor_nowprocess[run_number]).arg(LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process);
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------
                        if(!LINMotor_TotalSet.Manual_Automatic && LINMotorFP_SetData[run_number].m_motorEnabled && ProcessEN[run_number])
                        {
                            if(motor_nowprocess[run_number] <= 8 && motor_nowprocess[run_number] > 0)
                            {
                                if(LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process >= 1 && LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process <= 6)
                                    TemporaryFlage[run_number] = 2;
                                else if(LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process == 7)
                                    TemporaryFlage[run_number] = 5;
                                else if(LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process == 8)
                                    TemporaryFlage[run_number] = 6;
                                else TemporaryFlage[run_number] = 7;
                            }
                            else
                            {
                                if(motor_nowprocess[run_number] > 8)
                                {
                                    LinMotor_data[run_number].m_TotalResult = 1;
                                    LinMotor_data[run_number].m_TotalStatus = 0;
                                    TemporaryFlage[run_number] = 0;
                                }
                                motor_nowprocess[run_number] = 0;

    //                            TemporaryFlage[i] = 0;
                            }
                        }
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------
                        if(TemporaryFlage[run_number] == 0)
                        {
                            motor_contrl[run_number] = SaveRunProtocol(0, 0, 0);
                        }
                        else if(TemporaryFlage[run_number] == 1)//初始化
                        {
                            if(motor_ProcessStep[run_number] == 0)//发送数据
                            {
                                qDebug()<<QString("电机%1初始化").arg(run_number);
                                motor_contrl[run_number] = SaveRunProtocol(4, LINMotorFP_SetData[run_number].m_motorInitRunSetStep, LINMotorFP_SetData[run_number].m_motorInitRunDir);
                                motor_ProcessStep[run_number] = 1;
                                LinMotor_data[run_number].m_TotalStatus = 1;
                                ContrlOrWait |= (1<<run_number);
                            }
                            else if(motor_ProcessStep[run_number] == 1)//等待
                            {
                                if(!LINMotor_TotalSet.Manual_Automatic)LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 0;
                                if(!ContrlOrWait)motor_ProcessStep[run_number] = 2;
                            }
                            else if(motor_ProcessStep[run_number] == 2)//判断
                            {
                                if(!LINMotor_TotalSet.Manual_Automatic)LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 1;
                                if(MotorSingleInitRun(run_number) == 1)motor_ProcessStep[run_number] = 3;//OK
                                else if(MotorSingleInitRun(run_number) == 2)motor_ProcessStep[run_number] = 4;
                            }
                            else if(motor_ProcessStep[run_number] == 3)//垃圾时间
                            {
                                qDebug()<<QString("电机%1等待").arg(run_number);
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LINMotorFP_SetData[run_number].m_motorInitRunSetStep;
                                    LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 2;
                                    TemporaryFlage[run_number] = 7;
                                }
                                else
                                {
                                    LinMotor_data[run_number].m_TotalResult = 2;
                                    LinMotor_data[run_number].m_TotalStatus = 0;
                                    motor_ProcessStep[run_number] = 0;
                                    TemporaryFlage[run_number] = 0;
                                }
                            }
                            else if(motor_ProcessStep[run_number] == 4)//错误步骤锁存
                            {
                                TemporaryFlage[run_number] = 0;
                                motor_ProcessStep[run_number] = 0;

                                LinMotor_data[run_number].m_TotalResult = 17;

                                LinMotor_data[run_number].m_TotalStatus = 0;
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 3;
                                    motor_nowprocess[run_number] = 0;
                                }
                            }
                        }
                        else if(TemporaryFlage[run_number] == 2)//运行到位置
                        {
                            if(motor_ProcessStep[run_number] == 0)//发送数据
                            {
                                qDebug()<<QString("电机%1运行到目标位置").arg(run_number);
                                LINMotor_Data[run_number].m_state &= 0xFC;
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    Now_targetStep[run_number] = LINMotor_SetData[run_number][LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1].m_motortargetStep;
                                    Now_stepError[run_number] = LINMotorFP_SetData[run_number].m_motorStepError;
                                }
                                LinMotor_data[run_number].m_TotalStatus = 1;
                                motor_contrl[run_number] = SaveRunProtocol(1, Now_targetStep[run_number], Now_stepError[run_number]);
                                motor_ProcessStep[run_number] = 1;
                                ContrlOrWait |= (1<<run_number);
                            }
                            else if(motor_ProcessStep[run_number] == 1)//等待
                            {
                                if(!LINMotor_TotalSet.Manual_Automatic)LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 0;
                                if(!ContrlOrWait)motor_ProcessStep[run_number] = 2;
                            }
                            else if(motor_ProcessStep[run_number] == 2)//判断
                            {
                                if(!LINMotor_TotalSet.Manual_Automatic)//自动运行中
                                {
                                    LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 1;
                                    if(runtimeout[run_number] < LINMotorFP_SetData[run_number].m_motorRunTime)runtimeout[run_number]++;
                                    else
                                    {
                                        LinMotor_data[run_number].m_TotalResult = 3;
                                        LinMotor_data[run_number].m_TotalResult |= (LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process << 5);
                                        motor_ProcessStep[run_number] = 4;
                                        if(!LINMotor_TotalSet.Manual_Automatic)
                                        {
//                                            runtimeout[run_number] = 0;
                                            LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                            LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 3;
                                            LinMotor_data[run_number].m_TotalStatus = 0;
//                                            motor_nowprocess[run_number] = 0;
                                        }
                                    }
                                }

                                if(MotorRunStatus(run_number) == 1)
                                {
                                    runtimeout[run_number] = 0;
                                    motor_ProcessStep[run_number] = 3;
                                }
                                else if(MotorRunStatus(run_number) == 2)//堵转报警
                                {
                                    if(!ContrlOrWait)
                                    {
                                        LinMotor_data[run_number].m_TotalResult = 5;
                                        LinMotor_data[run_number].m_TotalResult |= (LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process << 5);
                                        motor_ProcessStep[run_number] = 4;
                                        if(!LINMotor_TotalSet.Manual_Automatic)
                                        {
//                                            runtimeout[run_number] = 0;
                                            LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                            LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 3;
                                            LinMotor_data[run_number].m_TotalStatus = 0;
//                                            motor_nowprocess[run_number] = 0;
                                        }
                                    }
                                }
                            }
                            else if(motor_ProcessStep[run_number] == 3)//垃圾时间
                            {
                                qDebug()<<QString("电机%1等待").arg(run_number);
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                    LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 2;
                                    TemporaryFlage[run_number] = 7;
                                }
                                else
                                {
                                    LinMotor_data[run_number].m_TotalResult = 2;
                                    LinMotor_data[run_number].m_TotalStatus = 0;
                                    motor_ProcessStep[run_number] = 0;
                                    TemporaryFlage[run_number] = 0;
                                }
                            }
                            else if(motor_ProcessStep[run_number] == 4)//错误步骤锁存
                            {
                                TemporaryFlage[run_number] = 3;
                                motor_ProcessStep[run_number] = 0;
                                LinMotor_data[run_number].m_TotalStatus = 0;
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    runtimeout[run_number] = 0;
                                    LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                    LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 3;
                                    motor_nowprocess[run_number] = 0;
                                }
                            }
                        }
                        else if(TemporaryFlage[run_number] == 3)//停止
                        {
                            if(motor_ProcessStep[run_number] == 0)//发送数据
                            {
                                motor_contrl[run_number] = SaveRunProtocol(6, 0, 0);
                                motor_ProcessStep[run_number] = 1;
                                ContrlOrWait |= (1<<run_number);
                            }
                            else if(motor_ProcessStep[run_number] == 1)//等待
                            {
                                if(!ContrlOrWait)motor_ProcessStep[run_number] = 2;
                            }
                            else if(motor_ProcessStep[run_number] == 2)//判断
                            {
                                if(MotorRunStatus(run_number) == 0)
                                {
                                    motor_ProcessStep[run_number] = 0;
                                    TemporaryFlage[run_number] = 0;
                                }
                            }
                        }
                        else if(TemporaryFlage[run_number] == 4)//设置步数
                        {
                            if(motor_ProcessStep[run_number] == 0)//发送数据
                            {
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    Now_setStep[run_number] = LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].m_motortargetStep;
                                }
                                motor_contrl[run_number] = SaveRunProtocol(5, Now_setStep[run_number], 0);
                                motor_ProcessStep[run_number] = 1;
                                ContrlOrWait |= (1<<run_number);
                            }
                            else if(motor_ProcessStep[run_number] == 1)//等待
                            {
                                if(!ContrlOrWait)motor_ProcessStep[run_number] = 2;
                            }
                            else if(motor_ProcessStep[run_number] == 2)//判断
                            {

                                if(LinMotor_data[run_number].CurrentStep == Now_setStep[run_number])motor_ProcessStep[run_number] = 3;
                            }
                            else if(motor_ProcessStep[run_number] == 3)//垃圾时间
                            {
                                if(!LINMotor_TotalSet.Manual_Automatic)TemporaryFlage[run_number] = 7;
                                else TemporaryFlage[run_number] = 0;
                            }
                        }
                        else if(TemporaryFlage[run_number] == 5)//检测开度1
                        {
                            if(motor_ProcessStep[run_number] == 0)//发送数据
                            {
                                qDebug()<<QString("电机%1检测开度1").arg(run_number);
                                motor_contrl[run_number] = SaveRunProtocol(2, 0, 0);
                                motor_ProcessStep[run_number] = 1;
                                LinMotor_data[run_number].m_TotalStatus = 1;
                                ContrlOrWait |= (1<<run_number);
                            }
                            else if(motor_ProcessStep[run_number] == 1)//等待
                            {

                                if(!LINMotor_TotalSet.Manual_Automatic)LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 0;
                                if(!ContrlOrWait)
                                {
                                    qDebug()<<QString("电机%1检测开度1已回应").arg(run_number);
                                    motor_ProcessStep[run_number] = 2;
                                }
                            }
                            else if(motor_ProcessStep[run_number] == 2)//判断
                            {
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 1;
                                    if(runtimeout[run_number] < LINMotorFP_SetData[run_number].m_motorRunTime)runtimeout[run_number]++;
                                    else
                                    {
                                        LinMotor_data[run_number].m_TotalResult = 3;
                                        LinMotor_data[run_number].m_TotalResult |= (LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process << 5);
                                        motor_ProcessStep[run_number] = 4;
                                        if(!LINMotor_TotalSet.Manual_Automatic)
                                        {
//                                            runtimeout[run_number] = 0;
                                            LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                            LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 3;
                                            LinMotor_data[run_number].m_TotalStatus = 0;
//                                            motor_nowprocess[run_number] = 0;
                                        }
                                    }
                                }
                                if(MotorRunStatus(run_number) == 2)
                                {
                                    runtimeout[run_number] = 0;
                                    motor_ProcessStep[run_number] = 3;

                                }
                                else if(MotorRunStatus(run_number) == 1)//到位了
                                {
                                    motor_ProcessStep[run_number] = 4;
                                    LinMotor_data[run_number].m_TotalResult = 9;
                                    LinMotor_data[run_number].m_TotalResult |= (LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process << 5);
                                    if(!LINMotor_TotalSet.Manual_Automatic)
                                    {
//                                        runtimeout[run_number] = 0;
                                        LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                        LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 3;
                                        LinMotor_data[run_number].m_TotalStatus = 0;
//                                        motor_nowprocess[run_number] = 0;
                                    }
                                }
                            }
                            else if(motor_ProcessStep[run_number] == 3)//垃圾时间
                            {
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                    LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 2;
                                    TemporaryFlage[run_number] = 7;
                                }
                                else
                                {
                                    LinMotor_data[run_number].m_TotalResult = 2;
                                    LinMotor_data[run_number].m_TotalStatus = 0;
                                    motor_ProcessStep[run_number] = 0;
                                    TemporaryFlage[run_number] = 0;
                                }
                            }
                            else if(motor_ProcessStep[run_number] == 4)//错误步骤锁存
                            {
                                TemporaryFlage[run_number] = 0;
                                motor_ProcessStep[run_number] = 0;
                                LinMotor_data[run_number].m_TotalStatus = 0;
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    runtimeout[run_number] = 0;
                                    LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                    LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 3;
                                    motor_nowprocess[run_number] = 0;
                                }
                            }
                        }
                        else if(TemporaryFlage[run_number] == 6)//检检测开度2
                        {
                            if(motor_ProcessStep[run_number] == 0)//发送数据
                            {
                                qDebug()<<QString("电机%1检测开度2").arg(run_number);
                                motor_contrl[run_number] = SaveRunProtocol(3, 0, 0);
                                motor_ProcessStep[run_number] = 1;
                                ContrlOrWait |= (1<<run_number);
                                LinMotor_data[run_number].m_TotalStatus = 1;
                            }
                            else if(motor_ProcessStep[run_number] == 1)//等待
                            {
                                LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 0;
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    if(runtimeout[run_number] < LINMotorFP_SetData[run_number].m_motorRunTime)runtimeout[run_number]++;
                                    else
                                    {
                                        motor_ProcessStep[run_number] = 4;
                                        LinMotor_data[run_number].m_TotalResult = 3;
                                        LinMotor_data[run_number].m_TotalResult |= (LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process << 5);
                                        if(!LINMotor_TotalSet.Manual_Automatic)
                                        {
//                                            runtimeout[run_number] = 0;
                                            LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                            LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 3;
                                            LinMotor_data[run_number].m_TotalStatus = 0;
//                                            motor_nowprocess[run_number] = 0;
                                        }
                                    }

                                }
                                if(!ContrlOrWait)motor_ProcessStep[run_number] = 2;
                            }
                            else if(motor_ProcessStep[run_number] == 2)//判断
                            {
                                if(!LINMotor_TotalSet.Manual_Automatic)LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 1;
                                if(MotorRunStatus(run_number) == 2)
                                {
                                    runtimeout[run_number] = 0;
                                    motor_ProcessStep[run_number] = 3;
                                }
                                else if(MotorRunStatus(run_number) == 1)//到位
                                {
                                    motor_ProcessStep[run_number] = 4;
                                    LinMotor_data[run_number].m_TotalResult = 9;
                                    LinMotor_data[run_number].m_TotalResult |= (LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process << 5);
                                    if(!LINMotor_TotalSet.Manual_Automatic)
                                    {
//                                        runtimeout[run_number] = 0;
                                        LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                        LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 3;
                                        LinMotor_data[run_number].m_TotalStatus = 0;
//                                        motor_nowprocess[run_number] = 0;
                                    }
                                }
                            }
                            else if(motor_ProcessStep[run_number] == 3)//垃圾时间
                            {
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                    LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 2;
                                    TemporaryFlage[run_number] = 7;
                                }
                                else
                                {
                                    LinMotor_data[run_number].m_TotalResult = 2;
                                    LinMotor_data[run_number].m_TotalStatus = 0;
                                    motor_ProcessStep[run_number] = 0;
                                    TemporaryFlage[run_number] = 0;
                                }
                            }
                            else if(motor_ProcessStep[run_number] == 4)//错误步骤锁存
                            {
                                TemporaryFlage[run_number] = 0;
                                motor_ProcessStep[run_number] = 0;
                                if(!LINMotor_TotalSet.Manual_Automatic)
                                {
                                    runtimeout[run_number] = 0;
                                    LinMotor_data[run_number].m_ProcessStep[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = LinMotor_data[run_number].CurrentStep;
                                    LinMotor_data[run_number].m_ProcessStatus[LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].process - 1] = 3;
                                    LinMotor_data[run_number].m_TotalStatus = 0;
                                    motor_nowprocess[run_number] = 0;
                                }
                            }
                        }
                        if(TemporaryFlage[run_number] == 7)//停留
                        {
                            if(timeout[run_number] < LINMotor_SetData[run_number][motor_nowprocess[run_number] - 1].m_stopTime)timeout[run_number]++;
                            else
                            {
                                TemporaryFlage[run_number] = 0;
                                motor_ProcessStep[run_number] = 0;
                                timeout[run_number] = 0;
                                motor_nowprocess[run_number]++;
                            }
                        }
                    }
                    else motor_contrl[run_number] = SaveRunProtocol(0, 0, 0);
                }
                if(ContrlOrWait)
                {
                    motor_totalcontrl = motor_contrl[0] + motor_contrl[1] + motor_contrl[2] + motor_contrl[3] + motor_contrl[4] + motor_contrl[5]
                                      + motor_contrl[6] + motor_contrl[7] + motor_contrl[8] + motor_contrl[9] + motor_contrl[10] + motor_contrl[11];
                    int j = sendRunProtocol(motor_totalcontrl,ContrlOrWait);
                    if(j)//发送控制指令
                    {
                        ContrlOrWait &= j;
                    }
                }
            }
            else if(ProcessSteps == 10)
            {
                QByteArray buff_send_data;
                buff_send_data.append(0x68);
                buff_send_data.append(0x02);
                buff_send_data.append(0xFF);

                buff_send_data.append(0x80);//功能码
                buff_send_data.append(0xFF);//板子类型

                buff_send_data.append(0x0D);//结束符
                buff_send_data.append(0x0A);//结束符
                ProcessSteps = 0;
            }

            if(ProcessStepsTime >= 666)
            {
                Total_Result = 3;
                Total_Status = 0;
                ProcessSteps = 10;
            }
            else
            {
                if(TotalStatusChange)
                {
                    for(run_number1 = MotorStartNumber; run_number1 <= MotorEndNunber; run_number1++)
                    {
    //                    qDebug()<<"总电机状态"<<LinMotor_data[run_number1].m_TotalStatus;
                        if(LinMotor_data[run_number1].m_TotalStatus)break;
                    }
                    if(run_number1 > MotorEndNunber)
                    {
                        Total_Status = 0;
                        ProcessSteps = 10;
                    }
    //                    qDebug()<<"总电机状态"<<run_number1<<Total_Status;
                }


                int OK_number = 0;
                int NG_number = 0;
                int Run_number = 0;
                for(run_number1 = MotorStartNumber; run_number1 <= MotorEndNunber; run_number1++)
                {
                    if(LinMotor_data[run_number1].m_TotalResult == 2)OK_number++;
                    else if(LinMotor_data[run_number1].m_TotalResult == 1)
                    {

                        Run_number++;
                    }
                    else if(LinMotor_data[run_number1].m_TotalResult > 2)
                    {
                        LinMotor_data[run_number1].m_TotalStatus = 0;
                        NG_number++;
                    }
                }
                if(NG_number)
                {
                    Total_Result = 3;
                }
                else
                {
                    if(OK_number == MotorToralNumber)Total_Result = 2;
                    else if(Run_number)Total_Result = 1;
                }
                OK_number = 0;
                NG_number = 0;
                Run_number = 0;
            }
        }
        QThread::msleep(100);//睡100ms
    }
}


//电机总参数设置
void thread_linmotor::SetMotor_TotalSetting(LINMotorTotal_basis _set)
{
    LINMotor_TotalSet = _set;
}
//线程复位
void thread_linmotor::ProcessStop()
{
    ProcessSteps = 0;
}


//电机全部停止
void thread_linmotor::AllStop()
{
    QByteArray buff_send_data;
    uchar buff_value;

    buff_send_data.append(0x68);
    buff_send_data.append(0x02);

    buff_value = static_cast<uchar>(LINMotor_TotalSet.BoardType);//
    buff_send_data.append(buff_value);

    buff_send_data.append(0x13);//功能码
    buff_value = static_cast<uchar>(M_LIN);//
    buff_send_data.append(buff_value);//板子类型

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符
//    Nthread_CommTask->addNormalTask(buff_send_data,&resultgogo);
    sendDataToSerial(my_portIndex, buff_send_data);
}
//步骤参数设置
void thread_linmotor::SetLINMotor_ProcessSet(QList<QList<MY_LINMotorIP_Setting_basis> > _set)
{
    LINMotor_SetData = _set;
}
//电机基本参数设置
bool thread_linmotor::SetMotorFP_Setting(QList<MY_LINMotorFP_Setting_basis> _set)
{
    resetStatus();
    int StartStep = 0;
    LINMotorFP_SetData = _set;
    qDebug()<<"实际使用的NAD"<<LINMotorFP_SetData[0].m_motorNAD;
    StartStep = MotorNumberJudge();
    if(StartStep)
    {
        Total_Status = 1;

        Total_Result = 0;
        qDebug()<<"开始流程"<<StartStep;
        ProcessSteps = 1;
//        LINMotor_TotalSet.Addressing_Enable ? (ProcessSteps = 1) : (ProcessSteps = 2);
        return true;
    }
    else return false;
}

//int thread_linmotor::run_funtion(int _Motor_N, QList<QList<LINMotorIP_Setting_basis> > _set)
//{
//    int status;
//    status = 0;
//    if(RunningState[_Motor_N] == 0)//未运行
//    {
//        //参数设置
//        LINMotor_SetData = _set;
//        for(int i = 0; i <= 12; i++)
//            if(LINMotor_SetData[_Motor_N][i].controlType == 3 || LINMotor_SetData[_Motor_N][i].controlType == 4)
//                LINMotor_SetData[_Motor_N][i].m_motorSetStep = LINMotor_SetData[_Motor_N][i].m_motortargetStep;
//    }
//    else
//    {
//        if(LINMotor_Data[_Motor_N].ErrorCode)//有错误代码（电机自身有问题）
//        {
//            //电压错误
//            if((LINMotor_Data[_Motor_N].ErrorCode & 0xC0) == 0x40)LINMotor_Data[_Motor_N].VoltageError =  1;
//            else if((LINMotor_Data[_Motor_N].ErrorCode & 0xC0) == 0x80)LINMotor_Data[_Motor_N].VoltageError = 2;
//            else LINMotor_Data[_Motor_N].VoltageError = 0;
//            //电气错误
//            if((LINMotor_Data[_Motor_N].ErrorCode & 0x30) == 0x20)LINMotor_Data[_Motor_N].ElectrError = 2;
//            else if((LINMotor_Data[_Motor_N].ErrorCode & 0x30) == 0x10)LINMotor_Data[_Motor_N].ElectrError = 1;
//            else LINMotor_Data[_Motor_N].ElectrError = 0;
//            //过温错误
//            if((LINMotor_Data[_Motor_N].ErrorCode & 0x0C) == 0x04)LINMotor_Data[_Motor_N].TempError = true;
//            else LINMotor_Data[_Motor_N].TempError = false;
//            //断线错误
//            if(LINMotor_Data[_Motor_N].ErrorCode & 0x02)LINMotor_Data[_Motor_N].DisconnectError = true;
//            else LINMotor_Data[_Motor_N].DisconnectError = false;
//            //响应错误
//            if(LINMotor_Data[_Motor_N].ErrorCode & 0x01)LINMotor_Data[_Motor_N].PresentError = true;
//            else LINMotor_Data[_Motor_N].PresentError = false;
//        }
//        else//空调有问题
//        {
//            if(((LINMotor_Data[_Motor_N].m_state & 0x30) == 0x20) || ((LINMotor_Data[_Motor_N].m_state & 0x0C) == 0x08))
//            {
//                RunningResult[_Motor_N] = 2;
//            }
//            else
//            {
//                if((LINMotor_Data[_Motor_N].m_state & 0xC0) == 0x40)
//                {
//                    RunningResult[_Motor_N] = 1;
//                }
//                else if((LINMotor_Data[_Motor_N].m_state & 0xC0) == 0x80)
//                {
//                    if(TemporaryFlage[_Motor_N] == 2)RunningResult[_Motor_N] = 2;
//                }
//            }
//         }
//        //返回结果
//        status = RunningResult[_Motor_N];
//    }
//    return status;
//}

//保存运行指令
QByteArray thread_linmotor::SaveRunProtocol(int _Cintrl, int _Step, int _other)
{
    QByteArray buff_send_data;
    uchar high;
    uchar low;
    uchar buff_value;

    if(_Cintrl == 1 || _Cintrl == 2 || _Cintrl == 3)//到目标位置/堵转
    {
        if(_Cintrl == 1)//走到指定位置
        {
            high = static_cast<uchar>((_Step >> 8) & 0xFF);  // 高8位
            low = static_cast<uchar>(_Step & 0xFF);          // 低8位
            buff_value = static_cast<uchar>(_other & 0xFF);//误差
        }
        else if(_Cintrl == 2)//左极限
        {
            high = '\0';
            low = '\0';
            buff_value = '\0';
        }
        else
        {
            high = 0xFF;
            low = 0xFE;
            buff_value = '\0';
        }

        buff_send_data.append(0x02);//控制码
        buff_send_data.append(low);//位置步数
        buff_send_data.append(high);
        buff_send_data.append(buff_value);
    }
    else if(_Cintrl == 4)//初始化
    {
        buff_send_data.append(0x01);//控制码
        high = static_cast<uchar>((_Step >> 8) & 0xFF);  // 高8位
        low = static_cast<uchar>(_Step & 0xFF);
        buff_value = static_cast<uchar>(_other & 0xFF);//误差

        buff_send_data.append(low);//位置步数
        buff_send_data.append(high);
        buff_send_data.append(buff_value);
    }
    else if(_Cintrl == 5)//设置步数
    {
        buff_send_data.append(0x05);//控制码
        high = static_cast<uchar>((_Step >> 8) & 0xFF);  // 高8位
        low = static_cast<uchar>(_Step & 0xFF);
        buff_send_data.append(low);//位置步数
        buff_send_data.append(high);
        buff_send_data.append('\0');
    }
    else if(_Cintrl == 6)//停止
    {
        buff_send_data.append(0x04);//控制码
        buff_send_data.append(3,'\0');
    }
    else buff_send_data.append(4,'\0');
    return buff_send_data;
}
//控制指令
int thread_linmotor::sendRunProtocol(QByteArray buff_send_data1,int Contrl)
{
    uchar buff_value;
    static int contrl = 0;
    QByteArray buff_send_data;

    if(SendDataOK == 0)
    {
        contrl = ~Contrl;
        buff_send_data.append(0x68);
        buff_send_data.append(0x33);
        //站号
        buff_value = static_cast<uchar>(LINMotor_TotalSet.BoardType);//
        buff_send_data.append(buff_value);

        buff_send_data.append(0x13);//功能码

        buff_value = static_cast<uchar>(M_LIN);
        buff_send_data.append(buff_value);//板子类型

        buff_value = static_cast<uchar>(MotorToralNumber);//电机数量
        buff_send_data.append(buff_value);

        buff_send_data += buff_send_data1;

        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
        qDebug()<<buff_send_data;
        SendDataOK = 1;
//        Nthread_CommTask->addNormalTask(buff_send_data,&resultgogo);
        sendDataToSerial(my_portIndex, buff_send_data);
        return 0;
    }
    else if(SendDataOK == 1)return 0;
    else
    {
        SendDataOK = 0;
        return contrl;
    }
}
//电机初始化
int thread_linmotor::sendMotorInitRunProtocol()
{
    uchar buff_value;
    uchar high;
    uchar low;

    QByteArray buff_send_data;
    if(SendDataOK == 0)
    {
        buff_send_data.append(0x68);
        buff_send_data.append(0x33);
        //站号
        buff_value = static_cast<uchar>(LINMotor_TotalSet.BoardType);//
        buff_send_data.append(buff_value);

        buff_send_data.append(0x13);//功能码
        buff_value = static_cast<uchar>(M_LIN);
        buff_send_data.append(buff_value);//板子类型

        buff_value = static_cast<uchar>(MotorToralNumber);//电机数量
        buff_send_data.append(buff_value);

        for(int i = 0; i < LINMotor_Count; i++)
        {
            if((i  >= MotorStartNumber) && (i <= MotorEndNunber) && (LINMotorFP_SetData[i].m_motorInitRunEnabled && !LINMotor_Data[i].m_InitState))
            {
                buff_send_data.append(0x01);//控制码
                high = static_cast<uchar>((LINMotorFP_SetData[i].m_motorInitRunSetStep >> 8) & 0xFF);  // 高8位
                low = static_cast<uchar>(LINMotorFP_SetData[i].m_motorInitRunSetStep & 0xFF);
                buff_send_data.append(low);//位置步数
                buff_send_data.append(high);

                buff_value = static_cast<uchar>(LINMotorFP_SetData[i].m_motorInitRunDir & 0xFF);//方向
                buff_send_data.append(buff_value);
            }
            else
            {
                buff_send_data.append(4,'\0');
            }
        }

        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
        qDebug()<<buff_send_data;
        SendDataOK = 1;
//        Nthread_CommTask->addNormalTask(buff_send_data,&resultgogo);
        sendDataToSerial(my_portIndex, buff_send_data);
        return 1;
    }
    else if(SendDataOK == 1)return 1;
    else
    {
        SendDataOK = 0;
        return 0;
    }
}

//发送电机参数
int thread_linmotor::sendMotorParameter(int _Motor_N)
{
    uint data;
    uchar buff_value;

    QByteArray buff_send_data;
    if(SendDataOK == 0)
    {
        buff_send_data.append(0x68);
        buff_send_data.append(0x08);

        //站号
        buff_value = static_cast<uchar>(LINMotor_TotalSet.BoardType);//
        buff_send_data.append(buff_value);

        buff_send_data.append(0x11);//功能码

        buff_value = static_cast<uchar>(M_LIN);
        buff_send_data.append(buff_value);//板子类型

        buff_value = static_cast<uchar>(_Motor_N + 1);//电机号
        buff_send_data.append(buff_value);
        buff_value = static_cast<uchar>(LINMotorFP_SetData[_Motor_N].m_motorNAD);//NAD
        buff_send_data.append(buff_value);
        buff_value = static_cast<uchar>(LINMotorFP_SetData[_Motor_N].m_motorContrlID);//控制ID
        buff_send_data.append(buff_value);
        buff_value = static_cast<uchar>(LINMotorFP_SetData[_Motor_N].m_motorStatusID);//状态ID
        buff_send_data.append(buff_value);

        data = 0xAA;
        LINMotorFP_SetData[_Motor_N].m_motorDirection ? (data |= 0x01) : (data |= 0x00);
        LINMotorFP_SetData[_Motor_N].m_motorEmren ? (data |= 0x04) : (data |= 0x00);
        LINMotorFP_SetData[_Motor_N].m_motorEmrDir ? (data |= 0x10) : (data | 0x00);
        data |= 0x40;
        buff_value = static_cast<uchar>(data);
        buff_send_data.append(buff_value);

        data = LINMotorFP_SetData[_Motor_N].m_motorSpeed;
        buff_value = static_cast<uchar>(data);
        buff_send_data.append(buff_value);

        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
        qDebug()<<buff_send_data;
//        Nthread_CommTask->addNormalTask(buff_send_data,&resultgogo);
        sendDataToSerial(my_portIndex, buff_send_data);
        SendDataOK = 1;
        return 0;
    }
    else if(SendDataOK == 1)return 0;
    else
    {
        SendDataOK = 0;
        return 1;
    }
}



//发送编址协议
int thread_linmotor::sendMotorAddressingProtocol()
{
    uchar buff_value;
    QByteArray buff_send_data;

    if(SendDataOK == 0)
    {
        buff_send_data.append(0x68);
        buff_send_data.append(0x04);

        //站号
        buff_value = static_cast<uchar>(LINMotor_TotalSet.BoardType);//
        buff_send_data.append(buff_value);

        buff_send_data.append(0x12);//功能码
        buff_value = static_cast<uchar>(M_LIN);
        buff_send_data.append(buff_value);//板子类型

        if(LINMotor_TotalSet.Addressing_Enable)
        {
            buff_value = static_cast<uchar>(MotorStartNumber + 1);
        }
        else
        {
            buff_value = static_cast<uchar>(MotorStartNumber + 1);
            buff_value |= 0x80;
        }
        buff_send_data.append(buff_value);
        buff_value = static_cast<uchar>(MotorToralNumber);
        buff_send_data.append(buff_value);
        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
        qDebug()<<buff_send_data;
        SendDataOK = 1;
//        Nthread_CommTask->addNormalTask(buff_send_data,&resultgogo);
        sendDataToSerial(my_portIndex, buff_send_data);
        return 0;
    }
    else if(SendDataOK == 1)return 0;
    else
    {
        SendDataOK = 0;
        return 1;
    }
}
//电机初始化
int thread_linmotor::InitRun(int _Motor_N)
{
    if(LINMotor_Data[_Motor_N].m_InitState == 0x01 && (LinMotor_data[_Motor_N].CurrentStep == LINMotor_SetData[_Motor_N][Motor_run_step[_Motor_N]].m_motorSetStep))
        return 2;//初始化完成
    else if(LINMotor_Data[_Motor_N].m_InitState == 0x03)return 1;
    else if(LINMotor_Data[_Motor_N].m_InitState == 0x02)return 3;
    else
    {
        return 0;
    };
}
//电机编址完成判断
int thread_linmotor::Addressing_OK()
{
    int Addressing = 0;
    for(int i = 0; i < LINMotor_Count; i++)
    {
        Addressing = (LINMotor_Data[i].m_state & 0x30) >> 4;
        qDebug()<<"编址"<<i<<Addressing<<LINMotor_Data[i].m_state<<LINMotor_TotalSet.Addressing_Enable;
        if(LINMotorFP_SetData[i].m_motorEnabled && Addressing == 0x02 && LINMotor_TotalSet.Addressing_Enable)return 3;//编址失败
        else if(LINMotorFP_SetData[i].m_motorEnabled && (Addressing == 0x03 || Addressing == 0))return 1;//
    }
    return 2;//编址完成
}
//电机状态判断
int thread_linmotor::MotorRunStatus(int _Motor_N)
{
    int Status = 0;
    Status = LINMotor_Data[_Motor_N].m_state & 0x03;//0：待机/停止 1：堵转 2：到位 3：运行
    qDebug()<<QString("电机%1的状态%2").arg(_Motor_N).arg(Status);
    return Status;
}
//电机运行状态判断
int thread_linmotor::MotorRunResult(int _Motor_N)
{
    int Result = 0;
    Result = (LINMotor_Data[_Motor_N].m_state & 0xC0) >> 6;//0:待机 1：OK 2:NG 3:RUN
    qDebug()<<QString("电机%1的运行结果%2").arg(_Motor_N).arg(Result);
    return Result;
}

//电机数量判断
int thread_linmotor::MotorNumberJudge()
{
    MotorToralNumber = 0;
    if(LINMotor_TotalSet.Addressing_Enable)
    {
        for(int i = 0; i < LINMotor_Count; i++)
        {
            if(LINMotorFP_SetData[i].m_motorEnabled)
            {
                if(MotorToralNumber == 0)
                {
                    MotorStartNumber = i;
                }
                MotorToralNumber++;
                MotorEndNunber = i;
            }
        }
        qDebug()<<"起始电机"<<MotorStartNumber<<"终止电机"<<MotorEndNunber<<"电机数量"<<MotorToralNumber;

        if(MotorToralNumber == 1 && MotorEndNunber == MotorStartNumber)return 1;
        else if(MotorToralNumber > 1 && (MotorEndNunber + 1 - MotorStartNumber) == MotorToralNumber)return 1;
        else return 0;//编址数量错误
    }
    else
    {
        for(int i = 0; i < LINMotor_Count; i++)
        {
            if(LINMotorFP_SetData[i].m_motorEnabled)
            {
                if(MotorToralNumber == 0)
                {
                    MotorStartNumber = i;
                }
                MotorToralNumber++;
                MotorEndNunber = i;
            }
        }
        qDebug()<<"起始电机"<<MotorStartNumber<<"终止电机"<<MotorEndNunber<<"电机数量"<<MotorToralNumber;

        if(MotorToralNumber > 0)return 2;//不需要编址
        else return 0;
    }
}

void thread_linmotor::MotorInitStatus()
{
    LINMotor_basis qlist;

    MY_LINMotorIP_Setting_basis list;
    LINMotor_Return list1;
    QList<MY_LINMotorIP_Setting_basis>qlist1;

    int j = 0;

    qlist.m_state = 0;
    qlist.ErrorCode = 0;
    qlist.TempError = 0;
    qlist.PresentError = 0;
    qlist.VoltageError = 0;
    qlist.m_AddressingState = 0;
    qlist.m_InitState = 0;

    list.process = 0;
    list.m_stopTime = 0;
    list.m_motorSetStep = 0;
    list.m_motortargetStep = 0;

    list1.m_motorSWID = 0;
    list1.m_motorHWID = 0;
    list1.m_motorVariantID = 0;
    list1.m_motorJEID = 0;
    list1.m_motorSupID = 0;
    list1.m_motorFunID = 0;

    memset(list1.m_ProcessStatus, 0, sizeof (list1.m_ProcessStatus));
    memset(list1.m_ProcessStep, 0, sizeof (list1.m_ProcessStep));
    memset(list1.show_flag, 0, sizeof (list1.show_flag));

    list1.m_TotalStatus = 0;
    list1.m_TotalResult = 0;
    list1.CurrentStep = 0;

    for(j = 0; j < 8; j++)
    {
        qlist1.insert(j,list);
    }

    for(int i = 0; i < LINMotor_Count; i++)
    {
        LINMotor_Data.insert(i, qlist);
        LINMotor_SetData.insert(i,qlist1);
        LinMotor_data.insert(i, list1);
    }
}
//总电机初始化运行 返回：4：NG 3：OK 2：RUN 1:again
int thread_linmotor::MotorTotalInitRun()
{
    int state = 0;
    static int time = 0;
    for(int i = MotorStartNumber; i <= MotorEndNunber; i++)
    {
        if(LINMotor_Data[i].m_InitState == 2)//有失败的直接失败
        {
            state = 4;
        }
        else if(LINMotor_Data[i].m_InitState == 1 && LINMotorFP_SetData[i].m_motorInitRunEnabled)
        {
            if(state == 0)state = 3;
        }
        else if(LINMotor_Data[i].m_InitState == 0 && LINMotorFP_SetData[i].m_motorInitRunEnabled)//有没有启动的，
        {
            if(state != 4)state = 1;
        }
        else if(LINMotor_Data[i].m_InitState == 3 && LINMotorFP_SetData[i].m_motorInitRunEnabled)
        {
            if(state != 4 || state != 1)state = 2;
        }
    }
    if(state == 1)
    {
        if(time < 5)
        {
            time++;
            state = 2;
        }
        else
        {
            time = 0;
        }
    }
    return state;
}
//单个电机初始化
int thread_linmotor::MotorSingleInitRun(int _Motor_N)
{
    int state = 0;
    state = LINMotor_Data[_Motor_N].m_state & 0x0C;
    state >>= 2;
    qDebug()<<QString("电机%1的初始化状态%2").arg(_Motor_N).arg(state);
    return state;
}
//电机状态读取
void thread_linmotor::ReadMotorState()
{

    if(!init_readFixed){

        init_readFixed = true;
        QByteArray buff_send_data;
        uchar buff_value;

        buff_send_data.append(0x68);
        buff_send_data.append(0x03);
        buff_send_data.append('\0');
        //ID
        buff_send_data.append(0x20);

        buff_value = static_cast<uchar>(M_LIN);
        buff_send_data.append(buff_value);//板子类型

        buff_value = static_cast<uchar>(MotorToralNumber);//电机数量
        buff_send_data.append(buff_value);

        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
        //Nthread_CommTask->Read_finish = true;
    //    Nthread_CommTask->addFixedTask(buff_send_data,&resultgogo);
//        sendDataToSerial(my_portIndex, buff_send_data);
        addFixedToSerial(my_portIndex, buff_send_data, &readFixed_en);

        //readFixed_en = true;
    }

    readFixed_en = true;

}
//电机版本读取
int thread_linmotor::ReadMotorVersion(int _Motor_N)
{
    uchar buff_value;
    QByteArray buff_send_data;
    if(SendDataOK == 0)
    {
        buff_send_data.append(0x68);
        buff_send_data.append(0x03);

        //站号
        buff_value = static_cast<uchar>(LINMotor_TotalSet.BoardType);//
        buff_send_data.append(buff_value);

        buff_send_data.append(0x21);//功能码
        buff_value = static_cast<uchar>(M_LIN);
        buff_send_data.append(buff_value);//板子类型

        buff_value = static_cast<uchar>(_Motor_N + 1);//电机号
        buff_send_data.append(buff_value);

        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
//        Nthread_CommTask->addNormalTask(buff_send_data,&resultgogo);
        sendDataToSerial(my_portIndex, buff_send_data);
        SendDataOK = 1;
        return 0;
    }
    else if(SendDataOK == 1)return 0;
    else
    {
        SendDataOK = 0;
        return 1;
    }
}
//控制单个电机停止
int thread_linmotor::sendMotorStopProtocol(int _Motor_N)
{
    uchar buff_value;
    QByteArray buff_send_data;
    if(SendDataOK == 0)
    {
        buff_send_data.append(0x68);
        buff_send_data.append(0x33);
        //站号
        buff_value = static_cast<uchar>(LINMotor_TotalSet.BoardType);//
        buff_send_data.append(buff_value);

        buff_value = static_cast<uchar>(M_LIN);
        buff_send_data.append(buff_value);//板子类型

        buff_value = static_cast<uchar>(MotorToralNumber);//电机数量
        buff_send_data.append(buff_value);

        for(int i = 0; i < LINMotor_Count; i++)
        {
            if(i == _Motor_N)
            {
                buff_send_data.append(0x04);//控制码
                buff_send_data.append(3,'\0');
            }
            else buff_send_data.append(4,'\0');
        }

        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
        qDebug()<<buff_send_data;

//        Nthread_CommTask->addNormalTask(buff_send_data,&resultgogo);
        sendDataToSerial(my_portIndex, buff_send_data);
        SendDataOK = 1;
        return 0;
    }
    else if(SendDataOK == 1)return 0;
    else
    {
        SendDataOK = 0;
        return 1;
    }
}
//数据处理
void thread_linmotor::DataProcessing(QByteArray _reData, int _MotorID)
{
    int FunctionCode = 0;//临时功能
    int *Data;
//    qDebug()<<"刘有数据进来le";
    // 存储十进制结果的数组
    QVector<int> decimalArray;
    int DataNumber = 0;
    for (int i = 0; i < _reData.size(); ++i) {
        decimalArray.append(static_cast<unsigned char>(_reData[i]));
        DataNumber++;
    }
    ProcessStepsTime = 0;
//     qDebug()<<"刘接收到的数据"<<decimalArray<<"接收的数据长度"<<_reData.size();
    FunctionCode = decimalArray[3];//功能码

    if(FunctionCode == 0x01)//读取板子信息
    {
        Data = &decimalArray[4];
        LINMotor_TotalSet.BoardType = Data[0];
        LINMotor_TotalSet.SoftwareVersion = Data[1];
        LINMotor_TotalSet.HardwareVersion = Data[2];
    }
    else if(FunctionCode == 0x20)//电机
    {
        Data = &decimalArray[6];
        for(int i = 0; i < LINMotor_Count; i++)
        {
            LINMotor_Data[i].m_state = Data[i * 4];
            LINMotor_Data[i].m_AddressingState = (LINMotor_Data[i].m_state & 0x30) >> 4;
            LINMotor_Data[i].m_InitState = (LINMotor_Data[i].m_state & 0x0C) >> 2;
            LinMotor_data[i].CurrentStep = Data[1 + i * 4] + Data[2 + i * 4] * 256;
            LINMotor_Data[i].ErrorCode = Data[3 + i * 4];
        }
    }
    else if(FunctionCode == 0x21)
    {
        Data = &decimalArray[6];
        LinMotor_data[_MotorID - 1].m_motorSWID = Data[0];
        LinMotor_data[_MotorID - 1].m_motorHWID = Data[1];
        LinMotor_data[_MotorID - 1].m_motorVariantID = Data[2];
        LinMotor_data[_MotorID - 1].m_motorJEID = Data[3] + Data[4] * 256;
        LinMotor_data[_MotorID - 1].m_motorSupID = Data[5] + Data[6] * 256;
        LinMotor_data[_MotorID - 1].m_motorFunID = Data[7] + Data[8] * 256;
        SendDataOK = 3;
    }
    else if(FunctionCode == 0x30)
    {
    }
    else//控制返回判断
    {
        if(FunctionCode == 0x10)//控制电机全部停止
        {
        }
        else if(FunctionCode == 0x11)//写入电机参数
        {
        }
        else if(FunctionCode == 0x12)//控制电机写地址
        {
            if(ProcessSteps == 4)ProcessSteps = 5;
        }
        else if(FunctionCode == 0x13)//控制电机作动
        {
        }
        else if(FunctionCode == 0x14)//自由协议控制
        {
        }
        else if(FunctionCode == 0x33)//设置协议版本、波特率
        {
        }
        SendDataOK = 3;
    }
}

LINMotorTotal_basis thread_linmotor::reBasicParameters()
{
    return LINMotor_TotalSet;
}

QList<LINMotor_Return> thread_linmotor::reLinRealTimeData()
{
    return LinMotor_data;
}

int thread_linmotor::getProcessStatus()
{
    return Total_Status;
}

int thread_linmotor::getProcessResult()
{
    return Total_Result;
}
//复位整体的结果和状态
void thread_linmotor::restProcessResultAndStatus()
{
    Total_Status = 0;
    Total_Result = 0;
}

void thread_linmotor::MotorRunProcess(int _Motor_N, bool _Enable)
{
    ProcessEN[_Motor_N] = _Enable;
}
//手动模式控制电机初始化
void thread_linmotor::Manual_Init(int _MotorID, int _SetStep)
{
    LINMotorFP_SetData[_MotorID].m_motorInitRunSetStep = _SetStep;
    TemporaryFlage[_MotorID] = 1;
}
//手动模式控制电机运行到目标步数
void thread_linmotor::Manual_Run(int _MotorID, int _TargetStep)
{
    Now_targetStep[_MotorID] = _TargetStep;
    Now_stepError[_MotorID] = 0;
    TemporaryFlage[_MotorID] = 2;
}
//手动模式走左极限
void thread_linmotor::Manual_LeftLimitRun(int _MotorID)
{
    TemporaryFlage[_MotorID] = 5;
}
//手动模式走右极限
void thread_linmotor::Manual_RightLimitRun(int _MotorID)
{
    TemporaryFlage[_MotorID] = 6;
}
/*
* @description 发送串口数据，区分串口分发到对应的处理线程
* @param {int} portIndex 串口号编号
* @param {QByteArray &} date 发送数据
* @returns {void} 无
* @date 2025-10-24 11:22:00
* @author zh
*/
void thread_linmotor::sendDataToSerial(int portIndex, const QByteArray &data)
{
    qDebug()<<"LIN线程：添加任务"<<portIndex<<data;
    switch (portIndex) {
        case 0:
            Nthread_CommTask[0]->addNormalTask(data);
            break;
        case 1:
            Nthread_CommTask[1]->addNormalTask(data);
            break;
        case 2:
            Nthread_CommTask[2]->addNormalTask(data);
            break;
        default:
            Nthread_CommTask[0]->addNormalTask(data);
            break;
     }
}

/*
* @description 发送串口数据，区分串口分发到对应的处理线程
* @param {int} portIndex 串口号编号
* @param {QByteArray &} date 发送数据
* @returns {void} 无
* @date 2025-10-24 11:22:00
* @author zh
*/
void thread_linmotor::addFixedToSerial(int portIndex, const QByteArray &data,bool *_en)
{
    qDebug()<<"LIN线程：添加固定任务"<<portIndex<<data;
    switch (portIndex) {
        case 0:
            Nthread_CommTask[0]->addFixedTask(data,_en);
            break;
        case 1:
            Nthread_CommTask[1]->addFixedTask(data,_en);
            break;
        case 2:
            Nthread_CommTask[2]->addFixedTask(data,_en);
            break;
        default:
            Nthread_CommTask[0]->addFixedTask(data,_en);
            break;
     }
}

