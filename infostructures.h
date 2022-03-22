#ifndef INFOSTRUCTURES_H
#define INFOSTRUCTURES_H

#include <QString>
#include <QVector>

struct Operators
{
    unsigned int mnc = 0;
    unsigned int mcc = 0;
    QString operatorName;
};

struct Country
{
    unsigned int mcc = 0;
    QString code;
    QString countryName;
    unsigned int mncLength = 0;
    QVector<Operators> operatorsList;
};


#endif // INFOSTRUCTURES_H
