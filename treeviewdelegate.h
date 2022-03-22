#ifndef TREEVIEWDELEGATE_H
#define TREEVIEWDELEGATE_H

#include <QStyledItemDelegate>
#include <QPushButton>
#include "editoperator.h"

class QPushButton;
class TreeViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TreeViewDelegate();
    ~TreeViewDelegate() override;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;

signals:
    void dataChamged();

public slots:
    void saveNewDataTobase(const QString &name, const QString &mcc, const QString &mnc, const bool isNewItem);

private:
    void editOperator();
    void addNewOperator();
    EditOperator editOperatorWindow;
    QAbstractItemModel *modelEdited;
    QModelIndex editedModelIndex;
};

#endif // TREEVIEWDELEGATE_H
