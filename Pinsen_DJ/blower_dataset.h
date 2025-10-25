#ifndef BLOWER_DATASET_H
#define BLOWER_DATASET_H

#include <QWidget>
#include <Header_File.h>

namespace Ui {
class Blower_DataSet;
}

class Blower_DataSet : public QWidget
{
    Q_OBJECT

public:
    explicit Blower_DataSet(QWidget *parent = nullptr);
    ~Blower_DataSet();
    Ui::Blower_DataSet *ui;
private:

};
extern Blower_DataSet *Blower_Set;
#endif // BLOWER_DATASET_H
