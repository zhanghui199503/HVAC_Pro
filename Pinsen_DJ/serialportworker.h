#ifndef SERIALPORTWORKER_H
#define SERIALPORTWORKER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>
//#include "thread_CommTask.h"

class SerialPortWorker : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortWorker(int portIndex = -1, QObject *parent = nullptr);
    ~SerialPortWorker();

    // 设置端口索引，用于标识是哪个串口
    void setPortIndex(int index);
    int getPortIndex() const;

public slots:
    void initSerialPort(); // 初始化并打开串口
    void updateSerialParameters(const QString &portName, qint32 baudRate,
                               QSerialPort::DataBits dataBits = QSerialPort::Data8,
                               QSerialPort::Parity parity = QSerialPort::NoParity,
                               QSerialPort::StopBits stopBits = QSerialPort::OneStop); // 更新串口参数
    void writeData(const QByteArray &data); // 写入数据
    void closeSerialPort(); // 关闭串口
    void setFlowControl(QSerialPort::FlowControl flowControl); // 设置流控制

    void parseFrames();// 数据解析方法
signals:
    void dataReceived(const QByteArray &data, int portIndex); // 收到数据时发出信号，附带端口索引
    void errorOccurred(const QString &errorString, int portIndex); // 发生错误时发出信号，附带端口索引
    void serialOpened(bool success, int portIndex); // 串口打开成功与否，附带端口索引
    void serialClosed(int portIndex); // 串口关闭时发出信号，附带端口索引

    void ptMotorDataReceived(QByteArray data, int m_portIndex);

    void Data_return();

private slots:
    void handleReadyRead(); // 处理串口收到的数据
    void handleError(QSerialPort::SerialPortError error); // 处理串口错误

private:
    QSerialPort *m_serialPort;
    QString m_portName;
    qint32 m_baudRate;
    QSerialPort::DataBits m_dataBits;
    QSerialPort::Parity m_parity;
    QSerialPort::StopBits m_stopBits;
    QSerialPort::FlowControl m_flowControl;
    int m_portIndex; // 端口索引，用于标识是哪个串口
    bool m_isOpen; // 记录串口是否已打开

    // 数据缓冲区
        QByteArray m_dataBuffer;

        // 协议解析器
//        MotorProtocolParser *m_protocolParser;

        // 数据处理器映射
//        QMap<QString, QObject*> m_dataHandlers;


        bool validateFrame(const QByteArray &frame);
        void dispatchParsedData(const QVariantMap &parsedData);
};

#endif // SERIALPORTWORKER_H
