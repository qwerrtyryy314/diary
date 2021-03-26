/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QVariant>
#include "common.h"
#include "treeitem.h"

class TreeItem;

//class TreeModelPrivate;

//class QPersistentModelIndexData
//{
//public:
//    QPersistentModelIndexData() : model(0) {}
//    QPersistentModelIndexData(const QModelIndex &idx) : index(idx), model(idx.model()) {}
//    QModelIndex index;
//    QAtomicInt ref;
//    const QAbstractItemModel *model;
//    static QPersistentModelIndexData *create(const QModelIndex &index);
//    static void destroy(QPersistentModelIndexData *data);
//};

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(const QStringList &headers, QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const;

    void setupTree(const QList<T_item *> treeData);//private

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    QMap<int, QVariant> itemData(const QModelIndex &index) const;
    T_item * itemLink(const QModelIndex &index) const;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole);

    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex());
    bool insertRow(const QModelIndex &aparent, T_item *itemLink);
    bool insertRows(int position, int rows, QList<T_item *> itemLink,
                    const QModelIndex &parent = QModelIndex());
    bool removeRow(int arow, const QModelIndex &aparent);
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex());
    void moveRows(const QModelIndexList &sourceIndexList, const QModelIndex &newParentIndex);

    bool allowMove(const QModelIndex &srcParent, int start, int end, const QModelIndex &destinationParent, int destinationStart, Qt::Orientation orientation);

    int itemCount();
    int indexChildCount(const QModelIndex &index);
private:
    TreeItem *getItem(const QModelIndex &index) const;
    TreeItem *rootItem;
    QList<TreeItem*> items;
//private:
//    struct Change {
//        Change() : first(-1), last(-1) {}
//        Change(const Change &c) : parent(c.parent), first(c.first), last(c.last), needsAdjust(c.needsAdjust) {}
//        Change(const QModelIndex &p, int f, int l) : parent(p), first(f), last(l), needsAdjust(false) {}
//        QModelIndex parent;
//        int first, last;
//        // In cases such as this:
//        // - A
//        // - B
//        // - C
//        // - - D
//        // - - E
//        // - - F
//        //
//        // If B is moved to above E, C is the source parent in the signal and its row is 2. When the move is
//        // completed however, C is at row 1 and there is no row 2 at the same level in the model at all.
//        // The QModelIndex is adjusted to correct that in those cases before reporting it though the
//        // rowsMoved signal.
//        bool needsAdjust;

//        bool isValid() { return first >= 0 && last >= 0; }
//    };
//    QStack<Change> changes;

//    struct Persistent {
//        Persistent() {}
//        QHash<QModelIndex, QPersistentModelIndexData *> indexes;
//        QStack<QVector<QPersistentModelIndexData *> > moved;
//        QStack<QVector<QPersistentModelIndexData *> > invalidated;
//        void insertMultiAtEnd(const QModelIndex& key, QPersistentModelIndexData *data);
//    } persistent;
//    void endMoveRows();
//    bool beginMoveRows(const QModelIndex &sourceParent, int sourceFirst, int sourceLast, const QModelIndex &destinationParent, int destinationChild);
//    void itemsAboutToBeMoved(const QModelIndex &srcParent, int srcFirst, int srcLast, const QModelIndex &destinationParent, int destinationChild, Qt::Orientation);
//    void itemsMoved(const QModelIndex &srcParent, int srcFirst, int srcLast, const QModelIndex &destinationParent, int destinationChild, Qt::Orientation orientation);
//    void movePersistentIndexes(QVector<QPersistentModelIndexData *> indexes, int change, const QModelIndex &parent, Qt::Orientation orientation);
//signals:
//    void rowsAboutToBeMoved( const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destinationParent, int destinationRow);
//    void rowsMoved( const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row);
};



#endif
