#include "plc_mc.h"
#include "ui_plc_mc.h"
// 常量定义
namespace {
    constexpr int HEADER_SIZE = 22; // 头部长度
    constexpr int WORD_SIZE = 4;    // 每个字占4个十六进制字符
    constexpr int MAX_RETRY = 3;    // 最大重试次数
    constexpr int AUTO_DATA_SIZE = 4000;
    constexpr int ZS_DATA_SIZE = 4000;
    constexpr int SET_DATA_SIZE = 2000;
    constexpr int IN_PLACE_SIZE = 20;
}

PLC_MC *PLC_Connet;
int AutoDataValue[4000] = {0};//存PLC的数据
int ZSDataValue[4000] = {0};//存追溯数据
int SetDataValue[2000] = {0};//存设置界面参数数据
int SetData1Value[2000]= {0};//存设置界面参数数据
int SetData2Value[2000]= {0};//存设置界面参数数据
int GetManualValue[2000]= {0};//获取手动界面
int GetInPlaceValue[20];//获取到位信号

//QVector<int> AutoDataValue(AUTO_DATA_SIZE, 0); // 存PLC的数据
//QVector<int> ZSDataValue(ZS_DATA_SIZE, 0);     // 存追溯数据
//QVector<int> SetDataValue(SET_DATA_SIZE, 0);   // 存设置界面参数数据
//QVector<int> SetData1Value(SET_DATA_SIZE, 0);  // 存设置界面参数数据
//QVector<int> SetData2Value(SET_DATA_SIZE, 0);  // 存设置界面参数数据
//QVector<int> GetManualValue(SET_DATA_SIZE, 0); // 获取手动界面
//QVector<int> GetInPlaceValue(IN_PLACE_SIZE, 0); // 获取到位信号
int checkflag = 0;//访问标志位
PLC_MC::PLC_MC(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PLC_MC)
{
    ui->setupUi(this);
    PLC_Init();
    testTimer = new QTimer(this);
    ReadSetDataTimer = new QTimer(this);
    ManualTimer = new QTimer(this);
    ReadInPlaceTimer = new QTimer(this);
    //    connect(testTimer,SIGNAL(timeout()),this,SLOT(on_MC_Read_clicked()));
    //    connect(ReadSetDataTimer,SIGNAL(timeout()),this,SLOT(GetSettingdata()));
    //    connect(ManualTimer,SIGNAL(timeout()),this,SLOT(GetManualdata()));
    //    connect(ReadInPlaceTimer,SIGNAL(timeout()),this,SLOT(GetInPlaceData()));
    connect(testTimer, &QTimer::timeout, this, &PLC_MC::on_MC_Read_clicked);
    connect(ReadSetDataTimer, &QTimer::timeout, this, &PLC_MC::GetSettingdata);
    connect(ManualTimer, &QTimer::timeout, this, &PLC_MC::GetManualdata);
    connect(ReadInPlaceTimer, &QTimer::timeout, this, &PLC_MC::GetInPlaceData);


    GetManualdata();

    ui->PLC_Connet->click();
    ReadInPlaceTimer->start(1000);

}

PLC_MC::~PLC_MC()
{
    delete ui;
}

void PLC_MC::GetInPlaceData()
{
    GetReadCommandD("M",4020,5);
    //    QVector<QString> index;
    //    QVector<int> index1;
    //    QVector<int> index2;
    //    index.append("M");
    //    index.append("M");
    //    index1.append(4020);
    //    index1.append(4601);
    //    index2.append(5);
    //    index2.append(1);

    //    GetReadMultiblock(2, index,index1,index2);
}
void PLC_MC::on_PLC_Connet_clicked()
{
//    if(ui->PLC_Connet->text()=="开始连接")
//    {
//        if(m_tcpSocket->state()==QAbstractSocket::ConnectedState){
//            //如果使用disconnectFromHost()不会重置套接字，isValid还是会为true
//            m_tcpSocket->abort();
//            qDebug()<<"PLC_MC连接成功";
//        }else if(m_tcpSocket->state()==QAbstractSocket::UnconnectedState){
//            //从界面上读取ip和端口
//            const QHostAddress address = QHostAddress(ui->PLC_IP->text());
//            const unsigned short port=ui->PLC_Port->value();
//            //连接服务器
//            m_tcpSocket->connectToHost(address,port);
//            if(m_tcpSocket->waitForConnected(500)){
//                qDebug()<<"PLC_MC连接成功";

//                ui->PLC_Connet->setText("断开连接");
//                testTimer->start(100);
//            }else{
//                qDebug()<<"PLC_MC连接失败";
//                emit  Heraterr();
//            }
//        }
//    }
//    else
//    {
//        if(m_tcpSocket->state()==QAbstractSocket::ConnectedState)
//        {
//            m_tcpSocket->disconnectFromHost();
//            ui->PLC_Connet->setText("开始连接");

//        }

//    }

    if (ui->PLC_Connet->text() == "开始连接") {
            connectToPLC();
        } else {
            disconnectPLC();
        }
}
void PLC_MC::Start_ReadPLC()
{
    ReadSetDataTimer->start(200);
}

void PLC_MC::Stop_ReadPLC()
{
    ReadSetDataTimer->stop();
}
void PLC_MC::PLC_Init()
{
    //创建client对象
    m_tcpSocket = new QTcpSocket(this);
    connect(m_tcpSocket,&QTcpSocket::connected,this, [this]() {
        //已连接就设置为不可编辑
        //        ui->pushButton_3->setText("Disconnect");
        ui->PLC_IP->setEnabled(false);
        ui->PLC_Port->setEnabled(false);
    });
    connect(m_tcpSocket,&QTcpSocket::disconnected,this, [this]() {
        //断开连接还原状态
        //        ui->pushButton_3->setText("Connect");
        ui->PLC_IP->setEnabled(true);
        ui->PLC_Port->setEnabled(true);
    });
    connect(m_tcpSocket,&QTcpSocket::readyRead,this,&PLC_MC::onReadMessage);
    connect(m_tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
            this, &PLC_MC::onSocketError);
//    connect(m_tcpSocket,SIGNAL(&QAbstractSocket::SocketError),this,SLOT(onDisplayError(QAbstractSocket::SocketError)));


    QString path = QApplication::applicationDirPath() + "/System/PLC_MC.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    ui->PLC_IP->setText(INI_File->value("PLC_IP").toString());
    ui->PLC_Port->setValue(INI_File->value("PLC_Port").toString().toInt());
    INI_File->destroyed();
}


void PLC_MC::onSocketError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Socket错误：" << m_tcpSocket->errorString();
    // 可以根据不同的错误类型处理
    emit Heraterr();
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            qInfo() << "PLC主动断开连接";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            qWarning() << "连接被拒绝，检查PLC IP和端口";
            break;
        case QAbstractSocket::NetworkError:
            qWarning() << "网络错误，检查网络连接";
            break;
        default:
            qWarning() << "未知套接字错误";
        }

        // 启动重连
        if (ui->PLC_Connet->text() == "断开连接") {
            QTimer::singleShot(5000, this, &PLC_MC::reconnectPLC);
        }
}

void PLC_MC::reconnectPLC()
{
    if (++connectionRetryCount <= MAX_RETRY) {
        qInfo() << "尝试重新连接PLC，重试次数:" << connectionRetryCount;
        connectToPLC();
    } else {
        qWarning() << "PLC连接失败超过最大重试次数";
//        emit connectionFailed();
    }
}

void PLC_MC::connectToPLC()
{
    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState) {
        return;
    }

    const QHostAddress address = QHostAddress(ui->PLC_IP->text());
    const quint16 port = static_cast<quint16>(ui->PLC_Port->value());
    m_tcpSocket->connectToHost(address, port);

    if (m_tcpSocket->waitForConnected(1000)) {
        connectionRetryCount = 0; // 重置重试计数
        ui->PLC_Connet->setText("断开连接");
        testTimer->start(100);
    } else {
        qWarning() << "PLC连接失败:" << m_tcpSocket->errorString();
        reconnectPLC();
    }
}

//void PLC_MC::on_PLC_Connet_clicked()
//{
//    if (ui->PLC_Connet->text() == "开始连接") {
//        connectToPLC();
//    } else {
//        disconnectPLC();
//    }
//}

void PLC_MC::disconnectPLC()
{
    testTimer->stop();
    ReadSetDataTimer->stop();
    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState) {
        m_tcpSocket->disconnectFromHost();
    }
    ui->PLC_Connet->setText("开始连接222");
}



void PLC_MC::onReadMessage()
{
    //    qDebug()<<"进入读取";
    //例 发    50 00 00 FF FF 03 00 0C 00 10 00 01 04 00 00 10 27 00 A8 02 00
    //例 收正确 D0 00 00 FF FF 03 00 06 00 00 00  10 00  09 00
    //例 收错误 D0 00 00 FF FF 03 00 0B 00 5B C0  00FFFF030001040000
    bool ok;
    QByteArray bt,Readdata;
    bt.resize(m_tcpSocket->bytesAvailable());
    m_tcpSocket->read(bt.data(),bt.size());
    Readdata = bt.toHex().toUpper();
    //将客户端反馈的数据显示到标签上
    //        qDebug()<<bt.toHex().toUpper();
    if(Readdata.mid(20,2) == "C0")
    {
        //        ui->ReadData_Edit->append("数据有问题");
        qDebug()<<"PLC返回数据有问题";
    }
    else
    {
        if(Readdata.at(14) == '8'&&Readdata.at(15) == '2'&&Readdata.at(16) == '0'&&Readdata.at(17) == '7')//获取自动界面 960字
        {
            bt = Readdata.remove(0,22);
            int right, left;int s =0;
            for(int i =0;i<bt.length()/4;i++)
            {
                s = bt.mid(i*4,4).toInt(&ok,16);
                right = (s & 0XFF)<<8;//低八位
                left = (s & 0XFF00)>> 8;//高八位  右移8位
                AutoDataValue[i] = right + left;
                if(AutoDataValue[i]>32767)
                {
                    AutoDataValue[i] =  AutoDataValue[i] - 65536;
                }
            }
            emit test();
            if(AutoDataValue[7]== 0)
            {
                reszult =  0;
            }
            else if(AutoDataValue[7]==1||AutoDataValue[7]==2)
            {

                QVector<QString> index;
                QVector<int> index1;
                QVector<int> index2;
                index.append("ZR");
                index.append("ZR");
                index1.append(200000);
                index1.append(200580);
                index2.append(400);
                index2.append(500);
                GetReadMultiblock(2, index,index1,index2);

            }

            //           qDebug()<<  QString::number(AutoDataValue[i]);

        }
        else if(Readdata.at(14) == '0'&&Readdata.at(15) == 'A'&&Readdata.at(16) == '0'&&Readdata.at(17) == '7')//获取追溯 900字
        {
            //            Data_Set->ui->textEdit->append("有结果开始记录");
            bt = Readdata.remove(0,26);
            int right, left;int s =0;
            for(int i =0;i<bt.length()/4;i++)
            {
                s = bt.mid(i*4,4).toInt(&ok,16);
                right = (s & 0XFF)<<8;//低八位
                left = (s & 0XFF00)>> 8;//高八位  右移8位
                ZSDataValue[i] = right + left;
                if(ZSDataValue[i]>32767)
                {
                    ZSDataValue[i] =  ZSDataValue[i] - 65536;

                }
                //                Data_Set->ui->textEdit->append(QString::number(i)+":"+QString::number(ZSDataValue[i]));
            }
            //           qDebug()<<  QString::number(AutoDataValue[i]);
            emit SendZSdata();
        }
        else if(Readdata.at(14) == '8'&&Readdata.at(15) == '0'&&Readdata.at(16) == '0'&&Readdata.at(17) == '7')//获取设置界面LIN 959字
        {

            bt = Readdata.remove(0,22);
            int right, left;int s =0;
            for(int i =0;i<bt.length()/4;i++)
            {
                s = bt.mid(i*4,4).toInt(&ok,16);
                right = (s & 0XFF)<<8;//低八位
                left = (s & 0XFF00)>> 8;//高八位  右移8位
                SetDataValue[i] = right + left;
                if(SetDataValue[i]>32767)
                {
                    SetDataValue[i] =  SetDataValue[i] - 65536;

                }
                //                Data_Set->ui->textEdit->append(QString::number(i)+":"+QString::number(SetDataValue[i]));
            }
            //                       qDebug()<<  QString::number(AutoDataValue[i]);
            checkflag =1;
            emit SendSetLinData();
        }
        else if(Readdata.at(14) == '4'&&Readdata.at(15) == '2'&&Readdata.at(16) == '0'&&Readdata.at(17) == '7')//获取设置界面Motor1-16 928字
        {

            bt = Readdata.remove(0,22);
            int right, left;int s =0;
            for(int i =0;i<bt.length()/4;i++)
            {
                s = bt.mid(i*4,4).toInt(&ok,16);
                right = (s & 0XFF)<<8;//低八位
                left = (s & 0XFF00)>> 8;//高八位  右移8位
                SetData1Value[i] = right + left;
                if(SetData1Value[i]>32767)
                {
                    SetData1Value[i] =  SetData1Value[i] - 65536;

                }
                //                Data_Set->ui->textEdit->append(QString::number(i)+":"+QString::number(SetDataValue[i]));
            }
            //                       qDebug()<<  QString::number(AutoDataValue[i]);
            checkflag =2;
            emit SendSetLinData();
        }

        else if(Readdata.at(14) == '3'&&Readdata.at(15) == '2'&&Readdata.at(16) == '0'&&Readdata.at(17) == '7')//获取设置界面Motor17 18 920字
        {
            bt = Readdata.remove(0,22);
            int right, left;int s =0;
            for(int i =0;i<bt.length()/4;i++)
            {
                s = bt.mid(i*4,4).toInt(&ok,16);
                right = (s & 0XFF)<<8;//低八位
                left = (s & 0XFF00)>> 8;//高八位  右移8位
                SetData2Value[i] = right + left;
                if(SetData2Value[i]>32767)
                {
                    SetData2Value[i] =  SetData2Value[i] - 65536;

                }
                //                Data_Set->ui->textEdit->append(QString::number(i)+":"+QString::number(SetDataValue[i]));
            }
            //                       qDebug()<<  QString::number(AutoDataValue[i]);
            checkflag =0;
            emit SendSetLinData();
        }
        else if(Readdata.at(14) == '5'&&Readdata.at(15) == '8'&&Readdata.at(16) == '0'&&Readdata.at(17) == '2')//手动界面
        {
            bt = Readdata.remove(0,22);
            int right, left;int s =0;
            for(int i =0;i<bt.length()/4;i++)
            {
                s = bt.mid(i*4,4).toInt(&ok,16);
                right = (s & 0XFF)<<8;//低八位
                left = (s & 0XFF00)>> 8;//高八位  右移8位
                GetManualValue[i] = right + left;
                if(GetManualValue[i]>32767)
                {
                    GetManualValue[i] =  GetManualValue[i] - 65536;

                }
                //                Data_Set->ui->textEdit->append(QString::number(i)+":"+QString::number(SetDataValue[i]));
            }
            emit SendManualData();
        }
        else if(Readdata.at(14) == '0'&&Readdata.at(15) == 'C'&&Readdata.at(16) == '0'&&Readdata.at(17) == '0')//访问到位信号
        {

            bt = Readdata.remove(0,22);
            int right, left;int s =0;
            for(int i =0;i<bt.length()/4;i++)
            {
                s = bt.mid(i*4,4).toInt(&ok,16);
                right = (s & 0XFF)<<8;//低八位
                left = (s & 0XFF00)>> 8;//高八位  右移8位
                GetInPlaceValue[i] = right + left;
                if(GetInPlaceValue[i]>32767)
                {
                    GetInPlaceValue[i] =  GetInPlaceValue[i] - 65536;

                }
                //                Data_Set->ui->textEdit->append(QString::number(i)+":"+QString::number(SetDataValue[i]));
            }
            emit InPlaceTime();
        }



    }

    //    Judge_data();
}

void PLC_MC::GetReadCommandD(QString Path,int startIndex,int len)//单块批量读取
{
    QByteArray Command ;
    //头部指令
    Command[0] = 0x50;
    Command[1] = 0x00;
    //网络编号
    Command[2] = 0x00;
    //PLC编号
    Command[3] = 0xFF;
    //请求目标模块IO号
    Command[4] = 0xFF;
    Command[5] = 0x03;
    //请求目标模块站编号
    Command[6] = 0x00;
    //访问数据物理长度
    Command[7] = 0x0C;
    Command[8] = 0x00;
    //CPU监视定时器
    Command[9]= 0x10;
    Command[10] = 0x00;
    //命令 读
    Command[11] = 0x01;
    Command[12] = 0x04;
    //子命令
    Command[13] = 0x00;
    Command[14] = 0x00;
    //首地址,字节序反转
    QString datavalue = QString("%1").arg(startIndex, 6, 16, QLatin1Char('0'));//前置位补0

    datavalue = datavalue.mid(4,2)+datavalue.mid(2,2)+datavalue.mid(0,2);
    //    byte yy = datavalue.toLatin1();/*/2*//*/2 *//*/ 2*//*/ 2 *//*/ 2 */

    Command[17] = (startIndex/256/256%256);

    Command[16] = (startIndex/256%256);
    Command[15] = (startIndex%256);
    //软元件
    //软元件单元
    if(Path == "D")//可以的
    {
        Command[18] = 0xA8;
    }
    else if(Path == "X")
    {
        Command[18] = 0x9C;
    }
    else if(Path == "Y")
    {
        Command[18] = 0x9D;
    }
    else if(Path == "M")//可以的
    {
        Command[18] = 0x90;
    }
    else if(Path == "ZR")
    {
        Command[18] = 0xB0;
    }
    //读取长度,字节序反转
    Command[20] = (len /256 % 256);
    Command[19] = (len % 256);

    //    qDebug()<<"Command1111"<<Command<<Command.toHex()<<QByteArray::fromHex(Command);

    m_tcpSocket->write(Command);

}


void PLC_MC::GetReadMultiblock(int BlockNum,QVector<QString> index,QVector<int> index1,QVector<int> index2)//多块读取
{
    BlockNum = index.count();
    //    50 00 00 FF FF 03 00 14 00 0A 00 06 04 00 00  02 00 40 0D 03 B0 90 01 84 0F 03 B0 F4 01
    QByteArray Command ;
    //头部指令
    Command[0] = 0x50;
    Command[1] = 0x00;
    //网络编号
    Command[2] = 0x00;
    //PLC编号
    Command[3] = 0xFF;
    //请求目标模块IO号
    Command[4] = 0xFF;
    Command[5] = 0x03;
    //请求目标模块站编号
    Command[6] = 0x00;
    //访问数据物理长度
    Command[7] = 0x0E;
    Command[8] = 0x00;
    //CPU监视定时器
    Command[9]= 0x10;
    Command[10] = 0x00;
    //命令 写字
    Command[11] = 0x06;
    Command[12] = 0x04;
    //子命令
    Command[13] = 0x00;
    Command[14] = 0x00;

    Command[15] = (BlockNum % 256);
    Command[16] = (BlockNum /256 % 256);

    //    Command
    for(int i = 0;i<index.count();i++)
    {
        if(index.at(i) == "D")//可以的
        {
            Command[20+(i*6)] = 0xA8;
        }
        else if(index.at(i) == "X")
        {
            Command[20+(i*6)] = 0x9C;
        }
        else if(index.at(i) == "Y")
        {
            Command[20+(i*6)] = 0x9D;
        }
        else if(index.at(i) == "M")//可以的
        {
            Command[20+(i*6)] = 0x90;
        }
        else if(index.at(i) == "ZR")
        {
            Command[20+(i*6)] = 0xB0;
        }

        Command[17+(i*6)] = (index1.at(i)%256);
        Command[18+(i*6)] = (index1.at(i)/256%256);
        Command[19+(i*6)] = (index1.at(i)/256/256%256);

        Command[21+(i*6)] = (index2.at(i) % 256);
        Command[22+(i*6)] = (index2.at(i) /256 % 256);
    }

    Command[7] = ((Command.count()-9 )% 256);

    Command[8] = ((Command.count()-9 ) /256 % 256);
    //        qDebug()<<"Command"<<Command<<Command.count()<<Command.toHex();
    m_tcpSocket->write(Command);
}

void PLC_MC::GetReadMultiblockBit(int BlockNum,int BitNum,QVector<QString> index,QVector<int> index1,QVector<int> index2)//多块多位读取
{
    //    50 00 00 FF FF 03 00 14 00 0A 00 06 04 00 00  02 00 40 0D 03 B0 90 01 84 0F 03 B0 F4 01
    QByteArray Command ;
    //头部指令
    Command[0] = 0x50;
    Command[1] = 0x00;
    //网络编号
    Command[2] = 0x00;
    //PLC编号
    Command[3] = 0xFF;
    //请求目标模块IO号
    Command[4] = 0xFF;
    Command[5] = 0x03;
    //请求目标模块站编号
    Command[6] = 0x00;
    //访问数据物理长度
    Command[7] = 0x0E;
    Command[8] = 0x00;
    //CPU监视定时器
    Command[9]= 0x10;
    Command[10] = 0x00;
    //命令 写字
    Command[11] = 0x06;
    Command[12] = 0x04;
    //子命令
    Command[13] = 0x00;
    Command[14] = 0x00;

    Command[15] = (BlockNum % 256);
    Command[16] = (BitNum  % 256);

    //    Command
    for(int i = 0;i<index.count();i++)
    {
        if(index.at(i) == "D")//可以的
        {
            Command[20+(i*6)] = 0xA8;
        }
        else if(index.at(i) == "X")
        {
            Command[20+(i*6)] = 0x9C;
        }
        else if(index.at(i) == "Y")
        {
            Command[20+(i*6)] = 0x9D;
        }
        else if(index.at(i) == "M")//可以的
        {
            Command[20+(i*6)] = 0x90;
        }
        else if(index.at(i) == "ZR")
        {
            Command[20+(i*6)] = 0xB0;
        }

        Command[17+(i*6)] = (index1.at(i)%256);
        Command[18+(i*6)] = (index1.at(i)/256%256);
        Command[19+(i*6)] = (index1.at(i)/256/256%256);

        Command[21+(i*6)] = (index2.at(i) % 256);
        Command[22+(i*6)] = (index2.at(i) /256 % 256);
    }

    Command[7] = ((Command.count()-9 )% 256);

    Command[8] = ((Command.count()-9 ) /256 % 256);
    //    qDebug()<<"Command"<<Command<<Command.count()<<Command.toHex();
    m_tcpSocket->write(Command);
}

void PLC_MC::GetManualdata()//设置单写(按字写)
{
    QVector<QString> index;
    QVector<int> index1;
    QVector<int> index2;

    index.append("ZR");
    index1.append(500124);
    index2.append(30);

    index.append("ZR");
    index1.append(500184);
    index2.append(45);

    index.append("ZR");
    index1.append(500229);
    index2.append(30);

    index.append("ZR");
    index1.append(500289);
    index2.append(45);

    index.append("ZR");
    index1.append(500334);
    index2.append(1);

    index.append("ZR");
    index1.append(500344);
    index2.append(1);

    index.append("ZR");
    index1.append(500354);
    index2.append(1);

    index.append("ZR");
    index1.append(500364);
    index2.append(1);

    index.append("ZR");
    index1.append(500374);
    index2.append(1);

    index.append("ZR");
    index1.append(500384);
    index2.append(1);

    index.append("ZR");
    index1.append(500394);
    index2.append(1);

    index.append("ZR");
    index1.append(500404);
    index2.append(1);

    index.append("ZR");
    index1.append(500414);
    index2.append(1);

    index.append("ZR");
    index1.append(500424);
    index2.append(1);

    index.append("ZR");
    index1.append(500434);
    index2.append(1);

    index.append("ZR");
    index1.append(500444);
    index2.append(1);

    index.append("ZR");
    index1.append(500454);
    index2.append(1);

    index.append("ZR");
    index1.append(500464);
    index2.append(1);

    index.append("ZR");
    index1.append(500474);
    index2.append(1);

    index.append("ZR");
    index1.append(500484);
    index2.append(1);

    index.append("ZR");
    index1.append(500494);
    index2.append(1);

    index.append("ZR");
    index1.append(500504);
    index2.append(1);

    index.append("ZR");
    index1.append(500514);
    index2.append(102);

    index.append("D");
    index1.append(1417);
    index2.append(1);

    index.append("ZR");
    index1.append(500525);
    index2.append(18);

    index.append("ZR");
    index1.append(500011);
    index2.append(9);

    index.append("ZR");
    index1.append(0);
    index2.append(1);

    GetReadMultiblock(2, index,index1,index2);
}
void PLC_MC::SetWriteCommand(QString unit, int address,int value)//设置单写(按字写)
{
    //    qDebug()<<"进入单写PLC"<<"地址:"+unit+QString::number(address);
    QByteArray Command ;
    //头部指令
    Command[0] = 0x50;
    Command[1] = 0x00;
    //网络编号
    Command[2] = 0x00;
    //PLC编号
    Command[3] = 0xFF;
    //请求目标模块IO号
    Command[4] = 0xFF;
    Command[5] = 0x03;
    //请求目标模块站编号
    Command[6] = 0x00;
    //访问数据物理长度
    Command[7] = 0x0E;
    Command[8] = 0x00;
    //CPU监视定时器
    Command[9]= 0x10;
    Command[10] = 0x00;
    //命令 写字
    Command[11] = 0x01;
    Command[12] = 0x14;
    //子命令
    Command[13] = 0x00;
    Command[14] = 0x00;
    //    //首地址,字节序反转
    //    QString datavalue = QString("%1").arg(address, 6, 16, QLatin1Char('0'));//前置位补0

    //    datavalue = datavalue.mid(4,2)+datavalue.mid(2,2)+datavalue.mid(0,2);
    //    //    byte yy = datavalue.toLatin1();/*/2*//*/2 *//*/ 2*//*/ 2 *//*/ 2 */
    //首地址,字节序反转
    Command[17] = (address/256/256%256);
    Command[16] = (address/256%256);
    Command[15] = (address%256);
    //软元件单元
    if(unit == "D")//可以的
    {
        Command[18] = 0xA8;
    }
    else if(unit == "X")
    {
        Command[18] = 0x9C;
    }
    else if(unit == "Y")
    {
        Command[18] = 0x9D;
    }
    else if(unit == "M")//可以的
    {
        Command[18] = 0x90;
    }
    else if(unit == "ZR")
    {
        Command[18] = 0xB0;
    }
    //写入长度,
    Command[19] = 0x01;

    Command[20] = 0x00;

    //写入值长度,字节序反转
    Command[22] = (value /256 % 256);
    Command[21] = (value % 256);

    //    qDebug()<<"Command"<<Command<<Command.toHex();

    m_tcpSocket->write(Command);
}



void PLC_MC::SetWriteCommandPoint(QString unit, int address,int value)//设置单写位(按字写)
{
    //    qDebug()<<"进入单写PLC"<<"地址:"+unit+QString::number(address);
    //    50 00  00  FF  FF 03  00  0D 00  10 00  01 14 01 00    0A 1A 00 90 01 00  00
    QByteArray Command ;
    //头部指令
    Command[0] = 0x50;
    Command[1] = 0x00;
    //网络编号
    Command[2] = 0x00;
    //PLC编号
    Command[3] = 0xFF;
    //请求目标模块IO号
    Command[4] = 0xFF;
    Command[5] = 0x03;
    //请求目标模块站编号
    Command[6] = 0x00;
    //访问数据物理长度
    Command[7] = 0x0D;
    Command[8] = 0x00;
    //CPU监视定时器
    Command[9]= 0x10;
    Command[10] = 0x00;
    //命令 写字
    Command[11] = 0x01;
    Command[12] = 0x14;
    //子命令
    Command[13] = 0x01;
    Command[14] = 0x00;
    //    //首地址,字节序反转
    //    QString datavalue = QString("%1").arg(address, 6, 16, QLatin1Char('0'));//前置位补0

    //    datavalue = datavalue.mid(4,2)+datavalue.mid(2,2)+datavalue.mid(0,2);
    //    //    byte yy = datavalue.toLatin1();/*/2*//*/2 *//*/ 2*//*/ 2 *//*/ 2 */
    //首地址,字节序反转
    Command[17] = (address/256/256%256);
    Command[16] = (address/256%256);
    Command[15] = (address%256);
    //软元件单元
    if(unit == "D")//可以的
    {
        Command[18] = 0xA8;
    }
    else if(unit == "X")
    {
        Command[18] = 0x9C;
    }
    else if(unit == "Y")
    {
        Command[18] = 0x9D;
    }
    else if(unit == "M")//可以的
    {
        Command[18] = 0x90;
    }
    else if(unit == "ZR")
    {
        Command[18] = 0xB0;
    }
    //写入长度,
    Command[19] = 0x01;

    Command[20] = 0x00;

    //写入值长度,字节序反转
    if(value == 1)
    {
        Command[21] = 0x10;
    }
    else if (value == 0)
    {
        Command[21] = 0x00;
    }

    //    Command[22] = (value /256 % 256);
    //    qDebug()<<"当前进入值为"<<value;
    //int vlue = value % 256;
    //    Command[21] = vlue;
    //    qDebug()<<"当前值转换为"+QString::number(vlue)+"转换为字节:"+Command[21];
    //        qDebug()<<"Command"<<Command<<Command.toHex();

    m_tcpSocket->write(Command);
}


void PLC_MC::GetSettingdata()
{
    if(checkflag == 0)
    {
        GetReadCommandD("ZR",600000,959);
    }
    else if(checkflag == 1)
    {
        GetReadCommandD("ZR",601000,928);
    }
    else if(checkflag == 2)
    {
        GetReadCommandD("ZR",601928,920);
    }
}

void PLC_MC::on_MC_Read_clicked()
{
    //    int Len = ui->StartPath->text().toInt();
    //    int data = ui->numdata->text().toInt();
    GetReadCommandD("ZR",500001,960);
}


void PLC_MC::on_SavePLCIP_Port_clicked()
{
    QString path = QApplication::applicationDirPath() + "/System/PLC_MC.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    INI_File->setValue("PLC_IP",ui->PLC_IP->text());
    INI_File->setValue("PLC_Port",ui->PLC_Port->text());
    INI_File->destroyed();
}

