#ifndef COMMUNICATIONERROR_H
#define COMMUNICATIONERROR_H

#include <QWidget>

namespace Ui {
class Communicationerror;
}

class Communicationerror : public QWidget
{
    Q_OBJECT

public:
    explicit Communicationerror(QWidget *parent = nullptr);
    ~Communicationerror();
    Ui::Communicationerror *ui;
private:

};

extern Communicationerror *Heart_error;

#endif // COMMUNICATIONERROR_H
