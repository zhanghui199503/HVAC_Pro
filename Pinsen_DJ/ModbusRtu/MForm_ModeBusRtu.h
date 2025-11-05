#ifndef MFORM_MODEBUSRTU_H
#define MFORM_MODEBUSRTU_H

#include <QWidget>
#include <QTimer>
#include <QButtonGroup>
#include <QSerialPortInfo>
#include <QSerialPortInfo>
#include <QDebug>
#include <QFile>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ModbusRtu/mModbusRtu.h"



namespace Ui {
class MForm_ModeBusRtu;
}

class MForm_ModeBusRtu : public QWidget
{
    Q_OBJECT

public:
    explicit MForm_ModeBusRtu(QWidget *parent = nullptr);
    ~MForm_ModeBusRtu();

    Ui::MForm_ModeBusRtu *ui;
    QTimer *ptimer = new QTimer(this);

    QDialog *m_Dialog485;
    QLabel *label485;

    QButtonGroup *BtnGroup;//IO调试

    QString languageName = "langue_ch";


    void load_File_INI();

    void RealUpdate_BSM_Display();

    void loadFile();
    void Slot_COMStyleSheet(const QString &name, bool b_value);
    void slot_setled_cicular(QLabel *label, const int color);
    void Init_TableWidget();
public slots:
    void Slot_AddBtnID(int id);

    void slot_Timeout();
private slots:
    void on_Btn_Save_clicked();
    void on_Btn_Updata_Com_clicked();
    void on_Btn_RS485_clicked();
    void on_Btn_loadfile_clicked();
    void on_Btn_board_1_toggled(bool checked);
    void on_Btn_board_2_toggled(bool checked);

signals:
    //ModbusRtu
    void sign_ReadDiscreteInputs();
    void sign_ReadCoils();
    void sign_WriteCoils();
    void sign_WriteCoils_2();
    void sign_ReadInputRegisters();
    void sign_WriteHoldingRegisters();
    void sign_reConnect_Rtu();
     void sign_OpenComBSM(QString com, uint baudBit, uint dataBit, uint stopBits, uint parityBit);

private:

     int v_agree_index = 0;

     enum _m_color{
         Gray,
         Red,
         Green,
         Yellow,
         White,
     };


//     QStringList _color_id_Name = {"gray", "red", "green", "yellow", "white", "black", "#ffaa00"};
     QStringList _mColorName = {
         "background-color: rgb(200,200,200);",
         "background-color: red;",
         "background-color: rgb(0,255,0);",
         "background-color: yellow;",
         "background-color: white;",

         "background-color: black;",
         "background-color: #ffaa00;",

     };


};

struct A1_MForm_ModeBusRtu{

    QString BSM_PORT;
    QString BSM_BUAD;

    QMap<QString, int> IO_XY;
    QMap<QString, int> IO_Y2;
};
extern A1_MForm_ModeBusRtu mS_BSMIO;

extern MForm_ModeBusRtu *m_Form_ModeBusRtu;
#endif // MFORM_MODEBUSRTU_H
