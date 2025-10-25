#ifndef MFORMMOTOR_H
#define MFORMMOTOR_H

#include <QGroupBox>
#include <QPushButton>
#include <QSettings>
#include <QTextCodec>


namespace Ui {
class MFormMotor;
}

class MFormMotor : public QGroupBox
{
    Q_OBJECT

public:
    explicit MFormMotor(QWidget *parent = nullptr,
                        QString title_name="###",
                        const uchar motor_name=EM::PT,
                        const uchar motor_index=1,
                        const uchar small_Board_MotorID=1,
                        const uchar big_Board_MotorID=1
            );
    ~MFormMotor();

    QString _titleName = "###";
    uchar _v_motorName = EM::PT;    //电机类型
    uchar _v_motorIndex = 1;        //控件名字 INI索引
    uchar _v_smallBoardMotorID = 1; //小板电机号ID
    uchar _v_bigBoardMotorID = 1;//大板ID

    float v_maxValue[8] = {0.0};    //上限
    float v_minValue[8] = {0.0};    //下限

    QList<QPushButton*> list_BTN_POS;

    void Init_OBJS();
    void load_FileINI(const QString &path_name, const QString channel);

public slots:
    void slot_setled(bool b_motorClass, const uchar pos_index, const uchar state);
    void slot_clearLED();
    void slot_SendMotorStatus(QString Modeltype, int ID, int MotorNum, int CurrentV, int CurrentA, int CurrentPos, int CurrentState);
private:
    Ui::MFormMotor *ui;

    enum EM{
        PT,
        LIN,
    };
};

#endif // MFORMMOTOR_H
