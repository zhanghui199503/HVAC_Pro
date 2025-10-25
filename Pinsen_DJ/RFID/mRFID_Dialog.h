#ifndef MRFID_DIALOG_H
#define MRFID_DIALOG_H

#include <QDialog>
//#include "mHeadFile.h"
#include <QLabel>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QSettings>
#include <QTextCodec>
#include <QTime>

namespace Ui {
class mRFID_Dialog;
}

class mRFID_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit mRFID_Dialog(QWidget *parent = nullptr);
    ~mRFID_Dialog();

    Ui::mRFID_Dialog *ui;

    void load_File_INI();

public slots:
    void slot_Tips(const QString mesg);
    void slot_Deal_RFID_RecDatas(QByteArray byte);
    void Slot_COMStyleSheet(const QString &name, bool b_value);
    void slot_setled_cicular(QLabel *label, const int color);


private slots:
    void on_Btn_ReadCard_clicked();
    void on_Btn_Read_DB_clicked();
    void on_Btn_Write_DB_clicked();
    void on_Btn_Save_clicked();
    void on_Btn_UpdateUarts_clicked();
    void on_Btn_RFID_clicked();
    void on_Btn_Debug_clicked(bool checked);

private:


signals:
    void sign_Write_DB(QString db_num, QString rfid);//写数据块
    void sign_Read_DB(QString db_num);//读数据块
    void sign_Read_Card();//读卡号
    void sign_OpenCOMRFID();//打开串口
    void sign_SwitchChannel(QString channel);


};

//RFID
//比速迪扭力串口采集
class MCOMRFID : public QObject
{
    Q_OBJECT
public:
    explicit MCOMRFID(QObject *parent = nullptr);

    QTimer *ptimer;
    bool B_RFID_Read_OK = false;
    bool B_RFID_Write_OK = false;

    bool b_DATAX = false;
    bool b_CMDX = false;
    bool b_CMD_ANS_151_OK = false;

    bool b_DATA100 = false;
    bool b_DATA101 = false;
    QString lock_count = "";
    QString Dp_add_sub = "";
    QString Dp_add_sub_Code = "";

    bool b_add = false;
    bool b_sub = false;
    QStringList DATAXS = {"", ""};
    QStringList CMDXS = {"", ""};

public slots:
    void Init_port();
    void SerialRead();
    void ReadFinish();
    void SendDatas(QByteArray byte);
    void slot_Write_DB(QString db_num, QString rfid);//写数据块
    void slot_Read_DB(QString db_num);//读数据块
    void slot_Read_Card();//读取卡号


signals:
    void Sign_TipsN(const int arg1, const QString &mes);
    void Sign_COMStyleSheet(const QString &name, bool b_value);
    void sign_DisplayBSD_Torque(QString torque_value, QString torque_unit);
    void sign_RFID_RecDatas(QByteArray byte);

private:
//    QMutex *mutex = new QMutex;
    bool B_open = false;
    QSerialPort *COM_1;
    QByteArray byte_1, rec_read;
    bool heart = false;

};

struct mS_RFID{
  QString Port;
  QString Baud;
  uchar uc_RFID_Funtion = 0;//0:RD 1:WR
  bool B_DEBUG_Mode = false;
  QString serial_number;
  QString Channel;
};
extern mS_RFID m_S_RFID_Pars;

extern MCOMRFID *m_COMRFID;
extern mRFID_Dialog *m_RFID_Dialog;
extern quint8 CRC_SUM(const QByteArray &data);

#endif // MRFID_DIALOG_H
