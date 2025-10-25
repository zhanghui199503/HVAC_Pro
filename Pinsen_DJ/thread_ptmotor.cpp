#include "thread_ptmotor.h"

thread_ptmotor::thread_ptmotor(QObject *parent)
    : QObject(parent)
    , threadState(false)
{
    DelayTimer = new QTimer(this);
}

thread_ptmotor::~thread_ptmotor()
{
    // 清理资源
}

void thread_ptmotor::setPTMotorSettings(QList<PTMotorFP_Setting_basis> &settings)
{
    m_ptMotorSettings = settings;

}

void thread_ptmotor::setPTMotorSettings1(QList<PTMotorFP_Setting_basis1> &settings1)
{
    m_ptMotorSettings1 = settings1;

}

void thread_ptmotor::doWork()
{
    qDebug() << "PT线程开始 - 使用moveToThread方式";

    // 设置线程状态
    threadState = true;
    //qDebug()<<"111";
    // 这里是线程的主要工作逻辑

    while(threadState) {
        for(int i=0;i<m_ptMotorSettings.count();i++)//将使能的电机设置参数都发送到单片机
        {
            if(Received_Success==1)
            {
                if(!All_Ptmotors_Success)
                {
                    qDebug()<<"当前电机"+QString::number(i+1)+"开始判断："<<m_ptMotorSettings.at(i).m_motorEnabled<<m_ptMotorSettings.at(i).b_Received;
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




        if(All_Ptmotors_Success)//确定电机参数都发送完成后才开始进行电机运行
        {
            for(int i=0;i<12;i++)//循环判断电机
            {
                if(m_ptMotorSettings.at(i).m_motorEnabled)//电机开了使能
                {
                    if(Pt[i] == 1)//启动电机
                    {
                        qDebug()<<"进入启动电机" << m_ptMotorSettings1.size() <<i;
                        QStringList POSList = m_ptMotorSettings1.at(i).m_POS.split(",");//1,2,7,8,4,5,6,7  //按设置传输
                        qDebug()<<"进入启动电机1";
                        QStringList DelayTimeList = m_ptMotorSettings1.at(i).m_Time.split(",");
                        qDebug()<<"进入启动电机2";
                        QStringList MaxValueList = m_ptMotorSettings1.at(i).m_MaxValue.split(",");
                        qDebug()<<"进入启动电机3";
                        QStringList MinValueList = m_ptMotorSettings1.at(i).m_MinValue.split(",");
                        qDebug()<<"进入启动电机4";
                        if(PtMotorOver[i][0]< 8)
                        {
                            qDebug()<<"进入启动电机5";
                            if(v_state_value[i] == 0)
                            {
                                qDebug()<< i << "进入电机运行POS完成";
//                                if(DelayTimeList.at(PtMotorOver[i][0])!=0)//电机设置了跳转延时
//                                {
//                                    StartDelayTime(DelayTimeList.at(PtMotorOver[i][0]).toDouble()*10);
//                                }
                                PtMotorOver[i][0] ++;
                                v_state_value[i] = 1;
                                if(PtMotorOver[i][0] > 7)
                                {
                                    Pt[i] = 2;
//                                    PtMotorOver[i][0] = 7;
                                    v_state_value[i] = -1;
                                    break;
                                }

                            }
                            qDebug()<<"当前运行POS"<<POSList.at(PtMotorOver[i][0]).toInt();
                            if(v_state_value[i] != -1 && (POSList.at(PtMotorOver[i][0]).toInt()==7|| POSList.at(PtMotorOver[i][0]).toInt()==8 ))
                            {
                                qDebug()<<"进入走开度流程";
                                //检测开度
                                v_state_value[i] = -1;
                                Receive_Flag=0;
                                SendPtMotorDetectionOpening(m_ptMotorSettings.at(i).m_name,
                                                            m_ptMotorSettings.at(i).m_id,
                                                            m_ptMotorSettings.at(i).m_motorType,
                                                            m_ptMotorSettings.at(i).m_motorNumber,
                                                            m_ptMotorSettings.at(i).m_motorDirection,
                                                            MaxValueList.at(PtMotorOver[i][0]).toDouble()*10000,
                                                            MinValueList.at(PtMotorOver[i][0]).toDouble()*10000,
                                                            m_ptMotorSettings.at(i).m_stallCurrent,
                                                            m_ptMotorSettings.at(i).m_currentLowerLimit,
                                                            m_ptMotorSettings.at(i).m_timeoutMs);
                                qDebug()<<"发送参数"<<"ID:"<<m_ptMotorSettings.at(i).m_id<<"电压上限值:"<<MaxValueList.at(PtMotorOver[i][0]).toDouble()*100<<"电压下限值:"<<MinValueList.at(PtMotorOver[i][0]).toDouble()*100
                                         <<"堵转电流:"<<m_ptMotorSettings.at(i).m_stallCurrent<<"电流下限:"<<m_ptMotorSettings.at(i).m_currentLowerLimit;
                            }
                            else if(v_state_value[i] != -1)
                            {
                                //走POS
                                qDebug()<<"进入走POS流程";
                                v_state_value[i] = -1;
                                Receive_Flag =0;
                                SendPtMotorOperation(m_ptMotorSettings.at(i).m_name,
                                                     m_ptMotorSettings.at(i).m_id,
                                                     m_ptMotorSettings.at(i).m_motorType,
                                                     m_ptMotorSettings.at(i).m_motorNumber,
                                                     MaxValueList.at(PtMotorOver[i][0]).toDouble()*10000,
                                                     MinValueList.at(PtMotorOver[i][0]).toDouble()*10000,
                                                     m_ptMotorSettings.at(i).m_currentUpperLimit,
                                                     m_ptMotorSettings.at(i).m_currentLowerLimit,
                                                     m_ptMotorSettings.at(i).m_timeoutMs);
                                qDebug()<<"发送参数"<<"ID:"<<m_ptMotorSettings.at(i).m_id<<"电压上限值:"<<MaxValueList.at(PtMotorOver[i][0]).toDouble()*100<<"电压下限值:"<<MinValueList.at(PtMotorOver[i][0]).toDouble()*100
                                                  <<"电流上限:"<<m_ptMotorSettings.at(i).m_currentUpperLimit<<"电流下限:"<<m_ptMotorSettings.at(i).m_currentLowerLimit;

                            }
                            if(v_state_value[i] == -1 && Receive_Flag==1 )//循环读取电机状态
                            {
                                qDebug()<<"进入启动电机6";
                                ReadPtMotorStatus(m_ptMotorSettings.at(i).m_name,m_ptMotorSettings.at(i).m_id,m_ptMotorSettings.at(i).m_motorType,m_ptMotorSettings.at(i).m_motorNumber);//读取电机状态
                                Receive_Flag=0;
                            }
                        }
                    }
                    else if(Pt[i] == 2)
                    {
                        qDebug()<<"电机"<<QString::number(i)<<"已运行8个POS";
                    }


                }
            }

        }

        QCoreApplication::processEvents();
        QThread::msleep(10); // 根据需要调整

        // 可以添加退出条件
        // if (some_condition) break;
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

    qDebug()<< "ID*2+Motornum:" << ID*2+Motornum;
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
        qDebug()<<"进入判断运行功能码";
        Receive_Flag=1;
    }
    else if(Data.mid(6,2) == "12")//判断检测开度功能码
    {
        qDebug()<<"进入判断检测开度功能码";
        Receive_Flag=1;

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
              qDebug()<<"全部电机写入完成";

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
        Receive_Flag=1;
    }
    else if(Data.mid(6,2) == "30")//判断读取状态参数功能码
    {
        qDebug()<<"进入判断读取状态参数功能码";
        if(1)
        {
            int startPos= 0;
            int byteCount =0;
            int ID=0,Motornum=0,CurrentState=0,CurrentPos=0;
            QString CurrentV=0,CurrentA=0;
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
            startPos = 12; // 起始位置
            byteCount = 4; // 4字节 = 8个16进制字符
            if(startPos + byteCount <= Data.size()) {
                QByteArray hexPart = Data.mid(startPos, byteCount);
                bool ok;

                 CurrentV = QString::number(hexPart.toInt(&ok, 16) / 10000.0, 'f', 2);
            }
            startPos = 16; // 起始位置
            byteCount = 4; // 4字节 = 8个16进制字符
            if(startPos + byteCount <= Data.size()) {
                QByteArray hexPart = Data.mid(startPos, byteCount);
                bool ok;
//                CurrentA  = hexPart.toInt(&ok, 16)/ 1000.0;;
                CurrentA = QString::number(hexPart.toInt(&ok, 16) / 1000.0, 'f', 3);
            }
            startPos = 22; // 起始位置
            byteCount = 2; // 4字节 = 8个16进制字符
            if(startPos + byteCount <= Data.size()) {
                QByteArray hexPart = Data.mid(startPos, byteCount);
                bool ok;
                CurrentState  = hexPart.toInt(&ok, 16);
            }
            qDebug()<<"接收参数"<<"ID:"<<ID<<"电机号:"<<Motornum<<"位置电压:"<<CurrentV<<"位置电流:"<<CurrentA;

            if(CurrentState == 0x00)//判断当前电机转态是否停止
            {
                qDebug()<<"进入到完成电机停止:"<<ID*2+Motornum-1;
                v_state_value[ID*2+Motornum-1] = 0;
            }
            else
            {
                v_state_value[ID*2+Motornum-1] = -1;
            }

            CurrentPos = PtMotorOver[ID*2+Motornum][0];

//            emit SendMotortatus("PT",ID,Motornum,CurrentV,CurrentA,CurrentPos,CurrentState);
        }
        Receive_Flag=1;

    }
}



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
    Nthread_CommTask->addNormalTask(PTName,buff_send_data,&resultgogo);
    qDebug()<<buff_send_data.toHex();
    //    emit SendData(PTName,buff_send_data);
}

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
    Nthread_CommTask->addNormalTask(PTName,buff_send_data,&resultgogo);
    qDebug()<<buff_send_data.toHex();
    //    emit SendData(PTName,buff_send_data);
}

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
    qDebug()<<buff_send_data.size()<<lengthPos + 4<<length;
    buff_send_data[lengthPos] = static_cast<char>(length);// 更新长度字段
    Nthread_CommTask->addNormalTask(PTName,buff_send_data,&resultgogo);
    qDebug()<<buff_send_data.toHex();
    //    emit SendData(PTName,buff_send_data);
}

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
    Nthread_CommTask->addNormalTask(PTName,buff_send_data,&resultgogo);
    qDebug()<<buff_send_data.toHex();
    //    emit SendData(PTName,buff_send_data);
}

void thread_ptmotor::ReceiveRunMotor(QString PTName)
{
    qDebug()<<"接收运行电机信号"+PTName;
    Pt[PTName.toInt()] = 1;
    PtMotorOver[PTName.toInt()][0] = 0;
    v_state_value[PTName.toInt()] = 1;
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

/*
* @description 发送串口数据，区分串口分发到对应的处理线程
* @param {int} portIndex 串口号编号
* @param {QByteArray &} date 发送数据
* @returns {void} 无
* @date 2025-10-24 11:22:00
* @author zh
*/
void thread_ptmotor::sendDataToSerial(int portIndex, const QByteArray &data)
{

}

