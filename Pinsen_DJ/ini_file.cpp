#include "ini_file.h"
#include <QtCore/QtCore>
#include <QFile>
#include <QDebug>


ini_file::ini_file()
{
    m_qstrFileName = QCoreApplication::applicationDirPath() + "/PLC_Data.ini";
    //qDebug()<<"m_qstrFileName: "<<m_qstrFileName;
    //"Config.ini"配置文件，文件存在则打开，不存在则创建
    m_psetting = new QSettings(m_qstrFileName,QSettings::IniFormat);
}

ini_file::~ini_file()
{
    delete m_psetting;
    m_psetting = NULL;
}

void ini_file::Set_Control(QString FilePath, QString FileValue)
{
    // arg1  =  "1/step" ; arg2 = "ui.s.value"
    m_psetting->setValue(FilePath, FileValue);
}
void ini_file::Ini_Remove(QString FilePath)
{
    // arg1  =  "1/step" ; arg2 = "ui.s.value"

    m_psetting->remove("/"+FilePath);
}

QString ini_file::Get_Control(QString FileValue)
{
    QString value = m_psetting->value(FileValue).toString();
    return value;
}
