#ifndef BASEREADER_H
#define BASEREADER_H

#include <QSqlQuery>

#include "infostructures.h"


class BaseReader
{
public:
    BaseReader();
    ~BaseReader();

    bool getCountriesList(QVector<Country> *countriesVector);
    void saveOperatorToBase(Operators *newOperator, bool isNewOperator);
    QString getCounryCodeByMcc(int mcc);

private:
    QSqlDatabase m_database;
    bool getOperatorsByCounry(Country &country);
};

#endif // BASEREADER_H
