#ifndef MBLOWER_H
#define MBLOWER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include "motor_types.h"
#include <QMetaType>
#include <QLabel>
#include <QTime>
#include <QMutex>

#define AD_VibrationX 0
#define AD_VibrationY 1
#define AD_VibrationZ 2
#define AD_Noise 3


struct MS_base{

    float v_start_delay = 0.0;  //启动延时
    float v_error_delay = 0.0;  //延时报警
    int8_t v_Result = 0;//总结果
    bool B_EN = false;
    QVector<float> v_MaxValue;
    QVector<float> v_MinValue;
    QVector<int8_t> v_PosResult;    //每个POS的振动结果
};

Q_DECLARE_METATYPE(Blower_Setting_basis)

//////////////////////////  负离子
union AC_IONR_BITS
{
    unsigned char byte_value;
    struct
    {
        unsigned char AC_IONRunReq  : 2;
        unsigned char VIU_UsageMode : 4;
        unsigned char IPB_VehicleSpeedValid : 1;
        unsigned char bit8 : 1;
    }bits;
};
/**
 * @brief The Union_BlowerResult union  结果
 */
union Union_BlowerResult
{
    unsigned char v_result = 0;
    struct
    {
        unsigned char Blower_bit0  : 1;
        unsigned char VibrationX_bit1  : 1;
        unsigned char VibrationY_bit2  : 1;
        unsigned char VibrationZ_bit3  : 1;
        unsigned char Noise_bit4  : 1;
        unsigned char AcIonr_bit5  : 1;
        unsigned char bit6  : 1;
        unsigned char bit7  : 1;
    }bits;
};

struct MS_ION{

    uchar v_ID = 0;
    uchar v_BoardType = 0;
    QString Id_Ctr;   //控制ID
    QString Id_Status;    //状态ID

    //写入数据
    union AC_IONR_BITS sendData0;
    unsigned char sendData1;

    //返回数据
    QList<QString> list_statusDescription = {"初始化", "正常工作", "断联"}; QString statusDescription;
    uint8_t v_status = 0;

    uint8_t v_recData0 = 0;
    uint8_t v_recData1 = 0;

    QList<QString> list_ION_L_ION_ErrSts = {"No Error", "Error(EEPROM/FLASH/Watdog Reset)", "Short Circuit", "Open Circuit", "UnderVoltage Error","OverVoltage Error","Reserved","Reserved"};
    QString ION_L_ION_ErrSts_Description;
    uint8_t v_ION_L_ION_ErrSts = 0;   //打开供模块的电源之后，模块将根据主节点发送的帧头报告模块错误状态

    QList<QString> list_ION_L_ION_Sts = {"Standby", "Running"};
    QString ION_L_ION_Sts_Description;
    uint8_t v_ION_L_ION_Sts = 0;  //当电源档处于IGN ON状态时，模块将根据主节点发送的帧头报告模块状态

    QList<QString> list_ION_RespErr = {"Normal","Error"};
    QString ION_RespErr_Description;
    uint8_t v_ION_RespErr = 0;    //LIN通讯错误

    QList<QString> list_ION_Majorversion = {"reserve", "A", "B", "C"};
    QString ION_Majorversion_Description;
    uint8_t v_ION_Majorversion = 0;   //主版本

    QList<QString> list_ION_Minorversion = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"};
    QString ION_Minorversion_Description;
    uint8_t v_ION_Minorversion = 0;   //次版本

    QList<QString> list_ION_Supplier = {"供应商A 苏州翰霖","供应商B 美时美克", "供应商C", "供应商D"};
    QString ION_Supplier_Description;
    uint8_t v_ION_Supplier = 0;   //供应商
};



typedef enum {
    LIN_STOP = 0,     //鼓风机已停止
    LIN_RUN,          //鼓风机在运行
    LIN_DISCONNECT,   //与鼓风机断联
    LIN_ERROR,        //鼓风机有故障码
    LIN_OVERSPEED,    //鼓风机超上限
    LIN_DOWMSPEED,     //鼓风机超下限
//	LIN_OVERTIME       //在规定时间未达到指定速度
    LIN_OVERCUR,
    LIN_DOWNCUR,
}EN_LIN_Status;


typedef enum {
    POS_NE,
    POS_RUNNING,
    POS_OK,
    POS_NG,
    POS_WAIT,
    POS_START,
    POS_CONTINUE,
    POS_SET_POS_PARS,
    POS_NEXT_POS,
    POS_Judge,
    POS_STOP_BLOWER,
    POS_RELAY_CTR,
    POS_START_DELAY_WAIT,

}EM_POS_STEP;

typedef enum {
    PWM=1,
    Vlot,
    LIN,
}EM_BlowerType;


typedef enum {
    LIN_SPEED_OVER,
    LIN_SPEED_DOWN,
    LIN_CURR_OVER,
    LIN_CURR_DOWN,

}EM_ErrorCode;

class MClassBlower;


struct MS_DisplayDatas{

//    int8_t *v_TimerStep = nullptr;    //定时器类型

    uint8_t v_Cur_PosIndex = 0; //当前POS
    QString errorCode_fun30;

    float v_BlowerRealVlot = 0;
    float v_BlowerRealCurr = 0;
    float v_BlowerRealCurr_YJ = 0;  //硬件电流
    int v_BlowerRealSpeed = 0;

    QVector<float> v_PosVlots_Blower; //记录每个位置的电压
    QVector<float> v_PosCurrs_Blower;  //  记录每个位置的电流
    QVector<uint16_t> v_PosSpeed_Blower;    //记录每个位置的速度

    //鼓风机
    int8_t v_allPosResult_blower = 0;
    float v_Real_Blower = 0;

    QVector<uint8_t> v_PosSteps_Blower;
    QVector<int8_t> v_PosResult_Blower;    //每个位置POS结果
    QVector<ushort> v_Speed_Blower; //LIN转速
    QVector<uint8_t> v_PWM_Blower;   //PWM占空比
    QVector<float> v_Vlot_Blower;  //端电压

    QVector<float> v_MaxValue_Blower;  //上限
    QVector<float> v_MinValue_Blower;  //下限

    //X轴
    int8_t v_allPosResult_VibrationX = 0;
    float v_Real_VibrationX = 0;    //当前
    bool B_EN_VibrationX = false;
    QVector<float> v_Datas_VibrationX;
    QVector<int8_t> v_PosResult_VibrationX;    //每个POS的振动结果
    QVector<float> v_MaxValue_VibrationX;
    QVector<float> v_MinValue_VibrationX;
    //Y轴
    int8_t v_allPosResult_VibrationY = 0;
    float v_Real_VibrationY = 0;    //当前
    bool B_EN_VibrationY = false;
    QVector<float> v_Datas_VibrationY;
    QVector<int8_t> v_PosResult_VibrationY;    //每个POS的振动结果
    QVector<float> v_MaxValue_VibrationY;
    QVector<float> v_MinValue_VibrationY;
    //Z轴
    int8_t v_allPosResult_VibrationZ = 0;
    float v_Real_VibrationZ = 0;
    bool B_EN_VibrationZ = false;
    QVector<float> v_Datas_VibrationZ;
    QVector<int8_t> v_PosResult_VibrationZ;    //每个POS的振动结果
    QVector<float> v_MaxValue_VibrationZ;
    QVector<float> v_MinValue_VibrationZ;
    //噪音
    int8_t v_allPosResult_Noise = 0;
    float v_Real_Noise = 0;
    bool B_EN_Noise = false;
    QVector<float> v_Datas_Noise;
    QVector<int8_t> v_PosResult_Noise;    //每个POS的振动结果
    QVector<float> v_MaxValue_Noise;
    QVector<float> v_MinValue_Noise;
};


class MBlower : public QObject
{
    Q_OBJECT

public:
    explicit MBlower(QObject *parent = nullptr);


    static MBlower* getInstance();

    QTimer *pTimer;
    QThread *pthread;

    bool B_RealReadBlower = false;  //实时读数据
    bool B_DoWork = false;
    bool B_TimeOut = false;   //定时器超时

    enum EM_TIMER{
        NONE,
        START_DELAY_BLOWER,
    };

    int8_t v_TimerStep = EM_TIMER::NONE; //定时器步骤

    /**
     * @brief The EM_WorkStatus enum    程序运行状态
     */
    enum EM_WorkStatus{
        Finished,
        Running,
        Stateless,
    };

    union Union_BlowerResult allResult;//当前工作的结果
    MS_ION ms_acIonr;   //负离子

    uchar v_WorkStatus = EM_WorkStatus::Finished; //整个流程工作状态
    uint8_t v_allResult = 0;//总结果 0：未有结果  1：OK  其他：NG（代码）

    uchar v_lastStepStatus = 0;//记录上一个状态
    uchar v_CurStepStatus = 0;//未开始
    uchar v_CurStepResult = 0;  //无结果

    MClassBlower *allPosBlower;
    MS_DisplayDatas ms_DisplayDatas;


    MS_base ms_VibrationX;
    MS_base ms_VibrationY;
    MS_base ms_VibrationZ;
    MS_base ms_Noise;

    uchar v_PosIndex = 0;
    ushort v_WatiTime = 0;  //时间范围内

    uchar v_Set_OR_Read = 0;    //0:设置  1:读取
    uchar v_Init_Finished = 0;  //初始化完成

    //鼓风机状态
    QVector<uchar> vec_Blower_LIN = {LIN_RUN};
    QVector<uchar> vec_Blower_PWM = {LIN_STOP, LIN_RUN, LIN_DISCONNECT, LIN_ERROR, LIN_OVERCUR, LIN_DOWNCUR};
    QVector<uchar> vec_Blower_Vlot = {LIN_STOP, LIN_RUN, LIN_DISCONNECT, LIN_ERROR, LIN_OVERCUR, LIN_DOWNCUR};

    QString errorCode_fun30;
    QList<QString> list_errorCode_fun30 = {"鼓风机已停止", "鼓风机在运行", "与鼓风机断联", "鼓风机有故障码", "鼓风机转速超上限", "鼓风机转速超下限", "鼓风机电流超上限", "鼓风机电流超下限"};

    int8_t v_Relay_On = -1;    //手动开继电器

    struct RealPosBlower{
        bool B_External_OK = false;//外部OK信号
        int v_BlowerStatus_fun30 = 0; //单片机返回鼓风机状态

        short v_faultCode = 0;  //鼓风机故障代码
        float v_Speed = 0.0;
        float v_Vlot = 0.0;
        float v_Curr = 0.0;
        float v_Time = 0.0;
        int v_version = 0.0;//版本号


        float v_current = 0;//硬件电流
    };

    RealPosBlower curPosBlower;


    void sendSetPars();
    void JudgePos();
    void SendStopWorkAndWR(char blower, char uvlamp, char avIonr, char blowerVer);
    void Send_FixedPars(short start_delay, char curr_aveCount, char vlot_aveCount, char buad_type, char id_type);
    void SendReadStatus();
    void SendPosPars();
    void TimerStop();
    void WorkFinished();

    void Send_AC_IONR_Control();
    void Send_BlowerReadVer();
    void Send_AC_IONR_Read();
    void dealIonrDatas(uint8_t funCode, QByteArray &byteArray);
    void TimerStart(int ms, char v_timerType = 0);
    void sort_DisplayDatas();
    void clear_DisplayDatas();
    void init_DisplayDatas();
    void sendDataToSerial(int portIndex, const QByteArray &data);
    void addFixedToSerial(int portIndex, const QByteArray &data, bool *_en);
    bool Judge_POS_EN();
private:

    static QMutex m_instanceMutex;      // 单例创建的互斥锁
    QVector<uchar>* p_vec_BlowerOKStatus = &vec_Blower_LIN;

    bool init_Fixed_en = false;
    bool Fixed_en = false;

    bool init_Fixed_en_current = false;
    bool Fixed_en_current = false;

signals:
    void sign_Blower_PosStatus(uchar posIndex, uchar posStatus);
    void sign_Blower_allPosFinished();
    void sign_BlowerWait(); //鼓风机NG，等待
    void sign_setled(QLabel* label, char color);

public slots:
    void doWork();
    void slot_Timeout();
    void slot_initWork();
    void slot_RecivceDatas(QByteArray byteArray);
    void slot_SendFixedPars();

    void slot_BlowerFixedPar(Blower_Setting_basis blowerFixPar, Blower_Setting_basis1 variablePars);
    void slot_BlowerStop();//停止鼓风机
    void slot_BlowerContinue();//继续鼓风机
    void MBlowerStart();
    uchar getProcessStatus();
    uint8_t getProcessResult();
    MS_DisplayDatas reLinRealTimeData();
    void Send_RelayControl(char status);
    void slot_Blower_ResetProcessFlags();
    void slot_Blower_ResetVars();
    void Send_SetCurrent();
    void Send_FixedPars_Relay(short start_delay, char curr_aveCount, char vlot_aveCount, char buad_type, char id_type);
    void SendReadStatus_Current();
};

class MClassBlower
{

public:

    QVector<int8_t> v_PosStatus;//位置完成状态
    QVector<int8_t> v_PosResult;    //每个位置POS结果

    uint8_t v_ID_Relay = 5; //继电器ID
    uint8_t v_BoardType_Relay = 5;//继电器板子类型
    uint8_t v_StartDelay_Relay = 0;//继电器启动延时
    uint8_t v_AlarmDelay_Relay = 0;//继电器报警延时

    uint8_t v_ID_Blower = 0;//板子ID

    uint8_t v_BoradType_Blower = 7;  //板子类型
    char v_linType = 1; // 只有鼓风机：1, 其他功能：2

    char v_allPosSize = 9; //支持POS个数

    char v_currAve = 10;
    char v_vlotAve = 10;
    int v_LINBaud = 19200;//默认19200
    char v_idType = 0;//帧ID

    bool B_Blower_EN = false;   //鼓风机使能标志
    char v_Type = 3;    //鼓风机类型

    float v_AlarmDelay = 0.5;   //报警延时
    float v_StartDelay = 1.1;   //启动延时
    float v_PowerMaxValue = 0.0;    //电源电压上限值
    float v_PowerMinValue = 0.0;    //电源电压下限值

    //LIN额外
    QString ID_Control = "0D";//控制ID
    QString ID_Status = "0E";//状态ID
    QString ID_Send;
    QString ID_Read;

    bool B_SpeedCompare = false;
    short v_SpeedError = 0;

    //运行顺序
    short v_HZ = 500;
    //1~9档
    QVector<uint8_t> v_PosStep;   //位置顺序
    QVector<ushort> v_Speed; //LIN转速
    QVector<uchar> v_PWM;   //PWM占空比
    QVector<float> v_Vlot;  //端电压
    QVector<float> v_Time;  //时间
    QVector<float> v_MaxValue;  //上限
    QVector<float> v_MinValue;  //下限
    QVector<ushort> v_WaitTime;//鼓风机判断时间

    //鼓风机版本
    uint8_t v_FAN_1_SW_MajorVersA = 0;  //硬件主版本号B
    uint8_t v_FAN_1_SW_MinorVersA = 0;  //软件次版本号A
    uint8_t v_FAN_1_HW_PhaVers = 0; //硬件阶段版本号
    uint8_t v_FAN_1_HW_MajorVersB = 0;  //硬件主版本号B
    uint8_t v_FAN_1_HW_MinorVersB = 0;  //硬件次版本号B
    uint8_t v_FAN_1_SN_MajorVersB = 0;  //主序号B
    uint8_t v_FAN_1_SN_MinorVersB = 0;  //次序号B
    uint8_t v_FAN_1_SN_SupplierCod = 0; //供应商代码

};

extern MBlower* m_Blower;

#endif // MBLOWER_H
