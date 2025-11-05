#ifndef MMODBUSRTU_H
#define MMODBUSRTU_H

#include <QObject>
#include <QTimer>
#include <QModbusRtuSerialMaster>
#include <QMutex>
#include <QLabel>
#include <QThread>
#include <QDebug>
#include "MForm_ModeBusRtu.h"

class mModbusRtu : public QObject
{
    Q_OBJECT

public:
    explicit mModbusRtu(QObject *parent = nullptr);


    QString tips;

    QTimer *pTimer;
    bool b_modbus_port_en = false;
    int v_response_timeout_count = 0;
    bool b_reConnecting = false;
    uint v_reConnect_Count = 0;

    QThread *pthread;
    QModbusRtuSerialMaster *m_modbusDevice = nullptr;

    uchar v_Size_DI = 16;
    uchar v_Size_CO = 16;
    uchar v_Size_DA = 16;
    uchar v_Size_AD = 16;

    QModbusDataUnit Wdata;

    QVector<quint16> recDatasCo = QVector<quint16> (v_Size_CO);
    QVector<quint16> recDatasDi = QVector<quint16> (v_Size_DI);

    QModbusDataUnit WdataDA;
    QVector<quint16> recDatasAD = QVector<quint16> (v_Size_AD);
    QVector<quint16> recDatasDA = QVector<quint16> (v_Size_DA);

//    bool b_recDatasDi_update = false; //判断是否刷新数据
//    QVector<quint16> recDatasDi_stateChange = QVector<quint16> (32);    //判断是否状态变化

    bool B_Rec_Finished = false;

    QString _COM_Name = "COM10";
    uint _BaudRate = 19200;
    uint _Parity = 0;
    uint _DataBits = 8;
    uint _StopBits = 1;
    uint _timeout = 3000;

    bool _rec_OK = true;

    QStringList _list_state = {"UnconnectedState", "ConnectingState", "ConnectedState", "ClosingState"};
    QStringList _list_error = {"NoError", "ReadError", "WriteError", "ConnectionError", "ConfigurationError", "TimeoutError", "ProtocolError", "ReplyAbortedError", "UnknownError"};
    QString errorCode_Connect = "UnconnectedState";
    QString errorCode_Occur = "UnconnectedState";
    QString errorCode_Sec = "NoError";
public:

    void creatModbusD(QString com, uint baudBit, uint dataBit, uint stopBits, uint parityBit);
    void disconnectDevice();

    void reconnectModbus();
public slots:

    void slot_ReadDiscreteInputs();
    void slot_ReadCoils();
    void slot_WriteCoils();
    void reConnectDevice();
    void slot_OpCl_Device(QString com, uint baudBit, uint dataBit, uint stopBits, uint parityBit);

    void slot_ReadInputRegisters();
    void slot_getState(QModbusDevice::State state);
    void slot_WriteHoldingRegisters();
private:
    QMutex mutex;
    QTimer *ptimer = new QTimer(this);

private slots:
    void _WR_OnReadReady();
    void _RD_OnReadReady();

signals:
    void sign_setled(QLabel*, int, int);
    void sign_setled_cicular(QLabel *label, const int color);
    void Sign_COMStyleSheet(const QString &name, bool b_value);
};

extern mModbusRtu *m_ModbusRtu;


#endif // MMODBUSRTU_H
