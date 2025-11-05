//#ifndef FORMDIALOGALARMDIALOG_H
//#define FORMDIALOGALARMDIALOG_H

//#include <QDialog>
//#include <QTimer>
//#include <QPropertyAnimation>
//#include <QPainter>
//#include <QPen>
//#include <QColor>

//namespace Ui {
//class FormDialogAlarmDialog;
//}

//class FormDialogAlarmDialog : public QDialog { // 类名修改为FormDialogAlarmDialog
//    Q_OBJECT
//    Q_PROPERTY(int borderOpacity READ borderOpacity WRITE setBorderOpacity)
//    Q_PROPERTY(QString bgColor READ bgColor WRITE setBgColor)

//public:
//    explicit FormDialogAlarmDialog(const QString &alarmInfo, QWidget *parent = nullptr);
//    ~FormDialogAlarmDialog();

//    int borderOpacity() const;
//    void setBorderOpacity(int opacity);
//    QString bgColor() const;
//    void setBgColor(const QString &color);

//private slots:
//    void on_flashTimer_timeout();
//    void on_confirmBtn_clicked();

//private:
//    Ui::FormDialogAlarmDialog *ui; // UI指针类名同步修改
//    QTimer *m_flashTimer;
//    QPropertyAnimation *m_bgAnim;
//    int m_borderOpacity;
//    bool m_isFlashIncreasing;
//protected:
//    void paintEvent(QPaintEvent *event) override;
//};

////class FormDialogAlarmDialog : public QDialog
////{
////    Q_OBJECT
////    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth) // 边框宽度动画属性

////public:
////    explicit FormDialogAlarmDialog(const QString &alarmInfo,QWidget *parent = nullptr);
////    ~FormDialogAlarmDialog();

////    int borderWidth() const;
////    void setBorderWidth(int width);

////private slots:
////    void on_flashTimer_timeout();     // 闪烁动画
////    void on_shakeTimer_timeout();     // 抖动动画
////    void on_confirmBtn_clicked();     // 确认按钮

////private:
////    Ui::FormDialogAlarmDialog *ui;
////    QTimer *m_flashTimer;             // 闪烁定时器
////    QTimer *m_shakeTimer;             // 抖动定时器
////    QPropertyAnimation *m_bgAnim;     // 背景渐变动画
////    int m_borderWidth;                // 边框宽度（用于动画）
////    bool m_isFlashOn;                 // 闪烁状态标记
////    int m_shakeOffset;                // 抖动偏移量
////    bool m_shakeDirection;            // 抖动方向

////protected:
////    void paintEvent(QPaintEvent *event) override;
////};

//#endif // FORMDIALOGALARMDIALOG_H


// formdialogalarmdialog.h
#ifndef FORMDIALOGALARMDIALOG_H
#define FORMDIALOGALARMDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QPaintEvent>
#include <QKeyEvent>

namespace Ui {
class FormDialogAlarmDialog;
}

class FormDialogAlarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormDialogAlarmDialog(QWidget *parent = nullptr);
    ~FormDialogAlarmDialog();

    // 设置报警信息
    void setAlarmInfo(const QString &title, const QString &message);

private slots:
    // 闪烁控制槽函数
    void onFlashTimerTimeout();
    // 关闭按钮槽函数
    void on_closeButton_clicked();

protected:
    // 重绘事件（绘制红色背景）
    void paintEvent(QPaintEvent *event) override;
    // 按键事件（支持ESC关闭）
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::FormDialogAlarmDialog *ui;
    QTimer *m_flashTimer;    // 闪烁定时器
    bool m_isHighIntensity;  // 控制颜色强度
    bool m_isHighOpacity;    // 透明度状态标记
    double m_highOpacity;    // 高透明度值
    double m_lowOpacity;     // 低透明度值
    QColor m_highColor;      // 高亮红色
    QColor m_lowColor;       // 低亮红色

};

#endif // FORMDIALOGALARMDIALOG_H
