#include "tree.h"

Tree::Tree(QTreeView *parent) : QTreeView(parent)
{
    this->setModel(&model);
    this->setItemDelegate(&viewDelegate);
    this->setWindowTitle(QObject::tr("Operators by country"));
    this->setColumnWidth(0, 60);
    connect(&viewDelegate, &TreeViewDelegate::dataChamged, &model,  &TreeModel::updateModel);
}

void Tree::updateModel()
{

}
