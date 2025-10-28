#ifndef FORMLOGSHOW_H
#define FORMLOGSHOW_H

#include <QWidget>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QSpinBox>
#include <QTextStream>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QTextBrowser>
#include <QObject>
#include <QMutex>

#include <QScrollBar>

namespace Ui {
class FormLogShow;
}

class FormLogShow : public QWidget
{
    Q_OBJECT

public:
    explicit FormLogShow(QWidget *parent = nullptr);
    ~FormLogShow();

    static FormLogShow* getInstance();

    void applyFilters();

private slots:
    void on_applyFilterButton_clicked();

    void updateActiveDateTimeEdit();

    void on_exportButton_clicked();

    void on_clearButton_clicked();

    void on_showAllButton_clicked();

public slots:
    void addLog(const QString &level, const QString &content);

private:
    static QMutex m_instanceMutex;      // 单例创建的互斥锁

    bool m_autoScroll = true;       // 自动滚动标志
    QTimer *m_scrollTimer = nullptr; // 延迟滚动定时器
    QMutex m_scrollMutex;           // 滚动操作互斥锁

    Ui::FormLogShow *ui;


    struct LogEntry {
            QString level;
            QDateTime timestamp;
            QString content;
            QString rawText;
            QString htmlText;
        };

     QList<LogEntry> allLogs;      // 存储所有日志
     QList<LogEntry> filteredLogs; // 存储筛选后的日志

     void showAllLogs();

     // 清空日志
    void clearLogs();

    // 导出日志
     void exportLogs();

     void limitLogLines(QTextBrowser* browser, int maxLines);
};

extern FormLogShow * NFormLogShow;

#endif // FORMLOGSHOW_H
