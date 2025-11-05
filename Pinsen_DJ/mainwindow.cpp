#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScreen>
MainWindow *MainShow;
MainWindow *MainWindow::mutualui = nullptr;

//-----------------------PT电机------------------------
QList<PTMotorFP_Setting_basis> PTmotorSettingsList;
QList<PTMotorFP_Setting_basis1> PTmotorSettingsList1;
QList<LINMotorFP_Setting_basis> LINmotorSettingsList;
QList<LINMotorFP_Setting_basis1> LINmotorSettingsList2;
QList<QList<LINMotorFP_Setting_basis1>> LINmotorSettingsList1;
//QList<Blower_Setting_basis> BlowerSettingsList;
//QList<Blower_Setting_basis1> BlowerSettingsList1;

QList<ToralThermistor_Setting_basis> ResSettingsList;
QList<Thermistor_Setting_basis> ResSettingsList1;
QList<QList<Thermistor_Setting_basis>> ResSettingsList2;

Blower_Setting_basis mBlowerSettingsList;
Blower_Setting_basis1 mBlowerSettingsList1;


QStringList MySql_TableName = {"datas_linecode_d","datas_linecode_d1","datas_linecode_d2","datas_linecode_d3"};
QStringList MySql_Create = {
    "create table jianghuai_songz.%1(序号 INTEGER PRIMARY KEY AUTO_INCREMENT ,"
    "频道号 text,产品型号 varchar(20),日期 varchar(25),电检总结果 text,总成条码 text,错误代码 text,检测时间 text,"
    "鼓风机检测结果 text,"
    "LIN1_1检测结果 text,LIN1_2检测结果 text,LIN1_3检测结果 text,LIN1_4检测结果 text,LIN1_5检测结果 text,LIN1_6检测结果 text,LIN1_7检测结果 text,LIN1_8检测结果 text,"
    "LIN1_9检测结果 text,LIN1_10检测结果 text,LIN1_11检测结果 text,LIN1_12检测结果 text,"
    "M1电机检测结果 text,M2电机检测结果 text,M3电机检测结果 text,M4电机检测结果 text,M5电机检测结果 text,M6电机检测结果 text,M7电机检测结果 text,M8电机检测结果 text,M9电机检测结果 text,"
    "M10电机检测结果 text,M11电机检测结果 text,M12电机检测结果 text,"
    "温敏1检测结果 text,温敏2检测结果 text,温敏3检测结果 text,温敏4检测结果 text,温敏5检测结果 text,温敏6检测结果 text,温敏7检测结果 text,温敏8检测结果 text,温敏9检测结果 text,温敏10检测结果 text,温敏11检测结果 text,温敏12检测结果 text,"
    "PM25检测结果 text,AQS检测结果 text,电子膨胀阀检测结果 text,PTC检测结果 text,负离子检测结果 text,噪音检测结果 text,X轴振动检测结果 text,Y轴振动检测结果 text,Z轴振动检测结果 text)",

    "create table jianghuai_songz.%2(序号 INTEGER PRIMARY KEY AUTO_INCREMENT ,"
    "频道号 text,产品型号 varchar(20),日期 varchar(25),电检总结果 text,总成条码 text,错误代码 text,检测时间 text,"
    "鼓风机频率 text,鼓风机硬件版本号 text,鼓风机软件版本号 text,"
    "鼓风机1档转速占空比端电压 text,鼓风机1档电流 text,鼓风机2档转速占空比端电压 text,鼓风机2档电流 text,鼓风机3档转速占空比端电压 text,鼓风机3档电流 text,"
    "鼓风机4档转速占空比端电压 text,鼓风机4档电流 text,鼓风机5档转速占空比端电压 text,鼓风机5档电流 text,鼓风机6档转速占空比端电压 text,鼓风机6档电流 text,"
    "鼓风机7档转速占空比端电压 text,鼓风机7档电流 text,鼓风机8档转速占空比端电压 text,鼓风机8档电流 text,鼓风机9档转速占空比端电压 text,鼓风机9档电流 text,"
    "鼓风机1档X轴振动值 text,鼓风机2档X轴振动值 text,鼓风机3档X轴振动值 text,鼓风机4档X轴振动值 text,鼓风机5档X轴振动值 text,鼓风机6档X轴振动值 text,鼓风机7档X轴振动值 text,鼓风机8档X轴振动值 text,鼓风机9档X轴振动值 text,"
    "鼓风机1档Y轴振动值 text,鼓风机2档Y轴振动值 text,鼓风机3档Y轴振动值 text,鼓风机4档Y轴振动值 text,鼓风机5档Y轴振动值 text,鼓风机6档Y轴振动值 text,鼓风机7档Y轴振动值 text,鼓风机8档Y轴振动值 text,鼓风机9档Y轴振动值 text,"
    "鼓风机1档Z轴振动值 text,鼓风机2档Z轴振动值 text,鼓风机3档Z轴振动值 text,鼓风机4档Z轴振动值 text,鼓风机5档Z轴振动值 text,鼓风机6档Z轴振动值 text,鼓风机7档Z轴振动值 text,鼓风机8档Z轴振动值 text,鼓风机9档Z轴振动值 text,"
    "鼓风机1档单轴振动值 text,鼓风机2档单轴振动值 text,鼓风机3档单轴振动值 text,鼓风机4档单轴振动值 text,鼓风机5档单轴振动值 text,鼓风机6档单轴振动值 text,鼓风机7档单轴振动值 text,鼓风机8档单轴振动值 text,鼓风机9档单轴振动值 text,"
    "鼓风机1档噪音检测值 text,鼓风机2档噪音检测值 text,鼓风机3档噪音检测值 text,鼓风机4档噪音检测值 text,鼓风机5档噪音检测值 text,鼓风机6档噪音检测值 text,鼓风机7档噪音检测值 text,鼓风机8档噪音检测值 text,鼓风机9档噪音检测值 text)",

    "create table jianghuai_songz.%3(序号 INTEGER PRIMARY KEY AUTO_INCREMENT ,"
    "频道号 text,产品型号 varchar(20),日期 varchar(25),电检总结果 text,总成条码 text,错误代码 text,检测时间 text,"
    "LIN1_1NAD text,LIN1_2NAD text,LIN1_3NAD text, LIN1_4NAD text,LIN1_5NAD text,LIN1_6NAD text,LIN1_7NAD text,LIN1_8NAD text,LIN1_9NAD text,LIN1_10NAD text,LIN1_11NAD text,LIN1_12NAD text,"
    "LIN1_1控制ID text,LIN1_2控制ID text,LIN1_3控制ID text,LIN1_4控制ID text,LIN1_5控制ID text,LIN1_6控制ID text,LIN1_7控制ID text,LIN1_8控制ID text,LIN1_9控制ID text,LIN1_10控制ID text,LIN1_11控制ID text,LIN1_12控制ID text,"
    "LIN1_1状态ID text,LIN1_2状态ID text,LIN1_3状态ID text,LIN1_4状态ID text,LIN1_5状态ID text,LIN1_6状态ID text,LIN1_7状态ID text,LIN1_8状态ID text,LIN1_9状态ID text,LIN1_10状态ID text,LIN1_11状态ID text,LIN1_12状态ID text,"
    "LIN1_1电机名称 text,LIN1_1电机步数汇总 text,LIN1_2电机名称 text,LIN1_2电机步数汇总 text,LIN1_3电机名称 text,LIN1_3电机步数汇总 text,"
    "LIN1_4电机名称 text,LIN1_4电机步数汇总 text,LIN1_5电机名称 text,LIN1_5电机步数汇总 text,LIN1_6电机名称 text,LIN1_6电机步数汇总 text,"
    "LIN1_7电机名称 text,LIN1_7电机步数汇总 text,LIN1_8电机名称 text,LIN1_8电机步数汇总 text,LIN1_9电机名称 text,LIN1_9电机步数汇总 text,"
    "LIN1_10电机名称 text,LIN1_10电机步数汇总 text,LIN1_11电机名称 text,LIN1_11电机步数汇总 text,LIN1_12电机名称 text,LIN1_12电机步数汇总 text,"
    "LIN1_1自学习极限步数1 text,LIN1_1自学习极限步数2 text,LIN1_2自学习极限步数1 text,LIN1_2自学习极限步数2,LIN1_3自学习极限步数1 text,LIN1_3自学习极限步数2 text,"
    "LIN1_4自学习极限步数1 text,LIN1_4自学习极限步数2 text,LIN1_5自学习极限步数1 text,LIN1_5自学习极限步数2,LIN1_6自学习极限步数1 text,LIN1_6自学习极限步数2 text,"
    "LIN1_7自学习极限步数1 text,LIN1_7自学习极限步数2 text,LIN1_8自学习极限步数1 text,LIN1_8自学习极限步数2,LIN1_9自学习极限步数1 text,LIN1_9自学习极限步数2 text,"
    "LIN1_10自学习极限步数1 text,LIN1_10自学习极限步数2 text,LIN1_11自学习极限步数1 text,LIN1_11自学习极限步数2,LIN1_12自学习极限步数1 text,LIN1_12自学习极限步数2 text)",

    "create table jianghuai_songz.%4(序号 INTEGER PRIMARY KEY AUTO_INCREMENT ,"
    "频道号 text,产品型号 varchar(20),日期 varchar(25),电检总结果 text,总成条码 text,错误代码 text,检测时间 text,"
    "M1电机名称 text,M1电机电压汇总 text,M1电机电流汇总 text,M2电机名称 text,M2电机电压汇总 text,M2电机电流汇总 text,"
    "M3电机名称 text,M3电机电压汇总 text,M3电机电流汇总 text,M4电机名称 text,M4电机电压汇总 text,M4电机电流汇总 text,"
    "M5电机名称 text,M5电机电压汇总 text,M5电机电流汇总 text,M6电机名称 text,M6电机电压汇总 text,M6电机电流汇总 text,"
    "M7电机名称 text,M7电机电压汇总 text,M7电机电流汇总 text,M8电机名称 text,M8电机电压汇总 text,M8电机电流汇总 text,"
    "M9电机名称 text,M9电机电压汇总 text,M9电机电流汇总 text,M10电机名称 text,M10电机电压汇总 text,M10电机电流汇总 text,"
    "M11电机名称 text,M11电机电压汇总 text,M11电机电流汇总 text,M12电机名称 text,M12电机电压汇总 text,M12电机电流汇总 text,"
    "室内环境温度 text,温敏1检测值 text,温敏2检测值 text,温敏3检测值 text,温敏4检测值 text,温敏5检测值 text,温敏6检测值 text,"
    "温敏7检测值 text,温敏8检测值 text,温敏9检测值 text,温敏10检测值 text,温敏11检测值 text,温敏12检测值 text,"
    "车内PM25检测浓度 text,车外PM25检测浓度 text,空气质量状态 text,电子膨胀阀ID text,电子膨胀阀当前位置 text,"
    "PTC_ID text,软件版本号 text,硬件版本号 text,负离子检测电压 text,噪音检测值 text)"
};


QVector<QString>Exceldata2{
    "频道号","产品型号","日期","电检总结果","总成条码","错误代码","检测时间",
    "鼓风机检测结果",
    "LIN1-1检测结果","LIN1-2检测结果","LIN1-3检测结果","LIN1-4检测结果","LIN1-5检测结果","LIN1-6检测结果","LIN1-7检测结果","LIN1-8检测结果",
    "LIN1-9检测结果","LIN1-10检测结果","LIN1-11检测结果","LIN1-12检测结果",
    "M1电机检测结果","M2电机检测结果","M3电机检测结果","M4电机检测结果","M5电机检测结果","M6电机检测结果","M7电机检测结果","M8电机检测结果","M9电机检测结果",
    "M10电机检测结果","M11电机检测结果","M12电机检测结果",
    "温敏1检测结果","温敏2检测结果","温敏3检测结果","温敏4检测结果","温敏5检测结果","温敏6检测结果","温敏7检测结果","温敏8检测结果","温敏9检测结果","温敏10检测结果","温敏11检测结果","温敏12检测结果",
    "PM2.5检测结果","AQS检测结果","电子膨胀阀检测结果","PTC检测结果","负离子检测结果","噪音检测结果","X轴振动检测结果","Y轴振动检测结果","Z轴振动检测结果",
    "鼓风机频率","鼓风机硬件版本号","鼓风机软件版本号",
    "鼓风机POS1转速/占空比/端电压","鼓风机POS1电流","鼓风机POS2转速/占空比/端电压","鼓风机POS2电流","鼓风机POS3转速/占空比/端电压","鼓风机POS3电流",
    "鼓风机POS4转速/占空比/端电压","鼓风机POS4电流","鼓风机POS5转速/占空比/端电压","鼓风机POS5电流","鼓风机POS6转速/占空比/端电压","鼓风机POS6电流",
    "鼓风机POS7转速/占空比/端电压","鼓风机POS7电流","鼓风机POS8转速/占空比/端电压","鼓风机POS8电流","鼓风机POS9转速/占空比/端电压","鼓风机POS9电流",
    "鼓风机1档X轴振动值","鼓风机2档X轴振动值","鼓风机3档X轴振动值","鼓风机4档X轴振动值","鼓风机5档X轴振动值","鼓风机6档X轴振动值","鼓风机7档X轴振动值","鼓风机8档X轴振动值","鼓风机9档X轴振动值",
    "鼓风机1档Y轴振动值","鼓风机2档Y轴振动值","鼓风机3档Y轴振动值","鼓风机4档Y轴振动值","鼓风机5档Y轴振动值","鼓风机6档Y轴振动值","鼓风机7档Y轴振动值","鼓风机8档Y轴振动值","鼓风机9档Y轴振动值",
    "鼓风机1档Z轴振动值","鼓风机2档Z轴振动值","鼓风机3档Z轴振动值","鼓风机4档Z轴振动值","鼓风机5档Z轴振动值","鼓风机6档Z轴振动值","鼓风机7档Z轴振动值","鼓风机8档Z轴振动值","鼓风机9档Z轴振动值",
    "鼓风机1档单轴振动值","鼓风机2档单轴振动值","鼓风机3档单轴振动值","鼓风机4档单轴振动值","鼓风机5档单轴振动值","鼓风机6档单轴振动值","鼓风机7档单轴振动值","鼓风机8档单轴振动值","鼓风机9档单轴振动值",
    "鼓风机1档噪音检测值","鼓风机2档噪音检测值","鼓风机3档噪音检测值","鼓风机4档噪音检测值","鼓风机5档噪音检测值","鼓风机6档噪音检测值","鼓风机7档噪音检测值","鼓风机8档噪音检测值","鼓风机9档噪音检测值",
    "LIN1-1NAD","LIN1-2NAD","LIN1-3NAD", "LIN1-4NAD","LIN1-5NAD","LIN1-6NAD","LIN1-7NAD","LIN1-8NAD","LIN1-9NAD","LIN1-10NAD","LIN1-11NAD","LIN1-12NAD",
    "LIN1-1控制ID","LIN1-2控制ID","LIN1-3控制ID","LIN1-4控制ID","LIN1-5控制ID","LIN1-6控制ID","LIN1-7控制ID","LIN1-8控制ID","LIN1-9控制ID","LIN1-10控制ID","LIN1-11控制ID","LIN1-12控制ID",
    "LIN1-1状态ID","LIN1-2状态ID","LIN1-3状态ID","LIN1-4状态ID","LIN1-5状态ID","LIN1-6状态ID","LIN1-7状态ID","LIN1-8状态ID","LIN1-9状态ID","LIN1-10状态ID","LIN1-11状态ID","LIN1-12状态ID",
    "LIN1_1电机名称","LIN1_1电机步数汇总","LIN1_2电机名称","LIN1_2电机步数汇总","LIN1_3电机名称","LIN1_3电机步数汇总",
    "LIN1_4电机名称","LIN1_4电机步数汇总","LIN1_5电机名称","LIN1_5电机步数汇总","LIN1_6电机名称","LIN1_6电机步数汇总",
    "LIN1_7电机名称","LIN1_7电机步数汇总","LIN1_8电机名称","LIN1_8电机步数汇总","LIN1_9电机名称","LIN1_9电机步数汇总",
    "LIN1_10电机名称","LIN1_10电机步数汇总","LIN1_11电机名称","LIN1_11电机步数汇总","LIN1_12电机名称","LIN1_12电机步数汇总",
    "LIN1_1自学习极限步数1","LIN1_1自学习极限步数2","LIN1_2自学习极限步数1","LIN1_2自学习极限步数2","LIN1_3自学习极限步数1","LIN1_3自学习极限步数2",
    "LIN1_4自学习极限步数1","LIN1_4自学习极限步数2","LIN1_5自学习极限步数1","LIN1_5自学习极限步数2","LIN1_6自学习极限步数1","LIN1_6自学习极限步数2",
    "LIN1_7自学习极限步数1","LIN1_7自学习极限步数2","LIN1_8自学习极限步数1","LIN1_8自学习极限步数2","LIN1_9自学习极限步数1","LIN1_9自学习极限步数2",
    "LIN1_10自学习极限步数1","LIN1_10自学习极限步数2","LIN1_11自学习极限步数1","LIN1_11自学习极限步数2","LIN1_12自学习极限步数1","LIN1_12自学习极限步数2",
    "M1电机名称","M1电机电压汇总","M1电机电流汇总","M2电机名称","M2电机电压汇总","M2电机电流汇总",
    "M3电机名称","M3电机电压汇总","M3电机电流汇总","M4电机名称","M4电机电压汇总","M4电机电流汇总",
    "M5电机名称","M5电机电压汇总","M5电机电流汇总","M6电机名称","M6电机电压汇总","M6电机电流汇总",
    "M7电机名称","M7电机电压汇总","M7电机电流汇总","M8电机名称","M8电机电压汇总","M8电机电流汇总",
    "M9电机名称","M9电机电压汇总","M9电机电流汇总","M10电机名称","M10电机电压汇总","M10电机电流汇总",
    "M11电机名称","M11电机电压汇总","M11电机电流汇总","M12电机名称","M12电机电压汇总","M12电机电流汇总",
    "室内环境温度","温敏1检测值","温敏2检测值","温敏3检测值","温敏4检测值","温敏5检测值","温敏6检测值","温敏7检测值","温敏8检测值","温敏9检测值","温敏10检测值","温敏11检测值","温敏12检测值",
    "车内PM2.5检测浓度","车外PM2.5检测浓度","空气质量状态","电子膨胀阀ID","电子膨胀阀当前位置",
    "PTC—ID","软件版本号","硬件版本号","负离子检测电压","噪音检测值"
};//Excel数据--江淮


QVector<QString> sqldata = { "序号","频道号","产品型号","日期","电检总结果","总成条码","错误代码","检测时间"};
QVector<QString> Allresults = {"鼓风机检测结果",
                               "LIN1-1检测结果","LIN1-2检测结果","LIN1-3检测结果","LIN1-4检测结果","LIN1-5检测结果","LIN1-6检测结果","LIN1-7检测结果","LIN1-8检测结果",
                               "LIN1-9检测结果","LIN1-10检测结果","LIN1-11检测结果","LIN1-12检测结果",
                               "M1电机检测结果","M2电机检测结果","M3电机检测结果","M4电机检测结果","M5电机检测结果","M6电机检测结果","M7电机检测结果","M8电机检测结果","M9电机检测结果",
                               "M10电机检测结果","M11电机检测结果","M12电机检测结果",
                               "温敏1检测结果","温敏2检测结果","温敏3检测结果","温敏4检测结果","温敏5检测结果","温敏6检测结果","温敏7检测结果","温敏8检测结果","温敏9检测结果","温敏10检测结果","温敏11检测结果","温敏12检测结果",
                               "PM2.5检测结果","AQS检测结果","电子膨胀阀检测结果","PTC检测结果","负离子检测结果","噪音检测结果","X轴检测结果","Y轴检测结果","Z轴检测结果"};
QVector<QString> sqldata1Blower = { "鼓风机频率","鼓风机硬件版本号","鼓风机软件版本号",
                                    "鼓风机POS1转速/占空比/电压","鼓风机POS1电流","鼓风机POS2转速/占空比/电压","鼓风机POS2电流","鼓风机POS3转速/占空比/电压","鼓风机POS3电流",
                                    "鼓风机POS4转速/占空比/电压","鼓风机POS4电流","鼓风机POS5转速/占空比/电压","鼓风机POS5电流","鼓风机POS6转速/占空比/电压","鼓风机POS6电流",
                                    "鼓风机POS7转速/占空比/电压","鼓风机POS7电流","鼓风机POS8转速/占空比/电压","鼓风机POS8电流","鼓风机POS9转速/占空比/电压","鼓风机POS9电流"};

QVector<QString> sqldataVibration = {  "鼓风机1档X轴振动值","鼓风机2档X轴振动值","鼓风机3档X轴振动值","鼓风机4档X轴振动值","鼓风机5档X轴振动值","鼓风机6档X轴振动值","鼓风机7档X轴振动值","鼓风机8档X轴振动值","鼓风机9档X轴振动值",
                                       "鼓风机1档Y轴振动值","鼓风机2档Y轴振动值" ,"鼓风机3档Y轴振动值","鼓风机4档Y轴振动值","鼓风机5档Y轴振动值","鼓风机6档Y轴振动值","鼓风机7档Y轴振动值","鼓风机8档Y轴振动值","鼓风机9档Y轴振动值",
                                       "鼓风机1档Z轴振动值","鼓风机2档Z轴振动值" ,"鼓风机3档Z轴振动值","鼓风机4档Z轴振动值","鼓风机5档Z轴振动值","鼓风机6档Z轴振动值","鼓风机7档Z轴振动值","鼓风机8档Z轴振动值","鼓风机9档Z轴振动值",
                                       "鼓风机1档单轴振动值","鼓风机2档单轴振动值" ,"鼓风机3档单轴振动值","鼓风机4档单轴振动值","鼓风机5档单轴振动值","鼓风机6档单轴振动值","鼓风机7档单轴振动值","鼓风机8档单轴振动值","鼓风机9档单轴振动值",
                                       "鼓风机1档噪音检测值","鼓风机2档噪音检测值","鼓风机3档噪音检测值","鼓风机4档噪音检测值","鼓风机5档噪音检测值","鼓风机6档噪音检测值","鼓风机7档噪音检测值","鼓风机8档噪音检测值","鼓风机9档噪音检测值"
                                    };


QVector<QString> LIN1NAD = { "LIN1-1NAD","LIN1-2NAD","LIN1-3NAD", "LIN1-4NAD","LIN1-5NAD","LIN1-6NAD","LIN1-7NAD","LIN1-8NAD","LIN1-9NAD","LIN1-10NAD","LIN1-11NAD","LIN1-12NAD"};
QVector<QString> LIN1StateID = {"LIN1-1状态ID","LIN1-2状态ID","LIN1-3状态ID","LIN1-4状态ID","LIN1-5状态ID","LIN1-6状态ID","LIN1-7状态ID","LIN1-8状态ID","LIN1-9状态ID","LIN1-10状态ID","LIN1-11状态ID","LIN1-12状态ID"};
QVector<QString> LIN1ControlID = {"LIN1-1控制ID","LIN1-2控制ID","LIN1-3控制ID","LIN1-4控制ID","LIN1-5控制ID","LIN1-6控制ID","LIN1-7控制ID","LIN1-8控制ID","LIN1-9控制ID","LIN1-10控制ID","LIN1-11控制ID","LIN1-12控制ID"};

QVector<QString> sqldataLIN1data = {"LIN1_1电机名称","LIN1_1电机步数汇总","LIN1_2电机名称","LIN1_2电机步数汇总","LIN1_3电机名称","LIN1_3电机步数汇总",
                                    "LIN1_4电机名称","LIN1_4电机步数汇总","LIN1_5电机名称","LIN1_5电机步数汇总","LIN1_6电机名称","LIN1_6电机步数汇总",
                                    "LIN1_7电机名称","LIN1_7电机步数汇总","LIN1_8电机名称","LIN1_8电机步数汇总","LIN1_9电机名称","LIN1_9电机步数汇总",
                                    "LIN1_10电机名称","LIN1_10电机步数汇总","LIN1_11电机名称","LIN1_11电机步数汇总","LIN1_12电机名称","LIN1_12电机步数汇总",
                                    "LIN1_1自学习极限步数1","LIN1_1自学习极限步数2","LIN1_2自学习极限步数1","LIN1_2自学习极限步数2","LIN1_3自学习极限步数1","LIN1_3自学习极限步数2",
                                    "LIN1_4自学习极限步数1","LIN1_4自学习极限步数2","LIN1_5自学习极限步数1","LIN1_5自学习极限步数2","LIN1_6自学习极限步数1","LIN1_6自学习极限步数2",
                                    "LIN1_7自学习极限步数1","LIN1_7自学习极限步数2","LIN1_8自学习极限步数1","LIN1_8自学习极限步数2","LIN1_9自学习极限步数1","LIN1_9自学习极限步数2",
                                    "LIN1_10自学习极限步数1","LIN1_10自学习极限步数2","LIN1_11自学习极限步数1","LIN1_11自学习极限步数2","LIN1_12自学习极限步数1","LIN1_12自学习极限步数2"};

QVector<QString> sqldataPTdata ={ "M1电机名称","M1电机电压汇总","M1电机电流汇总","M2电机名称","M2电机电压汇总","M2电机电流汇总",
                                  "M3电机名称","M3电机电压汇总","M3电机电流汇总","M4电机名称","M4电机电压汇总","M4电机电流汇总",
                                  "M5电机名称","M5电机电压汇总","M5电机电流汇总","M6电机名称","M6电机电压汇总","M6电机电流汇总",
                                  "M7电机名称","M7电机电压汇总","M7电机电流汇总","M8电机名称","M8电机电压汇总","M8电机电流汇总",
                                  "M9电机名称","M9电机电压汇总","M9电机电流汇总","M10电机名称","M10电机电压汇总","M10电机电流汇总",
                                  "M11电机名称","M11电机电压汇总","M11电机电流汇总","M12电机名称","M12电机电压汇总","M12电机电流汇总"
                                };

QVector<QString> sqldataRes ={
    "室内环境温度","温敏1检测值","温敏2检测值","温敏3检测值","温敏4检测值","温敏5检测值",
    "温敏6检测值","温敏7检测值","温敏8检测值","温敏9检测值","温敏10检测值","温敏11检测值","温敏12检测值",
    "车内PM2.5检测浓度","车外PM2.5检测浓度","空气质量状态","电子膨胀阀ID","电子膨胀阀当前位置",
    "PTC—ID","软件版本号","硬件版本号","负离子检测电压","噪音检测值"
};



QVector<QString> sqldataSpeed ={
    "模式1风速1检测值","模式1风速2检测值","模式1风速3检测值","模式1风速4检测值","模式1风速5检测值","模式1风速6检测值","模式1风速7检测值","模式1风速8检测值","模式1风速9检测值","模式1风速10检测值","模式1风速11检测值","模式1风速12检测值",
    "模式2风速1检测值","模式2风速2检测值","模式2风速3检测值","模式2风速4检测值","模式2风速5检测值","模式2风速6检测值","模式2风速7检测值","模式2风速8检测值","模式2风速9检测值","模式2风速10检测值","模式2风速11检测值","模式2风速12检测值",
    "模式3风速1检测值","模式3风速2检测值","模式3风速3检测值","模式3风速4检测值","模式3风速5检测值","模式3风速6检测值","模式3风速7检测值","模式3风速8检测值","模式3风速9检测值","模式3风速10检测值","模式3风速11检测值","模式3风速12检测值",
    "模式4风速1检测值","模式4风速2检测值","模式4风速3检测值","模式4风速4检测值","模式4风速5检测值","模式4风速6检测值","模式4风速7检测值","模式4风速8检测值","模式4风速9检测值","模式4风速10检测值","模式4风速11检测值","模式4风速12检测值",
    "模式5风速1检测值","模式5风速2检测值","模式5风速3检测值","模式5风速4检测值","模式5风速5检测值","模式5风速6检测值","模式5风速7检测值","模式5风速8检测值","模式5风速9检测值","模式5风速10检测值","模式5风速11检测值","模式5风速12检测值",
    "模式6风速1检测值","模式6风速2检测值","模式6风速3检测值","模式6风速4检测值","模式6风速5检测值","模式6风速6检测值","模式6风速7检测值","模式6风速8检测值","模式6风速9检测值","模式6风速10检测值","模式6风速11检测值","模式6风速12检测值",
    "模式7风速1检测值","模式7风速2检测值","模式7风速3检测值","模式7风速4检测值","模式7风速5检测值","模式7风速6检测值","模式7风速7检测值","模式7风速8检测值","模式7风速9检测值","模式7风速10检测值","模式7风速11检测值","模式7风速12检测值",
    "模式8风速1检测值","模式8风速2检测值","模式8风速3检测值","模式8风速4检测值","模式8风速5检测值","模式8风速6检测值","模式8风速7检测值","模式8风速8检测值","模式8风速9检测值","模式8风速10检测值","模式8风速11检测值","模式8风速12检测值",
};


int reszult = 0;//记录追溯结果
QByteArray ECUmode,ECUAPP,ECUBOOT,ECUyingjianbanben;//条码,型号
QString shangxianma,xinghao,liushuihao,Inplacetimes,Alarmdata;
QString liushuihao_flag,liushuihao_OKflag;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mutualui = this;

    ui->Auto_ManualNG->hide();


    qRegisterMetaType<Blower_Setting_basis>("Blower_Setting_basis");
    qRegisterMetaType<Blower_Setting_basis1>("Blower_Setting_basis1");
    m_Form_ModeBusRtu = new MForm_ModeBusRtu();

    NFormLogShow = FormLogShow::getInstance();
    NFormLogShow->show();
    NFormLogShow->addLog("主窗口","初始化");

    Nthread_ptmotor = thread_ptmotor::getInstance();

    m_Blower = MBlower::getInstance();
    connect(this, &MainWindow::sign_BlowerFixedPar, m_Blower, &MBlower::slot_BlowerFixedPar);
    //    connect(this, &MainWindow::sign_BlowerStop, m_Blower, &MBlower::slot_BlowerStop);
    //    connect(this, &MainWindow::sign_BlowerContinue, m_Blower, &MBlower::slot_BlowerContinue);
    //    connect(m_Blower, &MBlower::sign_setled, this, &MainWindow::slot_setled);


    initUIControlArrays();

    //    QGridLayout *lll = new QGridLayout;

    m_FormMotor[0] = new MFormMotor(nullptr, "PT1",0);
    m_FormMotor[1] = new MFormMotor(nullptr, "PT2",0);
    m_FormMotor[2] = new MFormMotor(nullptr, "PT3",0);
    m_FormMotor[3] = new MFormMotor(nullptr, "PT4",0);
    m_FormMotor[4] = new MFormMotor(nullptr, "PT5",0);
    m_FormMotor[5] = new MFormMotor(nullptr, "PT6",0);
    m_FormMotor[6] = new MFormMotor(nullptr, "PT7",0);
    m_FormMotor[7] = new MFormMotor(nullptr, "PT8",0);
    m_FormMotor[8] = new MFormMotor(nullptr, "PT9",0);
    m_FormMotor[9] = new MFormMotor(nullptr, "PT10",0);
    m_FormMotor[10] = new MFormMotor(nullptr, "PT11",0);
    m_FormMotor[11] = new MFormMotor(nullptr, "PT12",0);

    m_FormLinMotor[0] = new MFormMotor(nullptr, "LIN1",1);
    m_FormLinMotor[1] = new MFormMotor(nullptr, "LIN2",1);
    m_FormLinMotor[2] = new MFormMotor(nullptr, "LIN3",1);
    m_FormLinMotor[3] = new MFormMotor(nullptr, "LIN4",1);
    m_FormLinMotor[4] = new MFormMotor(nullptr, "LIN5",1);
    m_FormLinMotor[5] = new MFormMotor(nullptr, "LIN6",1);
    m_FormLinMotor[6] = new MFormMotor(nullptr, "LIN7",1);
    m_FormLinMotor[7] = new MFormMotor(nullptr, "LIN8",1);
    m_FormLinMotor[8] = new MFormMotor(nullptr, "LIN9",1);
    m_FormLinMotor[9] = new MFormMotor(nullptr, "LIN10",1);
    m_FormLinMotor[10] = new MFormMotor(nullptr, "LIN11",1);
    m_FormLinMotor[11] = new MFormMotor(nullptr, "LIN12",1);

    ui->gridLayout->addWidget(m_FormMotor[0] ,0, 0);
    ui->gridLayout->addWidget(m_FormMotor[1] , 0, 1);
    ui->gridLayout->addWidget(m_FormMotor[2] , 0, 2);
    ui->gridLayout->addWidget(m_FormMotor[3] , 0, 3);
    ui->gridLayout->addWidget(m_FormMotor[4] , 0, 4);
    ui->gridLayout->addWidget(m_FormMotor[5] , 0, 5);
    ui->gridLayout->addWidget(m_FormMotor[6] , 1, 0);
    ui->gridLayout->addWidget(m_FormMotor[7] , 1, 1);
    ui->gridLayout->addWidget(m_FormMotor[8] , 1, 2);
    ui->gridLayout->addWidget(m_FormMotor[9] , 1, 3);
    ui->gridLayout->addWidget(m_FormMotor[10], 1, 4);
    ui->gridLayout->addWidget(m_FormMotor[11], 1, 5);

    ui->gridLayout->addWidget(m_FormLinMotor[0] ,2, 0);
    ui->gridLayout->addWidget(m_FormLinMotor[1] ,2, 1);
    ui->gridLayout->addWidget(m_FormLinMotor[2] ,2, 2);
    ui->gridLayout->addWidget(m_FormLinMotor[3] ,2, 3);
    ui->gridLayout->addWidget(m_FormLinMotor[4] ,2, 4);
    ui->gridLayout->addWidget(m_FormLinMotor[5] ,2, 5);
    ui->gridLayout->addWidget(m_FormLinMotor[6] ,3, 0);
    ui->gridLayout->addWidget(m_FormLinMotor[7] ,3, 1);
    ui->gridLayout->addWidget(m_FormLinMotor[8] ,3, 2);
    ui->gridLayout->addWidget(m_FormLinMotor[9] ,3, 3);
    ui->gridLayout->addWidget(m_FormLinMotor[10], 3, 4);
    ui->gridLayout->addWidget(m_FormLinMotor[11], 3, 5);



    //    ui->groupBox_23->setLayout(lll);
    
    //----临时----
    //     this->showFullScreen();//全屏显示
    //    QDesktopWidget *desktop = QApplication::desktop();
    QDesktopWidget ww;
    
    //     this->setGeometry(ww.screenGeometry(1));//显示在分屏界面
    //     QList<QScreen *> screenList = QGuiApplication::screens();
    //         QRec5t rect = screenList[0]->geometry();
    //     ww.setGeometry(rect);


    Class_Init();//界面类初始化

    Main_Init();//界面初始化
    //    Connect_Init();//槽函数初始化

    Excelinit();//Excel初始化
    MySql_Init();//数据库初始化
    testsqlinit();//将数据参数全赋0
    ini_file().Set_Control("Null",QString::number(1));
    qRegisterMetaType<QVector<QString>>("QVector<QString>");//注册
    qRegisterMetaType<QVector<int>>("QVector<int>");//注册
    Update_Number();//开始访问一下数据库

    //    setVoltageToolTip(0, ui->M1_Motor_POS1,"1.26V","0.023A","1.28V","1.24V");
    ui->tabWidget->setStyleSheet("QTabWidget::pane { border: none; }QTabBar::tab { height: 0px; width: 0px; margin: 0px; padding: 0px; border: none; }");

}

void MainWindow::setVoltageToolTip(int index,QWidget* widget, const QString& positionV, const QString& positionA,const QString& upperLimit, const QString& lowerLimit)
{
    if(index==0)
    {
        widget->setToolTip(QString("运行电压:%1\n运行电流:%1\n电压上限:%2\n电压下限:%3").arg(positionV,positionA,upperLimit,lowerLimit));
    }
    else if(index==1)
    {
        widget->setToolTip(QString("电流值:%1\n电流上限:%2\n电流下限:%3").arg(positionV,upperLimit,lowerLimit));
    }
    else if(index==2)
    {
        widget->setToolTip(QString("转速值:%1\n转速上限:%2\n转速下限:%3").arg(positionV,upperLimit,lowerLimit));
    }
    else if(index==3)
    {
        widget->setToolTip(QString("震动值:%1\n震动上限:%2\n震动下限:%3").arg(positionV,upperLimit,lowerLimit));
    }
    else if(index==4)
    {
        widget->setToolTip(QString("噪音值:%1\n噪音上限:%2\n噪音下限:%3").arg(positionV,upperLimit,lowerLimit));
    }
    else if(index==5)
    {
        widget->setToolTip(QString("风速值:%1\n风速上限:%2\n风速下限:%3").arg(positionV,upperLimit,lowerLimit));
    }
    else if(index==6)
    {
        widget->setToolTip(QString("温度值:%1\n温度上限:%2\n温度下限:%3").arg(positionV,upperLimit,lowerLimit));
    }
}

MainWindow::~MainWindow()
{
    // 清理所有串口
    for (int portIndex : m_threads.keys()) {
        closeSerialConnection(portIndex);
    }
    delete ui;
}

void MainWindow::closeSerialConnection(int portIndex)
{
    if (m_threads.contains(portIndex) && m_threads[portIndex]->isRunning()) {
        // 通过信号触发工作对象的关闭串口操作
        QMetaObject::invokeMethod(m_workers[portIndex], &SerialPortWorker::closeSerialPort, Qt::QueuedConnection);

        // 退出线程
        m_threads[portIndex]->quit();
        m_threads[portIndex]->wait();

        // 从映射表中移除
        m_workers.remove(portIndex);
        m_threads.remove(portIndex);
        m_serialOpened.remove(portIndex);


        ui->textEdit->append(tr("串口连接 %1 已关闭").arg(portIndex));

    }
}

void MainWindow::onDataReceived(const QByteArray &data, int portIndex)
{
    // 在主线程中更新UI，显示接收到的数据
    QString displayText = QString::fromLocal8Bit(data);
    ui->textEdit->append(tr("从串口 %1 收到 %2 字节数据").arg(portIndex).arg(data.size()));
    qDebug() << "Data from port" << portIndex << ":" << displayText;
}

void MainWindow::onErrorOccurred(const QString &errorString, int portIndex)
{
    QMessageBox::warning(this, tr("串口错误"), tr("串口 %1 错误: %2").arg(portIndex).arg(errorString));
}

void MainWindow::Class_Init()
{
    SetSystemDataWindow = new SystemDataSet();
    Heart_error = new Communicationerror();
    //    PLC_Connet = new PLC_MC();//PLC通讯连接

    //    connect(PLC_Connet , &PLC_MC::Heraterr, this , &MainWindow::show_Err);



    DayTimer = new QTimer(this);
    connect(DayTimer,SIGNAL(timeout()),this,SLOT(UpdateTime()));
    DayTimer->start(1000);

    showLogo = new showpicture();//联系我们界面
    Aboutware = new AboutSoftware();//关于软件界面
    Pop_OK = new Pop_ups_OK();//OK界面
    Pop_NG = new Pop_ups_NG();//NG界面
    Pop_Alarm = new Pop_ups_Alarm();//报警弹窗
    HVAC_Modelist = new HVAC_Mode();//参数列表界面
    
    m_RFID_Dialog = new mRFID_Dialog();
    m_COMRFID->Init_port();
    Data_Set = new DataSetting();//频道配置界面
    Manualui_Main = new Manualui();//手动界面
    connect(Data_Set, &DataSetting::connectRequested,this,&MainWindow::onSerialConnectRequested);



    //    connect(PLC_Connet , &PLC_MC::test, this , &MainWindow::Update_show);
    //    connect(PLC_Connet , &PLC_MC::SendZSdata, this , &MainWindow::Data_Processing);
    //    connect(PLC_Connet , &PLC_MC::InPlaceTime, this , &MainWindow::Data_InPlaceTime);
    //    connect(PLC_Connet , &PLC_MC::SendManualData, Manualui_Main , &Manualui::Update_show);
    //    connect(this , &MainWindow::Sign_Start_detection, PLC_Connet , &PLC_MC::SetWriteCommand);
    //    connect(Manualui_Main , &Manualui::Sign_Set_PLCdata, PLC_Connet , &PLC_MC::SetWriteCommand);
    //    connect(Pop_OK , &Pop_ups_OK::Sign_Set_OK, PLC_Connet , &PLC_MC::SetWriteCommandPoint);
    //    connect(Pop_NG , &Pop_ups_NG::Sign_Set_NG, PLC_Connet , &PLC_MC::SetWriteCommandPoint);
    //    connect(this , &MainWindow::Sign_Start_detectionPoint, PLC_Connet , &PLC_MC::SetWriteCommandPoint);
    //    connect(Data_Set , &DataSetting::Sign_Set_PLCdataPoint, PLC_Connet , &PLC_MC::SetWriteCommandPoint);
    
    //    connect(Manualui_Main , &Manualui::Sign_Current_interface_flag, this , &MainWindow::Thread_Qtimer);
    //    connect(Data_Set , &DataSetting::Sign_Current_interface_flag, this , &MainWindow::Thread_Qtimer);
    //    connect(Data_Set , &DataSetting::Sign_Set_PLCdata, PLC_Connet , &PLC_MC::SetWriteCommand);
    //    connect(Data_Set , &DataSetting::Sign_Set_PLCWriteMode, PLC_Connet , &PLC_MC::Stop_ReadPLC);
    //    connect(Data_Set , &DataSetting::Sign_Set_PLCReadMode, PLC_Connet , &PLC_MC::Start_ReadPLC);
    //    connect(HVAC_Modelist , &HVAC_Mode::Sign_Set_PLCData, PLC_Connet , &PLC_MC::SetWriteCommand);
    //    connect(HVAC_Modelist , &HVAC_Mode::Sign_Set_PLCDataPoint, PLC_Connet , &PLC_MC::SetWriteCommandPoint);

    pressTimer = new QTimer(this);
    pressTimer->setInterval(2000); // 设置计时器为 1 秒
    pressTimer->setSingleShot(true); // 单次触发

    // 连接按钮的 pressed 和 released 信号
    connect(ui->MandatoryLetgo, &QPushButton::pressed, this, &MainWindow::onButtonPressed);
    connect(ui->MandatoryLetgo, &QPushButton::released, this, &MainWindow::onButtonReleased);
    connect(pressTimer, &QTimer::timeout, this, &MainWindow::onLongPress);

    CommunicationTimer = new QTimer(this);
    CommunicationTimer->setSingleShot(true);
    connect(CommunicationTimer, &QTimer::timeout, this, &MainWindow::CommunicationTimes);





    Nthread_CommTask[0] = new thread_CommTask();
    Nthread_CommTask[0]->my_portIndex = 0;
    //    Nthread_CommTask[0]->start();

    Nthread_CommTask[1] = new thread_CommTask();
    Nthread_CommTask[1]->my_portIndex = 1;
    //    Nthread_CommTask[1]->start();

    Nthread_CommTask[2] = new thread_CommTask();
    Nthread_CommTask[2]->my_portIndex = 2;
    //    Nthread_CommTask[2]->start();

    // 创建线程和工作对象
    workerThread = new QThread(this);

    //LIN
    Nthread_linmotor = thread_linmotor::getInstance();
    Nthread_linmotor->start();

    //温敏
    Nthread_Thermistor = thread_Thermistor::getInstance();
    Nthread_Thermistor->start();

    // 将工作对象移动到线程中
    Nthread_ptmotor->moveToThread(workerThread);


    // 连接信号和槽
    connect(workerThread, &QThread::started, Nthread_ptmotor, &thread_ptmotor::doWork);
    connect(Nthread_ptmotor, &thread_ptmotor::workFinished, workerThread, &QThread::quit);
    connect(Nthread_ptmotor, &thread_ptmotor::workFinished, Nthread_ptmotor, &thread_ptmotor::deleteLater);
    connect(workerThread, &QThread::finished, workerThread, &QThread::deleteLater);

    connect(this, &MainWindow::testRunMotor, Nthread_ptmotor, &thread_ptmotor::ReceiveRunMotor);
    // 启动线程
    //    workerThread->start();


    Nthread_main = new thread_main();


    connect(Nthread_main, &thread_main::Sign_ShowUI_Step, this, &MainWindow::Slot_ShowUI_Step);
    connect(Nthread_main, &thread_main::Sign_ShowUI_Results, this, &MainWindow::Slot_ShowUI_Results);

    connect(Nthread_main, &thread_main::Sign_Run_Start, this, &MainWindow::on_Auto_Start_clicked);
    connect(Nthread_main, &thread_main::Sign_Run_Reset, this, &MainWindow::on_Auto_Reset_clicked);
    connect(Nthread_main, &thread_main::Sign_Run_Stop, this, &MainWindow::on_MandatoryLetgo_clicked);


    if(! Data_Set->ui->Serial_Number->currentText().isEmpty()&& Data_Set->ui->Baud_rate->value()!=0)
    {
        Data_Set->ui->Start_Connect->click();
    }
    if(! Data_Set->ui->Serial_Number2->currentText().isEmpty()&& Data_Set->ui->Baud_rate_2->value()!=0)
    {
        Data_Set->ui->Start_Connect_2->click();
    }
    if(! Data_Set->ui->Serial_Number3->currentText().isEmpty()&& Data_Set->ui->Baud_rate_3->value()!=0)
    {
        Data_Set->ui->Start_Connect_3->click();
    }

    workerThread->start();

    ShowUI_DataTimer = new QTimer(this);
    connect(ShowUI_DataTimer,SIGNAL(timeout()),this,SLOT(Slot_ShowUI_Data()));
    ShowUI_DataTimer->start(100);
    Nthread_main->start();



    //    QThread::msleep(5000);

    //消费线程开始
    Nthread_CommTask[0]->start();
    Nthread_CommTask[1]->start();
}

void MainWindow::onSerialConnectRequested(const QString &portName, qint32 baudRate,QSerialPort::DataBits dataBits,QSerialPort::Parity parity,QSerialPort::StopBits stopBits)
{
    // 创建串口连接
    createSerialConnection(portName, baudRate, dataBits, parity, stopBits);
}

void MainWindow::createSerialConnection(const QString &portName, qint32 baudRate, QSerialPort::DataBits dataBits,QSerialPort::Parity parity,QSerialPort::StopBits stopBits)
{
    int portIndex = m_nextPortIndex++;

    // 创建线程和工作对象
    QThread *thread = new QThread(this);
    SerialPortWorker *worker = new SerialPortWorker(portIndex);

    // 设置参数
    worker->updateSerialParameters(portName, baudRate, dataBits, parity, stopBits);

    // 将工作对象移动到线程
    worker->moveToThread(thread);

    // 连接信号槽
    connect(thread, &QThread::started, worker, &SerialPortWorker::initSerialPort);
    connect(worker, &SerialPortWorker::dataReceived, this, &MainWindow::onDataReceived);
    connect(worker, &SerialPortWorker::errorOccurred, this, &MainWindow::onErrorOccurred);
    connect(worker, &SerialPortWorker::serialOpened, this, &MainWindow::onSerialOpened);
    connect(worker, &SerialPortWorker::serialClosed, this, &MainWindow::onSerialClosed);
    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(worker, &SerialPortWorker::ptMotorDataReceived, Nthread_ptmotor, &thread_ptmotor::Receive_DataProcessing);

    connect(worker, &SerialPortWorker::blowerDataReceived, m_Blower, &MBlower::slot_RecivceDatas);
    connect(worker, &SerialPortWorker::linMotorDataReceived, Nthread_linmotor, &thread_linmotor::DataProcessing);

    connect(worker, &SerialPortWorker::thermistorDataReceived, Nthread_Thermistor, &thread_Thermistor::DataProcessing);

    // 保存到映射表
    m_workers[portIndex] = worker;
    m_threads[portIndex] = thread;
    m_serialOpened[portIndex] = false;

    //thread_CommTask Nthread_CommTask


    if(portIndex == 1){
        connect(worker, &SerialPortWorker::Data_return, this,[=](int _num) {
            //            _num = _num - 1;
            if(_num == 0)
            {

                Nthread_CommTask[0]->Send_finish=true;
            }else if(_num == 1){
                Nthread_CommTask[1]->Send_finish=true;
            }else if(_num == 2){
                Nthread_CommTask[2]->Send_finish=true;
            }
            qDebug()<<"Nthread_CommTask->Send_finish=true;"<<_num;
        });
        connect(Nthread_CommTask[0], &thread_CommTask::SendData_Board1, worker, &SerialPortWorker::writeData);
    }else if(portIndex == 2){
        connect(worker, &SerialPortWorker::Data_return, this,[=](int _num) {
            Nthread_CommTask[1]->Send_finish=true;
            if(_num == 0)
            {
                Nthread_CommTask[0]->Send_finish=true;
            }else if(_num == 1){
                Nthread_CommTask[1]->Send_finish=true;
            }else if(_num == 2){
                Nthread_CommTask[2]->Send_finish=true;
            }
            qDebug()<<"Nthread_CommTask->Send_finish=true;"<<_num;
        });
        connect(Nthread_CommTask[1], &thread_CommTask::SendData_Board2, worker, &SerialPortWorker::writeData);
    }else if(portIndex == 3){
        connect(worker, &SerialPortWorker::Data_return, this,[=](int _num) {
            Nthread_CommTask[2]->Send_finish=true;
            if(_num == 0)
            {
                Nthread_CommTask[0]->Send_finish=true;
            }else if(_num == 1){
                Nthread_CommTask[1]->Send_finish=true;
            }else if(_num == 2){
                Nthread_CommTask[2]->Send_finish=true;
            }
            qDebug()<<"Nthread_CommTask->Send_finish=true;"<<_num;
        });
        connect(Nthread_CommTask[2], &thread_CommTask::SendData_Board3, worker, &SerialPortWorker::writeData);
    }
    // 启动线程
    thread->start();
}

void MainWindow::CommunicationTimes()
{
    emit Sign_Start_detectionPoint("M",4022,0);
    ui->Auto_heart_Stop->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #fdfd7e, stop: 1 #fdfd7e);"
                                       "border: 3px solid #848484;"
                                       " border-radius: 20%;");
}
void MainWindow::show_Err()
{
    Heart_error->show();
    qDebug()<<"开始显示NG界面";
}
void MainWindow::Data_InPlaceTime()
{

}

void MainWindow::Thread_Qtimer(int index)//控制线程是否启动定时
{
    if(index == 1)
    {
        //        PLC_Connet->ManualTimer->stop();
        //        PLC_Connet->testTimer->start();
    }
    else if(index == 2)
    {
        //        PLC_Connet->ReadSetDataTimer->stop();
        //        PLC_Connet->testTimer->start();
    }
}

void MainWindow::Main_Init()
{
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);
    for(int i = 1;i<31;i++)
    {
        ui->Auto_PDbox->addItems({QString::number(i)});//频道
    }
    //    ui->Auto_PDbox->blockSignals(true);//阻塞掉函数
    //    ui->pushButton_6->hide();//测试按钮
}

// 3.  创建多级文件夹
QString MainWindow::createMultipleFolders(const QString path)
{
    QDir dir(path);
    if (dir.exists(path)) {
        
        qDebug()<<"创建Excel存储文件路径"<<path;
        return path;
    }
    
    QString parentDir = createMultipleFolders(path.mid(0, path.lastIndexOf('\\')));//截取根目录
    QString dirName = path.mid(path.lastIndexOf('\\') + 1);//截取父目录
    
    QDir parentPath(parentDir);
    if (!dirName.isEmpty())
    {
        parentPath.mkpath(dirName);
    }
    
    return parentDir + "\\" + dirName;
}

void MainWindow::Excelinit()
{
    QString path = QApplication::applicationDirPath() + "/System/System.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    if(INI_File->value("DataSavePath").toString().isEmpty())
    {
        QMessageBox::information(this, "提示", "软件的默认存储未配置，默认情况下存储在C盘中");
        INI_File->setValue("DataSavePath","C:");
        
    }

    QDateTime time = QDateTime::currentDateTime();
    QString SaveDataPath =INI_File->value("DataSavePath").toString().replace(QString("/"), QString("//"))+QString("\\%1\\screenshot").arg(time.toString("yyyy-MM-dd"));
    createMultipleFolders(SaveDataPath);
    QString newexcel = time.toString("yyyy-MM-dd");
    //    qDebug()<<time.toString("yyyy-MM-dd");
    QString excelname = INI_File->value("DataSavePath").toString().replace(QString("/"), QString("//"))+ QString("\\%1\\%2.xlsx").arg(newexcel,newexcel);
    
    
    if (QFile::exists(excelname))
    {
        qDebug()<<"文件存在";
    }
    else
    {
        InitialValue = 2;
        QXlsx::Document xlsx(excelname);
        //        qDebug()<<"Exceldata2"<<Exceldata2.count();
        for(int i = 0;i<Exceldata2.count();i++)
        {
            xlsx.write(1,1+i,Exceldata2[i]);
        }
        INI_File->setValue("InitialValue",QString::number(InitialValue));
        xlsx.save();
    }
    INI_File->destroyed();
}

void MainWindow::slot_Get_uplineCode(const QString rfid)//获取工位历史数据
{
    //    if(!B_Connect){
    //    qDebug() << "开始查询产品是否有上线码";
    //        return;
    //    }
    QString str1;
    if(rfid.mid(0,1)=='E')
    {
        str1 = "SELECT 返修码 FROM jianghuai_songz.rfid_to_uplinecode " + tr("WHERE 流水号='%1'").arg(rfid);
    }
    else if(rfid.mid(0,1)=='A')
    {
        str1 = "SELECT 上线码 FROM jianghuai_songz.rfid_to_uplinecode " + tr("WHERE 流水号='%1'").arg(rfid);
    }
    
    QSqlQuery query(Sqlserverdb);
    query.prepare(str1);
    //    qDebug()<<"查询语句"<<str1;
    if(!query.exec()){
        //        QString mesg = tr("搜索 产品上线码 失败，语法：%1").arg(str1);
        //        qDebug() << mesg;
    }else{
        QString upline_code;
        while(query.next()){
            //            qDebug()<<query.value(0).toString();
            upline_code = query.value(0).toString();
        }
        if(upline_code == ""){
            ui->Auto_Code->setText(upline_code);
            //            Data_Set->ui->textEdit->append("产品未有上线码");
            shangxianma = upline_code;
            //            qDebug()<<"产品未有上线码";
        }else{
            ui->Auto_Code->setText(upline_code);
            shangxianma = upline_code.toLatin1();
            //            qDebug()<<"产品已有上线码"+shangxianma;
        }
    }
}

void MainWindow::Update_Number()
{
    QString PD = ui->Auto_PDbox->currentText();
    QSqlQuery query(Sqlserverdb);
    QString sql = QString("SELECT 计划生产数量 FROM jianghuai_songz.plan_number WHERE 频道号 = %1").arg(PD);
    if (!query.exec(sql))
    {
        qDebug() << "计划生产数量查询错误:" << query.lastError().text();
    }
    // 3. 获取查询结果
    if (query.next())
    {
        QVariant value = query.value(0); // 获取第一列的数据
        ui->Auto_OKNum->setValue(value.toInt());//计划生产数量
    }

    sql = QString("SELECT 电检OK数量 FROM jianghuai_songz.plan_number WHERE 频道号 = %1").arg(PD);
    if (!query.exec(sql))
    {
        qDebug() << "电检OK数量查询错误:" << query.lastError().text();
    }
    // 3. 获取查询结果
    if (query.next())
    {
        QVariant value = query.value(0); // 获取第一列的数据
        ui->Auto_NGNum->setValue(value.toInt());//计划生产数量
    }

}

void MainWindow::MySql_Init()
{
    //Sqlserverdb = QSqlDatabase::addDatabase("QODBC");   //数据库驱动类型为SQL Server
    Sqlserverdb = QSqlDatabase::addDatabase("QODBC","connection2");
    QString dsn = QString::fromLocal8Bit("DJ_ZS_Datas");      //数据源名称
    Sqlserverdb.setHostName("192.168.10.200");                        //选择本地主机，127.0.1.1
    Sqlserverdb.setDatabaseName(dsn);                            //设置数据源名称
    Sqlserverdb.setUserName("admin2");                               //登录用户
    Sqlserverdb.setPassword("123456");                           //密码
    if (!Sqlserverdb.open())                                     //打开数据库，密码自己设置
    {
        qDebug() << "MySql数据库打开失败" << Sqlserverdb.lastError().text();
    }
    else
    {
        qDebug() << "MySql数据库打开成功" << Sqlserverdb.lastError().text();
        QSqlQuery query(Sqlserverdb);
        //        qDebug()<<"创建数量:"<<MySql_Create.count();
        
        for(int i=0;i<MySql_Create.count();i++)
        {
            //            qDebug()<<(QString(MySql_Create[i]).arg(MySql_TableName[i]));
            qDebug()<<QString("创建数据库'%1'表格").arg(MySql_TableName[i]);
            query.exec(QString(MySql_Create[i]).arg(MySql_TableName[i]));
        }
    }
    //    for(int i=0;i<MySql_Create.count();i++)
    //    {
    //        qDebug()<<(QString(MySql_Create[i]).arg(MySql_TableName[i]));
    //    }
}

void MainWindow::Save_MySql()
{
    
    qDebug()<<"数据库开始存储";
    QMap<QString,QString> m_map; //定义一个QMap对象
    m_map.insert("序号", sqldata[0]); //向map里添加一对“键-值”
    m_map.insert("频道号", sqldata[1]); //向map里添加一对“键-值”
    m_map.insert("产品型号", sqldata[2]); //向map里添加一对“键-值”
    m_map.insert("日期", sqldata[3]); //向map里添加一对“键-值”
    m_map.insert("电检总结果", sqldata[4]); //向map里添加一对“键-值”
    m_map.insert("总成条码", sqldata[5]); //向map里添加一对“键-值”
    m_map.insert("错误代码", sqldata[6]); //向map里添加一对“键-值”
    m_map.insert("检测时间", sqldata[7]); //向map里添加一对“键-值”

    m_map.insert("鼓风机检测结果", Allresults[0]); //向map里添加一对“键_值”
    m_map.insert("LIN1_1检测结果", Allresults[1]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2检测结果", Allresults[2]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3检测结果", Allresults[3]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4检测结果", Allresults[4]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5检测结果", Allresults[5]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6检测结果", Allresults[6]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7检测结果", Allresults[7]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8检测结果", Allresults[8]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9检测结果", Allresults[9]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10检测结果", Allresults[10]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11检测结果", Allresults[11]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12检测结果", Allresults[12]); //向map里添加一对“键_值”

    m_map.insert("M1电机检测结果", Allresults[13]); //向map里添加一对“键_值”
    m_map.insert("M2电机检测结果", Allresults[14]); //向map里添加一对“键-值”
    m_map.insert("M3电机检测结果", Allresults[15]); //向map里添加一对“键-值”
    m_map.insert("M4电机检测结果", Allresults[16]); //向map里添加一对“键-值”
    m_map.insert("M5电机检测结果", Allresults[17]); //向map里添加一对“键-值”
    m_map.insert("M6电机检测结果", Allresults[18]); //向map里添加一对“键-值”
    m_map.insert("M7电机检测结果", Allresults[19]); //向map里添加一对“键-值”
    m_map.insert("M8电机检测结果", Allresults[20]); //向map里添加一对“键-值”
    m_map.insert("M9电机检测结果", Allresults[21]); //向map里添加一对“键-值”
    m_map.insert("M10电机检测结果", Allresults[22]); //向map里添加一对“键-值”
    m_map.insert("M11电机检测结果", Allresults[23]); //向map里添加一对“键-值”
    m_map.insert("M12电机检测结果", Allresults[24]); //向map里添加一对“键-值”

    m_map.insert("温敏1检测结果", Allresults[25]); //向map里添加一对“键-值”
    m_map.insert("温敏2检测结果", Allresults[26]); //向map里添加一对“键-值”
    m_map.insert("温敏3检测结果", Allresults[27]); //向map里添加一对“键-值”
    m_map.insert("温敏4检测结果", Allresults[28]); //向map里添加一对“键-值”
    m_map.insert("温敏5检测结果", Allresults[29]); //向map里添加一对“键-值”
    m_map.insert("温敏6检测结果", Allresults[30]); //向map里添加一对“键-值”
    m_map.insert("温敏7检测结果", Allresults[31]); //向map里添加一对“键-值”
    m_map.insert("温敏8检测结果", Allresults[32]); //向map里添加一对“键-值”
    m_map.insert("温敏9检测结果", Allresults[33]); //向map里添加一对“键-值”
    m_map.insert("温敏10检测结果", Allresults[34]); //向map里添加一对“键-值”
    m_map.insert("温敏11检测结果", Allresults[35]); //向map里添加一对“键-值”
    m_map.insert("温敏12检测结果", Allresults[36]); //向map里添加一对“键-值”

    m_map.insert("PM25检测结果", Allresults[37]); //向map里添加一对“键-值”
    m_map.insert("AQS检测结果", Allresults[38]); //向map里添加一对“键-值”
    m_map.insert("电子膨胀阀检测结果", Allresults[39]); //向map里添加一对“键-值”
    m_map.insert("PTC检测结果", Allresults[40]); //向map里添加一对“键-值”
    m_map.insert("负离子检测结果", Allresults[41]); //向map里添加一对“键-值”
    m_map.insert("噪音检测结果", Allresults[42]); //向map里添加一对“键-值”
    m_map.insert("X轴振动检测结果", Allresults[43]); //向map里添加一对“键-值”
    m_map.insert("Y轴振动检测结果", Allresults[44]); //向map里添加一对“键-值”
    m_map.insert("Z轴振动检测结果", Allresults[45]); //向map里添加一对“键-值”

    
    QMap<QString,QString>::iterator it; //遍历map
    QString data1,data2;
    data1 = "";
    data2 = "";
    for ( it = m_map.begin(); it != m_map.end(); ++it )
    {
        if(data1 == "")
        {
            data1 = it.key();
        }
        else
        {
            data1 += "," + it.key();
        }
        
        if(data2 == "")
        {
            data2 = "'" + it.value() + "'";
        }
        else
        {
            data2 += ",'" + it.value() + "'";
        }
        
    }
    data2 = data2.replace("'NULL'","NULL");

    QString str = QString("DELETE from jianghuai_songz.datas_linecode_d where 流水号 = '%1'").arg(sqldata[4]);
    Slots_MySql_exec(str);//发送到主控数据库追溯
    str = QString("insert into jianghuai_songz.datas_linecode_d(%1) values(%2)").arg(data1).arg(data2);
    Slots_MySql_exec(str);//发送到主控数据库追溯
    m_map.clear();
    
    m_map.insert("序号", sqldata[0]); //向map里添加一对“键-值”
    m_map.insert("频道号", sqldata[1]); //向map里添加一对“键-值”
    m_map.insert("产品型号", sqldata[2]); //向map里添加一对“键-值”
    m_map.insert("日期", sqldata[3]); //向map里添加一对“键-值”
    m_map.insert("电检总结果", sqldata[4]); //向map里添加一对“键-值”
    m_map.insert("总成条码", sqldata[5]); //向map里添加一对“键-值”
    m_map.insert("错误代码", sqldata[6]); //向map里添加一对“键-值”
    m_map.insert("检测时间", sqldata[7]); //向map里添加一对“键-值”
    
    m_map.insert("鼓风机频率", sqldata1Blower[0]); //向map里添加一对“键-值”"鼓风机硬件版本号","鼓风机软件版本号",
    m_map.insert("鼓风机硬件版本号", sqldata1Blower[1]); //向map里添加一对“键-值”
    m_map.insert("鼓风机软件版本号", sqldata1Blower[2]); //向map里添加一对“键-值”
    m_map.insert("鼓风机1档转速占空比端电压", sqldata1Blower[3]); //向map里添加一对“键-值”
    m_map.insert("鼓风机1档电流", sqldata1Blower[4]); //向map里添加一对“键-值”
    m_map.insert("鼓风机2档转速占空比端电压", sqldata1Blower[5]); //向map里添加一对“键-值”
    m_map.insert("鼓风机2档电流", sqldata1Blower[6]); //向map里添加一对“键-值”
    m_map.insert("鼓风机3档转速占空比端电压", sqldata1Blower[7]); //向map里添加一对“键-值”
    m_map.insert("鼓风机3档电流", sqldata1Blower[8]); //向map里添加一对“键-值”
    m_map.insert("鼓风机4档转速占空比端电压", sqldata1Blower[9]); //向map里添加一对“键-值”
    m_map.insert("鼓风机4档电流", sqldata1Blower[10]); //向map里添加一对“键-值”
    m_map.insert("鼓风机5档转速占空比端电压", sqldata1Blower[11]); //向map里添加一对“键-值”
    m_map.insert("鼓风机5档电流", sqldata1Blower[12]); //向map里添加一对“键-值”
    m_map.insert("鼓风机6档转速占空比端电压", sqldata1Blower[13]); //向map里添加一对“键-值”
    m_map.insert("鼓风机6档电流", sqldata1Blower[14]); //向map里添加一对“键-值”
    m_map.insert("鼓风机7档转速占空比端电压", sqldata1Blower[15]); //向map里添加一对“键-值”
    m_map.insert("鼓风机7档电流", sqldata1Blower[16]); //向map里添加一对“键-值”
    m_map.insert("鼓风机8档转速占空比端电压", sqldata1Blower[17]); //向map里添加一对“键-值”
    m_map.insert("鼓风机8档电流", sqldata1Blower[18]); //向map里添加一对“键-值”
    m_map.insert("鼓风机9档转速占空比端电压", sqldata1Blower[19]); //向map里添加一对“键-值”
    m_map.insert("鼓风机9档电流", sqldata1Blower[20]); //向map里添加一对“键-值”
    
    m_map.insert("鼓风机1档X轴振动值", sqldataVibration[0]); //向map里添加一对“键-值”
    m_map.insert("鼓风机2档X轴振动值", sqldataVibration[1]); //向map里添加一对“键-值”
    m_map.insert("鼓风机3档X轴振动值", sqldataVibration[2]); //向map里添加一对“键-值”
    m_map.insert("鼓风机4档X轴振动值", sqldataVibration[3]); //向map里添加一对“键-值”
    m_map.insert("鼓风机5档X轴振动值", sqldataVibration[4]); //向map里添加一对“键-值”
    m_map.insert("鼓风机6档X轴振动值", sqldataVibration[5]); //向map里添加一对“键-值”
    m_map.insert("鼓风机7档X轴振动值", sqldataVibration[6]); //向map里添加一对“键-值”
    m_map.insert("鼓风机8档X轴振动值", sqldataVibration[7]); //向map里添加一对“键-值”
    m_map.insert("鼓风机9档X轴振动值", sqldataVibration[8]); //向map里添加一对“键-值”
    m_map.insert("鼓风机1档Y轴振动值", sqldataVibration[9]); //向map里添加一对“键-值”
    m_map.insert("鼓风机2档Y轴振动值", sqldataVibration[10]); //向map里添加一对“键-值”
    m_map.insert("鼓风机3档Y轴振动值", sqldataVibration[11]); //向map里添加一对“键-值”
    m_map.insert("鼓风机4档Y轴振动值", sqldataVibration[12]); //向map里添加一对“键-值”
    m_map.insert("鼓风机5档Y轴振动值", sqldataVibration[13]); //向map里添加一对“键-值”
    m_map.insert("鼓风机6档Y轴振动值", sqldataVibration[14]); //向map里添加一对“键-值”
    m_map.insert("鼓风机7档Y轴振动值", sqldataVibration[15]); //向map里添加一对“键-值”
    m_map.insert("鼓风机8档Y轴振动值", sqldataVibration[16]); //向map里添加一对“键-值”
    m_map.insert("鼓风机9档Y轴振动值", sqldataVibration[17]); //向map里添加一对“键-值”
    m_map.insert("鼓风机1档Z轴振动值", sqldataVibration[18]); //向map里添加一对“键-值”
    m_map.insert("鼓风机2档Z轴振动值", sqldataVibration[19]); //向map里添加一对“键-值”
    m_map.insert("鼓风机3档Z轴振动值", sqldataVibration[20]); //向map里添加一对“键-值”
    m_map.insert("鼓风机4档Z轴振动值", sqldataVibration[21]); //向map里添加一对“键-值”
    m_map.insert("鼓风机5档Z轴振动值", sqldataVibration[22]); //向map里添加一对“键-值”
    m_map.insert("鼓风机6档Z轴振动值", sqldataVibration[23]); //向map里添加一对“键-值”
    m_map.insert("鼓风机7档Z轴振动值", sqldataVibration[24]); //向map里添加一对“键-值”
    m_map.insert("鼓风机8档Z轴振动值", sqldataVibration[25]); //向map里添加一对“键-值”
    m_map.insert("鼓风机9档Z轴振动值", sqldataVibration[26]); //向map里添加一对“键-值”
    m_map.insert("鼓风机1档单轴振动值", sqldataVibration[27]); //向map里添加一对“键-值”
    m_map.insert("鼓风机2档单轴振动值", sqldataVibration[28]); //向map里添加一对“键-值”
    m_map.insert("鼓风机3档单轴振动值", sqldataVibration[29]); //向map里添加一对“键-值”
    m_map.insert("鼓风机4档单轴振动值", sqldataVibration[30]); //向map里添加一对“键-值”
    m_map.insert("鼓风机5档单轴振动值", sqldataVibration[31]); //向map里添加一对“键-值”
    m_map.insert("鼓风机6档单轴振动值", sqldataVibration[32]); //向map里添加一对“键-值”
    m_map.insert("鼓风机7档单轴振动值", sqldataVibration[33]); //向map里添加一对“键-值”
    m_map.insert("鼓风机8档单轴振动值", sqldataVibration[34]); //向map里添加一对“键-值”
    m_map.insert("鼓风机9档单轴振动值", sqldataVibration[35]); //向map里添加一对“键-值”

    m_map.insert("鼓风机1档噪音检测值", sqldataVibration[36]); //向map里添加一对“键-值”
    m_map.insert("鼓风机2档噪音检测值", sqldataVibration[37]); //向map里添加一对“键-值”
    m_map.insert("鼓风机3档噪音检测值", sqldataVibration[38]); //向map里添加一对“键-值”
    m_map.insert("鼓风机4档噪音检测值", sqldataVibration[39]); //向map里添加一对“键-值”
    m_map.insert("鼓风机5档噪音检测值", sqldataVibration[40]); //向map里添加一对“键-值”
    m_map.insert("鼓风机6档噪音检测值", sqldataVibration[41]); //向map里添加一对“键-值”
    m_map.insert("鼓风机7档噪音检测值", sqldataVibration[42]); //向map里添加一对“键-值”
    m_map.insert("鼓风机8档噪音检测值", sqldataVibration[43]); //向map里添加一对“键-值”
    m_map.insert("鼓风机9档噪音检测值", sqldataVibration[44]); //向map里添加一对“键-值”
    
    data1 = "";
    data2 = "";
    for ( it = m_map.begin(); it != m_map.end(); ++it )
    {
        if(data1 == "")
        {
            data1 = it.key();
        }
        else
        {
            data1 += "," + it.key();
        }
        
        if(data2 == "")
        {
            data2 = "'" + it.value() + "'";
        }
        else
        {
            data2 += ",'" + it.value() + "'";
        }
    }
    data2 = data2.replace("'NULL'","NULL");
    //    qDebug()<<"data1"<<data1<<"data2"<<data2;
    QString str1 = QString("DELETE from jianghuai_songz.datas_linecode_d1 where 流水号 = '%1'").arg(sqldata[4]);
    Slots_MySql_exec(str1);//发送到主控数据库追溯
    str1 = QString("insert into jianghuai_songz.datas_linecode_d1(%1) values(%2)").arg(data1).arg(data2);
    //    qDebug()<<"存入数据库表d1";
    //    Data_Set->ui->textEdit->append(str1);
    Slots_MySql_exec(str1);//发送到主控数据库追溯
    m_map.clear();
    
    
    m_map.insert("序号", sqldata[0]); //向map里添加一对“键-值”
    m_map.insert("频道号", sqldata[1]); //向map里添加一对“键-值”
    m_map.insert("产品型号", sqldata[2]); //向map里添加一对“键-值”
    m_map.insert("日期", sqldata[3]); //向map里添加一对“键-值”
    m_map.insert("电检总结果", sqldata[4]); //向map里添加一对“键-值”
    m_map.insert("总成条码", sqldata[5]); //向map里添加一对“键-值”
    m_map.insert("错误代码", sqldata[6]); //向map里添加一对“键-值”
    m_map.insert("检测时间", sqldata[7]); //向map里添加一对“键-值”
    
    m_map.insert("LIN1_1NAD", LIN1NAD[0]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2NAD", LIN1NAD[1]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3NAD", LIN1NAD[2]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4NAD", LIN1NAD[3]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5NAD", LIN1NAD[4]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6NAD", LIN1NAD[5]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7NAD", LIN1NAD[6]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8NAD", LIN1NAD[7]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9NAD", LIN1NAD[8]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10NAD", LIN1NAD[9]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11NAD", LIN1NAD[10]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12NAD", LIN1NAD[11]); //向map里添加一对“键_值”
    
    m_map.insert("LIN1_1控制ID", LIN1ControlID[0]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2控制ID", LIN1ControlID[1]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3控制ID", LIN1ControlID[2]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4控制ID", LIN1ControlID[3]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5控制ID", LIN1ControlID[4]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6控制ID", LIN1ControlID[5]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7控制ID", LIN1ControlID[6]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8控制ID", LIN1ControlID[7]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9控制ID", LIN1ControlID[8]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10控制ID ", LIN1ControlID[9]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11控制ID ", LIN1ControlID[10]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12控制ID ", LIN1ControlID[11]); //向map里添加一对“键_值”
    
    m_map.insert("LIN1_1状态ID", LIN1StateID[0]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2状态ID",LIN1StateID[1]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3状态ID",LIN1StateID[2]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4状态ID",LIN1StateID[3]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5状态ID",LIN1StateID[4]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6状态ID",LIN1StateID[5]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7状态ID",LIN1StateID[6]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8状态ID",LIN1StateID[7]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9状态ID",LIN1StateID[8]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10状态ID ", LIN1StateID[9]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11状态ID ", LIN1StateID[10]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12状态ID ", LIN1StateID[11]); //向map里添加一对“键_值”

    m_map.insert("LIN1_1电机名称", sqldataLIN1data[0]); //向map里添加一对“键_值”
    m_map.insert("LIN1_1电机步数汇总", sqldataLIN1data[1]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2电机名称", sqldataLIN1data[2]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2电机步数汇总", sqldataLIN1data[3]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3电机名称", sqldataLIN1data[4]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3电机步数汇总", sqldataLIN1data[5]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4电机名称", sqldataLIN1data[6]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4电机步数汇总", sqldataLIN1data[7]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5电机名称", sqldataLIN1data[8]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5电机步数汇总", sqldataLIN1data[9]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6电机名称", sqldataLIN1data[10]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6电机步数汇总", sqldataLIN1data[11]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7电机名称", sqldataLIN1data[12]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7电机步数汇总", sqldataLIN1data[13]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8电机名称", sqldataLIN1data[14]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8电机步数汇总", sqldataLIN1data[15]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9电机名称", sqldataLIN1data[16]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9电机步数汇总", sqldataLIN1data[17]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10电机名称", sqldataLIN1data[18]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10电机步数汇总", sqldataLIN1data[19]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11电机名称", sqldataLIN1data[20]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11电机步数汇总", sqldataLIN1data[21]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12电机名称", sqldataLIN1data[22]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12电机步数汇总", sqldataLIN1data[23]); //向map里添加一对“键_值”
    m_map.insert("LIN1_1自学习极限步数1", sqldataLIN1data[24]); //向map里添加一对“键_值”
    m_map.insert("LIN1_1自学习极限步数2", sqldataLIN1data[25]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2自学习极限步数1", sqldataLIN1data[26]); //向map里添加一对“键_值”
    m_map.insert("LIN1_2自学习极限步数2", sqldataLIN1data[27]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3自学习极限步数1", sqldataLIN1data[28]); //向map里添加一对“键_值”
    m_map.insert("LIN1_3自学习极限步数2", sqldataLIN1data[29]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4自学习极限步数1", sqldataLIN1data[30]); //向map里添加一对“键_值”
    m_map.insert("LIN1_4自学习极限步数2", sqldataLIN1data[31]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5自学习极限步数1", sqldataLIN1data[32]); //向map里添加一对“键_值”
    m_map.insert("LIN1_5自学习极限步数2", sqldataLIN1data[33]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6自学习极限步数1", sqldataLIN1data[34]); //向map里添加一对“键_值”
    m_map.insert("LIN1_6自学习极限步数2", sqldataLIN1data[35]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7自学习极限步数1", sqldataLIN1data[36]); //向map里添加一对“键_值”
    m_map.insert("LIN1_7自学习极限步数2", sqldataLIN1data[37]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8自学习极限步数1", sqldataLIN1data[38]); //向map里添加一对“键_值”
    m_map.insert("LIN1_8自学习极限步数2", sqldataLIN1data[39]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9自学习极限步数1", sqldataLIN1data[40]); //向map里添加一对“键_值”
    m_map.insert("LIN1_9自学习极限步数2", sqldataLIN1data[41]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10自学习极限步数1", sqldataLIN1data[42]); //向map里添加一对“键_值”
    m_map.insert("LIN1_10自学习极限步数2", sqldataLIN1data[43]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11自学习极限步数1", sqldataLIN1data[44]); //向map里添加一对“键_值”
    m_map.insert("LIN1_11自学习极限步数2", sqldataLIN1data[45]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12自学习极限步数1", sqldataLIN1data[46]); //向map里添加一对“键_值”
    m_map.insert("LIN1_12自学习极限步数2", sqldataLIN1data[47]); //向map里添加一对“键_值”


    //    QMap<QString,QString>::iterator it; //遍历map
    //    QString data1,data2;
    data1 = "";
    data2 = "";
    for ( it = m_map.begin(); it != m_map.end(); ++it )
    {
        if(data1 == "")
        {
            data1 = it.key();
        }
        else
        {
            data1 += "," + it.key();
        }
    }
    for ( it = m_map.begin(); it != m_map.end(); ++it )
    {
        if(data2 == "")
        {
            data2 = "'" + it.value() + "'";
        }
        else
        {
            data2 += ",'" + it.value() + "'";
        }
    }
    data2 = data2.replace("'NULL'","NULL");
    //    qDebug()<<"data1"<<data1<<"data2"<<data2;
    QString str2 = QString("DELETE from jianghuai_songz.datas_linecode_d2 where 流水号 = '%1'").arg(sqldata[4]);
    Slots_MySql_exec(str2);//发送到主控数据库追溯
    str2 = QString("insert into jianghuai_songz.datas_linecode_d2(%1) values(%2)").arg(data1).arg(data2);
    //    ui->textEdit->append(str2);
    //    qDebug()<<"存入数据库表d2";
    //    Data_Set->ui->textEdit->append(str2);
    Slots_MySql_exec(str2);//发送到主控数据库追溯
    m_map.clear();
    
    m_map.insert("序号", sqldata[0]); //向map里添加一对“键-值”
    m_map.insert("频道号", sqldata[1]); //向map里添加一对“键-值”
    m_map.insert("产品型号", sqldata[2]); //向map里添加一对“键-值”
    m_map.insert("日期", sqldata[3]); //向map里添加一对“键-值”
    m_map.insert("电检总结果", sqldata[4]); //向map里添加一对“键-值”
    m_map.insert("总成条码", sqldata[5]); //向map里添加一对“键-值”
    m_map.insert("错误代码", sqldata[6]); //向map里添加一对“键-值”
    m_map.insert("检测时间", sqldata[7]); //向map里添加一对“键-值”
    
    m_map.insert("M1电机名称", sqldataPTdata[0]); //向map里添加一对“键-值”
    m_map.insert("M1电机电压汇总", sqldataPTdata[1]); //向map里添加一对“键-值”
    m_map.insert("M1电机电流汇总", sqldataPTdata[2]); //向map里添加一对“键-值”
    m_map.insert("M2电机名称", sqldataPTdata[3]); //向map里添加一对“键-值”
    m_map.insert("M2电机电压汇总", sqldataPTdata[4]); //向map里添加一对“键-值”
    m_map.insert("M2电机电流汇总", sqldataPTdata[5]); //向map里添加一对“键-值”
    m_map.insert("M3电机名称", sqldataPTdata[6]); //向map里添加一对“键-值”
    m_map.insert("M3电机电压汇总", sqldataPTdata[7]); //向map里添加一对“键-值”
    m_map.insert("M3电机电流汇总", sqldataPTdata[8]); //向map里添加一对“键-值”
    m_map.insert("M4电机名称", sqldataPTdata[9]); //向map里添加一对“键-值”
    m_map.insert("M4电机电压汇总", sqldataPTdata[10]); //向map里添加一对“键-值”
    m_map.insert("M4电机电流汇总", sqldataPTdata[11]); //向map里添加一对“键-值”
    m_map.insert("M5电机名称", sqldataPTdata[12]); //向map里添加一对“键-值”
    m_map.insert("M5电机电压汇总", sqldataPTdata[13]); //向map里添加一对“键-值”
    m_map.insert("M5电机电流汇总", sqldataPTdata[14]); //向map里添加一对“键-值”
    m_map.insert("M6电机名称", sqldataPTdata[15]); //向map里添加一对“键-值”
    m_map.insert("M6电机电压汇总", sqldataPTdata[16]); //向map里添加一对“键-值”
    m_map.insert("M6电机电流汇总", sqldataPTdata[17]); //向map里添加一对“键-值”
    m_map.insert("M7电机名称", sqldataPTdata[18]); //向map里添加一对“键-值”
    m_map.insert("M7电机电压汇总", sqldataPTdata[19]); //向map里添加一对“键-值”
    m_map.insert("M7电机电流汇总", sqldataPTdata[20]); //向map里添加一对“键-值”
    m_map.insert("M8电机名称", sqldataPTdata[21]); //向map里添加一对“键-值”
    m_map.insert("M8电机电压汇总", sqldataPTdata[22]); //向map里添加一对“键-值”
    m_map.insert("M8电机电流汇总", sqldataPTdata[23]); //向map里添加一对“键-值”
    m_map.insert("M9电机名称", sqldataPTdata[24]); //向map里添加一对“键-值”
    m_map.insert("M9电机电压汇总", sqldataPTdata[25]); //向map里添加一对“键-值”
    m_map.insert("M9电机电流汇总", sqldataPTdata[26]); //向map里添加一对“键-值”
    m_map.insert("M10电机名称", sqldataPTdata[27]); //向map里添加一对“键-值”
    m_map.insert("M10电机电压汇总", sqldataPTdata[28]); //向map里添加一对“键-值”
    m_map.insert("M10电机电流汇总", sqldataPTdata[29]); //向map里添加一对“键-值”
    m_map.insert("M11电机名称", sqldataPTdata[30]); //向map里添加一对“键-值”
    m_map.insert("M11电机电压汇总", sqldataPTdata[31]); //向map里添加一对“键-值”
    m_map.insert("M11电机电流汇总", sqldataPTdata[32]); //向map里添加一对“键-值”
    m_map.insert("M12电机名称", sqldataPTdata[33]); //向map里添加一对“键-值”
    m_map.insert("M12电机电压汇总", sqldataPTdata[34]); //向map里添加一对“键-值”
    m_map.insert("M12电机电流汇总", sqldataPTdata[35]); //向map里添加一对“键-值”
    
    m_map.insert("室内环境温度", sqldataRes[0]); //向map里添加一对“键-值”
    m_map.insert("温敏1检测值", sqldataRes[1]); //向map里添加一对“键-值”
    m_map.insert("温敏2检测值", sqldataRes[2]); //向map里添加一对“键-值”
    m_map.insert("温敏3检测值", sqldataRes[3]); //向map里添加一对“键-值”
    m_map.insert("温敏4检测值", sqldataRes[4]); //向map里添加一对“键-值”
    m_map.insert("温敏5检测值", sqldataRes[5]); //向map里添加一对“键-值”
    m_map.insert("温敏6检测值", sqldataRes[6]); //向map里添加一对“键-值”
    m_map.insert("温敏7检测值", sqldataRes[7]); //向map里添加一对“键-值”
    m_map.insert("温敏8检测值", sqldataRes[8]); //向map里添加一对“键-值”
    m_map.insert("温敏9检测值", sqldataRes[9]); //向map里添加一对“键-值”
    m_map.insert("温敏10检测值", sqldataRes[10]); //向map里添加一对“键-值”
    m_map.insert("温敏11检测值", sqldataRes[11]); //向map里添加一对“键-值”
    m_map.insert("温敏12检测值", sqldataRes[12]); //向map里添加一对“键-值”
    m_map.insert("车内PM25检测浓度", sqldataRes[13]); //向map里添加一对“键-值”
    m_map.insert("车外PM25检测浓度", sqldataRes[14]); //向map里添加一对“键-值”
    m_map.insert("空气质量状态", sqldataRes[15]); //向map里添加一对“键-值”
    m_map.insert("电子膨胀阀ID", sqldataRes[16]); //向map里添加一对“键-值”
    m_map.insert("电子膨胀阀当前位置", sqldataRes[17]); //向map里添加一对“键-值”
    m_map.insert("PTC_ID", sqldataRes[18]); //向map里添加一对“键-值”
    m_map.insert("软件版本号", sqldataRes[19]); //向map里添加一对“键-值”
    m_map.insert("硬件版本号", sqldataRes[20]); //向map里添加一对“键-值”
    m_map.insert("负离子检测电压", sqldataRes[21]); //向map里添加一对“键-值”
    m_map.insert("噪音检测值", sqldataRes[22]); //向map里添加一对“键-值”
    
    //    QMap<QString,QString>::iterator it; //遍历map
    //    QString data1,data2;
    data1 = "";
    data2 = "";
    for ( it = m_map.begin(); it != m_map.end(); ++it )
    {
        if(data1 == "")
        {
            data1 = it.key();
        }
        else
        {
            data1 += "," + it.key();
        }
    }
    for ( it = m_map.begin(); it != m_map.end(); ++it )
    {
        if(data2 == "")
        {
            data2 = "'" + it.value() + "'";
        }
        else
        {
            data2 += ",'" + it.value() + "'";
        }
    }
    data2 = data2.replace("'NULL'","NULL");
    //    qDebug()<<"data1"<<data1<<"data2"<<data2;
    QString str3 = QString("DELETE from jianghuai_songz.datas_linecode_d3 where 流水号 = '%1'").arg(sqldata[4]);
    Slots_MySql_exec(str3);//发送到主控数据库追溯
    str3 = QString("insert into jianghuai_songz.datas_linecode_d3(%1) values(%2)").arg(data1).arg(data2);
    //    qDebug()<<"存入数据库表d3";
    //    Data_Set->ui->textEdit->append(str3);
    Slots_MySql_exec(str3);//发送到主控数据库追溯
    m_map.clear();
    
    qDebug()<<"数据库存储完成";
    
}

void MainWindow::Slots_MySql_exec(QString String)
{
    QSqlQuery query(Sqlserverdb);
    bool er = query.exec(String);
    if(!er)
    {
        qDebug()<<"MySQL数据库语句执行失败"<<String<<"错误信息："<<query.lastError().text();
    }
}

void MainWindow::Save_Excel()
{
    QString path = QApplication::applicationDirPath() + "/System/System.ini";
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    
    
    QDateTime time = QDateTime::currentDateTime();
    qDebug()<<"开始存入本地Excel";
    
    //    qDebug()<<time.toString("hh:mm:ss.zzz");
    QString newexcel = time.toString("yyyy-MM-dd");
    
    QString excelname = INI_File->value("DataSavePath").toString().replace(QString("/"), QString("//"))+QString("\\%1\\%2.xlsx").arg(newexcel).arg(newexcel);
    QXlsx::Document xlsx(excelname);
    InitialValue = INI_File->value("InitialValue").toString().toInt();//行
    
    uint size=0;
    
    for(int i = 1;i<sqldata.count();i++ )//参数10
    {
        xlsx.write(InitialValue,i,sqldata[i]);
    }
    size += sqldata.count();
    for(int i = 0;i<Allresults.count();i++ )//所有结果
    {
        //        qDebug()<<InitialValue<<i<<Allresults[i];
        xlsx.write(InitialValue,i+size,Allresults[i]);
    }
    size += Allresults.count();
    for(int i = 0;i<sqldata1Blower.count();i++ )//鼓风机
    {
        xlsx.write(InitialValue,i+size,sqldata1Blower[i]);
    }
    size += sqldata1Blower.count();
    for(int i = 0;i<sqldataVibration.count();i++ )//振动值
    {
        xlsx.write(InitialValue,i+size,sqldataVibration[i]);
    }
    size += sqldataVibration.count();
    
    for(int i = 0;i<LIN1NAD.count();i++ )//LIN1NAD
    {
        xlsx.write(InitialValue,i+size,LIN1NAD[i]);
    }
    
    size += LIN1NAD.count();
    for(int i = 0;i<LIN1ControlID.count();i++ )//LIN1ControlID
    {
        xlsx.write(InitialValue,i+size,LIN1ControlID[i]);
    }
    size += LIN1ControlID.count();
    for(int i = 0;i<LIN1StateID.count();i++ )//LIN1StateID
    {
        xlsx.write(InitialValue,i+size,LIN1StateID[i]);
    }
    size += LIN1StateID.count();
    



    for(int i = 0;i<sqldataLIN1data.count();i++ )//LIN1-1步数
    {
        xlsx.write(InitialValue,i+size,sqldataLIN1data[i]);
    }
    size += sqldataLIN1data.count();
    

    for(int i = 0;i<sqldataPTdata.count();i++ )//LIN1-2步数
    {
        xlsx.write(InitialValue,i+size,sqldataPTdata[i]);
    }
    size += sqldataPTdata.count();
    


    for(int i = 0;i<sqldataRes.count();i++ )//电阻
    {
        xlsx.write(InitialValue,i+size,sqldataRes[i]);
    }
    InitialValue++;
    INI_File->setValue("InitialValue",QString::number(InitialValue));
    xlsx.save();
    INI_File->destroyed();
    qDebug()<<"存入本地Excel完成";

}

void MainWindow::Update_show()
{
    if(AutoDataValue[899]==1 && adminman == 1)//手自动按钮
    {
        ReadChannel_flag = 1;
        ui->Auto_PDbox->setEnabled(true);
    }
    else
    {
        ui->Auto_PDbox->setEnabled(false);
    }
    if((AutoDataValue[0] != m_S_RFID_Pars.Channel.toInt()) && (ReadChannel_flag == 2) )
    {
        qDebug()<<"进入操作员频道切换";
        ReadChannel_flag = 2;
        MainShow->ui->Auto_PDbox->setCurrentText(m_S_RFID_Pars.Channel);
        on_Auto_PDbox_currentTextChanged(m_S_RFID_Pars.Channel);
    }
    if(m_S_RFID_Pars.serial_number.toLatin1().length()==13)
    {
        liushuihao = m_S_RFID_Pars.serial_number.toLatin1();
        if(liushuihao.mid(0,1) == "E")
        {
            ui->Auto_Mode_Show->setText("返修");
            ui->Auto_Mode_Show->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(255, 0, 0);");
        }
        else if(liushuihao.mid(0,1) == "A")
        {
            ui->Auto_Mode_Show->setText("正常");
            ui->Auto_Mode_Show->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(170, 0, 255);");
        }
        else
        {
            ui->Auto_Mode_Show->setText("模式");
            ui->Auto_Mode_Show->setStyleSheet("color: rgb(0, 0, 0);background-color: rgb(234, 234, 0);");
        }
    }
    slot_Get_uplineCode(liushuihao);
    ui->Auto_SerialNumber->setText(liushuihao);
    if(ReadChannel_flag == 2)
    {
        if(NewPD_Flag != AutoDataValue[0]&& (m_S_RFID_Pars.Channel.toInt()== AutoDataValue[0]))
        {
            qDebug()<<"PLC——MC切换频道";
            NewPD_Flag = AutoDataValue[0];
            QString PD = "PD"+QString::number(NewPD_Flag);

            QList<QPushButton *> Res_Name;
            Res_Name.append(ui->Auto_Tem1);Res_Name.append(ui->Auto_Tem2);Res_Name.append(ui->Auto_Tem3);Res_Name.append(ui->Auto_Tem4);Res_Name.append(ui->Auto_Tem5);
            Res_Name.append(ui->Auto_Tem6);Res_Name.append(ui->Auto_Tem7);Res_Name.append(ui->Auto_Tem8);Res_Name.append(ui->Auto_Tem9);Res_Name.append(ui->Auto_Tem10);
            for (int i = 1;i<11 ; i++)
            {
                Res_Name.at(i-1)->setText(ini_file().Get_Control(PD+"/Res"+QString::number(i)+"_Name"));
            }
            QList<QPushButton *> Speed_Name;
            Speed_Name.append(ui->Auto_Speed1);Speed_Name.append(ui->Auto_Speed2);Speed_Name.append(ui->Auto_Speed3);Speed_Name.append(ui->Auto_Speed4);Speed_Name.append(ui->Auto_Speed5);
            Speed_Name.append(ui->Auto_Speed6);Speed_Name.append(ui->Auto_Speed7);Speed_Name.append(ui->Auto_Speed8);
            for (int i = 1;i<13; i++)
            {
                Speed_Name.at(i-1)->setText(ini_file().Get_Control(PD+"/Speed"+QString::number(i)+"_Name"));
            }

            QString path = QApplication::applicationDirPath() + "/HVAC/PD_HVACMode.ini";
            QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
            INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
            ui->Auto_Model->setText(INI_File->value(PD+"_HVAC_Name").toString());
            INI_File->destroyed();
        }
        if(m_S_RFID_Pars.Channel.toInt() != ui->Auto_PDbox->currentText().toInt())
        {
            ui->Auto_PDbox->setCurrentText(QString::number(m_S_RFID_Pars.Channel.toInt()));
        }
    }
    else
    {
        if(NewPD_Flag != AutoDataValue[0])
        {
            qDebug()<<"PLC——MC切换频道";
            NewPD_Flag = AutoDataValue[0];
            QString PD = "PD"+QString::number(NewPD_Flag);

            QList<QPushButton *> Res_Name;
            Res_Name.append(ui->Auto_Tem1);Res_Name.append(ui->Auto_Tem2);Res_Name.append(ui->Auto_Tem3);Res_Name.append(ui->Auto_Tem4);Res_Name.append(ui->Auto_Tem5);
            Res_Name.append(ui->Auto_Tem6);Res_Name.append(ui->Auto_Tem7);Res_Name.append(ui->Auto_Tem8);Res_Name.append(ui->Auto_Tem9);Res_Name.append(ui->Auto_Tem10);
            for (int i = 1;i<11 ; i++)
            {
                Res_Name.at(i-1)->setText(ini_file().Get_Control(PD+"/Res"+QString::number(i)+"_Name"));
            }
            QList<QPushButton *> Speed_Name;
            Speed_Name.append(ui->Auto_Speed1);Speed_Name.append(ui->Auto_Speed2);Speed_Name.append(ui->Auto_Speed3);Speed_Name.append(ui->Auto_Speed4);Speed_Name.append(ui->Auto_Speed5);
            Speed_Name.append(ui->Auto_Speed6);Speed_Name.append(ui->Auto_Speed7);Speed_Name.append(ui->Auto_Speed8);
            for (int i = 1;i<13; i++)
            {
                Speed_Name.at(i-1)->setText(ini_file().Get_Control(PD+"/Speed"+QString::number(i)+"_Name"));
            }

            QString path = QApplication::applicationDirPath() + "/HVAC/PD_HVACMode.ini";
            QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
            INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
            ui->Auto_Model->setText(INI_File->value(PD+"_HVAC_Name").toString());
            INI_File->destroyed();
        }

    }
    ui->Auto_CheckTime->setValue(QString::number(AutoDataValue[1]/10.0,'f',1).toFloat());//检测时间
    ui->Auto_RunSteps->setText(QString::number(AutoDataValue[6]));//步骤
    if(AutoDataValue[7]==0)//最终检测结果
    {
        ui->Auto_results->setText("");
        ui->Auto_results->setStyleSheet("");
    }
    else if(AutoDataValue[7]==1)
    {
        ui->Auto_results->setText("OK");
        ui->Auto_results->setStyleSheet(Button_background_color(1));
    }
    else if(AutoDataValue[7]==2)
    {
        ui->Auto_results->setText("NG");
        ui->Auto_results->setStyleSheet(Button_background_color(3));
    }
    else if(AutoDataValue[7]==3)
    {
        ui->Auto_results->setText("检测中");
        ui->Auto_results->setStyleSheet(Button_background_color(2));
    }
    
    
    //-------------------------------------鼓风机-----------------------------------
    ui->Auto_Blower->setStyleSheet(Button_background_color(AutoDataValue[9]));//鼓风机结果
    ui->Auto_Blower_Now_A->setValue(QString::number(AutoDataValue[21]/100.0,'f',1).toFloat());//实时电流
    ui->Auto_Blower_Now_V->setValue(AutoDataValue[19]);//实时电压
    
    //    unsigned char highByte = (AutoDataValue[765] >> 8) & 0xFF;
    //    unsigned char lowByte = AutoDataValue[765] & 0xFF;
    //    // 转换为ASCII字符
    //    QChar highChar(highByte);
    //    QChar lowChar(lowByte);
    //    QString ASCII;
    //    ASCII  =  ASCII.append(lowByte);
    //    ASCII  =  ASCII.append(highChar);
    //    // 输出结果
    //    ui->Auto_Blower_Hardware->setText(ASCII);
    //    unsigned char highByte_2 = (AutoDataValue[766] >> 8) & 0xFF;
    //    unsigned char lowByte_2 = AutoDataValue[766] & 0xFF;
    //    // 转换为ASCII字符
    //    QChar lowChar_2(lowByte_2);
    //    QChar highChar_2(highByte_2);
    //    QString ASCII_2;
    //    ASCII_2  =  ASCII_2.append(lowByte_2);
    //    ASCII_2  =  ASCII_2.append(highByte_2);
    //    // ui->Auto_Blower_Hardware->setText(ASCII);
    //    ui->Auto_Blower_Software->setText(ASCII_2);
    
    ui->Auto_Blower_POS1->setStyleSheet(Button_background_color(AutoDataValue[10]));//鼓风机POS1结果
    ui->Auto_Blower_POS2->setStyleSheet(Button_background_color(AutoDataValue[11]));//鼓风机POS2结果
    ui->Auto_Blower_POS3->setStyleSheet(Button_background_color(AutoDataValue[12]));//鼓风机POS3结果
    ui->Auto_Blower_POS4->setStyleSheet(Button_background_color(AutoDataValue[13]));//鼓风机POS4结果
    ui->Auto_Blower_POS5->setStyleSheet(Button_background_color(AutoDataValue[14]));//鼓风机POS5结果
    ui->Auto_Blower_POS6->setStyleSheet(Button_background_color(AutoDataValue[15]));//鼓风机POS6结果
    ui->Auto_Blower_POS7->setStyleSheet(Button_background_color(AutoDataValue[16]));//鼓风机POS7结果
    ui->Auto_Blower_POS8->setStyleSheet(Button_background_color(AutoDataValue[17]));//鼓风机POS8结果
    ui->Auto_Blower_POS9->setStyleSheet(Button_background_color(AutoDataValue[18]));//鼓风机POS9结果
    
    ui->Auto_Blower_POS1_Value->setValue(QString::number(AutoDataValue[24]/100.0,'f',1).toFloat());//鼓风机1档电流值
    ui->Auto_Blower_POS2_Value->setValue(QString::number(AutoDataValue[25]/100.0,'f',1).toFloat());//鼓风机2档电流值
    ui->Auto_Blower_POS3_Value->setValue(QString::number(AutoDataValue[26]/100.0,'f',1).toFloat());//鼓风机3档电流值
    ui->Auto_Blower_POS4_Value->setValue(QString::number(AutoDataValue[27]/100.0,'f',1).toFloat());//鼓风机4档电流值
    ui->Auto_Blower_POS5_Value->setValue(QString::number(AutoDataValue[28]/100.0,'f',1).toFloat());//鼓风机5档电流值
    ui->Auto_Blower_POS6_Value->setValue(QString::number(AutoDataValue[29]/100.0,'f',1).toFloat());//鼓风机6档电流值
    ui->Auto_Blower_POS7_Value->setValue(QString::number(AutoDataValue[30]/100.0,'f',1).toFloat());//鼓风机7档电流值
    ui->Auto_Blower_POS8_Value->setValue(QString::number(AutoDataValue[31]/100.0,'f',1).toFloat());//鼓风机8档电流值
    ui->Auto_Blower_POS9_Value->setValue(QString::number(AutoDataValue[32]/100.0,'f',1).toFloat());//鼓风机9档电流值

    ui->Auto_Blower_POS1_Value_2->setValue(AutoDataValue[42]);//鼓风机1档电压值/转速值
    ui->Auto_Blower_POS2_Value_2->setValue(AutoDataValue[43]);//鼓风机2档电压值/转速值
    ui->Auto_Blower_POS3_Value_2->setValue(AutoDataValue[44]);//鼓风机3档电压值/转速值
    ui->Auto_Blower_POS4_Value_2->setValue(AutoDataValue[45]);//鼓风机4档电压值/转速值
    ui->Auto_Blower_POS5_Value_2->setValue(AutoDataValue[46]);//鼓风机5档电压值/转速值
    ui->Auto_Blower_POS6_Value_2->setValue(AutoDataValue[47]);//鼓风机6档电压值/转速值
    ui->Auto_Blower_POS7_Value_2->setValue(AutoDataValue[48]);//鼓风机7档电压值/转速值
    ui->Auto_Blower_POS8_Value_2->setValue(AutoDataValue[49]);//鼓风机8档电压值/转速值
    ui->Auto_Blower_POS9_Value_2->setValue(AutoDataValue[50]);//鼓风机9档电压值/转速值
    
    ui->Auto_Vibration_X->setStyleSheet(Button_background_color(AutoDataValue[615]));//振动X轴结果
    ui->Auto_Vibration_POS1_X->setValue(QString::number(AutoDataValue[51]/100.0,'f',2).toFloat());//振动X轴1档值
    ui->Auto_Vibration_POS2_X->setValue(QString::number(AutoDataValue[53]/100.0,'f',2).toFloat());//振动X轴2档值
    ui->Auto_Vibration_POS3_X->setValue(QString::number(AutoDataValue[55]/100.0,'f',2).toFloat());//振动X轴3档值
    ui->Auto_Vibration_POS4_X->setValue(QString::number(AutoDataValue[57]/100.0,'f',2).toFloat());//振动X轴4档值
    ui->Auto_Vibration_POS5_X->setValue(QString::number(AutoDataValue[59]/100.0,'f',2).toFloat());//振动X轴5档值
    ui->Auto_Vibration_POS6_X->setValue(QString::number(AutoDataValue[61]/100.0,'f',2).toFloat());//振动X轴6档值
    ui->Auto_Vibration_POS7_X->setValue(QString::number(AutoDataValue[63]/100.0,'f',2).toFloat());//振动X轴7档值
    ui->Auto_Vibration_POS8_X->setValue(QString::number(AutoDataValue[65]/100.0,'f',2).toFloat());//振动X轴8档值
    ui->Auto_Vibration_POS9_X->setValue(QString::number(AutoDataValue[67]/100.0,'f',2).toFloat());//振动X轴9档值
    
    ui->Auto_Vibration_Y->setStyleSheet(Button_background_color(AutoDataValue[616]));//振动Y轴结果
    ui->Auto_Vibration_POS1_Y->setValue(QString::number(AutoDataValue[69]/100.0,'f',2).toFloat());//振动Y轴1档值
    ui->Auto_Vibration_POS2_Y->setValue(QString::number(AutoDataValue[71]/100.0,'f',2).toFloat());//振动Y轴2档值
    ui->Auto_Vibration_POS3_Y->setValue(QString::number(AutoDataValue[73]/100.0,'f',2).toFloat());//振动Y轴3档值
    ui->Auto_Vibration_POS4_Y->setValue(QString::number(AutoDataValue[75]/100.0,'f',2).toFloat());//振动Y轴4档值
    ui->Auto_Vibration_POS5_Y->setValue(QString::number(AutoDataValue[77]/100.0,'f',2).toFloat());//振动Y轴5档值
    ui->Auto_Vibration_POS6_Y->setValue(QString::number(AutoDataValue[79]/100.0,'f',2).toFloat());//振动Y轴6档值
    ui->Auto_Vibration_POS7_Y->setValue(QString::number(AutoDataValue[81]/100.0,'f',2).toFloat());//振动Y轴7档值
    ui->Auto_Vibration_POS8_Y->setValue(QString::number(AutoDataValue[83]/100.0,'f',2).toFloat());//振动Y轴8档值
    ui->Auto_Vibration_POS9_Y->setValue(QString::number(AutoDataValue[85]/100.0,'f',2).toFloat());//振动Y轴9档值
    
    ui->Auto_Vibration_Z->setStyleSheet(Button_background_color(AutoDataValue[617]));//振动Z轴结果
    ui->Auto_Vibration_POS1_Z->setValue(QString::number(AutoDataValue[87]/100.0,'f',2).toFloat());//振动Z轴1档值
    ui->Auto_Vibration_POS2_Z->setValue(QString::number(AutoDataValue[89]/100.0,'f',2).toFloat());//振动Z轴2档值
    ui->Auto_Vibration_POS3_Z->setValue(QString::number(AutoDataValue[91]/100.0,'f',2).toFloat());//振动Z轴3档值
    ui->Auto_Vibration_POS4_Z->setValue(QString::number(AutoDataValue[93]/100.0,'f',2).toFloat());//振动Z轴4档值
    ui->Auto_Vibration_POS5_Z->setValue(QString::number(AutoDataValue[95]/100.0,'f',2).toFloat());//振动Z轴5档值
    ui->Auto_Vibration_POS6_Z->setValue(QString::number(AutoDataValue[97]/100.0,'f',2).toFloat());//振动Z轴6档值
    ui->Auto_Vibration_POS7_Z->setValue(QString::number(AutoDataValue[99]/100.0,'f',2).toFloat());//振动Z轴7档值
    ui->Auto_Vibration_POS8_Z->setValue(QString::number(AutoDataValue[101]/100.0,'f',2).toFloat());//振动Z轴8档值
    ui->Auto_Vibration_POS9_Z->setValue(QString::number(AutoDataValue[103]/100.0,'f',2).toFloat());//振动Z轴9档值
    

    
    //    ui->Auto_LIN1_1_NAD->setText(QString("%1").arg(AutoDataValue[183], 0, 16).toUpper());
    //    ui->Auto_LIN1_1_Controlid->setText(QString("%1").arg(AutoDataValue[184], 0, 16).toUpper());
    //    ui->Auto_LIN1_1_Stateid->setText(QString("%1").arg(AutoDataValue[185], 0, 16).toUpper());

    ui->Auto_Tem1->setStyleSheet(Button_background_color(AutoDataValue[595]));
    ui->Auto_Tem2->setStyleSheet(Button_background_color(AutoDataValue[596]));
    ui->Auto_Tem3->setStyleSheet(Button_background_color(AutoDataValue[597]));
    ui->Auto_Tem4->setStyleSheet(Button_background_color(AutoDataValue[598]));
    ui->Auto_Tem5->setStyleSheet(Button_background_color(AutoDataValue[599]));
    ui->Auto_Tem6->setStyleSheet(Button_background_color(AutoDataValue[600]));
    ui->Auto_Tem7->setStyleSheet(Button_background_color(AutoDataValue[601]));
    ui->Auto_Tem8->setStyleSheet(Button_background_color(AutoDataValue[602]));
    ui->Auto_Tem9->setStyleSheet(Button_background_color(AutoDataValue[603]));
    ui->Auto_Tem10->setStyleSheet(Button_background_color(AutoDataValue[604]));
    
    //    QString::number(AutoDataValue[24]/10.0,'f',1).toFloat()
    ui->Auto_Tem1_Now->setValue(QString::number(AutoDataValue[605]/10.0,'f',1).toFloat());
    ui->Auto_Tem2_Now->setValue(QString::number(AutoDataValue[606]/10.0,'f',1).toFloat());
    ui->Auto_Tem3_Now->setValue(QString::number(AutoDataValue[607]/10.0,'f',1).toFloat());
    ui->Auto_Tem4_Now->setValue(QString::number(AutoDataValue[608]/10.0,'f',1).toFloat());
    ui->Auto_Tem5_Now->setValue(QString::number(AutoDataValue[609]/10.0,'f',1).toFloat());
    ui->Auto_Tem6_Now->setValue(QString::number(AutoDataValue[610]/10.0,'f',1).toFloat());
    ui->Auto_Tem7_Now->setValue(QString::number(AutoDataValue[611]/10.0,'f',1).toFloat());//环境温敏
    ui->Auto_NowTem->setValue(QString::number(AutoDataValue[611]/10.0,'f',1).toFloat());//环境温敏
    ui->Auto_Tem8_Now->setValue(QString::number(AutoDataValue[612]/10.0,'f',1).toFloat());
    ui->Auto_Tem9_Now->setValue(QString::number(AutoDataValue[613]/10.0,'f',1).toFloat());
    ui->Auto_Tem10_Now->setValue(QString::number(AutoDataValue[614]/10.0,'f',1).toFloat());
    
    ui->Auto_PM25->setStyleSheet(Button_background_color(AutoDataValue[619]));
    ui->Auto_PM25_InValue->setValue(AutoDataValue[620]);
    ui->Auto_PM25_OutValue->setValue(AutoDataValue[621]);
    ui->Auto_PM25_error->setValue(AutoDataValue[622]);
    
    ui->Auto_PTC->setStyleSheet(Button_background_color(AutoDataValue[623]));
    ui->Auto_PTC_ID->setText(QString("%1").arg(AutoDataValue[624], 0, 16).toUpper());
    ui->Auto_PTC_Software->setText(QString("%1").arg(AutoDataValue[625], 0, 16).toUpper());
    ui->Auto_PTC_Hardware->setText(QString("%1").arg(AutoDataValue[626], 0, 16).toUpper());
    
    ui->Auto_FLZ->setStyleSheet(Button_background_color(AutoDataValue[627]));
    ui->Auto_FLZ_Value->setValue(QString::number(AutoDataValue[628]/100.0,'f',1).toFloat());
    
    ui->Auto_AQS->setStyleSheet(Button_background_color(AutoDataValue[629]));
    ui->Auto_AQS_Value->setText(QString("%1").arg(AutoDataValue[630], 0, 16).toUpper());
    
    ui->Auto_Swell->setStyleSheet(Button_background_color(AutoDataValue[631]));
    ui->Auto_Swell_ID->setText(QString("%1").arg(AutoDataValue[632], 0, 16).toUpper());
    ui->Auto_Swell_Value->setValue(AutoDataValue[633]);
    
    ui->Auto_Noises->setStyleSheet(Button_background_color(AutoDataValue[634]));
    //    ui->Auto_Noises_Value->setValue(QString::number(AutoDataValue[635]/10.0,'f',1).toFloat());

    ui->Auto_Noises_Value_POS1->setValue(QString::number(AutoDataValue[850]/10.0,'f',1).toFloat());
    ui->Auto_Noises_Value_POS2->setValue(QString::number(AutoDataValue[851]/10.0,'f',1).toFloat());
    ui->Auto_Noises_Value_POS3->setValue(QString::number(AutoDataValue[852]/10.0,'f',1).toFloat());
    ui->Auto_Noises_Value_POS4->setValue(QString::number(AutoDataValue[853]/10.0,'f',1).toFloat());
    ui->Auto_Noises_Value_POS5->setValue(QString::number(AutoDataValue[854]/10.0,'f',1).toFloat());
    ui->Auto_Noises_Value_POS6->setValue(QString::number(AutoDataValue[855]/10.0,'f',1).toFloat());
    ui->Auto_Noises_Value_POS7->setValue(QString::number(AutoDataValue[856]/10.0,'f',1).toFloat());
    ui->Auto_Noises_Value_POS8->setValue(QString::number(AutoDataValue[857]/10.0,'f',1).toFloat());
    ui->Auto_Noises_Value_POS9->setValue(QString::number(AutoDataValue[858]/10.0,'f',1).toFloat());

    ui->Auto_Speed->setStyleSheet(Button_background_color(AutoDataValue[636]));
    ui->Auto_Speed1->setStyleSheet(Button_background_color(AutoDataValue[637]));
    ui->Auto_Speed2->setStyleSheet(Button_background_color(AutoDataValue[638]));
    ui->Auto_Speed3->setStyleSheet(Button_background_color(AutoDataValue[639]));
    ui->Auto_Speed4->setStyleSheet(Button_background_color(AutoDataValue[640]));
    ui->Auto_Speed5->setStyleSheet(Button_background_color(AutoDataValue[641]));
    ui->Auto_Speed6->setStyleSheet(Button_background_color(AutoDataValue[642]));
    ui->Auto_Speed7->setStyleSheet(Button_background_color(AutoDataValue[643]));
    ui->Auto_Speed8->setStyleSheet(Button_background_color(AutoDataValue[644]));

    ui->Auto_Speed_Mode1->setStyleSheet(Button_background_color(AutoDataValue[649]));
    ui->Auto_Speed_Mode2->setStyleSheet(Button_background_color(AutoDataValue[650]));
    ui->Auto_Speed_Mode3->setStyleSheet(Button_background_color(AutoDataValue[651]));
    ui->Auto_Speed_Mode4->setStyleSheet(Button_background_color(AutoDataValue[652]));
    ui->Auto_Speed_Mode5->setStyleSheet(Button_background_color(AutoDataValue[653]));
    ui->Auto_Speed_Mode6->setStyleSheet(Button_background_color(AutoDataValue[654]));
    ui->Auto_Speed_Mode7->setStyleSheet(Button_background_color(AutoDataValue[655]));
    ui->Auto_Speed_Mode8->setStyleSheet(Button_background_color(AutoDataValue[656]));
    
    ui->Auto_Speed1_Value->setValue(QString::number(AutoDataValue[657]/10.0,'f',1).toFloat());
    ui->Auto_Speed2_Value->setValue(QString::number(AutoDataValue[658]/10.0,'f',1).toFloat());
    ui->Auto_Speed3_Value->setValue(QString::number(AutoDataValue[659]/10.0,'f',1).toFloat());
    ui->Auto_Speed4_Value->setValue(QString::number(AutoDataValue[660]/10.0,'f',1).toFloat());
    ui->Auto_Speed5_Value->setValue(QString::number(AutoDataValue[661]/10.0,'f',1).toFloat());
    ui->Auto_Speed6_Value->setValue(QString::number(AutoDataValue[662]/10.0,'f',1).toFloat());
    ui->Auto_Speed7_Value->setValue(QString::number(AutoDataValue[663]/10.0,'f',1).toFloat());
    ui->Auto_Speed8_Value->setValue(QString::number(AutoDataValue[664]/10.0,'f',1).toFloat());

    ui->Auto_Speed1_Mode1_Value->setValue(QString::number(AutoDataValue[669]/10.0,'f',1).toFloat());
    ui->Auto_Speed2_Mode1_Value->setValue(QString::number(AutoDataValue[670]/10.0,'f',1).toFloat());
    ui->Auto_Speed3_Mode1_Value->setValue(QString::number(AutoDataValue[671]/10.0,'f',1).toFloat());
    ui->Auto_Speed4_Mode1_Value->setValue(QString::number(AutoDataValue[672]/10.0,'f',1).toFloat());
    ui->Auto_Speed5_Mode1_Value->setValue(QString::number(AutoDataValue[673]/10.0,'f',1).toFloat());
    ui->Auto_Speed6_Mode1_Value->setValue(QString::number(AutoDataValue[674]/10.0,'f',1).toFloat());
    ui->Auto_Speed7_Mode1_Value->setValue(QString::number(AutoDataValue[675]/10.0,'f',1).toFloat());
    ui->Auto_Speed8_Mode1_Value->setValue(QString::number(AutoDataValue[676]/10.0,'f',1).toFloat());
    
    ui->Auto_Speed1_Mode2_Value->setValue(QString::number(AutoDataValue[681]/10.0,'f',1).toFloat());
    ui->Auto_Speed2_Mode2_Value->setValue(QString::number(AutoDataValue[682]/10.0,'f',1).toFloat());
    ui->Auto_Speed3_Mode2_Value->setValue(QString::number(AutoDataValue[683]/10.0,'f',1).toFloat());
    ui->Auto_Speed4_Mode2_Value->setValue(QString::number(AutoDataValue[684]/10.0,'f',1).toFloat());
    ui->Auto_Speed5_Mode2_Value->setValue(QString::number(AutoDataValue[685]/10.0,'f',1).toFloat());
    ui->Auto_Speed6_Mode2_Value->setValue(QString::number(AutoDataValue[686]/10.0,'f',1).toFloat());
    ui->Auto_Speed7_Mode2_Value->setValue(QString::number(AutoDataValue[687]/10.0,'f',1).toFloat());
    ui->Auto_Speed8_Mode2_Value->setValue(QString::number(AutoDataValue[688]/10.0,'f',1).toFloat());
    
    ui->Auto_Speed1_Mode3_Value->setValue(QString::number(AutoDataValue[693]/10.0,'f',1).toFloat());
    ui->Auto_Speed2_Mode3_Value->setValue(QString::number(AutoDataValue[694]/10.0,'f',1).toFloat());
    ui->Auto_Speed3_Mode3_Value->setValue(QString::number(AutoDataValue[695]/10.0,'f',1).toFloat());
    ui->Auto_Speed4_Mode3_Value->setValue(QString::number(AutoDataValue[696]/10.0,'f',1).toFloat());
    ui->Auto_Speed5_Mode3_Value->setValue(QString::number(AutoDataValue[697]/10.0,'f',1).toFloat());
    ui->Auto_Speed6_Mode3_Value->setValue(QString::number(AutoDataValue[698]/10.0,'f',1).toFloat());
    ui->Auto_Speed7_Mode3_Value->setValue(QString::number(AutoDataValue[699]/10.0,'f',1).toFloat());
    ui->Auto_Speed8_Mode3_Value->setValue(QString::number(AutoDataValue[700]/10.0,'f',1).toFloat());
    
    ui->Auto_Speed1_Mode4_Value->setValue(QString::number(AutoDataValue[705]/10.0,'f',1).toFloat());
    ui->Auto_Speed2_Mode4_Value->setValue(QString::number(AutoDataValue[706]/10.0,'f',1).toFloat());
    ui->Auto_Speed3_Mode4_Value->setValue(QString::number(AutoDataValue[707]/10.0,'f',1).toFloat());
    ui->Auto_Speed4_Mode4_Value->setValue(QString::number(AutoDataValue[708]/10.0,'f',1).toFloat());
    ui->Auto_Speed5_Mode4_Value->setValue(QString::number(AutoDataValue[709]/10.0,'f',1).toFloat());
    ui->Auto_Speed6_Mode4_Value->setValue(QString::number(AutoDataValue[710]/10.0,'f',1).toFloat());
    ui->Auto_Speed7_Mode4_Value->setValue(QString::number(AutoDataValue[711]/10.0,'f',1).toFloat());
    ui->Auto_Speed8_Mode4_Value->setValue(QString::number(AutoDataValue[712]/10.0,'f',1).toFloat());
    
    ui->Auto_Speed1_Mode5_Value->setValue(QString::number(AutoDataValue[717]/10.0,'f',1).toFloat());
    ui->Auto_Speed2_Mode5_Value->setValue(QString::number(AutoDataValue[718]/10.0,'f',1).toFloat());
    ui->Auto_Speed3_Mode5_Value->setValue(QString::number(AutoDataValue[719]/10.0,'f',1).toFloat());
    ui->Auto_Speed4_Mode5_Value->setValue(QString::number(AutoDataValue[720]/10.0,'f',1).toFloat());
    ui->Auto_Speed5_Mode5_Value->setValue(QString::number(AutoDataValue[721]/10.0,'f',1).toFloat());
    ui->Auto_Speed6_Mode5_Value->setValue(QString::number(AutoDataValue[722]/10.0,'f',1).toFloat());
    ui->Auto_Speed7_Mode5_Value->setValue(QString::number(AutoDataValue[723]/10.0,'f',1).toFloat());
    ui->Auto_Speed8_Mode5_Value->setValue(QString::number(AutoDataValue[724]/10.0,'f',1).toFloat());
    
    ui->Auto_Speed1_Mode6_Value->setValue(QString::number(AutoDataValue[729]/10.0,'f',1).toFloat());
    ui->Auto_Speed2_Mode6_Value->setValue(QString::number(AutoDataValue[730]/10.0,'f',1).toFloat());
    ui->Auto_Speed3_Mode6_Value->setValue(QString::number(AutoDataValue[731]/10.0,'f',1).toFloat());
    ui->Auto_Speed4_Mode6_Value->setValue(QString::number(AutoDataValue[732]/10.0,'f',1).toFloat());
    ui->Auto_Speed5_Mode6_Value->setValue(QString::number(AutoDataValue[733]/10.0,'f',1).toFloat());
    ui->Auto_Speed6_Mode6_Value->setValue(QString::number(AutoDataValue[734]/10.0,'f',1).toFloat());
    ui->Auto_Speed7_Mode6_Value->setValue(QString::number(AutoDataValue[735]/10.0,'f',1).toFloat());
    ui->Auto_Speed8_Mode6_Value->setValue(QString::number(AutoDataValue[736]/10.0,'f',1).toFloat());
    
    ui->Auto_Speed1_Mode7_Value->setValue(QString::number(AutoDataValue[741]/10.0,'f',1).toFloat());
    ui->Auto_Speed2_Mode7_Value->setValue(QString::number(AutoDataValue[742]/10.0,'f',1).toFloat());
    ui->Auto_Speed3_Mode7_Value->setValue(QString::number(AutoDataValue[743]/10.0,'f',1).toFloat());
    ui->Auto_Speed4_Mode7_Value->setValue(QString::number(AutoDataValue[744]/10.0,'f',1).toFloat());
    ui->Auto_Speed5_Mode7_Value->setValue(QString::number(AutoDataValue[745]/10.0,'f',1).toFloat());
    ui->Auto_Speed6_Mode7_Value->setValue(QString::number(AutoDataValue[746]/10.0,'f',1).toFloat());
    ui->Auto_Speed7_Mode7_Value->setValue(QString::number(AutoDataValue[747]/10.0,'f',1).toFloat());
    ui->Auto_Speed8_Mode7_Value->setValue(QString::number(AutoDataValue[748]/10.0,'f',1).toFloat());
    
    ui->Auto_Speed1_Mode8_Value->setValue(QString::number(AutoDataValue[753]/10.0,'f',1).toFloat());
    ui->Auto_Speed2_Mode8_Value->setValue(QString::number(AutoDataValue[754]/10.0,'f',1).toFloat());
    ui->Auto_Speed3_Mode8_Value->setValue(QString::number(AutoDataValue[755]/10.0,'f',1).toFloat());
    ui->Auto_Speed4_Mode8_Value->setValue(QString::number(AutoDataValue[756]/10.0,'f',1).toFloat());
    ui->Auto_Speed5_Mode8_Value->setValue(QString::number(AutoDataValue[757]/10.0,'f',1).toFloat());
    ui->Auto_Speed6_Mode8_Value->setValue(QString::number(AutoDataValue[758]/10.0,'f',1).toFloat());
    ui->Auto_Speed7_Mode8_Value->setValue(QString::number(AutoDataValue[759]/10.0,'f',1).toFloat());
    ui->Auto_Speed8_Mode8_Value->setValue(QString::number(AutoDataValue[760]/10.0,'f',1).toFloat());

    if(Pop_OK_flag != AutoDataValue[769])
    {
        Pop_OK_flag = AutoDataValue[769];
        if(Pop_OK_flag == 1)
        {
            Pop_OK->show();
        }
        else
        {
            Pop_OK->hide();
        }
    }
    
    if(Pop_NG_flag != AutoDataValue[767])
    {
        Pop_NG_flag = AutoDataValue[767];
        if(Pop_NG_flag == 1)
        {
            Pop_NG->show();
            Pop_NG->setGeometry(680,0,640,256);
        }
        else
        {
            Pop_NG->hide();
        }
    }
    
    if(Pop_Alarm_flag != AutoDataValue[770])
    {
        Pop_Alarm_flag = AutoDataValue[770];
        if(Pop_Alarm_flag == 1)
        {
            Alarmdata = "";
            qDebug()<<"进入错误代码报警弹窗";
            Alarm_MessageData();
            Pop_Alarm->show();
            //            reszult =1;
        }
        else
        {
            Pop_Alarm->hide();
        }
    }
    
    //20250412改 增加极限位置
    //    ui->Auto_LIN1_1_ExtremeValue->setValue(AutoDataValue[859]);//LIN1-1极限位置
    //    ui->Auto_LIN1_2_ExtremeValue->setValue(AutoDataValue[860]);//LIN1-2极限位置
    //    ui->Auto_LIN1_3_ExtremeValue->setValue(AutoDataValue[861]);//LIN1-3极限位置
    //    ui->Auto_LIN1_4_ExtremeValue->setValue(AutoDataValue[862]);//LIN1-4极限位置
    //    ui->Auto_LIN1_5_ExtremeValue->setValue(AutoDataValue[863]);//LIN1-5极限位置
    //    ui->Auto_LIN1_6_ExtremeValue->setValue(AutoDataValue[864]);//LIN1-6极限位置
    //    ui->Auto_LIN1_7_ExtremeValue->setValue(AutoDataValue[865]);//LIN1-7极限位置
    //    ui->Auto_LIN1_8_ExtremeValue->setValue(AutoDataValue[866]);//LIN1-8极限位置
    //    ui->Auto_LIN1_9_ExtremeValue->setValue(AutoDataValue[867]);//LIN1-9极限位置
    //    ui->Auto_LIN1_10_ExtremeValue->setValue(AutoDataValue[868]);//LIN1-10极限位置
    //    ui->Auto_LIN1_11_ExtremeValue->setValue(AutoDataValue[869]);//LIN1-11极限位置
    //    ui->Auto_LIN1_12_ExtremeValue->setValue(AutoDataValue[870]);//LIN1-12极限位置
    //    ui->Auto_LIN1_13_ExtremeValue->setValue(AutoDataValue[871]);//LIN1-13极限位置
    //    ui->Auto_LIN1_14_ExtremeValue->setValue(AutoDataValue[872]);//LIN1-14极限位置
    //    ui->Auto_LIN1_15_ExtremeValue->setValue(AutoDataValue[873]);//LIN1-15极限位置




}
void MainWindow::Alarm_MessageData()
{
    Pop_Alarm->ui->Alarm_Message->clear();
    QString binaryString = QString::number(AutoDataValue[771], 2).rightJustified(16, '0').right(16);
    
    if(AutoDataValue[771]!= 0)//M10电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.320 M10电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(0);
            
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.321 M10电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(1);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.322 M10电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(3);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.323 M10电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(4);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.324 2线 M10电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(5);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.325 M10电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(6);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.326 M10电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(7);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.327 M10电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(8);
        }
    }
    binaryString = QString::number(AutoDataValue[772], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[772]!= 0)//M11电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.328 M11电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(9);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.329 M11电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(10);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.330 M11电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(11);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.331 M11电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(12);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.332 2线 M11电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(13);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.333 M11电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(14);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.334 M11电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(15);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.335 M11电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(16);
        }
    }
    binaryString = QString::number(AutoDataValue[773], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[773]!= 0)//M12电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.336 M12电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(17);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.337 M12电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(18);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.338 M12电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(19);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.339 M12电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(20);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.340 2线 M12电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(21);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.341 M12电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(22);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.342 M12电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(23);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.343 M12电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(24);
        }
    }
    binaryString = QString::number(AutoDataValue[774], 2).rightJustified(16, '0').right(16);
    //    Pop_Alarm->ui->Alarm_Message->append("判定4："+binaryString+QString::number(AutoDataValue[774]));
    if(AutoDataValue[774]!= 0)//M13电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.344 M13电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(25);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.345 M13电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(26);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.346 M13电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(27);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.347 M13电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(28);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.348 2线 M13电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(29);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.349 M13电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(30);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.350 M13电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(31);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.351 M13电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(32);
        }
    }
    binaryString = QString::number(AutoDataValue[775], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[775]!= 0)//M14电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.352 M14电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(33);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.353 M14电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(34);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.354 M14电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(35);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.355 M14电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(36);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.356 2线 M14电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(37);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.357 M14电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(38);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.358 M14电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(39);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.359 M14电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(40);
        }
    }
    binaryString = QString::number(AutoDataValue[776], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[776]!= 0)//M15电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.360 M15电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(41);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.361 M15电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(42);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.362 M15电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(43);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.363 M15电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(44);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.363 2线 M15电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(45);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.364 M15电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(46);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.365 M15电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(47);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.366 M15电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(48);
        }
    }
    binaryString = QString::number(AutoDataValue[777], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[777]!= 0)//M16电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.367 M16电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(49);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.368 M16电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(50);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.369 M16电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(51);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.370 M16电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(52);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.371 2线 M16电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(53);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.372 M16电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(54);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.373 M16电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(55);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.374 M16电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(56);
        }
    }
    binaryString = QString::number(AutoDataValue[778], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[778]!= 0)//M17电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.375 M17电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(57);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.376 M17电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(58);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.377 M17电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(59);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.378 M17电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(60);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.379 2线 M17电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(61);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.380 M17电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(62);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.381 M17电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(63);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.382 M17电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(64);
        }
    }
    binaryString = QString::number(AutoDataValue[779], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[779]!= 0)//M18电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.383 M18电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(65);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.384 M18电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(66);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.385 M18电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(67);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.386 M18电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(68);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.387 2线 M18电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(69);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.388 M18电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(70);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.389 M18电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(71);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.390 M18电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(72);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻8超限");
            Alarmdata = Alarmdata+"、D"+QString::number(73);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻9超限");
            Alarmdata = Alarmdata+"、D"+QString::number(74);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻10超限");
            Alarmdata = Alarmdata+"、D"+QString::number(75);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻11超限");
            Alarmdata = Alarmdata+"、D"+QString::number(76);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻12超限");
            Alarmdata = Alarmdata+"、D"+QString::number(77);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻13超限");
            Alarmdata = Alarmdata+"、D"+QString::number(78);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻14超限");
            Alarmdata = Alarmdata+"、D"+QString::number(79);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            
        }
    }
    binaryString = QString::number(AutoDataValue[780], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[780]!= 0)//温敏8到温敏14
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻8断路");
            Alarmdata = Alarmdata+"、D"+QString::number(80);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻8短路");
            Alarmdata = Alarmdata+"、D"+QString::number(81);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻9断路");
            Alarmdata = Alarmdata+"、D"+QString::number(82);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻9短路");
            Alarmdata = Alarmdata+"、D"+QString::number(83);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻10断路");
            Alarmdata = Alarmdata+"、D"+QString::number(84);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻10短路");
            Alarmdata = Alarmdata+"、D"+QString::number(85);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻11断路");
            Alarmdata = Alarmdata+"、D"+QString::number(86);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻11短路");
            Alarmdata = Alarmdata+"、D"+QString::number(87);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻12断路");
            Alarmdata = Alarmdata+"、D"+QString::number(88);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻12短路");
            Alarmdata = Alarmdata+"、D"+QString::number(89);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻13断路");
            Alarmdata = Alarmdata+"、D"+QString::number(90);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻13短路");
            Alarmdata = Alarmdata+"、D"+QString::number(91);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻14断路");
            Alarmdata = Alarmdata+"、D"+QString::number(92);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("温敏电阻14短路");
            Alarmdata = Alarmdata+"、D"+QString::number(93);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            
        }
    }
    binaryString = QString::number(AutoDataValue[781], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[781]!= 0)//M1电机，M2电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.1 M1电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(94);
            
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.2 M1电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(95);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.3 M1电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(96);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.4 M1电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(97);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.5 2线M1电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(98);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.6 M1电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(99);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.7 M1电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(100);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.8 M1电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(101);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.9 M2电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(102);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.10 M2电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(103);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.11 M2电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(104);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.12 M2电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(105);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.13 2线M2电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(106);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.14 M2电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(107);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.15 M2电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(108);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.16 M2电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(109);
        }
    }
    binaryString = QString::number(AutoDataValue[782], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[782]!= 0)//M3电机，M4电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.17 M3电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(110);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.18 M3电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(111);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.19 M3电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(112);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.20 M3电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(113);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.21 2线M3电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(114);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.22 M3电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(115);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.23 M3电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(116);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.24 M3电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(117);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.25 M4电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(118);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.26 M4电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(119);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.27 M4电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(120);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.28 M4电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(121);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.29 2线M4电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(122);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.30 M4电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(123);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.31 M4电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(124);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.32 M4电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(125);
        }
    }
    binaryString = QString::number(AutoDataValue[783], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[783]!= 0)//M5电机
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.33 M5电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(126);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.34 M5电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(127);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.35 M5极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(128);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.36 M5极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(129);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.37 2线M5卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(130);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.38 M5运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(131);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.39 M5断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(132);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.40 M5 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(133);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.41 温敏电阻1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(134);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.42 温敏电阻2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(135);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.43 温敏电阻3超限");
            Alarmdata = Alarmdata+"、D"+QString::number(136);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.44 温敏电阻4超限");
            Alarmdata = Alarmdata+"、D"+QString::number(137);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.45 温敏电阻5超限");
            Alarmdata = Alarmdata+"、D"+QString::number(138);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.46 温敏电阻6超限");
            Alarmdata = Alarmdata+"、D"+QString::number(139);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.47 室内温敏电阻超限");
            Alarmdata = Alarmdata+"、D"+QString::number(140);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.48 鼓风机声音异常");
            Alarmdata = Alarmdata+"、D"+QString::number(141);
        }
    }
    binaryString = QString::number(AutoDataValue[784], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[784]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.49 温敏电阻1断路");
            Alarmdata = Alarmdata+"、D"+QString::number(142);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.50 温敏电阻1短路");
            Alarmdata = Alarmdata+"、D"+QString::number(143);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.51 温敏电阻2断路");
            Alarmdata = Alarmdata+"、D"+QString::number(144);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.52 温敏电阻2短路");
            Alarmdata = Alarmdata+"、D"+QString::number(145);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.53 温敏电阻3断路");
            Alarmdata = Alarmdata+"、D"+QString::number(146);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.54 温敏电阻3短路");
            Alarmdata = Alarmdata+"、D"+QString::number(147);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.55 温敏电阻4断路");
            Alarmdata = Alarmdata+"、D"+QString::number(148);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.56 温敏电阻4短路");
            Alarmdata = Alarmdata+"、D"+QString::number(149);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.57 温敏电阻5断路");
            Alarmdata = Alarmdata+"、D"+QString::number(150);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.58 温敏电阻5短路");
            Alarmdata = Alarmdata+"、D"+QString::number(151);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.59 温敏电阻6断路");
            Alarmdata = Alarmdata+"、D"+QString::number(152);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.60 温敏电阻6短路");
            Alarmdata = Alarmdata+"、D"+QString::number(153);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.61 室内温敏电阻断路");
            Alarmdata = Alarmdata+"、D"+QString::number(154);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.62 室内温敏电阻短路");
            Alarmdata = Alarmdata+"、D"+QString::number(155);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.63 风速1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(156);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.64 风速2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(157);
        }
    }
    binaryString = QString::number(AutoDataValue[785], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[785]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.65 风速3超限");
            Alarmdata = Alarmdata+"、D"+QString::number(158);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.66 风速4超限");
            Alarmdata = Alarmdata+"、D"+QString::number(159);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.67 风速5超限");
            Alarmdata = Alarmdata+"、D"+QString::number(160);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.68 风速6超限");
            Alarmdata = Alarmdata+"、D"+QString::number(161);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.69 风速7超限");
            Alarmdata = Alarmdata+"、D"+QString::number(162);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.70 风速8超限");
            Alarmdata = Alarmdata+"、D"+QString::number(163);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            
        }
    }
    binaryString = QString::number(AutoDataValue[786], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[786]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.91 鼓风机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(164);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.92 鼓风机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(165);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.93 鼓风机线束插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(166);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.94 X轴振动超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(167);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.95 X轴振动超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(168);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.96 Y轴振动超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(169);
        }
    }
    binaryString = QString::number(AutoDataValue[787], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[787]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.97 Y轴振动超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(170);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.98 Z轴振动超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(171);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.99 Z轴振动超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(172);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.100 噪音值超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(173);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.101 噪音值超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(174);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.102 人工判断NG");
            Alarmdata = Alarmdata+"、D"+QString::number(175);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.103 一档风速检测NG");
            Alarmdata = Alarmdata+"、D"+QString::number(176);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.104 ECU通讯失败");
            Alarmdata = Alarmdata+"、D"+QString::number(177);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.105 ECU产品型号不匹配");
            Alarmdata = Alarmdata+"、D"+QString::number(178);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.106 ECU APP版本不匹配");
            Alarmdata = Alarmdata+"、D"+QString::number(179);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.107 ECU BOOT版本不匹配");
            Alarmdata = Alarmdata+"、D"+QString::number(180);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.108 ECU 硬件版本不匹配");
            Alarmdata = Alarmdata+"、D"+QString::number(181);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.109 LIN总电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(182);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.110 LIN总电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(183);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.111 LIN 1.X通讯错误");
            Alarmdata = Alarmdata+"、D"+QString::number(184);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.112 LIN2.X通讯错误");
            Alarmdata = Alarmdata+"、D"+QString::number(185);
        }
    }
    binaryString = QString::number(AutoDataValue[788], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[788]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.114 PM2.5浓度与等级不匹配");
            Alarmdata = Alarmdata+"、D"+QString::number(186);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.115 PM2.5通讯失败");
            Alarmdata = Alarmdata+"、D"+QString::number(187);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.116 负离子发生器超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(188);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.117 负离子发生器超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(189);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.118 PLC与PC通讯失败");
            Alarmdata = Alarmdata+"、D"+QString::number(190);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.119 生产号重复，打印错误。");
            Alarmdata = Alarmdata+"、D"+QString::number(191);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.120 急停按钮被按下");
            Alarmdata = Alarmdata+"、D"+QString::number(192);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.121 静音房门被打开");
            Alarmdata = Alarmdata+"、D"+QString::number(193);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.122 负离子反馈电压超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(194);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.123 负离子反馈电压超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(195);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.124 负离子电流过大");
            Alarmdata = Alarmdata+"、D"+QString::number(196);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.125 负离子断线");
            Alarmdata = Alarmdata+"、D"+QString::number(197);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.126 AQS反馈电压超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(198);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.127 AQS反馈电压超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(199);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.128 LINK声音异常");
            Alarmdata = Alarmdata+"、D"+QString::number(200);
        }
    }
    
    binaryString = QString::number(AutoDataValue[790], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[790]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.145 风门位置1时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(201);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.146 风门位置1超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(202);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.147 风门位置1超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(203);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.148 风门位置2时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(204);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.149 风门位置2超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(205);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.150 风门位置2超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(206);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.151 条码与空调不对应");
            Alarmdata = Alarmdata+"、D"+QString::number(207);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.152 LIN2电机1发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(208);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.153 LIN2电机1断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(209);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.154 LIN2电机2发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(210);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.155 LIN2电机2断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(211);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.156 LIN2电机3发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(212);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.157 LIN2电机3断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(213);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.158 LIN2电机4发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(214);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.159 LIN2电机4断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(215);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.160 PLC电池电压过低，请更换电池");
            Alarmdata = Alarmdata+"、D"+QString::number(216);
        }
    }
    binaryString = QString::number(AutoDataValue[791], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[791]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.161 M6电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(217);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.162 M6电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(218);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.163 M6电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(219);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.164 M6电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(220);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.165 2线M6电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(221);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.166 M6电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(222);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.167 M6电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(223);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.168 M6电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(224);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.169 M7电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(225);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.170 M7电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(226);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.171 M7电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(227);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.172 M7电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(228);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.173 2线M7电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(229);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.174 M7电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(230);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.175 M7电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(231);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.176 M7电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(232);
        }
    }
    binaryString = QString::number(AutoDataValue[792], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[792]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.177 M8电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(233);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.178 M8电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(234);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.179 M8电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(235);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.180 M8电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(236);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.181 2线M8电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(237);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.182 M8电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(238);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.183 M8电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(239);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.184 M8电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(240);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.185 M9电机电流超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(241);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.186 M9电机电流超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(242);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.187 M9电机极限位置1超限");
            Alarmdata = Alarmdata+"、D"+QString::number(243);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.188 M9电机极限位置2超限");
            Alarmdata = Alarmdata+"、D"+QString::number(244);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.189 2线M9电机卡滞");
            Alarmdata = Alarmdata+"、D"+QString::number(245);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.190 M9电机运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(246);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.191 M9电机断线或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(247);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.192 M9电机 5线与2线错装");
            Alarmdata = Alarmdata+"、D"+QString::number(248);
        }
    }
    binaryString = QString::number(AutoDataValue[793], 2).rightJustified(16, '0').right(16);
    //    Pop_Alarm->ui->Alarm_Message->append("判定23："+binaryString);
    if(AutoDataValue[793]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.193 LIN2.X 电机1运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(249);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.194 LIN2.X 电机2运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(250);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.195 LIN2.X 电机3运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(251);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.196  LIN2.X 电机4运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(252);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.197 PTC电压超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(253);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.198 PTC电压超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(254);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.199 LIN2.x 电机5发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(255);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.200 LIN2.x 电机5断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(256);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.201 LIN2.X 电机5运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(257);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.202 LIN2.X-PM2.5插头未插或断线");
            Alarmdata = Alarmdata+"、D"+QString::number(258);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.203 LIN2.X-AQS插头未插或断线");
            Alarmdata = Alarmdata+"、D"+QString::number(259);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.204 车内PM2.5浓度超限");
            Alarmdata = Alarmdata+"、D"+QString::number(260);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.205 车外PM2.5浓度超限");
            Alarmdata = Alarmdata+"、D"+QString::number(261);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.206 AQS空气质量超限");
            Alarmdata = Alarmdata+"、D"+QString::number(262);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.207 PM2.5通讯错误或传感器故障");
            Alarmdata = Alarmdata+"、D"+QString::number(263);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            
        }
    }
    binaryString = QString::number(AutoDataValue[794], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[794]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.209 LIN2.X 电机6发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(264);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.210 LIN2.X电机6断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(265);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.211 LIN2.X 电机7发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(266);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.212 LIN2.X 电机7断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(267);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.213 LIN2.X电机8发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(268);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.214 LIN2.X电机8断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(269);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.215 LIN2.X电机9发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(270);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.216 LIN2.X电机9断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(271);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.217 LIN2.X电机6运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(272);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.218 LIN2.X电机7运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(273);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.219 LIN2.X电机8运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(274);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.220 LIN2.X电机9运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(275);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.221 LIN2.X电机10发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(276);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.222 LIN2.X电机10断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(277);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.223 LIN2.X 电机10运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(278);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.224 LIN鼓风机诊断标志/响应错误");
            Alarmdata = Alarmdata+"、D"+QString::number(279);
        }
    }
    binaryString = QString::number(AutoDataValue[795], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[795]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.225 LIN1.X 电机1发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(280);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.226 LIN1.X 电机1断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(281);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.227 LIN1.X 电机2发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(282);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.228 LIN1.X 电机2断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(283);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.229 LIN1.X 电机3发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(284);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.230 LIN1.X 电机3断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(285);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.231 LIN1.X 电机4发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(286);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.232 LIN1.X 电机4断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(287);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.233 LIN1.X 电机1运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(288);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.234 LIN1.X 电机2运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(289);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.235 LIN1.X 电机3运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(290);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.236 LIN1.X 电机4运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(291);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.237 LIN1.X 电机5发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(292);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.238 LIN1.X 电机5断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(293);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.239 LIN1.X 电机5运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(294);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.240 LIN1.X 电机6发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(295);
        }
    }
    binaryString = QString::number(AutoDataValue[796], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[796]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.241 LIN1.X 电机6断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(296);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.242 LIN1.X 电机7发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(297);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.243 LIN1.X 电机7断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(298);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.244 LIN1.X 电机8发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(299);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.245 LIN1.X 电机8断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(300);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.246 LIN1.X 电机9发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(200);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.247 LIN1.X 电机9断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(301);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.248 LIN1.X 电机6运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(302);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.249 LIN1.X 电机7运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(303);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.250 LIN1.X 电机8运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(304);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.251 LIN1.X 电机9运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(305);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.252 LIN1.X 电机10发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(306);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.253 LIN1.X 电机10断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(307);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.254 LIN1.X 电机10运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(308);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.255 后左M2电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(309);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.256 前左M2电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(310);
        }
    }
    binaryString = QString::number(AutoDataValue[797], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[797]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.257 前左吹面电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(311);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.258 后左吹面电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(312);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.259 左双层流电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(313);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.260 后右吹面电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(314);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.261 后右M2电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(315);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.262 后双层流电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(316);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.263 前右M2电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(317);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.264 前右吹面电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(318);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.265 后左吹脚电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(319);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.266 前左吹脚电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(320);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.267 后右吹脚电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(321);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.268 前右吹脚电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(322);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.269 LIN除霜电机 ID错误");
            Alarmdata = Alarmdata+"、D"+QString::number(323);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.270 电子膨胀阀通信错误或故障");
            Alarmdata = Alarmdata+"、D"+QString::number(324);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.271 电子膨胀阀运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(325);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.272 PTC读取错误或插头未插");
            Alarmdata = Alarmdata+"、D"+QString::number(326);
        }
    }
    binaryString = QString::number(AutoDataValue[798], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[798]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.273 PTC软/硬件版本号错误");
            Alarmdata = Alarmdata+"、D"+QString::number(327);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.275 LIN1.X整体电机回原点超时");
            Alarmdata = Alarmdata+"、D"+QString::number(328);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.276 LIN2.X整体电机回原点超时");
            Alarmdata = Alarmdata+"、D"+QString::number(329);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机11发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(330);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机11断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(331);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机12发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(332);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机12断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(333);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机13发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(334);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机13断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(335);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机14发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(336);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机14断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(337);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机11运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(338);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机12运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(339);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机13运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(340);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机14运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(341);
        }
    }
    binaryString = QString::number(AutoDataValue[799], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[799]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机15发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(342);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN2电机15断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(343);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN15运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(345);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机11发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(346);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机11断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(347);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机12发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(348);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机12断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(349);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机13发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(350);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机13断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(351);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机14发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(352);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机14断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(353);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机11运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(354);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机12运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(355);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机13运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(356);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机14运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(357);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机15发生堵转");
            Alarmdata = Alarmdata+"、D"+QString::number(358);
        }
    }
    binaryString = QString::number(AutoDataValue[800], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[800]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN1电机15断线或未插");
            Alarmdata = Alarmdata+"、D"+QString::number(359);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("LIN15运行时间超限");
            Alarmdata = Alarmdata+"、D"+QString::number(360);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.313 第四轴振动超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(361);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.314 第四轴振动超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(362);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.277 风速9超限");
            Alarmdata = Alarmdata+"、D"+QString::number(363);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.278 风速10超限");
            Alarmdata = Alarmdata+"、D"+QString::number(364);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.279 风速11超限");
            Alarmdata = Alarmdata+"、D"+QString::number(365);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.280 风速12超限");
            Alarmdata = Alarmdata+"、D"+QString::number(366);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.315 鼓风机软件版本错误");
            Alarmdata = Alarmdata+"、D"+QString::number(367);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.316 鼓风机硬件版本错误");
            Alarmdata = Alarmdata+"、D"+QString::number(368);
        }
    }
    binaryString = QString::number(AutoDataValue[789], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[789]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {
            
            Pop_Alarm->ui->Alarm_Message->append("NO.129鼓风机第1步骤端电压超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(369);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.130鼓风机第1步骤端电压超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(370);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.131鼓风机第2步骤端电压超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(371);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.132鼓风机第2步骤端电压超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(372);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.133鼓风机第3步骤端电压超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(373);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.134鼓风机第3步骤端电压超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(374);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.135鼓风机第4步骤端电压超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(375);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.136鼓风机第4步骤端电压超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(376);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.137鼓风机第5步骤端电压超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(377);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.138鼓风机第5步骤端电压超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(378);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.139鼓风机第6步骤端电压超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(379);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.140鼓风机第6步骤端电压超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(380);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.141鼓风机第7步骤端电压超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(381);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.142鼓风机第7步骤端电压超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(382);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.143鼓风机第8步骤端电压超上限");
            Alarmdata = Alarmdata+"、D"+QString::number(383);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.144鼓风机第8步骤端电压超下限");
            Alarmdata = Alarmdata+"、D"+QString::number(384);
        }
    }
    binaryString = QString::number(AutoDataValue[889], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[889]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {

            Pop_Alarm->ui->Alarm_Message->append("NO.281 LIN2-1电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(385);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.282 LIN2-2电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(386);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.283 LIN2-3电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(387);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.284 LIN2-4电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(388);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.285 LIN2-5电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(389);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.286 LIN2-6电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(390);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.287 LIN2-7电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(391);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.288 LIN2-8电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(392);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.289 LIN2-9电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(393);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.290 LIN2-10电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(394);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.291 LIN2-11电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(395);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.292 LIN2-12电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(396);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.293 LIN2-13电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(397);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.294 LIN2-14电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(398);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.295 LIN2-15电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(399);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.296 LIN2电机整体初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(400);
        }
    }
    binaryString = QString::number(AutoDataValue[890], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[890]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {

            Pop_Alarm->ui->Alarm_Message->append("NO.71 LIN1-1电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(401);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.72 LIN1-2电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(402);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.73 LIN1-3电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(403);
        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.74 LIN1-4电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(404);
        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.75 LIN1-5电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(405);
        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.76 LIN1-6电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(406);
        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.77 LIN1-7电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(407);
        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.78 LIN1-8电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(408);
        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.79 LIN1-9电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(409);
        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.70 LIN1-10电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(410);
        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.71 LIN1-11电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(411);
        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.72 LIN1-12电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(412);
        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.73 LIN1-13电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(413);
        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.74 LIN1-14电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(414);
        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.75 LIN1-15电机初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(415);
        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.76 LIN1电机整体初始化失败");
            Alarmdata = Alarmdata+"、D"+QString::number(416);
        }
    }
    binaryString = QString::number(AutoDataValue[891], 2).rightJustified(16, '0').right(16);
    if(AutoDataValue[891]!= 0)
    {
        if(binaryString.at(15) == QLatin1Char('1'))
        {

            Pop_Alarm->ui->Alarm_Message->append("NO.297 PM2.5软/硬件版本错误");
            Alarmdata = Alarmdata+"、D"+QString::number(417);
        }
        if(binaryString.at(14) == QLatin1Char('1'))
        {
            Pop_Alarm->ui->Alarm_Message->append("NO.298 AQS软/硬件版本错误");
            Alarmdata = Alarmdata+"、D"+QString::number(418);
        }
        if(binaryString.at(13) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(12) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(11) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(10) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(9) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(8) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(7) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(6) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(5) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(4) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(3) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(2) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(1) == QLatin1Char('1'))
        {

        }
        if(binaryString.at(0) == QLatin1Char('1'))
        {

        }
    }
    qDebug()<<"此次检测错误代码为："<<Alarmdata;
}

void MainWindow::Slot_MySql_JDL_writeOK(int PD,QString index)
{
    //index为检测OK后的流水号 liushuihao_flag为记录的上一台OK流水号
    if(liushuihao_OKflag!=index)
    {
        liushuihao_OKflag = index;
        QSqlQuery query(Sqlserverdb);
        QString sql = QString("SELECT 电检OK数量 FROM jianghuai_songz.plan_number WHERE 频道号 = %1").arg(PD);
        if (!query.exec(sql))
        {
            qDebug() << "查询数据库OK数量错误:" << query.lastError().text();
        }
        // 3. 获取查询结果
        if (query.next())
        {
            QVariant value = query.value(0); // 获取第一列的数据
            //            qDebug() << "Value from database:" << value.toString();
            QString sql = QString("UPDATE jianghuai_songz.plan_number SET 电检OK数量 = %1 WHERE 频道号 = %2").arg(value.toInt()+1).arg(PD);
            if (!query.exec(sql))
            {
                qDebug() << "查询数据库OK数量错误:" << query.lastError().text();
            }
        }
        else //无结果
        {
            QString sql = QString("UPDATE jianghuai_songz.plan_number SET 电检OK数量 = %1 WHERE 频道号 = %2").arg(1).arg(PD);
            if (!query.exec(sql))
            {
                qDebug() << "查询数据库OK数量错误:" << query.lastError().text();
            }
        }
        
    }
    
}

void MainWindow::Slot_MySql_JDL_writeALL(int Result,int PD,QString index)
{
    if(liushuihao_flag!=index)
    {
        if(Result==1 || Result==2)
        {
            liushuihao_flag = index;
            QSqlQuery query(Sqlserverdb);
            QString sql = QString("SELECT 电检总数量 FROM jianghuai_songz.plan_number WHERE 频道号 = %1").arg(PD);
            if (!query.exec(sql))
            {
                qDebug() << "查询数据库电检总数量错误:" << query.lastError().text();
            }
            // 3. 获取查询结果
            if (query.next())
            {
                QVariant value = query.value(0); // 获取数据库数据
                //                qDebug() << "Value from database:" << value.toString();
                QString sql = QString("UPDATE jianghuai_songz.plan_number SET 电检总数量 = %1 WHERE 频道号 = %2").arg(value.toInt()+1).arg(PD);
                if (!query.exec(sql))
                {
                    qDebug() << "查询数据库电检总数量错误:" << query.lastError().text();
                }
            }
            else //无结果
            {
                QString sql = QString("UPDATE jianghuai_songz.plan_number SET 电检总数量 = %1 WHERE 频道号 = %2").arg(1).arg(PD);
                if (!query.exec(sql))
                {
                    qDebug() << "查询数据库电检总数量错误:" << query.lastError().text();
                }
            }
            
        }
        //        else if(Result==2)
        //        {
        //            QSqlQuery query(Sqlserverdb);
        //            QString sql = QString("SELECT 电检总数量 FROM jianghuai_songz.plan_number WHERE 频道号 = %1").arg(PD);
        //            if (!query.exec(sql))
        //            {
        //                qDebug() << "查询数据库电检总数量错误:" << query.lastError().text();
        //            }
        //            // 3. 获取查询结果
        //            if (query.next())
        //            {
        //                QVariant value = query.value(0); // 获取第一列的数据
        //                //                qDebug() << "Value from database:" << value.toString();
        //                if(value.toInt()>0)
        //                {
        //                    QString sql = QString("UPDATE jianghuai_songz.plan_number SET 电检总数量 = %1 WHERE 频道号 = %2").arg(value.toInt()-1).arg(PD);
        //                }
        //                else
        //                {
        //                    qDebug() << "数据库电检总数量为0或空白";
        //                }

        //                if (!query.exec(sql))
        //                {
        //                    qDebug() << "查询数据库电检总数量错误:" << query.lastError().text();
        //                }
        //            }
        //            else //无结果
        //            {
        //                QString sql = QString("UPDATE jianghuai_songz.plan_number SET 电检总数量 = %1 WHERE 频道号 = %2").arg(0).arg(PD);
        //                if (!query.exec(sql))
        //                {
        //                    qDebug() << "查询数据库电检总数量错误:" << query.lastError().text();
        //                }
        //            }

        //        }
    }
    //    else
    //    {
    //        qDebug()<<"检测到相同的流水号，OK检测后再次检测";
    //  }

}


void MainWindow::Data_Processing()//数据处理
{
    xinghao = ui->Auto_Model->text();
    //-------------------------------------检测结果-------------------------------------
    if(ZSDataValue[1]== 1)
    {
        if(reszult == 0)
        {
            reszult =  1;
        }
    }
    else if(ZSDataValue[1]== 3)
    {
        if(reszult == 0)
        {
            reszult =  1;

        }
    }
    //-------------------------------------sql数据保存-------------------------------------
    if(reszult == 1)
    {
        
        qDebug()<<"开始追溯";
        reszult = 2;
        sqldata[1] = QString::number(ZSDataValue[5]);//"频道号"
        sqldata[2] = xinghao;
        sqldata[3] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        sqldata[4] = liushuihao;
        sqldata[5] = shangxianma;
        //        qDebug()<<"当前错误代码为:"<< Alarmdata<<"流水号:"<<liushuihao;
        if(Alarmdata.isEmpty())
        {
            Alarmdata = "无";
        }
        else
        {
            //            Alarm_MessageData();

            sqldata[9] = Alarmdata;
            if(sqldata[9].mid(0,1)=="、")
            {
                sqldata[9]  = sqldata[9].remove(0,1);
            }
        }
        sqldata[10] = QString::number(ZSDataValue[2]/10.0,'f', 2);
        sqldata[7] = Inplacetimes;
        if(liushuihao.mid(0,1) == "E")
        {
            sqldata[6] = "返修";
        }
        else
        {
            sqldata[6] = "正常";
        }
        //        Slot_MySql_JDL_writeALL(QString Result,int PD,QString index);
        if(ZSDataValue[1] == 1)//检测结果判断
        {
            sqldata[8] = "OK";
            qDebug()<<"产品检测OK";
            sqldata[9]  ="无";
            //            ScreenshotOK();
            Slot_MySql_JDL_writeOK(sqldata[1].toInt(),liushuihao);
            Slot_MySql_JDL_writeALL(1,sqldata[1].toInt(),liushuihao);
        }
        else
        {
            sqldata[8] = "NG";
            qDebug()<<"产品检测NG";
            qDebug()<<"当前错误代码为:"<< Alarmdata;
            //            ScreenshotNG();
            Slot_MySql_JDL_writeALL(2,sqldata[1].toInt(),liushuihao);
        }
        
        
        //-------------------------------------鼓风机-------------------------------------
        //         qDebug()<<"问题1";
        if(ZSDataValue[46] == 0)
        {
            Allresults[0] = "未检测";
        }
        else if(ZSDataValue[46]== 1)
        {
            Allresults[0] = "OK";
        }
        else if(ZSDataValue[46]== 2)
        {
            Allresults[0] = "检测中";
        }
        else if(ZSDataValue[46]== 3)
        {
            Allresults[0] = "NG";
        }
        sqldata1Blower[0] = QString::number(ZSDataValue[45]);
        
        //        sqldata1Blower[1] = QString("%1").arg(ZSDataValue[820], 0, 16);
        //        sqldata1Blower[2] = QString("%1").arg(ZSDataValue[821], 0, 16);
        
        unsigned char highByte = (ZSDataValue[820] >> 8) & 0xFF;
        unsigned char lowByte = ZSDataValue[820] & 0xFF;
        // 转换为ASCII字符
        QChar highChar(highByte);
        QChar lowChar(lowByte);
        QString ASCII;
        ASCII  =  ASCII.append(lowByte);
        ASCII  =  ASCII.append(highChar);
        QChar rep_str = 0x00;
        if (ASCII.contains(rep_str))
        {
            ASCII.replace(rep_str,"");
        }
        if(ASCII.isEmpty())
        {
            ASCII = "";
        }
        // 输出结果
        //        qDebug() << "High Byte Char:" << highChar;
        //        qDebug() << "Low Byte Char:" << lowChar;
        //        qDebug() << "结果:" << ASCII;
        sqldata1Blower[2] = ASCII;
        unsigned char highByte_2 = (ZSDataValue[821] >> 8) & 0xFF;
        unsigned char lowByte_2 = ZSDataValue[821] & 0xFF;
        // 转换为ASCII字符
        QChar lowChar_2(lowByte_2);
        QChar highChar_2(highByte_2);
        QString ASCII_2;
        ASCII_2  =  ASCII_2.append(lowByte_2);
        ASCII_2  =  ASCII_2.append(highByte_2);
        if (ASCII_2.contains(rep_str))
        {
            ASCII_2.replace(rep_str,"");
        }
        if(ASCII_2.isEmpty())
        {
            ASCII_2 = "";
        }
        sqldata1Blower[1] = ASCII_2;
        
        
        sqldata1Blower[3] = QString::number(ZSDataValue[49]);//1
        sqldata1Blower[4] = QString::number(ZSDataValue[47]/100.0,'f', 2);
        //        sqldata1Blower[5] = QString::number(ZSDataValue[48]);
        
        sqldata1Blower[5] = QString::number(ZSDataValue[52]);//2
        sqldata1Blower[6] = QString::number(ZSDataValue[50]/100.0,'f', 2);
        //        sqldata1Blower[8] = QString::number(ZSDataValue[51]);
        
        sqldata1Blower[7] = QString::number(ZSDataValue[55]);//3
        sqldata1Blower[8] = QString::number(ZSDataValue[53]/100.0,'f', 2);
        //        sqldata1Blower[11] = QString::number(ZSDataValue[54]);
        
        sqldata1Blower[9] = QString::number(ZSDataValue[58]);//4
        sqldata1Blower[10] = QString::number(ZSDataValue[56]/100.0,'f', 2);
        //        sqldata1Blower[14] = QString::number(ZSDataValue[57]);
        
        sqldata1Blower[11] = QString::number(ZSDataValue[61]);//5
        sqldata1Blower[12] = QString::number(ZSDataValue[59]/100.0,'f', 2);
        //        sqldata1Blower[17] = QString::number(ZSDataValue[60]);
        
        sqldata1Blower[13] = QString::number(ZSDataValue[64]);//6
        sqldata1Blower[14] = QString::number(ZSDataValue[62]/100.0,'f', 2);
        //        sqldata1Blower[20] = QString::number(ZSDataValue[63]);
        
        sqldata1Blower[15] = QString::number(ZSDataValue[67]);//7
        sqldata1Blower[16] = QString::number(ZSDataValue[65]/100.0,'f', 2);
        //        sqldata1Blower[23] = QString::number(ZSDataValue[66]);
        
        sqldata1Blower[17] = QString::number(ZSDataValue[70]);//8
        sqldata1Blower[18] = QString::number(ZSDataValue[68]/100.0,'f', 2);
        //        sqldata1Blower[26] = QString::number(ZSDataValue[69]);
        
        sqldata1Blower[19] = QString::number(ZSDataValue[73]);//9
        sqldata1Blower[20] = QString::number(ZSDataValue[71]/100.0,'f', 2);
        //        sqldata1Blower[29] = QString::number(ZSDataValue[72]);
        
        //         qDebug()<<"问题2";
        //--------------------------------------LIN1电机--------------------------------------
        if (ZSDataValue[76]==0 || ZSDataValue[76]==1 || ZSDataValue[76]==2 || ZSDataValue[76]==3)//LIN1.1 未检测或OK或NG
        {
            if(ZSDataValue[76]==0)
            {
                Allresults[1] = "未检测";
                LIN1NAD[0] = QString::number(0);
                LIN1ControlID[0] = QString::number(0);
                LIN1StateID[0] = QString::number(0);
            }
            else if(ZSDataValue[76] == 1)
            {
                Allresults[1] = "OK";
                LIN1NAD[0] = QString("%1").arg(ZSDataValue[77], 0, 16);
                LIN1ControlID[0] = QString("%1").arg(ZSDataValue[78], 0, 16);
                LIN1StateID[0] = QString("%1").arg(ZSDataValue[79], 0, 16);
            }
            else if(ZSDataValue[76] == 2)
            {
                Allresults[1] = "检测中";
                LIN1NAD[0] = QString("%1").arg(ZSDataValue[77], 0, 16);
                LIN1ControlID[0] = QString("%1").arg(ZSDataValue[78], 0, 16);
                LIN1StateID[0] = QString("%1").arg(ZSDataValue[79], 0, 16);
            }
            else if(ZSDataValue[76] == 3)
            {
                Allresults[1] = "NG";
                LIN1NAD[0] = QString("%1").arg(ZSDataValue[77], 0, 16);
                LIN1ControlID[0] = QString("%1").arg(ZSDataValue[78], 0, 16);
                LIN1StateID[0] = QString("%1").arg(ZSDataValue[79], 0, 16);
            }
            //            for(int i = 0;i<sqldataLIN1_1.count();i++)
            //            {
            //                sqldataLIN1_1[i] = QString::number(ZSDataValue[i+80]*1.0, 'f', 2);
            //            }
        }
        
        if (ZSDataValue[88]==0 || ZSDataValue[88]==1 || ZSDataValue[88]==2 || ZSDataValue[88]==3)//LIN1.2 OK或NG
        {
            if(ZSDataValue[88] == 0)
            {
                Allresults[2] = "未检测";
                LIN1NAD[1] =       QString::number(0);
                LIN1ControlID[1] = QString::number(0);
                LIN1StateID[1] =   QString::number(0);
            }
            if(ZSDataValue[88] == 1)
            {
                Allresults[2] = "OK";
                LIN1NAD[1] =       QString("%1").arg(ZSDataValue[89], 0, 16);
                LIN1ControlID[1] = QString("%1").arg(ZSDataValue[90], 0, 16);
                LIN1StateID[1] =   QString("%1").arg(ZSDataValue[91], 0, 16);
            }
            else if(ZSDataValue[88] == 2)
            {
                Allresults[2] = "检测中";
                LIN1NAD[1] =       QString("%1").arg(ZSDataValue[89], 0, 16);
                LIN1ControlID[1] = QString("%1").arg(ZSDataValue[90], 0, 16);
                LIN1StateID[1] =   QString("%1").arg(ZSDataValue[91], 0, 16);
            }
            else if(ZSDataValue[88] == 3)
            {
                Allresults[2] = "NG";
                LIN1NAD[1] =       QString("%1").arg(ZSDataValue[89], 0, 16);
                LIN1ControlID[1] = QString("%1").arg(ZSDataValue[90], 0, 16);
                LIN1StateID[1] =   QString("%1").arg(ZSDataValue[91], 0, 16);
            }
            //            for(int i = 0;i<sqldataLIN1_2.count();i++)
            //            {
            //                sqldataLIN1_2[i] = QString::number(ZSDataValue[i+92]*1.0, 'f', 2);
            //            }
        }
        
        if (ZSDataValue[100]==0 || ZSDataValue[100]==1 || ZSDataValue[100]==2 || ZSDataValue[100]==3)//LIN1.3 OK或NG
        {
            
            if(ZSDataValue[100] == 0)
            {
                Allresults[3] = "未检测";
                LIN1NAD[2] =       QString::number(0);
                LIN1ControlID[2] = QString::number(0);
                LIN1StateID[2] =   QString::number(0);
            }
            else if(ZSDataValue[100] == 1)
            {
                Allresults[3] = "OK";
                LIN1NAD[2] =       QString("%1").arg(ZSDataValue[101], 0, 16);
                LIN1ControlID[2] = QString("%1").arg(ZSDataValue[102], 0, 16);
                LIN1StateID[2] =   QString("%1").arg(ZSDataValue[103], 0, 16);
            }
            else if(ZSDataValue[100] == 2)
            {
                Allresults[3] = "检测中";
                LIN1NAD[2] =       QString("%1").arg(ZSDataValue[101], 0, 16);
                LIN1ControlID[2] = QString("%1").arg(ZSDataValue[102], 0, 16);
                LIN1StateID[2] =   QString("%1").arg(ZSDataValue[103], 0, 16);
            }
            else if(ZSDataValue[100] == 3)
            {
                Allresults[3] = "NG";
                LIN1NAD[2] =       QString("%1").arg(ZSDataValue[101], 0, 16);
                LIN1ControlID[2] = QString("%1").arg(ZSDataValue[102], 0, 16);
                LIN1StateID[2] =   QString("%1").arg(ZSDataValue[103], 0, 16);
            }
            //            for(int i = 0;i<sqldataLIN1_3.count();i++)
            //            {
            //                sqldataLIN1_3[i] = QString::number(ZSDataValue[i+104]*1.0, 'f', 2);
            //            }
        }
        
        if(ZSDataValue[112]==0 || ZSDataValue[112]==1 || ZSDataValue[112]==2 || ZSDataValue[112]==3)//LIN1.4 OK或NG
        {
            if(ZSDataValue[112] == 0)
            {
                Allresults[4] = "未检测";
                LIN1NAD[3] =       QString::number(0);
                LIN1ControlID[3] = QString::number(0);
                LIN1StateID[3] =   QString::number(0);
            }
            else if(ZSDataValue[112] == 1)
            {
                Allresults[4] = "OK";
                LIN1NAD[3] =       QString("%1").arg(ZSDataValue[113], 0, 16);
                LIN1ControlID[3] = QString("%1").arg(ZSDataValue[114], 0, 16);
                LIN1StateID[3] =   QString("%1").arg(ZSDataValue[115], 0, 16);
            }
            else if(ZSDataValue[112] == 2)
            {
                Allresults[4] = "检测中";
                LIN1NAD[3] =       QString("%1").arg(ZSDataValue[113], 0, 16);
                LIN1ControlID[3] = QString("%1").arg(ZSDataValue[114], 0, 16);
                LIN1StateID[3] =   QString("%1").arg(ZSDataValue[115], 0, 16);
            }
            else if(ZSDataValue[112] == 3)
            {
                Allresults[4] = "NG";
                LIN1NAD[3] =       QString("%1").arg(ZSDataValue[113], 0, 16);
                LIN1ControlID[3] = QString("%1").arg(ZSDataValue[114], 0, 16);
                LIN1StateID[3] =   QString("%1").arg(ZSDataValue[115], 0, 16);
            }
            //            for(int i = 0;i<sqldataLIN1_4.count();i++)
            //            {
            //                sqldataLIN1_4[i] = QString::number(ZSDataValue[i+116]*1.0, 'f', 2);
            //            }
        }
        
        if (ZSDataValue[124]==0 || ZSDataValue[124]==1 || ZSDataValue[124]==2 || ZSDataValue[124]==3)//LIN1.5 OK或NG
        {
            if(ZSDataValue[124] == 0)
            {
                Allresults[5] = "未检测";
                LIN1NAD[4] =       QString::number(0);
                LIN1ControlID[4] = QString::number(0);
                LIN1StateID[4] =   QString::number(0);
            }
            else if(ZSDataValue[124] == 1)
            {
                Allresults[5] = "OK";
                LIN1NAD[4] =       QString("%1").arg(ZSDataValue[125], 0, 16);
                LIN1ControlID[4] = QString("%1").arg(ZSDataValue[126], 0, 16);
                LIN1StateID[4] =   QString("%1").arg(ZSDataValue[127], 0, 16);
            }
            else if(ZSDataValue[124] == 2)
            {
                Allresults[5] = "检测中";
                LIN1NAD[4] =       QString("%1").arg(ZSDataValue[125], 0, 16);
                LIN1ControlID[4] = QString("%1").arg(ZSDataValue[126], 0, 16);
                LIN1StateID[4] =   QString("%1").arg(ZSDataValue[127], 0, 16);
            }
            else if(ZSDataValue[124] == 3)
            {
                Allresults[5] = "NG";
                LIN1NAD[4] =       QString("%1").arg(ZSDataValue[125], 0, 16);
                LIN1ControlID[4] = QString("%1").arg(ZSDataValue[126], 0, 16);
                LIN1StateID[4] =   QString("%1").arg(ZSDataValue[127], 0, 16);
            }
            //            for(int i = 0;i<sqldataLIN1_5.count();i++)
            //            {
            //                sqldataLIN1_5[i] = QString::number(ZSDataValue[i+128]*1.0, 'f', 2);
            //            }
        }
        
        if (ZSDataValue[136]==0 || ZSDataValue[136]==1 || ZSDataValue[136]==2 || ZSDataValue[136]==3)//LIN1.6 OK或NG
        {
            if(ZSDataValue[136] == 0)
            {
                Allresults[6] = "未检测";
                LIN1NAD[5] =      QString::number(0);
                LIN1ControlID[5] =QString::number(0);
                LIN1StateID[5] =  QString::number(0);
            }
            if(ZSDataValue[136] == 1)
            {
                Allresults[6] = "OK";
                LIN1NAD[5] =       QString("%1").arg(ZSDataValue[137], 0, 16);
                LIN1ControlID[5] = QString("%1").arg(ZSDataValue[138], 0, 16);
                LIN1StateID[5] =   QString("%1").arg(ZSDataValue[139], 0, 16);
            }
            else if(ZSDataValue[136] == 2)
            {
                Allresults[6] = "检测中";
                LIN1NAD[5] =       QString("%1").arg(ZSDataValue[137], 0, 16);
                LIN1ControlID[5] = QString("%1").arg(ZSDataValue[138], 0, 16);
                LIN1StateID[5] =   QString("%1").arg(ZSDataValue[139], 0, 16);
            }
            else if(ZSDataValue[136] == 3)
            {
                Allresults[6] = "NG";
                LIN1NAD[5] =       QString("%1").arg(ZSDataValue[137], 0, 16);
                LIN1ControlID[5] = QString("%1").arg(ZSDataValue[138], 0, 16);
                LIN1StateID[5] =   QString("%1").arg(ZSDataValue[139], 0, 16);
            }
            //            for(int i = 0;i<sqldataLIN1_6.count();i++)
            //            {
            //                sqldataLIN1_6[i] = QString::number(ZSDataValue[i+140]*1.0, 'f', 2);
            //            }
        }
        
        if (ZSDataValue[148]==0 || ZSDataValue[148]==1 || ZSDataValue[148]==2 || ZSDataValue[148]==3)//LIN1.7 OK或NG
        {
            if(ZSDataValue[148] == 0)
            {
                Allresults[7] = "未检测";
                LIN1NAD[6] =      QString::number(0);
                LIN1ControlID[6] =QString::number(0);
                LIN1StateID[6] =  QString::number(0);
            }
            if(ZSDataValue[148] == 1)
            {
                Allresults[7] = "OK";
                LIN1NAD[6] =      QString("%1").arg(ZSDataValue[149], 0, 16);
                LIN1ControlID[6] =QString("%1").arg(ZSDataValue[150], 0, 16);
                LIN1StateID[6] =  QString("%1").arg(ZSDataValue[151], 0, 16);
            }
            else if(ZSDataValue[148] == 2)
            {
                Allresults[7] = "检测中";
                LIN1NAD[6] =      QString("%1").arg(ZSDataValue[149], 0, 16);
                LIN1ControlID[6] =QString("%1").arg(ZSDataValue[150], 0, 16);
                LIN1StateID[6] =  QString("%1").arg(ZSDataValue[151], 0, 16);
            }
            else if(ZSDataValue[148] == 3)
            {
                Allresults[7] = "NG";
                LIN1NAD[6] =      QString("%1").arg(ZSDataValue[149], 0, 16);
                LIN1ControlID[6] =QString("%1").arg(ZSDataValue[150], 0, 16);
                LIN1StateID[6] =  QString("%1").arg(ZSDataValue[151], 0, 16);
            }
            //            for(int i = 0;i<sqldataLIN1_7.count();i++)
            //            {
            //                sqldataLIN1_7[i] = QString::number(ZSDataValue[i+152]*1.0, 'f', 2);
            //            }
        }
        
        if (ZSDataValue[160] == 0 || ZSDataValue[160]==1 || ZSDataValue[160]==2 || ZSDataValue[160]==3)//LIN1.8 OK或NG
        {
            if(ZSDataValue[160] == 0)
            {
                Allresults[8] = "未检测";
                LIN1NAD[7] =      QString::number(0);
                LIN1ControlID[7] =QString::number(0);
                LIN1StateID[7] =  QString::number(0);
            }
            if(ZSDataValue[160] == 1)
            {
                Allresults[8] = "OK";
                LIN1NAD[7] =      QString("%1").arg(ZSDataValue[161], 0, 16);
                LIN1ControlID[7] =QString("%1").arg(ZSDataValue[162], 0, 16);
                LIN1StateID[7] =  QString("%1").arg(ZSDataValue[163], 0, 16);
            }
            else if(ZSDataValue[160] == 2)
            {
                Allresults[8] = "检测中";
                LIN1NAD[7] =      QString("%1").arg(ZSDataValue[161], 0, 16);
                LIN1ControlID[7] =QString("%1").arg(ZSDataValue[162], 0, 16);
                LIN1StateID[7] =  QString("%1").arg(ZSDataValue[163], 0, 16);
            }
            else if(ZSDataValue[160] == 3)
            {
                Allresults[8] = "NG";
                LIN1NAD[7] =      QString("%1").arg(ZSDataValue[161], 0, 16);
                LIN1ControlID[7] =QString("%1").arg(ZSDataValue[162], 0, 16);
                LIN1StateID[7] =  QString("%1").arg(ZSDataValue[163], 0, 16);
            }
            //            for(int i = 0;i<sqldataLIN1_8.count();i++)
            //            {
            //                sqldataLIN1_8[i] = QString::number(ZSDataValue[i+164]*1.0, 'f', 2);
            //            }
        }
        
        if (ZSDataValue[172]==0 || ZSDataValue[172]==1 || ZSDataValue[172]==2 || ZSDataValue[172]==3)//LIN1.9 OK或NG
        {
            if(ZSDataValue[172]==0)
            {
                Allresults[9] = "未检测";
                LIN1NAD[8] =      QString::number(0);
                LIN1ControlID[8] =QString::number(0);
                LIN1StateID[8] =  QString::number(0);
            }
            else if(ZSDataValue[172] == 1)
            {
                Allresults[9] = "OK";
                LIN1NAD[8] =      QString("%1").arg(ZSDataValue[173], 0, 16);
                LIN1ControlID[8] =QString("%1").arg(ZSDataValue[174], 0, 16);
                LIN1StateID[8] =  QString("%1").arg(ZSDataValue[175], 0, 16);
            }
            else if(ZSDataValue[172] == 2)
            {
                Allresults[9] = "检测中";
                LIN1NAD[8] =      QString("%1").arg(ZSDataValue[173], 0, 16);
                LIN1ControlID[8] =QString("%1").arg(ZSDataValue[174], 0, 16);
                LIN1StateID[8] =  QString("%1").arg(ZSDataValue[175], 0, 16);
            }
            else if(ZSDataValue[172] == 3)
            {
                Allresults[9] = "NG";
                LIN1NAD[8] =      QString("%1").arg(ZSDataValue[173], 0, 16);
                LIN1ControlID[8] =QString("%1").arg(ZSDataValue[174], 0, 16);
                LIN1StateID[8] =  QString("%1").arg(ZSDataValue[175], 0, 16);
            }
            //            for(int i = 0;i<sqldataLIN1_9.count();i++)
            //            {
            //                sqldataLIN1_9[i] = QString::number(ZSDataValue[i+176]*1.0, 'f', 2);
            //            }
        }
        
        if (ZSDataValue[184]==0 || ZSDataValue[184]==1 || ZSDataValue[184]==2 || ZSDataValue[184]==3)//LIN1.10 OK或NG
        {
            if(ZSDataValue[184] == 0)
            {
                Allresults[10] = "未检测";
                LIN1NAD[9] =      QString::number(0);
                LIN1ControlID[9] =QString::number(0);
                LIN1StateID[9] =  QString::number(0);
            }
            else if(ZSDataValue[184] == 1)
            {
                Allresults[10] = "OK";
                LIN1NAD[9] =     QString("%1").arg(ZSDataValue[185], 0, 16);
                LIN1ControlID[9] =QString("%1").arg(ZSDataValue[186], 0, 16);
                LIN1StateID[9] =  QString("%1").arg(ZSDataValue[187], 0, 16);
            }
            else if(ZSDataValue[184] == 2)
            {
                Allresults[10] = "检测中";
                LIN1NAD[9] =     QString("%1").arg(ZSDataValue[185], 0, 16);
                LIN1ControlID[9] =QString("%1").arg(ZSDataValue[186], 0, 16);
                LIN1StateID[9] =  QString("%1").arg(ZSDataValue[187], 0, 16);
            }
            else if(ZSDataValue[184] == 3)
            {
                Allresults[10] = "NG";
                LIN1NAD[9] =     QString("%1").arg(ZSDataValue[185], 0, 16);
                LIN1ControlID[9] =QString("%1").arg(ZSDataValue[186], 0, 16);
                LIN1StateID[9] =  QString("%1").arg(ZSDataValue[187], 0, 16);
            }
            //            for(int i = 0;i<sqldataLIN1_10.count();i++)
            //            {
            //                sqldataLIN1_10[i] = QString::number(ZSDataValue[i+188]*1.0, 'f', 2);
            //            }
        }

        //--------------------------------------M1电机--------------------------------------
        if(ZSDataValue[399]== 0)//M1电机
        {
            Allresults[16] = "未检测";
            //            sqldataPTdata[0] = ui->Auto_Motor_M1_Name->text();
            sqldataPTdata[1] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[2] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[399]== 1 || ZSDataValue[399]== 2 || ZSDataValue[399]== 3)
        {
            if(ZSDataValue[399]== 1)
            {
                Allresults[16] = "OK";
            }
            else if(ZSDataValue[399]== 2)
            {
                Allresults[16] = "检测中";
            }
            else if(ZSDataValue[399]== 3)
            {
                Allresults[16] = "NG";
            }
            //            sqldataPTdata[0] = ui->Auto_Motor_M1_Name->text();
            sqldataPTdata[1] = QString::number(ZSDataValue[401]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[402]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[403]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[404]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[405]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[406]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[407]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[408]/100.0, 'f', 2);
            sqldataPTdata[2] = QString::number(ZSDataValue[409]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[410]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[411]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[412]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[413]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[414]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[415]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[416]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[417]== 0)//M2电机
        {
            Allresults[17] = "未检测";
            //            sqldataPTdata[3] = ui->Auto_Motor_M2_Name->text();
            sqldataPTdata[4] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[5] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[417]== 1 || ZSDataValue[417]== 2 || ZSDataValue[417]== 3)
        {
            if(ZSDataValue[417]== 1)
            {
                Allresults[17] = "OK";
            }
            else if(ZSDataValue[417]== 2)
            {
                Allresults[17] = "检测中";
            }
            else if(ZSDataValue[417]== 3)
            {
                Allresults[17] = "NG";
            }
            //            sqldataPTdata[3] = ui->Auto_Motor_M2_Name->text();
            sqldataPTdata[4] = QString::number(ZSDataValue[419]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[420]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[421]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[422]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[423]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[424]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[425]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[426]/100.0, 'f', 2);
            sqldataPTdata[5] = QString::number(ZSDataValue[427]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[428]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[429]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[430]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[431]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[432]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[433]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[434]/1000.0, 'f', 3);
            
            
        }
        
        if(ZSDataValue[435]== 0)//M3电机
        {
            Allresults[18] = "未检测";
            //            sqldataPTdata[6] = ui->Auto_Motor_M3_Name->text();
            sqldataPTdata[7] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[8] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[435]== 1 || ZSDataValue[435]== 2 || ZSDataValue[435]== 3)
        {
            if(ZSDataValue[435]== 1)
            {
                Allresults[18] = "OK";
            }
            else if(ZSDataValue[435]== 2)
            {
                Allresults[18] = "检测中";
            }
            else if(ZSDataValue[435]== 3)
            {
                Allresults[18] = "NG";
            }
            //            sqldataPTdata[6] = ui->Auto_Motor_M3_Name->text();
            sqldataPTdata[7] = QString::number(ZSDataValue[437]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[438]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[439]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[440]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[441]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[442]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[443]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[444]/100.0, 'f', 2);
            sqldataPTdata[8] = QString::number(ZSDataValue[445]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[446]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[447]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[448]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[449]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[450]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[451]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[452]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[453]== 0)//M4电机
        {
            Allresults[19] = "未检测";
            //            sqldataPTdata[9] = ui->Auto_Motor_M4_Name->text();
            sqldataPTdata[10] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[11] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
        }
        else if (ZSDataValue[453]== 1 || ZSDataValue[453]== 2 || ZSDataValue[453]== 3)
        {
            if(ZSDataValue[453]== 1)
            {
                Allresults[19] = "OK";
            }
            else if(ZSDataValue[453]== 2)
            {
                Allresults[19] = "检测中";
            }
            else if(ZSDataValue[453]== 3)
            {
                Allresults[19] = "NG";
            }
            //            sqldataPTdata[9] = ui->Auto_Motor_M4_Name->text();
            sqldataPTdata[10] = QString::number(ZSDataValue[455]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[456]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[457]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[458]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[459]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[460]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[461]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[462]/100.0, 'f', 2);
            sqldataPTdata[11] = QString::number(ZSDataValue[463]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[464]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[465]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[466]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[467]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[468]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[469]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[470]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[471]== 0)//M5电机
        {
            Allresults[20] = "未检测";
            //            sqldataPTdata[12] = ui->Auto_Motor_M5_Name->text();
            sqldataPTdata[13] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[14] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[471]== 1 || ZSDataValue[471]== 2 || ZSDataValue[471]== 3)
        {
            if(ZSDataValue[471]== 1)
            {
                Allresults[20] = "OK";
            }
            else if(ZSDataValue[471]== 2)
            {
                Allresults[20] = "检测中";
            }
            else if(ZSDataValue[471]== 3)
            {
                Allresults[20] = "NG";
            }
            //            sqldataPTdata[12] = ui->Auto_Motor_M5_Name->text();
            sqldataPTdata[13] = QString::number(ZSDataValue[473]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[474]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[475]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[476]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[477]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[478]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[479]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[480]/100.0, 'f', 2);
            sqldataPTdata[14] = QString::number(ZSDataValue[481]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[482]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[483]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[484]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[485]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[486]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[487]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[488]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[489]== 0)//M6电机
        {
            Allresults[21] = "未检测";
            //            sqldataPTdata[15] = ui->Auto_Motor_M6_Name->text();
            sqldataPTdata[16] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[17] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[489]== 1 || ZSDataValue[489]== 2 || ZSDataValue[489]== 3)
        {
            if(ZSDataValue[489]== 1)
            {
                Allresults[21] = "OK";
            }
            else if(ZSDataValue[489]== 2)
            {
                Allresults[21] = "检测中";
            }
            else if(ZSDataValue[489]== 3)
            {
                Allresults[21] = "NG";
            }
            //            sqldataPTdata[15] = ui->Auto_Motor_M6_Name->text();
            sqldataPTdata[16] = QString::number(ZSDataValue[491]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[492]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[493]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[494]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[495]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[496]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[497]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[498]/100.0, 'f', 2);
            sqldataPTdata[17] = QString::number(ZSDataValue[499]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[500]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[501]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[502]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[503]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[504]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[505]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[506]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[507]== 0)//M7电机
        {
            Allresults[22] = "未检测";
            //            sqldataPTdata[18] = ui->Auto_Motor_M7_Name->text();
            sqldataPTdata[19] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[20] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[507]== 1 || ZSDataValue[507]== 2 || ZSDataValue[507]== 3)
        {
            if(ZSDataValue[507]== 1)
            {
                Allresults[22] = "OK";
            }
            else if(ZSDataValue[507]== 2)
            {
                Allresults[22] = "检测中";
            }
            else if(ZSDataValue[507]== 3)
            {
                Allresults[22] = "NG";
            }
            //            sqldataPTdata[18] = ui->Auto_Motor_M7_Name->text();
            sqldataPTdata[19] = QString::number(ZSDataValue[509]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[510]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[511]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[512]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[513]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[514]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[515]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[516]/100.0, 'f', 2);
            sqldataPTdata[20] = QString::number(ZSDataValue[517]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[518]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[519]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[520]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[521]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[522]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[523]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[524]/1000.0, 'f', 3);
        }
        
        if(ZSDataValue[525]== 0)//M8电机
        {
            Allresults[23] = "未检测";
            //            sqldataPTdata[21] = ui->Auto_Motor_M8_Name->text();
            sqldataPTdata[22] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[23] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
        }
        else if (ZSDataValue[525]== 1 || ZSDataValue[525]== 2 || ZSDataValue[525]== 3)
        {
            if(ZSDataValue[525]== 1)
            {
                Allresults[23] = "OK";
            }
            else if(ZSDataValue[525]== 2)
            {
                Allresults[23] = "检测中";
            }
            else if(ZSDataValue[525]== 3)
            {
                Allresults[23] = "NG";
            }
            //            sqldataPTdata[21] = ui->Auto_Motor_M8_Name->text();
            sqldataPTdata[22] = QString::number(ZSDataValue[527]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[528]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[529]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[530]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[532]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[532]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[533]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[534]/100.0, 'f', 2);
            sqldataPTdata[23] = QString::number(ZSDataValue[535]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[536]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[537]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[538]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[539]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[540]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[541]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[542]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[543]== 0)//M9电机
        {
            Allresults[24] = "未检测";
            //            sqldataPTdata[24] = ui->Auto_Motor_M9_Name->text();
            sqldataPTdata[25] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[26] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
        }
        else if (ZSDataValue[543]== 1 || ZSDataValue[543]== 2 || ZSDataValue[543]== 3)
        {
            if(ZSDataValue[543]== 1)
            {
                Allresults[24] = "OK";
            }
            else if(ZSDataValue[543]== 2)
            {
                Allresults[24] = "检测中";
            }
            else if(ZSDataValue[543]== 3)
            {
                Allresults[24] = "NG";
            }
            //            sqldataPTdata[24] = ui->Auto_Motor_M9_Name->text();
            sqldataPTdata[25] = QString::number(ZSDataValue[545]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[546]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[547]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[548]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[549]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[550]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[551]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[552]/100.0, 'f', 2);
            sqldataPTdata[26] = QString::number(ZSDataValue[553]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[554]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[555]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[556]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[557]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[558]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[559]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[560]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[561]== 0)//M10电机
        {
            Allresults[25] = "未检测";
            //            sqldataPTdata[27] = ui->Auto_Motor_M10_Name->text();
            sqldataPTdata[28] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[29] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[561]== 1 || ZSDataValue[561]== 2 || ZSDataValue[561]== 3)
        {
            if(ZSDataValue[561]== 1)
            {
                Allresults[25] = "OK";
            }
            else if(ZSDataValue[561]== 2)
            {
                Allresults[25] = "检测中";
            }
            else if(ZSDataValue[561]== 3)
            {
                Allresults[25] = "NG";
            }
            //            sqldataPTdata[27] = ui->Auto_Motor_M10_Name->text();
            sqldataPTdata[28] = QString::number(ZSDataValue[563]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[564]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[565]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[566]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[567]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[568]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[569]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[570]/100.0, 'f', 2);
            sqldataPTdata[29] = QString::number(ZSDataValue[571]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[572]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[573]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[574]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[575]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[576]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[577]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[578]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[579]== 0)//M11电机
        {
            Allresults[26] = "未检测";
            //            sqldataPTdata[30] = ui->Auto_Motor_M11_Name->text();
            sqldataPTdata[31] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[32] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[579]== 1 || ZSDataValue[579]== 2 || ZSDataValue[579]== 3)
        {
            if(ZSDataValue[579]== 1)
            {
                Allresults[26] = "OK";
            }
            else if(ZSDataValue[579]== 2)
            {
                Allresults[26] = "检测中";
            }
            else if(ZSDataValue[579]== 3)
            {
                Allresults[26] = "NG";
            }
            //            sqldataPTdata[30] = ui->Auto_Motor_M11_Name->text();
            sqldataPTdata[31] = QString::number(ZSDataValue[581]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[582]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[583]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[584]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[585]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[586]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[587]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[588]/100.0, 'f', 2);
            sqldataPTdata[32] = QString::number(ZSDataValue[589]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[590]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[591]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[592]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[593]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[594]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[595]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[596]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[597]== 0)//M12电机
        {
            Allresults[27] = "未检测";
            //            sqldataPTdata[33] = ui->Auto_Motor_M12_Name->text();
            sqldataPTdata[34] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[35] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[597]== 1 || ZSDataValue[597]== 2 || ZSDataValue[597]== 3)
        {
            if(ZSDataValue[597]== 1)
            {
                Allresults[27] = "OK";
            }
            else if(ZSDataValue[597]== 2)
            {
                Allresults[27] = "检测中";
            }
            else if(ZSDataValue[597]== 3)
            {
                Allresults[27] = "NG";
            }
            //            sqldataPTdata[33] = ui->Auto_Motor_M12_Name->text();
            sqldataPTdata[34] = QString::number(ZSDataValue[599]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[600]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[601]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[602]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[603]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[604]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[605]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[606]/100.0, 'f', 2);
            sqldataPTdata[35] = QString::number(ZSDataValue[607]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[608]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[609]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[610]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[611]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[612]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[613]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[614]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[615]== 0)//M13电机
        {
            Allresults[28] = "未检测";
            //            sqldataPTdata[36] = ui->Auto_Motor_M13_Name->text();
            sqldataPTdata[37] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[38] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
        }
        else if (ZSDataValue[615]== 1 || ZSDataValue[615]== 2 || ZSDataValue[615]== 3)
        {
            if(ZSDataValue[615]== 1)
            {
                Allresults[28] = "OK";
            }
            else if(ZSDataValue[615]== 2)
            {
                Allresults[28] = "检测中";
            }
            else if(ZSDataValue[615]== 3)
            {
                Allresults[28] = "NG";
            }
            //            sqldataPTdata[36] = ui->Auto_Motor_M13_Name->text();
            sqldataPTdata[37] = QString::number(ZSDataValue[617]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[618]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[619]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[620]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[621]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[622]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[623]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[624]/100.0, 'f', 2);
            sqldataPTdata[38] = QString::number(ZSDataValue[625]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[626]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[627]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[628]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[629]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[630]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[631]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[632]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[633]== 0)//M14电机
        {
            Allresults[29] = "未检测";
            //            sqldataPTdata[39] = ui->Auto_Motor_M14_Name->text();
            sqldataPTdata[40] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[41] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[633]== 1 || ZSDataValue[633]== 2 || ZSDataValue[633]== 3)
        {
            if(ZSDataValue[633]== 1)
            {
                Allresults[29] = "OK";
            }
            else if(ZSDataValue[633]== 2)
            {
                Allresults[29] = "检测中";
            }
            else if(ZSDataValue[633]== 3)
            {
                Allresults[29] = "NG";
            }
            //            sqldataPTdata[39] = ui->Auto_Motor_M14_Name->text();
            sqldataPTdata[40] = QString::number(ZSDataValue[635]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[636]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[637]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[638]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[639]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[640]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[641]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[642]/100.0, 'f', 2);
            sqldataPTdata[41] = QString::number(ZSDataValue[643]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[644]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[645]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[646]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[647]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[648]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[649]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[650]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[651]== 0)//M15电机
        {
            Allresults[30] = "未检测";
            //            sqldataPTdata[42] = ui->Auto_Motor_M15_Name->text();
            sqldataPTdata[43] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[44] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[651]== 1 || ZSDataValue[651]== 2 || ZSDataValue[651]== 3)
        {
            if(ZSDataValue[651]== 1)
            {
                Allresults[30] = "OK";
            }
            else if(ZSDataValue[651]== 2)
            {
                Allresults[30] = "检测中";
            }
            else if(ZSDataValue[651]== 3)
            {
                Allresults[30] = "NG";
            }
            //            sqldataPTdata[42] = ui->Auto_Motor_M15_Name->text();
            sqldataPTdata[43] = QString::number(ZSDataValue[653]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[654]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[655]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[656]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[657]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[658]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[659]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[660]/100.0, 'f', 2);
            sqldataPTdata[44] = QString::number(ZSDataValue[661]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[662]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[663]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[664]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[665]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[666]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[667]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[668]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[669]== 0)//M16电机
        {
            Allresults[31] = "未检测";
            //            sqldataPTdata[45] = ui->Auto_Motor_M16_Name->text();
            sqldataPTdata[46] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[47] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[669]== 1 || ZSDataValue[669]== 2 || ZSDataValue[669]== 3)
        {
            if(ZSDataValue[669]== 1)
            {
                Allresults[31] = "OK";
            }
            else if(ZSDataValue[669]== 2)
            {
                Allresults[31] = "检测中";
            }
            else if(ZSDataValue[669]== 3)
            {
                Allresults[31] = "NG";
            }
            //            sqldataPTdata[45] = ui->Auto_Motor_M16_Name->text();
            sqldataPTdata[46] = QString::number(ZSDataValue[671]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[672]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[673]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[674]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[675]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[676]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[677]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[678]/100.0, 'f', 2);
            sqldataPTdata[47] = QString::number(ZSDataValue[679]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[680]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[681]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[682]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[683]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[684]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[685]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[686]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[687]== 0)//M17电机
        {
            Allresults[32] = "未检测";
            //            sqldataPTdata[48] = ui->Auto_Motor_M17_Name->text();
            sqldataPTdata[49] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[50] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[687]== 1 || ZSDataValue[687]== 2 || ZSDataValue[687]== 3)
        {
            if(ZSDataValue[687]== 1)
            {
                Allresults[32] = "OK";
            }
            else if(ZSDataValue[687]== 2)
            {
                Allresults[32] = "检测中";
            }
            else if(ZSDataValue[687]== 3)
            {
                Allresults[32] = "NG";
            }
            //            sqldataPTdata[48] = ui->Auto_Motor_M17_Name->text();
            sqldataPTdata[49] = QString::number(ZSDataValue[689]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[690]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[691]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[692]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[693]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[694]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[695]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[696]/100.0, 'f', 2);
            sqldataPTdata[50] = QString::number(ZSDataValue[697]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[698]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[699]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[700]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[701]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[702]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[703]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[704]/1000.0, 'f', 3);
            
        }
        
        if(ZSDataValue[705]== 0)//M18电机
        {
            Allresults[33] = "未检测";
            //            sqldataPTdata[36] = INI_File().Get_Control("PD"+QString::number(ZSDataValue[5])+"/Name_M19");
            //            sqldataPTdata[51] = ui->Auto_Motor_M18_Name->text();
            sqldataPTdata[52] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            sqldataPTdata[53] = QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0)+"、"+QString::number(0);
            
        }
        else if (ZSDataValue[705]== 1 || ZSDataValue[705]== 2 || ZSDataValue[705]== 3)
        {
            if(ZSDataValue[705]== 1)
            {
                Allresults[33] = "OK";
            }
            else if(ZSDataValue[705]== 2)
            {
                Allresults[33] = "检测中";
            }
            else if(ZSDataValue[705]== 3)
            {
                Allresults[33] = "NG";
            }
            //            sqldataPTdata[51] = ui->Auto_Motor_M18_Name->text();
            sqldataPTdata[52] = QString::number(ZSDataValue[707]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[708]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[709]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[710]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[711]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[712]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[713]/100.0, 'f', 2)+"、"+QString::number(ZSDataValue[714]/100.0, 'f', 2);
            sqldataPTdata[53] = QString::number(ZSDataValue[715]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[716]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[717]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[718]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[719]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[720]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[721]/1000.0, 'f', 3)+"、"+QString::number(ZSDataValue[722]/1000.0, 'f', 3);
            
        }
        //--------------------------------------温敏--------------------------------------
        
        sqldataRes[0] = QString::number(ZSDataValue[338]/10.0, 'f', 2);//室内环境温度
        
        if(ZSDataValue[339]== 0)//温敏1
        {
            Allresults[34] = "未检测";
            sqldataRes[1] = QString::number(0);
        }
        else if(ZSDataValue[339]== 1 || ZSDataValue[339]== 2 || ZSDataValue[339]== 3)
        {
            if(ZSDataValue[339]== 1)
            {
                Allresults[34] = "OK";
            }
            else if(ZSDataValue[339]== 2)
            {
                Allresults[34] = "检测中";
            }
            else if(ZSDataValue[339]== 3)
            {
                Allresults[34] = "NG";
            }
            sqldataRes[1] = QString::number(ZSDataValue[340]/10.0, 'f', 1);
        }
        
        if(ZSDataValue[341]== 0)//温敏2
        {
            Allresults[35] = "未检测";
            sqldataRes[2] = QString::number(0);
        }
        else if(ZSDataValue[341]== 1 || ZSDataValue[341]== 2 || ZSDataValue[341]== 3)
        {
            if(ZSDataValue[341]== 1)
            {
                Allresults[35] = "OK";
            }
            else if(ZSDataValue[341]== 2)
            {
                Allresults[35] = "检测中";
            }
            else if(ZSDataValue[341]== 3)
            {
                Allresults[35] = "NG";
            }
            sqldataRes[2] = QString::number(ZSDataValue[342]/10.0, 'f', 1);
        }
        
        if(ZSDataValue[343]== 0)//温敏3
        {
            Allresults[36] = "未检测";
            sqldataRes[3] = QString::number(0);
        }
        else if(ZSDataValue[343]== 1 || ZSDataValue[343]== 2 || ZSDataValue[343]== 3)
        {
            if(ZSDataValue[343]== 1)
            {
                Allresults[36] = "OK";
            }
            else if(ZSDataValue[343]== 2)
            {
                Allresults[36] = "检测中";
            }
            else if(ZSDataValue[343]== 3)
            {
                Allresults[36] = "NG";
            }
            sqldataRes[3] = QString::number(ZSDataValue[344]/10.0, 'f', 1);
        }
        
        if(ZSDataValue[345]== 0)//温敏4
        {
            Allresults[37] = "未检测";
            sqldataRes[4] = QString::number(0);
        }
        else if(ZSDataValue[345]== 1 || ZSDataValue[345]== 2 || ZSDataValue[345]== 3)
        {
            if(ZSDataValue[345]== 1)
            {
                Allresults[37] = "OK";
            }
            else if(ZSDataValue[345]== 2)
            {
                Allresults[37] = "检测中";
            }
            else if(ZSDataValue[345]== 3)
            {
                Allresults[37] = "NG";
            }
            sqldataRes[4] = QString::number(ZSDataValue[346]/10.0, 'f', 1);
        }
        
        if(ZSDataValue[347]== 0)//温敏5
        {
            Allresults[38] = "未检测";
            sqldataRes[5] = QString::number(0);
        }
        else if(ZSDataValue[347]== 1 || ZSDataValue[347]== 2 || ZSDataValue[347]== 3)
        {
            if(ZSDataValue[347]== 1)
            {
                Allresults[38] = "OK";
            }
            else if(ZSDataValue[347]== 2)
            {
                Allresults[38] = "检测中";
            }
            else if(ZSDataValue[347]== 3)
            {
                Allresults[38] = "NG";
            }
            sqldataRes[5] = QString::number(ZSDataValue[348]/10.0, 'f', 1);
        }
        
        if(ZSDataValue[349]== 0)//温敏6
        {
            Allresults[39] = "未检测";
            sqldataRes[6] = QString::number(0);
        }
        else if(ZSDataValue[349]== 1 || ZSDataValue[349]== 2 || ZSDataValue[349]== 3)
        {
            if(ZSDataValue[349]== 1)
            {
                Allresults[39] = "OK";
            }
            else if(ZSDataValue[349]== 2)
            {
                Allresults[39] = "检测中";
            }
            else if(ZSDataValue[349]== 3)
            {
                Allresults[39] = "NG";
            }
            sqldataRes[6] = QString::number(ZSDataValue[350]/10.0, 'f', 1);
        }
        
        if(ZSDataValue[351]== 0)//温敏7
        {
            Allresults[40] = "未检测";
            sqldataRes[7] = QString::number(0);
        }
        else if(ZSDataValue[351]== 1 || ZSDataValue[351]== 2 || ZSDataValue[351]== 3)
        {
            if(ZSDataValue[351]== 1)
            {
                Allresults[40] = "OK";
            }
            else if(ZSDataValue[351]== 2)
            {
                Allresults[40] = "检测中";
            }
            else if(ZSDataValue[351]== 3)
            {
                Allresults[40] = "NG";
            }
            sqldataRes[7] = QString::number(ZSDataValue[352]/10.0, 'f', 1);
        }
        
        if(ZSDataValue[353]== 0)//温敏8
        {
            Allresults[41] = "未检测";
            sqldataRes[8] = QString::number(0);
        }
        else if(ZSDataValue[353]== 1 || ZSDataValue[353]== 2 || ZSDataValue[353]== 3)
        {
            if(ZSDataValue[353]== 1)
            {
                Allresults[41] = "OK";
            }
            else if(ZSDataValue[353]== 2)
            {
                Allresults[41] = "检测中";
            }
            else if(ZSDataValue[353]== 3)
            {
                Allresults[41] = "NG";
            }
            sqldataRes[8] = QString::number(ZSDataValue[354]/10.0, 'f', 1);
        }
        
        if(ZSDataValue[355]== 0)//温敏9
        {
            Allresults[42] = "未检测";
            sqldataRes[9] = QString::number(0);
        }
        else if(ZSDataValue[355]== 1 || ZSDataValue[355]== 2 || ZSDataValue[355]== 3)
        {
            if(ZSDataValue[355]== 1)
            {
                Allresults[42] = "OK";
            }
            else if(ZSDataValue[355]== 2)
            {
                Allresults[42] = "检测中";
            }
            else if(ZSDataValue[355]== 3)
            {
                Allresults[42] = "NG";
            }
            sqldataRes[9] = QString::number(ZSDataValue[356]/10.0, 'f', 1);
        }
        
        if(ZSDataValue[357]== 0)//温敏10
        {
            Allresults[43] = "未检测";
            sqldataRes[10] = QString::number(0);
        }
        else if(ZSDataValue[357]== 1 || ZSDataValue[357]== 2 || ZSDataValue[357]== 3)
        {

            if(ZSDataValue[357]== 1)
            {
                Allresults[43] = "OK";
            }
            else if(ZSDataValue[357]== 2)
            {
                Allresults[43] = "检测中";
            }
            else if(ZSDataValue[357]== 3)
            {
                Allresults[43] = "NG";
            }
            sqldataRes[10] = QString::number(ZSDataValue[358]/10.0, 'f', 1);
        }
        //        -------------------------------------- PM2.5 负离子 AQS 噪音--------------------------------------
        if(ZSDataValue[359] == 0)//PM2.5
        {
            Allresults[44] = "未检测";
            sqldataRes[11] = QString::number(0);
            sqldataRes[12] = QString::number(0);
        }
        else if(ZSDataValue[359] == 1 || ZSDataValue[359] == 2 || ZSDataValue[359] == 3)
        {
            if(ZSDataValue[359]== 1)
            {
                Allresults[44] = "OK";
            }
            else if(ZSDataValue[359]== 2)
            {
                Allresults[44] = "检测中";
            }
            else if(ZSDataValue[359]== 3)
            {
                Allresults[44] = "NG";
            }
            sqldataRes[11] = QString::number(ZSDataValue[360]);
            sqldataRes[12] = QString::number(ZSDataValue[361]);
        }
        //        室内环境温度","温敏1检测值","温敏2检测值","温敏3检测值","温敏4检测值","温敏5检测值",
        //            "温敏6检测值","温敏7检测值","温敏8检测值","温敏9检测值","温敏10检测值",
        //            "车内PM2.5检测浓度","车外PM2.5检测浓度","空气质量状态","电子膨胀阀ID","电子膨胀阀当前位置",
        //            "PTC—ID","软件版本号","硬件版本号","负离子检测电压","噪音检测值"
        if(ZSDataValue[362] == 0)//AQS
        {
            Allresults[45] = "未检测";
            sqldataRes[13] = QString("%1").arg(ZSDataValue[363], 0, 16);
        }
        else if(ZSDataValue[362] == 1 || ZSDataValue[362] == 2 || ZSDataValue[362] == 3)
        {
            if(ZSDataValue[362]== 1)
            {
                Allresults[45] = "OK";
            }
            else if(ZSDataValue[362]== 2)
            {
                Allresults[45] = "检测中";
            }
            else if(ZSDataValue[362]== 3)
            {
                Allresults[45] = "NG";
            }
            sqldataRes[13] = QString("%1").arg(ZSDataValue[363], 0, 16);
        }
        
        if(ZSDataValue[364] == 0)//电子膨胀阀
        {
            Allresults[46] = "未检测";
            sqldataRes[14] = QString::number(0);
            sqldataRes[15] = QString::number(0);
        }
        else if(ZSDataValue[364] == 1 || ZSDataValue[364] == 2 || ZSDataValue[364] == 3)
        {
            if(ZSDataValue[364]== 1)
            {
                Allresults[46] = "OK";
            }
            else if(ZSDataValue[364]== 2)
            {
                Allresults[46] = "检测中";
            }
            else if(ZSDataValue[364]== 3)
            {
                Allresults[46] = "NG";
            }
            sqldataRes[14] = QString("%1").arg(ZSDataValue[365], 0, 16);
            sqldataRes[15] = QString::number(ZSDataValue[366], 'f', 2);
        }
        if(ZSDataValue[367] == 0)//PTC
        {
            Allresults[47] = "未检测";
            sqldataRes[16] = QString::number(0);
            sqldataRes[17] = QString::number(0);
            sqldataRes[18] = QString::number(0);
        }
        else if(ZSDataValue[367] == 1 || ZSDataValue[367] == 2 || ZSDataValue[367] == 3)
        {
            if(ZSDataValue[367]== 1)
            {
                Allresults[47] = "OK";
            }
            else if(ZSDataValue[364]== 2)
            {
                Allresults[47] = "检测中";
            }
            else if(ZSDataValue[364]== 3)
            {
                Allresults[47] = "NG";
            }
            sqldataRes[16] = QString("%1").arg(ZSDataValue[368], 0, 16);
            sqldataRes[17] = QString::number(ZSDataValue[369], 'f', 2);
            sqldataRes[18] = QString::number(ZSDataValue[370], 'f', 2);
        }
        if(ZSDataValue[371] == 0)//负离子
        {
            Allresults[48] = "未检测";
            sqldataRes[19] = QString::number(0);
        }
        else if(ZSDataValue[371] == 1 || ZSDataValue[371]== 2 || ZSDataValue[371]== 3)
        {
            if(ZSDataValue[371]== 1)
            {
                Allresults[48] = "OK";
            }
            else if(ZSDataValue[371]== 2)
            {
                Allresults[48] = "检测中";
            }
            else if(ZSDataValue[371]== 3)
            {
                Allresults[48] = "NG";
            }
            sqldataRes[19] = QString::number(ZSDataValue[372]/100.0, 'f', 2);//电压
        }
        if(ZSDataValue[870] == 0)//噪音
        {
            Allresults[49] = "未检测";
            for (int i =0;i<9;i++ )
            {
                sqldataVibration[i+36] = QString::number(0);
            }
        }
        else if(ZSDataValue[870] == 1 || ZSDataValue[870] == 2 || ZSDataValue[870] == 3)
        {
            if(ZSDataValue[870]== 1)
            {
                Allresults[49] = "OK";
            }
            else if(ZSDataValue[870]== 2)
            {
                Allresults[49] = "检测中";
            }
            else if(ZSDataValue[870]== 3)
            {
                Allresults[49] = "NG";
            }
            for (int i =0;i<9;i++ )
            {
                sqldataVibration[i+36] = QString::number(ZSDataValue[871+i]/10.0, 'f', 1);
            }
        }
        //----------------------------------振动-----------------------------------
        if(ZSDataValue[822] == 0)//X轴振动
        {
            Allresults[50] = "未检测";
            for (int i =0;i<9;i++ )
            {
                sqldataVibration[i] = QString::number(0);
            }
        }
        else if(ZSDataValue[822] == 1 || ZSDataValue[822] == 2 || ZSDataValue[822] == 3)
        {
            if(ZSDataValue[822]== 1)
            {
                Allresults[50] = "OK";
            }
            else if(ZSDataValue[822]== 2)
            {
                Allresults[50] = "检测中";
            }
            else if(ZSDataValue[822]== 3)
            {
                Allresults[50] = "NG";
            }
            for (int i =0;i<9;i++ )
            {
                sqldataVibration[i] = QString::number(ZSDataValue[826+i]/100.0, 'f', 2);
            }
        }
        if(ZSDataValue[823] == 0)//Y轴振动
        {
            Allresults[51] = "未检测";
            for (int i =0;i<9;i++ )
            {
                sqldataVibration[i+9] = QString::number(0);
            }
        }
        else if(ZSDataValue[823] == 1 || ZSDataValue[823] == 2 || ZSDataValue[823] == 3)
        {
            if(ZSDataValue[823]== 1)
            {
                Allresults[51] = "OK";
            }
            else if(ZSDataValue[823]== 2)
            {
                Allresults[51] = "检测中";
            }
            else if(ZSDataValue[823]== 3)
            {
                Allresults[51] = "NG";
            }
            for (int i =0;i<9;i++ )
            {
                sqldataVibration[i+9] = QString::number(ZSDataValue[835+i]/100.0, 'f', 2);
            }
        }
        if(ZSDataValue[824] == 0)//Z轴振动
        {
            Allresults[52] = "未检测";
            for (int i =0;i<9;i++ )
            {
                sqldataVibration[i+18] = QString::number(0);
            }
        }
        else if(ZSDataValue[824] == 1 || ZSDataValue[824] == 2|| ZSDataValue[824] == 3)
        {
            if(ZSDataValue[824]== 1)
            {
                Allresults[52] = "OK";
            }
            else if(ZSDataValue[824]== 2)
            {
                Allresults[52] = "检测中";
            }
            else if(ZSDataValue[824]== 3)
            {
                Allresults[52] = "NG";
            }
            for (int i =0;i<9;i++ )
            {
                sqldataVibration[i+18] = QString::number(ZSDataValue[844+i]/100.0, 'f', 2);
            }
        }
        if(ZSDataValue[825] == 0)//单轴振动
        {
            Allresults[53] = "未检测";
            for (int i =0;i<9;i++ )
            {
                sqldataVibration[i+27] = QString::number(0);
            }
        }
        else if(ZSDataValue[825] == 1 || ZSDataValue[825] == 2|| ZSDataValue[825] == 3)
        {
            if(ZSDataValue[825]== 1)
            {
                Allresults[53] = "OK";
            }
            else if(ZSDataValue[825]== 2)
            {
                Allresults[53] = "检测中";
            }
            else if(ZSDataValue[825]== 3)
            {
                Allresults[53] = "NG";
            }
            for (int i =0;i<9;i++ )
            {
                sqldataVibration[i+27] = QString::number(ZSDataValue[853+i]/100.0, 'f', 2);
            }
        }

        if(!sqldata[10].isEmpty()&&INplace_flag&&!liushuihao.isEmpty()&&sqldata[10]!=0)
        {
            Save_Excel();
            Save_MySql();
            Update_Number();
        }
        else
        {

            if(sqldata[10].isEmpty())
            {
                qDebug()<< "检测时间为空，无法存储。";
            }
            if(!INplace_flag)
            {
                qDebug()<< "无到位信号";
            }
            if(liushuihao.isEmpty())
            {
                qDebug()<< "空流水号";
            }
            if(sqldata[10]==0)
            {
                qDebug()<< "检测时间为0";
            }
        }

    }
}


QString MainWindow::setled_Vibration(int result)
{
    QString result_color = "";
    if(result == 0)
    {
        result_color = "";
    }
    else if(result == 1)
    {

        result_color = "background-color:  rgb(250, 250, 0);";
    }
    else if(result == 2)
    {
        result_color = "background-color:  rgb(0, 150, 0);";
    }
    else if(result == 3)
    {
        result_color = "background-color:  rgb(255, 40, 0);";
    }
    return result_color;
}

QString MainWindow::Button_background_color(int result)
{
    QString result_color = "";
    if(result == 0)
    {
        result_color = "";
    }
    else if(result == 1)
    {
        result_color = "background-color:  rgb(0, 150, 0);";

    }
    else if(result == 2)
    {

        result_color = "background-color:  rgb(250, 250, 0);";
    }
    else if(result == 3)
    {
        result_color = "background-color:  rgb(255, 40, 0);";
    }
    return result_color;
}

QString MainWindow::Button_blower_background_color(int result)
{
    QString result_color = "";
    if(result == 0)
    {
        result_color = "";
    }
    else if(result == 1)
    {

        result_color = "background-color:  rgb(250, 250, 0);";
    }
    else if(result == 2)
    {
        result_color = "background-color:  rgb(0, 150, 0);";
    }
    else if(result == 3)
    {
        result_color = "background-color:  rgb(255, 40, 0);";
    }
    return result_color;
}

void MainWindow::Connect_Init()
{
    
    //    emit Sign_Start_detection("M",220,1);
}
void MainWindow::UpdateTime()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->DatTime->setText(str);
}


void MainWindow::on_actionPLC_triggered()
{
    //    PLC_Connet->show();
}


void MainWindow::on_actionSetPD_triggered()
{

    Data_Set->showMaximized();
    Data_Set->ui->SetMain_ReadMode->click();//读模式
    //    PLC_Connet->testTimer->stop();
    //    PLC_Connet->ManualTimer->stop();
    //    PLC_Connet->ReadSetDataTimer->start(200);
}


void MainWindow::on_actionHandMain_triggered()
{
    
    Manualui_Main->showMaximized();
    //    PLC_Connet->testTimer->stop();
    //    PLC_Connet->ReadSetDataTimer->stop();
    //    PLC_Connet->ManualTimer->start(100);
    
}


void MainWindow::on_actionAbout_Software_triggered()
{
    Aboutware->show();
}


void MainWindow::on_actionContact_Us_triggered()
{
    showLogo->show();
}


void MainWindow::on_Auto_Blower_clicked()
{
    //    PLC_Connet->SetWriteCommand("D",100,5);
}


void MainWindow::on_pushButton_6_clicked()
{
    //    Save_Excel();/
    //    ZSDataValue[1]=1;
    //    Data_Processing();
    Pop_NG->show();
    Pop_NG->setGeometry(680,0,640,256);
}

void MainWindow::testsqlinit()
{
    for(int i = 0;i<sqldata.count();i++)
    {
        sqldata[i] = "0";
    }
    for(int i = 0;i<sqldata1Blower.count();i++)
    {
        sqldata1Blower[i] = "0";
    }

    for(int i = 0;i<LIN1NAD.count();i++)
    {
        LIN1NAD[i] = "0";
    }for(int i = 0;i<LIN1ControlID.count();i++)
    {
        LIN1ControlID[i] = "0";
    }for(int i = 0;i<LIN1StateID.count();i++)
    {
        LIN1StateID[i] = "0";
    }

    
    for(int i = 0;i<Allresults.count();i++)
    {
        Allresults[i] = "0";
    }
    for(int i = 0;i<sqldataPTdata.count();i++)
    {
        sqldataPTdata[i] = "0";
    }
    for(int i = 0;i<sqldataSpeed.count();i++)
    {
        sqldataSpeed[i] = "0";
    }
    for(int i = 0;i<sqldataRes.count();i++)
    {
        sqldataRes[i] = "0";
    }
    for(int i = 0;i<sqldataVibration.count();i++)
    {
        sqldataVibration[i] = "0";
    }

}

void MainWindow::on_actionRfid_triggered()
{
    m_RFID_Dialog->show();
}


void MainWindow::on_actionPD_Data_triggered()
{
    HVAC_Modelist->show();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    //    auto temp = QMessageBox::information(this,"提示","是否关闭软件",QMessageBox::Yes | QMessageBox::No);
    //    if(temp == QMessageBox::Yes)
    //    {
    //    PLC_Connet->m_tcpSocket->close();
    //    PLC_Connet->close();//鼓风机参数设置
    Data_Set->close();//频道配置界面
    Manualui_Main->close();//手动界面
    showLogo->close();//联系我们界面
    Aboutware->close();//关于软件界面
    Pop_OK->close();//OK界面
    Pop_NG->close();//NG界面
    Pop_Alarm->close();//OK界面
    HVAC_Modelist->close();//参数列表界面
    //        event->accept();
    //    }
    //    else
    //    {
    //        event->ignore();
    //    }
}
//-----------------------------------------屏幕按钮-----------------------------------------------------

void MainWindow::on_LIN_IDWrite_clicked()
{
    qDebug()<<"点击屏幕ID写入按钮";
}


void MainWindow::on_LIN1_IDRead_clicked()
{
    qDebug()<<"点击屏幕LIN1.XID读取按钮";
}


void MainWindow::on_LIN2_IDRead_clicked()
{
    qDebug()<<"点击屏幕LIN2.XID读取按钮";
}

void MainWindow::Start_reset_funtion()
{
    Slot_ShowUI_Step(0);
    Slot_ShowUI_Results(0);

}

void MainWindow::on_Auto_Start_clicked()//启动
{
    if(!Nthread_main->KeyBoxStop_flag){
    if(Nthread_main->read_state())
    {
        Start_reset_funtion();

        check_time_Start();
        Slot_ShowUI_Results(3);

        Nthread_main->run_start();
    }
    else
    {
        qDebug()<<"设备正在运行";
    }
    }

//    qDebug()<<"点击屏幕启动按钮";
}
void MainWindow::on_MandatoryLetgo_clicked()
{

    if(!Nthread_main->KeyBoxStop_flag){
        check_time_flag = false;
        Slot_ShowUI_Results(4);
        Nthread_main->run_stop();
    }


//    qDebug()<<"点击屏幕停止按钮";
}
void MainWindow::on_Auto_Reset_clicked()
{
    if(!Nthread_main->KeyBoxStop_flag){
        Nthread_main->run_stop();
//        setFinishResult(3);

        //复位界面显示的东西

        Nthread_linmotor->resetStatus();
        m_Blower->slot_Blower_ResetVars();
        Nthread_Thermistor->resetStatus();
        Nthread_ptmotor->ResetDisplayData();

        Start_reset_funtion();

        check_time_reset();
    //    check_time_Start();
        Slot_ShowUI_Results(0);

    //    qDebug()<<"点击屏幕复位按钮";
    }

}
void MainWindow::check_time_reset(){
    check_time_flag = false;
    check_time = 0;
    ui->Auto_CheckTime->setValue(QString::number(check_time/10.0,'f',1).toFloat());//检测时间
}

void MainWindow::Process_Initiation()
{
    if(Start_Process)
    {
        QString PD = "PD" + ui->Auto_PDbox->currentText();
        QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_Equence_Data.ini";
        QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
        INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
        QString SequenceStr = INI_File->value(PD + "/Equence").toString();

        QStringList numberList = SequenceStr.remove(" ").split(",");
        qDebug() << numberList;

        // 设备索引到名称的映射
        QMap<int, QString> deviceMap =
        {
            {12, "Lin电机"}, {13, "鼓风机"}, {14, "温敏"},
            {15, "负离子"}, {16, "AQS"}, {17, "PM2.5"}, {18, "PTC"}
        };

        // 找出最大步骤数
        int maxStep = 0;
        for (const QString& step : numberList)
        {
            bool ok;
            int stepNum = step.toInt(&ok);
            if (ok && stepNum > maxStep) {
                maxStep = stepNum;
            }
        }

        // 按步骤执行
        for (int step = 1; step <= maxStep; ++step)
        {
            qDebug() << "执行步骤" << step;

            QList<int> currentStepDevices;

            // 收集当前步骤的所有设备
            for (int i = 0; i < numberList.size(); ++i) {
                if (numberList[i].toInt() == step) {
                    currentStepDevices.append(i);
                }
            }
            // 启动当前步骤的设备
            for (int deviceIndex : currentStepDevices) {
                if (deviceIndex < 12) {
                    qDebug() << "启动PT电机" << deviceIndex;

                    // emit Start_PTMotor(deviceIndex); // 可以传递索引
                } else if (deviceMap.contains(deviceIndex)) {
                    qDebug() << "启动" << deviceMap[deviceIndex];
                    // 根据deviceIndex发射对应信号
                    switch(deviceIndex) {
                    case 12: /*emit Start_LINMotor();*/ break;
                    case 13: /*emit Start_Blower();*/ break;
                        // ... 其他设备
                    }
                }
            }

            // 等待步骤完成
            if(1)
            { // 你的完成判断条件
                qDebug() << "步骤" << step << "完成";
            }
        }
    }
}




void MainWindow::on_Auto_ManualNG_clicked()
{
    
    qDebug()<<"点击屏幕强制NG按钮";
}




void MainWindow::on_Goback_clicked()
{
    ReadChannel_flag = 0;
    emit Sign_Goback();
}

void MainWindow::onButtonPressed()
{
    pressTimer->start(); // 按下按钮时启动计时器
}

void MainWindow::onButtonReleased()
{
    pressTimer->stop(); // 松开按钮时停止计时器
}

void MainWindow::onLongPress()
{
    //    qDebug() << "Button long pressed!";
    // 在这里执行长按后的操作Btn_LetgoNum++;
    //    if(Btn_LetgoNum>1)
    //    {
    //        Btn_LetgoNum = 0;
    emit Sign_Start_detectionPoint("M",4600,1);
    qDebug()<<"点击屏幕强制放行";
    emit Sign_Start_detectionPoint("M",4600,0);
    //    }
}

void MainWindow::on_actionSysSet_triggered()
{
    SetSystemDataWindow->show();
}

QList<PTMotorFP_Setting_basis> readPTMotorSettingsFromIni(QString channel)//读取PT电机参数
{
    PTmotorSettingsList.clear();
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_PT_Data.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    settings.beginGroup(channel);

    // 读取12个电机的配置
    for (int motorNum = 1; motorNum <= 12; ++motorNum)
    {
        QString motorPrefix = QString("Motor_%1").arg(motorNum);
        PTMotorFP_Setting_basis motorSetting;

        QPair<uchar, uchar> res1Pos = Data_Set->getMotorPosition(settings.value(motorPrefix + "_PTName").toString());
        QString path1 = QApplication::applicationDirPath() + "/HVAC/SettingData.ini";
        QSettings *INI_File = new QSettings(path1, QSettings::IniFormat);
        INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));

        motorSetting.m_COM = INI_File->value(QString::number(res1Pos.first)+"/serialNumber").toString();
        motorSetting.m_Borad = QString::number(res1Pos.first).toInt();//板号
        motorSetting.m_id = QString::number(res1Pos.second).toInt();//id号
        qDebug()<<"读取到"+settings.value(motorPrefix + "_PTName").toString()+"串口号："<<motorSetting.m_COM<<motorSetting.m_Borad<<motorSetting.m_id;
        if(settings.value(motorPrefix + "_Enable").toInt() == 1)//使能
        {
            motorSetting.m_motorEnabled = 1;
        }
        else
        {
            motorSetting.m_motorEnabled = 0;
        }

        motorSetting.m_name = settings.value(motorPrefix + "_PTName").toString();// 读取名称
        //        if (motorSetting.m_name.isEmpty()) {
        //            motorSetting.m_name = QString("电机%1").arg(motorNum);
        //        }

        motorSetting.m_motorNumber = settings.value(motorPrefix + "_MotorNum").toInt();//电机号

        if(settings.value(motorPrefix + "_PT_Mode_flag").toInt() == 1)//PT类型：1五线 2两线
        {
            motorSetting.m_motorType =1;
            motorSetting.m_PTmotorMode = 1;

        }
        else
        {
            motorSetting.m_motorType =1;
            motorSetting.m_PTmotorMode = 2;
        }

        if(settings.value(motorPrefix + "_PT_Direction_flag").toInt() == 1)//电机方向：1=5~0V  2=0~5V
        {
            motorSetting.m_motorDirection = 2;
        }
        else
        {
            motorSetting.m_motorDirection = 1;
        }

        if(settings.value(motorPrefix + "_PT_Line2_flag").toInt() == 1)//两线类型：1=堵转  2=停止
        {
            motorSetting.m_towmotortype = true;
        }
        else
        {
            motorSetting.m_towmotortype = false;
        }

        motorSetting.m_currentUpperLimit = static_cast<int>(settings.value(motorPrefix + "_Run_Max_A", 0).toDouble() * 1000); // 电流上限(毫安)
        motorSetting.m_currentLowerLimit = static_cast<int>(settings.value(motorPrefix + "_Run_Min_A", 0).toDouble() * 1000); // 电流下限(毫安)
        motorSetting.m_stallCurrent = static_cast<int>(settings.value(motorPrefix + "_Stuck_A", 0).toDouble() * 1000);        // 读取堵转电流参数
        motorSetting.m_timeoutMs = static_cast<int>(settings.value(motorPrefix + "_Run_MaxTime", 0).toDouble()* 100);         //最大运行时间
        motorSetting.m_startDelayMs = static_cast<int>(settings.value(motorPrefix + "_Start_Delay", 0).toDouble() * 100);    //启动延时
        motorSetting.m_alarmDelayMs = static_cast<int>(settings.value(motorPrefix + "_Delay_alarm", 0).toDouble() * 100);    //报警延时
        motorSetting.m_line2MotorRunTime = settings.value(motorPrefix + "_Line2Motor_RunTime", 0).toDouble();          //两线电机运行时间
        motorSetting.m_voltageAvgCount = static_cast<int>(settings.value(motorPrefix + "_voltageAvgCount").toInt());   // 默认电压平均次数
        motorSetting.m_currentAvgCount = static_cast<int>(settings.value(motorPrefix + "_currentAvgCount").toInt());  // 默认电流平均次数

        PTmotorSettingsList.append(motorSetting);
    }

    settings.endGroup();
    return PTmotorSettingsList;
}
QList<PTMotorFP_Setting_basis1> readPTMotorSettingsFromIni1(QString channel)//读取PT电机参数上下限
{
    PTmotorSettingsList1.clear();
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_PT_Data.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    settings.beginGroup(channel);

    // 读取12个电机的配置
    for (int motorNum = 1; motorNum <= 12; ++motorNum)
    {
        QString motorPrefix = QString("Motor_%1").arg(motorNum);
        PTMotorFP_Setting_basis1 motorSetting;
        QString stepStr = settings.value(motorPrefix + "_Step").toString();
        motorSetting.m_POS = stepStr;
        QString maxStr = settings.value(motorPrefix + "_Max_Value").toString();
        QString minStr = settings.value(motorPrefix + "_Min_Value").toString();
        // 将字符串分割为列表
        QStringList stepList = stepStr.split(",");
        QStringList maxList = maxStr.split(",");
        QStringList minList = minStr.split(",");
        // 生成重新排序后的字符串
        QStringList newMaxList;
        QStringList newMinList;
        foreach (QString step, stepList) {
            bool ok;
            int index = step.toInt(&ok) - 1; // Step从1开始，列表索引从0开始
            if (ok && index >= 0 && index < maxList.size()) {
                newMaxList.append(maxList.at(index));
                newMinList.append(minList.at(index));
            } else {
                // 处理无效索引的情况，这里添加空字符串作为占位符
                newMaxList.append("");
                newMinList.append("");
            }
        }
        motorSetting.m_MaxValue = newMaxList.join(",");
        motorSetting.m_MinValue = newMinList.join(",");
        motorSetting.m_Time = settings.value(motorPrefix + "_Delay").toString();
        motorSetting.m_PTName = settings.value(motorPrefix + "_PTName").toString();
        PTmotorSettingsList1.append(motorSetting);
    }

    settings.endGroup();
    return PTmotorSettingsList1;
}

QList<LINMotorFP_Setting_basis> readLINMotorSettingsFromIni(QString channel)//读取LIN电机参数
{
    LINmotorSettingsList.clear();
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_LIN_Data.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    settings.beginGroup(channel);

    // 读取12个电机的配置
    for (int motorNum = 1; motorNum <= 12; ++motorNum)
    {
        QString motorPrefix = QString("LIN1_%1").arg(motorNum);
        LINMotorFP_Setting_basis motorSetting;

        motorSetting.m_id = settings.value(motorPrefix + "_id").toInt();//id号
        if(settings.value(motorPrefix + "_Enable").toInt() == 1)//使能
        {
            motorSetting.m_motorEnabled = 1;
        }
        else
        {
            motorSetting.m_motorEnabled = 0;
        }
        if(settings.value(motorPrefix + "_ErrorEnable").toInt() == 1)//步数误差使能
        {
            motorSetting.m_motorerrEnabled = 1;
        }
        else
        {
            motorSetting.m_motorerrEnabled = 0;
        }
        if(settings.value(motorPrefix + "_InitEnable").toInt() == 1)//初始化使能
        {
            motorSetting.m_motorInitEnabled = 1;
        }
        else
        {
            motorSetting.m_motorInitEnabled = 0;
        }
        motorSetting.m_name = settings.value(motorPrefix + "_Name", "").toString();// 读取名称
        if (motorSetting.m_name.isEmpty()) {
            motorSetting.m_name = QString("电机%1").arg(motorNum);
        }
        motorSetting.m_motorRunSpeed = settings.value(motorPrefix + "_RunSpeed").toDouble(); //运行速度
        motorSetting.m_motorMaxtimer = settings.value(motorPrefix + "_MaxRunTime").toDouble() * 1000; // 最大运行时间
        motorSetting.m_motorInitDirection = settings.value(motorPrefix + "_InitDirection").toInt(); //初始化方向
        if(motorSetting.m_motorerrEnabled == 1)
        {
            motorSetting.m_motorStepErrValue = settings.value(motorPrefix + "_errorValue").toInt();  //误差值
        }
        else
        {
            motorSetting.m_motorStepErrValue = 0;  //误差值
        }

        motorSetting.m_motorNAD = settings.value(motorPrefix + "_NAD").toString();    //启动延时
        motorSetting.m_motorControlid = settings.value(motorPrefix + "_Controlid").toString();//控制ID
        motorSetting.m_motorStateid = settings.value(motorPrefix + "_Stateid").toString();//状态ID
        motorSetting.m_motorOther = settings.value(motorPrefix + "_Direction").toInt();   //旋转方向，应急位置，应急释放
        motorSetting.m_motorInitValue = settings.value(motorPrefix + "_InitValue").toInt();  // 初始化值
        LINmotorSettingsList.append(motorSetting);

    }

    settings.endGroup();
    return LINmotorSettingsList;
}
/*
QList<LINMotorFP_Setting_basis1> readLINMotorSettingsFromIni1(QString channel)//读取LIN电机参数上下限
{
    LINmotorSettingsList1.clear();
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_LIN_Data.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    settings.beginGroup(channel);

    // 读取12个电机的配置
    for (int motorNum = 1; motorNum <= 12; ++motorNum)
    {
        QString motorPrefix = QString("LIN1_%1").arg(motorNum);
        LINMotorFP_Setting_basis1 motorSetting;
        QString stepStr = settings.value(motorPrefix + "_Step").toString();
        motorSetting.m_POS = stepStr;//原顺序
        QString ValueStr = settings.value(motorPrefix + "_POS_Value").toString();
        // 将字符串分割为列表
        QStringList stepList = stepStr.split(",");
        QStringList ValueList = ValueStr.split(",");
        // 生成重新排序后的字符串
        QStringList newValueList;
        foreach (QString step, stepList) {
            bool ok;
            int index = step.toInt(&ok) - 1; // Step从1开始，列表索引从0开始
            if (ok && index >= 0 && index < ValueList.size()) {
                newValueList.append(ValueList.at(index));
            } else {
                // 处理无效索引的情况，这里添加空字符串作为占位符
                newValueList.append("");
            }
        }

        motorSetting.m_Value = newValueList.join(",");

        motorSetting.m_Time = settings.value(motorPrefix + "_Time").toString();
        motorSetting.m_LINName = settings.value(motorPrefix + "_LINName").toString();

        LINmotorSettingsList1.append(motorSetting);

    }

    settings.endGroup();
    return LINmotorSettingsList1;
}*/

Blower_Setting_basis readBlowerSettingsFromIni(QString channel)//读取鼓风机参数
{
    //    BlowerSettingsList.clear();
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_Blower_Data.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    settings.beginGroup(channel);
    Blower_Setting_basis motorSetting;
    if(settings.value("Blower_Enable").toInt()==1)
    {
        motorSetting.m_BlowerEnabled = true;
    }

    motorSetting.m_BlowerMode = settings.value("Blower_Mode").toInt();
    motorSetting.m_BlowerPowervoltageUP = settings.value("Blower_V_Max").toDouble()*1000;
    motorSetting.m_BlowerPowervoltageDown = settings.value("Blower_V_Min").toDouble()*1000;
    motorSetting.m_BlowerRate = settings.value("Blower_PWM_HZ").toInt();
    motorSetting.m_LINBlowerControlid= settings.value("LINBlower_Controlid").toString();
    motorSetting.m_LINBlowerStateid= settings.value("LINBlower_Stateid").toString();
    motorSetting.m_LINBlowerSendid  = settings.value("LINBlower_Send_ID").toString();
    motorSetting.m_LINBlowerReadid  = settings.value("LINBlower_Read_ID").toString();
    motorSetting.m_BlowerStartDelay  = settings.value("Blower_Start_Delay").toString();

    if(settings.value("Blower_Enable").toInt()==1)
    {
        motorSetting.m_LINBlowerSpeed_Compare = true;
    }
    motorSetting.m_LINBlowerErrorValue= settings.value("LINBlower_error").toInt();

    if(settings.value("X_vibration_Enable").toInt()==1)
    {
        motorSetting.m_X_vibration_Enable = true;
    }
    if(settings.value("Y_vibration_Enable").toInt()==1)
    {
        motorSetting.m_Y_vibration_Enable = true;
    }
    if(settings.value("Z_vibration_Enable").toInt()==1)
    {
        motorSetting.m_Z_vibration_Enable = true;
    }
    if(settings.value("Noises_Enable").toInt()==1)
    {
        motorSetting.m_Noises_Enable = true;
    }
    motorSetting.m_vibration_StartDelay= settings.value("Vibration_Delay").toDouble()*1000;
    motorSetting.m_vibration_DelayAlarm= settings.value("Vibration_CheckTime").toDouble()*1000;
    motorSetting.m_Noises_StartDelay= settings.value("Noises_Delay").toDouble()*1000;
    motorSetting.m_Noises_DelayAlarm= settings.value("Noises_CheckTime").toDouble()*1000;

    settings.endGroup();

    settings.destroyed();


    return motorSetting;
}
Blower_Setting_basis1 readBlowerSettingsFromIni1(QString channel)//读取鼓风机上下限参数
{
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_Blower_Data.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));

    settings.beginGroup(channel);
    Blower_Setting_basis1 motorSetting;
    motorSetting.m_POS = settings.value("Blower_Step").toString();

    if(settings.value("Blower_Mode").toInt()==2)
    {
        motorSetting.m_Type = QString::number(2);
        QString stepStr = settings.value("Blower_Step").toString();
        QString ValueStr = settings.value("VoltageBlower_Voltage").toString();
        QString TimeStr = settings.value("VoltageBlower_Time").toString();
        QString MaxValueStr = settings.value("VoltageBlower_MaxA").toString();
        QString MinValueStr = settings.value("VoltageBlower_MinA").toString();

        // 将字符串分割为列表
        QStringList stepList = stepStr.split(",");
        QStringList ValueList = ValueStr.split(",");
        QStringList TimeList = TimeStr.split(",");
        QStringList MaxValueList = MaxValueStr.split(",");
        QStringList MinValueList = MinValueStr.split(",");
        // 生成重新排序后的字符串
        QStringList newValueList;
        QStringList newTimeList;
        QStringList newMaxValueList;
        QStringList newMinValueList;
        foreach (QString step, stepList) {
            bool ok;
            int index = step.toInt(&ok) - 1; // Step从1开始，列表索引从0开始
            if (ok && index >= 0 && index < stepList.size()) {
                newValueList.append(ValueList.at(index));
                newTimeList.append(TimeList.at(index));
                newMaxValueList.append(MaxValueList.at(index));
                newMinValueList.append(MinValueList.at(index));
            } else {
                // 处理无效索引的情况，这里添加空字符串作为占位符
                newValueList.append("");
                newTimeList.append("");
                newMaxValueList.append("");
                newMinValueList.append("");
            }
        }
        motorSetting.m_Value = newValueList.join(",");
        motorSetting.m_Time = newTimeList.join(",");
        motorSetting.m_BlowerMaxValue = newMaxValueList.join(",");
        motorSetting.m_BlowerMinValue = newMinValueList.join(",");

    }
    else if(settings.value("Blower_Mode").toInt()==1)
    {
        motorSetting.m_Type = QString::number(1);
        QString stepStr = settings.value("Blower_Step").toString();
        QString ValueStr = settings.value("PWMBlower_PWM").toString();
        QString TimeStr = settings.value("PWMBlower_Time").toString();
        QString MaxValueStr = settings.value("PWMBlower_MaxA").toString();
        QString MinValueStr = settings.value("PWMBlower_MinA").toString();
        // 将字符串分割为列表
        QStringList stepList = stepStr.split(",");
        QStringList ValueList = ValueStr.split(",");
        QStringList TimeList = TimeStr.split(",");
        QStringList MaxValueList = MaxValueStr.split(",");
        QStringList MinValueList = MinValueStr.split(",");
        // 生成重新排序后的字符串
        QStringList newValueList;
        QStringList newTimeList;
        QStringList newMaxValueList;
        QStringList newMinValueList;
        foreach (QString step, stepList) {
            bool ok;
            int index = step.toInt(&ok) - 1; // Step从1开始，列表索引从0开始
            if (ok && index >= 0 && index < stepList.size()) {
                newValueList.append(ValueList.at(index));
                newTimeList.append(TimeList.at(index));
                newMaxValueList.append(MaxValueList.at(index));
                newMinValueList.append(MinValueList.at(index));
            } else {
                // 处理无效索引的情况，这里添加空字符串作为占位符
                newValueList.append("");
                newTimeList.append("");
                newMaxValueList.append("");
                newMinValueList.append("");
            }
        }
        motorSetting.m_Value = newValueList.join(",");
        motorSetting.m_Time = newTimeList.join(",");
        motorSetting.m_BlowerMaxValue = newMaxValueList.join(",");
        motorSetting.m_BlowerMinValue = newMinValueList.join(",");
    }
    else if(settings.value("Blower_Mode").toInt()==3)
    {
        motorSetting.m_Type = QString::number(3);
        QString stepStr = settings.value("Blower_Step").toString();
        QString ValueStr = settings.value("LINBlower_LIN").toString();
        QString TimeStr = settings.value("LINBlower_Time").toString();
        QString MaxValueStr = settings.value("LINBlower_MaxA").toString();
        QString MinValueStr = settings.value("LINBlower_MinA").toString();
        // 将字符串分割为列表
        QStringList stepList = stepStr.split(",");
        QStringList ValueList = ValueStr.split(",");
        QStringList TimeList = TimeStr.split(",");
        QStringList MaxValueList = MaxValueStr.split(",");
        QStringList MinValueList = MinValueStr.split(",");
        // 生成重新排序后的字符串
        QStringList newValueList;
        QStringList newTimeList;
        QStringList newMaxValueList;
        QStringList newMinValueList;
        foreach (QString step, stepList) {
            bool ok;
            int index = step.toInt(&ok) - 1; // Step从1开始，列表索引从0开始
            if (ok && index >= 0 && index < stepList.size()) {
                newValueList.append(ValueList.at(index));
                newTimeList.append(TimeList.at(index));
                newMaxValueList.append(MaxValueList.at(index));
                newMinValueList.append(MinValueList.at(index));
            } else {
                // 处理无效索引的情况，这里添加空字符串作为占位符
                newValueList.append("");
                newTimeList.append("");
                newMaxValueList.append("");
                newMinValueList.append("");
            }
        }
        motorSetting.m_Value = newValueList.join(",");
        motorSetting.m_Time = newTimeList.join(",");
        motorSetting.m_BlowerMaxValue = newMaxValueList.join(",");
        motorSetting.m_BlowerMinValue = newMinValueList.join(",");
    }

    QString stepStr = settings.value("Blower_Step").toString();
    QString XVibrationMaxValue = settings.value("XVibration_MaxValue").toString();
    QString XVibrationMinValue = settings.value("XVibration_MinValue").toString();
    QString YVibrationMaxValue = settings.value("YVibration_MaxValue").toString();
    QString YVibrationMinValue = settings.value("YVibration_MinValue").toString();
    QString ZVibrationMaxValue = settings.value("ZVibration_MaxValue").toString();
    QString ZVibrationMinValue = settings.value("ZVibration_MinValue").toString();
    QString NoisesMaxValue = settings.value("Noises_MaxValue").toString();
    QString NoisesMinValue = settings.value("Noises_MinValue").toString();
    // 将字符串分割为列表
    QStringList stepList = stepStr.split(",");
    QStringList XVibrationMaxValueList = XVibrationMaxValue.split(",");
    QStringList XVibrationMinValueList = XVibrationMinValue.split(",");
    QStringList YVibrationMaxValueList = YVibrationMaxValue.split(",");
    QStringList YVibrationMinValueList = YVibrationMinValue.split(",");
    QStringList ZVibrationMaxValueList = ZVibrationMaxValue.split(",");
    QStringList ZVibrationMinValueList = ZVibrationMinValue.split(",");
    QStringList NoisesMaxValueList = NoisesMaxValue.split(",");
    QStringList NoisesMinValueList = NoisesMinValue.split(",");
    // 生成重新排序后的字符串
    QStringList newXVibrationMaxValueList;
    QStringList newXVibrationMinValueList;
    QStringList newYVibrationMaxValueList;
    QStringList newYVibrationMinValueList;
    QStringList newZVibrationMaxValueList;
    QStringList newZVibrationMinValueList;
    QStringList newNoisesMaxValueList ;
    QStringList newNoisesMinValueList ;

    foreach (QString step, stepList) {
        bool ok;
        int index = step.toInt(&ok) - 1; // Step从1开始，列表索引从0开始
        if (ok && index >= 0 && index < stepList.size()) {
            newXVibrationMaxValueList.append(XVibrationMaxValueList.at(index));
            newXVibrationMinValueList.append(XVibrationMinValueList.at(index));
            newYVibrationMaxValueList.append(YVibrationMaxValueList.at(index));
            newYVibrationMinValueList.append(YVibrationMinValueList.at(index));
            newZVibrationMaxValueList.append(ZVibrationMaxValueList.at(index));
            newZVibrationMinValueList.append(ZVibrationMinValueList.at(index));
            newNoisesMaxValueList.append(NoisesMaxValueList.at(index));
            newNoisesMinValueList.append(NoisesMinValueList.at(index));
        } else {
            // 处理无效索引的情况，这里添加空字符串作为占位符
            newXVibrationMaxValueList.append("");
            newXVibrationMinValueList.append("");
            newYVibrationMaxValueList.append("");
            newYVibrationMinValueList.append("");
            newZVibrationMaxValueList.append("");
            newZVibrationMinValueList.append("");
            newNoisesMaxValueList.append("");
            newNoisesMinValueList.append("");
        }
    }
    motorSetting.m_X_vibrationrMaxValue = newXVibrationMaxValueList.join(",");
    motorSetting.m_X_vibrationrMinValue = newXVibrationMinValueList.join(",");
    motorSetting.m_Y_vibrationMaxValue = newYVibrationMaxValueList.join(",");
    motorSetting.m_Y_vibrationMinValue = newYVibrationMinValueList.join(",");
    motorSetting.m_Z_vibrationMaxValue = newZVibrationMaxValueList.join(",");
    motorSetting.m_Z_vibrationMinValue = newZVibrationMinValueList.join(",");
    motorSetting.m_NoisesMaxValue = newNoisesMaxValueList.join(",");
    motorSetting.m_NoisesMinValue = newNoisesMinValueList.join(",");

    settings.endGroup();

    settings.destroyed();
    return motorSetting;
}

QList<QList<LINMotorFP_Setting_basis1>> readLINMotorSettingsFromIniData(QString channel)//读取LIN电机参数上下限
{
    //    LINmotorSettingsList2.clear();
    LINmotorSettingsList1.clear();

    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_LIN_Data.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    settings.beginGroup(channel);

    // 读取12个电机的配置
    for (int motorNum = 1; motorNum <= 12; ++motorNum)
    {

        QString motorPrefix = QString("LIN1_%1").arg(motorNum);
        LINMotorFP_Setting_basis1 motorSetting;
        QString stepStr = settings.value(motorPrefix + "_Step").toString();
        motorSetting.m_POS = stepStr;//原顺序
        QString ValueStr = settings.value(motorPrefix + "_POS_Value").toString();
        // 将字符串分割为列表
        QStringList stepList = stepStr.split(",");
        QStringList ValueList = ValueStr.split(",");
        // 生成重新排序后的字符串
        QStringList newValueList;
        foreach (QString step, stepList) {
            bool ok;
            int index = step.toInt(&ok) - 1; // Step从1开始，列表索引从0开始
            if (ok && index >= 0 && index < ValueList.size()) {
                newValueList.append(ValueList.at(index));
            } else {
                // 处理无效索引的情况，这里添加空字符串作为占位符
                newValueList.append("");
            }
        }

        motorSetting.m_Value = newValueList.join(",");

        motorSetting.m_Time = settings.value(motorPrefix + "_Time").toString();
        motorSetting.m_LINName = settings.value(motorPrefix + "_LINName").toString();


        QStringList POSList = motorSetting.m_POS.split(",");//把POS分割
        QStringList Value1List = motorSetting.m_Value.split(",");
        QStringList TimeList = motorSetting.m_Time.split(",");
        //        QStringList LINNameList = motorSetting.m_LINName.split(",");
        qDebug()<<POSList.count()<<Value1List.count()<<TimeList.count();
        LINmotorSettingsList2.clear();
        for(int j=0;j<POSList.count();j++)
        {
            LINMotorFP_Setting_basis1 motorSetting1;
            motorSetting1 .m_POS =  POSList.at(j);
            motorSetting1.m_Value  = Value1List.at(j);
            motorSetting1.m_LINName = settings.value(motorPrefix + "_LINName").toString();
            if(j<7)
            {
                motorSetting1.m_Time = TimeList.at(j);
            }
            else
            {
                motorSetting1.m_Time = "0";
            }

            //            LINmotorSettingsList2.clear();
            LINmotorSettingsList2.append(motorSetting1);
        }

        LINmotorSettingsList1.append(LINmotorSettingsList2);
    }

    settings.endGroup();
    return LINmotorSettingsList1;
}


QList<ToralThermistor_Setting_basis> readRESSettingsFromIni(QString channel)
{
    ResSettingsList.clear();
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_ResSpeed_Data.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
//    settings.beginGroup(channel);
    for(int i=0;i<3;i++)
    {
        ToralThermistor_Setting_basis ResSetting;
        ResSetting.Compare_Enable = settings.value(channel+"/ResSurroundings").toBool();
        ResSetting.RunTime = (settings.value(channel+"/Res_CheckTime").toFloat() * 10);
        ResSetting.DelayTime = (settings.value(channel+"/Res_StartDelay").toFloat() * 10);
        ResSetting.m_Borad = i+2;
        ResSetting.temperature_Err = settings.value(channel+"/Res_Tem_error").toDouble();





        ResSettingsList.append(ResSetting);
    }

    return ResSettingsList;
}

QList<QList<Thermistor_Setting_basis>> readRESSettingsFromIni1(QString channel)
{
    ResSettingsList1.clear();
    ResSettingsList2.clear();
    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_ResSpeed_Data.ini";
    QSettings settings(path, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    //    settings.beginGroup(channel);
    qDebug()<<channel+"/Res_Enable"<<settings.value(channel+"/Res_Enable").toString();

    QString Res_Enable = settings.value(channel+"/Res_Enable").toString();

    QString Res_PosName = settings.value(channel+"/Res_PosName").toString();
    QString Res_Temp = settings.value(channel+"/Res_Temp").toString();
    QString Res_Value = settings.value(channel+"/Res_Value").toString();
    QString Res_MaterialConstant = settings.value(channel+"/Res_MaterialConstant").toString();
    QString Res_MaxValue = settings.value(channel+"/Res_MaxValue").toString();
    QString Res_MinValue = settings.value(channel+"/Res_MinValue").toString();
    qDebug()<<"11111111111111"<<Res_Enable;

    QStringList Res_EnableList = Res_Enable.split(",");//温敏电阻使能
    QStringList Res_PosNameList = Res_PosName.split(",");
    QStringList Res_TempList = Res_Temp.split(",");
    QStringList Res_ValueList = Res_Value.split(",");
    QStringList Res_MaterialConstantList = Res_MaterialConstant.split(",");
    QStringList Res_MaxValueList = Res_MaxValue.split(",");
    QStringList Res_MinValueList = Res_MinValue.split(",");


    for(int i =0;i<15;i++)
    {
        Thermistor_Setting_basis ResSetting1;
        if(i<5)
        {
            ResSetting1.Environment = Res_EnableList.last().toInt();
            qDebug()<<"温敏电阻使能数量："<<Res_EnableList.count();
            if(Res_EnableList.at(i).toInt()==1)
            {
                ResSetting1.Temperature_Enable = true;
            }
            else
            {
                ResSetting1.Temperature_Enable = false;
            }
            ResSetting1.RC = Res_TempList.at(i).toDouble();
            ResSetting1.Beta = Res_MaterialConstantList.at(i).toDouble();
            ResSetting1.R25 = Res_ValueList.at(i).toDouble();
            ResSetting1.Temperature_upper = Res_MaxValueList.at(i).toDouble();
            ResSetting1.Temperature_lower = Res_MinValueList.at(i).toDouble();
            ResSettingsList1.append(ResSetting1);
        }
        else if(i<10)
        {
            ResSetting1.Environment = Res_EnableList.last().toInt();
            if(Res_EnableList.at(i).toInt()==1)
            {
                ResSetting1.Temperature_Enable = true;
            }
            else
            {
                ResSetting1.Temperature_Enable = false;
            }
            ResSetting1.RC = Res_TempList.at(i).toDouble();
            ResSetting1.Beta = Res_MaterialConstantList.at(i).toDouble();
            ResSetting1.R25 = Res_ValueList.at(i).toDouble();
            ResSetting1.Temperature_upper = Res_MaxValueList.at(i).toDouble();
            ResSetting1.Temperature_lower = Res_MinValueList.at(i).toDouble();
            ResSettingsList1.append(ResSetting1);
        }
        else if(i<15)
        {
            ResSetting1.Environment = Res_EnableList.last().toInt();
            qDebug()<<"温敏电阻使能数量："<<Res_EnableList.count();
            if(i>11)
            {
                ResSetting1.Temperature_Enable = false;
                ResSetting1.RC = 0;
                ResSetting1.Beta = 0;
                ResSetting1.R25 = 0;
                ResSetting1.Temperature_upper = 0;
                ResSetting1.Temperature_lower = 0;
            }
            else
            {
                if(Res_EnableList.at(i).toInt()==1)
                {
                    ResSetting1.Temperature_Enable = true;
                }
                else
                {
                    ResSetting1.Temperature_Enable = false;
                }

                ResSetting1.RC = Res_TempList.at(i).toDouble();
                ResSetting1.Beta = Res_MaterialConstantList.at(i).toDouble();
                ResSetting1.R25 = Res_ValueList.at(i).toDouble();
                ResSetting1.Temperature_upper = Res_MaxValueList.at(i).toDouble();
                ResSetting1.Temperature_lower = Res_MinValueList.at(i).toDouble();

            }
            ResSettingsList1.append(ResSetting1);
        }


        if(i == 4 || i == 9 || i == 14){
            ResSettingsList2.append(ResSettingsList1);
            ResSettingsList1.clear();
        }

    }

    return ResSettingsList2 ;
}







void MainWindow::on_Auto_PDbox_currentTextChanged(const QString &arg1)//界面频道切换
{
    QString PD = "PD" + arg1;
    readPTMotorSettingsFromIni(PD);

    readPTMotorSettingsFromIni1(PD);
    //    for (int i=0;i<PTmotorSettingsList1.count();i++ ) {
    //      qDebug()<<"-------------------"<<PTmotorSettingsList1.at(i).m_POS;
    //      qDebug()<<"-------------------"<<PTmotorSettingsList1.at(i).m_MaxValue;
    //       qDebug()<<"-------------------"<<PTmotorSettingsList1.at(i).m_MinValue;
    //    }


    readLINMotorSettingsFromIni(PD);

    readLINMotorSettingsFromIniData(PD);

    readRESSettingsFromIni(PD);

    readRESSettingsFromIni1(PD);

    Nthread_ptmotor->setPTMotorSettings(PTmotorSettingsList);
    Nthread_ptmotor->setPTMotorSettings1(PTmotorSettingsList1);





    QString path = QApplication::applicationDirPath() + "/HVAC/HVAC_Equence_Data.ini";
    qDebug()<<path;
    QSettings *INI_File = new QSettings(path, QSettings::IniFormat);
    INI_File->setIniCodec(QTextCodec::codecForName("GB2312"));
    QString SequenceStr = INI_File->value(PD+"/Equence").toString();//获取运行顺序
    qDebug()<<"当前设置运行顺序"<<SequenceStr;
    // 移除空格并分割字符串
    Nthread_main->m_stepOrderList = SequenceStr.remove(" ").split(",");
    qDebug()<<"执行顺序："<<Nthread_main->m_stepOrderList;
    //    INI_File->clear();

    MY_LINMotorIP_Setting_basis lin_fp;
    QList<MY_LINMotorIP_Setting_basis> lin_fp_qlist;
    QList<QList<MY_LINMotorIP_Setting_basis>> lin_fp_basis;//需移到其他地方并初始化赋值
    double doubleValue;




    //    qDebug()<<"当前列表数据有111"<<LINmotorSettingsList1[0][1].m_POS;
    bool ok;
    qDebug()<<"刘保存Lin电机参数";
    for(int i = 0; i < LINMotor_Count; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            lin_fp.process = LINmotorSettingsList1[i][j].m_POS.toInt(&ok);
            //            qDebug()<<lin_fp.process<<LINmotorSettingsList1[i][j].m_POS;
            lin_fp.m_motortargetStep = LINmotorSettingsList1[i][j].m_Value.toInt(&ok);
            //            qDebug()<<lin_fp.m_motortargetStep;
            lin_fp.m_motorSetStep = 0;

            doubleValue = LINmotorSettingsList1[i][j].m_Time.toDouble();
            lin_fp.m_stopTime = static_cast<int>(doubleValue * 10);


            //            qDebug()<<lin_fp.m_stopTime;

            lin_fp_qlist.insert(j,lin_fp);
        }
        lin_fp_basis.insert(i,lin_fp_qlist);
    }

    Nthread_linmotor->SetLINMotor_ProcessSet(lin_fp_basis);

    //鼓风机参数
    mBlowerSettingsList = readBlowerSettingsFromIni(PD);
    mBlowerSettingsList1 = readBlowerSettingsFromIni1(PD);
    //    emit sign_BlowerFixedPar(mBlowerSettingsList, mBlowerSettingsList1);
    m_Blower->slot_BlowerFixedPar(mBlowerSettingsList, mBlowerSettingsList1);


    //温敏参数---------------------------------------------------------------


        Nthread_Thermistor->SetToralThermistorBorad_Setting(ResSettingsList);

    //----------------------------------------------------------------------

    lin_fp_qlist.clear();
    lin_fp_basis.clear();
}

QList<int> MainWindow::getOpenedSerialPorts() const
{
    QList<int> openedPorts;
    for (auto it = m_serialOpened.constBegin(); it != m_serialOpened.constEnd(); ++it) {
        if (it.value()) {
            openedPorts.append(it.key());
        }
    }
    return openedPorts;
}

bool MainWindow::isSerialPortOpened(int portIndex) const
{
    return m_serialOpened.value(portIndex, false);
}

void MainWindow::closeSerialPort(int portIndex)
{
    if (m_workers.contains(portIndex)) {
        SerialPortWorker *worker = m_workers.value(portIndex);
        if (worker) {
            QMetaObject::invokeMethod(worker, "closeSerialPort", Qt::QueuedConnection);
        }
    }
}
void MainWindow::onSerialOpened(bool success, int portIndex)
{
    m_serialOpened[portIndex] = success;
    if (success) {
        ui->textEdit->append(tr("串口 %1 打开成功").arg(portIndex));//textEdit->append(tr("串口 %1 打开成功").arg(portIndex));
    } else {
        ui->textEdit->append(tr("串口 %1 打开失败").arg(portIndex));
    }
    emit serialPortStatusChanged(portIndex, success);
}

void MainWindow::onSerialClosed(int portIndex)
{
    m_serialOpened[portIndex] = false;
    ui->textEdit->append(tr("串口 %1 已关闭").arg(portIndex));
    emit serialPortStatusChanged(portIndex, false);
}

void MainWindow::sendDataToSerial(int portIndex, const QByteArray &data)
{
    //    // 检查端口索引是否存在且已打开
    //    if (m_workers.contains(portIndex) && m_serialOpened.value(portIndex, false)) {
    //        SerialPortWorker *worker = m_workers.value(portIndex);
    //        if (worker) {
    //            // 使用Qt::QueuedConnection确保线程安全
    //            QMetaObject::invokeMethod(worker, "writeData",Qt::QueuedConnection,Q_ARG(QByteArray, data));
    //        }
    //    } else {
    //        qDebug() << "Serial port" << portIndex << "is not available or not opened";
    //    }
}

void MainWindow::on_actiontest_triggered()
{
    ui->tabWidget->setCurrentIndex(1);
}


void MainWindow::on_Btn_test1_clicked()
{
    workerThread->start();
}


void MainWindow::on_actionMain_triggered()
{
    ui->tabWidget->setCurrentIndex(0);
}


void MainWindow::on_Btn_test2_clicked()
{

    emit testRunMotor(ui->lineEdit->text());
}

/*
* @description 界面控件重新定义
* @param { } 无
* @returns {void} 无
* @date 2025-10-28 20:21:00
* @author zh
*/
void MainWindow::initUIControlArrays()
{
    Auto_Blower_button[0] = ui->Auto_Blower_POS1;
    Auto_Blower_button[1] = ui->Auto_Blower_POS2;
    Auto_Blower_button[2] = ui->Auto_Blower_POS3;
    Auto_Blower_button[3] = ui->Auto_Blower_POS4;
    Auto_Blower_button[4] = ui->Auto_Blower_POS5;
    Auto_Blower_button[5] = ui->Auto_Blower_POS6;
    Auto_Blower_button[6] = ui->Auto_Blower_POS7;
    Auto_Blower_button[7] = ui->Auto_Blower_POS8;
    Auto_Blower_button[8] = ui->Auto_Blower_POS9;

    // 初始化x轴振动控件数组
    Auto_Vibration_x[0] = ui->Auto_Vibration_POS1_X;
    Auto_Vibration_x[1] = ui->Auto_Vibration_POS2_X;
    Auto_Vibration_x[2] = ui->Auto_Vibration_POS3_X;
    Auto_Vibration_x[3] = ui->Auto_Vibration_POS4_X;
    Auto_Vibration_x[4] = ui->Auto_Vibration_POS5_X;
    Auto_Vibration_x[5] = ui->Auto_Vibration_POS6_X;
    Auto_Vibration_x[6] = ui->Auto_Vibration_POS7_X;
    Auto_Vibration_x[7] = ui->Auto_Vibration_POS8_X;
    Auto_Vibration_x[8] = ui->Auto_Vibration_POS9_X;

    // 初始化y轴振动控件数组
    Auto_Vibration_y[0] = ui->Auto_Vibration_POS1_Y;
    Auto_Vibration_y[1] = ui->Auto_Vibration_POS2_Y;
    Auto_Vibration_y[2] = ui->Auto_Vibration_POS3_Y;
    Auto_Vibration_y[3] = ui->Auto_Vibration_POS4_Y;
    Auto_Vibration_y[4] = ui->Auto_Vibration_POS5_Y;
    Auto_Vibration_y[5] = ui->Auto_Vibration_POS6_Y;
    Auto_Vibration_y[6] = ui->Auto_Vibration_POS7_Y;
    Auto_Vibration_y[7] = ui->Auto_Vibration_POS8_Y;
    Auto_Vibration_y[8] = ui->Auto_Vibration_POS9_Y;

    // 初始化z轴振动控件数组
    Auto_Vibration_z[0] = ui->Auto_Vibration_POS1_Z;
    Auto_Vibration_z[1] = ui->Auto_Vibration_POS2_Z;
    Auto_Vibration_z[2] = ui->Auto_Vibration_POS3_Z;
    Auto_Vibration_z[3] = ui->Auto_Vibration_POS4_Z;
    Auto_Vibration_z[4] = ui->Auto_Vibration_POS5_Z;
    Auto_Vibration_z[5] = ui->Auto_Vibration_POS6_Z;
    Auto_Vibration_z[6] = ui->Auto_Vibration_POS7_Z;
    Auto_Vibration_z[7] = ui->Auto_Vibration_POS8_Z;
    Auto_Vibration_z[8] = ui->Auto_Vibration_POS9_Z;

    // 初始化噪音值控件数组
    Auto_Noises_Value[0] = ui->Auto_Noises_Value_POS1;
    Auto_Noises_Value[1] = ui->Auto_Noises_Value_POS2;
    Auto_Noises_Value[2] = ui->Auto_Noises_Value_POS3;
    Auto_Noises_Value[3] = ui->Auto_Noises_Value_POS4;
    Auto_Noises_Value[4] = ui->Auto_Noises_Value_POS5;
    Auto_Noises_Value[5] = ui->Auto_Noises_Value_POS6;
    Auto_Noises_Value[6] = ui->Auto_Noises_Value_POS7;
    Auto_Noises_Value[7] = ui->Auto_Noises_Value_POS8;
    Auto_Noises_Value[8] = ui->Auto_Noises_Value_POS9;

    // 初始化风速显示颜色按钮数组
    Auto_Speed_button[0] = ui->Auto_Speed1;
    Auto_Speed_button[1] = ui->Auto_Speed2;
    Auto_Speed_button[2] = ui->Auto_Speed3;
    Auto_Speed_button[3] = ui->Auto_Speed4;
    Auto_Speed_button[4] = ui->Auto_Speed5;
    Auto_Speed_button[5] = ui->Auto_Speed6;
    Auto_Speed_button[6] = ui->Auto_Speed7;
    Auto_Speed_button[7] = ui->Auto_Speed8;

    // 初始化鼓风机传值1控件数组
    Auto_Blower_Value[0] = ui->Auto_Blower_POS1_Value;
    Auto_Blower_Value[1] = ui->Auto_Blower_POS2_Value;
    Auto_Blower_Value[2] = ui->Auto_Blower_POS3_Value;
    Auto_Blower_Value[3] = ui->Auto_Blower_POS4_Value;
    Auto_Blower_Value[4] = ui->Auto_Blower_POS5_Value;
    Auto_Blower_Value[5] = ui->Auto_Blower_POS6_Value;
    Auto_Blower_Value[6] = ui->Auto_Blower_POS7_Value;
    Auto_Blower_Value[7] = ui->Auto_Blower_POS8_Value;
    Auto_Blower_Value[8] = ui->Auto_Blower_POS9_Value;

    // 初始化鼓风机传值2控件数组
    Auto_Blower_set_Value[0] = ui->Auto_Blower_POS1_Value_2;
    Auto_Blower_set_Value[1] = ui->Auto_Blower_POS2_Value_2;
    Auto_Blower_set_Value[2] = ui->Auto_Blower_POS3_Value_2;
    Auto_Blower_set_Value[3] = ui->Auto_Blower_POS4_Value_2;
    Auto_Blower_set_Value[4] = ui->Auto_Blower_POS5_Value_2;
    Auto_Blower_set_Value[5] = ui->Auto_Blower_POS6_Value_2;
    Auto_Blower_set_Value[6] = ui->Auto_Blower_POS7_Value_2;
    Auto_Blower_set_Value[7] = ui->Auto_Blower_POS8_Value_2;
    Auto_Blower_set_Value[8] = ui->Auto_Blower_POS9_Value_2;

    // 初始化风速值控件数组
    Auto_Speed_Value[0] = ui->Auto_Speed1_Value;
    Auto_Speed_Value[1] = ui->Auto_Speed2_Value;
    Auto_Speed_Value[2] = ui->Auto_Speed3_Value;
    Auto_Speed_Value[3] = ui->Auto_Speed4_Value;
    Auto_Speed_Value[4] = ui->Auto_Speed5_Value;
    Auto_Speed_Value[5] = ui->Auto_Speed6_Value;
    Auto_Speed_Value[6] = ui->Auto_Speed7_Value;
    Auto_Speed_Value[7] = ui->Auto_Speed8_Value;

    // 初始化风速模式值二维数组
    // 第1行（Speed1的8种模式）
    Auto_Speed_Mode_Value[0][0] = ui->Auto_Speed1_Mode1_Value;
    Auto_Speed_Mode_Value[0][1] = ui->Auto_Speed1_Mode2_Value;
    Auto_Speed_Mode_Value[0][2] = ui->Auto_Speed1_Mode3_Value;
    Auto_Speed_Mode_Value[0][3] = ui->Auto_Speed1_Mode4_Value;
    Auto_Speed_Mode_Value[0][4] = ui->Auto_Speed1_Mode5_Value;
    Auto_Speed_Mode_Value[0][5] = ui->Auto_Speed1_Mode6_Value;
    Auto_Speed_Mode_Value[0][6] = ui->Auto_Speed1_Mode7_Value;
    Auto_Speed_Mode_Value[0][7] = ui->Auto_Speed1_Mode8_Value;

    // 第2行（Speed2的8种模式）
    Auto_Speed_Mode_Value[1][0] = ui->Auto_Speed2_Mode1_Value;
    Auto_Speed_Mode_Value[1][1] = ui->Auto_Speed2_Mode2_Value;
    Auto_Speed_Mode_Value[1][2] = ui->Auto_Speed2_Mode3_Value;
    Auto_Speed_Mode_Value[1][3] = ui->Auto_Speed2_Mode4_Value;
    Auto_Speed_Mode_Value[1][4] = ui->Auto_Speed2_Mode5_Value;
    Auto_Speed_Mode_Value[1][5] = ui->Auto_Speed2_Mode6_Value;
    Auto_Speed_Mode_Value[1][6] = ui->Auto_Speed2_Mode7_Value;
    Auto_Speed_Mode_Value[1][7] = ui->Auto_Speed2_Mode8_Value;

    // 第3行（Speed3的8种模式）
    Auto_Speed_Mode_Value[2][0] = ui->Auto_Speed3_Mode1_Value;
    Auto_Speed_Mode_Value[2][1] = ui->Auto_Speed3_Mode2_Value;
    Auto_Speed_Mode_Value[2][2] = ui->Auto_Speed3_Mode3_Value;
    Auto_Speed_Mode_Value[2][3] = ui->Auto_Speed3_Mode4_Value;
    Auto_Speed_Mode_Value[2][4] = ui->Auto_Speed3_Mode5_Value;
    Auto_Speed_Mode_Value[2][5] = ui->Auto_Speed3_Mode6_Value;
    Auto_Speed_Mode_Value[2][6] = ui->Auto_Speed3_Mode7_Value;
    Auto_Speed_Mode_Value[2][7] = ui->Auto_Speed3_Mode8_Value;

    // 第4行（Speed4的8种模式）
    Auto_Speed_Mode_Value[3][0] = ui->Auto_Speed4_Mode1_Value;
    Auto_Speed_Mode_Value[3][1] = ui->Auto_Speed4_Mode2_Value;
    Auto_Speed_Mode_Value[3][2] = ui->Auto_Speed4_Mode3_Value;
    Auto_Speed_Mode_Value[3][3] = ui->Auto_Speed4_Mode4_Value;
    Auto_Speed_Mode_Value[3][4] = ui->Auto_Speed4_Mode5_Value;
    Auto_Speed_Mode_Value[3][5] = ui->Auto_Speed4_Mode6_Value;
    Auto_Speed_Mode_Value[3][6] = ui->Auto_Speed4_Mode7_Value;
    Auto_Speed_Mode_Value[3][7] = ui->Auto_Speed4_Mode8_Value;

    // 第5行（Speed5的8种模式）
    Auto_Speed_Mode_Value[4][0] = ui->Auto_Speed5_Mode1_Value;
    Auto_Speed_Mode_Value[4][1] = ui->Auto_Speed5_Mode2_Value;
    Auto_Speed_Mode_Value[4][2] = ui->Auto_Speed5_Mode3_Value;
    Auto_Speed_Mode_Value[4][3] = ui->Auto_Speed5_Mode4_Value;
    Auto_Speed_Mode_Value[4][4] = ui->Auto_Speed5_Mode5_Value;
    Auto_Speed_Mode_Value[4][5] = ui->Auto_Speed5_Mode6_Value;
    Auto_Speed_Mode_Value[4][6] = ui->Auto_Speed5_Mode7_Value;
    Auto_Speed_Mode_Value[4][7] = ui->Auto_Speed5_Mode8_Value;

    // 第6行（Speed6的8种模式）
    Auto_Speed_Mode_Value[5][0] = ui->Auto_Speed6_Mode1_Value;
    Auto_Speed_Mode_Value[5][1] = ui->Auto_Speed6_Mode2_Value;
    Auto_Speed_Mode_Value[5][2] = ui->Auto_Speed6_Mode3_Value;
    Auto_Speed_Mode_Value[5][3] = ui->Auto_Speed6_Mode4_Value;
    Auto_Speed_Mode_Value[5][4] = ui->Auto_Speed6_Mode5_Value;
    Auto_Speed_Mode_Value[5][5] = ui->Auto_Speed6_Mode6_Value;
    Auto_Speed_Mode_Value[5][6] = ui->Auto_Speed6_Mode7_Value;
    Auto_Speed_Mode_Value[5][7] = ui->Auto_Speed6_Mode8_Value;

    // 第7行（Speed7的8种模式）
    Auto_Speed_Mode_Value[6][0] = ui->Auto_Speed7_Mode1_Value;
    Auto_Speed_Mode_Value[6][1] = ui->Auto_Speed7_Mode2_Value;
    Auto_Speed_Mode_Value[6][2] = ui->Auto_Speed7_Mode3_Value;
    Auto_Speed_Mode_Value[6][3] = ui->Auto_Speed7_Mode4_Value;
    Auto_Speed_Mode_Value[6][4] = ui->Auto_Speed7_Mode5_Value;
    Auto_Speed_Mode_Value[6][5] = ui->Auto_Speed7_Mode6_Value;
    Auto_Speed_Mode_Value[6][6] = ui->Auto_Speed7_Mode7_Value;
    Auto_Speed_Mode_Value[6][7] = ui->Auto_Speed7_Mode8_Value;

    // 第8行（Speed8的8种模式）
    Auto_Speed_Mode_Value[7][0] = ui->Auto_Speed8_Mode1_Value;
    Auto_Speed_Mode_Value[7][1] = ui->Auto_Speed8_Mode2_Value;
    Auto_Speed_Mode_Value[7][2] = ui->Auto_Speed8_Mode3_Value;
    Auto_Speed_Mode_Value[7][3] = ui->Auto_Speed8_Mode4_Value;
    Auto_Speed_Mode_Value[7][4] = ui->Auto_Speed8_Mode5_Value;
    Auto_Speed_Mode_Value[7][5] = ui->Auto_Speed8_Mode6_Value;
    Auto_Speed_Mode_Value[7][6] = ui->Auto_Speed8_Mode7_Value;
    Auto_Speed_Mode_Value[7][7] = ui->Auto_Speed8_Mode8_Value;

    // 初始化12路温度控件数组（Auto_Tem1~Auto_Tem12_Value）
    Auto_Tem_Value[0] = ui->Auto_Tem1_Now;
    Auto_Tem_Value[1] = ui->Auto_Tem2_Now;
    Auto_Tem_Value[2] = ui->Auto_Tem3_Now;
    Auto_Tem_Value[3] = ui->Auto_Tem4_Now;
    Auto_Tem_Value[4] = ui->Auto_Tem5_Now;
    Auto_Tem_Value[5] = ui->Auto_Tem6_Now;
    Auto_Tem_Value[6] = ui->Auto_Tem7_Now;
    Auto_Tem_Value[7] = ui->Auto_Tem8_Now;
    Auto_Tem_Value[8] = ui->Auto_Tem9_Now;
    Auto_Tem_Value[9] = ui->Auto_Tem10_Now;
    Auto_Tem_Value[10] = ui->Auto_Tem11_Now;
    Auto_Tem_Value[11] = ui->Auto_Tem12_Now;
    Auto_Tem_Value[12] = ui->Auto_NowTem;
    //初始化温度状态
    Auto_Tem_Status[0]  = ui->Auto_Tem1;
    Auto_Tem_Status[1]  = ui->Auto_Tem2;
    Auto_Tem_Status[2]  = ui->Auto_Tem3;
    Auto_Tem_Status[3]  = ui->Auto_Tem4;
    Auto_Tem_Status[4]  = ui->Auto_Tem5;
    Auto_Tem_Status[5]  = ui->Auto_Tem6;
    Auto_Tem_Status[6]  = ui->Auto_Tem7;
    Auto_Tem_Status[7]  = ui->Auto_Tem8;
    Auto_Tem_Status[8]  = ui->Auto_Tem9;
    Auto_Tem_Status[9]  = ui->Auto_Tem10;
    Auto_Tem_Status[10] = ui->Auto_Tem11;
    Auto_Tem_Status[11] = ui->Auto_Tem12;
    Auto_Tem_Status[12] = ui->Auto_Tem13;

}

/*
* @description 界面数据显示槽函数
* @param { } 无
* @returns {void} 无
* @date 2025-10-28 11:51:00
* @author zh
*/
void MainWindow::Slot_ShowUI_Data()
{
    //PT电机
    //    bool motor_pt_show_flag = true;
    //    if(motor_pt_show_flag){

    //    }
    if(check_time_flag){


        check_time++;
        ui->Auto_CheckTime->setValue(QString::number(check_time/10.0,'f',1).toFloat());//检测时间
    }

    for(int i = 1 ;i <= 8;i++){

        showFuncUIData(i);
    }

    //LIN电机

    //鼓风机

    //温敏电阻

    //其他


}


//#define FUNC_PT_ID      1
//#define FUNC_LIN_ID     2
//#define FUNC_BLO_ID     3
//#define FUNC_THE_ID     4
//#define FUNC_ANION_ID   5
//#define FUNC_AQS_ID     6
//#define RUNC_PM25_ID    7
//#define RUNC_PTC_ID     8
/*
* @description 分功能界面数据显示
* @param {uchar} _num 功能ID
* @returns {void} 无
* @date 2025-10-28 14:03:00
* @author zh
*/
void MainWindow::showFuncUIData(uchar _num){
    switch (_num) {
    case FUNC_PT_ID:{

        //读取PT
        QList<PTMotorFP_Status_basis> Now_data = Nthread_ptmotor->reLinRealTimeData();

        for(int i = 0 ;i < 12;i++){

            for(int j = 0 ;j < 8;j++){
                m_FormMotor[i]->slot_PTSendMotorStatus("1",1,1,Now_data[i].Current_V,Now_data[i].Current_A, j + 1, Now_data[i].POSStatus[j],Now_data[i].POS_V[j],Now_data[i].POS_A[j],Now_data[i].m_type[j]);
            }

            //Now_data[i].m_TotalResult 0:  1:OK  2: NG
            //Now_data[i].m_TotalStatus  0: 停止 1：运行
            m_FormMotor[i]->slot_setled(true, 0, Now_data[i].m_TotalResult,Now_data[i].m_TotalStatus);

        }

        break;}
    case FUNC_LIN_ID:{
        LINMotor_Return linreturn;
        QList<LINMotor_Return> LinNowData;//读取电机实时数据
        for(int x = 0;x < LINMotor_Count; x++)
            LinNowData.insert(x, linreturn);

        LinNowData = Nthread_linmotor->reLinRealTimeData();

        for(int i = 0 ;i < 12;i++){

            for(int j = 0 ;j < 8;j++){
                m_FormLinMotor[i]->slot_SendMotorStatus("1",1,1,LinNowData[i].CurrentStep,0, j + 1 ,LinNowData[i].m_ProcessStatus[j],LinNowData[i].m_ProcessStep[j],0);//0:未运行 1：运行 2:OK 3:NG
            }
            m_FormLinMotor[i]->slot_setled(true, 0, LinNowData[i].m_TotalResult, LinNowData[i].m_TotalStatus);//0:停止 1：运行
        }
        LinNowData.clear();
        break;
    }

    case FUNC_BLO_ID:{


        MS_DisplayDatas msDisplayDatas;
        msDisplayDatas = m_Blower->reLinRealTimeData();
        for(int i = 0 ;i < msDisplayDatas.v_PosResult_Blower.size();i++){

            Auto_Blower_button[i]->setText(QString::number(msDisplayDatas.v_PosSteps_Blower.at(i)) + "档");//档位显示
            ui->led_BlowerError->setText(msDisplayDatas.errorCode_fun30);
            ui->Auto_Blower_Now_A_2->setValue(msDisplayDatas.v_BlowerRealCurr_YJ);
            ui->Auto_Blower->setStyleSheet(Button_blower_background_color(msDisplayDatas.v_allPosResult_blower));
            Auto_Blower_button[i]->setStyleSheet(Button_blower_background_color(msDisplayDatas.v_PosResult_Blower.at(i)));


            ui->Auto_Vibration_X->setStyleSheet(Button_blower_background_color(msDisplayDatas.v_allPosResult_VibrationX));
            //                    Auto_Vibration_x[i]->setStyleSheet(setled_Vibration(msDisplayDatas.v_PosResult_VibrationX.at(i)));
            Auto_Vibration_x[i]->setValue(QString::number(msDisplayDatas.v_Datas_VibrationX[i] /1.0,'f',3).toFloat());

            ui->Auto_Vibration_Y->setStyleSheet(Button_blower_background_color(msDisplayDatas.v_allPosResult_VibrationY));
            //                    Auto_Vibration_y[i]->setStyleSheet(setled_Vibration(msDisplayDatas.v_PosResult_VibrationY.at(i)));
            Auto_Vibration_y[i]->setValue(QString::number(msDisplayDatas.v_Datas_VibrationY[i] /1.0,'f',3).toFloat());

            ui->Auto_Vibration_Z->setStyleSheet(Button_blower_background_color(msDisplayDatas.v_allPosResult_VibrationZ));
            //                    Auto_Vibration_z[i]->setStyleSheet(setled_Vibration(msDisplayDatas.v_PosResult_VibrationZ.at(i)));
            Auto_Vibration_z[i]->setValue(QString::number(msDisplayDatas.v_Datas_VibrationZ[i] /1.0,'f',3).toFloat());

            ui->Auto_Noises->setStyleSheet(Button_blower_background_color(msDisplayDatas.v_allPosResult_Noise));
            //                    Auto_Noises_Value[i]->setStyleSheet(setled_Vibration(msDisplayDatas.v_PosResult_Noise.at(i)));
            Auto_Noises_Value[i]->setValue(QString::number(msDisplayDatas.v_Datas_Noise[i] /1.0,'f',1).toFloat());

            Auto_Blower_Value[i]->setValue(QString::number(msDisplayDatas.v_PosCurrs_Blower[i] /1.0, 'f',1).toFloat());
            Auto_Blower_set_Value[i]->setValue(QString::number(msDisplayDatas.v_PosSpeed_Blower[i]).toUInt());

            ui->doubleSpinBox_29->setValue(msDisplayDatas.v_BlowerRealVlot);
            ui->Auto_Blower_Now_A->setValue(msDisplayDatas.v_BlowerRealCurr);
            ui->Auto_Blower_Now_V->setValue(msDisplayDatas.v_BlowerRealSpeed);
        }
        break;
    }
    case FUNC_THE_ID:{
        Thermistor_Status_basis thermistorreturn;
        thermistorreturn = Nthread_Thermistor->reLinRealTimeData();

        //       int borad_num = 0;
        //       int i_num = 0;

        for(int i = 0 ;i < 13;i++){

            //            if((i%4 == 0) && i != 0)
            //            {
            //               borad_num++;
            //               i_num = 0;
            //            }
            Auto_Tem_Status[i]->setStyleSheet(Button_blower_background_color(thermistorreturn.m_SingleStatus[i]));

            Auto_Tem_Value[i]->setValue(QString::number(thermistorreturn.m_Temperature[i]/1.0,'f',1).toFloat());
            //            i_num ++;
        }
        break;
    }
    case FUNC_ANION_ID:{
        Anion_Status_basis anionstatusreturn;
        anionstatusreturn = Nthread_Thermistor->reAnionRealTimeData();
        break;
    }
    case FUNC_AQS_ID:{
        break;
    }
    case RUNC_PM25_ID:{
        break;
    }
    case RUNC_PTC_ID:{
        break;
    }
    default:{

        break;
    }


    }
}
/*
* @description 分功能界面数据显示
* @param {uchar} _num 功能ID
* @returns {void} 无
* @date 2025-10-28 14:03:00
* @author zh
*/
void MainWindow::Slot_ShowUI_Results(uchar _num){
    if(_num==0)//最终检测结果
    {
        ui->Auto_results->setText("");
        ui->Auto_results->setStyleSheet("");
    }
    else if(_num==1)
    {
        check_time_Stop();
        ui->Auto_results->setText("OK");
        ui->Auto_results->setStyleSheet(Button_background_color(1));
    }
    else if(_num==2)
    {
        check_time_Stop();
        ui->Auto_results->setText("NG");
        ui->Auto_results->setStyleSheet(Button_background_color(3));
    }
    else if(_num==3)
    {
        ui->Auto_results->setText("RUN");
        ui->Auto_results->setStyleSheet(Button_background_color(2));
    }
    else if(_num==4)
    {
        check_time_Stop();
        ui->Auto_results->setText("STOP");
        ui->Auto_results->setStyleSheet(Button_background_color(3));
    }
}
/*
* @description 分功能界面数据显示
* @param {uchar} _num 功能ID
* @returns {void} 无
* @date 2025-10-28 14:03:00
* @author zh
*/
void MainWindow::check_time_Start()
{
    check_time = 0;
    check_time_flag = true;
}
/*
* @description 分功能界面数据显示
* @param {uchar} _num 功能ID
* @returns {void} 无
* @date 2025-10-28 14:03:00
* @author zh
*/
void MainWindow::check_time_Stop()
{
    check_time_flag = false;
}
/*
* @description 分功能界面数据显示
* @param {uchar} _num 功能ID
* @returns {void} 无
* @date 2025-10-28 14:03:00
* @author zh
*/
void MainWindow::Slot_ShowUI_Step(int _num){
    ui->Auto_RunSteps->setText(QString::number(_num));//步骤
}



void MainWindow::on_Auto_PDbox_currentIndexChanged(int index)
{

}

void MainWindow::on_actionModbus_triggered()
{
    m_Form_ModeBusRtu->show();
}

void MainWindow::on_actionstart_blower_triggered()
{
    m_Blower->slot_BlowerStop();
}

void MainWindow::on_actioncontinue_blower_triggered()
{
    m_Blower->slot_BlowerContinue();
}

void MainWindow::on_actionctr_relay_on_triggered()
{
    m_Blower->Send_RelayControl(1);
}

void MainWindow::on_actionctr_relay_off_triggered()
{

    m_Blower->Send_RelayControl(0);
}

