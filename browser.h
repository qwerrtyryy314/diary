#ifndef BROWSER_H
#define BROWSER_H

//#include <QWidget>
#include <QtGui>
#include <QtSql>
#include "treemodel.h"
#include "itemselectionmodel.h"
#include <QTreeView>

//class TreeWidget : public QTreeWidget
//{
//public:
//    TreeWidget(QWidget *parent) : QTreeWidget(parent) {}
//    virtual ~TreeWidget() {}
//    virtual void mousePressEvent(QMouseEvent *event);
//};

class TextEdit;
class Browser : public QWidget
{
    Q_OBJECT
public:
    explicit Browser(QWidget *parent = 0);
    bool isConnected;
public slots:
    void addConnection();//public?

signals:
private slots:
    void addItem();
    void delItem();
    void beginMoveItem();
    void endMoveItem();
    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                                     const QString &user, const QString &passwd, int port);
    //void deselectTreeWidgetItemSlot(const QModelIndex index);
    void initTree();
    void showText(QModelIndex index);
    void saveToDB(const QByteArray data);
private:
    void createActions();
    QSqlDatabase db;
    QTreeView *treeView;
    TreeModel *treeModel;
    ItemSelectionModel *itemSelectionModel;
    TextEdit *textEdit;
    QAction *addTreeWidgetItemAction;
    QAction *delTreeWidgetItemAction;
    QAction *initTreeAction;
    QAction *addItemAction;
    QAction *delItemAction;
    QAction *beginMoveItemAction;
    QAction *endMoveItemAction;
    QModelIndexList moveIndexList;
};

#endif // BROWSER_H
