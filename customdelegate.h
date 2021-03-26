#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QtGui>
#include <QtWidgets>
#include <QVector>
//#include <QtSql>

class lineEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QWidget * createEditor (QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    explicit lineEditDelegate(const short &mask_t){maskType=mask_t;}
private:
    short maskType;
};

class comboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit comboBoxDelegate(const QStringList &slist,const QList<uint> &intlist,const uint foreignColIndex);
    explicit comboBoxDelegate(const QStringList &slist);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
private:
    QVector<QString> Items;
    QList<uint> Indexes;
    uint fr;
};

class TimeEditDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class DateTimeEditDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CUSTOMDELEGATE_H
