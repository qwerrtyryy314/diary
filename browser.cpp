#include "browser.h"
#include "common.h"
#include <customdelegate.h>
#include <sqlconnectiondialog.h>
#include "textedit.h"
#include <QSqlDriver>

Browser::Browser(QWidget *parent) :
    QWidget(parent)
{

    treeView = new QTreeView(this);
    treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    treeView->setSortingEnabled(false);
    treeView->setSelectionBehavior(QAbstractItemView::SelectItems);//TODO: selection only for 1st col
    //TODO: select only children of same parent
    //treeView->setDragDropMode(QAbstractItemView::DragDrop);
    //TreeModel.setHeaderData()
    //? treeView->setEditTriggers(QAbstractItemView::DoubleClicked);
    QSizePolicy sizePolicy0(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy0.setHorizontalStretch(1);
    sizePolicy0.setVerticalStretch(0);
    sizePolicy0.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
    treeView->setSizePolicy(sizePolicy0);

    textEdit = new TextEdit(this);
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(2);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
    textEdit->setSizePolicy(sizePolicy1);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(treeView);
    splitter->addWidget(textEdit);
    QHBoxLayout *hboxLayout = new QHBoxLayout();
    hboxLayout->addWidget(splitter);
    setLayout(hboxLayout);

    //setCentralWidget(treeWidget);
    //connect(treeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(testSlot(QModelIndex)));
    isConnected = false;
    createActions();

    QSqlDatabase::database("diary", false).close();
    QSqlDatabase::removeDatabase("diary");
    db = QSqlDatabase::addDatabase("QSQLITE", "diary");
    db.setDatabaseName("../diary.sqlite");//TODO:absolute path?
    if(db.open())
    {
        //emit connected(true); //TODO: signal here?
        isConnected=true;
        //just to test
        initTree();
    }
    else
        QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
                                                                     "opening the connection: ") + db.lastError().text());
    //moveIndex = 0;
}

void Browser::createActions()
{
    //    addTreeWidgetItemAction = new QAction(tr("Add tree element"), treeView);
    //    connect(addTreeWidgetItemAction,SIGNAL(triggered()),this,SLOT(addTreeWidgetItemSlot()));
    //    treeView->addAction(addTreeWidgetItemAction);
    //    delTreeWidgetItemAction = new QAction(tr("Delete tree element"), treeView);
    //    connect(delTreeWidgetItemAction,SIGNAL(triggered()),this,SLOT(delTreeWidgetItemSlot()));
    //    treeView->addAction(delTreeWidgetItemAction);

    initTreeAction = new QAction(tr("Init tree"), treeView);
    connect(initTreeAction,SIGNAL(triggered()),this,SLOT(initTree()));
    treeView->addAction(initTreeAction);

    addItemAction = new QAction(tr("Add item"), treeView);
    connect(addItemAction,SIGNAL(triggered()),this,SLOT(addItem()));
    treeView->addAction(addItemAction);

    delItemAction = new QAction(tr("Delete item"), treeView);
    connect(delItemAction,SIGNAL(triggered()),this,SLOT(delItem()));
    treeView->addAction(delItemAction);

    beginMoveItemAction = new QAction(tr("Begin move"), treeView);
    connect(beginMoveItemAction,SIGNAL(triggered()),this,SLOT(beginMoveItem()));
    treeView->addAction(beginMoveItemAction);

    endMoveItemAction = new QAction(tr("End move"), treeView);
    connect(endMoveItemAction,SIGNAL(triggered()),this,SLOT(endMoveItem()));
    treeView->addAction(endMoveItemAction);
    endMoveItemAction->setEnabled(false);

    connect(treeView,SIGNAL(clicked(QModelIndex)),this,SLOT(showText(QModelIndex)));
    connect(textEdit,SIGNAL(saveToDBsignal(QByteArray)),this,SLOT(saveToDB(QByteArray)));

    treeView->setContextMenuPolicy(Qt::ActionsContextMenu);

    //connect(treeWidget,SIGNAL(clicked(QModelIndex)),this,SLOT(deselectTreeWidgetItemSlot(QModelIndex)));


}

QSqlError Browser::addConnection(const QString &driver, const QString &dbName, const QString &host,
                                 const QString &user, const QString &passwd, int port)
{
    static int cCount = 0;

    QSqlError err;
    //QSqlDatabase db
    db = QSqlDatabase::addDatabase(driver, QString("Browser%1").arg(++cCount));
    db.setDatabaseName(dbName);
    db.setHostName(host);
    db.setPort(port);
    if (db.open(user, passwd))
        isConnected=true; else
    {
        err = db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(QString("Browser%1").arg(cCount));

    }
    //connectionWidget->refresh();//TODO:refresh tree?

    return err;
}

void Browser::addConnection()
{
    SqlConnectionDialog dialog(this);
    if (dialog.exec() != QDialog::Accepted)
        return;

    if (dialog.useFileDatabase()) {
        //FIXME: absolute path to db?
        QSqlDatabase::database("diary", false).close();
        QSqlDatabase::removeDatabase("diary");
        db = QSqlDatabase::addDatabase("QSQLITE", "diary");
        db.setDatabaseName("diary.sqlite");
        if(db.open())
        {
            //emit connected(true); //TODO: signal here?
            isConnected=true;
        }
        else
            QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
                                                                         "opening the connection: ") + db.lastError().text());
        //connectionWidget->refresh();//TODO: refresh tree here
    } else {
        QSqlError err = addConnection(dialog.driverName(), dialog.databaseName(), dialog.hostName(),
                                      dialog.userName(), dialog.password(), dialog.port());
        if (err.type() == QSqlError::NoError)
            isConnected=true;
        else
            QMessageBox::warning(this, tr("Unable to open database"), tr("An error occurred while "
                                                                         "opening the connection: ") + err.text());
    }

}

/*
void Browser::showTable(const QString &t)
{
    QSqlTableModel *model = new QSqlTableModel(table, connectionWidget->currentDatabase());
    model->setEditStrategy(QSqlTableModel::OnFieldChange);//?(default)
    model->setTable(connectionWidget->currentDatabase().driver()->escapeIdentifier(t, QSqlDriver::TableName));
    model->select();

    if (model->lastError().type() != QSqlError::NoError)
        emit statusMessage(model->lastError().text());
    table->setModel(model);

    table->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::EditKeyPressed);
    connect(table->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentChanged()));

    if(!table->isHidden())
        setInputMasks();
    updateActions();
    TableTranslation();
    for(int i=0;i<model->columnCount();i++)
    {
        if((model->headerData(i,Qt::Horizontal).toString().compare("id")==0)&&(!table->isColumnHidden(i)))
            table->setColumnHidden(i,true);
        else
            table->setColumnHidden(i,false);
    }

    table->resizeColumnsToContents();
    table->setSortingEnabled(true);
}
*/

void Browser::initTree()
{   //TODO: move to thread
    //TODO: query error
    QStringList headers;
    headers << tr("ID") << tr("Parent ID")<<tr("Position");
    treeModel = new TreeModel(headers,treeView);
    treeView->setModel(treeModel);
    itemSelectionModel = new ItemSelectionModel(treeModel);
    treeView->setSelectionModel(itemSelectionModel);
    //treeView->columnAt(1);

    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT id,parentid,pos,value FROM items ORDER BY id ASC, pos ASC");
    QList<T_item*> itemList;
    while(query->next())
    {
        T_item *item = new T_item;
        item->id=query->value(0).toInt();
        item->parentId=query->value(1).toInt();
        item->pos=query->value(2).toInt();
        item->value=query->value(3).toString();//FIXME: will eat ram, remove
        itemList<<item;
    }
    query->clear();//?
    if(!itemList.isEmpty())
    {
        treeModel->setupTree(itemList);
        //qDeleteAll(itemList);
    }
}

void Browser::showText(QModelIndex index)//TODO: save text to current index
{
    QSqlQuery *query = new QSqlQuery(db);
    query->exec("SELECT id,value FROM items");
    bool match = false;
    while(query->next())
    {
        if(query->value(0).toInt() == treeModel->itemData(index).value(0).toInt())
        {
            match = true;
            textEdit->dbOpenRecord(query->value(1).toByteArray());//TODO:textedit::save to db
            //qDebug()<<query->value(1);
            break;
        }
    }
    if(!match)
        qDebug()<<"bad index:"<<index;//FIXME: index
    query->clear();
}

void Browser::saveToDB(const QByteArray data)//TODO: html?
{
    if(treeView->currentIndex().isValid())
    {
        //QSqlQuery *query = new QSqlQuery(db);
        QSqlField sqlData(QString("value"),QVariant::ByteArray);
        sqlData.setValue(data);
        //FIXME:send bytearray
        //qDebug()<<sqlData;
//        qDebug()<<"Formatted_string:-------------------------------------------------------------------------------------------";
//        qDebug()<<db.driver()->formatValue(sqlData,true);
//        qDebug()<<"Default_string:---------------------------------------------------------------------------------------------";
//        qDebug()<<sqlData.value().toString();
//        qDebug()<<"data:------------------------------------------------------------------------------------------------------------";
//        qDebug()<<data;
//        qDebug()<<"------------------------------------------------------------------------------------------------------------";

        QSqlQuery query(db);
        query.prepare(QString("UPDATE items\n"
                      "SET value=?\n"
                      "WHERE id=%1;").arg('6'));
        query.addBindValue(data);
       //query.addBindValue('6');
        query.exec();
//        if(!query->exec(QString("UPDATE items\n"
//                                "SET value=%1\n"
//                                "WHERE id=%2;").arg(db.driver()->formatValue(sqlData,false)).arg('6')));
        qDebug()<<query.lastError();
    }
}

//For example, to allow the user to drag and drop an image onto a QTextEdit, you could the implement these functions in the following way:

//    bool TextEdit::canInsertFromMimeData( const QMimeData *source ) const
//     {
//        if (source->hasImage())
//            return true;
//        else
//            return QTextEdit::canInsertFromMimeData(source);
//    }

//We add support for image MIME types by returning true. For all other MIME types, we use the default implementation.

//    void TextEdit::insertFromMimeData( const QMimeData *source )
//     {
//        if (source->hasImage())
//         {
//            QImage image = qvariant_cast<QImage>(source->imageData());
//            QTextCursor cursor = this->textCursor();
//            QTextDocument *document = this->document();
//            document->addResource(QTextDocument::ImageResource, QUrl("image"), image);
//            cursor.insertImage("image");
//        }
//    }



void Browser::addItem()
{//TODO:addquery
    //TODO:id/pos indexes for item
    //    treeView->expandAll();
    //    for (int column = 0; column < treeModel->columnCount(); ++column)
    //    {
    //        treeView->resizeColumnToContents(column);
    //    }
    //TODO: generate id, find parent id, set position(last?)

    //FIXME: add items after old items deleted
    treeView->setDragEnabled(true);
    T_item *itemLink = new T_item;
    itemLink->id=99;//FIXME: generate unique id (get from DB!)somehow
    itemLink->parentId=treeModel->itemLink(treeView->currentIndex())->id;
    itemLink->pos=treeModel->indexChildCount(treeView->currentIndex());//FIXME: generate unique pos somehow
    itemLink->value="000";

    treeModel->insertRow(treeView->currentIndex(),itemLink);

}

void Browser::delItem()
{//TODO:deletequery
    //TODO: make sure child items are cleared
    treeModel->removeRow(treeView->currentIndex().row(),treeView->currentIndex().parent());
    //TODO: remove by row only?
    //FIXME: mem leak
    //FIXME: if index is valid!
    //treeModel->removeRow(0,treeView->currentIndex().parent());
}

void Browser::beginMoveItem()
{
    moveIndexList = treeView->selectionModel()->selectedIndexes();
    endMoveItemAction->setEnabled(true);
    treeView->setSelectionMode(QAbstractItemView::NoSelection);
}

void Browser::endMoveItem()//TODO: move to a new parent; or move above/below selected item
{
    //TODO: Esc for cancel selection
    if(moveIndexList.size()>0)
    {
        endMoveItemAction->setEnabled(false);
        treeModel->moveRows(moveIndexList,treeView->currentIndex());
    }
    treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

//TODO: custom delegate to move up/down

//void TreeWidget::mousePressEvent(QMouseEvent *event)
//{//TODO: better deselection
//    QModelIndex item = indexAt(event->pos());
//    bool selected = selectionModel()->isSelected(indexAt(event->pos()));
//    QTreeView::mousePressEvent(event);
//    if (selected)
//        selectionModel()->select(item, QItemSelectionModel::Deselect);
//}
