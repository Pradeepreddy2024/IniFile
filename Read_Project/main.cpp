#include "Read.h"
#include <QSettings>
#include <QDebug>
#include <QString>
#include <QSysInfo>

void ReadWrite::updateuser(QString inplabel, QString filename) {
    QTextStream in(stdin);

    QSettings settings(filename, QSettings::IniFormat);
    QStringList sections = settings.childGroups();

    if (sections.contains(inplabel)) {

        settings.beginGroup(inplabel);

        qDebug() << "Enter your name:";

        QString uname;
        in.readLineInto(&uname);
        QString storedName = settings.value("Name").toString();

        if (storedName == uname) {

            qDebug() << "Name matched successfully.";
            qDebug() << "What do you want to update?";
            qDebug() << "1 - Age";
            qDebug() << "2 - Company";

            QString choiceStr;
            in.readLineInto(&choiceStr);
            int choice = choiceStr.toInt();

            if (choice == 1) {

                qDebug() << "Enter new Age:";

                QString ageStr;
                in.readLineInto(&ageStr);
                int newAge = ageStr.toInt();

                settings.setValue("Age", newAge);
                qDebug() << "Age updated successfully.";

            } else if (choice == 2) {

                qDebug() << "Enter new Company:";

                QString company;
                in.readLineInto(&company);
                settings.setValue("Company", company);

                qDebug() << "Company updated successfully.";

            } else {

                qDebug() << "Invalid choice.";

            }

        } else {

            qDebug() << "Name doesn't match with stored record.";
        }

        settings.endGroup();
    } else {

        qDebug() << "User label not found in INI file.";

    }
}

void ReadWrite::addnewuser(QString filename) {
    QSettings settings(filename, QSettings::IniFormat);
    QTextStream in(stdin);

    qDebug() << "Enter label:";
    QString newUserLabel;
    in.readLineInto(&newUserLabel);

    qDebug() << "Enter name:";
    QString newUserName;
    in.readLineInto(&newUserName);

    qDebug() << "Enter age:";
    QString newUserAgeStr;
    in.readLineInto(&newUserAgeStr);
    int newUserAge = newUserAgeStr.toInt();

    qDebug() << "Enter company:";
    QString newUserCompany;
    in.readLineInto(&newUserCompany);

    settings.beginGroup(newUserLabel);
    settings.setValue("Name", newUserName);
    settings.setValue("Age", newUserAge);
    settings.setValue("Company", newUserCompany);
    settings.endGroup();

    qDebug() << "New user added successfully!";
}


void ReadWrite::readAllUsers(QString filename) {

    //qDebug()<<"Hello from inside"
    QSettings settings(filename, QSettings::IniFormat);


    QStringList users = settings.childGroups();
    qDebug();


    for (const QString &user : users) {

        settings.beginGroup(user);

        QString name = settings.value("Name").toString();
        int age = settings.value("Age").toInt();
        QString cname = settings.value("Company").toString();


        qDebug().noquote() << user << ": details: ";
        qDebug() << "Name:" << name;
        qDebug()<< "Age:" << age;
        qDebug() <<"Company:"<<cname;
        qDebug();


        settings.endGroup();
    }
}

int main(){

    qDebug()<<"Hello";
    QString filepath = "config.ini";
    ReadWrite r;
    r.readAllUsers(filepath);
    r.addnewuser(filepath);
    return 0;
}

