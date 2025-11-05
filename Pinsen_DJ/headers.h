



#include <QTcpSocket>
#include <QHostAddress>
#include <QDesktopWidget>
#include <QTimer>
#include <QDateTime>
#include <QtSerialPort>
#include <QLabel>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlTableModel>

#ifndef HEADS_H
#define HEADS_H

// 定义任务结果结构体，用于传递执行状态
//struct TaskResult {
//    bool completed;  // 任务是否完成
//    QByteArray result;  // 任务执行结果
//    bool success;    // 任务是否成功执行

//    TaskResult() : completed(false), success(false) {}
//};
#endif // HEADS_H

#include <QThread>
#include <QMap>



//主界面
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "serialportworker.h"

#include "thread_ptmotor.h"
#include "motor_types.h"
#include "MFormMotor.h"

//PLC通讯界面
#include "plc_mc.h"
#include "ui_plc_mc.h"

//参数设置界面
#include "datasetting.h"
#include "ui_datasetting.h"

//EXCEl
#include "xlsxdocument.h"

//手动界面
#include "manualui.h"
#include "ui_manualui.h"

//鼓风机设置界面
//#include "blower_dataset.h"
//#include "ui_blower_dataset.h"

////LIN电机设置界面
//#include "lin_dataset.h"
//#include "ui_lin_dataset.h"

//联系我们界面
#include "showpicture.h"

//关于软件界面
#include "aboutsoftware.h"
#include "ui_aboutsoftware.h"

#include "ini_file.h"

//RFID界面
#include "ui_mRFID_Dialog.h"
#include "RFID/mRFID_Dialog.h"

//OK界面
#include "pop_ups_ok.h"
#include "ui_pop_ups_ok.h"

//NG界面
#include "pop_ups_ng.h"
#include "ui_pop_ups_ng.h"

//江淮主界面
#include "home_interface.h"
#include "ui_home_interface.h"


#include "login.h"
#include "ui_login.h"

//报警界面
#include "pop_ups_alarm.h"
#include "ui_pop_ups_alarm.h"

//参数列表界面
#include "hvac_mode.h"
#include "ui_hvac_mode.h"

//通讯界面
#include "communicationerror.h"
#include "ui_communicationerror.h"

#include "thread_CommTask.h"
#include "thread_main.h"




