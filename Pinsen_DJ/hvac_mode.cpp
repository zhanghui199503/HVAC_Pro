#include "hvac_mode.h"
#include "ui_hvac_mode.h"

HVAC_Mode *HVAC_Modelist;

HVAC_Mode::HVAC_Mode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HVAC_Mode)
{
    ui->setupUi(this);
    Main_Init();//界面初始化
    this->setWindowTitle("HVAC参数列表");
}

HVAC_Mode::~HVAC_Mode()
{
    delete ui;
}
void HVAC_Mode::Main_Init()
{
    QList<QLineEdit *> Main_PD_Name;
    Main_PD_Name.append(ui->PD1_HVAC_Name);Main_PD_Name.append(ui->PD2_HVAC_Name);Main_PD_Name.append(ui->PD3_HVAC_Name);
    Main_PD_Name.append(ui->PD4_HVAC_Name);Main_PD_Name.append(ui->PD5_HVAC_Name);Main_PD_Name.append(ui->PD6_HVAC_Name);
    Main_PD_Name.append(ui->PD7_HVAC_Name);Main_PD_Name.append(ui->PD8_HVAC_Name);Main_PD_Name.append(ui->PD9_HVAC_Name);
    Main_PD_Name.append(ui->PD10_HVAC_Name);Main_PD_Name.append(ui->PD11_HVAC_Name);Main_PD_Name.append(ui->PD12_HVAC_Name);
    Main_PD_Name.append(ui->PD13_HVAC_Name);Main_PD_Name.append(ui->PD14_HVAC_Name);Main_PD_Name.append(ui->PD15_HVAC_Name);
    Main_PD_Name.append(ui->PD16_HVAC_Name);Main_PD_Name.append(ui->PD17_HVAC_Name);Main_PD_Name.append(ui->PD18_HVAC_Name);
    Main_PD_Name.append(ui->PD19_HVAC_Name);Main_PD_Name.append(ui->PD20_HVAC_Name);Main_PD_Name.append(ui->PD21_HVAC_Name);
    Main_PD_Name.append(ui->PD22_HVAC_Name);Main_PD_Name.append(ui->PD23_HVAC_Name);Main_PD_Name.append(ui->PD24_HVAC_Name);
    Main_PD_Name.append(ui->PD25_HVAC_Name);Main_PD_Name.append(ui->PD26_HVAC_Name);Main_PD_Name.append(ui->PD27_HVAC_Name);
    Main_PD_Name.append(ui->PD28_HVAC_Name);Main_PD_Name.append(ui->PD29_HVAC_Name);Main_PD_Name.append(ui->PD30_HVAC_Name);

    QString path = QApplication::applicationDirPath() + "/HVAC/PD_HVACMode.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

    for (int i = 0;i <Main_PD_Name.count();i++ )
    {
        Main_PD_Name.at(i)->setText(INI_File->value("PD"+QString::number(i+1)+"_HVAC_Name").toString());
    }
    INI_File->destroyed();
}
void HVAC_Mode::on_Save_HVAC_ModeData_clicked()
{
    QList<QLineEdit *> Main_PD_Name;
    Main_PD_Name.append(ui->PD1_HVAC_Name);Main_PD_Name.append(ui->PD2_HVAC_Name);Main_PD_Name.append(ui->PD3_HVAC_Name);
    Main_PD_Name.append(ui->PD4_HVAC_Name);Main_PD_Name.append(ui->PD5_HVAC_Name);Main_PD_Name.append(ui->PD6_HVAC_Name);
    Main_PD_Name.append(ui->PD7_HVAC_Name);Main_PD_Name.append(ui->PD8_HVAC_Name);Main_PD_Name.append(ui->PD9_HVAC_Name);
    Main_PD_Name.append(ui->PD10_HVAC_Name);Main_PD_Name.append(ui->PD11_HVAC_Name);Main_PD_Name.append(ui->PD12_HVAC_Name);
    Main_PD_Name.append(ui->PD13_HVAC_Name);Main_PD_Name.append(ui->PD14_HVAC_Name);Main_PD_Name.append(ui->PD15_HVAC_Name);
    Main_PD_Name.append(ui->PD16_HVAC_Name);Main_PD_Name.append(ui->PD17_HVAC_Name);Main_PD_Name.append(ui->PD18_HVAC_Name);
    Main_PD_Name.append(ui->PD19_HVAC_Name);Main_PD_Name.append(ui->PD20_HVAC_Name);Main_PD_Name.append(ui->PD21_HVAC_Name);
    Main_PD_Name.append(ui->PD22_HVAC_Name);Main_PD_Name.append(ui->PD23_HVAC_Name);Main_PD_Name.append(ui->PD24_HVAC_Name);
    Main_PD_Name.append(ui->PD25_HVAC_Name);Main_PD_Name.append(ui->PD26_HVAC_Name);Main_PD_Name.append(ui->PD27_HVAC_Name);
    Main_PD_Name.append(ui->PD28_HVAC_Name);Main_PD_Name.append(ui->PD29_HVAC_Name);Main_PD_Name.append(ui->PD30_HVAC_Name);

    QString path = QApplication::applicationDirPath() + "/HVAC/PD_HVACMode.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    for (int i = 0;i <Main_PD_Name.count();i++ )
    {
        INI_File->setValue("PD"+QString::number(i+1)+"_HVAC_Name",Main_PD_Name.at(i)->text());
    }
    INI_File->destroyed();
}


void HVAC_Mode::on_Edit_Enable_clicked()
{
    if(Edit_Enable_flag == 0)
    {
        Edit_Enable_flag = 1;
        ui->Edit_Enable->setText("可编辑");
        ui->Edit_Enable->setStyleSheet("background-color: #00ff00; border: 2px solid #00ff00;color: #00ff00;");
        emit Sign_Set_PLCDataPoint("M",197,1);
        qDebug()<<"点击屏幕不可编辑按钮";
    }
    else
    {
        Edit_Enable_flag = 0;
        ui->Edit_Enable->setText("不可编辑");
        ui->Edit_Enable->setStyleSheet("background-color: #dcdcdc;border: 2px solid #81C784;color: #E8F5E9;");
        emit Sign_Set_PLCDataPoint("M",197,0);
    }


}


void HVAC_Mode::on_CopyPD_textChanged(const QString &arg1)
{
    if(Edit_Enable_flag == 1)
    {

        emit Sign_Set_PLCData("D",813,arg1.toInt());
        qDebug()<<"输入屏幕复制频道1";
    }
}


void HVAC_Mode::on_CopyPD2_textChanged(const QString &arg1)
{
    if(Edit_Enable_flag == 1)
    {

        emit Sign_Set_PLCData("D",814,arg1.toInt());
        qDebug()<<"输入屏幕复制频道2";
    }
}


void HVAC_Mode::on_DataCopy_clicked()
{
    if(Edit_Enable_flag == 1)
    {
        emit Sign_Set_PLCDataPoint("M",198,1);
        qDebug()<<"点击屏幕开始复制按钮";
        emit Sign_Set_PLCDataPoint("M",198,0);
    }
}

