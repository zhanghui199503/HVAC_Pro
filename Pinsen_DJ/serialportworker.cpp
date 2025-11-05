#include "serialportworker.h"

#include <QDebug>
#include <QThread>

#include "thread_CommTask.h"

// 协议常量
namespace {
const quint8 HEADER_SEND = 0x68;
const quint8 HEADER_RECV = 0x69;
const quint8 END_BYTE1 = 0x0D;
const quint8 END_BYTE2 = 0x0A;

const quint8 BOARD_TYPE_PT = 0x01;        // PT电机
const quint8 BOARD_TYPE_BJ = 0x02;        // PT电机
const quint8 BOARD_TYPE_LIN = 0x03;       // LIN电机
const quint8 BOARD_TYPE_THERMISTOR = 0x04; // 温敏电阻
const quint8 BOARD_TYPE_BLOWER = 0x07;    // 鼓风机
const quint8 BOARD_TYPE_Curr = 0x05;    // 硬件电流
}

SerialPortWorker::SerialPortWorker(int portIndex, QObject *parent)
    : QObject(parent)
    , m_serialPort(nullptr)
    , m_portName("")
    , m_baudRate(115200)//波特率
    , m_dataBits(QSerialPort::Data8)//8个数据位
    , m_parity(QSerialPort::NoParity)//无奇偶校验位
    , m_stopBits(QSerialPort::OneStop)//停止位
    , m_flowControl(QSerialPort::NoFlowControl)//无流控制
    , m_portIndex(portIndex)//串口索引
    , m_isOpen(false)//判断状态
{
    qDebug() << "SerialPortWorker created for port index:" << m_portIndex << "in thread:" << QThread::currentThreadId();
}

SerialPortWorker::~SerialPortWorker()
{
    closeSerialPort();
    qDebug() << "SerialPortWorker destroyed for port index:" << m_portIndex;
}

void SerialPortWorker::setPortIndex(int index)
{
    m_portIndex = index;
}

int SerialPortWorker::getPortIndex() const
{
    return m_portIndex;
}

void SerialPortWorker::initSerialPort()
{
    if (m_serialPort) {
        closeSerialPort();
    }

    m_serialPort = new QSerialPort(); // 在工作线程中创建
    m_serialPort->setPortName(m_portName);
    m_serialPort->setBaudRate(m_baudRate);
    m_serialPort->setDataBits(m_dataBits);
    m_serialPort->setParity(m_parity);
    m_serialPort->setStopBits(m_stopBits);
    m_serialPort->setFlowControl(m_flowControl);

    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortWorker::handleReadyRead);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortWorker::handleError);

    if (m_serialPort->open(QIODevice::ReadWrite)) {
        m_isOpen = true;
        qDebug() << "Serial port" << m_portName << "opened successfully for index:" << m_portIndex << "in thread:" << QThread::currentThreadId();
        emit serialOpened(true, m_portIndex);
    } else {
        QString errorStr = m_serialPort->errorString();
        qDebug() << "Failed to open serial port" << m_portName << "for index:" << m_portIndex << "Error:" << errorStr;
        emit errorOccurred(errorStr, m_portIndex);
        emit serialOpened(false, m_portIndex);
        delete m_serialPort;
        m_serialPort = nullptr;
    }
}

void SerialPortWorker::updateSerialParameters(const QString &portName, qint32 baudRate,QSerialPort::DataBits dataBits,QSerialPort::Parity parity,QSerialPort::StopBits stopBits)
{
    m_portName = portName;
    m_baudRate = baudRate;
    m_dataBits = dataBits;
    m_parity = parity;
    m_stopBits = stopBits;

    qDebug() << "Serial parameters updated for index:" << m_portIndex
             << "Port:" << m_portName
             << "Baud:" << m_baudRate;
}

void SerialPortWorker::writeData(const QByteArray &data)
{

qDebug() << "开始发送数据:" << data.toHex();
    if (m_serialPort && m_serialPort->isOpen()) {
        qint64 bytesWritten = m_serialPort->write(data);
        if (bytesWritten == -1) {
            qDebug() << "Failed to write data to serial port for index:" << m_portIndex;
            emit errorOccurred("Write failed", m_portIndex);
        } else if (bytesWritten != data.size()) {
//            qDebug()<<"Partial write to serial port for index:"<< m_portIndex<<"Expected:"<< data.size()<< "Actual:"<< bytesWritten;
        } else {
//            qDebug()<<"Data written to serial port for index:"<< m_portIndex<< "Size:"<< bytesWritten;
        }
    } else {
//        qDebug() << "Cannot write data - serial port not open for index:" << m_portIndex;
        emit errorOccurred("Port not open", m_portIndex);
    }
}

void SerialPortWorker::closeSerialPort()
{
    if (m_serialPort) {
        if (m_serialPort->isOpen()) {
            m_serialPort->close();
            m_isOpen = false;
            qDebug() << "Serial port closed for index:" << m_portIndex;
            emit serialClosed(m_portIndex);
        }
        disconnect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortWorker::handleReadyRead);
        disconnect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortWorker::handleError);
        delete m_serialPort;
        m_serialPort = nullptr;
    }
}

void SerialPortWorker::setFlowControl(QSerialPort::FlowControl flowControl)
{
    m_flowControl = flowControl;
    if (m_serialPort && m_serialPort->isOpen()) {
        m_serialPort->setFlowControl(m_flowControl);
    }
}

void SerialPortWorker::handleReadyRead()
{
    //qDebug()<<m_serialPort<<m_serialPort->isOpen();
    if (m_serialPort && m_serialPort->isOpen()) {
        QByteArray data = m_serialPort->readAll();
//        qDebug()<<"林辉收到数据:"<<data;
//         emit Data_return();
        if (!data.isEmpty()) {
//            qDebug() << "Data received from serial port for index:" << m_portIndex<< "Size:" << data.size();
//                        emit dataReceived(data, m_portIndex);
            // 将新数据添加到缓冲区
            m_dataBuffer.append(data);

            // 解析接收到的数据
            parseFrames();
        }
    }
}

void SerialPortWorker::parseFrames()
{
    while (m_dataBuffer.size() >= 5) // 至少需要帧头和长度字段
       {
           // 查找帧头0x69
           int headerIndex = m_dataBuffer.indexOf(0x69);
//           qDebug() << "检测当前69数据位置:" << headerIndex;
           if (headerIndex == -1)
           {
               // 没有找到帧头，清空缓冲区
               m_dataBuffer.clear();
               break;
           }
           // 移除帧头之前的所有数据
           if (headerIndex > 0) {
               qDebug() << "移除帧头前的" << headerIndex << "字节";
               m_dataBuffer = m_dataBuffer.mid(headerIndex);
               headerIndex = 0; // 现在帧头在位置0
           }
           // 检查长度字段是否可用
           if (m_dataBuffer.size() < 2)
           {
               // 数据不足，等待更多数据
               break;
           }
           // 读取长度字段 (Data1) - 这个长度是从功能码(Data3)开始到结束符前的内容长度
           quint8 length = static_cast<quint8>(m_dataBuffer[1]);
//           qDebug() << "长度字段:" << length;

           // 计算完整帧长度: 帧头(1) + 长度(1) + ID(1) + 数据(length) + 结束符(2)
           int frameLength = 1 + 1 + 1 + length + 2;
//           qDebug() << "计算得到的帧长度:" << frameLength;

           // 检查是否收到完整帧
           if (m_dataBuffer.size() < frameLength) {
//               qDebug() << "数据不完整，需要" << frameLength << "字节，当前只有" << m_dataBuffer.size() << "字节";
               // 等待更多数据
               break;
           }


           //qDebug() <<"接收到数据，串口号为："<<m_portIndex;
//                   emit Data_return(m_portIndex);
           switch (m_portIndex) {
               case 0:
                   Nthread_CommTask[0]->Send_finish=true;
                   break;
               case 1:
                   Nthread_CommTask[1]->Send_finish=true;
                  break;
               case 2:
                   Nthread_CommTask[2]->Send_finish=true;
                  break;
               default:

               break;
           }


           // 提取完整帧
           QByteArray frame = m_dataBuffer.mid(0, frameLength);
           qDebug() << "提取的帧 (hex):" << frame.toHex().toUpper();

           // 验证结束符
           if (static_cast<quint8>(frame[frameLength-2]) != END_BYTE1 || static_cast<quint8>(frame[frameLength-1]) != END_BYTE2)
           {
               qDebug() << "结束符错误，跳过这个帧头";
               // 结束符错误，跳过这个帧头，继续查找
               m_dataBuffer = m_dataBuffer.mid(1);
               continue;
           }

//           qDebug() << "检测5";

           // 检查帧长度是否足够包含板子类型（至少5字节: 头+长度+ID+功能码+板子类型）
           if (frameLength < 5) {
               qDebug() << "帧长度不足，跳过";
               m_dataBuffer = m_dataBuffer.mid(frameLength);
               continue;
           }
           // 提取板子类型 (Data4位置，索引4)
           quint8 boardType = static_cast<quint8>(frame[4]);
           // 根据板子类型发射信号
           switch (boardType) {
           case BOARD_TYPE_PT: // PT电机
               qDebug() << "接收到数据，下发到PT线程进行处理";
               emit ptMotorDataReceived(frame, m_portIndex);
               break;
           case BOARD_TYPE_BJ: // BJ电机
               qDebug() << "下发到BJ线程进行处理";
//               emit BJMotorDataReceived(frame, m_portIndex);
               break;
           case BOARD_TYPE_LIN: // LIN电机
               qDebug() << "下发到LIN线程进行处理";

               emit linMotorDataReceived(frame, frame[5]);
               break;
           case BOARD_TYPE_THERMISTOR: // 温敏电阻
               qDebug() << "下发到RES线程进行处理"<<frame;
               emit thermistorDataReceived(frame);
               break;
           case BOARD_TYPE_BLOWER: // 鼓风机
               emit blowerDataReceived(frame, m_portIndex);
               break;
           case BOARD_TYPE_Curr:
               qDebug() << "鼓风机数据返回：";
               emit blowerDataReceived(frame, m_portIndex);
               break;
           default:
               qDebug() << "Unknown board type: 0x" << QString::number(boardType, 16).toUpper()
                        << "in frame from port" << m_portIndex;
               break;
           }

//           qDebug() << "检测7";

           // 从缓冲区中移除该帧
           m_dataBuffer = m_dataBuffer.mid(frameLength);
//           qDebug() << "移除帧后缓冲区大小:" << m_dataBuffer.size();
       }

}

void SerialPortWorker::handleError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError && m_serialPort) {
        QString errorStr = m_serialPort->errorString();
        qDebug() << "Serial port error for index:" << m_portIndex<< "Error:" << errorStr;
        emit errorOccurred(errorStr, m_portIndex);
        // 如果发生严重错误，自动关闭串口
        if (error == QSerialPort::ResourceError||error == QSerialPort::PermissionError||error == QSerialPort::DeviceNotFoundError)
        {
            closeSerialPort();
        }
    }
}
