#include "home_interface.h"
#include "ui_home_interface.h"

Home_interface::Home_interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_interface)
{
    ui->setupUi(this);
    this->setWindowTitle("电检性能检测软件V1.17");
    Slot_Init();

}

void Home_interface::Slot_Init()
{
    MainShow = new MainWindow();//频道配置界面
    QString path = QApplication::applicationDirPath() + "/HVAC/PD_HVACMode.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    for(int i = 1;i<31;i++)
    {
        ui->Cbt_ProductName->addItems({QString::number(i)+"."+ INI_File->value("PD"+QString::number(i)+"_HVAC_Name").toString()});//频道
    }
    INI_File->destroyed();

    connect(MainShow , &MainWindow::Sign_Goback, this , &Home_interface::Slot_Goback);

    Login_Main = new Login();//登录界面
    connect(Login_Main , &Login::Sign_GoMain, this , &Home_interface::Slot_GoMainwindow);

}

void Home_interface::Slot_GoMainwindow(int index)
{
    if(index==0)//操作员
    {

        //        int PD = 1+ui->Cbt_ProductName->currentIndex();
        MainShow->ReadChannel_flag = 2;
        //        if(m_S_RFID_Pars.Channel.toInt()<31&&m_S_RFID_Pars.Channel.toInt()>0)
        //        {
        ////           emit Sign_Start_detection("ZR",0,m_S_RFID_Pars.Channel.toInt());
        //            MainShow->ui->Auto_PDbox->setCurrentText(m_S_RFID_Pars.Channel);
        //        }
        //        MainShow->ui->Auto_PDbox->setStyleSheet("QComboBox::drop-down { border: 0px; }"
        //                                                 "QComboBox::down-arrow { image: none; }");

        MainShow->ui->Auto_PDbox->setEnabled(false);  // 确保启用
        MainShow->ui->actionSetPD->setEnabled(false);
        MainShow->ui->actionPD_Data->setEnabled(false);
        MainShow->showMaximized();
        this->hide();
    }
    else if(index == 1)//管理员
    {
        MainShow->ui->actionSetPD->setEnabled(true);
        MainShow->ui->actionPD_Data->setEnabled(true);
        //        int PD = 1+ui->Cbt_ProductName->currentIndex();
        MainShow->ReadChannel_flag = 2;
        MainShow->adminman =1;
        if(AutoDataValue[899]==1 )
        {
            int PD = 1+ui->Cbt_ProductName->currentIndex();
            //            MainShow->on_Auto_PDbox_currentTextChanged(QString::number(PD));
            MainShow->ui->Auto_PDbox->setCurrentText(QString::number(PD));
            MainShow->on_Auto_PDbox_currentTextChanged(QString::number(PD));
        }

        MainShow->showMaximized();
        this->hide();
    }
    else if(index == 2)//CPP
    {
        MainShow->ui->actionSetPD->setEnabled(true);
        MainShow->ui->actionPD_Data->setEnabled(true);
        //        int PD = 1+ui->Cbt_ProductName->currentIndex();
        MainShow->ReadChannel_flag = 1;
        MainShow->adminman =2;

        int PD = 1+ui->Cbt_ProductName->currentIndex();
        MainShow->on_Auto_PDbox_currentTextChanged(QString::number(PD));
        MainShow->ui->Auto_PDbox->setCurrentText(QString::number(PD));
        MainShow->on_Auto_PDbox_currentTextChanged(QString::number(PD));


        MainShow->showMaximized();
        this->hide();
    }
}

void Home_interface::Slot_Goback()
{

    this->showMaximized();
    MainShow->hide();
}

Home_interface::~Home_interface()
{
    delete ui;
}

void Home_interface::on_Btn_Enter_updateChannelsName_clicked()
{
    ui->Cbt_ProductName->clear();
    QString path = QApplication::applicationDirPath() + "/HVAC/PD_HVACMode.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    for(int i = 1;i<31;i++)
    {
        ui->Cbt_ProductName->addItems({QString::number(i)+"."+INI_File->value("PD"+QString::number(i)+"_HVAC_Name").toString()});//频道
    }
    INI_File->destroyed();
}


void Home_interface::on_Btn_EnterWork_clicked()
{
    Login_Main->ui->groupBox->show();
    Login_Main->ui->groupBox_2->hide();
    Login_Main->show();

}

void Home_interface::closeEvent(QCloseEvent *event)
{
    auto temp = QMessageBox::information(this,"提示","是否关闭软件",QMessageBox::Yes | QMessageBox::No);
    if(temp == QMessageBox::Yes)
    {
        MainShow->close();//鼓风机参数设置
    }
    else
    {
        event->ignore();
    }
}


