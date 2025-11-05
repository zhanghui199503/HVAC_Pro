//#include "Formdialogalarmdialog.h"
//#include "ui_Formdialogalarmdialog.h"




//FormDialogAlarmDialog::FormDialogAlarmDialog(const QString &alarmInfo, QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::FormDialogAlarmDialog), // UI实例类名同步修改
//    m_borderOpacity(255),
//    m_isFlashIncreasing(false) {
//    ui->setupUi(this);

//    // 窗口基础设置
//    setWindowTitle("紧急报警");
//    setFixedSize(400, 200);
//    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
//    setStyleSheet("background-color: rgb(255, 0, 0);"); // 全红背景

//    // 报警信息设置
//    ui->alarmInfoLabel->setText(alarmInfo);
//    ui->alarmInfoLabel->setStyleSheet("color: white; font-size: 14pt; font-weight: bold;");
//    ui->alarmInfoLabel->setAlignment(Qt::AlignCenter);

//    // 边框闪烁定时器
//    m_flashTimer = new QTimer(this);
//    m_flashTimer->setInterval(200);
//    connect(m_flashTimer, &QTimer::timeout, this, &FormDialogAlarmDialog::on_flashTimer_timeout);
//    m_flashTimer->start();

//    // 背景呼吸动画
//    m_bgAnim = new QPropertyAnimation(this, "bgColor");
//    m_bgAnim->setDuration(800);
//    m_bgAnim->setStartValue("rgb(255, 50, 50)");
//    m_bgAnim->setEndValue("rgb(255, 0, 0)");
//    m_bgAnim->setLoopCount(-1);
//    m_bgAnim->start();
//}

//FormDialogAlarmDialog::~FormDialogAlarmDialog() {
//    delete ui;
//}

//int FormDialogAlarmDialog::borderOpacity() const {
//    return m_borderOpacity;
//}

//void FormDialogAlarmDialog::setBorderOpacity(int opacity) {
//    m_borderOpacity = opacity;
//    update();
//}

//QString FormDialogAlarmDialog::bgColor() const {
//    return styleSheet().split(":").last().trimmed();
//}

//void FormDialogAlarmDialog::setBgColor(const QString &color) {
//    setStyleSheet(QString("background-color: %1;").arg(color));
//}

//void FormDialogAlarmDialog::on_flashTimer_timeout() {
//    if (m_isFlashIncreasing) {
//        m_borderOpacity += 20;
//        if (m_borderOpacity >= 255) {
//            m_borderOpacity = 255;
//            m_isFlashIncreasing = false;
//        }
//    } else {
//        m_borderOpacity -= 20;
//        if (m_borderOpacity <= 50) {
//            m_borderOpacity = 50;
//            m_isFlashIncreasing = true;
//        }
//    }
//    setBorderOpacity(m_borderOpacity);
//}

//void FormDialogAlarmDialog::on_confirmBtn_clicked() {
//    m_flashTimer->stop();
//    m_bgAnim->stop();
//    accept();
//}

//void FormDialogAlarmDialog::paintEvent(QPaintEvent *event) {
//    QDialog::paintEvent(event);
//    QPainter painter(this);

//    // 绘制外层闪烁边框
//    QPen borderPen(QColor(255, 0, 0, m_borderOpacity), 8);
//    painter.setPen(borderPen);
//    painter.drawRect(-2, -2, width() + 4, height() + 4);

//    // 绘制内层细边框
//    QPen innerPen(QColor(255, 200, 200), 2);
//    painter.setPen(innerPen);
//    painter.drawRect(0, 0, width() - 1, height() - 1);
//}

////FormDialogAlarmDialog::FormDialogAlarmDialog(const QString &alarmInfo,QWidget *parent) :

////    QDialog(parent),
////    ui(new Ui::FormDialogAlarmDialog),
////    m_borderWidth(2),
////    m_isFlashOn(true),
////    m_shakeOffset(0),
////    m_shakeDirection(true)
////{
////    ui->setupUi(this);

////    // 窗口基础设置
////        setWindowTitle("紧急报警");
////        setFixedSize(400, 200); // 固定大小
////        setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint); // 置顶显示
////        ui->alarmInfoLabel->setText(alarmInfo); // 设置报警信息

////        // 1. 闪烁定时器（控制边框闪烁）
////        m_flashTimer = new QTimer(this);
////        m_flashTimer->setInterval(300); // 300ms闪烁一次
////        connect(m_flashTimer, &QTimer::timeout, this, &FormDialogAlarmDialog::on_flashTimer_timeout);
////        m_flashTimer->start();

////        // 2. 抖动定时器（窗口左右抖动）
////        m_shakeTimer = new QTimer(this);
////        m_shakeTimer->setInterval(50); // 50ms抖动一次
////        connect(m_shakeTimer, &QTimer::timeout, this, &FormDialogAlarmDialog::on_shakeTimer_timeout);
////        m_shakeTimer->start();

////        // 3. 背景渐变动画（红色背景呼吸效果）
////        m_bgAnim = new QPropertyAnimation(this, "styleSheet");
////        m_bgAnim->setDuration(1000); // 1秒一个周期
////        m_bgAnim->setStartValue("background-color: rgb(255, 200, 200);"); // 浅红
////        m_bgAnim->setEndValue("background-color: rgb(255, 50, 50);");    // 深红
////        m_bgAnim->setLoopCount(-1); // 无限循环
////        m_bgAnim->start();
////}

////FormDialogAlarmDialog::~FormDialogAlarmDialog()
////{
////    delete ui;
////}

////// 边框宽度属性（用于动画）
////int FormDialogAlarmDialog::borderWidth() const {
////    return m_borderWidth;
////}

////void FormDialogAlarmDialog::setBorderWidth(int width) {
////    m_borderWidth = width;
////    update(); // 触发重绘
////}

////// 闪烁动画：控制边框宽度变化
////void FormDialogAlarmDialog::on_flashTimer_timeout() {
////    m_isFlashOn = !m_isFlashOn;
////    setBorderWidth(m_isFlashOn ? 6 : 2); // 闪烁时边框变宽
////}

////// 抖动动画：窗口左右小幅抖动
////void FormDialogAlarmDialog::on_shakeTimer_timeout() {
////    const int maxOffset = 10; // 最大抖动偏移量
////    if (m_shakeDirection) {
////        m_shakeOffset++;
////        if (m_shakeOffset >= maxOffset) m_shakeDirection = false;
////    } else {
////        m_shakeOffset--;
////        if (m_shakeOffset <= -maxOffset) m_shakeDirection = true;
////    }
////    // 移动窗口实现抖动效果
////    move(x() + m_shakeOffset, y());
////}

////// 确认按钮：关闭报警窗口
////void FormDialogAlarmDialog::on_confirmBtn_clicked() {
////    m_flashTimer->stop();
////    m_shakeTimer->stop();
////    m_bgAnim->stop();
////    accept(); // 关闭窗口
////}

////// 重绘事件：绘制动态边框
////void FormDialogAlarmDialog::paintEvent(QPaintEvent *event) {
////    QDialog::paintEvent(event);
////    QPainter painter(this);
////    painter.setPen(QPen(QColor(255, 0, 0), m_borderWidth)); // 红色边框
////    painter.drawRect(0, 0, width() - 1, height() - 1); // 绘制边框（留1px避免超出）
////}


//111111111
// formdialogalarmdialog.cpp
#include "formdialogalarmdialog.h"
#include "ui_formdialogalarmdialog.h"
#include <QPainter>
#include <QFont>
#include <QScreen>
#include <QGuiApplication>
#include <QKeyEvent>

FormDialogAlarmDialog::FormDialogAlarmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormDialogAlarmDialog),
    m_flashTimer(new QTimer(this))
{
    ui->setupUi(this);

    // 窗口设置
    setWindowTitle("系统报警");
    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    // 取消半透明背景，改用绘制方式控制颜色，避免影响按钮
    setAttribute(Qt::WA_TranslucentBackground, false);

    // 调整窗口大小和位置
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen) {
        QRect screenRect = screen->geometry();
        int w = screenRect.width() * 2 / 8;
        int h = screenRect.height() * 2 / 8;
        setGeometry(
            (screenRect.width() - w) / 2,
            (screenRect.height() - h) / 2,
            w, h
        );
    }

    // 初始化颜色（使用不同强度的红色实现闪烁）
    m_highColor = QColor(255, 0, 0);      // 亮红色
    m_lowColor = QColor(180, 0, 0);       // 暗红色

    // 初始化UI样式
    //ui->titleLabel->setStyleSheet("color: white; font-weight: bold;");
    ui->alarmInfoLabel->setStyleSheet("color: white;");
    ui->confirmBtn->setStyleSheet(
        "QPushButton {"
        "   background-color: white;"
        "   color: red;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   border-radius: 8px;"
        "   padding: 10px 30px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #f0f0f0;"
        "   border: 2px solid #ff6666;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #eeeeee;"
        "}"
    );

    // 设置字体大小
//    QFont titleFont = ui->titleLabel->font();
//    titleFont.setPointSize(36);
//    ui->titleLabel->setFont(titleFont);

    QFont msgFont = ui->alarmInfoLabel->font();
    msgFont.setPointSize(24);
    ui->alarmInfoLabel->setFont(msgFont);

    // 定时器设置（控制闪烁频率）
    m_flashTimer->setInterval(300);  // 300ms一次闪烁
    connect(m_flashTimer, &QTimer::timeout, this, &FormDialogAlarmDialog::onFlashTimerTimeout);
    m_flashTimer->start();

    // 连接关闭按钮信号（显式连接，确保不会遗漏）
    connect(ui->confirmBtn, &QPushButton::clicked, this, &FormDialogAlarmDialog::on_closeButton_clicked);

    // 默认报警信息
    setAlarmInfo("⚠️ 紧急报警 ⚠️", "系统检测到异常，请立即处理！");
}

FormDialogAlarmDialog::~FormDialogAlarmDialog()
{
    delete ui;
}

void FormDialogAlarmDialog::setAlarmInfo(const QString &title, const QString &message)
{
    //ui->titleLabel->setText(title);
    ui->alarmInfoLabel->setText(message);
}

void FormDialogAlarmDialog::onFlashTimerTimeout()
{
    // 切换颜色强度实现闪烁效果
    m_isHighIntensity = !m_isHighIntensity;
    update();  // 触发重绘
}

void FormDialogAlarmDialog::on_closeButton_clicked()
{
    close();
}

void FormDialogAlarmDialog::paintEvent(QPaintEvent *event)
{
    // 绘制背景（根据状态切换颜色）
    QPainter painter(this);
    painter.fillRect(rect(), m_isHighIntensity ? m_highColor : m_lowColor);

    // 调用父类paintEvent确保子控件正常绘制
    QDialog::paintEvent(event);
}

void FormDialogAlarmDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();
    }
    QDialog::keyPressEvent(event);
}
