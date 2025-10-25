#ifndef SHOWPICTURE_H
#define SHOWPICTURE_H

#include <QWidget>

namespace Ui {
class showpicture;
}

class showpicture : public QWidget
{
    Q_OBJECT

public:
    explicit showpicture(QWidget *parent = nullptr);
    ~showpicture();

private:
    Ui::showpicture *ui;
};
extern showpicture *showLogo;
#endif // SHOWPICTURE_H
