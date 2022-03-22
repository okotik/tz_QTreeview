#ifndef TREE_H
#define TREE_H

#include <QTreeView>
#include "treemodel.h"
#include "treeviewdelegate.h"

class Tree : public QTreeView
{
    Q_OBJECT
public:
    explicit Tree(QTreeView *parent = nullptr);

public slots:
    void updateModel();

private:
    TreeModel model;
    TreeViewDelegate viewDelegate;
};

#endif // TREE_H
