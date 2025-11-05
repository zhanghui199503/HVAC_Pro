#include "MBlower.h"
#include <QCoreApplication>
#include "MBlower.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MBlower* m_Blower = nullptr;

QMutex MBlower::m_instanceMutex; // 关键：类外定义，分配内存


//鼓风机启动
void MBlower::MBlowerStart()
{
    m_Blower->v_PosIndex = 0;
    m_Blower->v_CurStepStatus = EM_POS_STEP::POS_START;
}


MBlower::MBlower(QObject *parent)
{
    qRegisterMetaType<Blower_Setting_basis>("Blower_Setting_basis");
    qRegisterMetaType<Blower_Setting_basis1>("Blower_Setting_basis1");


//    ms_DisplayDatas.v_TimerStep = &v_TimerStep;

    allPosBlower = new MClassBlower();
    pthread = new QThread();
    pTimer = new QTimer();
    pTimer->setSingleShot(true);
    pTimer->moveToThread(pthread);
    connect(pTimer, &QTimer::timeout, this, &MBlower::slot_Timeout);
    connect(pthread, &QThread::started, this, &MBlower::doWork);

    this->moveToThread(pthread);
    pthread->start();
}

MBlower* MBlower::getInstance()
{
    // 双重检查锁定（提高效率，避免每次获取实例都加锁）
    if (!m_Blower) {
        QMutexLocker locker(&m_instanceMutex);  // 加锁确保线程安全
        if (!m_Blower) {
            m_Blower = new MBlower();
        }
    }
    return m_Blower;
}

void MBlower::sendDataToSerial(int portIndex, const QByteArray &data)
{

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
void MBlower::addFixedToSerial(int portIndex, const QByteArray &data,bool *_en)
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
/**
 * @brief MBlower::TimerStop    停止定时器
 */
void MBlower::TimerStop()
{
    if(pTimer->isActive()){
        //定时器停止
        pTimer->stop();
    }
}
/**
 * @brief MBlower::TimerStart   开启定时器
 * @param ms
 */
void MBlower::TimerStart(int ms, char v_timerType)
{
    v_TimerStep = v_timerType;
    B_TimeOut = false;
    pTimer->start(ms);
}
/**
 * @brief MBlower::slot_Timeout 定时器超时
 */
void MBlower::slot_Timeout()
{
    if(v_TimerStep == EM_TIMER::START_DELAY_BLOWER){

        qDebug() << "鼓风机首次启动结束：" << QTime::currentTime();
        v_TimerStep = EM_TIMER::NONE;
        TimerStart(allPosBlower->v_Time.at(v_PosIndex) * 1000);
        v_CurStepStatus = POS_Judge;
    }else{
        B_TimeOut = true;
        qDebug() << "位置ID：" << v_PosIndex  << "定时器停止：" << QTime::currentTime();
    }
}
/**
 * @brief MBlower::slot_BlowerFixedPar  设置鼓风机固定速度
 * @param blowerFixPar
 */
void MBlower::slot_BlowerFixedPar(Blower_Setting_basis fixPars, Blower_Setting_basis1 variablePars)
{
    ////////////////////////////////////////////////    固定参数
    allPosBlower->v_ID_Blower = 1;
    allPosBlower->B_Blower_EN = fixPars.m_BlowerEnabled;
    allPosBlower->v_PowerMaxValue = fixPars.m_BlowerPowervoltageUP;
    allPosBlower->v_PowerMinValue = fixPars.m_BlowerPowervoltageDown;
    allPosBlower->v_HZ = fixPars.m_BlowerRate.toUShort();
    allPosBlower->ID_Control = fixPars.m_LINBlowerControlid;
    allPosBlower->ID_Status = fixPars.m_LINBlowerStateid;
    allPosBlower->ID_Send = fixPars.m_LINBlowerSendid;
    allPosBlower->ID_Read = fixPars.m_LINBlowerReadid;
    allPosBlower->B_SpeedCompare = fixPars.m_LINBlowerSpeed_Compare;
    allPosBlower->v_SpeedError = fixPars.m_LINBlowerErrorValue;
    allPosBlower->v_StartDelay = fixPars.m_BlowerStartDelay.toFloat();

    //振动X轴
    ms_VibrationX.B_EN = fixPars.m_X_vibration_Enable;
    ms_VibrationX.v_error_delay = fixPars.m_vibration_DelayAlarm;
    ms_VibrationX.v_start_delay = fixPars.m_vibration_StartDelay;
    //振动Y轴
    ms_VibrationY.B_EN = fixPars.m_Y_vibration_Enable;
    ms_VibrationY.v_error_delay = fixPars.m_vibration_DelayAlarm;
    ms_VibrationY.v_start_delay = fixPars.m_vibration_StartDelay;
    //振动Z轴
    ms_VibrationZ.B_EN = fixPars.m_Z_vibration_Enable;
    ms_VibrationZ.v_error_delay = fixPars.m_vibration_DelayAlarm;
    ms_VibrationZ.v_start_delay = fixPars.m_vibration_StartDelay;
    //噪音
    ms_Noise.B_EN = fixPars.m_Noises_Enable;
    ms_Noise.v_error_delay = fixPars.m_Noises_DelayAlarm;
    ms_Noise.v_start_delay = fixPars.m_Noises_StartDelay;

    ////////////////////////////////////////    位置参数

//    QStringList posname = fixPars.
    QStringList pos = variablePars.m_POS.split(',');
    QStringList time = variablePars.m_Time.split(',');
    QStringList value = variablePars.m_Value.split(',');
    QStringList max = variablePars.m_BlowerMaxValue.split(',');
    QStringList min = variablePars.m_BlowerMinValue.split(',');

    QStringList max_vX = variablePars.m_X_vibrationrMaxValue.split(',');
    QStringList min_vX = variablePars.m_X_vibrationrMinValue.split(',');
    QStringList max_vY = variablePars.m_Y_vibrationMaxValue.split(',');
    QStringList min_vY = variablePars.m_Y_vibrationMinValue.split(',');
    QStringList max_vZ = variablePars.m_Z_vibrationMaxValue.split(',');
    QStringList min_vZ = variablePars.m_Z_vibrationMinValue.split(',');
    QStringList max_noise = variablePars.m_NoisesMaxValue.split(',');
    QStringList min_noise = variablePars.m_NoisesMinValue.split(',');

    allPosBlower->v_allPosSize = pos.size();//支持位置

    allPosBlower->v_Type = fixPars.m_BlowerMode;

    if(allPosBlower->v_Type == EM_BlowerType::PWM){

        p_vec_BlowerOKStatus = &vec_Blower_PWM;

    }else if(allPosBlower->v_Type == EM_BlowerType::Vlot){

        p_vec_BlowerOKStatus = &vec_Blower_Vlot;

    }else if(allPosBlower->v_Type == EM_BlowerType::LIN){

        p_vec_BlowerOKStatus = &vec_Blower_LIN;
    }

    if(allPosBlower->v_Type == EM_BlowerType::Vlot){

        allPosBlower->v_Vlot.resize(allPosBlower->v_allPosSize);
        for(int i=0; i<pos.size(); ++i){
            allPosBlower->v_Vlot[i] = value.at(i).toFloat();
        }
    }else if(allPosBlower->v_Type == EM_BlowerType::PWM){

        allPosBlower->v_PWM.resize(allPosBlower->v_allPosSize);
        for(int i=0; i<pos.size(); ++i){
            allPosBlower->v_PWM[i] = value.at(i).toUShort();
        }
    }else if(allPosBlower->v_Type == EM_BlowerType::LIN){

        allPosBlower->v_Speed.resize(allPosBlower->v_allPosSize);
        for(int i=0; i<pos.size(); ++i){
            allPosBlower->v_Speed[i] = value.at(i).toUShort();
        }
    }

    allPosBlower->v_PosResult.resize(allPosBlower->v_allPosSize);   //结果
    allPosBlower->v_PosResult.fill(POS_NE); //填充无效值

    allPosBlower->v_PosStep.resize(allPosBlower->v_allPosSize);

    allPosBlower->v_Time.resize(allPosBlower->v_allPosSize);
    allPosBlower->v_MaxValue.resize(allPosBlower->v_allPosSize);
    allPosBlower->v_MinValue.resize(allPosBlower->v_allPosSize);

    ms_VibrationX.v_PosResult.resize(allPosBlower->v_allPosSize);
    ms_VibrationX.v_PosResult.fill(POS_NE);
    ms_VibrationX.v_MaxValue.resize(allPosBlower->v_allPosSize);
    ms_VibrationX.v_MinValue.resize(allPosBlower->v_allPosSize);

    ms_VibrationY.v_PosResult.resize(allPosBlower->v_allPosSize);
    ms_VibrationY.v_PosResult.fill(POS_NE);
    ms_VibrationY.v_MaxValue.resize(allPosBlower->v_allPosSize);
    ms_VibrationY.v_MinValue.resize(allPosBlower->v_allPosSize);

    ms_VibrationZ.v_PosResult.resize(allPosBlower->v_allPosSize);
    ms_VibrationZ.v_PosResult.fill(POS_NE);
    ms_VibrationZ.v_MaxValue.resize(allPosBlower->v_allPosSize);
    ms_VibrationZ.v_MinValue.resize(allPosBlower->v_allPosSize);

    ms_Noise.v_PosResult.resize(allPosBlower->v_allPosSize);
    ms_Noise.v_PosResult.fill(POS_NE);
    ms_Noise.v_MaxValue.resize(allPosBlower->v_allPosSize);
    ms_Noise.v_MinValue.resize(allPosBlower->v_allPosSize);

    for(int i=0; i<allPosBlower->v_allPosSize; ++i){

        allPosBlower->v_PosStep[i] = pos.at(i).toUShort();
        allPosBlower->v_Time[i] = abs(time.at(i).toFloat());
        allPosBlower->v_MaxValue[i] = max.at(i).toFloat();
        allPosBlower->v_MinValue[i] = min.at(i).toFloat();

        ms_VibrationX.v_MaxValue[i] = max_vX.at(i).toFloat();
        ms_VibrationX.v_MinValue[i] = min_vX.at(i).toFloat();
        ms_VibrationY.v_MaxValue[i] = max_vY.at(i).toFloat();
        ms_VibrationY.v_MinValue[i] = min_vY.at(i).toFloat();
        ms_VibrationZ.v_MaxValue[i] = max_vZ.at(i).toFloat();
        ms_VibrationZ.v_MinValue[i] = min_vZ.at(i).toFloat();

        ms_Noise.v_MaxValue[i] = max_noise.at(i).toFloat();
        ms_Noise.v_MinValue[i] = min_noise.at(i).toFloat();
    }

    //根据使能，重置每一项结果
    allResult.bits.Blower_bit0 = static_cast<uint8_t>(!allPosBlower->B_Blower_EN);
    allResult.bits.VibrationX_bit1 = static_cast<uint8_t>(!ms_VibrationX.B_EN);
    allResult.bits.VibrationY_bit2 = static_cast<uint8_t>(!ms_VibrationY.B_EN);
    allResult.bits.VibrationZ_bit3 = static_cast<uint8_t>(!ms_VibrationZ.B_EN);
    allResult.bits.Noise_bit4 = static_cast<uint8_t>(!ms_Noise.B_EN);
    allResult.bits.AcIonr_bit5 = 1;
    allResult.bits.bit6 = 1;
    allResult.bits.bit7 = 1;

    qDebug() << "鼓风机同步位置参数完成";

    //显示数据
    init_DisplayDatas();
    sort_DisplayDatas();
    clear_DisplayDatas();

    slot_initWork();
    Send_FixedPars(allPosBlower->v_StartDelay, allPosBlower->v_currAve, allPosBlower->v_vlotAve, allPosBlower->v_LINBaud, allPosBlower->v_idType);
    Send_FixedPars_Relay(allPosBlower->v_StartDelay_Relay, allPosBlower->v_currAve, allPosBlower->v_vlotAve, allPosBlower->v_LINBaud, allPosBlower->v_idType);

}
/**
 * @brief MBlower::init_DisplayDatas    初始化容器大小
 */
void MBlower::init_DisplayDatas()
{
    ms_DisplayDatas.v_MaxValue_Blower.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_MinValue_Blower.resize(allPosBlower->v_allPosSize);

    ms_DisplayDatas.v_MaxValue_VibrationX.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_MinValue_VibrationX.resize(allPosBlower->v_allPosSize);

    ms_DisplayDatas.v_MaxValue_VibrationY.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_MinValue_VibrationY.resize(allPosBlower->v_allPosSize);

    ms_DisplayDatas.v_MaxValue_VibrationZ.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_MinValue_VibrationZ.resize(allPosBlower->v_allPosSize);

    ms_DisplayDatas.v_MaxValue_Noise.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_MinValue_Noise.resize(allPosBlower->v_allPosSize);

    //结果
    ms_DisplayDatas.v_PosResult_Blower.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_PosCurrs_Blower.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_PosVlots_Blower.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_PosSpeed_Blower.resize(allPosBlower->v_allPosSize);



    ms_DisplayDatas.v_PosResult_VibrationX.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_Datas_VibrationX.resize(allPosBlower->v_allPosSize);

    ms_DisplayDatas.v_PosResult_VibrationY.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_Datas_VibrationY.resize(allPosBlower->v_allPosSize);

    ms_DisplayDatas.v_PosResult_VibrationZ.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_Datas_VibrationZ.resize(allPosBlower->v_allPosSize);

    ms_DisplayDatas.v_PosResult_Noise.resize(allPosBlower->v_allPosSize);
    ms_DisplayDatas.v_Datas_Noise.resize(allPosBlower->v_allPosSize);

}
/**
 * @brief MBlower::clear_DisplayData    清除显示数据
 */
void MBlower::clear_DisplayDatas()
{
    ms_DisplayDatas.v_Cur_PosIndex = 0;
    ms_DisplayDatas.v_Real_Blower = 0;

    ms_DisplayDatas.v_PosCurrs_Blower.fill(0);
    ms_DisplayDatas.v_PosVlots_Blower.fill(0);
    ms_DisplayDatas.v_PosResult_Blower.fill(0);
    ms_DisplayDatas.v_PosSpeed_Blower.fill(0);
    ms_DisplayDatas.v_allPosResult_blower = EM_WorkStatus::Finished;

    //X轴
    ms_DisplayDatas.v_allPosResult_VibrationX = EM_WorkStatus::Finished;
    ms_DisplayDatas.v_Real_VibrationX = 0;
    ms_DisplayDatas.v_PosResult_VibrationX.fill(0);
    ms_DisplayDatas.v_Datas_VibrationX.fill(0);
    //Y轴
    ms_DisplayDatas.v_allPosResult_VibrationY = EM_WorkStatus::Finished;
    ms_DisplayDatas.v_Real_VibrationY = 0;
    ms_DisplayDatas.v_PosResult_VibrationY.fill(0);
    ms_DisplayDatas.v_Datas_VibrationY.fill(0);
    //Z轴
    ms_DisplayDatas.v_allPosResult_VibrationZ = EM_WorkStatus::Finished;
    ms_DisplayDatas.v_Real_VibrationZ = 0;
    ms_DisplayDatas.v_PosResult_VibrationZ.fill(0);
    ms_DisplayDatas.v_Datas_VibrationZ.fill(0);
    //噪音
    ms_DisplayDatas.v_allPosResult_Noise = EM_WorkStatus::Finished;
    ms_DisplayDatas.v_Real_Noise = 0;
    ms_DisplayDatas.v_PosResult_Noise.fill(0);
    ms_DisplayDatas.v_Datas_Noise.fill(0);
}
/**
 * @brief MBlower::sort_DisplayDatas
 */
void MBlower::sort_DisplayDatas()
{
    //鼓风机
    ms_DisplayDatas.v_PosSteps_Blower = allPosBlower->v_PosStep;
    ms_DisplayDatas.v_MaxValue_Blower = allPosBlower->v_MaxValue;
    ms_DisplayDatas.v_MinValue_Blower = allPosBlower->v_MinValue;

    //X轴
    ms_DisplayDatas.v_MaxValue_VibrationX = ms_VibrationX.v_MaxValue;
    ms_DisplayDatas.v_MinValue_VibrationX = ms_VibrationX.v_MinValue;

    //Y轴
    ms_DisplayDatas.v_MaxValue_VibrationY = ms_VibrationY.v_MaxValue;
    ms_DisplayDatas.v_MinValue_VibrationY = ms_VibrationY.v_MinValue;

    //Z轴
    ms_DisplayDatas.v_MaxValue_VibrationZ = ms_VibrationZ.v_MaxValue;
    ms_DisplayDatas.v_MinValue_VibrationZ = ms_VibrationZ.v_MinValue;

    //噪音
    ms_DisplayDatas.v_MaxValue_Noise = ms_Noise.v_MaxValue;
    ms_DisplayDatas.v_MinValue_Noise = ms_Noise.v_MinValue;

}

/**
 * @brief MBlower::initWork
 */
void MBlower::slot_initWork()
{
    v_PosIndex = 0;
    ms_DisplayDatas.v_Cur_PosIndex = v_PosIndex;

    allPosBlower->v_PosStatus.resize(allPosBlower->v_allPosSize);  //初始化位置状态
    allPosBlower->v_PosStatus.fill(EM_POS_STEP::POS_NE);

    allPosBlower->v_PWM.resize(allPosBlower->v_allPosSize);
    allPosBlower->v_PWM.fill(0);
}
/**
 * @brief MBlower::slot_ResetVars   复位之前数据
 */
void MBlower::slot_Blower_ResetVars()
{
    v_allResult = 0;
    clear_DisplayDatas();
    v_PosIndex = 0;
    ms_DisplayDatas.v_Cur_PosIndex = v_PosIndex;
}
/**
 * @brief MBlower::slot_Blower_ResetProcessFlags    复位流程标志
 */
void MBlower::slot_Blower_ResetProcessFlags()
{
    v_allResult = EM_WorkStatus::Finished;
    v_WorkStatus = EM_WorkStatus::Finished;
}

//////////////////////////////////////////                  工作线程主函数
void MBlower::doWork()
{
    B_DoWork = true;
    qDebug() << "Working";
    while (B_DoWork) {

        pthread->msleep(1);
        QCoreApplication::processEvents();

        if(v_PosIndex < allPosBlower->v_allPosSize && v_Set_OR_Read == 1){

            if(v_CurStepStatus == EM_POS_STEP::POS_START){

                v_allResult = 0;
                clear_DisplayDatas();
                v_PosIndex = 0;
                ms_DisplayDatas.v_Cur_PosIndex = v_PosIndex;
                Send_RelayControl(1);
                SendReadStatus();
                SendReadStatus_Current();
                v_CurStepStatus = EM_POS_STEP::POS_CONTINUE;

            }/*else if(v_CurStepStatus == EM_POS_STEP::POS_RELAY_CTR){
                //控制等待继电器完成
                if(v_Relay_On == -1){
                }else if(v_Relay_On == 0){

                }else if(v_Relay_On == 1){
                    v_Relay_On = -1;
                    v_CurStepStatus = EM_POS_STEP::POS_CONTINUE;
                }

            }*/else if(v_CurStepStatus == EM_POS_STEP::POS_CONTINUE){

                SendPosPars();
                Send_SetCurrent();
                qDebug() << "首次延时启动：" << QTime::currentTime() << static_cast<int>(allPosBlower->v_StartDelay * 1000);
                TimerStart(allPosBlower->v_StartDelay * 1000, EM_TIMER::START_DELAY_BLOWER);  //启动延时
                v_WorkStatus = EM_WorkStatus::Running;
                v_CurStepStatus = EM_POS_STEP::POS_WAIT;    //启动延时定时器启动后，进入等待判断定时器
                ms_DisplayDatas.v_PosResult_Blower[v_PosIndex] = POS_RUNNING;

            }else if(v_CurStepStatus == EM_POS_STEP::POS_NEXT_POS){

                if(v_PosIndex < allPosBlower->v_allPosSize - 1){

                    if(Judge_POS_EN()){
                        ms_DisplayDatas.v_Cur_PosIndex = v_PosIndex;
                        B_TimeOut = false;
                        curPosBlower.v_BlowerStatus_fun30 = -1;
                        SendPosPars();
                        Send_SetCurrent();
                        TimerStart(allPosBlower->v_StartDelay * 1000, EM_TIMER::START_DELAY_BLOWER);  //启动延时
                        v_CurStepStatus = EM_POS_STEP::POS_WAIT;
                        ms_DisplayDatas.v_PosResult_Blower[v_PosIndex] = POS_RUNNING;
                    }

                }else{
                    //所有位置以执行完毕
                    qDebug() << "鼓风机所有档位执行完毕,停止鼓风机";
                    slot_BlowerStop();
                    Fixed_en = false;
                    WorkFinished();
                    v_WorkStatus = EM_WorkStatus::Finished;
                }

            }else if(v_CurStepStatus == EM_POS_STEP::POS_Judge){

                JudgePos();

            }else if(v_CurStepStatus == EM_POS_STEP::POS_WAIT){
                //等待
            }else if(v_CurStepStatus == EM_POS_STEP::POS_STOP_BLOWER){

            }
        }/*else if(v_PosIndex == allPosBlower->v_allPosSize){

            v_WorkStatus = EM_WorkStatus::Finished;

        }*/
    }
    qDebug() << "Worked";
}
/**
 * @brief MBlower::Judge_POS_EN 判断POS使能
 */
bool MBlower::Judge_POS_EN()
{
    if(v_PosIndex >= allPosBlower->v_allPosSize - 1){
        return false;
    }else{
        v_PosIndex++;    //下一个POS位置Index
    }
    if(allPosBlower->v_PosStep.at(v_PosIndex) <= 0){
        return Judge_POS_EN();
    }else{
        return true;
    }
}
/**
 * @brief MBlower::JudgePos 判断鼓风机POS
 */
void MBlower::JudgePos()
{
    if(allPosBlower->B_Blower_EN){
        //鼓风机
        ms_DisplayDatas.v_PosVlots_Blower[v_PosIndex] = curPosBlower.v_Vlot;
        ms_DisplayDatas.v_PosCurrs_Blower[v_PosIndex] = curPosBlower.v_Curr;
        ms_DisplayDatas.v_PosSpeed_Blower[v_PosIndex] = curPosBlower.v_Speed;

        if(ms_DisplayDatas.v_allPosResult_blower == EM_WorkStatus::Finished){
            ms_DisplayDatas.v_allPosResult_blower = EM_WorkStatus::Running;
        }

        if(p_vec_BlowerOKStatus && p_vec_BlowerOKStatus->contains(curPosBlower.v_BlowerStatus_fun30)){
            //当前位置在目标范围内

        }else if(p_vec_BlowerOKStatus){

            allPosBlower->v_PosStatus[v_PosIndex] = POS_NG;
            ms_DisplayDatas.v_PosResult_Blower[v_PosIndex] = POS_NG;
            ms_DisplayDatas.v_allPosResult_blower = POS_NG;
            //当前位置不在目标范围内
        }
    }
    //X轴
    if(ms_VibrationX.B_EN){
        ms_DisplayDatas.v_Datas_VibrationX[v_PosIndex] = m_ModbusRtu->recDatasAD.at(AD_VibrationX) * 1.0 / 4000.0;
        if(ms_DisplayDatas.v_allPosResult_VibrationX == EM_WorkStatus::Finished){
            ms_DisplayDatas.v_allPosResult_VibrationX = EM_WorkStatus::Running;
        }

        if( ms_DisplayDatas.v_Datas_VibrationX[v_PosIndex] >= ms_VibrationX.v_MinValue.at(v_PosIndex)
                && ms_DisplayDatas.v_Datas_VibrationX[v_PosIndex] <= ms_VibrationX.v_MaxValue.at(v_PosIndex) ){

        }else{
            ms_VibrationX.v_PosResult[v_PosIndex] = POS_NG;
            ms_DisplayDatas.v_PosResult_VibrationX[v_PosIndex] = POS_NG;
            ms_DisplayDatas.v_allPosResult_VibrationX = POS_NG;
        }
    }
    //Y轴
    if(ms_VibrationY.B_EN){
        ms_DisplayDatas.v_Datas_VibrationY[v_PosIndex] = m_ModbusRtu->recDatasAD.at(AD_VibrationY) * 1.0 / 4000.0;
        if(ms_DisplayDatas.v_allPosResult_VibrationY == EM_WorkStatus::Finished){
            ms_DisplayDatas.v_allPosResult_VibrationY = EM_WorkStatus::Running;
        }
        if( ms_DisplayDatas.v_Datas_VibrationY[v_PosIndex] >= ms_VibrationY.v_MinValue.at(v_PosIndex)
                && ms_DisplayDatas.v_Datas_VibrationY[v_PosIndex] <= ms_VibrationY.v_MaxValue.at(v_PosIndex) ){

        }else{
            ms_VibrationY.v_PosResult[v_PosIndex] = POS_NG;
            ms_DisplayDatas.v_PosResult_VibrationY[v_PosIndex] = POS_NG;
            ms_DisplayDatas.v_allPosResult_VibrationY = POS_NG;
        }
    }
    //Z轴
    if(ms_VibrationZ.B_EN){

        ms_DisplayDatas.v_Datas_VibrationZ[v_PosIndex] = m_ModbusRtu->recDatasAD.at(AD_VibrationZ) * 1.0 / 4000.0;

        if(ms_DisplayDatas.v_allPosResult_VibrationZ == EM_WorkStatus::Finished){
            ms_DisplayDatas.v_allPosResult_VibrationZ = EM_WorkStatus::Running;
        }
        if( ms_DisplayDatas.v_Datas_VibrationZ[v_PosIndex] >= ms_VibrationZ.v_MinValue.at(v_PosIndex)
                && ms_DisplayDatas.v_Datas_VibrationZ[v_PosIndex] <= ms_VibrationZ.v_MaxValue.at(v_PosIndex) ){

        }else{
            ms_VibrationZ.v_PosResult[v_PosIndex] = POS_NG;
            ms_DisplayDatas.v_PosResult_VibrationZ[v_PosIndex] = POS_NG;
            ms_DisplayDatas.v_allPosResult_VibrationZ = POS_NG;
        }
    }
    //噪音
    if(ms_Noise.B_EN){
        if(ms_DisplayDatas.v_Datas_Noise[v_PosIndex] <= m_ModbusRtu->recDatasAD.at(AD_Noise) * 1.0 / 10.0){
            ms_DisplayDatas.v_Datas_Noise[v_PosIndex] = m_ModbusRtu->recDatasAD.at(AD_Noise) * 1.0 / 10.0;
        }
        if(ms_DisplayDatas.v_allPosResult_Noise == EM_WorkStatus::Finished){
            ms_DisplayDatas.v_allPosResult_Noise = EM_WorkStatus::Running;
        }
        //噪音
        if( ms_DisplayDatas.v_Datas_Noise[v_PosIndex] >= ms_Noise.v_MinValue.at(v_PosIndex)
                && ms_DisplayDatas.v_Datas_Noise[v_PosIndex] <= ms_Noise.v_MaxValue.at(v_PosIndex) ){

        }else{
            ms_Noise.v_PosResult[v_PosIndex] = POS_NG;
            ms_DisplayDatas.v_PosResult_Noise[v_PosIndex] = POS_NG;
            ms_DisplayDatas.v_allPosResult_Noise = POS_NG;
        }
    }

    if(B_TimeOut){
        bool b_signalStep_result = true;

        if(ms_VibrationX.B_EN){
            //振动X轴
            if( ms_DisplayDatas.v_Datas_VibrationX[v_PosIndex] != POS_NG){
                ms_VibrationX.v_PosResult[v_PosIndex] = POS_OK;
                ms_DisplayDatas.v_PosResult_VibrationX[v_PosIndex] = POS_OK;

            }else{
                b_signalStep_result = false;
            }
        }

        if(ms_VibrationY.B_EN){
            //振动Y轴
            if( ms_DisplayDatas.v_Datas_VibrationY[v_PosIndex] != POS_NG){
                ms_VibrationY.v_PosResult[v_PosIndex] = POS_OK;
                ms_DisplayDatas.v_PosResult_VibrationY[v_PosIndex] = POS_OK;

            }else{
                b_signalStep_result = false;
            }
        }

        if(ms_VibrationZ.B_EN){
            //振动Z轴
            if( ms_DisplayDatas.v_Datas_VibrationZ[v_PosIndex] != POS_NG){
                ms_VibrationZ.v_PosResult[v_PosIndex] = POS_OK;
                ms_DisplayDatas.v_PosResult_VibrationZ[v_PosIndex] = POS_OK;

            }else{
                b_signalStep_result = false;
            }
        }
        if(ms_Noise.B_EN){
            //噪音
            if( ms_DisplayDatas.v_PosResult_Noise[v_PosIndex] == POS_NG){
                b_signalStep_result = false;

            }else{
                ms_Noise.v_PosResult[v_PosIndex] = POS_OK;
                ms_DisplayDatas.v_PosResult_Noise[v_PosIndex] = POS_OK;
            }

        }

        if(allPosBlower->B_Blower_EN){
            if(allPosBlower->v_PosStatus[v_PosIndex] != POS_NG){

                ms_DisplayDatas.v_PosResult_Blower[v_PosIndex] = POS_OK;
                allPosBlower->v_PosResult[v_PosIndex] = POS_OK;

            }else if(allPosBlower->v_PosStatus[v_PosIndex] == POS_NG){
                b_signalStep_result = false;
            }

//            qDebug() << "鼓风机结果:" << allPosBlower->v_PosStatus[v_PosIndex] << "数据："
//                     << "\n电流：" << ms_DisplayDatas.v_PosCurrs_Blower[v_PosIndex]
//                     << "\n电压：" << ms_DisplayDatas.v_PosVlots_Blower[v_PosIndex]
//                     << "\n转速：" << ms_DisplayDatas.v_PosSpeed_Blower[v_PosIndex];
        }


        //判断单步总结果
        if(b_signalStep_result){
            v_CurStepStatus = EM_POS_STEP::POS_NEXT_POS;
            qDebug() << "单步OK" << v_PosIndex;
        }else{
            qDebug() << "需要等待外部确认";
            //NG之后，等待信号是否
            v_CurStepResult = EM_POS_STEP::POS_NG;
            v_lastStepStatus = v_CurStepResult;
            v_CurStepStatus = EM_POS_STEP::POS_WAIT;    //等待
            v_allResult = 2;
        }

    }
}
/**
 * @brief MBlower::slot_SendFixedPars   接收设置鼓风机固定参数信号
 */
void MBlower::slot_SendFixedPars()
{
    Send_FixedPars(allPosBlower->v_StartDelay_Relay, allPosBlower->v_currAve, allPosBlower->v_vlotAve, allPosBlower->v_LINBaud, allPosBlower->v_idType);
}
/**
 * @brief MBlower::slot_getWorkFinishedFlag 返回流程工作状态
 * @param finishedFlag
 */
uchar MBlower::getProcessStatus()
{

    return v_WorkStatus;
}
/**
 * @brief MBlower::getProcessResult 获取总结果
 * @return
 */
uint8_t MBlower::getProcessResult()
{
    return v_allResult;
}

/**
 * @brief MBlower::reLinRealTimeData    界面显示数据
 * @return
 */
MS_DisplayDatas MBlower::reLinRealTimeData()
{
    return ms_DisplayDatas;
}
/**
 * @brief MBlower::SendStopWorkAndWR    停止（关闭鼓风机并停止相对应的设备写和读）   每个产品发送一次
 */
void MBlower::SendStopWorkAndWR(char blower=1, char uvlamp=1, char avIonr=1, char blowerVer=1)
{
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0)); // 长度占位符

    buff_send_data.append(allPosBlower->v_ID_Blower);//ID
    buff_send_data.append(0x10);//功能码
    buff_send_data.append(allPosBlower->v_BoradType_Blower);//板子类型
    buff_send_data.append(blower);//鼓风机
    buff_send_data.append(uvlamp);//紫外灯
    buff_send_data.append(avIonr);//负离子
    buff_send_data.append(blowerVer);//鼓风机版本读取

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符

    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

//    Nthread_CommTask->addNormalTask(buff_send_data, &resultgogo);
    sendDataToSerial(1, buff_send_data);
}
/**
 * @brief MBlower::slot_BlowerContinue  继续鼓风机
 */
void MBlower::slot_BlowerContinue()
{
    if(v_lastStepStatus == EM_POS_STEP::POS_NG){
        v_CurStepStatus = EM_POS_STEP::POS_NEXT_POS;
        qDebug() << "NG继续测试";
    }else{
        v_CurStepStatus = EM_POS_STEP::POS_CONTINUE;
    }
    //重新设置鼓风机当前档位参数，并且继续测试
    qDebug() << "重新设置鼓风机当前档位参数，并且继续鼓风机测试";
}
/**
 * @brief MBlower::slot_BlowerStop   停止鼓风机
 */
void MBlower::slot_BlowerStop()
{

    TimerStop();
    v_CurStepStatus = EM_POS_STEP::POS_STOP_BLOWER;

    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0)); // 长度占位符

    buff_send_data.append(allPosBlower->v_ID_Blower);//ID
    buff_send_data.append(0x11);//功能码

    buff_send_data.append(allPosBlower->v_BoradType_Blower);//板子类型
    buff_send_data.append(allPosBlower->v_linType);//鼓风机LIN类型
    buff_send_data.append(allPosBlower->v_Type);//鼓风机类型

    if(allPosBlower->v_Type == EM_BlowerType::PWM){

        uchar lo = static_cast<uchar>(allPosBlower->v_HZ & 0xFF);
        uchar hi = static_cast<uchar>((allPosBlower->v_HZ >> 8) & 0xFF);
        buff_send_data.append(lo);
        buff_send_data.append(hi);
        buff_send_data.append(allPosBlower->v_PWM.at(v_PosIndex)); //占空比

    }else if(allPosBlower->v_Type == EM_BlowerType::Vlot){

        uchar lo = static_cast<uchar>(allPosBlower->v_HZ & 0xFF);
        uchar hi = static_cast<uchar>((allPosBlower->v_HZ >> 8) & 0xFF);
        buff_send_data.append(lo);
        buff_send_data.append(hi);
        buff_send_data.append(static_cast<uchar>(0));

    }else{

        buff_send_data.append(static_cast<uchar>(allPosBlower->ID_Control.toInt(nullptr, 16)));
        buff_send_data.append(static_cast<uchar>(allPosBlower->ID_Status.toInt(nullptr, 16)));

        short v_data = 0;
        uchar lo = static_cast<uchar>(v_data & 0xFF);
        uchar hi = static_cast<uchar>((v_data >> 8) & 0xFF);
        buff_send_data.append(lo);
        buff_send_data.append(hi);

        v_data = static_cast<short>(allPosBlower->v_Speed[v_PosIndex] + allPosBlower->v_SpeedError);
        lo = static_cast<uchar>(v_data & 0xFF);
        hi = static_cast<uchar>((v_data >> 8) & 0xFF);
        buff_send_data.append(lo);
        buff_send_data.append(hi);

        v_data = static_cast<short>(allPosBlower->v_Speed[v_PosIndex] - allPosBlower->v_SpeedError);
        lo = static_cast<uchar>(v_data & 0xFF);
        hi = static_cast<uchar>((v_data >> 8) & 0xFF);
        buff_send_data.append(lo);
        buff_send_data.append(hi);
    }


    short v_data = static_cast<short>(allPosBlower->v_MaxValue[v_PosIndex] * 1000);
    uchar lo = static_cast<uchar>(v_data & 0xFF);
    uchar hi = static_cast<uchar>((v_data >> 8) & 0xFF);
    buff_send_data.append(lo);
    buff_send_data.append(hi);

    v_data = static_cast<short>(allPosBlower->v_MinValue[v_PosIndex] * 1000);
    lo = static_cast<uchar>(v_data & 0xFF);
    hi = static_cast<uchar>((v_data >> 8) & 0xFF);
    buff_send_data.append(lo);
    buff_send_data.append(hi);

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符

    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

//    Nthread_CommTask->addNormalTask(buff_send_data, &resultgogo);
    sendDataToSerial(1, buff_send_data);
    SendStopWorkAndWR(0,0,0,0);    //发送一次单片机读写停止
}
/**
 * @brief MBlower::SendPosPars  发送位置
 * @param blower
 */
void MBlower::SendPosPars()
{
    v_lastStepStatus = EM_POS_STEP::POS_NE;

    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0)); // 长度占位符

    buff_send_data.append(allPosBlower->v_ID_Blower);//ID
    buff_send_data.append(0x11);//功能码

    buff_send_data.append(allPosBlower->v_BoradType_Blower);//板子类型
    buff_send_data.append(allPosBlower->v_linType);//鼓风机LIN类型
    buff_send_data.append(allPosBlower->v_Type);//鼓风机类型

    if(allPosBlower->v_Type == EM_BlowerType::PWM){

        uchar lo = static_cast<uchar>(allPosBlower->v_HZ & 0xFF);
        uchar hi = static_cast<uchar>((allPosBlower->v_HZ >> 8) & 0xFF);
        buff_send_data.append(lo);
        buff_send_data.append(hi);
        buff_send_data.append(allPosBlower->v_PWM.at(v_PosIndex)); //占空比

    }else if(allPosBlower->v_Type == EM_BlowerType::Vlot){

        uchar lo = static_cast<uchar>(allPosBlower->v_HZ & 0xFF);
        uchar hi = static_cast<uchar>((allPosBlower->v_HZ >> 8) & 0xFF);
        buff_send_data.append(lo);
        buff_send_data.append(hi);
        buff_send_data.append(static_cast<uchar>(0));

    }else{

        buff_send_data.append(static_cast<uchar>(allPosBlower->ID_Control.toInt(nullptr, 16)));
        buff_send_data.append(static_cast<uchar>(allPosBlower->ID_Status.toInt(nullptr, 16)));

        short v_data = allPosBlower->v_Speed[v_PosIndex];
        uchar lo = static_cast<uchar>(v_data & 0xFF);
        uchar hi = static_cast<uchar>((v_data >> 8) & 0xFF);
        buff_send_data.append(lo);
        buff_send_data.append(hi);

        v_data = static_cast<short>(allPosBlower->v_Speed[v_PosIndex] + allPosBlower->v_SpeedError);
        lo = static_cast<uchar>(v_data & 0xFF);
        hi = static_cast<uchar>((v_data >> 8) & 0xFF);
        buff_send_data.append(lo);
        buff_send_data.append(hi);

        v_data = static_cast<short>(allPosBlower->v_Speed[v_PosIndex] - allPosBlower->v_SpeedError);
        lo = static_cast<uchar>(v_data & 0xFF);
        hi = static_cast<uchar>((v_data >> 8) & 0xFF);
        buff_send_data.append(lo);
        buff_send_data.append(hi);
    }


    short v_data = static_cast<short>(allPosBlower->v_MaxValue[v_PosIndex] * 1000);
    uchar lo = static_cast<uchar>(v_data & 0xFF);
    uchar hi = static_cast<uchar>((v_data >> 8) & 0xFF);
    buff_send_data.append(lo);
    buff_send_data.append(hi);

    v_data = static_cast<short>(allPosBlower->v_MinValue[v_PosIndex] * 1000);
    lo = static_cast<uchar>(v_data & 0xFF);
    hi = static_cast<uchar>((v_data >> 8) & 0xFF);
    buff_send_data.append(lo);
    buff_send_data.append(hi);

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符

    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

    qDebug() << "***********************    设置位置信息  ****************************" << buff_send_data.toHex();
//    Nthread_CommTask->addNormalTask(buff_send_data, &resultgogo);
    sendDataToSerial(1, buff_send_data);
}
/**
 * @brief MBlower::Finished 整体工作完成
 */
void MBlower::WorkFinished()
{
    Send_RelayControl(0);   //工作停止后，控制继电器关

    if(ms_VibrationX.B_EN){
        if(ms_VibrationX.v_PosResult.contains(POS_NG)){
            allResult.bits.VibrationX_bit1 = 0;
        }else{

            allResult.bits.VibrationX_bit1 = 1;
            ms_DisplayDatas.v_allPosResult_VibrationX = POS_OK;
        }
    }

    if(ms_VibrationY.B_EN){
        if(ms_VibrationY.v_PosResult.contains(POS_NG)){
            allResult.bits.VibrationY_bit2 = 0;
        }else{
            allResult.bits.VibrationY_bit2 = 1;
            ms_DisplayDatas.v_allPosResult_VibrationY = POS_OK;
        }
    }

    if(ms_VibrationZ.B_EN){
        if(ms_VibrationZ.v_PosResult.contains(POS_NG)){
            allResult.bits.VibrationZ_bit3 = 0;
        }else{
            allResult.bits.VibrationZ_bit3 = 1;
            ms_DisplayDatas.v_allPosResult_VibrationZ = POS_OK;
        }
    }


    if(ms_Noise.B_EN){
        if(ms_Noise.v_PosResult.contains(POS_NG)){
            allResult.bits.Noise_bit4 = 0;
        }else{
            allResult.bits.Noise_bit4 = 1;
            ms_DisplayDatas.v_allPosResult_Noise = POS_OK;
        }
    }

    if(allPosBlower->B_Blower_EN){
        if(allPosBlower->v_PosResult.contains(POS_NG)){
            allResult.bits.Blower_bit0 = 0;
        }else{
            allResult.bits.Blower_bit0 = 1;
            ms_DisplayDatas.v_allPosResult_blower = POS_OK;
        }
    }

    if(allResult.v_result == 0xFF){
        qDebug() << "整体测试结果OK" << static_cast<uint8_t>(allResult.v_result);
        v_allResult = 1;

    }else{
        qDebug() << "整体测试结果NG" << static_cast<uint8_t>(allResult.v_result);
        v_allResult = 2;
    }
}
/**
 * @brief MBlower::SendFixedPars    设置鼓风机固定参数
 */
void MBlower::Send_FixedPars(short start_delay, char curr_aveCount, char vlot_aveCount, char buad_type, char id_type)
{
    v_Set_OR_Read = 0;  //当前执行写入参数操作

    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0)); // 长度占位符

    buff_send_data.append(allPosBlower->v_ID_Blower);//ID
    buff_send_data.append(0x20);//功能码
    buff_send_data.append(allPosBlower->v_BoradType_Blower);//板子类型
    buff_send_data.append(static_cast<uint8_t>(0));
    buff_send_data.append(static_cast<char>(allPosBlower->v_AlarmDelay * 100));

    int32_t delayt = static_cast<uint32_t>(start_delay * 10);
    short v_data = static_cast<short>(delayt);
    uchar lo = static_cast<uchar>(v_data & 0xFF);
    uchar hi = static_cast<uchar>((v_data >> 8) & 0xFF);
    buff_send_data.append(lo);
    buff_send_data.append(hi);

    buff_send_data.append(curr_aveCount);//电压平均次数
    buff_send_data.append(vlot_aveCount);//电流平均次数

    buff_send_data.append(buad_type);//LIN波特率
    buff_send_data.append(id_type);//帧类型

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符

    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

//    Nthread_CommTask->addNormalTask(buff_send_data, &resultgogo);
    sendDataToSerial(1, buff_send_data);

    qDebug() << "鼓风机版启动延时：" << buff_send_data.toHex();

    qDebug() << "设置鼓风机固定参数";
    v_Set_OR_Read = 1;  //当前执行写入参数操作
}
/**
 * @brief MBlower::Send_FixedPars_Relay 设置鼓风机硬件电流的固定参数
 * @param start_delay
 * @param curr_aveCount
 * @param vlot_aveCount
 * @param buad_type
 * @param id_type
 */
void MBlower::Send_FixedPars_Relay(short start_delay, char curr_aveCount, char vlot_aveCount, char buad_type, char id_type)
{
    v_Set_OR_Read = 0;  //当前执行写入参数操作

    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0)); // 长度占位符

    buff_send_data.append(allPosBlower->v_ID_Relay);//ID
    buff_send_data.append(0x20);//功能码
    buff_send_data.append(allPosBlower->v_BoardType_Relay);//板子类型
    buff_send_data.append(static_cast<uint8_t>(0));
    buff_send_data.append(static_cast<uint8_t>(allPosBlower->v_AlarmDelay_Relay * 100));

    int32_t delayt = static_cast<uint32_t>(start_delay * 10);
    short v_data = static_cast<short>(delayt);
    uchar lo = static_cast<uchar>(v_data & 0xFF);
    uchar hi = static_cast<uchar>((v_data >> 8) & 0xFF);
    buff_send_data.append(lo);
    buff_send_data.append(hi);

    buff_send_data.append(curr_aveCount);//电压平均次数
    buff_send_data.append(vlot_aveCount);//电流平均次数

    buff_send_data.append(buad_type);//LIN波特率
    buff_send_data.append(id_type);//帧类型

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符

    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

//    Nthread_CommTask->addNormalTask(buff_send_data, &resultgogo);
    sendDataToSerial(1, buff_send_data);

    qDebug() << "设置鼓风机固定参数";
    v_Set_OR_Read = 1;  //当前执行写入参数操作
}
/**
 * @brief MBlower::SendReadStatus   读鼓风机状态
 */
void MBlower::SendReadStatus()
{
    if(!init_Fixed_en){
        init_Fixed_en = true;
        QByteArray buff_send_data;
        buff_send_data.append(0x68);
        int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
        buff_send_data.append(static_cast<char>(0)); // 长度占位符

        buff_send_data.append(allPosBlower->v_ID_Blower);//ID
        buff_send_data.append(0x30);//功能码

        buff_send_data.append(allPosBlower->v_BoradType_Blower);//板子类型
        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符

        int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
        buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

    //    Nthread_CommTask->addFixedTask(buff_send_data, &resultgogo);
        addFixedToSerial(1, buff_send_data, &Fixed_en);
    }
    Fixed_en = true;
}
/**
 * @brief MBlower::SendReadStatus_Current   读取硬件电流状态
 */
void MBlower::SendReadStatus_Current()
{
    if(!init_Fixed_en_current){
        init_Fixed_en_current = true;
        QByteArray buff_send_data;
        buff_send_data.append(0x68);
        int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
        buff_send_data.append(static_cast<char>(0)); // 长度占位符

        buff_send_data.append(allPosBlower->v_ID_Relay);//ID
        buff_send_data.append(0x30);//功能码

        buff_send_data.append(allPosBlower->v_BoardType_Relay);//板子类型
        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符

        int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
        buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

    //    Nthread_CommTask->addFixedTask(buff_send_data, &resultgogo);
        addFixedToSerial(1, buff_send_data, &Fixed_en_current);
    }
    Fixed_en_current = true;
}

/**
 * @brief MBlower::slot_RecivceDatas    接收数据解析
 * @param recivceDatas
 */
void MBlower::slot_RecivceDatas(QByteArray recivceDatas)
{
    int8_t id = recivceDatas.at(2);
    int8_t board_type = recivceDatas.at(4);

//    if(id != allPosBlower->v_ID_Blower && board_type != allPosBlower->v_BoradType_Blower){
//        return;
//    }
    int8_t funtion_code = recivceDatas.at(3); //功能码
    if(0x10 == funtion_code){
        if(id != allPosBlower->v_ID_Blower && board_type != allPosBlower->v_BoradType_Blower){
            // 停止（关闭鼓风机并停止相对应的设备写和读）
            if(0x0B == recivceDatas.at(5)){
                qDebug() << "停止（关闭鼓风机并停止相对应的设备写和读）" << "执行成功";

            }else{
                qDebug() << "鼓风机功能码0x10报错：" << static_cast<uchar>(recivceDatas.at(5));
            }
        }

    }else if(0x15 == funtion_code){
        //读取负离子返回
//        ms_acIonr.v_status = recivceDatas.at(5);
//        ms_acIonr.v_recData0 = recivceDatas.at(6);
//        ms_acIonr.v_recData1 = recivceDatas.at(7);

//        dealIonrDatas(0x15, recivceDatas);

    }else if(0x16 == funtion_code){
        //控制继电器返回
        qDebug() << "控制继电器返回";
        if(0x08 == recivceDatas.at(5)){
            v_Relay_On = 1;
        }else{
            v_Relay_On = -1;
        }
    }else if(0x20 == funtion_code){
        if(id != allPosBlower->v_ID_Blower && board_type != allPosBlower->v_BoradType_Blower){
            //鼓风机(切品番发送一次或保存发送一次)
            v_Set_OR_Read = 1;
            qDebug() << "设置成功 0x20";
            if(0x0C == recivceDatas.at(5)){

            }else{
                qDebug() << "鼓风机功能码0x20报错：" << (int)recivceDatas.at(5);
            }
        }
    }else if(0x30 == funtion_code){

//        qDebug() << "功能码返回功能码：" << funtion_code << id << board_type << "鼓风机：" << allPosBlower->v_ID_Blower << allPosBlower->v_BoradType_Blower << "硬件电流：" << allPosBlower->v_ID_Relay << allPosBlower->v_BoardType_Relay;
        if(id == allPosBlower->v_ID_Blower && board_type == allPosBlower->v_BoradType_Blower){

            curPosBlower.v_BlowerStatus_fun30 =  recivceDatas.at(5);
            errorCode_fun30 = list_errorCode_fun30.at(curPosBlower.v_BlowerStatus_fun30);
            ms_DisplayDatas.errorCode_fun30 = errorCode_fun30;


            uchar hi = recivceDatas.at(7);
            uchar lo = recivceDatas.at(6);
            curPosBlower.v_faultCode = (hi << 8) + lo;

            hi = recivceDatas.at(9);
            lo = recivceDatas.at(8);
            curPosBlower.v_Curr = ((hi << 8) + lo) / 1000.0;
            ms_DisplayDatas.v_BlowerRealCurr = curPosBlower.v_Curr;

            hi = recivceDatas.at(11);
            lo = recivceDatas.at(10);
            curPosBlower.v_Vlot = ((hi << 8) + lo) / 1000.0;
            ms_DisplayDatas.v_BlowerRealVlot = curPosBlower.v_Vlot;

            hi = recivceDatas.at(13);
            lo = recivceDatas.at(12);
            curPosBlower.v_Speed = ((hi << 8) + lo);
            ms_DisplayDatas.v_BlowerRealSpeed = curPosBlower.v_Speed;

            curPosBlower.v_version = recivceDatas.at(14);   //版本号

//            qDebug() << "鼓风机功能码：" << 0x30
//                     << curPosBlower.v_faultCode << curPosBlower.v_Curr
//                     << curPosBlower.v_Vlot << curPosBlower.v_Speed << curPosBlower.v_version;
        }else if(id == allPosBlower->v_ID_Relay && board_type == allPosBlower->v_BoardType_Relay){


            uint8_t hi = recivceDatas.at(9);
            uint8_t lo = recivceDatas.at(8);
            curPosBlower.v_current = ((hi << 8) + lo) / 1000.0;
            ms_DisplayDatas.v_BlowerRealCurr_YJ = curPosBlower.v_current;
        }


    }else if(0x31 == funtion_code){

        if(recivceDatas.at(2) == allPosBlower->v_ID_Blower && recivceDatas.at(4) == allPosBlower->v_BoradType_Blower){

//            uint8_t data = recivceDatas.at(7);

//            allPosBlower->v_FAN_1_SW_MajorVersA = data & 0x3

        }else{

        }
    }
}
/**
 * @brief MBlower::dealIonrDatas    处理负离子功能码返回的信息
 * @param funCode
 * @param byteArray
 */
void MBlower::dealIonrDatas(uint8_t funCode, QByteArray &byteArray)
{
    Q_UNUSED(byteArray);
    if(funCode == 0x15){
        ms_acIonr.statusDescription = ms_acIonr.list_statusDescription.at(ms_acIonr.v_status);  //负离子运行状态信息

        ms_acIonr.v_ION_L_ION_ErrSts = ms_acIonr.v_recData0 & 0x07;
        ms_acIonr.ION_L_ION_ErrSts_Description = ms_acIonr.list_ION_L_ION_ErrSts.at(ms_acIonr.v_ION_L_ION_ErrSts);

        ms_acIonr.v_ION_L_ION_Sts = ms_acIonr.v_recData0 & 0x08;
        ms_acIonr.ION_L_ION_Sts_Description = ms_acIonr.list_ION_L_ION_Sts.at(ms_acIonr.v_ION_L_ION_Sts);

        ms_acIonr.v_ION_RespErr = ms_acIonr.v_recData0 & 0x10;
        ms_acIonr.ION_RespErr_Description = ms_acIonr.list_ION_RespErr.at(ms_acIonr.v_ION_RespErr);

        ms_acIonr.v_ION_Majorversion = ms_acIonr.v_recData1 & 0x3C;
        ms_acIonr.ION_Majorversion_Description = ms_acIonr.list_ION_Majorversion.at(ms_acIonr.v_ION_Majorversion);

        ms_acIonr.v_ION_Supplier = ms_acIonr.v_recData1 & 0xC0;
        ms_acIonr.ION_Supplier_Description = ms_acIonr.list_ION_Supplier.at(ms_acIonr.v_ION_Supplier);
    }
}
/**
 * @brief MBlower::Send_BlowerReadVer   读取鼓风机版本
 */
void MBlower::Send_BlowerReadVer()
{
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0)); // 长度占位符

    buff_send_data.append(allPosBlower->v_ID_Blower);//ID
    buff_send_data.append(0x31);//功能码
    buff_send_data.append(allPosBlower->v_BoradType_Blower);//板子类型

    buff_send_data.append(static_cast<uchar>(allPosBlower->ID_Control.toInt(nullptr, 16)));
    buff_send_data.append(static_cast<uchar>(allPosBlower->ID_Status.toInt(nullptr, 16)));

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符

    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

//    Nthread_CommTask->addNormalTask(buff_send_data, &resultgogo);
    sendDataToSerial(1, buff_send_data);
}
///////////////////////////////////////////////////////////////  负离子
/**
* @brief MBlower::Send_AC_IONR_Control 负离子控制
*/
void MBlower::Send_AC_IONR_Control()
{
   QByteArray buff_send_data;
   buff_send_data.append(0x68);
   int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
   buff_send_data.append(char(0)); // 长度占位符


   buff_send_data.append(ms_acIonr.v_ID);//ID
   buff_send_data.append(0x14);//功能码
   buff_send_data.append(ms_acIonr.v_BoardType);//ID

   buff_send_data.append(static_cast<uchar>(ms_acIonr.Id_Ctr.toInt(nullptr, 16)));
   buff_send_data.append(static_cast<uchar>(ms_acIonr.Id_Status.toInt(nullptr, 16)));


   buff_send_data.append(ms_acIonr.sendData0.byte_value);
   buff_send_data.append(ms_acIonr.sendData1);
   buff_send_data.append(char(0));
   buff_send_data.append(char(0));
   buff_send_data.append(char(0));
   buff_send_data.append(char(0));
   buff_send_data.append(char(0));
   buff_send_data.append(char(0));

   buff_send_data.append(0x0D);//结束符
   buff_send_data.append(0x0A);//结束符

   int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
   buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

//   Nthread_CommTask->addNormalTask(buff_send_data, &resultgogo);
   sendDataToSerial(1, buff_send_data);
}
/**
 * @brief MBlower::Send_AC_IONR_Read    读取负离子
 */
void MBlower::Send_AC_IONR_Read()
{
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(char(0)); // 长度占位符

    buff_send_data.append(ms_acIonr.v_ID);//ID
    buff_send_data.append(0x15);//功能码
    buff_send_data.append(ms_acIonr.v_BoardType);//ID

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符

    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

//    Nthread_CommTask->addNormalTask(buff_send_data, &resultgogo);
    sendDataToSerial(1, buff_send_data);
}
/**
 * @brief MBlower::Send_RelayControl    控制继电器
 * @param status
 */
void MBlower::Send_RelayControl(char status)
{
    v_Relay_On = 0;
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(char(0)); // 长度占位符

    buff_send_data.append(allPosBlower->v_ID_Relay);//ID
    buff_send_data.append(0x16);//功能码
    buff_send_data.append(allPosBlower->v_BoardType_Relay);//ID

    buff_send_data.append(status);

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符

    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

//    Nthread_CommTask->addNormalTask(buff_send_data, &resultgogo);
    sendDataToSerial(1, buff_send_data);
}
/**
 * @brief MBlower::Send_GetCurrent  设置硬件电流
 */
void MBlower::Send_SetCurrent()
{
    QByteArray buff_send_data;
    buff_send_data.append(0x68);
    int lengthPos = buff_send_data.size();// 长度位置先占位，后面计算
    buff_send_data.append(static_cast<char>(0)); // 长度占位符

    buff_send_data.append(allPosBlower->v_ID_Relay);//ID
    buff_send_data.append(0x11);//功能码

    buff_send_data.append(allPosBlower->v_BoardType_Relay);//板子类型
    buff_send_data.append(0x01);//用PWM

    buff_send_data.append(char(0));
    buff_send_data.append(char(0));
    buff_send_data.append(char(0)); //占空比

    short v_data = static_cast<short>(allPosBlower->v_MaxValue[v_PosIndex] * 1000);
    uchar lo = static_cast<uchar>(v_data & 0xFF);
    uchar hi = static_cast<uchar>((v_data >> 8) & 0xFF);
    buff_send_data.append(lo);
    buff_send_data.append(hi);

    v_data = static_cast<short>(allPosBlower->v_MinValue[v_PosIndex] * 1000);
    lo = static_cast<uchar>(v_data & 0xFF);
    hi = static_cast<uchar>((v_data >> 8) & 0xFF);
    buff_send_data.append(lo);
    buff_send_data.append(hi);

    buff_send_data.append(0x0D);//结束符
    buff_send_data.append(0x0A);//结束符

    int length = buff_send_data.size() - (lengthPos + 4); // 减去长度字节本身
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段

    qDebug() << "***********************    设置位置信息  ****************************" << buff_send_data.toHex();
//    Nthread_CommTask->addNormalTask(buff_send_data, &resultgogo);
    sendDataToSerial(1, buff_send_data);
}


