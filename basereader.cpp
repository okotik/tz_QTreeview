#include <QFile>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>
#include "basereader.h"

BaseReader::BaseReader()
{
    const QString databaseName = "D:/MSYS2_Commander/mission/testove/OMsystem.db";
    if(QFile::exists(databaseName))
    {
        const QString hostName = "localhost";
        m_database = QSqlDatabase::addDatabase("QSQLITE");
        m_database.setConnectOptions("QSQLITE_BUSY_TIMEOUT=5000"); // установим время ожидания освобождения базы 5 сек
        m_database.setHostName(hostName);
        m_database.setDatabaseName(databaseName);

        m_database.open();
    }
}

BaseReader::~BaseReader()
{
    m_database.close();
}

bool BaseReader::getCountriesList(QVector<Country> *countriesVector)
{
    if(!countriesVector)
        return false;

    QSqlQuery query(m_database);
    query.prepare("SELECT"
                  " mcc, "
                  " code, "
                  " name, "
                  " mnc_length "
                  " FROM "
                  " countries ");


    if(!query.exec())
    {
        qWarning() << (QString("BaseReader::getCountriesList() SELECT SQL Error: %1").arg(query.lastError().text()));
        return false;
    }

    countriesVector->clear();

    QSqlRecord record = query.record();
    const int ix_mcc = record.indexOf("mcc");
    const int ix_code = record.indexOf("code");
    const int ix_name = record.indexOf("name");
    const int ix_mnc_length = record.indexOf("mnc_length");

    while(query.next())
    {
        Country country;
        country.mcc = query.value(ix_mcc).toInt();
        country.code = query.value(ix_code).toString();
        country.countryName = query.value(ix_name).toString();
        country.mncLength = query.value(ix_mnc_length).toInt();
        countriesVector->push_back(country);
    }

    for (Country &country : *countriesVector)
        getOperatorsByCounry(country);
}

void BaseReader::saveOperatorToBase(Operators *newOperator, bool isNewOperator)
{
    if(!newOperator)
    {
        qWarning() << "BaseReader::saveOperatorToBase() error nullptr";
        return;
    }

    QSqlQuery query(m_database);
    if(!isNewOperator)
    {
        query.prepare("UPDATE "
                      " operators "
                      " SET name = :newName "
                      " WHERE "
                      " mcc = :current_mcc "
                      " AND "
                      " mnc = :current_mnc");
    }
    else
    {
        query.prepare("INSERT INTO operators (mcc, mnc, name)"
                      "VALUES (:current_mcc, :current_mnc, :newName)");
    }

    query.bindValue(":newName", newOperator->operatorName);
    query.bindValue(":current_mcc", newOperator->mcc);
    query.bindValue(":current_mnc", newOperator->mnc);
    if(!query.exec())
    {
        qWarning() << (QString("BaseReader::saveOperatorToBase() SELECT SQL Error: %1").arg(query.lastError().text()));
    }
}

QString BaseReader::getCounryCodeByMcc(int mcc)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT"
                  " code "
                  " FROM "
                  " countries "
                  " WHERE "
                  " mcc = :mcc");
    query.bindValue(":mcc", mcc);

    if(!query.exec())
    {
        qWarning() << (QString("BaseReader::getCounryCodeByMcc() SELECT SQL Error: %1").arg(query.lastError().text()));
        return "";
    }


    QSqlRecord record = query.record();
    const int ix_code = record.indexOf("code");
    query.next();
    return query.value(ix_code).toString();
}

bool BaseReader::getOperatorsByCounry(Country &country)
{
    QSqlQuery query(m_database);
    query.prepare(" SELECT "
                  " mnc, "
                  " name "
                  " FROM "
                  " operators "
                  " WHERE "
                  " operators.mcc = :mcc");

    query.bindValue(":mcc", country.mcc);

    if(!query.exec())
    {
        qWarning() << (QString("BaseReader::getCountriesList() SELECT SQL Error: %1").arg(query.lastError().text()));
        return false;
    }

    country.operatorsList.clear();

    QSqlRecord record = query.record();
    const int ix_mnc = record.indexOf("mnc");
    const int ix_name = record.indexOf("name");

    while(query.next())
    {
        Operators operators;
        operators.mnc = query.value(ix_mnc).toInt();
        operators.operatorName = query.value(ix_name).toString();
        country.operatorsList.push_back(operators);
    }
}
