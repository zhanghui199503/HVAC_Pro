#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Header_File.h"
#include <QMainWindow>
#include <QThread>
#include <QMap>
#include "serialportworker.h"
#include "thread_ptmotor.h"
#include "motor_types.h"
#include "MFormMotor.h"

#include "FormLogShow.h"

#define FUNC_PT_ID      1
#define FUNC_LIN_ID     2
#define FUNC_BLO_ID     3
#define FUNC_THE_ID     4
#define FUNC_ANION_ID   5
#define FUNC_AQS_ID     6
#define RUNC_PM25_ID    7
#define RUNC_PTC_ID     8


class thread_ptmotor;
//struct PTMotorFP_Setting_basis
//{
//    int m_id;                    //id号
//    bool m_motorEnabled;         // 电机使能状态 (Motor_X_Enable)
//    int m_motorNumber;           // 电机号 (1-2)
//    QString m_name;              // 电机名称
//    int m_motorType;             // 电机类型 (根据 PT_Mode_flag 和 PT_Line2_flag 判断)
//    bool m_motorDirection;       // 电机方向 (Motor_X_PT_Direction_flag)
//    int m_towmotortype;          // 两线类型
//    int m_currentUpperLimit;     // 电流上限(毫安)
//    int m_currentLowerLimit;     // 电流下限(毫安)
//    int m_stallCurrent;          // 堵转电流(毫安)
//    int m_startDelayMs;          // 启动延时时间(毫秒)
//    int m_alarmDelayMs;          // 报警延时时间(毫秒)
//    int m_timeoutMs;             // 超时时间(秒) (Motor_X_Run_MaxTime)
//    double m_line2MotorRunTime;  // 2线电机运行时间
//    int m_voltageAvgCount;       // 默认电压平均次数
//    int m_currentAvgCount;       // 默认电流平均次数
//};
//QList<PTMotorFP_Setting_basis> PTmotorSettingsList;
//struct PTMotorFP_Setting_basis1
//{
//    QString m_PTName;            //PT名字
//    QString m_POS;               //POS顺序
//    QString m_MaxValue;          //上限
//    QString m_MinValue;          //下限
//    QString m_Time;              //跳转
//};
//QList<PTMotorFP_Setting_basis1> PTmotorSettingsList1;

////-----------------------LIN电机------------------------
//struct LINMotorFP_Setting_basis
//{
//    int m_id;                    //id号
//    bool m_motorEnabled;         //电机使能状态
//    bool m_motorerrEnabled;      //步数误差使能状态
//    bool m_motorInitEnabled;     //初始化使能
//    QString m_name;              //电机名称
//    int m_motorRunSpeed;         //电机运行速度
//    int m_motorMaxtimer;         //电机运行最大时间
//    bool m_motorInitDirection;   //电机初始化方向
//    int m_motorStepErrValue;     //步数误差值
//    QString m_motorNAD;          //电机NAD
//    QString m_motorControlid;    //电机控制ID
//    QString m_motorStateid;      //电机状态ID
//    int m_motorOther;            //电机旋转方向，应急运行位置,应急运行释放
//    int m_motorInitValue;        //初始化使能位置
//};
//QList<LINMotorFP_Setting_basis> LINmotorSettingsList;
//struct LINMotorFP_Setting_basis1
//{
//    QString m_LINName;           //LIN名字
//    QString m_POS;               //POS顺序
//    //    QString m_Type;              //类型
//    QString m_Value;             //值
//    QString m_Time;              //跳转
//};
//QList<LINMotorFP_Setting_basis1> LINmotorSettingsList1;

//struct Blower_Setting_basis
//{
//    int m_Blowerid;                //id号
//    bool m_BlowerEnabled;          //鼓风机使能状态
//    int m_BlowerMode;              //鼓风机类型
//    QString m_BlowerStartDelay;     //鼓风机名称
//    int m_BlowerPowervoltageUP;    //鼓风机电源电压上限
//    int m_BlowerPowervoltageDown;  //鼓风机电源电压下限
//    //    QString m_BlowerStep;          //鼓风机运行顺序
//    QString m_BlowerRate;          //鼓风机频率
//    QString m_LINBlowerControlid;  //控制ID
//    QString m_LINBlowerStateid;    //状态ID
//    QString m_LINBlowerSendid;     //发送ID
//    QString m_LINBlowerReadid;     //读取ID
//    bool m_LINBlowerSpeed_Compare;  //转速比对使能
//    int m_LINBlowerErrorValue;     //转速比对误差值
//    bool m_X_vibration_Enable;          //X轴震动使能状态
//    bool m_Y_vibration_Enable;          //Y轴震动使能状态
//    bool m_Z_vibration_Enable;          //Z轴震动使能状态
//    bool m_Noises_Enable;          //噪音使能状态
//    double m_vibration_StartDelay; //启动延时
//    double m_vibration_DelayAlarm; //震动报警延时
//    double m_Noises_StartDelay; //噪音启动延时
//    double m_Noises_DelayAlarm; //噪音震动报警延时

//};
//QList<Blower_Setting_basis> BlowerSettingsList;

//struct Blower_Setting_basis1
//{
//    QString m_POS;   //POS顺序
//    QString m_Type;  //类型
//    QString m_Value; //端电压，占空比，转速
//    QString m_Time;  //运行时间
//    QString m_BlowerMaxValue;  //上限
//    QString m_BlowerMinValue;  //下限
//    QString m_X_vibrationrMaxValue;  //上限
//    QString m_X_vibrationrMinValue;  //下限
//    QString m_Y_vibrationMaxValue;  //上限
//    QString m_Y_vibrationMinValue;  //下限
//    QString m_Z_vibrationMaxValue;  //上限
//    QString m_Z_vibrationMinValue;  //下限
//    QString m_NoisesMaxValue;  //上限
//    QString m_NoisesMinValue;  //下限
//};
//QList<Blower_Setting_basis1> BlowerSettingsList1;


//struct Res_Setting_basis
//{
//    QString m_POS;   //POS顺序
//    QString m_Type;  //类型
//    QString m_Value; //端电压，占空比，转速
//    QString m_Time;  //运行时间
//    QString m_BlowerMaxValue;  //上限
//    QString m_BlowerMinValue;  //下限
//    QString m_X_vibrationrMaxValue;  //上限
//    QString m_X_vibrationrMinValue;  //下限
//    QString m_Y_vibrationMaxValue;  //上限
//    QString m_Y_vibrationMinValue;  //下限
//    QString m_Z_vibrationMaxValue;  //上限
//    QString m_Z_vibrationMinValue;  //下限
//    QString m_NoisesMaxValue;  //上限
//    QString m_NoisesMinValue;  //下限
//};
//QList<Res_Setting_basis> ResSettingsList;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT




public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow *mutualui;

    Ui::MainWindow *ui;

    QList<int> getOpenedSerialPorts() const;// 获取当前打开的串口列表
    bool isSerialPortOpened(int portIndex) const;// 检查特定串口是否打开

    QTimer *DayTimer;
    QTimer *pressTimer;
    QTimer *CommunicationTimer;

    QTimer *ShowUI_DataTimer;//显示界面数据定时器

    int InitialValue = 0;//初始值Excel行数
    QSqlDatabase Sqlserverdb;//创建数据库
    int Pop_OK_flag = 0;//弹窗标志位
    int Pop_NG_flag = 0;//弹窗标志位
    int Pop_Alarm_flag = 0;//弹窗标志位
    int NewPD_Flag = 0;//频道载入
    int ReadChannel_flag = 0;//读取频道标志位

    int  INplace_flag = 0;//到位标志
    int  INplace_oldflag = 0;//到位标志位
    int Channel_Flag = 0;

    int CommunicationHeartbeat=0;//通讯标志
    int adminman = 0;//0操作1管理

    // 使用映射表管理多个串口
    QMap<int, SerialPortWorker*> m_workers;
    QMap<int, QThread*> m_threads;
    QMap<int, bool> m_serialOpened;

    bool Start_Process = false;
public slots:
    void sendDataToSerial(int portIndex, const QByteArray &data);// 发送数据到指定串口
    void closeSerialPort(int portIndex);// 关闭指定串口

    void Class_Init();//初始化
    void Connect_Init();//槽函数初始化
    void Update_show();//界面刷新
    void Main_Init();//界面初始化
    void Excelinit();//excel初始化
    void Save_Excel();//保存参数
    void Save_MySql();//保存数据库
    void Update_Number();//更新数量
    void testsqlinit();
    QString createMultipleFolders(const QString path);//创建多级文件夹
    QString Button_background_color(int result);
    void Data_Processing();//数据处理
    void MySql_Init();//连接主控追溯初始化
    void Thread_Qtimer(int index);//控制线程是否启动定时
    void slot_Get_uplineCode(const QString rfid);//获取工位历史数据
    void Slots_MySql_exec(QString  str);//  存入数据库
    void Data_InPlaceTime();// 到位时间记录
    void Alarm_MessageData();// 报错信息数据

    void Slot_MySql_JDL_writeOK(int PD,QString index);
    void Slot_MySql_JDL_writeALL(int Result,int PD,QString index);
    void on_Auto_PDbox_currentTextChanged(const QString &arg1);

    void onButtonPressed();
    void onButtonReleased();
    void onLongPress();
    void CommunicationTimes();//通讯心跳检测
    void show_Err();


    void setVoltageToolTip(int index,QWidget* widget,const QString& positionV, const QString& positionA,const QString& upperLimit, const QString& lowerLimit);


    void Process_Initiation();
private slots:
    void on_actionPLC_triggered();//PLC通讯界面
    void UpdateTime();//更新主界面时间

    void on_actionSetPD_triggered();

    void on_actionHandMain_triggered();

    void on_actionAbout_Software_triggered();

    void on_actionContact_Us_triggered();

    void on_Auto_Blower_clicked();



    void on_Auto_Start_clicked();

    void on_Auto_Reset_clicked();

    void on_Auto_ManualNG_clicked();

    void on_pushButton_6_clicked();

    void on_actionRfid_triggered();

    void on_actionPD_Data_triggered();

    void on_LIN_IDWrite_clicked();

    void on_LIN1_IDRead_clicked();

    void on_LIN2_IDRead_clicked();

    void on_Goback_clicked();

    void on_actionSysSet_triggered();

    // 串口对话框的信号处理
    void onSerialConnectRequested(const QString &portName, qint32 baudRate,QSerialPort::DataBits dataBits,QSerialPort::Parity parity,QSerialPort::StopBits stopBits);
    void onDataReceived(const QByteArray &data, int portIndex);
    void onErrorOccurred(const QString &errorString, int portIndex);
    void onSerialOpened(bool success, int portIndex);
    void onSerialClosed(int portIndex);
    void on_actiontest_triggered();

    void on_Btn_test1_clicked();

    void on_actionMain_triggered();

    void on_Btn_test2_clicked();

    void Slot_ShowUI_Data();
    void showFuncUIData(uchar _num);

private:


    int m_nextPortIndex=0; // 下一个可用的端口索引
    // 创建串口连接
    void createSerialConnection(const QString &portName, qint32 baudRate,QSerialPort::DataBits dataBits,QSerialPort::Parity parity,QSerialPort::StopBits stopBits);
    // 关闭指定串口
    void closeSerialConnection(int portIndex);


    //------------PT电机线程-------------
    QThread *workerThread;
    thread_ptmotor *PTworker;

protected:
    void closeEvent(QCloseEvent *event);
signals:
    void Sign_Start_detection(QString unit, int address,int value);//发送启动检测
    void Sign_Multiblock_detection(int BlockNum,QVector<QStringList> index);//发送多地址检测
    void Sign_Start_detectionPoint(QString unit, int address,int value);//发送检测点位
    void Sign_Goback();//发送检测点位
    void serialPortStatusChanged(int portIndex, bool isOpened);// 可以添加更多管理信号

    void testRunMotor(QString index);

};
extern int reszult ;//记录追溯结果
extern MainWindow *MainShow;


extern QList<PTMotorFP_Setting_basis> PTmotorSettingsList;
extern QList<PTMotorFP_Setting_basis1> PTmotorSettingsList1;
extern QList<LINMotorFP_Setting_basis> LINmotorSettingsList;
extern QList<LINMotorFP_Setting_basis1> LINmotorSettingsList1;
extern QList<Blower_Setting_basis> BlowerSettingsList;
extern QList<Blower_Setting_basis1> BlowerSettingsList1;
extern QList<Res_Setting_basis> ResSettingsList;

#endif // MAINWINDOW_H
