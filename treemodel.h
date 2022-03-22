#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QStandardItemModel>
#include "basereader.h"

class TreeModel : public QStandardItemModel
{
    Q_OBJECT

public:
    TreeModel(QStandardItemModel *parent = nullptr);
    ~TreeModel();
public slots:
    void updateModel();
private:
    void setupModelData();
    QStandardItem *parentItem;
};
#endif // TREEMODEL_H
