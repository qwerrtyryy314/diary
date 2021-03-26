#ifndef ITEMSELECTIONMODEL_H
#define ITEMSELECTIONMODEL_H

#include <QItemSelectionModel>

class ItemSelectionModel : public QItemSelectionModel
{
    Q_OBJECT
public:
    explicit ItemSelectionModel(QAbstractItemModel *parent=0);
    ~ItemSelectionModel();

signals:

public slots:
    virtual void select(const QItemSelection &selection, SelectionFlags command);
private:
    void updateSelection();
};

#endif // ITEMSELECTIONMODEL_H
