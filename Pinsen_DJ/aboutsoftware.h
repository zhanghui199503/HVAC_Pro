#ifndef ABOUTSOFTWARE_H
#define ABOUTSOFTWARE_H

#include <QWidget>

namespace Ui {
class AboutSoftware;
}

class AboutSoftware : public QWidget
{
    Q_OBJECT

public:
    explicit AboutSoftware(QWidget *parent = nullptr);
    ~AboutSoftware();
Ui::AboutSoftware *ui;
private:

};
extern AboutSoftware *Aboutware;
#endif // ABOUTSOFTWARE_H
