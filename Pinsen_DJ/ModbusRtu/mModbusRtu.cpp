#include "mModbusRtu.h"
///
/// \brief m_ModbusRtu
///
/// 站号1：32输入32输出
/// 站号2：32输出
/// 站号3：16AD采集
///
mModbusRtu *m_ModbusRtu;

// ***************************************************************** IO采集
mModbusRtu::mModbusRtu(QObject *parent) : QObject(parent)
{
    pthread = new QThread;
    Wdata = QModbusDataUnit(QModbusDataUnit::Coils, 0, v_Size_CO);
    WdataDA = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, v_Size_DA);

    recDatasAD.resize(v_Size_AD);

//    recDatasAD[4] = 1;
//    recDatasAD[5] = 1;
//    recDatasAD[6] = 2;
//    recDatasAD[7] = 44;

    // 在初始化时监听状态变化
    this->moveToThread(pthread);
    connect(pthread, &QThread::started, this, [=](){
        creatModbusD(mS_BSMIO.BSM_PORT, mS_BSMIO.BSM_BUAD.toUInt(), 8, 1, 0);
    });
}
/**
 * @brief mModbusRtu::slot_getState 状态改变
 * @param state
 */
void mModbusRtu::slot_getState(QModbusDevice::State state)
{
    qDebug() << "串口状态：" << _list_state.at(state);
    if (state == QModbusDevice::UnconnectedState){
        reconnectModbus();
    }
}
void mModbusRtu::reconnectModbus()
{
    if (m_modbusDevice->state() == QModbusDevice::ConnectedState)
        return;
    m_modbusDevice->disconnectDevice();
//    if (!m_modbusDevice->connectDevice()) {
//        qDebug() << "重新连接 报错:" << m_modbusDevice->errorString();

////        ptimer->singleShot(1000, this, &mModbusRtu::reconnectModbus);
//    }
}

void mModbusRtu::creatModbusD(QString com, uint baudBit, uint dataBit, uint stopBits, uint parityBit)//连接ModbusRtu
{
    _COM_Name = com;
    _BaudRate = baudBit;
    _DataBits = dataBit;
    _StopBits = stopBits;
    _Parity = parityBit;

    m_modbusDevice = new QModbusRtuSerialMaster(this);
//    connect(m_modbusDevice, &QModbusDevice::errorOccurred, this, [=](QModbusDevice::Error error){
//        qDebug() << _list_error.at(error);
//    });
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, _COM_Name);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, _BaudRate);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, _DataBits);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, _StopBits);
    m_modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, _Parity);
    m_modbusDevice->setTimeout(100);
    m_modbusDevice->setNumberOfRetries(0);

    //5. 连接到设备
    bool ok = m_modbusDevice->connectDevice();
    if (!ok){
        b_modbus_port_en = false;
        emit Sign_COMStyleSheet("防误箱", false);
        qDebug() << QString("连接BSM串口参数%1,%2失败： ").arg(_COM_Name).arg(_BaudRate) << m_modbusDevice->error();
    }else{
        b_modbus_port_en = true;
        emit Sign_COMStyleSheet("防误箱", true);
    }
    qDebug() << "创建串口";
}

void mModbusRtu::slot_OpCl_Device(QString com, uint baudBit, uint dataBit, uint stopBits, uint parityBit)
{
    if(m_modbusDevice == nullptr){
        creatModbusD(com, baudBit, dataBit, stopBits, parityBit);
        return;
    }
    if(m_modbusDevice->state() == QModbusDevice::ConnectedState){
        m_modbusDevice->disconnectDevice();
       emit Sign_COMStyleSheet("防误箱", false);
    }else{
        creatModbusD(com, baudBit, dataBit, stopBits, parityBit);
    }
}
void mModbusRtu::reConnectDevice()//重连
{
    v_reConnect_Count++;
    m_modbusDevice->disconnectDevice();
    bool ok = m_modbusDevice->connectDevice();
    if (!ok){
        b_modbus_port_en = false;
        qDebug() << QString("重连串口失败:").arg(_COM_Name).arg(_BaudRate) << m_modbusDevice->error();
        pTimer->start(500);
    }else{
        pTimer->stop();
        b_reConnecting = false;
        b_modbus_port_en = true;
//        emit sign_setled_cicular(MainWindow::mutualUi->ui->led_485, m_color::Green);
    }
}
//读取离散输入值
void mModbusRtu::slot_ReadDiscreteInputs()
{
    mutex.lock();
    //    从地址0开始读取10个离散输入量的值 02
    QModbusDataUnit data(QModbusDataUnit::DiscreteInputs, 0, v_Size_DI);

   QModbusReply *_RD_Reply  = m_modbusDevice->sendReadRequest(data, 0x01);

    if (nullptr == _RD_Reply){
        qDebug() << "发送请求数据失败: " << m_modbusDevice->errorString();
    }else{
        if (!_RD_Reply->isFinished()){
            connect(_RD_Reply, &QModbusReply::finished, this, &mModbusRtu::_RD_OnReadReady);
        }
    }
    mutex.unlock();
}
//读取AD输入
void mModbusRtu::slot_ReadInputRegisters()
{
    if(m_modbusDevice == nullptr){
        return;
    }
    if(m_modbusDevice->state() != QModbusDevice::ConnectedState){
        qDebug() << "状态未连接:" << _list_state.at(m_modbusDevice->state());
        return;
    }
    mutex.lock();
    //    从地址0开始读取10个离散输入量的值 02
    QModbusDataUnit data(QModbusDataUnit::InputRegisters, 0, v_Size_AD);

   QModbusReply *_RD_Reply  = m_modbusDevice->sendReadRequest(data, 0x02);

    if (nullptr == _RD_Reply){
        qDebug() << "发送请求数据失败: " << m_modbusDevice->errorString();
    }else{
        if (!_RD_Reply->isFinished()){
            connect(_RD_Reply, &QModbusReply::finished, this, &mModbusRtu::_RD_OnReadReady);
        }
    }
    mutex.unlock();
}
/**
 * @brief mModbusRtu::slot_WriteHoldingRegisters
 */
void mModbusRtu::slot_WriteHoldingRegisters()
{
    if(m_modbusDevice == nullptr){
        return;
    }
    if(m_modbusDevice->state() != QModbusDevice::ConnectedState){
        qDebug() << "状态未连接:" << _list_state.at(m_modbusDevice->state());
        return;
    }
    mutex.lock();

   QModbusReply *_RD_Reply  = m_modbusDevice->sendWriteRequest(WdataDA, 0x02);

    if (nullptr == _RD_Reply){
        qDebug() << "发送请求数据失败: " << m_modbusDevice->errorString();
    }else{
        if (!_RD_Reply->isFinished()){
            connect(_RD_Reply, &QModbusReply::finished, this, &mModbusRtu::_RD_OnReadReady);
        }
    }
    mutex.unlock();
}

//读取线圈值
void mModbusRtu::slot_ReadCoils()
{
    if(m_modbusDevice == nullptr){

        return;
    }
    if(m_modbusDevice->state() != QModbusDevice::ConnectedState){
        qDebug() << "状态未连接:" << _list_state.at(m_modbusDevice->state());
        return;
    }

    QModbusDataUnit data(QModbusDataUnit::Coils, 0, v_Size_CO);
    QModbusReply *_RD_Reply = m_modbusDevice->sendReadRequest(data, 0x01);

    if (nullptr == _RD_Reply){
        qDebug() << "发送请求数据失败: " << m_modbusDevice->errorString();
    }else{
        if (!_RD_Reply->isFinished()){
            connect(_RD_Reply, &QModbusReply::finished, this, &mModbusRtu::_RD_OnReadReady);
        }
    }
}
/**
 * @brief mModbusRtu::slot_WriteCoils   写线圈
 */
void mModbusRtu::slot_WriteCoils()
{
    if(m_modbusDevice == nullptr){
        return;
    }
    if(m_modbusDevice->state() != QModbusDevice::ConnectedState){
        qDebug() << "状态未连接:" << _list_state.at(m_modbusDevice->state());
        return;
    }
    mutex.lock();
    QModbusReply *_WR_Reply = m_modbusDevice->sendWriteRequest(Wdata, 0x01);

    if (nullptr == _WR_Reply){
        qDebug() << "发送请求数据失败: " << m_modbusDevice->errorString();
    }else{
        if (!_WR_Reply->isFinished()){
            connect(_WR_Reply, &QModbusReply::finished, this, &mModbusRtu::_WR_OnReadReady);
        }
    }
    mutex.unlock();
}

void mModbusRtu::_RD_OnReadReady()
{
    QModbusReply* reply = qobject_cast<QModbusReply*>(sender());
    //判断是否出错
    errorCode_Sec = _list_error.at(reply->error());
    if (reply->error() == QModbusDevice::NoError){
        //读取响应数据
        const QModbusDataUnit responseData = reply->result();

        if(reply->result().registerType() == QModbusDataUnit::Coils){            //线圈输出
            if(reply->serverAddress() == 1){
                recDatasCo = responseData.values();
            }
        }else if(reply->result().registerType() == QModbusDataUnit::DiscreteInputs){            //离散输入
            if(reply->serverAddress() == 1){

                recDatasDi = responseData.values();
            }

        }else if(reply->result().registerType() == QModbusDataUnit::InputRegisters){
            //输入寄存器
            if(reply->serverAddress() == 2){
                recDatasAD = responseData.values();
            }

        }else if(reply->result().registerType() == QModbusDataUnit::HoldingRegisters){
            //保存寄存器
            if(reply->serverAddress() == 2){
                recDatasDA = responseData.values();
            }
        }
    }else{
        if (reply->error() == QModbusDevice::ProtocolError){
            v_response_timeout_count ++;
        }else if(reply->error() == QModbusDevice::TimeoutError){
            v_response_timeout_count ++;
             b_modbus_port_en = false;
        }else if(reply->error() == QModbusDevice::ReplyAbortedError){//设备终端，无法回复
            b_modbus_port_en = false;
        }
    }
    B_Rec_Finished = true;
    reply->deleteLater();
}

void mModbusRtu::_WR_OnReadReady()
{
    QModbusReply* reply = qobject_cast<QModbusReply*>(sender());
    errorCode_Sec = _list_error.at(reply->error());
    //判断是否出错
    if (reply->error() == QModbusDevice::NoError){
        //读取响应数据
        const QModbusDataUnit responseData = reply->result();

        if(reply->serverAddress() == 1){
            recDatasCo = responseData.values();
        }
    }else{
        if (reply->error() == QModbusDevice::ProtocolError){
            v_response_timeout_count ++;
        }else if(reply->error() == QModbusDevice::TimeoutError){
            v_response_timeout_count ++;
            b_modbus_port_en = false;
        }else if(reply->error() == QModbusDevice::ReplyAbortedError){
            b_modbus_port_en = false;
        }
    }
    B_Rec_Finished = true;
    //删除reply
    reply->deleteLater();
}



