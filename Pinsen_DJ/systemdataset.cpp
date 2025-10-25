#include "systemdataset.h"
#include "ui_systemdataset.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QTextCodec>
#include <QDateTime>
SystemDataSet *SetSystemDataWindow;
SystemDataSet::SystemDataSet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemDataSet)
{
    ui->setupUi(this);
}

SystemDataSet::~SystemDataSet()
{
    delete ui;
}

void SystemDataSet::on_SelectPath_clicked()
{
    QString file_path = QFileDialog::getExistingDirectory(this, "请选择存储文件夹路径...", "./");
    ui->DataPath->setText(file_path);
    if(file_path.isEmpty())

    { return; }
}


void SystemDataSet::on_SavePath_clicked()

{
    QString path = QApplication::applicationDirPath() + "/System/System.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    INI_File->setValue("DataSavePath",ui->DataPath->text());
    QMessageBox::information(this, "提示", "数据存储成功");
}

