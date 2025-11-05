#include "thread_thermistor.h"

thread_Thermistor* Nthread_Thermistor = nullptr;

QMutex thread_Thermistor::m_instanceMutex; // 关键：类外定义，分配内存
//声明
thread_Thermistor *thread_Thermistor::getInstance()
{
    // 双重检查锁定（提高效率，避免每次获取实例都加锁）
    if (!Nthread_Thermistor) {
        QMutexLocker locker(&m_instanceMutex);  // 加锁确保线程安全
        if (!Nthread_Thermistor) {
            Nthread_Thermistor = new thread_Thermistor();
        }
    }
    return Nthread_Thermistor;
}
//B值计算温度
double thread_Thermistor::betaMethod(int resistance, double beta, double r25, double T)
{
    // 第一步：验证Beta参数法参数的有效性
    if (!validateBetaParameters(beta, r25)) {
        return -273.15;
    }

    // 第二步：检查电阻值和参考电阻值是否有效
    if (resistance <= 0 || r25 <= 0) {
        return -273.15;
    }

    // 第三步：计算电阻比值的自然对数
    // ln(R/R25) = 当前电阻值与25°C时电阻值的比值的对数
    double lnR = log(static_cast<double>(resistance) / r25);

    // 第四步：应用Beta参数法公式
    // 公式：1/T = 1/T0 + (1/B)*ln(R/R0)
    // 其中：T0 = 298.15K (25°C), R0 = r25

    double tempKelvin = 1.0 / ((1.0 / (273.15 + T)) + (1.0 / beta) * lnR);

    // 第五步：将开尔文温度转换为摄氏度
    return tempKelvin - 273.15;
}
//添加普通任务
void thread_Thermistor::sendDataToSerial(int portIndex, const QByteArray &data)
{
    qDebug()<<"温敏线程：添加任务"<<portIndex<<data;
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
//添加固定任务
void thread_Thermistor::addFixedToSerial(int portIndex, const QByteArray &data, bool *_en)
{
    qDebug()<<"温敏线程：添加固定任务"<<portIndex<<data;
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
//参数初始化
void thread_Thermistor::ThermistorInit()
{
    ToralThermistor_Setting_basis ToralTher_SetData;

    Thermistor_Setting_basis        Ther_SetData;
    QList<Thermistor_Setting_basis> Ther_SetData_list;

    MY_Thermistor_Status_basis          MY_Ther_Status;
    QList<MY_Thermistor_Status_basis>   MY_Ther_Status_list;

    ToralTher_SetData.DelayTime = 0;
    ToralTher_SetData.RunTime = 0;
    ToralTher_SetData.m_Borad = 0;
    ToralTher_SetData.Compare_Enable = false;
    ToralTher_SetData.temperature_Err = 0;

    Ther_SetData.RC = 0.0;
    Ther_SetData.R25 = 5000.0;
    Ther_SetData.Beta = 10.0;
    Ther_SetData.Environment = false;
    Ther_SetData.Temperature_lower = 10.0;
    Ther_SetData.Temperature_upper = 100.0;
    Ther_SetData.Temperature_Enable = false;

    MY_Ther_Status.value = 0;
    MY_Ther_Status.status = 0;
    MY_Ther_Status.temperature = 0.0;

    for(int i = 0; i < Borad_NUm; i++)
    {
        ToralThermistor_SetData.insert(i,ToralTher_SetData);
        for(int j = 0; j <= TherNumber; j++)
        {
            Ther_SetData_list.insert(j,Ther_SetData);
            MY_Ther_Status_list.insert(j,MY_Ther_Status);
        }
        Thermistor_SetData.insert(i,Ther_SetData_list);
        MY_Thermistor_Data.insert(i,MY_Ther_Status_list);
    }
}
//复位结果
void thread_Thermistor::resetStatus()
{
    ProcessSteps = 0;

    for(int i = 0; i < Borad_NUm; i++)
    {
        Borad_Enable[i] = false;
//        memset(Thermistor_Data.m_Temperature[i], 0.0, sizeof (Thermistor_Data.m_Temperature[i]));
//        memset(Thermistor_Data.m_SingleStatus[i], 0.0, sizeof (Thermistor_Data.m_SingleStatus[i]));
//        memset(Thermistor_Data.m_SingleResult[i], 0.0, sizeof (Thermistor_Data.m_SingleResult[i]));


        memset(Thermistor_Data.m_Temperature, 0.0, sizeof (Thermistor_Data.m_Temperature));
        memset(Thermistor_Data.m_SingleStatus, 0.0, sizeof (Thermistor_Data.m_SingleStatus));
        memset(Thermistor_Data.m_SingleResult, 0.0, sizeof (Thermistor_Data.m_SingleResult));

    }
    Thermistor_Data.m_TotalStatus  = 0;
    Thermistor_Data.m_TotalResult = 0;

//    Thermistor_Data1.m_TotalStatus  = 0;
    //    Thermistor_Data1.m_TotalResult = 0;
}

void thread_Thermistor::ProcessStop()
{
    ProcessSteps = 6;
}


void thread_Thermistor::run()
{
    int i = 0;
    int Themp_Num = 0;
    int delay_time = 0;
    int RunThemp_Num = 0;
    int run_number = 0;
    int run_number1 = 0;
    QByteArray themp_contrl[TherNumber],temp_totalcontrl;
    threadState = true;
    ThermistorInit();//参数初始化
    while(threadState)
    {
        if(ProcessSteps == 0)//复位
        {
            run_number1 = 0;
            run_number = 0;
            RunTime = 0;//运行时间
            RunThemp_Num = 0;
            ContrlOrWait = 0;
            delay_time = 0;
            ProcessStepsTime = 0;
            for(run_number = 0; run_number < Borad_NUm; run_number++)
            {
                for(run_number1 = 0; run_number1 < TherNumber; run_number1++)
                {
                    MY_Thermistor_Data[run_number][run_number1].value = 0;
                    MY_Thermistor_Data[run_number][run_number1].status = 0;
                    MY_Thermistor_Data[run_number][run_number1].temperature = 0;
                }
            }
            i = 0;
            Enable_Enable = 0;
        }
        else
        {
            if(ProcessStepsTime < 666)ProcessStepsTime++;
            if(ProcessSteps == 1)//开启继电器
            {
                if(Borad_Enable[i])//板子是否有检测的温敏
                {
                    if(SendThermistorOPEN(true,i))i++;
                }
                else i++;
                if(i >= Borad_NUm)
                {
                    i = 0;
                    ProcessSteps = 2;
                }
            }
            else if(ProcessSteps == 2)//开启温敏电阻检测
            {
                if(Borad_Enable[i])
                {

                    for(Themp_Num = 0; Themp_Num < TherNumber; Themp_Num++)
                    {
                        Thermistor_SetData[i][Themp_Num].Temperature_Enable ? Thermistor_Data.m_SingleStatus[i * 5 + Themp_Num] = 1 : Thermistor_Data.m_SingleStatus[i * 5 + Themp_Num] = 0;

                        themp_contrl[Themp_Num] = Thermistor_SendContrl(Thermistor_SetData[i][Themp_Num].Temperature_Enable);
                        qDebug()<<"刘温敏没问题4";
                        if(Themp_Num == 0)temp_totalcontrl = themp_contrl[Themp_Num];
                        else temp_totalcontrl += themp_contrl[Themp_Num];
                    }

                    qDebug()<<"刘温敏没问题1";
                    if(SendThermistorRun(i, temp_totalcontrl))i++;
                }
                else i++;
                if(i >= Borad_NUm)
                {
                    i = 0;
                    ProcessSteps = 3;
                }
            }
            else if(ProcessSteps == 3)//开启读取
            {
                for(i = 0; i < Borad_NUm; i++)
                {
                    if(Borad_Enable[i])ReadThermistorData(i);//读取温度
                }
                ProcessSteps = 4;
            }
            else if(ProcessSteps == 4)//温敏电阻判断
            {
                if(delay_time < ToralThermistor_SetData[0].DelayTime)delay_time++;
                else
                {
                    for(i = 0; i < Borad_NUm; i++)
                    {
                        if(Borad_Enable[i])
                        {
                            RunThemp_Num = 0;
                            for(Themp_Num = 0; Themp_Num < TherNumber; Themp_Num++)
                            {
                                if(Thermistor_SetData[i][Themp_Num].Environment && Thermistor_Data.m_SingleStatus[i * 5 + Themp_Num] == 1)//环境温度电阻
                                {
                                    Thermistor_Data.m_Temperature[i * 5 + Themp_Num] = MY_Thermistor_Data[i][Themp_Num].temperature;
                                    RunThemp_Num++;
                                }
                                else//普通电阻
                                {
                                    if(Thermistor_Data.m_SingleStatus[i * 5 +Themp_Num] == 1)
                                    {
                                        Thermistor_Data.m_Temperature[i * 5 + Themp_Num] = MY_Thermistor_Data[i][Themp_Num].temperature;

                                        if(ToralThermistor_SetData[i].Compare_Enable)//对比判断
                                        {
                                            if(Thermistor_Data.m_Temperature[i * 5 + Themp_Num] > (Environment_temperature + ToralThermistor_SetData[i].temperature_Err))
                                            {
                                                Thermistor_Data.m_SingleStatus[i * 5 + Themp_Num] = 3;
                                                Thermistor_Data.m_SingleResult[i * 5 + Themp_Num] = 2;
                                            }
                                            else if(Thermistor_Data.m_Temperature[i * 5 + Themp_Num] < (Environment_temperature - ToralThermistor_SetData[i].temperature_Err))
                                            {
                                                Thermistor_Data.m_SingleStatus[i * 5 + Themp_Num] = 0;
                                                Thermistor_Data.m_SingleResult[i * 5 + Themp_Num] = 3;
                                            }
                                        }
                                        else
                                        {
                                            //判断温度上下限
                                            if(Thermistor_Data.m_Temperature[i * 5 + Themp_Num] > Thermistor_SetData[i][Themp_Num].Temperature_upper)//大于上限
                                            {
                                                Thermistor_Data.m_SingleStatus[i * 5 + Themp_Num] = 3;
                                                Thermistor_Data.m_SingleResult[i * 5 + Themp_Num] = 2;
                                            }
                                            else if(Thermistor_Data.m_Temperature[i * 5 + Themp_Num] < Thermistor_SetData[i][Themp_Num].Temperature_lower)//小于下限
                                            {
                                                Thermistor_Data.m_SingleStatus[i * 5 + Themp_Num] = 3;
                                                Thermistor_Data.m_SingleResult[i * 5 + Themp_Num] = 3;
                                            }
                                        }

                                        RunThemp_Num++;
                                    }
                                }
                            }
                            if(RunThemp_Num == 0 && ContrlOrWait == 0)//关闭继电器
                            {
                                ContrlOrWait = i + 1;
                            }
                            if(ContrlOrWait == (i + 1))
                            {
                                if(SendThermistorStop(ContrlOrWait - 1))
                                {
                                    readFixed_en[i] = false;
                                    Borad_Enable[i] = false;
                                    ContrlOrWait = 0;
                                }
                            }
                        }
                    }
//---------------------------------------------------------------------------------------

                    int Run_number = 0;

                    Run_number = 0;
                    if(RunTime < ToralThermistor_SetData[0].RunTime)
                    {
                        RunTime++;
                        for(run_number = 0; run_number < Borad_NUm; run_number++)
                        {
                            for(run_number1 = 0; run_number1 < TherNumber; run_number1++)
                            {
                                if(!Thermistor_SetData[run_number][run_number1].Environment && Thermistor_Data.m_SingleResult[run_number * 5 +run_number1])Run_number++;
                            }
                        }
                        if(Run_number >= Enable_Enable)
                        {
                            ProcessSteps = 5;//结算
                        }
                    }
                    else//到达运行时间 RUN变OK
                    {
                        for(run_number = 0; run_number < Borad_NUm; run_number++)
                        {
                            for(run_number1 = 0; run_number1 < TherNumber; run_number1++)
                            {
                                if(Thermistor_Data.m_SingleStatus[run_number * 5 + run_number1] == 1)
                                {
                                    Thermistor_Data.m_SingleStatus[run_number * 5 + run_number1] = 2;
                                    Thermistor_Data.m_SingleResult[run_number * 5 + run_number1] = 1;
                                }
                            }
                        }
                        ProcessSteps = 5;
                    }
                }
            }
            else if(ProcessSteps == 5)//结算
            {
                int Result = 0;
                int Num = 0;
                Num = 0;
                Result = 0;
                for(i = 0; i < Borad_NUm; i++)
                {
                    readFixed_en[i] = false;
                    if(Borad_Enable[i])
                    {
                        if(SendThermistorStop(i))
                        {
                            Borad_Enable[i] = false;
                            Num++;
                        }
                    }
                    else Num++;
                    for(Themp_Num = 0; Themp_Num < TherNumber; Themp_Num++)
                    {
                        if(Themp_Num == 0 && i == 0)Thermistor_Data.m_TotalResult = 0x01;
                        Result = Thermistor_Data.m_SingleResult[i * 5 + Themp_Num] & 0x02;
                        Thermistor_Data.m_TotalResult |= (Result<<(i * 5 + Themp_Num));
                    }
                }
                if(Num >= Borad_NUm)
                {
                    Thermistor_Data.m_TotalStatus = 0;
                    ProcessSteps = 0;
                }
            }
            else if(ProcessSteps == 6)//不结算
            {
                int Result = 0;
                int Num = 0;
                Num = 0;
                Result = 0;
                for(i = 0; i < Borad_NUm; i++)
                {
                    readFixed_en[i] = false;
                    if(Borad_Enable[i])
                    {
                        if(SendThermistorStop(i))
                        {
                            Borad_Enable[i] = false;
                            Num++;
                        }
                    }
                    else Num++;
//                    for(Themp_Num = 0; Themp_Num < TherNumber; Themp_Num++)
//                    {
//                        Thermistor_Data.m_TotalResult = 0x01;
//                        Result = Thermistor_Data.m_SingleResult[i * 5 + Themp_Num] & 0x02;
//                        Thermistor_Data.m_TotalResult |= (Result<<(i * 5 + Themp_Num));
//                    }
                }
                if(Num >= Borad_NUm)
                {
                    Thermistor_Data.m_TotalStatus = 0;
                    ProcessSteps = 0;
                }
            }
            if(ProcessStepsTime >= 666)
            {
                ProcessSteps = 0;
                Thermistor_Data.m_TotalStatus = 0;
                Thermistor_Data.m_TotalResult = 2;//通讯超时
            }
        }



        if(AnionProcessSteps == 0)//负离子复位
        {
            SendAnionDataOK = 0;
        }
        else
        {
            if(AnionProcessSteps == 1)//发送负离子参数
            {
                Anion_Data.m_TotalStatus = 1;
                Anion_Data.m_SingleStatus = 1;
                if(SendAnionSendData())
                {
                    AnionProcessSteps = 2;
                }
            }
            else if(AnionProcessSteps == 2)//发送负离子读取参数
            {
                if(SendAnionReadData())
                {
                    AnionProcessSteps = 3;
                }
            }
            else if(AnionProcessSteps == 3)
            {
                mempcpy(Anion_Data.ReturnData,MY_Anion_Data.ReadData,sizeof (MY_Anion_Data.ReadData));
                if(MY_Anion_Data.Error_Num)
                {
                    Anion_Data.m_SingleStatus = 3;
                    Anion_Data.m_TotalResult = MY_Anion_Data.Error_Num;
                }
                else
                {
                    Anion_Data.m_SingleStatus = 2;
                    Anion_Data.m_TotalResult = 1;
                }
                Anion_Data.m_TotalStatus = 0;
                AnionProcessSteps = 0;
            }

        }
        QThread::msleep(100);//睡100ms
    }
}

QByteArray thread_Thermistor::Thermistor_SendContrl(bool _enable)
{
    QByteArray buff_send_data;
    _enable ? buff_send_data.append(0x01) : buff_send_data.append('\0');
    return buff_send_data;
}
//数据判断
bool thread_Thermistor::validateBetaParameters(double beta, double r25)
{
    // Beta值必须为正数，通常在3000-5000范围内
    // R25值也必须为正数，通常在1k-100k范围内
    if (beta <= 0 || r25 <= 0) {
        return false;
    }

    // 参数验证通过
    return true;
}
//温敏电阻停止
int thread_Thermistor::SendThermistorStop(int _Number)
{
    if(SendDataOK == 0)
    {
        uchar buff_value;
        QByteArray buff_send_data;

        buff_send_data.append(0x68);
        buff_send_data.append(0x02);

        buff_value = static_cast<uchar>(ToralThermistor_SetData[_Number].m_Borad);//
        buff_send_data.append(buff_value);

        buff_send_data.append(0x10);

        buff_value = static_cast<uchar>(R_TEM);
        buff_send_data.append(buff_value);//板子类型

        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
        qDebug()<<buff_send_data;
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
//温敏电阻打开
int thread_Thermistor::SendThermistorOPEN(bool OPEN, int _Number)
{
    if(SendDataOK == 0)
    {
        uchar buff_value;
        QByteArray buff_send_data;

        buff_send_data.append(0x68);
        buff_send_data.append(0x03);

        buff_value = static_cast<uchar>(ToralThermistor_SetData[_Number].m_Borad);//
        buff_send_data.append(buff_value);

        buff_send_data.append(0x11);

        buff_value = static_cast<uchar>(R_TEM);
        buff_send_data.append(buff_value);//板子类型

        OPEN ? (buff_send_data.append(0x01)) : (buff_send_data.append('\0'));
        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
        qDebug()<<buff_send_data;
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
//温敏电阻运行
int thread_Thermistor::SendThermistorRun(int _Number,QByteArray buff_send_data1)
{
    uchar buff_value;
    QByteArray buff_send_data;
    if(SendDataOK == 0)
    {
        buff_send_data.append(0x68);
        buff_send_data.append(0x07);

        buff_value = static_cast<uchar>(ToralThermistor_SetData[_Number].m_Borad);//
        buff_send_data.append(buff_value);

        buff_send_data.append(0x12);

        buff_value = static_cast<uchar>(R_TEM);
        buff_send_data.append(buff_value);//板子类型


        buff_send_data += buff_send_data1;

        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
        qDebug()<<buff_send_data;
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
//读取温敏电阻数据
void thread_Thermistor::ReadThermistorData(int _Number)
{
    if(!init_readFixed[_Number])
    {
        init_readFixed[_Number] = true;
        uchar buff_value;
        QByteArray buff_send_data;

        buff_send_data.append(0x68);
        buff_send_data.append(0x02);

        buff_value = static_cast<uchar>(ToralThermistor_SetData[_Number].m_Borad);//
        buff_send_data.append(buff_value);

        buff_send_data.append(0x30);

        buff_value = static_cast<uchar>(R_TEM);
        buff_send_data.append(buff_value);//板子类型

        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符

        qDebug()<<"读取温敏"<<buff_send_data;
         addFixedToSerial(my_portIndex, buff_send_data, &readFixed_en[_Number]);
    }
    readFixed_en[_Number] = true;
}
//发送负离子发送数据
int thread_Thermistor::SendAnionSendData()
{
    uchar buff_value;
    bool OK = false;
    int hexValue = 0;
    QByteArray buff_send_data;
    if(SendAnionDataOK == 0)
    {
        buff_send_data.append(0x68);
        buff_send_data.append(0x0C);

        buff_value = static_cast<uchar>(Anion_SetData.m_Borad);//
        buff_send_data.append(buff_value);

        buff_send_data.append(0x14);

        buff_value = static_cast<uchar>(BLOWER);
        buff_send_data.append(buff_value);//板子类型

        buff_value = static_cast<uchar>(Anion_SetData.CtrID);
        buff_send_data.append(buff_value);

        buff_value = static_cast<uchar>(Anion_SetData.StatusID);
        buff_send_data.append(buff_value);
        for(int i = 0; i < 8; i++)
        {
            hexValue = Anion_SetData.SendData[i].toInt(&OK, 16);
            buff_value = static_cast<uchar>(hexValue);
            buff_send_data.append(buff_value);
        }
        buff_send_data.append(0x0D);//结束符
        buff_send_data.append(0x0A);//结束符
        qDebug()<<"发送负离子发送协议"<<buff_send_data;
        sendDataToSerial(my_portIndex, buff_send_data);
        SendAnionDataOK = 1;
        return 0;
    }
    else if(SendAnionDataOK == 1)return 0;
    else
    {
        SendAnionDataOK = 0;
        return 1;
    }
}
//发送负离子读取数据
int thread_Thermistor::SendAnionReadData()
{
    uchar buff_value;
   QByteArray buff_send_data;
   if(SendAnionDataOK == 0)
   {
       buff_send_data.append(0x68);
       buff_send_data.append(0x02);

       buff_value = static_cast<uchar>(Anion_SetData.m_Borad);//
       buff_send_data.append(buff_value);

       buff_send_data.append(0x15);

       buff_value = static_cast<uchar>(BLOWER);
       buff_send_data.append(buff_value);//板子类型

       buff_send_data.append(0x0D);//结束符
       buff_send_data.append(0x0A);//结束符

       qDebug()<<"发送负离子读取协议"<<buff_send_data;
       sendDataToSerial(my_portIndex, buff_send_data);

       SendAnionDataOK = 1;
       return 0;
   }
   else if(SendAnionDataOK == 1)return 0;
   else
   {
       SendAnionDataOK = 0;
       return 1;
   }
}
//数据处理
void thread_Thermistor::DataProcessing(QByteArray _reData)
{
    int FunctionCode = 0;//临时功能
    int *Data;

    QVector<int> decimalArray;
    int DataNumber = 0;
    ProcessStepsTime = 0;//线程超时
    for (int i = 0; i < _reData.size(); ++i) {
        decimalArray.append(static_cast<unsigned char>(_reData[i]));
        DataNumber++;
    }

    FunctionCode = decimalArray[3];//功能码

    if(FunctionCode == 0x30)//处理温敏电阻数据
    {
        Data = &decimalArray[5];

        for(int j = 0; j < Borad_NUm; j++)
        {
//            qDebug()<<"温敏电阻阻值"<<_reData.toHex().toUpper();
            if(decimalArray[2] == ToralThermistor_SetData[j].m_Borad)//判断板号匹配
            {
                qDebug()<<"板子匹配";
                for(int i = 0; i < TherNumber; i++)
                {
                    MY_Thermistor_Data[j][i].status = (Data[0] >> i) & 0x01;//状态
                    if(Data[1 + i * 2] != 0xFF || Data[2 + i * 2] * 256 != 0xFF)
                    {
                        MY_Thermistor_Data[j][i].value = Data[1 + i * 2] + Data[2 + i * 2] * 256;//温敏电阻阻值
                        MY_Thermistor_Data[j][i].temperature =  betaMethod(MY_Thermistor_Data[j][i].value, Thermistor_SetData[j][i].Beta, Thermistor_SetData[j][i].R25, Thermistor_SetData[j][i].RC);//转温度
                        qDebug()<<QString("第%1块板的第%2温敏的阻值为%3,温度为%4,状态为%5").arg(j).arg(i).arg(MY_Thermistor_Data[j][i].value).arg(MY_Thermistor_Data[j][i].temperature).arg(MY_Thermistor_Data[j][i].status);
                        if(Thermistor_SetData[j][i].Environment)Environment_temperature = MY_Thermistor_Data[j][i].temperature;//环境温度
                    }
                    else//断线
                    {
                        if(Thermistor_Data.m_SingleStatus[j * 5 +i])
                        {
                            Thermistor_Data.m_SingleStatus[j * 5 + i] = 0;
                            Thermistor_Data.m_SingleResult[j * 5 + i] = 2;
                            Thermistor_Data.m_Temperature[j * 5 + i] = 0;
                        }
                    }
                }
                break;
            }
        }
    }
    else//控制返回判断
    {
        if(FunctionCode == 0x10)
        {

        }
        else if(FunctionCode == 0x11)
        {

        }
        else if(FunctionCode == 0x12)
        {

        }
        SendDataOK = 3;
    }
}

int thread_Thermistor::getProcessStatus()
{
    return Thermistor_Data.m_TotalStatus;
}

int thread_Thermistor::getProcessResult()
{
    return Thermistor_Data.m_TotalResult;//通讯超时
}
//复位整体的结果和状态
void thread_Thermistor::restProcessResultAndStatus()
{
    Thermistor_Data.m_TotalStatus = 0;
    Thermistor_Data.m_TotalResult = 0;
}
//复位结果
void thread_Thermistor::resetAnionStatus()
{
    for(int i = 0; i < 8; i++)
    {
        Anion_Data.ReturnData[i].clear();
        MY_Anion_Data.ReadData[i].clear();

    }
    MY_Anion_Data.Error_Num = 0;

}
//负离子参数设置
void thread_Thermistor::SetAnionFP_Setting(Anion_etting_basis _set)
{
    resetAnionStatus();
    Anion_SetData = _set;
    AnionProcessSteps = 1;
}
//负离子数据处理
void thread_Thermistor::AnionDataProcessing(QByteArray _reData)
{
    int FunctionCode = 0;//临时功能
    int *Data;

    QVector<int> decimalArray;
    int DataNumber = 0;
    for (int i = 0; i < _reData.size(); ++i) {
        decimalArray.append(static_cast<unsigned char>(_reData[i]));
        DataNumber++;
    }
    FunctionCode = decimalArray[3];//功能码
    if(FunctionCode == 0x15)
    {
        Data = &decimalArray[5];
        MY_Anion_Data.Error_Num =  Data[0] >> 1;

        for(int i = 0; i < 8; i++)
        {
            MY_Anion_Data.ReadData[i] = QString("%1").arg(Data[i + 1], 4, 16, QChar('0')).toUpper();
            if(MY_Anion_Data.ReadData[i] != Anion_SetData.Compare[i] && Anion_SetData.CompareEnable[i])
            {
                MY_Anion_Data.Error_Num |= (1<<(i+1));
            }
        }
        SendAnionDataOK = 0;
    }
    else//控制
    {
        SendAnionDataOK = 0;
    }
}
//返回数据
Anion_Status_basis thread_Thermistor::reAnionRealTimeData()
{
    return Anion_Data;
}
//获取整体的状态
int thread_Thermistor::getAnionProcessStatus()
{
    return Anion_Data.m_TotalStatus;
}
//获取整体结果
int thread_Thermistor::getAnionProcessResult()
{
    return Anion_Data.m_TotalResult;
}
//复位整体的结果和状态
void thread_Thermistor::restAnionProcessResultAndStatus()
{
    Anion_Data.m_TotalResult = 0;
    Anion_Data.m_TotalStatus = 0;
}
//设置温敏板数据
void thread_Thermistor::SetToralThermistorBorad_Setting(QList<ToralThermistor_Setting_basis> _set)
{
    ToralThermistor_SetData = _set;
}
//温敏参数设置
void thread_Thermistor::SetThermistorFP_Setting(QList<QList<Thermistor_Setting_basis> > _set)
{
    resetStatus();//复位结果
    Thermistor_Data.m_TotalStatus = 1;
    Thermistor_SetData = _set;
    for(int i = 0; i < Borad_NUm; i ++)
    {
        for(int j = 0; j < TherNumber; j++)
        {
            if(Thermistor_SetData[i][j].Temperature_Enable)
            {
                Enable_Enable++;//使能温敏数
                Borad_Enable[i] = true;
            }
        }
    }

    ProcessSteps = 1;
}
//读取温敏实时数据
Thermistor_Status_basis thread_Thermistor::reLinRealTimeData()
{
    return Thermistor_Data;
}
