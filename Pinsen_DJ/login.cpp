#include "login.h"
#include "ui_login.h"
 Login *Login_Main;
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    Login_Init();
    this->setWindowTitle("登录界面");

}

Login::~Login()
{
    delete ui;
}

void Login::Login_Init()
{
    QString path = QApplication::applicationDirPath() + "/HVAC/Passwords.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    if(INI_File->value("Operator").toString().isEmpty())
    {
        INI_File->setValue("Operator","000000");
    }
    if(INI_File->value("Admin").toString().isEmpty())
    {
        INI_File->setValue("Admin","111111");
    }
    if(INI_File->value("CPP").toString().isEmpty())
    {
        INI_File->setValue("CPP","0551");
    }

    INI_File->destroyed();
//     connect(m_MysqlThread, &mMysqlThread::sign_Login_Info, m_Form_Account, &MForm_Account::slot_FindUser);
}

void Login::slot_Find_Account(const QString user, const QString password)//查找用户等级
{
    Q_UNUSED(user);
    QString str1 = "SELECT 权限, 用户名, 权限等级 FROM admin" + tr(" WHERE 员工密码='%1'").arg(password);
    QSqlQuery query(MainWindow::mutualui->Sqlserverdb);
    query.prepare(str1);
    if(query.exec()){
        QString c_privilege_level = 0;
        QString username = "";
        QString Permissions = "";
        while(query.next()){
            c_privilege_level = query.value(0).toString();
            username = query.value(1).toString();
            Permissions = query.value(2).toString();
        }
        if(!c_privilege_level.isEmpty())
        {
            if(Permissions.toInt() == 1)
            {
               Login_flag = 1;
               qDebug()<<"进入人："+Permissions;
            }
            else if(Permissions.toInt() == 2)
            {
               Login_flag = 2;
            }
        }
        else
        {
            Login_flag = 0;
        }
    }
}


void Login::on_Btn_Login_clicked()
{
    QString path = QApplication::applicationDirPath() + "/HVAC/Passwords.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    QString InputPassword = ui->Login_Password->text();
    slot_Find_Account("",InputPassword);
    if(InputPassword == INI_File->value("Operator").toString()|| Login_flag == 2)//操作员(无法切频道操作)
    {
        qDebug()<<"当前进入权限等级：操作员";
        emit Sign_GoMain(0);
        ui->Login_Password->clear();
        this->hide();
    }
    else if (InputPassword == INI_File->value("Admin").toString()|| Login_flag == 1)//管理员(可以切频道操作)
    {
        qDebug()<<"当前进入权限等级：管理员";
        emit Sign_GoMain(1);
        ui->Login_Password->clear();
        this->hide();
    }
    else if (InputPassword == INI_File->value("CPP").toString())//管理员(可以切频道操作)
    {
        qDebug()<<"当前进入权限等级：CPP手动选择频道密码";
        emit Sign_GoMain(2);
        ui->Login_Password->clear();
        this->hide();
    }
    else
    {
        QMessageBox::about(this,"提示","输入密码错误！");
    }
    INI_File->destroyed();
}


void Login::on_revise_Password_clicked()
{
    ui->groupBox->hide();
    ui->groupBox_2->show();
}


void Login::on_Goback_Login_clicked()
{
    ui->groupBox->show();
    ui->groupBox_2->hide();
}


void Login::on_Confirm_changes_clicked()
{
    QString path = QApplication::applicationDirPath() + "/HVAC/Passwords.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    QString str1 = ui->Old_Password->text();
    QString str2 = ui->New_Password->text();
    QString str3 = ui->Again_Password->text();

    QString oldPasswords1 = INI_File->value("Operator").toString();
    QString oldPasswords2 = INI_File->value("Admin").toString();

    if(!str1.isEmpty() && (oldPasswords1 == str1 || oldPasswords2 == str1))
    {
        if(str2 == str3)
        {
            if(oldPasswords1 == str1 )//更改的是操作员密码
            {
                INI_File->setValue("Operator",str2);
                QMessageBox::about(this,"提示","操作员密码修改成功");
            }
            else if (oldPasswords2 == str1)//更改的是管理员密码
            {
               INI_File->setValue("Admin",str2);
               QMessageBox::about(this,"提示","管理员密码修改成功");
            }
        }
        else
        {
            QMessageBox::about(this,"提示","两次输入的密码不一致，请重新输入！");
        }
    }
    else
    {
        QMessageBox::about(this,"提示","请输入正确的旧密码！");
    }
    INI_File->destroyed();
}

