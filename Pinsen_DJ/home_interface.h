#ifndef HOME_INTERFACE_H
#define HOME_INTERFACE_H

#include <QWidget>
#include "Header_File.h"

namespace Ui {
class Home_interface;
}

class Home_interface : public QWidget
{
    Q_OBJECT

public:
    explicit Home_interface(QWidget *parent = nullptr);
    ~Home_interface();
    Ui::Home_interface *ui;

public slots:
    void Slot_Init();//界面初始化

    void Slot_Goback();//返回
    void Slot_GoMainwindow(int index);//进入主界面
private slots:
    void on_Btn_Enter_updateChannelsName_clicked();

    void on_Btn_EnterWork_clicked();

protected:
    void closeEvent(QCloseEvent *event);

private:

};
//extern Home_interface *interfaceMain;
#endif // HOME_INTERFACE_H
