#include "thread_ptmotor.h"
thread_ptmotor* Nthread_ptmotor = nullptr;

QMutex thread_ptmotor::m_instanceMutex; // 关键：类外定义，分配内存

thread_ptmotor::thread_ptmotor(QObject *parent)
    : QObject(parent)
    , threadState(false)
{
    DelayTimer = new QTimer(this);
    InitPtData();
}

thread_ptmotor::~thread_ptmotor()
{
    // 清理资源
}

thread_ptmotor* thread_ptmotor::getInstance()
{
    // 双重检查锁定（提高效率，避免每次获取实例都加锁）
    if (!Nthread_ptmotor) {
        QMutexLocker locker(&m_instanceMutex);  // 加锁确保线程安全
        if (!Nthread_ptmotor) {
            Nthread_ptmotor = new thread_ptmotor();
        }
    }
    return Nthread_ptmotor;
}

void thread_ptmotor::ProcessStop()
{
    ProcessStart_flag = false;
    for(int i =0;i<12;i++)
    {
        Stop_ReadState(i);
    }

}




void thread_ptmotor::setPTMotorSettings(QList<PTMotorFP_Setting_basis> settings)
{
    m_ptMotorSettings = settings;

}

void thread_ptmotor::setPTMotorSettings1(QList<PTMotorFP_Setting_basis1> settings1)
{
    m_ptMotorSettings1 = settings1;



    for(int i=0;i<PtMotor_Count;i++)
    {
        QStringList MaxValue = m_ptMotorSettings1.at(i).m_MaxValue.split(",");
        QStringList MinValue = m_ptMotorSettings1.at(i).m_MinValue.split(",");
        for(int j=0;j<8;j++)
        {
            if(MaxValue.count()>=8)
            {
                m_ptMotorStatus[i].V_UpperLimit[j] = MaxValue.at(j).toDouble();
                m_ptMotorStatus[i].V_LowerLimit[j] = MinValue.at(j).toDouble();
            }

        }
    }

}



// 发送检测开度命令
bool thread_ptmotor::SendDetectionOpeningCommand(int motorIndex)
{
    if(Receive_Flag[motorIndex] == 0|| Motor_state[motorIndex] != 0) return false; // 等待上次命令完成

    qDebug()<<"返回状态没问题，开始走开度";
    QStringList MaxValueList = m_ptMotorSettings1.at(motorIndex).m_MaxValue.split(",");
    QStringList MinValueList = m_ptMotorSettings1.at(motorIndex).m_MinValue.split(",");

    int currentPOSIndex = motor_nowprocess[motorIndex];
    m_ptMotorStatus[motorIndex].POSStatus[motor_nowprocess[motorIndex]]=1;
    Receive_Flag[motorIndex] = 0;
    SendPtMotorDetectionOpening(
                m_ptMotorSettings.at(motorIndex).m_name,
                m_ptMotorSettings.at(motorIndex).m_id,
                m_ptMotorSettings.at(motorIndex).m_motorType,
                m_ptMotorSettings.at(motorIndex).m_motorNumber,
                m_ptMotorSettings.at(motorIndex).m_motorDirection,
                MaxValueList.at(currentPOSIndex).toDouble() * 10000,
                MinValueList.at(currentPOSIndex).toDouble() * 10000,
                m_ptMotorSettings.at(motorIndex).m_stallCurrent,
                m_ptMotorSettings.at(motorIndex).m_currentLowerLimit,
                m_ptMotorSettings.at(motorIndex).m_timeoutMs
                );


    return true;
}

// 发送走POS命令
bool thread_ptmotor::SendRunPOSCommand(int motorIndex)
{
    //    qDebug()<<"当前标志位如下1："<<Receive_Flag[motorIndex]<<"当前标志位如下2："<< static_cast<int>(Motor_state[motorIndex])  << "结束";
    if(Receive_Flag[motorIndex] == 0 || Motor_state[motorIndex] != 0) return false; // 等待上次命令完成

    qDebug()<<"返回状态没问题，开始走POS";
    QStringList MaxValueList = m_ptMotorSettings1.at(motorIndex).m_MaxValue.split(",");
    QStringList MinValueList = m_ptMotorSettings1.at(motorIndex).m_MinValue.split(",");

    int currentPOSIndex = motor_nowprocess[motorIndex];
    //    POS_Over[motorIndex][currentPOSIndex] =1; //档位状态 0：未运行 1：RUN 2：OK 3：NG
    m_ptMotorStatus[motorIndex].POSStatus[motor_nowprocess[motorIndex]]=1;
    Receive_Flag[motorIndex] = 0;
    SendPtMotorOperation(
                m_ptMotorSettings.at(motorIndex).m_name,
                m_ptMotorSettings.at(motorIndex).m_id,
                m_ptMotorSettings.at(motorIndex).m_motorType,
                m_ptMotorSettings.at(motorIndex).m_motorNumber,
                MaxValueList.at(currentPOSIndex).toDouble() * 10000,
                MinValueList.at(currentPOSIndex).toDouble() * 10000,
                m_ptMotorSettings.at(motorIndex).m_currentUpperLimit,
                m_ptMotorSettings.at(motorIndex).m_currentLowerLimit,
                m_ptMotorSettings.at(motorIndex).m_timeoutMs
                );

    //68 0d 00 12 01 02 0028238813dc050100e80d0a
    return true;
}

// 检查电机执行完成状态
bool thread_ptmotor::CheckMotorCompletion(int motorIndex)
{
    if(Receive_Flag[motorIndex] == 1 && Motor_state[motorIndex] == 1) {
        Receive_Flag[motorIndex] = 0;
        //        ReadPtMotorStatus(
        //                    m_ptMotorSettings.at(motorIndex).m_name,
        //                    m_ptMotorSettings.at(motorIndex).m_id,
        //                    m_ptMotorSettings.at(motorIndex).m_motorType,
        //                    m_ptMotorSettings.at(motorIndex).m_motorNumber
        //                    );

        Start_ReadState(motorIndex);
        return false;
    }

    // 检查电机状态，如果停止则表示完成
    if(Motor_state[motorIndex] == 0) {
        qDebug()<<"电机"<<QString::number(motorIndex)<<"当前状态为停止";


        return true;
    }


    return false;
}

// 处理延时和转到下一步
bool thread_ptmotor::ProcessDelayAndNext(int motorIndex)
{
    QStringList DelayTimeList = m_ptMotorSettings1.at(motorIndex).m_Time.split(",");
    int currentPOSIndex = motor_nowprocess[motorIndex];

    if(currentPOSIndex < DelayTimeList.count()) {
        double delayTime = DelayTimeList.at(currentPOSIndex).toDouble();
        if(delayTime > 0) {
            StartDelayTime(delayTime * 10);
            qDebug()<<"线程睡眠";
        }
    }

    return true;
}


void thread_ptmotor::doWork()
{

    qDebug() << "PT线程开始 - 使用moveToThread方式";

    threadState = true;

    // 定义流程步骤相关变量

    //            Receive_Flag =0;
    int judgment = 0;

    // 初始化电机使能状态
    //    for(int i = 0; i < 12; i++) {
    //        motor_Enabled[i] = m_ptMotorSettings.at(i).m_motorEnabled;
    //    }

    while(threadState) {


        if(ProcessSteps == 0) {
            // 步骤0: 初始化
            judgment = 0;
            memset(motor_ProcessStep, 0, sizeof(motor_ProcessStep));
            memset(motor_nowprocess, 0, sizeof(motor_nowprocess));
            ProcessSteps = 1;

            qDebug() << "进入步骤0: 初始化";
        }
        else if(ProcessSteps == 1) {
            if(!All_Ptmotors_Success)
            {
                MotorParameterInit();
            }
            if(All_Ptmotors_Success) {
                ProcessSteps = 2;
                qDebug() << "进入步骤2: 参数发送完成";
            }
        }
        else if(ProcessSteps == 2) {
            //            if(ProcessStart_flag)
            //            {
            // 步骤3: 电机运行主流程
            bool allMotorsCompleted = true;

            for(int i = 0; i < 12; i++) {

                if(m_ptMotorSettings.at(i).m_motorEnabled && Pt[i] == 1)
                {
                    //                    qDebug()<<"当前电机为"<<QString::number(i)<<"当前电机motor_ProcessStep[i]值："<<motor_ProcessStep[i];
                    allMotorsCompleted = false;
                    ProcessStatus = 1;
                    if(motor_ProcessStep[i] == 0) {

                        Start_ReadState(i);//开启固定任务

                        // 子步骤0: 准备运行当前POS
                        QStringList POSList = m_ptMotorSettings1.at(i).m_POS.split(",");
                        QStringList DelayTimeList = m_ptMotorSettings1.at(i).m_Time.split(",");
                        QStringList MaxValueList = m_ptMotorSettings1.at(i).m_MaxValue.split(",");
                        QStringList MinValueList = m_ptMotorSettings1.at(i).m_MinValue.split(",");

                        if(motor_nowprocess[i] < POSList.count() && motor_nowprocess[i] < 8) {
                            m_ptMotorStatus[i].m_TotalStatus = 1;
                            int currentPOS = POSList.at(motor_nowprocess[i]).toInt();

                            qDebug()<<"电机"<<i<<"当前POS："<<currentPOS;
                            //                            qDebug() << "开始获取数据";
                            if(currentPOS == 7 ) {
                                // 检测开度流程
                                qDebug()<<"流程为走开度";
                                motor_ProcessStep[i] = 1;
                                m_ptMotorStatus[i].m_type[motor_nowprocess[i]] = 1;



                            }else if(currentPOS == 8)
                            {
                                motor_ProcessStep[i] = 1;
                                m_ptMotorStatus[i].m_type[motor_nowprocess[i]] = 2;
                            }

                            else {
                                // 走POS流程
                                qDebug()<<"流程为走POS";
                                if(currentPOS==0)
                                {
                                    motor_nowprocess[i]++;
                                }
                                else
                                {
                                    motor_ProcessStep[i] = 2;
                                    m_ptMotorStatus[i].m_type[motor_nowprocess[i]] = 0;
                                }

                            }
                        }
                        else {
                            // 所有POS完成
                            qDebug()<<"电机运行完成"+QString::number(i);

                            motor_ProcessStep[i] = 4;
                        }
                    }
                    else if(motor_ProcessStep[i] == 1) {
                        // 子步骤1: 发送检测开度命令
                        qDebug()<<"发送开度命令"<<Receive_Flag[i];
                        if(SendDetectionOpeningCommand(i)) {
                            Motor_state[i] = 1;
                            motor_ProcessStep[i] = 3;
                            //                            my_Recevie_flag[i] = false;
                            Deley_Elaps[i].restart();
                        }
                    }
                    else if(motor_ProcessStep[i] == 2) {
                        // 子步骤2: 发送走POS命令
                        qDebug()<<"当前电机"+QString::number(i);
                        if(SendRunPOSCommand(i)) {

                            qDebug()<<"进入发送运行命令"<<Receive_Flag[i];
                            Motor_state[i] = 1;
                            motor_ProcessStep[i] = 3;
                            //                            my_Recevie_flag[i] = false;
                            Deley_Elaps[i].restart();
                        }
                    }
                    else if(motor_ProcessStep[i] == 3){
                        //延时
                        double testTime;

                        testTime = (double)Deley_Elaps[i].nsecsElapsed() / (double)1000000 / (double)1000; //s
                        if(testTime > 1 && my_Recevie_flag[i]){//S  大于该描数还未接收为接收失败
                            motor_ProcessStep[i] = 30;
                        }
                    }
                    else if(motor_ProcessStep[i] == 30) {
                        // 子步骤3: 等待执行完成并读取状态
                        //                        qDebug()<<"读取访问判断";
                        if(CheckMotorCompletion(i))
                        {
                            UpData_ShowValue[i][motor_nowprocess[i]] = false;


                            QStringList DelayTimeList = m_ptMotorSettings1.at(i).m_Time.split(",");
                            int currentPOSIndex = motor_nowprocess[i];
                            if(currentPOSIndex <= 6){
                                delayTime[i] = DelayTimeList.at(currentPOSIndex).toDouble();
                            }else{
                                delayTime[i] = 0;
                            }
                            Deley_Elaps[i].restart();

                            motor_ProcessStep[i] = 31;
                        }
                        else
                        {
                            qDebug()<<"【电机状态】电机当前正在运行"<<motor_nowprocess[i];

                        }
                    }
                    else if(motor_ProcessStep[i] == 31) {

                        //延时
                        double testTime;

                        testTime = (double)Deley_Elaps[i].nsecsElapsed() / (double)1000000 / (double)1000; //s
                        if(testTime > delayTime[i]){//S  大于该描数还未接收为接收失败
                            // 执行完成，处理延时和下一步
                            qDebug()<<"POS开始加1";
                            //                            POS_Over[i][motor_nowprocess[i]] =0;
                            m_ptMotorStatus[i].POSStatus[motor_nowprocess[i]]=2;
                            motor_nowprocess[i]++;
                            motor_ProcessStep[i] = 0;
                            qDebug()<<"【电机状态】电机POS开始加1";
                        }
                    }

                    else if(motor_ProcessStep[i] == 4) {
                        // 子步骤4: 电机运行完成
                        Stop_ReadState(i);
                        qDebug() << "电机" << i << "运行完成,停止访问固定任务";
                        //                        Stop_ReadState(i);
                        Pt[i] = 2;
                        m_ptMotorStatus[i].m_TotalStatus = 0;
                        m_ptMotorStatus[i].m_TotalResult= 1;//结果：默认是0，OK为1，NG为错误代码
                        //                        int m_TotalStatus= 0;//总状态 状态：停止为0，运行为1
                        //                        int m_TotalResult= 0;//结果：默认是0，OK为1，NG为错误代码
                    }
                    else if(motor_ProcessStep[i] == 5)
                    {
                        Pt[i] = 2;
                        Stop_ReadState(i);
                        qDebug() << "电机" << i << "运行故障";
                        m_ptMotorStatus[i].m_TotalStatus = 0;
                        m_ptMotorStatus[i].m_TotalResult= 2;//结果：默认是0，OK为1，NG为错误代码

                        qDebug()<< "电机" << i << "检测过程中NG";
                    }
                }
            }


            if(allMotorsCompleted) {
                ProcessSteps = 4;
                qDebug() << "进入步骤4: 所有电机运行完成";
                bool RunStatus = true;
                ProcessStatus = 0;
                for(int i = 0; i < 12; i++) {

                    if(m_ptMotorStatus[i].m_TotalResult ==2)
                    {
                        RunStatus = false;
                    }

                }
                if(RunStatus)
                {

                    ProcessResult = 1;
                }
                else
                {
                    ProcessResult = 2;
                }


            }
        }
        //        }
        else if(ProcessSteps == 4) {
            // 步骤4: 完成状态，可以重置或等待新指令
            // 这里可以添加重置逻辑或等待新任务
            QThread::msleep(100);
        }
        QCoreApplication::processEvents();
        QThread::msleep(10);
    }
    qDebug() << "PT线程结束";
    emit workFinished();
}


void thread_ptmotor::Receive_DataProcessing(QByteArray Data,int index)
{
    Data = Data.toHex();
    qDebug()<<"接收到数据"<<Data<<index;

    int startPos= 0;
    int byteCount =0;
    int ID=0,Motornum=0;

    startPos = 4; // 起始位置
    byteCount = 2; // 4字节 = 8个16进制字符
    if(startPos + byteCount <= Data.size()) {
        QByteArray hexPart = Data.mid(startPos, byteCount);
        bool ok;
        ID  = hexPart.toInt(&ok, 16);
    }

    startPos = 10; // 起始位置
    byteCount = 2; // 4字节 = 8个16进制字符
    if(startPos + byteCount <= Data.size()) {
        QByteArray hexPart = Data.mid(startPos, byteCount);
        bool ok;
        Motornum  = hexPart.toInt(&ok, 16);
    }



    if(Data.mid(6,2) == "10")//判断停止功能码
    {
        qDebug()<<"进入判断停止功能码";
    }
    else if(Data.mid(6,2) == "11")//判断运行功能码
    {
        //        Motornum = 2;
        qDebug()<<"进入判断运行功能码";
        Receive_Flag[ID*2+Motornum-1]=1;
        my_Recevie_flag[ID*2+Motornum-1] = true;
    }
    else if(Data.mid(6,2) == "12")//判断检测开度功能码
    {
        qDebug()<<"进入判断检测开度功能码";
        Receive_Flag[ID*2+Motornum-1]=1;

    }
    else if(Data.mid(6,2) == "13")//判断2线电机控制功能码
    {
        qDebug()<<"进入判断2线电机控制功能码";
    }
    else if(Data.mid(6,2) == "14")//判断手动控制功能码
    {
        qDebug()<<"进入判断手动控制功能码";
    }
    else if(Data.mid(6,2) == "20")//判断写入参数功能码
    {
        qDebug()<<"进入判断写入参数功能码";
        for(int i = 0;i< m_ptMotorSettings.count();i++)//查询返回来的ID电机
        {
            if(m_ptMotorSettings.at(i).m_id == Data.mid(4,2).toInt()&&m_ptMotorSettings.at(i).m_motorNumber == Data.mid(10,2).toInt())//判断返回来的电机写入完成
            {
                m_ptMotorSettings[i].b_Received = false;
            }
        }
        bool All_PtSuccess = true;  // 先假设全部成功
        for(int i = 0;i< m_ptMotorSettings.count();i++)//查询返回来的ID电机
        {
            if(m_ptMotorSettings.at(i).b_Received == false)//判断返回来的电机全都写入完成
            {
                All_PtSuccess = true;  // 置位为true
                //                qDebug()<<"全部电机写入完成";

            }
            else
            {
                All_PtSuccess = false;  // 置位为true
                break;
            }
        }
        if(All_PtSuccess)
        {
            All_Ptmotors_Success = true;
        }
        else
        {
            All_Ptmotors_Success = false;
        }
        Received_Success=1;
        Receive_Flag[ID*2+Motornum-1]=1;


    }
    else if(Data.mid(6,2) == "30")//判断读取状态参数功能码
    {
        qDebug()<<"进入判断读取状态参数功能码";
        if(1)
        {
            int startPos= 0;
            int byteCount =0;
            int CurrentState=0;
            int FunctionCode =0;//功能码
            QString CurrentV=0,CurrentA=0;
            startPos = 4; // 起始位置
            byteCount = 2; // 4字节 = 8个16进制字符
            if(startPos + byteCount <= Data.size()) {
                QByteArray hexPart = Data.mid(startPos, byteCount);
                bool ok;
                ID  = hexPart.toInt(&ok, 16);
            }
            //            startPos = 6; // 起始位置
            //            byteCount = 2; // 4字节 = 8个16进制字符
            //            if(startPos + byteCount <= Data.size()) {
            //                QByteArray hexPart = Data.mid(startPos, byteCount);
            //                bool ok;
            //                FunctionCode  = hexPart.toInt(&ok, 16);
            //            }
            startPos = 10; // 起始位置
            byteCount = 2; // 4字节 = 8个16进制字符
            if(startPos + byteCount <= Data.size()) {
                QByteArray hexPart = Data.mid(startPos, byteCount);
                bool ok;
                Motornum  = hexPart.toInt(&ok, 16);
            }
            startPos = 12; // 起始位置
            byteCount = 4; // 4字节 = 8个16进制字符
            if(startPos + byteCount <= Data.size()) {
                QByteArray hexPart = Data.mid(startPos, byteCount);
                QByteArray swapped;
                for(int i = hexPart.size()-2; i >= 0; i -= 2) {
                    swapped.append(hexPart.mid(i, 2));
                }

                bool ok;
                CurrentV = QString::number(swapped.toInt(&ok, 16) / 10000.0, 'f', 2);
            }
            startPos = 16; // 起始位置
            byteCount = 4; // 4字节 = 8个16进制字符
            if(startPos + byteCount <= Data.size()) {
                QByteArray hexPart = Data.mid(startPos, byteCount);
                QByteArray swapped;
                for(int i = hexPart.size()-2; i >= 0; i -= 2) {
                    swapped.append(hexPart.mid(i, 2));
                }
                bool ok;
                CurrentA = QString::number(swapped.toInt(&ok, 16) / 1000.0, 'f', 3);
            }
            startPos = 22; // 起始位置
            byteCount = 2; // 4字节 = 8个16进制字符
            if(startPos + byteCount <= Data.size()) {
                QByteArray hexPart = Data.mid(startPos, byteCount);
                bool ok;
                CurrentState  = hexPart.toInt(&ok, 16);
            }
            qDebug()<<"接收参数"<<"ID:"<<ID<<"电机号:"<<Motornum<<"位置电压:"<<CurrentV<<"位置电流:"<<CurrentA<<"当前状态:"<<CurrentState;
            m_ptMotorStatus[ID*2+Motornum-1].Current_A = CurrentA.toDouble();
            m_ptMotorStatus[ID*2+Motornum-1].Current_V = CurrentV.toDouble();
            //             POSStatus[currentPOSIndex] = {0};
            //          int m_TotalStatus= 0;//总状态 状态：停止为0，运行为1
            //          int m_TotalResult= 0;//结果：默认是0，OK为1，NG为错误代码
            //            int POSStatus[8] = {0};//档位状态 0：未运行 1：RUN 2：OK 3：NG
            //          int V_UpperLimit[8] = {0};//电压上限
            //          int V_LowerLimit[8] = {0};//电压下限
            //            int POS_V[8] = {0};//电压
            //            int POS_A[8] = {0};//电流
            //            bool show_flag[8] = {0};//显示完成状态,功能模块在启动时复位，这个POS显现完成后主流程置为true


            if((CurrentState == 0x00 || CurrentState == 0x16)/*&&Motor_state[ID*2+Motornum-1] ==1*/)//判断当前电机转态是否停止
            {
                //                qDebug()<<"-------------------------------"<<motor_nowprocess[ID*2+Motornum-1];

                if(UpData_ShowValue[ID*2+Motornum-1][motor_nowprocess[ID*2+Motornum-1]]){
                    m_ptMotorStatus[ID*2+Motornum-1].POS_V[motor_nowprocess[ID*2+Motornum-1]]=CurrentV.toDouble();
                    m_ptMotorStatus[ID*2+Motornum-1].POS_A[motor_nowprocess[ID*2+Motornum-1]]=CurrentA.toDouble();
                }
                //               POS_Over[ID*2+Motornum-1][motor_nowprocess[ID*2+Motornum-1]] = 1;

                Motor_state[ID*2+Motornum-1] = 0;//电机完成当前命令，可进行下一步
                qDebug()<<"【电机状态】电机已经停止，可以进入到下一个POS"<<Data;
            }
            else if(CurrentState == 0x13)
            {
                if(UpData_ShowValue[ID*2+Motornum-1][motor_nowprocess[ID*2+Motornum-1]]){
                    m_ptMotorStatus[ID*2+Motornum-1].POSStatus[motor_nowprocess[ID*2+Motornum-1]]=3;

                    m_ptMotorStatus[ID*2+Motornum-1].POS_V[motor_nowprocess[ID*2+Motornum-1]]=CurrentV.toDouble();
                    m_ptMotorStatus[ID*2+Motornum-1].POS_A[motor_nowprocess[ID*2+Motornum-1]]=CurrentA.toDouble();
                }
                Motor_state[ID*2+Motornum-1] = 1;
                qDebug()<<"电机"<<QString::number(ID*2+Motornum-1)<< "电流超上限，NG停止";
                motor_ProcessStep[ID*2+Motornum-1] = 5;
            }
            else if( CurrentState == 0x14)
            {
                if(UpData_ShowValue[ID*2+Motornum-1][motor_nowprocess[ID*2+Motornum-1]]){
                    m_ptMotorStatus[ID*2+Motornum-1].POSStatus[motor_nowprocess[ID*2+Motornum-1]]=3;
                    m_ptMotorStatus[ID*2+Motornum-1].POS_V[motor_nowprocess[ID*2+Motornum-1]]=CurrentV.toDouble();
                    m_ptMotorStatus[ID*2+Motornum-1].POS_A[motor_nowprocess[ID*2+Motornum-1]]=CurrentA.toDouble();
                }
                Motor_state[ID*2+Motornum-1] = 1;//电机电流超下限，NG停止
                qDebug()<<"电机"<<QString::number(ID*2+Motornum-1)<< "电流超下限，NG停止";
                motor_ProcessStep[ID*2+Motornum-1] = 5;
            }
            else if(CurrentState == 0x15)
            {
                if(UpData_ShowValue[ID*2+Motornum-1][motor_nowprocess[ID*2+Motornum-1]]){
                    m_ptMotorStatus[ID*2+Motornum-1].POSStatus[motor_nowprocess[ID*2+Motornum-1]]=3;
                    m_ptMotorStatus[ID*2+Motornum-1].POS_V[motor_nowprocess[ID*2+Motornum-1]]=CurrentV.toDouble();
                    m_ptMotorStatus[ID*2+Motornum-1].POS_A[motor_nowprocess[ID*2+Motornum-1]]=CurrentA.toDouble();
                }
                Motor_state[ID*2+Motornum-1] = 1;//电机超时，NG停止
                qDebug()<<"电机"<<QString::number(ID*2+Motornum-1)<< "超时，NG停止";
                motor_ProcessStep[ID*2+Motornum-1] = 5;
            }
            else if(CurrentState == 0x20)
            {
                if(UpData_ShowValue[ID*2+Motornum-1][motor_nowprocess[ID*2+Motornum-1]]){
                    m_ptMotorStatus[ID*2+Motornum-1].POSStatus[motor_nowprocess[ID*2+Motornum-1]]=3;
                    m_ptMotorStatus[ID*2+Motornum-1].POS_V[motor_nowprocess[ID*2+Motornum-1]]=CurrentV.toDouble();
                    m_ptMotorStatus[ID*2+Motornum-1].POS_A[motor_nowprocess[ID*2+Motornum-1]]=CurrentA.toDouble();
                }
                Motor_state[ID*2+Motornum-1] = 1;//电机堵转，设置范围小，超上限
                qDebug()<<"电机"<<QString::number(ID*2+Motornum-1)<< "堵转，设置范围小，超上限";
                motor_ProcessStep[ID*2+Motornum-1] = 5;
            }
            else if(CurrentState == 0x21)
            {
                if(UpData_ShowValue[ID*2+Motornum-1][motor_nowprocess[ID*2+Motornum-1]]){
                    m_ptMotorStatus[ID*2+Motornum-1].POSStatus[motor_nowprocess[ID*2+Motornum-1]]=3;
                    m_ptMotorStatus[ID*2+Motornum-1].POS_V[motor_nowprocess[ID*2+Motornum-1]]=CurrentV.toDouble();
                    m_ptMotorStatus[ID*2+Motornum-1].POS_A[motor_nowprocess[ID*2+Motornum-1]]=CurrentA.toDouble();
                }
                Motor_state[ID*2+Motornum-1] = 1;//电机堵转，设置范围大，超下限
                qDebug()<<"电机"<<QString::number(ID*2+Motornum-1)<< "堵转，设置范围大，超下限";
                motor_ProcessStep[ID*2+Motornum-1] = 5;
            }
            else{
                Motor_state[ID*2+Motornum-1] = 1;//电机完成当前命令，可进行下一步
            }

            //            CurrentPos = PtMotorOver[ID*2+Motornum][0];
            //            emit SendMotortatus("PT",ID,Motornum,CurrentV,CurrentA,CurrentPos,CurrentState);
        }
        //        my_Recevie_flag[ID*2+Motornum-1] = true;
        Receive_Flag[ID*2+Motornum-1]=1;
        qDebug()<<"读取判断结束";
    }
    qDebug()<<"退出接收分析函数";
}



/*
* @description 发送串口数据，发送电机停止
* @param {QString} PTName 伺服电机名字
* @param {int} PT_ID 电机ID
* @param {int} Broad_type 主板板号
* @param {int} Motor_Num 电机号
* @returns {void} 无
* @date 2025-10-28 10:55:00
* @author lh
*/
void thread_ptmotor::SendPtMotorStop(QString PTName,int PT_ID,int Broad_type,int Motor_Num)//发送电机停止
{
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0x00)); // 长度占位符
    buff_send_data.append(PT_ID);//ID
    buff_send_data.append(0x10);//功能码
    buff_send_data.append(Broad_type);//板子类型
    buff_send_data.append(Motor_Num);//电机号
    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符
    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段
    //      emit SendData1(buff_send_data);
    //    Nthread_CommTask->addNormalTask(PTName,buff_send_data,&resultgogo);
    sendDataToSerial(0,buff_send_data);
}


/*
* @description 发送串口数据，电机固定参数
* @param {QString} PTName 伺服电机名字
* @param {int} PT_ID 电机ID
* @param {int} Broad_type 主板板号
* @param {int} Motor_Num 电机号
* * @param {int} StartDelay 启动延时
* * @param {int} AlarmDelay 报警延时
* * @param {int} V_AverageCount 电压平均次数
* * @param {int} A_AverageCount 电流平均次数
* * @param {int} RunDirection 运行方向
* @returns {void} 无
* @date 2025-10-25 09:36:00
* @author lh
*/
void thread_ptmotor::SendPtMotorFixedParameter(QString PTName,int PT_ID,int Broad_type,int Motor_Num,int StartDelay,int AlarmDelay,int V_AverageCount,int A_AverageCount,int RunDirection)//设置电机参数
{
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0x00)); // 长度占位符
    buff_send_data.append(PT_ID);//ID
    buff_send_data.append(0x20);//功能码
    buff_send_data.append(Broad_type);//板子类型
    buff_send_data.append(Motor_Num);//电机号
    buff_send_data.append(StartDelay);//启动延时
    buff_send_data.append(AlarmDelay);//报警延时
    buff_send_data.append(V_AverageCount);//电压平均次数
    buff_send_data.append(A_AverageCount);//电流平均次数
    buff_send_data.append(RunDirection);//运行方向
    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符
    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段
    qDebug()<<"往任务队列增加任务"<<buff_send_data.toHex();
    //      emit SendData1(buff_send_data);
    //    Nthread_CommTask->addNormalTask(PTName,buff_send_data,&resultgogo);
    sendDataToSerial(0,buff_send_data);
    //    qDebug()<<buff_send_data.toHex();
    //    emit SendData(PTName,buff_send_data);
}

/*
* @description 发送串口数据，运行电机走位置电压
* @param {QString} PTName 伺服电机名字
* @param {int} PT_ID 电机ID
* @param {int} Broad_type 主板板号
* @param {int} Motor_Num 电机号
* @param {int} PositionVoltage_UpperLimit 位置电压上限
* @param {int} PositionVoltage_LowerLimit 位置电压下限
* @param {int} PositionCurrent_UpperLimit 电流上限
* @param {int} PositionCurrent_LowerLimit 电流下限
* @param {int} Timeout 超时时间
* @returns {void} 无
* @date 2025-10-25 09:36:00
* @author lh
*/
void thread_ptmotor::SendPtMotorOperation(QString PTName,int PT_ID,int Broad_type,int Motor_Num,int PositionVoltage_UpperLimit,int PositionVoltage_LowerLimit,int PositionCurrent_UpperLimit,int PositionCurrent_LowerLimit,int Timeout)
{

    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0x00)); // 长度占位符
    buff_send_data.append(PT_ID);//ID
    buff_send_data.append(0x11);//功能码
    buff_send_data.append(Broad_type);//板子类型
    buff_send_data.append(Motor_Num);//电机号
    // 位置电压上限 - 双字节，低位在前高位在后
    buff_send_data.append(static_cast<char>(PositionVoltage_UpperLimit & 0xFF));        // 低字节
    buff_send_data.append(static_cast<char>((PositionVoltage_UpperLimit >> 8) & 0xFF)); // 高字节

    // 位置电压下限 - 双字节，低位在前高位在后
    buff_send_data.append(static_cast<char>(PositionVoltage_LowerLimit & 0xFF));        // 低字节
    buff_send_data.append(static_cast<char>((PositionVoltage_LowerLimit >> 8) & 0xFF)); // 高字节

    // 电流上限 - 双字节，低位在前高位在后
    buff_send_data.append(static_cast<char>(PositionCurrent_UpperLimit & 0xFF));        // 低字节
    buff_send_data.append(static_cast<char>((PositionCurrent_UpperLimit >> 8) & 0xFF)); // 高字节

    // 电流下限 - 双字节，低位在前高位在后
    buff_send_data.append(static_cast<char>(PositionCurrent_LowerLimit & 0xFF));        // 低字节
    buff_send_data.append(static_cast<char>((PositionCurrent_LowerLimit >> 8) & 0xFF)); // 高字节
    buff_send_data.append(Timeout);//超时时间
    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符
    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段
    //      emit SendData1(buff_send_data);
    //    Nthread_CommTask->addNormalTask(PTName,buff_send_data,&resultgogo);
    my_Recevie_flag[PT_ID*2+Motor_Num-1] = false;
    sendDataToSerial(0,buff_send_data);
    //        qDebug()<<"往任务列表添加任务";
    //    emit SendData(PTName,buff_send_data);
}


/*
* @description 发送串口数据，运行电机走位置电压
* @param {QString} PTName 伺服电机名字
* @param {int} PT_ID 电机ID
* @param {int} Broad_type 主板板号
* @param {int} Motor_Num 电机号
* @param {int} Direction 运行方向
* @param {int} PositionVoltage_UpperLimit 位置电压上限
* @param {int} PositionVoltage_LowerLimit 位置电压下限
* @param {int} LockedCurrent 堵转电流
* @param {int} PositionCurrent_LowerLimit 电流下限
* @param {int} Timeout 超时时间
* @returns {void} 无
* @date 2025-10-25 09:36:00
* @author lh
*/
//68 0d 00 12 0102 00 2823 8813 6400 0100 f4 0d0a
void thread_ptmotor::SendPtMotorDetectionOpening(QString PTName, int PT_ID, int Broad_type, int Motor_Num, int Direction, int PositionVoltage_UpperLimit, int PositionVoltage_LowerLimit, int LockedCurrent, int PositionCurrent_LowerLimit, int TimeOut)
{
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0x00)); // 长度占位符
    buff_send_data.append(PT_ID);//ID
    buff_send_data.append(0x12);//功能码
    buff_send_data.append(Broad_type);//板子类型
    buff_send_data.append(Motor_Num);//电机号
    buff_send_data.append(static_cast<char>(0x00)); //方向
    // 位置电压上限 - 双字节，低位在前高位在后
    buff_send_data.append(static_cast<char>(PositionVoltage_UpperLimit & 0xFF));        // 低字节
    buff_send_data.append(static_cast<char>((PositionVoltage_UpperLimit >> 8) & 0xFF)); // 高字节
    // 位置电压下限 - 双字节，低位在前高位在后
    buff_send_data.append(static_cast<char>(PositionVoltage_LowerLimit & 0xFF));        // 低字节
    buff_send_data.append(static_cast<char>((PositionVoltage_LowerLimit >> 8) & 0xFF)); // 高字节
    // 电流上限 - 双字节，低位在前高位在后
    buff_send_data.append(static_cast<char>(LockedCurrent & 0xFF));        // 低字节
    buff_send_data.append(static_cast<char>((LockedCurrent >> 8) & 0xFF)); // 高字节
    // 电流下限 - 双字节，低位在前高位在后
    buff_send_data.append(static_cast<char>(PositionCurrent_LowerLimit & 0xFF));        // 低字节
    buff_send_data.append(static_cast<char>((PositionCurrent_LowerLimit >> 8) & 0xFF)); // 高字节

    buff_send_data.append(TimeOut);//超时
    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符

    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    //    qDebug()<<buff_send_data.size()<<lengthPos + 4<<length;
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段
    //      emit SendData1(buff_send_data);
    //    Nthread_CommTask->addNormalTask(PTName,buff_send_data,&resultgogo);
    sendDataToSerial(0,buff_send_data);
    //    qDebug()<<buff_send_data.toHex();
    //    emit SendData(PTName,buff_send_data);
}


/*
* @description 发送串口数据，读取电机当前状态
* @param {QString} PTName 伺服电机名字
* @param {int} PT_ID 电机ID
* @param {int} Broad_type 主板板号
* @param {int} Motor_Num 电机号
* @returns {void} 无
* @date 2025-10-25 09:36:00
* @author lh
*/
void thread_ptmotor::ReadPtMotorStatus(QString PTName, int PT_ID, int Broad_type, int Motor_Num)//读取电机状态
{
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0x00)); // 长度占位符
    buff_send_data.append(PT_ID);//ID
    buff_send_data.append(0x30);//功能码
    buff_send_data.append(Broad_type);//板子类型
    buff_send_data.append(Motor_Num);//电机号
    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符
    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段
    //      emit SendData1(buff_send_data);
    //    Nthread_CommTask->addNormalTask(PTName,buff_send_data,&resultgogo);
    sendDataToSerial(0,buff_send_data);
    //    qDebug()<<buff_send_data.toHex();
    //    emit SendData(PTName,buff_send_data);
}


/*
* @description 发送串口数据，控制电机正反转
* @param {QString} PTName 伺服电机名字
* @param {int} PT_ID 电机ID
* @param {int} Broad_type 主板板号
* @param {int} Motor_Num 电机号
* @param {int} Direction 方向 1正转 2反转
* @param {int} RunTime 运行时间
* @date 2025-10-29 16:03:00
* @author lh
*/
void thread_ptmotor::SendPtMotorRun(QString PTName, int PT_ID, int Broad_type, int Motor_Num,int Direction,int RunTime)
{
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0x00)); // 长度占位符
    buff_send_data.append(PT_ID);//ID
    buff_send_data.append(0x30);//功能码
    buff_send_data.append(Broad_type);//板子类型
    buff_send_data.append(Motor_Num);//电机号
    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符
    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段
    //    Nthread_CommTask->addNormalTask(PTName,buff_send_data,&resultgogo);
    sendDataToSerial(0,buff_send_data);


    //    emit SendData1(buff_send_data);


    //    qDebug()<<buff_send_data.toHex();
    //    emit SendData(PTName,buff_send_data);
}



/*
* @description 发送串口数据，电机固定参数初始化
* @date 2025-10-29 16:03:00
* @author lh
*/
void thread_ptmotor::MotorParameterInit()//
{
    if(!All_Ptmotors_Success)
    {
        for(int i=0;i<m_ptMotorSettings.count();i++)//将使能的电机设置参数都发送到单片机
        {
            if(Received_Success==1)
            {

                //               qDebug()<<"当前电机"+QString::number(i+1)+"开始判断："<<m_ptMotorSettings.at(i).m_motorEnabled<<m_ptMotorSettings.at(i).b_Received;
                if(m_ptMotorSettings.at(i).m_motorEnabled && m_ptMotorSettings.at(i).b_Received)
                {
                    qDebug()<<m_ptMotorSettings.at(i).m_name<<m_ptMotorSettings.at(i).m_id<<m_ptMotorSettings.at(i).m_motorType<<m_ptMotorSettings.at(i).m_motorNumber<<m_ptMotorSettings.at(i).m_startDelayMs<<m_ptMotorSettings.at(i).m_alarmDelayMs<<m_ptMotorSettings.at(i).m_voltageAvgCount<<m_ptMotorSettings.at(i).m_currentAvgCount<<m_ptMotorSettings.at(i).m_motorDirection;
                    //发送电机固定参数
                    SendPtMotorFixedParameter(m_ptMotorSettings.at(i).m_name,m_ptMotorSettings.at(i).m_id,m_ptMotorSettings.at(i).m_motorType,m_ptMotorSettings.at(i).m_motorNumber,m_ptMotorSettings.at(i).m_startDelayMs,m_ptMotorSettings.at(i).m_alarmDelayMs,m_ptMotorSettings.at(i).m_voltageAvgCount,m_ptMotorSettings.at(i).m_currentAvgCount,m_ptMotorSettings.at(i).m_motorDirection);
                    m_ptMotorSettings[i].b_Received = false;
                    Received_Success =0;
                    break;
                }
            }
        }
    }

}



void thread_ptmotor::ReceiveRunMotor(QString PTName)
{
    qDebug()<<"接收运行电机信号"+PTName;
    ProcessStart_flag = true;
    Pt[PTName.toInt()] = 1;
    ProcessSteps = 2;
    ProcessStatus = 0;
    ProcessResult = 0;
    motor_ProcessStep[PTName.toInt()] = 0;
    //    PtMotorOver[PTName.toInt()][0] = 0;
    Motor_state[PTName.toInt()] = 0;
    motor_nowprocess[PTName.toInt()] = 0;


    /*
    m_ptMotorStatus[PTName.toInt()].Current_V = 0;
    m_ptMotorStatus[PTName.toInt()].Current_A = 0;
    m_ptMotorStatus[PTName.toInt()].m_TotalStatus= 0;
    m_ptMotorStatus[PTName.toInt()].m_TotalResult = 0;

    for (int i = 0; i < 8; i++) {
        UpData_ShowValue[PTName.toInt()][i] = true;
        m_ptMotorStatus[PTName.toInt()].show_flag[i] = 0;
        m_ptMotorStatus[PTName.toInt()].POSStatus[i] = 0;
        m_ptMotorStatus[PTName.toInt()].V_UpperLimit[i] = 0;
        m_ptMotorStatus[PTName.toInt()].V_LowerLimit[i] = 0;
        m_ptMotorStatus[PTName.toInt()].POS_V[i] = 0;
        m_ptMotorStatus[PTName.toInt()].POS_A[i] = 0;
        m_ptMotorStatus[PTName.toInt()].m_type[i] = 0;
    }
    */

}

void thread_ptmotor::StartDelayTime(int DelayTimer)
{
    QThread::msleep(DelayTimer);
}

void thread_ptmotor::DetermineCurrentMotor(QString ID, QString ID_Num)
{
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_PT_Data.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

}


void thread_ptmotor::sendDataToSerial(int portIndex, const QByteArray &data)
{
    //    switch (portIndex) {
    //    case 0:
    //        Nthread_CommTask->addNormalTask(data,&resultgogo1);
    //        break;
    //    case 1:
    //        Nthread_CommTask->addNormalTask(data,&resultgogo1);
    //        break;
    //    default:
    //        Nthread_CommTask->addNormalTask(data,&resultgogo1);
    //        break;
    //    }
    qDebug()<<"PT线程：添加任务"<<portIndex<<data.toHex();
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

void thread_ptmotor::InitPtData()
{

    m_ptMotorStatus.clear();
    PTMotorFP_Status_basis motorSetting;
    for(int i=0;i<12;i++)
    {
        m_ptMotorStatus.append(motorSetting);
    }


}

void thread_ptmotor::testRunData()
{
    //    for (PTMotorFP_Status_basis& status : m_ptMotorStatus) {
    //        // 访问结构体成员
    //        qDebug() << "m_TotalStatus:" << status.m_TotalStatus;
    //        qDebug() << "m_TotalResult:" << status.m_TotalResult;

    //        // 遍历数组成员
    //        for (int i = 0; i < 8; ++i) {
    //            qDebug() << "POS Status" << i << ":" << status.POSStatus[i];
    //            qDebug() << "Voltage" << i << ":" << status.POS_V[i];
    //             qDebug() << "A" << i << ":" << status.POS_A[i];

    //             qDebug() << "V_UpperLimit" << i << ":" << status.V_UpperLimit[i];
    //             qDebug() << "V_LowerLimit" << i << ":" << status.V_LowerLimit[i];
    //        }
    //    }

    for (int i = 0; i < m_ptMotorStatus.size(); ++i) {
        PTMotorFP_Status_basis& status = m_ptMotorStatus[i];

        // 访问结构体成员
        qDebug() << "m_TotalStatus:" << status.m_TotalStatus;
        qDebug() << "m_TotalResult:" << status.m_TotalResult;
        // 重置所有 show_flag 为 false
        for (int j = 0; j < 8; ++j) {
            qDebug() << "POS Status:电机" << i <<"POS:"<< j << "状态：" << status.POSStatus[j];
            qDebug() << "Voltage:电机" << i<<"POS:"<< j  <<"电压：" << status.POS_V[j];
            qDebug() << "Current:电机" << i <<"POS:"<< j << "电流：" << status.POS_A[j];
            qDebug() << "V_UpperLimit:电机" << i <<"POS:"<< j << "电压上限：" << status.V_UpperLimit[j];
            qDebug() << "V_LowerLimit:电机" << i<<"POS:"<< j << "电压下限：" << status.V_LowerLimit[j];
        }
    }
}

QList<PTMotorFP_Status_basis> thread_ptmotor::reLinRealTimeData()
{
    return m_ptMotorStatus;
}

/*
* @description 发送串口数据，区分串口分发到对应的处理线程
* @param {int} portIndex 串口号编号
* @param {QByteArray &} date 发送数据
* @returns {void} 无
* @date 2025-10-24 11:22:00
* @author zh
*/
void thread_ptmotor::addFixedToSerial(int portIndex, const QByteArray &data,bool *_en)
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

/*
* @description 发送串口数据，区分串口分发到对应的处理线程
* @param {int} portIndex 串口号编号
* @param {QByteArray &} date 发送数据
* @returns {void} 无
* @date 2025-10-24 11:22:00
* @author zh
*/
void thread_ptmotor::Start_ReadState(int _pt_num){
    if(!init_readFixed[_pt_num]){
        QByteArray buff_send_data;
        buff_send_data.append(0x68);
        int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
        buff_send_data.append(static_cast<char>(0x00)); // 长度占位符
        buff_send_data.append(m_ptMotorSettings.at(_pt_num).m_id);//ID
        buff_send_data.append(0x30);//功能码
        buff_send_data.append(m_ptMotorSettings.at(_pt_num).m_motorType);//板子类型
        buff_send_data.append(m_ptMotorSettings.at(_pt_num).m_motorNumber);//电机号
        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
        int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
        buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段


        addFixedToSerial(0,buff_send_data,&readFixed_en[_pt_num]);

        init_readFixed[_pt_num] = true;
    }

    readFixed_en[_pt_num] = true;

}

/*
* @description 发送串口数据，区分串口分发到对应的处理线程
* @param {int} portIndex 串口号编号
* @param {QByteArray &} date 发送数据
* @returns {void} 无
* @date 2025-10-24 11:22:00
* @author zh
*/
void thread_ptmotor::Stop_ReadState(int _pt_num){
    if(readFixed_en[_pt_num]){

        readFixed_en[_pt_num] = false;
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
int thread_ptmotor::getProcessStatus()
{
    return ProcessStatus;
}

/*
* @description 发送串口数据，区分串口分发到对应的处理线程
* @param {int} portIndex 串口号编号
* @param {QByteArray &} date 发送数据
* @returns {void} 无
* @date 2025-10-24 11:22:00
* @author zh
*/
int thread_ptmotor::getProcessResult()
{
    return ProcessResult;
}

/*
* @description
* @param {int} portIndex 串口号编号
* @param {QByteArray &} date 发送数据
* @returns {void} 无
* @date 2025-10-24 11:22:00
* @author zh
*/
void thread_ptmotor::ResetProcessStatusAndResult()
{
    ProcessStatus = 0;
    ProcessResult = 0;
}


/*
* @description
* @param {int} portIndex 串口号编号
* @param {QByteArray &} date 发送数据
* @returns {void} 无
* @date 2025-10-24 11:22:00
* @author zh
*/
void thread_ptmotor::ResetDisplayData()
{
    for(int i = 0;i < 12; i++){
        m_ptMotorStatus[i].Current_V = 0;
        m_ptMotorStatus[i].Current_A = 0;
        m_ptMotorStatus[i].m_TotalStatus= 0;
        m_ptMotorStatus[i].m_TotalResult = 0;

        for (int j = 0; j < 8; j++) {
            UpData_ShowValue[i][j] = true;
            m_ptMotorStatus[i].show_flag[j] = 0;
            m_ptMotorStatus[i].POSStatus[j] = 0;
            m_ptMotorStatus[i].V_UpperLimit[j] = 0;
            m_ptMotorStatus[i].V_LowerLimit[j] = 0;
            m_ptMotorStatus[i].POS_V[j] = 0;
            m_ptMotorStatus[i].POS_A[j] = 0;
            m_ptMotorStatus[i].m_type[j] = 0;
        }
    }
}
