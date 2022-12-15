#include <QPainter>
#include <QApplication>
#include <QPixmap>
#include <QDebug>
#include <QStandardItem>
#include <QMouseEvent>
#include "treeviewdelegate.h"
#include "basereader.h"

TreeViewDelegate::TreeViewDelegate()
{
    modelEdited = nullptr;
    connect(&editOperatorWindow, &EditOperator::saveNewData, this,  &TreeViewDelegate::saveNewDataTobase);
}

TreeViewDelegate::~TreeViewDelegate()
{
}

void TreeViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int hierarchyLevel = 1;
    QModelIndex seekRoot = index;
    while(seekRoot.parent() != QModelIndex())
    {
        seekRoot = seekRoot.parent();
        hierarchyLevel++;
    }

    if(option.state & QStyle::State_MouseOver && index.column() == 2 && index.parent() != QModelIndex())//check if item is hovered
    {
        QPushButton  btn;
        btn.setText("+");
        btn.setStyleSheet("border: 1px solid black; text-align: left; background: white");
        btn.setGeometry(option.rect);
        QPixmap map = QPixmap::grabWidget(&btn);
        painter->drawPixmap(option.rect.x(),option.rect.y(),map);
    }

    if (index.column() == 0)
    {
        QImage image(index.model()->data(index).toString());
        QRect rect = option.rect;
        rect.setSize(image.size());
        painter->drawImage(rect, image);
    }
    else
        QStyledItemDelegate::paint(painter, option, index);

}

QSize TreeViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setWidth(1000);
    return size;
}

bool TreeViewDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(event->type() == QEvent::MouseButtonPress && index.column() == 2 && index.parent() != QModelIndex())
    {
        modelEdited = model;
        editedModelIndex = index;
        addNewOperator();
    }

    if(event->type() == QEvent::MouseButtonDblClick && index.parent() != QModelIndex())
    {
        modelEdited = model;
        editedModelIndex = index;
        editOperator();
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void TreeViewDelegate::saveNewDataTobase(const QString &name, const QString &mcc, const QString &mnc, const bool isNewItem)
{
    QString operatorInfo = name + " " + "(" + mcc + ", " + mnc + ")";
    if(!isNewItem)
    {
        QModelIndex dataIndex = editedModelIndex.sibling(editedModelIndex.row(), 1);
        modelEdited->setData(dataIndex, operatorInfo);
    }
    else
    {
        QStandardItemModel *sModel = qobject_cast<QStandardItemModel *>(modelEdited);
        QStandardItem *item = sModel->itemFromIndex(editedModelIndex.sibling(editedModelIndex.row(), 0).parent());

        QList<QStandardItem *> newRows;
        newRows.append(new QStandardItem(":/icon/Operators/unnown.png"));
        newRows.append(new QStandardItem(operatorInfo));
        newRows.append(new QStandardItem(" "));
        item->appendRow(newRows);        
    }

    Operators newOperator;
    newOperator.mnc = mnc.toInt();
    newOperator.mcc = mcc.toInt();
    newOperator.operatorName = name;
    BaseReader::getInstance().saveOperatorToBase(&newOperator, isNewItem);
    if(isNewItem)
        emit dataChamged();
}

void TreeViewDelegate::editOperator()
{
    QModelIndex dataIndex = editedModelIndex.sibling(editedModelIndex.row(), 1);
    QModelIndex imageIndex = editedModelIndex.sibling(editedModelIndex.row(), 0);
    QString data = editedModelIndex.model()->data(dataIndex).toString();
    QStringList nameSplit = data.split('(');
    QStringList mccMNC = nameSplit.at(1).split(',');
    QString mnc = mccMNC.at(1);
    mnc.remove(0, 1);
    mnc.remove(')');
    QModelIndex parentIndex = editedModelIndex.sibling(editedModelIndex.row(), 0).parent();
    QPixmap pix(editedModelIndex.model()->data(imageIndex).toString());
    QPixmap pixCounry(parentIndex.model()->data(parentIndex).toString());
    editOperatorWindow.setDataForm(nameSplit.at(0), mccMNC.at(0), mnc, pix, pixCounry);
    editOperatorWindow.show();
}

void TreeViewDelegate::addNewOperator()
{
    QPixmap pix(":/icon/Operators/unnown.png");
    editOperatorWindow.setDataForm("", "0", "0", pix, pix, true);
    editOperatorWindow.show();
}
