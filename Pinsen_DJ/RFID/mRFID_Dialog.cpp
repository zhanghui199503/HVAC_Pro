#include "mRFID_Dialog.h"
#include "ui_mRFID_Dialog.h"

MCOMRFID *m_COMRFID;
mRFID_Dialog *m_RFID_Dialog;
mS_RFID m_S_RFID_Pars;

static QStringList mColorName = {
    "background-color: rgb(200,200,200);",
    "background-color: red;",
    "background-color: rgb(0,255,0);",
    "background-color: yellow;",
    "background-color: white;",
};

enum m_color{
    Gray,
    Red,
    Green,
    Yellow,
    White,
};

//  ************************************************************************************************    //
//  **************************************  COM_BSM  ********************************************    //
//  ************************************************************************************************    //

static QStringList GetUarts()//获取串口资源
{
    //获取当前计算机所有串口设备
    QList<QSerialPortInfo> coms = QSerialPortInfo::availablePorts();
    QStringList list_ports;
    list_ports.append("");
    for(int i=0; i<coms.size(); i++){
        list_ports.append(coms[i].portName());
    }
    return list_ports;
}

quint8 CRC_SUM(const QByteArray &data)//CRC校验
{
    char checksum;
    char i;
    checksum = 0;
    for(i=0; i<data[1] - 1; i++){
        checksum ^= data[i];
    }
    return ~checksum;
}

//******************************************************************** RFID 读写类
MCOMRFID::MCOMRFID(QObject *parent) : QObject(parent)
{
    ptimer = new QTimer;
    ptimer->setSingleShot(true);
    connect(ptimer, &QTimer::timeout, this, &MCOMRFID::ReadFinish);


}

void MCOMRFID::Init_port()
{
    if(!B_open){
        COM_1 = new QSerialPort(this);
        COM_1->setPortName(m_S_RFID_Pars.Port);
        COM_1->setBaudRate(m_S_RFID_Pars.Baud.toUInt());
        COM_1->setDataBits(QSerialPort::Data8);
        COM_1->setStopBits(QSerialPort::OneStop);
        COM_1->setParity(QSerialPort::NoParity);
        if(!COM_1->open(QIODevice::ReadWrite)){
            qDebug() << "RFID 打开串口失败" << m_S_RFID_Pars.Port << m_S_RFID_Pars.Baud;
          m_RFID_Dialog->slot_Tips("RFID 打开串口失败");
            return;
        }
        qDebug() << "RFID 打开串口成功";
        m_RFID_Dialog->slot_Tips("RFID 打开串口成功");
        B_open = true;
        emit Sign_COMStyleSheet("RFID", true);
        connect(COM_1, &QSerialPort::readyRead, this, &MCOMRFID::SerialRead);
    }else{
        B_open = false;
        emit Sign_COMStyleSheet("RFID", false);
        COM_1->close();
        delete COM_1;
    }
}

void MCOMRFID::SerialRead()
{
    if(!ptimer->isActive()){
        ptimer->start(150);
    }
    QByteArray byte;
    byte = COM_1->readAll();
    byte_1.append(byte);
}

void MCOMRFID::ReadFinish()
{
    rec_read = byte_1;
    QByteArray aaa = rec_read.toHex().toUpper();
//    qDebug() << "RFID返回数据:" << aaa;
    emit sign_RFID_RecDatas(aaa);

    byte_1.clear();
}

void MCOMRFID::SendDatas(QByteArray byte)
{
    COM_1->write(byte);
}

void MCOMRFID::slot_Read_Card()//读取卡号
{

    QByteArray byte;
    byte.append(0x01);
    byte.append(0x08);
    byte.append(0xA1);
    byte.append(0x20);
    byte.append(int(0));
    byte.append(0x01);
    byte.append(int(0));
    quint8 a = CRC_SUM(byte);
    byte.append(a);
    SendDatas(byte);
}


void MCOMRFID::slot_Read_DB(QString db_num)//读数据块
{
    QByteArray byte;
    byte.append(0x01);
    byte.append(0x08);
    byte.append(0xA3);
    byte.append(0x20);
    byte.append(db_num.toInt());
    byte.append(int(0));//蜂鸣器声音
    byte.append(int(0));
    quint8 a = CRC_SUM(byte);
    byte.append(a);

    SendDatas(byte);
//    m_WorkTask->B_Read_RFID_DBs[db_num.toUShort()] = 2;
}

void MCOMRFID::slot_Write_DB(QString db_num, QString rfid)//处理发送RFID
{
    B_RFID_Write_OK = false;
    QByteArray byte;
    byte.append(0x01);
    byte.append(0x17);
    byte.append(0xA4);
    byte.append(0x20);
    byte.append(db_num.toInt());
    byte.append(0x01);

    int count = 32 - rfid.size();
    for(int i=0; i<count; i++){
        rfid.append('0');
    }
    bool ok;
    for(int i=0; i<rfid.size(); i+=2){
        byte.append((char)rfid.mid(i, 2).toInt(&ok, 16));
    }
    quint8 a = CRC_SUM(byte);
    byte.append(a);
    SendDatas(byte);
}

/***********************************************************************************
 ******************************** RFID界面 *****************************************
 ***********************************************************************************/

mRFID_Dialog::mRFID_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mRFID_Dialog)
{
    ui->setupUi(this);

    ui->GB_Debug->setVisible(false);

    ui->Cbt_Com_RFID->addItems(GetUarts());

    QString regexString = "[0-9A-F]+$"; // 正则表达式，匹配1-9或a-f的字符序列
    QRegExp regex(regexString);
    QRegExpValidator *validator = new QRegExpValidator(regex, ui->Write_DB);
    ui->Write_DB->setValidator(validator);
    load_File_INI();

    m_COMRFID = new MCOMRFID(this);
    connect(this, &mRFID_Dialog::sign_Write_DB, m_COMRFID, &MCOMRFID::slot_Write_DB);
    connect(this, &mRFID_Dialog::sign_Read_DB, m_COMRFID, &MCOMRFID::slot_Read_DB);
    connect(this, &mRFID_Dialog::sign_Read_Card, m_COMRFID, &MCOMRFID::slot_Read_Card);
    connect(m_COMRFID, &MCOMRFID::sign_RFID_RecDatas, this, &mRFID_Dialog::slot_Deal_RFID_RecDatas);
}

mRFID_Dialog::~mRFID_Dialog()
{
    delete ui;
}

void mRFID_Dialog::slot_Deal_RFID_RecDatas(QByteArray byte)//RFID读取
{

    slot_Tips(tr("接收 | 数据[%1]").arg(QString(byte)));
    if(byte.mid(4, 2) == "A1"){//读卡号命令，无需验证密钥
        if(byte.mid(8, 2) == "01"){
            qDebug() << "读取卡号命令失败";
        }else{

        }
        ui->RFID_Kind->setText(byte.mid(10, 4));
        ui->RFID_Number->setText(byte.mid(14, 8));

    }else if(byte.mid(4, 2) == "A3" || byte.mid(4, 2) == "03"){//读指定数据块命令，验证 KEYA，一次读取一个数据块，一个数据块长度为 16 字节
        if(byte.mid(8, 2) == "01"){
            m_COMRFID->B_RFID_Read_OK = false;
            slot_Tips("[A3]读取RFID失败");
//            m_S_RFID_Pars.Channel = "";
            m_S_RFID_Pars.serial_number = "";
        }else{
            m_COMRFID->B_RFID_Read_OK = true;

            QString data_valid = byte.mid(10, byte.size() - 2); //32字符
            QString work_code = data_valid.mid(0, 1);//工作代号 （正常工作、返修模式）
            QString channel = QString::number(data_valid.mid(1, 2).toUShort());//获取频道号
            m_S_RFID_Pars.Channel = channel;
            m_S_RFID_Pars.serial_number = data_valid.mid(3, 13);
//            CurWorkPar.rfid_number = data_valid.mid(3, 12);
//            MainWindow::mutualUi->ui->SerialNumber->setText(CurWorkPar.rfid_number);

            if(m_S_RFID_Pars.uc_RFID_Funtion == 0){
//                m_Form_SwitchChannel->RecInfo(channel, "");
            }
//            if(work_code == "E" && m_S_RFID_Pars.uc_RFID_Funtion == 0){
//                //返修模式
//                CurRepair.rfid_number = CurWorkPar.rfid_number;
//                CurRepair.B_REPAIR_EN = true;
//                CurRepair.B_Repair_Product = true;
//                m_DialogRepair->slot_show(true);
//            }
//            emit m_Form_SwitchChannel->sign_load_Channel_Pars(CurSystemConf.Line_Kind, CurSystemConf.station, channel);
        }
        ui->Read_DB->setText(byte.mid(10, byte.count() - 12));
    }else if(byte.mid(4, 2) == "A4"){//写指定数据块命令，验证 KEYA，一次写入一个数据块，一个数据块长度为 16 字节
        if(byte.mid(8, 2) == "01"){
            m_COMRFID->B_RFID_Write_OK = false;
            slot_Tips("[A4]写入RFID失败");
        }else{
//            slot_Tips(tr("[A4]写入RFID[%1]成功").arg(m_Struct_PublicVar.PreWrite_RFID));
//            m_COMRFID->B_RFID_Write_OK = true;
//            CurWorkPar.rfid_number = m_Struct_PublicVar.PreSerialNumber;
//            Write_Product_Primary_Key();
//            if(CurRepair.B_REPAIR_EN){
////                CurRepair.rfid_number = m_Struct_PublicVar.PreSerialNumber;
//                m_DialogRepair->slot_show(true);
//            }
        }
    }
}

void mRFID_Dialog::on_Btn_ReadCard_clicked()//读取卡号
{
    emit sign_Read_Card();
}

void mRFID_Dialog::on_Btn_Read_DB_clicked()//读数据块
{
    emit sign_Read_DB(ui->Cbt_Read_DB->currentText());
}

void mRFID_Dialog::on_Btn_Write_DB_clicked()//写数据
{
    emit sign_Write_DB(ui->Cbt_Write_DB->currentText(), ui->Write_DB->text());
}

void mRFID_Dialog::slot_Tips(const QString mesg)//记录信息
{
    ui->textBrowser->append(QTime::currentTime().toString() + " >> " + mesg);
}

void mRFID_Dialog::load_File_INI()
{
    QString path = QApplication::applicationDirPath() + "/System/System.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    ui->Cbt_Com_RFID->setCurrentText(INI_File->value("RFID/Port").toString());
    ui->Cbt_Baud_RFID->setCurrentText(INI_File->value("RFID/Baud").toString());
    ui->Cbt_RFID_Funtion->setCurrentIndex(INI_File->value("RFID/uc_RFID_Funtion").toUInt());

    m_S_RFID_Pars.Port = ui->Cbt_Com_RFID->currentText();
    m_S_RFID_Pars.Baud = ui->Cbt_Baud_RFID->currentText();
    m_S_RFID_Pars.uc_RFID_Funtion = ui->Cbt_RFID_Funtion->currentIndex();

    INI_File->destroyed();

    slot_Tips("参数加载成功");
}

void mRFID_Dialog::on_Btn_Save_clicked()//保存参数
{
    QString path = QApplication::applicationDirPath() + "/System/System.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    m_S_RFID_Pars.Port = ui->Cbt_Com_RFID->currentText();
    m_S_RFID_Pars.Baud = ui->Cbt_Baud_RFID->currentText();
    m_S_RFID_Pars.uc_RFID_Funtion = ui->Cbt_RFID_Funtion->currentIndex();

    INI_File->setValue("RFID/Port", ui->Cbt_Com_RFID->currentText());
    INI_File->setValue("RFID/Baud", ui->Cbt_Baud_RFID->currentText());
    INI_File->setValue("RFID/uc_RFID_Funtion", ui->Cbt_RFID_Funtion->currentIndex());

    INI_File->destroyed();

    slot_Tips("保存参数成功");

}

void mRFID_Dialog::on_Btn_UpdateUarts_clicked()//刷新串口
{
    if(ui->Cbt_Com_RFID->isEnabled()){
        ui->Cbt_Com_RFID->clear();
        ui->Cbt_Com_RFID->addItems(GetUarts());
    }
}

void mRFID_Dialog::on_Btn_RFID_clicked()
{
    m_S_RFID_Pars.Port = ui->Cbt_Com_RFID->currentText();
    m_S_RFID_Pars.Baud = ui->Cbt_Baud_RFID->currentText();
//    emit sign_OpenCOMRFID();
    m_COMRFID->Init_port();
}

void mRFID_Dialog::Slot_COMStyleSheet(const QString &name, bool b_value)
{
    if(name == "RFID"){
        if(b_value){
            slot_setled_cicular(ui->led_RFID_State, m_color::Green);
        }else{
            slot_setled_cicular(ui->led_RFID_State, m_color::Red);
        }
        ui->Cbt_Com_RFID->setEnabled(!b_value);
        ui->Cbt_Baud_RFID->setEnabled(!b_value);
    }
}

void mRFID_Dialog::slot_setled_cicular(QLabel *label, const int color)
{
    QString sheet = mColorName.at(color);
    sheet += QString("border-radius: %1px;").arg(label->width() / 2);
    sheet += "border: 1px solid black;";
    label->setStyleSheet(sheet);
}
void mRFID_Dialog::on_Btn_Debug_clicked(bool checked)
{
    m_S_RFID_Pars.B_DEBUG_Mode = checked;
    if(checked){
        ui->Btn_Debug->setText("调试模式");
        ui->GB_Debug->setVisible(true);
    }else{
        ui->Btn_Debug->setText("工作模式");
        ui->GB_Debug->setVisible(false);
    }
}
