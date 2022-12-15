#ifndef BASEREADER_H
#define BASEREADER_H

#include <QSqlQuery>

#include "infostructures.h"


class BaseReader
{
public:
    static BaseReader &getInstance();
    bool getCountriesList(QVector<Country> *countriesVector);
    void saveOperatorToBase(Operators *newOperator, bool isNewOperator);
    QString getCounryCodeByMcc(int mcc);

private:
    BaseReader();
    ~BaseReader();
    BaseReader(const BaseReader&) = delete;
    BaseReader(BaseReader&&) = delete;
    BaseReader& operator=(const BaseReader&) = delete;
    BaseReader& operator=(BaseReader&&) = delete;
    QSqlDatabase m_database;
    bool getOperatorsByCounry(Country &country);
};

#endif // BASEREADER_H
