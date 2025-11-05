#include "FormLogShow.h"
#include "ui_FormLogShow.h"
FormLogShow * NFormLogShow;

QMutex FormLogShow::m_instanceMutex; // 关键：类外定义，分配内存

QList<QString> level_name = {"全部级别", "故障", "警告", "主窗口", "主流程", "消费线程"};
QList<QString> Str_Color = {
    "color:red",        // 红色
    /*"color:yellow", */     // 黄色
    "color:fuchsia",    // 紫红色
    "color:blue",       // 蓝色
    "color:green",     // 绿色
    "color:navy",       // 深蓝色
    "color:orange",     // 橙色
    "color:purple",     // 紫色
    /*"color:pink",*/       // 粉色
    "color:brown",      // 棕色
    "color:black",      // 黑色
    /*"color:white",*/      // 白色
    "color:gray",       // 灰色
    "color:silver",     // 银灰色
    "color:gold",       // 金色
    "color:teal",       // 青绿色
    "color:maroon",     // 褐红色
    "color:olive",      // 橄榄色
    "color:lime",       // 酸橙色
    "color:aqua",       // 浅绿色
    "color:indigo",     // 靛蓝色
    "color:violet",     // 紫罗兰色
    "color:coral",      // 珊瑚色
    "color:crimson",    // 深红色
    "color:cyan",       // 青色
    /*"color:khaki",*/      // 卡其色
    /*"color:lavender",*/  // 淡紫色
    "color:magenta",    // 品红色
    "color:salmon",     // 鲑鱼色
    "color:skyblue",    // 天蓝色
    "color:tan",        // 棕褐色
    /*"color:wheat"*/       // 小麦色
};

FormLogShow::FormLogShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLogShow)
{
    ui->setupUi(this);

    this->setWindowTitle("日志信息");

    ui->logTextBrowser->setVisible(false);

//    QThread *cmd_thread = new QThread;
//    this->moveToThread(cmd_thread);
//    cmd_thread->start();

    ui->levelComboBox->addItems(level_name);

    ui->startTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->startTimeEdit->setDateTime(QDateTime::currentDateTime().addDays(-1));

    ui->endTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->endTimeEdit->setDateTime(QDateTime::currentDateTime());

    // 定时器用于检测当前活动的DateTimeEdit
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FormLogShow::updateActiveDateTimeEdit);
    //timer->start(100); // 每100ms检查一次

    ui->plainTextEdit->setMaximumBlockCount(5000); // 自动限制最多1000行


}

FormLogShow::~FormLogShow()
{
    delete ui;
}

FormLogShow* FormLogShow::getInstance()
{
    // 双重检查锁定（提高效率，避免每次获取实例都加锁）
    if (!NFormLogShow) {
        QMutexLocker locker(&m_instanceMutex);  // 加锁确保线程安全
        if (!NFormLogShow) {
            NFormLogShow = new FormLogShow();
        }
    }
    return NFormLogShow;
}

void FormLogShow::addLog(const QString &level, const QString &content) {
    static long count = 0;

    QDateTime timestamp = QDateTime::currentDateTime();
    QString timestampStr = QString::number (count++) + "." + timestamp.toString("yyyy-MM-dd HH:mm:ss");

    LogEntry entry;
    entry.level = level;
    entry.timestamp = timestamp;
    entry.content = content;
    entry.rawText = QString("[%1] [%2] %3").arg(timestampStr, level, content);

    // 根据日志级别设置HTML样式
//    if (level == "ERROR") {
//        entry.htmlText = QString("<p style=\"color:red;\">%1</p>").arg(entry.rawText.toHtmlEscaped());
//    } else if (level == "WARNING") {
//        entry.htmlText = QString("<p style=\"color:orange;\">%1</p>").arg(entry.rawText.toHtmlEscaped());
//    } else if (level == "INFO") {
//        entry.htmlText = QString("<p style=\"color:green;\">%1</p>").arg(entry.rawText.toHtmlEscaped());
//    } else {
//        entry.htmlText = QString("<p style=\"color:black;\">%1</p>").arg(entry.rawText.toHtmlEscaped());
//    }

    int color_num = 0;


    for (auto it = level_name.begin(); it != level_name.end(); ++it) {
        //qDebug() << *it;
        if (level == *it) {
            entry.htmlText = QString("<p style=\"%1;\">%2</p>").arg(Str_Color[color_num - 1]).arg(entry.rawText.toHtmlEscaped());
            //entry.htmlText = QString("<p style=\"%1;\">%2</p>").arg(Str_Color[gogo]).arg(entry.rawText.toHtmlEscaped() + Str_Color[gogo]);
            break;
        }
        color_num++;
        //如果全部种类都没有
        if(color_num == level_name.size())
        {
            entry.htmlText = QString("<p style=\"%1;\">%2</p>").arg(Str_Color[8]).arg(entry.rawText.toHtmlEscaped());
            //entry.htmlText = QString("<p style=\"%1;\">%2</p>").arg(Str_Color[gogo]).arg(entry.rawText.toHtmlEscaped() + Str_Color[gogo]);
        }

    }

    // 保存日志
    allLogs.append(entry);



    // 如果没有筛选条件，直接显示
    if (ui->levelComboBox->currentText() == "全部级别" &&
            !ui->TimecheckBox->isChecked()) {
        if(!ui->keywordLineEdit->text().isEmpty())
        {
            if(entry.rawText.contains(ui->keywordLineEdit->text()))
            {
                //ui->logTextBrowser->append(entry.htmlText);
                ui->plainTextEdit->appendHtml(entry.htmlText);
                filteredLogs.append(entry);
                qDebug()<<ui->keywordLineEdit->text()<<entry.rawText;
            }
            //qDebug()<<"wu";
        }
        else
        {


            //ui->logTextBrowser->append(entry.htmlText);
            ui->plainTextEdit->appendHtml(entry.htmlText);
            filteredLogs.append(entry);
            //qDebug()<<"wu2";

        }
    }
    else if(level == ui->levelComboBox->currentText()){

        if(!ui->keywordLineEdit->text().isEmpty())
        {
            if(entry.rawText.compare(ui->keywordLineEdit->text()))
            {
                //ui->logTextBrowser->append(entry.htmlText);
                ui->plainTextEdit->appendHtml(entry.htmlText);
                filteredLogs.append(entry);
            }
        }
        else
        {
            //ui->logTextBrowser->append(entry.htmlText);
            ui->plainTextEdit->appendHtml(entry.htmlText);
            filteredLogs.append(entry);
        }

    }


    if (filteredLogs.size() > 2000) {
        QList<LogEntry> temp = filteredLogs.mid(1000, 2000); // 截取前100条
        filteredLogs.swap(temp); // 释放原有内存
    }

    if (allLogs.size() > 2000) {
        QList<LogEntry> temp = allLogs.mid(1000, 2000); // 截取前100条
        allLogs.swap(temp); // 释放原有内存
        //limitLogLines(ui->logTextBrowser, 2000);

        qDebug()<<"清理数据";
    }

    // 自动滚动到底部
    //ui->logTextBrowser->moveCursor(QTextCursor::End);
}

void FormLogShow::applyFilters() {
    QString selectedLevel = ui->levelComboBox->currentText();
    QString keyword = ui->keywordLineEdit->text();
    QDateTime startTime = ui->startTimeEdit->dateTime();
    QDateTime endTime = ui->endTimeEdit->dateTime();

    // 清空当前显示
    //ui->logTextBrowser->clear();
    ui->plainTextEdit->clear();

    // 筛选日志
    filteredLogs.clear();
    foreach (LogEntry entry, allLogs) {
        bool levelMatch = (selectedLevel == "全部级别") || (entry.level == selectedLevel);
        bool keywordMatch = keyword.isEmpty() || entry.content.contains(keyword, Qt::CaseInsensitive);
        bool timeMatch = true;

        if (ui->TimecheckBox->isChecked())
            timeMatch = timeMatch && (entry.timestamp >= startTime);

        if (ui->TimecheckBox->isChecked())
            timeMatch = timeMatch && (entry.timestamp <= endTime);

        if (levelMatch && keywordMatch && timeMatch) {
            filteredLogs.append(entry);
            //ui->logTextBrowser->append(entry.htmlText);
            ui->plainTextEdit->appendHtml(entry.htmlText);
        }
    }

    // 自动滚动到底部
//    ui->logTextBrowser->moveCursor(QTextCursor::End);
    ui->plainTextEdit->moveCursor(QTextCursor::End);
}

// 清空日志
void FormLogShow::clearLogs() {
    if (QMessageBox::question(this, "确认", "确定要清空所有日志吗？") == QMessageBox::Yes) {
        allLogs.clear();
        filteredLogs.clear();
        //ui->logTextBrowser->clear();
        ui->plainTextEdit->clear();
    }
}

// 导出日志
void FormLogShow::exportLogs() {
    if (allLogs.isEmpty()) {
        QMessageBox::information(this, "提示", "没有可导出的日志");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
                this, "导出日志", QDateTime::currentDateTime().toString("yyyy-MM-dd") + ".log",
                "文本文件 (*.txt);;所有文件 (*)"
                );

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            foreach (const LogEntry &entry, allLogs) {
                out << entry.rawText << "\n";
            }
            file.close();
            QMessageBox::information(this, "成功", "日志导出成功");
        } else {
            QMessageBox::warning(this, "错误", "无法打开文件进行写入");
        }
    }
}

// 显示全部日志
void FormLogShow::showAllLogs() {
    ui->levelComboBox->setCurrentText("全部级别");
    ui->keywordLineEdit->clear();
    ui->TimecheckBox->setChecked(false);
    applyFilters();
}

// 在添加新日志后调用此函数
void FormLogShow::limitLogLines(QTextBrowser* browser, int maxLines) {
    QTextDocument* doc = browser->document();
    while (doc->blockCount() > maxLines) {
        QTextCursor cursor = browser->textCursor();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
        cursor.deleteChar(); // 删除换行符
    }
}

void FormLogShow::updateActiveDateTimeEdit()
{
    //QList<QString> level_name = {"全部级别", "故障", "警告", "主窗口", "主流程"};
    addLog("故障", "系统启动成功");
    addLog("警告", "数据库连接已建立");
    addLog("主窗口", "检测到网络波动");
    addLog("故障", "文件操作失败：文件不存在");
    addLog("主流程", "用户登录成功");
}

void FormLogShow::on_applyFilterButton_clicked()
{
    applyFilters();
}

void FormLogShow::on_exportButton_clicked()
{
    exportLogs();
}

void FormLogShow::on_clearButton_clicked()
{
    clearLogs();
}

void FormLogShow::on_showAllButton_clicked()
{
    showAllLogs() ;
}
