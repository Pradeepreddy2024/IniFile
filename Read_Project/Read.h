#ifndef READ_H
#define READ_H

#include <QString>

class ReadWrite {
public:
    void readAllUsers(QString filename);
    void updateuser(QString inplabel, QString filename);
    void addnewuser(QString filename);
};

#endif // READ_H
