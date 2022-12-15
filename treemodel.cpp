#include "treemodel.h"

#include <QStringList>
#include "basereader.h"

TreeModel::TreeModel(QStandardItemModel *parent)
    : QStandardItemModel(parent)
{
    parentItem = this->invisibleRootItem();
    parentItem->setColumnCount(3);
    setupModelData();
}

TreeModel::~TreeModel()
{
    parentItem->clearData();
}

void TreeModel::updateModel()
{
    parentItem->clearData();
    this->clear();
    parentItem = this->invisibleRootItem();
    parentItem->setColumnCount(3);

    setupModelData();
}

void TreeModel::setupModelData()
{
    QVector<Country> modelData;
    if(!BaseReader::getInstance().getCountriesList(&modelData))
        return;

    for (Country data : modelData)
    {
        QList<QStandardItem *> countries;
        QString pathCountry = QString(":/icon/Countries/%1.png").arg(data.code) ;
        QStandardItem *countryIcon = new QStandardItem(pathCountry);
        QStandardItem *countryName = new QStandardItem(data.countryName);
        QStandardItem *counryCode = new QStandardItem(" ");
        countries.append(countryIcon);
        countries.append(countryName);
        countries.append(counryCode);
        parentItem->appendRow(countries);
        parentItem = countryIcon;

        for(int i = 0; i < data.operatorsList.size(); ++i)
        {
            QList<QStandardItem *> operators;
            QString pathOperator = QString(":/icon/Operators/%1_%2.png").arg(data.mcc).arg(data.operatorsList.at(i).mnc) ;
            QStandardItem *operatorIcon = new QStandardItem(pathOperator);
            QString operatorFullName = data.operatorsList.at(i).operatorName + " " + "(" + QString::number(data.mcc) + ", " + QString::number(data.operatorsList.at(i).mnc) + ")";
            QStandardItem *operatorName = new QStandardItem(operatorFullName);
            QStandardItem *mnc = new QStandardItem(" ");
            operators.append(operatorIcon);
            operators.append(operatorName);
            operators.append(mnc);
            parentItem->appendRow(operators);
        }
        parentItem = this->invisibleRootItem();
    }
}
