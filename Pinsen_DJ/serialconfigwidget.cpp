#include "serialconfigwidget.h"
#include "ui_serialconfigwidget.h"

#include <QSerialPortInfo>
#include <QMessageBox>

SerialConfigWidget::SerialConfigWidget(int index, QWidget *parent)
    : QWidget(parent), ui(new Ui::SerialConfigWidget), m_index(index), m_serialPort(nullptr)
{
    ui->setupUi(this);

    // 设置组标题
    ui->groupBox->setTitle(QString("串口 %1").arg(index));

    // 创建状态指示灯
//    m_statusIndicator = new StatusIndicator(this);
//    ui->horizontalLayout->addWidget(m_statusIndicator);

    // 初始化端口列表
    updateAvailablePorts();

    // 初始化波特率列表
    ui->baudRateCombo->addItem("9600", QSerialPort::Baud9600);
    ui->baudRateCombo->addItem("19200", QSerialPort::Baud19200);
    ui->baudRateCombo->addItem("38400", QSerialPort::Baud38400);
    ui->baudRateCombo->addItem("57600", QSerialPort::Baud57600);
    ui->baudRateCombo->addItem("115200", QSerialPort::Baud115200);
    ui->baudRateCombo->setCurrentIndex(4); // 默认115200

    // 连接信号槽
    connect(ui->connectButton, &QPushButton::clicked, this, &SerialConfigWidget::toggleConnection);
    connect(ui->refreshButton, &QPushButton::clicked, this, &SerialConfigWidget::updateAvailablePorts);
}

SerialConfigWidget::~SerialConfigWidget()
{
    if (m_serialPort && m_serialPort->isOpen()) {
        m_serialPort->close();
    }
    delete m_serialPort;
    delete ui;
}

bool SerialConfigWidget::isConnected() const
{
    return m_serialPort && m_serialPort->isOpen();
}

QString SerialConfigWidget::portName() const
{
    return ui->portCombo->currentText();
}

qint32 SerialConfigWidget::baudRate() const
{
    return ui->baudRateCombo->currentData().toInt();
}

void SerialConfigWidget::toggleConnection()
{
    if (isConnected()) {
        // 断开连接
        m_serialPort->close();
        delete m_serialPort;
        m_serialPort = nullptr;

//        m_statusIndicator->setConnected(false);
        ui->connectButton->setText("连接");
        emit connectionChanged(m_index, false);
    } else {
        // 尝试连接
//        m_serialPort = new QSerialPort(this);
        m_serialPort->setPortName(ui->portCombo->currentText());
        m_serialPort->setBaudRate(baudRate());
        m_serialPort->setDataBits(QSerialPort::Data8);
        m_serialPort->setParity(QSerialPort::NoParity);
        m_serialPort->setStopBits(QSerialPort::OneStop);
        m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

        if (m_serialPort->open(QIODevice::ReadWrite)) {
//            m_statusIndicator->setConnected(true);
            ui->connectButton->setText("断开");
            emit connectionChanged(m_index, true);
        } else {
            QMessageBox::about(this, "错误", QString("无法打开串口: %1").arg(m_serialPort->errorString()));
            delete m_serialPort;
            m_serialPort = nullptr;
        }
    }
}

void SerialConfigWidget::updateAvailablePorts()
{
    QString current = ui->portCombo->currentText();
    ui->portCombo->clear();

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->portCombo->addItem(info.portName());
    }

    // 尝试恢复之前的选择
    int index = ui->portCombo->findText(current);
    if (index != -1) {
        ui->portCombo->setCurrentIndex(index);
    }
}
