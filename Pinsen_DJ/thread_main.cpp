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

    Nthread_ptmotor = thread_ptmotor::getInstance();

}

thread_main::~thread_main()
{
    threadPause();//暂停线程
}

// 获取单例实例（线程安全的创建方式）
thread_main* thread_main::getInstance()
{
    // 双重检查锁定（提高效率，避免每次获取实例都加锁）
    if (!Nthread_main) {
        QMutexLocker locker(&m_instanceMutex);  // 加锁确保线程安全
        if (!Nthread_main) {
            Nthread_main = new thread_main();
        }
    }
    return Nthread_main;
}

void thread_main::run_start()
{

    if(Main_Stop){
        FinishResultOk = true;//结果标志
        Main_step = 0;
        Main_Funtion_step = 0;
        Main_Stop = false;
        stopFunctionflag = false;//停止信号后再置为false

        //复位界面显示的东西
        Nthread_ptmotor->ResetDisplayData();
        Nthread_linmotor->resetStatus();
        m_Blower->slot_Blower_ResetVars();
        Nthread_Thermistor->resetStatus();
        setFinishResult(RES_RUN);
    }
    else{
        //已经启动
    }
}

void thread_main::run_stop()
{
    Main_Stop = true;
    Main_step = 0;
    Main_Funtion_step = 0;

    FinishResultOk = true;//结果标志

    //发送停止指令
    stopFunction();

//    setFinishResult(RES_STOP);
}

bool thread_main::read_state(){
    return Main_Stop;
}

void thread_main::stopFunction()
{
    if(!stopFunctionflag){
        //先停止线程和功能
        Nthread_linmotor->ProcessStop();
        Nthread_Thermistor->ProcessStop();
        m_Blower->slot_BlowerStop();
        Nthread_ptmotor->ProcessStop();


        sendProtocol_AllStop();
        stopFunctionflag = true;
    }

    //发送停止指令
}

void thread_main::sendProtocol_AllStop(){
    //再发送停止指令
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    buff_send_data.append(0x02);
    buff_send_data.append(0xFF);

    buff_send_data.append(0x10);//功能码
    buff_send_data.append(0xFF);//板子类型

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符


    Nthread_CommTask[0]->addNormalTask(buff_send_data);
    Nthread_CommTask[1]->addNormalTask(buff_send_data);
}

void thread_main::run()
{
    m_buttonState=true;


    sendProtocol_AllStop();

    while(m_buttonState)
    {


        if(!m_buttonState)
            break;


        //按键盒功能
        KeyBox_judge();


        //计时停止
        if(Light_open)
        {
            //延时
            double testTime;

            testTime = (double)LightDeley_Elaps.nsecsElapsed() / (double)1000000 / (double)1000; //s
            if(testTime > 1.5){//S  大于该描数还未接收为接收失败
                m_ModbusRtu->Wdata.setValue(4, 0);
                Light_open = false;
            }
        }

        //停止运行 保证每个线程都已经停止了
        if(Main_Stop){
            //发送停止信号

            this->msleep(50);
            //NFormLogShow->addLog("主线程","线程停止中");
            continue;
        }

        QMutexLocker locker(&m_mutex); // 自动加锁/解锁


            int res = Main_Funtion(Main_step);
            switch (res) {
                case RES_RUN:

                    break;
                case RES_OK:
                    qDebug()<<"主流程"<<Main_step<<"RES_OK";
                    Main_step++;
                    Main_Funtion_step = 0;
                    emit Sign_ShowUI_Step(Main_step);
                    if(Main_step >= 5)
                    {
                        if(FinishResultOk){
                            emit Sign_ShowUI_Results(1);
                            setFinishResult(RES_OK);

                        }else{
                            emit Sign_ShowUI_Results(2);
                            setFinishResult(RES_NG);
                        }
                        Main_Stop = true;
                    }
                    break;
                case RES_NG:
                    qDebug()<<"主流程"<<Main_step<<"RES_NG";
                    Main_step++;
                    Main_Funtion_step = 0;
                    emit Sign_ShowUI_Step(Main_step);
                    if(Main_step >= 5)
                    {
                        emit Sign_ShowUI_Results(2);
                        setFinishResult(RES_NG);
                        Main_Stop = true;
                    }
                    break;
                case RES_STOP:
                    //NG立马停止


//                    emit Sign_ShowUI_Results(2);
                    if(FinishResultOk){
                        emit Sign_ShowUI_Results(1);
                        setFinishResult(RES_OK);


                    }else{
                        emit Sign_ShowUI_Results(2);
                        setFinishResult(RES_NG);

                    }

                    run_stop();
                    Main_Stop = true;

                    //停止运行
                    break;
                default:

                    break;
             }
        this->msleep(10);
    }
}

int thread_main::Main_Funtion(int _step)
{
    if(Main_Funtion_step == 0){

        //复位状态
        Nthread_ptmotor->ResetProcessStatusAndResult();
        Nthread_linmotor->restProcessResultAndStatus();
        m_Blower->slot_Blower_ResetProcessFlags();
        Nthread_Thermistor->restProcessResultAndStatus();


        //初始化参数
        isResultOk = true;//单步结果标志
        Main_Funtion_step = 1;
    }else if(Main_Funtion_step == 1){

        qDebug()<<"PT电机启动1";
        QList<PTMotorFP_Setting_basis1> ptmotor_setting;


        //============================================================================PT电机

        int pt_en[12] = {false};

        //判断电机顺序
        for(int i = 0;i < 12;i++){
//            qDebug()<<"PT电机启动2:"<<m_stepOrderList[i];
            if(m_stepOrderList[i] == QString::number(_step + 1)){//1-12是PT电机如果是该步骤，则赋值
//                PTmotorSettingsList1[i].en = false;
                ProcessParams_state.PT_motor = true;
                pt_en[i] = true;

//                NFormLogShow->addLog("主流程",QString("第%1步骤开启PT电机的M%2检测").arg(_step,i+1));
//                Nthread_ptmotor->MotorParameterInit();
//                Nthread_ptmotor->ReceiveRunMotor(QString::number(i));//电机启动

            }else{
//                PTmotorSettingsList1[i].en = false;
                pt_en[i] = false;
            }
        }
        //读取参数
        if(ProcessParams_state.PT_motor){//PT电机赋值
            //Nthread_ptmotor->setPTMotorSettings1(PTmotorSettingsList1);
            for(int i = 0;i < 12;i++){
                if(pt_en[i]){


                    NFormLogShow->addLog("主流程",QString("第%1步骤开启PT电机的M%2检测").arg(_step,i+1));
                    Nthread_ptmotor->MotorParameterInit();
                    Nthread_ptmotor->ReceiveRunMotor(QString::number(i));//电机启动
                }
            }

            Nthread_ptmotor->setPTMotorSettings1(PTmotorSettingsList1);
        }
        //=================================================================================

        //======================================================================LIN电机
        qDebug()<<"LIN电机启动1";
        if(m_stepOrderList[12] == QString::number(_step + 1)){//13是LIN电机如果是该步骤，则赋值


            ProcessParams_state.Lin_motor = true;

            qDebug()<<"LIN电机启动2";
            MY_LINMotorFP_Setting_basis lin_fp_basis;
            QList<MY_LINMotorFP_Setting_basis> qlistLIN;
            bool ok;
            for(int i = 0; i < LINMotor_Count; i++)
            {
                qDebug()<<"LIN电机启动3";
                lin_fp_basis.m_motorNAD = LINmotorSettingsList[i].m_motorNAD.toInt(&ok,16);//NAD
                qDebug()<<"m_motorNAD"<<lin_fp_basis.m_motorNAD;
                lin_fp_basis.m_motorSpeed = LINmotorSettingsList[i].m_motorRunSpeed; //速度
                lin_fp_basis.m_motorEnabled = LINmotorSettingsList[i].m_motorEnabled;//电机使能
                if(lin_fp_basis.m_motorEnabled)Nthread_linmotor->MotorRunProcess(i,true);
                lin_fp_basis.m_motorRunTime = LINmotorSettingsList[i].m_motorMaxtimer / 100;//运行时间
                lin_fp_basis.m_motorContrlID = LINmotorSettingsList[i].m_motorControlid.toInt(&ok,16);//控制ID
//                qDebug()<<"m_motorContrlID"<<lin_fp_basis.m_motorContrlID;
                lin_fp_basis.m_motorStatusID = LINmotorSettingsList[i].m_motorStateid.toInt(&ok,16);//状态id
//                qDebug()<<"m_motorStatusID"<<lin_fp_basis.m_motorStatusID;
                lin_fp_basis.m_motorStepError = LINmotorSettingsList[i].m_motorStepErrValue;//步数误差
                lin_fp_basis.m_motorExcitation = false;
                lin_fp_basis.m_motorInitRunDir = LINmotorSettingsList[i].m_motorInitDirection;
                lin_fp_basis.m_motorInitRunEnabled = LINmotorSettingsList[i].m_motorInitEnabled;
                lin_fp_basis.m_motorInitRunSetStep = LINmotorSettingsList[i].m_motorInitValue;
                lin_fp_basis.m_motorLockedrotorChange = true;

                (LINmotorSettingsList[i].m_motorOther > 4) ? (lin_fp_basis.m_motorDirection = false) : (lin_fp_basis.m_motorDirection = true);// 电机方向 (true:正转 false:反转)
                (LINmotorSettingsList[i].m_motorOther % 2) ? (lin_fp_basis.m_motorEmren = false) : (lin_fp_basis.m_motorEmren = true);//紧急运行使能
                if(LINmotorSettingsList[i].m_motorOther < 3 || LINmotorSettingsList[i].m_motorOther == 5 || LINmotorSettingsList[i].m_motorOther == 6)
                {
                    lin_fp_basis.m_motorEmrDir = true;//应急方向
                }
                else lin_fp_basis.m_motorEmrDir = false;//应急方向
                qlistLIN.insert(i,lin_fp_basis);
            }
            NFormLogShow->addLog("主流程",QString("第%1步骤开启LIN电机检测").arg(_step));
            Nthread_linmotor->SetMotorFP_Setting(qlistLIN);
            qlistLIN.clear();
        }
        else{
            ProcessParams_state.Lin_motor = false;
        }
        //======================================================================

        //======================================================================Blower鼓风机
        if(m_stepOrderList[13] == QString::number(_step + 1)){
            NFormLogShow->addLog("主流程",QString("第%1步骤开启鼓风机检测").arg(_step));

            //鼓风机启动
            m_Blower->MBlowerStart();

            ProcessParams_state.Blower = true;
        }else{
            ProcessParams_state.Blower = false;
        }
        //======================================================================

        //======================================================================温敏电阻
        if(m_stepOrderList[14] == QString::number(_step + 1)){
            NFormLogShow->addLog("主流程",QString("第%1步骤开启温敏电阻检测").arg(_step));



            //启动
            Nthread_Thermistor->SetThermistorFP_Setting(ResSettingsList2);

            ProcessParams_state.Thermistor = true;
        }else{
            ProcessParams_state.Thermistor = false;
        }
        //======================================================================

        //======================================================================负离子
        if(m_stepOrderList[15] == QString::number(_step + 1)){
            NFormLogShow->addLog("主流程",QString("第%1步骤开启负离子检测").arg(_step));
//            Nthread_Thermistor->SetAnionFP_Setting()
            ProcessParams_state.Anion = true;
        }else{
            ProcessParams_state.Anion = false;
        }
        //======================================================================

        //======================================================================AQS
        if(m_stepOrderList[16] == QString::number(_step + 1)){
            NFormLogShow->addLog("主流程",QString("第%1步骤开启负AQS检测").arg(_step));
            ProcessParams_state.AQS = true;
        }else{
            ProcessParams_state.AQS = false;
        }
        //======================================================================

        //======================================================================pm25
        if(m_stepOrderList[17] == QString::number(_step + 1)){
            NFormLogShow->addLog("主流程",QString("第%1步骤开启负PM2.5检测").arg(_step));
            ProcessParams_state.PM25 = true;
        }else{
            ProcessParams_state.PM25 = false;
        }
        //======================================================================

        //======================================================================ptc
        if(m_stepOrderList[18] == QString::number(_step + 1)){
            NFormLogShow->addLog("主流程",QString("第%1步骤开启负PTC检测").arg(_step));
            ProcessParams_state.Ptc = true;
        }else{
            ProcessParams_state.Ptc = false;
        }
        //======================================================================

        //======================================================================uvc
//        if(m_stepOrderList[19] == QString::number(_step + 1)){
//            NFormLogShow->addLog("主流程",QString("第%1步骤开启紫外灯检测").arg(_step));
//            ProcessParams_state.Ptc = true;
//        }else{
//            ProcessParams_state.Ptc = false;
//        }
        //======================================================================

        for(int i = 0;i < sizeof(stepResult) / sizeof(stepResult[0]); i++)
        {
            stepResult[i] = false;
        }
        if(!ProcessParams_state.PT_motor &&
                !ProcessParams_state.Lin_motor &&
                !ProcessParams_state.Blower&&
                !ProcessParams_state.Thermistor &&
                !ProcessParams_state.Anion &&
                !ProcessParams_state.AQS &&
                !ProcessParams_state.PM25 &&
                !ProcessParams_state.Ptc &&
                !ProcessParams_state.Uvc){//全部没启动
            Main_Funtion_step = 4;
        }
        else{//有启动的
            Main_Funtion_step = 2;
            Deley_Elaps.restart();
        }
    }else if(Main_Funtion_step == 2){
        //延时
        double testTime;

        testTime = (double)Deley_Elaps.nsecsElapsed() / (double)1000000 / (double)1000; //s
        if(testTime > 0.5){//S  大于该描数还未接收为接收失败
            Main_Funtion_step = 3;
        }

    }else if(Main_Funtion_step == 3){
        int f_finish = 0; //临时存放状态
        int f_res = 0; //临时存放结果
        int stepResult_i = 0;//存储结果下标
        //pt电机读取状态

        if(ProcessParams_state.PT_motor){
            f_finish = Nthread_ptmotor->getProcessStatus();//获取整体状态
            f_res = Nthread_ptmotor->getProcessResult();//获取整体结果
    //        qDebug()<<"【主流程】PT电机检查结果："<<f_finish<<f_res ;
            if((f_finish == 0 && !stepResult[stepResult_i]) || (f_res >= 2 && !stepResult[stepResult_i])){
                //读取结果
                if(f_res == 0){
                    //未运行，直接跳过
                }else if(f_res == 1){
                    NFormLogShow->addLog("主流程",QString("第%1步骤PT电机检查OK").arg(_step));
                    //ok
                }else if(f_res > 1){
                    NFormLogShow->addLog("主流程",QString("第%1步骤PT电机检查NG").arg(_step));
                    //ng
                    FinishResultOk = false;
                    isResultOk = false;//单步结果标志
                }
                stepResult[stepResult_i] = true;
            }
        }else{
            stepResult[stepResult_i] = true;
        }

        stepResult_i++;
        //lin电机读取状态

        f_finish = 0; //临时存放状态
        f_res = 0; //临时存放结果
        if(ProcessParams_state.Lin_motor){
            //NFormLogShow->addLog("主流程",QString("第%1步骤开启LIN电机检测结果：%2").arg(_step).arg(f_res));
            //        qDebug()<<"【主流程】LIN电机检查结果："<<f_res ;
            f_finish = Nthread_linmotor->getProcessStatus();
            f_res = Nthread_linmotor->getProcessResult();//获取整体结果
            if((f_finish == 0 && !stepResult[stepResult_i]) || (f_res > 1 && !stepResult[stepResult_i])){
                //读取结果
                if(f_res == 0){
                    //未运行，直接跳过
                }else if(f_res == 2){
                    NFormLogShow->addLog("主流程",QString("第%1步骤lin电机检查OK").arg(_step));
                    //ok
                }else if(f_res > 2){
                    NFormLogShow->addLog("主流程",QString("第%1步骤lin电机检查NG").arg(_step));
                    //ng
                    isResultOk = false;//单步结果标志
                    FinishResultOk = false;
                }
                stepResult[stepResult_i] = true;
            }
        }else{
            stepResult[stepResult_i] = true;
        }


        stepResult_i++;
        f_finish = 0; //临时存放状态
        f_res = 0; //临时存放结果

        //鼓风机电机读取状态
        if(ProcessParams_state.Blower){
            f_finish = m_Blower->getProcessStatus();//获取整体状态
            f_res = m_Blower->getProcessResult();//获取整体结果
            if(f_finish == 0 && !stepResult[stepResult_i] || (f_res > 1 && !stepResult[stepResult_i])){
                //读取结果
                if(f_res == 0){
                    //未运行，直接跳过
                }else if(f_res == 1){
                    NFormLogShow->addLog("主流程",QString("第%1步骤鼓风机检查OK").arg(_step));
                    //ok
                }else if(f_res > 1){
                    NFormLogShow->addLog("主流程",QString("第%1步骤鼓风机检查NG").arg(_step));


                    if(ngStopFlag){//NG停止运行
                        //发送停止指令
                        m_Blower->slot_BlowerStop();

                    }else{
                        m_Blower->slot_BlowerContinue();
                        //继续运行，不做任何处理
                    }


                    //ng
                    isResultOk = false;//单步结果标志
                    FinishResultOk = false;
                }
                stepResult[stepResult_i] = true;
                m_Blower->slot_Blower_ResetProcessFlags();
            }
        }else{
            stepResult[stepResult_i] = true;
        }

        stepResult_i++;

        f_finish = 0; //临时存放状态
        f_res = 0; //临时存放结果

        if(ProcessParams_state.Thermistor){
            //温敏电阻读取状态
            f_finish = Nthread_Thermistor->getProcessStatus();//获取整体状态
            f_res = Nthread_Thermistor->getProcessResult();//获取整体结果
            if(f_finish == 0 && !stepResult[stepResult_i]){
                //读取结果
                if(f_res == 0){//未运行，直接跳过
                }else if(f_res == 1){//ok
                    NFormLogShow->addLog("主流程",QString("第%1步骤温敏电阻检查OK").arg(_step));
                }else if(f_res > 1){//ng
                    NFormLogShow->addLog("主流程",QString("第%1步骤温敏电阻检查NG").arg(_step));
                    isResultOk = false;//单步结果标志
                    FinishResultOk = false;
                }
                stepResult[stepResult_i] = true;
            }
        }else{
            stepResult[stepResult_i] = true;
        }

        stepResult_i++;

        f_finish = 0; //临时存放状态
        f_res = 0; //临时存放结果

        if(ProcessParams_state.Anion){
            //负离子读取状态
            f_finish = Nthread_Thermistor->getAnionProcessStatus();
            f_res = Nthread_Thermistor->getAnionProcessStatus();
            if(f_finish == 0 && !stepResult[stepResult_i]){
                //读取结果
                if(f_res == 0){//未运行，直接跳过
                }else if(f_res == 1){//ok
                    NFormLogShow->addLog("主流程",QString("第%1步骤负离子检查OK").arg(_step));
                }else if(f_res > 1){//ng
                    NFormLogShow->addLog("主流程",QString("第%1步骤负离子检查NG").arg(_step));
                    isResultOk = false;//单步结果标志
                    FinishResultOk = false;
                }
                stepResult[stepResult_i] = true;
            }
        }else{
            stepResult[stepResult_i] = true;
        }


        stepResult_i++;

        f_finish = 0; //临时存放状态
        f_res = 0; //临时存放结果

        if(ProcessParams_state.AQS){
            //AQS读取状态
            if(f_finish == 0 && !stepResult[stepResult_i]){
                //读取结果
                if(f_res == 0){//未运行，直接跳过
                }else if(f_res == 1){//ok
                    NFormLogShow->addLog("主流程",QString("第%1步骤AQS检查OK").arg(_step));
                }else if(f_res > 1){//ng
                    NFormLogShow->addLog("主流程",QString("第%1步骤AQS检查NG").arg(_step));
                    isResultOk = false;//单步结果标志
                    FinishResultOk = false;
                }
                stepResult[stepResult_i] = true;
            }
        }else{
            stepResult[stepResult_i] = true;
        }

        stepResult_i++;

        f_finish = 0; //临时存放状态
        f_res = 0; //临时存放结果

        if(ProcessParams_state.PM25){
            //PM2.5读取状态
            if(f_finish == 0 && !stepResult[stepResult_i]){
                //读取结果
                if(f_res == 0){//未运行，直接跳过
                }else if(f_res == 1){//ok
                    NFormLogShow->addLog("主流程",QString("第%1步骤PM2.5检查OK").arg(_step));
                }else if(f_res > 1){//ng
                    NFormLogShow->addLog("主流程",QString("第%1步骤PM2.5检查NG").arg(_step));
                    isResultOk = false;//单步结果标志
                    FinishResultOk = false;
                }
                stepResult[stepResult_i] = true;
            }
        }else{
            stepResult[stepResult_i] = true;
        }

        stepResult_i++;

        f_finish = 0; //临时存放状态
        f_res = 0; //临时存放结果
        if(ProcessParams_state.Ptc){
            //Ptc读取状态
            if(f_finish == 0 && !stepResult[stepResult_i]){
                //读取结果
                if(f_res == 0){//未运行，直接跳过
                }else if(f_res == 1){//ok
                    NFormLogShow->addLog("主流程",QString("第%1步骤PTC检查OK").arg(_step));
                }else if(f_res > 1){//ng
                    NFormLogShow->addLog("主流程",QString("第%1步骤PTC检查NG").arg(_step));
                    isResultOk = false;//单步结果标志
                    FinishResultOk = false;
                }
                stepResult[stepResult_i] = true;
            }
        }else{
            stepResult[stepResult_i] = true;
        }

        stepResult_i++;

        f_finish = 0; //临时存放状态
        f_res = 0; //临时存放结果

        if(ProcessParams_state.Uvc){
            //uvc读取状态
            if(f_finish == 0 && !stepResult[stepResult_i]){
                //读取结果
                if(f_res == 0){//未运行，直接跳过
                }else if(f_res == 1){//ok
                    NFormLogShow->addLog("主流程",QString("第%1步骤紫外灯检查OK").arg(_step));
                }else if(f_res > 1){//ng
                    NFormLogShow->addLog("主流程",QString("第%1步骤紫外灯检查NG").arg(_step));
                    isResultOk = false;//单步结果标志
                    FinishResultOk = false;
                }
                stepResult[stepResult_i] = true;
            }
        }else{
            stepResult[stepResult_i] = true;
        }

        //----------------------------------------
        if(!isResultOk){//判断停止还是继续运行
            if(ngStopFlag){//NG停止运行
                //发送停止指令
                return RES_STOP;
                //返回结果
            }
            else{
                //继续运行，不做任何处理
            }
        }

        //全部完成
        for(int i = 0;i <= stepResult_i;i++){


            if(!stepResult[i]){
                return RES_RUN;
            }

        }

            Main_Funtion_step = 4;
            NFormLogShow->addLog("主流程",QString("第%1步骤全部检查完成").arg(_step));

    }else if(Main_Funtion_step == 4){

        if(!isResultOk){//判断停止还是继续运行
            return RES_NG;
        }else{
            return RES_OK;
        }//
    }

    return RES_RUN;
}

void thread_main::KeyBox_judge()
{

    //复位按钮
//    if(m_ModbusRtu->b_modbus_port_en){
        if(m_ModbusRtu_delayTime > 20){//启动延时，避免还未读到结果

            for(int i = 0;i < 5;i++){
                bool currentRawState = (m_ModbusRtu->recDatasDi.value(i) == 1);
//                qDebug()<<"实时Button"<<i<<currentRawState;
                if( currentRawState != m_lastRawState[i]){//与上一次不一致

                    qDebug()<<"实时Button不一致"<<i;
                    if(currentRawState)
                    {
                        KeyBox_timer[i].start();
                        m_buttonPressed[i] = true;
                    }
                    else
                    {
                        KeyBox_timer[i].start();
                        m_buttonPressed[i] = false;
                    }
                    R_Res_timer_funFlag[i] = false;
                }
                else if((currentRawState == m_lastRawState[i]) && !R_Res_timer_funFlag[i])
                {
                    double testTime = (double)KeyBox_timer[i].nsecsElapsed() / (double)1000000 / (double)1000; //s
                    if(testTime > 0.1)
                    {
                        if(currentRawState)
                        {
                            KeyboxFuntion(i,currentRawState);
                           qDebug()<<"Button1"<<i<<currentRawState;

                        }
                        else
                        {
                            KeyboxFuntion(i,currentRawState);

                            qDebug()<<"Button0"<<i<<currentRawState;

                        }
                        R_Res_timer_funFlag[i] = true;
                    }
                }

//                qDebug()<<"实时Button "<<currentRawState<<i;
                m_lastRawState[i] = currentRawState;
            }
        }
        else
        {
            m_ModbusRtu_delayTime++;
        }
//    }


}
void thread_main::KeyboxFuntion(int _num,bool _state){
    switch (_num) {
        case KeyboxNum::START:{
            if(_state){
                if(!KeyBoxStop_flag){
                    emit Sign_Run_Start();
                }
            }
            break;
        }
        case KeyboxNum::RESET:{
            if(_state){
                if(!KeyBoxStop_flag){
                    emit Sign_Run_Reset();
                    setFinishResult(RES_STOP);
                }
            }
            break;
        }

        case KeyboxNum::MANUAL:{

            break;
        }
        case KeyboxNum::OK_JUDGE:{


            break;
        }
        case KeyboxNum::STOP:{
            if(_state){
                emit Sign_ShowUI_Results(0);
                setFinishResult(RES_STOP);
                KeyBoxStop_flag = false;
            }else{
//                qDebug()<<"Button急停";
//                Nthread_main->run_stop();
//                emit Sign_Run_Stop();
                setFinishResult(RES_NG);
//                this->msleep(10);
                emit Sign_ShowUI_Results(4);
                emit Sign_Run_Stop();
                this->msleep(60);
                KeyBoxStop_flag = true;
            }
            break;
        }
        default:{

            break;
        }
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

void thread_main::setFinishResult(uchar _res)
{

    switch (_res) {
    case RES_OK:{


        m_ModbusRtu->Wdata.setValue(2, 1);
        m_ModbusRtu->Wdata.setValue(0, 0);
        m_ModbusRtu->Wdata.setValue(1, 0);
        m_ModbusRtu->Wdata.setValue(3, 0);
        m_ModbusRtu->Wdata.setValue(4, 1);
        LightDeley_Elaps.restart();
        Light_open = true;
        break;
    }
    case RES_NG:{
        m_ModbusRtu->Wdata.setValue(0, 1);
        m_ModbusRtu->Wdata.setValue(1, 0);
        m_ModbusRtu->Wdata.setValue(2, 0);
        m_ModbusRtu->Wdata.setValue(3, 1);
        m_ModbusRtu->Wdata.setValue(4, 0);
        break;}

    case RES_STOP:{
        m_ModbusRtu->Wdata.setValue(0, 0);
        m_ModbusRtu->Wdata.setValue(1, 0);
        m_ModbusRtu->Wdata.setValue(2, 0);
        m_ModbusRtu->Wdata.setValue(3, 0);
        m_ModbusRtu->Wdata.setValue(4, 0);
        break;
    }

    case RES_RUN:{
        m_ModbusRtu->Wdata.setValue(0, 0);
        m_ModbusRtu->Wdata.setValue(1, 1);
        m_ModbusRtu->Wdata.setValue(2, 0);
        m_ModbusRtu->Wdata.setValue(3, 0);
        m_ModbusRtu->Wdata.setValue(4, 0);
        break;
    }
    default:{

        break;
    }


    }
}

