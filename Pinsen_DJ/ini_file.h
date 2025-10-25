#ifndef INI_FILE_H
#define INI_FILE_H


#include <QString>
#include <QSettings>


class ini_file
{
public:
    ini_file();
    virtual ~ini_file();

    void Set_Control(QString FilePath, QString FileValue);

    QString Get_Control(QString FileValue);
    void Ini_Remove(QString FilePath);



private:
    QString m_qstrFileName;
    QSettings *m_psetting;
};

#endif // INI_FILE_H
