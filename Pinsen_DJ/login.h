#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "Header_File.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    Ui::Login *ui;
    int Login_flag = 0;
public slots:
    void Login_Init();
private slots:
    void on_Btn_Login_clicked();

    void on_revise_Password_clicked();

    void on_Goback_Login_clicked();

    void on_Confirm_changes_clicked();

    void slot_Find_Account(const QString user, const QString password);//查找用户等级

private:

signals:
    void Sign_GoMain(int Main_flag);//发送启动检测
    void sign_Login_Info(QString index,QString index2);
};
extern Login *Login_Main;

#endif // LOGIN_H
