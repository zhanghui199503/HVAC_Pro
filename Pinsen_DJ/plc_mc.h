#ifndef PLC_MC_H
#define PLC_MC_H

#include <QWidget>
#include "Header_File.h"
//#include <QTcpSocket>

//constexpr int MAX_RETRY = 3;    // 最大重试次数

namespace Ui {
class PLC_MC;
}

class PLC_MC : public QWidget
{
    Q_OBJECT

public:
    explicit PLC_MC(QWidget *parent = nullptr);
    ~PLC_MC();
    Ui::PLC_MC *ui;
    QTcpSocket *m_tcpSocket;

    QTimer *testTimer;
    QTimer *ReadSetDataTimer;
    QTimer *ManualTimer;

    QTimer *ReadInPlaceTimer;

    int connectionRetryCount = 0;

//    int checkflag = 0;//访问标志位
public slots:
    void PLC_Init();//PLC初始化
    void onReadMessage();//PLC读取
    void GetReadCommandD(QString Path,int startIndex,int len);//单块D单元批量读取
    void SetWriteCommand(QString unit, int address,int value);//单元 地址 值

    void GetReadMultiblock(int BlockNum,QVector<QString> index,QVector<int> index1,QVector<int> index2);
    void GetReadMultiblockBit(int BlockNum,int BitNum,QVector<QString> index,QVector<int> index1,QVector<int> index2);
    void GetSettingdata();//获取设置界面参数
    void GetManualdata();//获取手动界面参数
    void Stop_ReadPLC();//读模式暂停
    void Start_ReadPLC();//读模式启动

    void SetWriteCommandPoint(QString unit, int address,int value);//单元 地址 值


    void GetInPlaceData();//读取到位信号
    void onSocketError(QAbstractSocket::SocketError socketError);// 错误处理

//    void onSocketError(QAbstractSocket::SocketError socketError);
        void connectToPLC();                             // 连接PLC
        void disconnectPLC();                            // 断开PLC连接
        void reconnectPLC();                             // 重新连接PLC

private slots:
    void on_PLC_Connet_clicked();

    void on_MC_Read_clicked();

    void on_SavePLCIP_Port_clicked();



private:

signals:
    void test();
    void SendZSdata();//发送追溯信号
    void SendSetLinData();//发送设置界面信号
    void SendManualData();//发送手动界面
    void InPlaceTime();//到位时间
    void Heraterr();//心跳报警

     void connectionFailed();        // 连接失败信号
};
extern PLC_MC *PLC_Connet;
extern int AutoDataValue[4000];
extern int ZSDataValue[4000] ;//存追溯数据
extern int SetDataValue[2000];//存设置界面参数数据
extern int SetData1Value[2000];//存设置界面参数数据
extern int SetData2Value[2000];//存设置界面参数数据
extern int GetManualValue[2000];//存设置界面参数数据
extern int GetInPlaceValue[20];//获取到位信号
extern int checkflag ;//访问标志位
#endif // PLC_MC_H
