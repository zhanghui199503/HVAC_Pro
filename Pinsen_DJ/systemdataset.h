#ifndef SYSTEMDATASET_H
#define SYSTEMDATASET_H

#include <QWidget>

namespace Ui {
class SystemDataSet;
}

class SystemDataSet : public QWidget
{
    Q_OBJECT

public:
    explicit SystemDataSet(QWidget *parent = nullptr);
    ~SystemDataSet();

private slots:
    void on_SelectPath_clicked();

    void on_SavePath_clicked();

private:
    Ui::SystemDataSet *ui;
};

extern SystemDataSet *SetSystemDataWindow;

#endif // SYSTEMDATASET_H
