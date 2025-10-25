#ifndef HVAC_MODE_H
#define HVAC_MODE_H

#include <QWidget>
#include <Header_File.h>

namespace Ui {
class HVAC_Mode;
}

class HVAC_Mode : public QWidget
{
    Q_OBJECT

public:
    explicit HVAC_Mode(QWidget *parent = nullptr);
    ~HVAC_Mode();
Ui::HVAC_Mode *ui;
int Edit_Enable_flag  =0;//编辑标志位
public slots:
    void Main_Init();//界面初始化

private slots:
    void on_Save_HVAC_ModeData_clicked();

    void on_Edit_Enable_clicked();

    void on_CopyPD_textChanged(const QString &arg1);

    void on_CopyPD2_textChanged(const QString &arg1);

    void on_DataCopy_clicked();

private:

signals:
//    void Sign_Set_PLCData()
    void Sign_Set_PLCData(QString unit, int address,int value);//发送信号
    void Sign_Set_PLCDataPoint(QString unit, int address,int value);//发送信号
};
extern HVAC_Mode *HVAC_Modelist;
#endif // HVAC_MODE_H
