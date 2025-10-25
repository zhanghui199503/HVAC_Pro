#ifndef THREAD_MAIN_H
#define THREAD_MAIN_H

#include "Header_File.h"
#include <QObject>

class thread_main : public QThread
{
    Q_OBJECT
public:
    explicit thread_main(QObject *parent = 0);
    ~thread_main();
    void threadPause();
    void threadResume();

    bool st = false;

    QElapsedTimer  R_Rfid_timer;

protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start（）间接调用
    void run();

signals:
    void isDone();

    void addLog(const QString &level, const QString &content);

public slots:

    void test();


private:
    bool m_buttonState; //if pause m_buttonState=false;else m_buttonState=true;
    QMutex m_mutex;//互斥量



};

extern thread_main * Nthread_main;

#endif // THREAD_MAIN_H
