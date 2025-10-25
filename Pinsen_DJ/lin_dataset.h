#ifndef LIN_DATASET_H
#define LIN_DATASET_H

#include <QWidget>
//#include <Header_File.h>


#include "editablelabel.h"

namespace Ui {
class LIN_Dataset;
}

class LIN_Dataset : public QWidget
{
    Q_OBJECT

public:
    explicit LIN_Dataset(QWidget *parent = nullptr);
    ~LIN_Dataset();
    Ui::LIN_Dataset *ui;
    int LIN_Enable_flag = 0;//使能 1 不使能0
    int LIN_ErrorEnable = 0;//使能 1 不使能0
    int LIN_InitEnable_flag =0;//使能 1 不使能0
    int LIN_Direction_flag  =0;//方向，运行应急位置，运行应急释放
    int LIN_InitDirection_flag =0;//初始化方向



    int LIN = 0;//LIN标志位
    int Read_Write_Mode = 0;//判断当前模式 0读取模式 1写入模式
public slots:
//    void slot_DoubleSpinBox_textChange(QString str);
//    void slot_LineEdit_textChange(QString str);
//    void slot_ComboBox_Change(int index);
//    void slot_PushButton_Clink();
    void Main_Init();//界面初始化
    void slot_SaveChangeData(QString);

    void slot_NowMode(int index);//判断当前模式
private slots:
    void on_Set_LIN_Enable_clicked();

    void on_Set_LIN_ErrorEnable_clicked();

    void on_Set_LIN_InitEnable_clicked();

    void on_Set_LIN_Direction_currentIndexChanged(int index);


    void on_Set_LIN_InitDirection_currentIndexChanged(int index);

private:

signals:
    void Sign_Set_PLCdata(QString unit, int address,int value);//发送设置

};

#endif // LIN_DATASET_H
