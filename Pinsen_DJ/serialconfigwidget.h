#ifndef SERIALCONFIGWIDGET_H
#define SERIALCONFIGWIDGET_H

#include <QWidget>
#include <QSerialPort>
//#include "statusindicator.h"

namespace Ui {
class SerialConfigWidget;
}

class SerialConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerialConfigWidget(int index, QWidget *parent = nullptr);
    ~SerialConfigWidget();

    bool isConnected() const;
    QString portName() const;
    qint32 baudRate() const;

signals:
    void connectionChanged(int index, bool connected);

public slots:
    void toggleConnection();
    void updateAvailablePorts();

private:
    Ui::SerialConfigWidget *ui;
    int m_index;
    QSerialPort *m_serialPort;
//    StatusIndicator *m_statusIndicator;
};

#endif // SERIALCONFIGWIDGET_H
