#include "itemselectionmodel.h"
#include <QDebug>

ItemSelectionModel::ItemSelectionModel(QAbstractItemModel *parent) :
    QItemSelectionModel(parent)
{
}

ItemSelectionModel::~ItemSelectionModel()
{
}

void ItemSelectionModel::select(const QItemSelection &selection, SelectionFlags command)
{
    QItemSelectionModel::select(selection, command);
    updateSelection();
}

void ItemSelectionModel::updateSelection()
{
    QModelIndexList nodes = selectedIndexes();
    if(nodes.size()>1)
    {
        QModelIndex firstParent = nodes.at(0).parent();
        for(int i=1;i<nodes.size();i++)
        {
            if(nodes.at(i).parent()!=firstParent)
            {
                QItemSelectionModel::select(selection(),QItemSelectionModel::Deselect);
                QItemSelectionModel::select(currentIndex(),QItemSelectionModel::Select);
                break;
            }
        }
    }
}
